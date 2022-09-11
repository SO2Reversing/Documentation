package main

import "vendor:sdl2"
import "core:log"
import "core:os"
import core_img "core:image"
import "core:math"
import "core:mem"
import "core:strings"

WINDOW_TITLE  :: "SO2 Sprite Viewer";
WINDOW_X      := i32(0);
WINDOW_Y      := i32(0);
WINDOW_WIDTH  := i32(240);
WINDOW_HEIGHT := i32(460);
WINDOW_FLAGS  :: sdl2.WindowFlags{.SHOWN,};


CENTER_WINDOW :: true;


CTX :: struct {
	window:        ^sdl2.Window,
	surface:       ^sdl2.Surface,
	renderer:      ^sdl2.Renderer,

	should_close:  bool,
}

ctx := CTX{};


SpriteFile :: struct {
	filedata: []u8,
	header: []u32,
	unknown_data: []u8,
	sprite_layout: []u8,
	pallets: []u16,
	sprite_img_data: []u8,
}

Sprite :: struct {
	pallet_idx: u8,
	width: u8,
	height: u8,

	origin_x: i16,
	origin_y: i16,

	file_offset: u32,
}

SpriteTexture :: struct {
	sdl_texture: ^sdl2.Texture,
	pixels: [^]u16,
	width: i32,
	height: i32,
	row: i32,
}

init_sdl :: proc() -> (ok: bool) {
	if sdl_res := sdl2.Init(sdl2.INIT_VIDEO); sdl_res < 0 {
		log.errorf("sdl2.init returned %v.", sdl_res);
		return false;
	}

	if CENTER_WINDOW {
		/*
			Get desktop bounds for primary adapter
		*/
		bounds := sdl2.Rect{};
		if e := sdl2.GetDisplayBounds(0, &bounds); e != 0 {
			log.errorf("Unable to get desktop bounds.");
			return false;
		}

		WINDOW_X = ((bounds.w - bounds.x) / 2) - (WINDOW_WIDTH  / 2) + bounds.x;
		WINDOW_Y = ((bounds.h - bounds.y) / 2) - (WINDOW_HEIGHT / 2) + bounds.y;
	}

	ctx.window = sdl2.CreateWindow(WINDOW_TITLE, WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);
	if ctx.window == nil {
		log.errorf("sdl2.CreateWindow failed.");
		return false;
	}

	ctx.surface = sdl2.GetWindowSurface(ctx.window);
	if ctx.surface == nil {
		log.errorf("sdl2.GetWindowSurface failed.");
		return false;
	}

	ctx.renderer = sdl2.CreateRenderer(ctx.window, -1, {.ACCELERATED, .PRESENTVSYNC});
	if ctx.surface == nil {
		log.errorf("sdl2.CreateRenderer failed.");
		return false;
	}

	return true;
}


process_input :: proc() {
	e: sdl2.Event;

	for sdl2.PollEvent(&e) {
		#partial switch(e.type) {
		case .QUIT:
			ctx.should_close = true;
		case .KEYDOWN:
			#partial switch(e.key.keysym.sym) {
			case .ESCAPE:
				ctx.should_close = true;
			}
		}
	}
}


loadspriteFile :: proc(filename: string) -> (file: SpriteFile, sprites: [dynamic]Sprite){
	data, ok := os.read_entire_file(filename, context.allocator)
	file.filedata = data

	file_id := (^u32)(&data[0])^

	header : []u32
	header_size := u32(0)

	sprite_layout_offset := u32(0)

	log.infof("file type: %08X\n",file_id);

	if  file_id == 0x00_00_00_28 {
		header_size = u32(16)
		header = mem.slice_data_cast([]u32, data)[0:4]
		sprite_layout_offset = u32(16+header[3])
		
	}
	else if file_id == 0x00_00_00_20 {
		header_size = u32(24)
		header = mem.slice_data_cast([]u32, data)[0:6]
		sprite_layout_offset = u32(16+header[5])
	}
	else if file_id == 0x00_00_00_2C {
		header_size = u32(24)
		header = mem.slice_data_cast([]u32, data)[0:6]
		sprite_layout_offset = u32(16+header[5])
	}
	else if file_id == 0x00_00_00_07 || file_id == 0x00_00_00_0C || file_id == 0x00_00_00_04{
		header_size = u32(24)
		header = mem.slice_data_cast([]u32, data)[0:6]
		sprite_layout_offset = u32(16+header[5])
	}

	file.header = header
	unknown_data := data[header_size:sprite_layout_offset]
	file.unknown_data = unknown_data
	//num_sprites := (^u32)(&data[num_sprites_offset])^
	num_sprites := u32(unknown_data[len(unknown_data)-6])
	log.infof("Num Sprites: %v\n",num_sprites);
	bytes_per_sprite := u32(12)
	sprite_layout_end := sprite_layout_offset+num_sprites*bytes_per_sprite
	sprite_layout := data[sprite_layout_offset:sprite_layout_end]
	file.sprite_layout = sprite_layout
	//sprites = make([dynamic]Sprite, num_sprites)


	log.infof("sprite layout offset: %02X\n",sprite_layout_offset);

	for i:=0; i< len(sprite_layout);i+=int(bytes_per_sprite) {
		pallet_idx := sprite_layout[i]
		sprite_width := sprite_layout[i+1]
		sprite_height := sprite_layout[i+2]

		sprite_origin_x := (^i16)(&sprite_layout[i+4])^
		sprite_origin_y := (^i16)(&sprite_layout[i+6])^

		sprite_data_offset := (^u32)(&sprite_layout[i+8])^

		sprite_pixel_data_bytes_len := u32(sprite_width*sprite_height)/2
		sprite_pixel_data_bytes := data[sprite_data_offset: sprite_data_offset + sprite_pixel_data_bytes_len]

		sprite := Sprite {
			pallet_idx,
			sprite_width,
			sprite_height,
			sprite_origin_x,
			sprite_origin_y,
			sprite_data_offset,
		}

		append(&sprites, sprite)

		log.infof("sprite: %v\n",sprite);
	}

	pallet_offset := sprite_layout_end + 4

	// for i:=int(sprite_layout_end); i< len(data); i+=4{
	// 	marker := (^u32)(&data[i])^
	// 	log.infof("marker: %08X\n",marker);
	// 	if marker == 0x00_00_00_80 {
	// 		pallet_offset = u32(i+4)
	// 		log.infof("found marker: %v\n",pallet_offset);
	// 		break
	// 	}
	// }


	


	pallets_size := ((^u32)(&data[sprite_layout_end])^)*2
	file.pallets = mem.slice_data_cast([]u16,data[pallet_offset:pallet_offset+pallets_size])
	file.sprite_img_data = data[pallet_offset+pallets_size:len(data)]

	log.infof("Pallet Offset: %v\n",pallet_offset);
	log.infof("Pallet Size: %v\n",pallets_size);
	log.infof("Pallet: %02X\n",file.pallets);
	return
}


main :: proc() {
	context.logger = log.create_console_logger();


	filename := "raw_sprites/1974.slz.raw0"

	fileinfo,sprites := loadspriteFile(filename)

    	




	image_width := i32(sprites[0].width)
	image_length := i32(sprites[0].height)

	sprite_row_widths := [8]int{}
	sprite_row_height := [8]int{}

	sprite_spacing_px := 1

	for sprite in sprites {
		sprite_row_widths[sprite.pallet_idx] += (int(sprite.width) + sprite_spacing_px)
		if int(sprite.height) + sprite_spacing_px > sprite_row_height[sprite.pallet_idx] {
			sprite_row_height[sprite.pallet_idx] = (int(sprite.height) + sprite_spacing_px)
		}
	}

	log.infof("sprite row widths: %v\n",sprite_row_widths);
	log.infof("sprite row heights: %v\n",sprite_row_height);



	tex_width := int(0)
	for width in sprite_row_widths {
		if width > tex_width {
			tex_width = width
		}
	}

	tex_height := int(0)
	for height in sprite_row_height {
		tex_height += height
	}




	log.infof("Texture Width: %v\n",tex_width);
	log.infof("Texture Height: %v\n",tex_height);

	//WINDOW_WIDTH  = i32(sprites[0].width)*10;
	//WINDOW_HEIGHT = i32(sprites[0].height)*10;

	WINDOW_WIDTH  = i32(tex_width);
	WINDOW_HEIGHT = i32(tex_height);


	if res := init_sdl(); !res {
		log.errorf("Initialization failed.");
		os.exit(1);
	}


	sprite_textures := make([]SpriteTexture,len(sprites))

	for sprite, idx in sprites {

		if sprite.width == 0 {continue}

		sprite_textures[idx].width = i32(sprite.width)
		sprite_textures[idx].height = i32(sprite.height)
		sprite_textures[idx].row = i32(sprite.pallet_idx)
		sprite_textures[idx].sdl_texture = sdl2.CreateTexture(ctx.renderer,
                       u32(sdl2.PixelFormatEnum.XBGR1555),
                       .STREAMING,
                       sprite_textures[idx].width,
                       sprite_textures[idx].height);

		sprite_textures[idx].pixels = 
			make([^]u16, sprite_textures[idx].width * sprite_textures[idx].height)

		sprite_pixel_data_bytes_len := u32(sprite_textures[idx].width*sprite_textures[idx].height)/2
		data := fileinfo.sprite_img_data[sprite.file_offset:sprite.file_offset+sprite_pixel_data_bytes_len]

		j := u32(0)
		for i := 0; i < len(data); i += 1 {

			first_pixel_pallet_idx := data[i] & 0b00001111
			second_pixel_pallet_idx := (data[i] & 0b11110000) >> 4

			pallet_offset := sprite.pallet_idx * 16

			first_pixel := fileinfo.pallets[first_pixel_pallet_idx + pallet_offset]
			second_pixel := fileinfo.pallets[second_pixel_pallet_idx + pallet_offset]

			sprite_textures[idx].pixels[j] = u16(first_pixel)
			sprite_textures[idx].pixels[j+1] = u16(second_pixel)
			j+=2
		}


		sdl2.UpdateTexture(sprite_textures[idx].sdl_texture, nil,
						   sprite_textures[idx].pixels, sprite_textures[idx].width * 2);

	}


	log.infof("Sprite Data: %v\n",sprite_textures);



	save_copy := true


	for !ctx.should_close{

		process_input();

	  	sdl2.SetRenderDrawColor(ctx.renderer, 0, 0, 0, 0xff);
	  	sdl2.RenderClear(ctx.renderer);


	  	x_blit_pos := []i32{0,0,0,0,0,0,0,0}
	  	for tex in sprite_textures {

	  		if tex.width == 0 {continue}

	  		y_blit_pos := i32(0)
  			for i:= tex.row; i>0; i-=1{
  				y_blit_pos += i32(sprite_row_height[tex.row-i])
  			}

	  		dst := sdl2.Rect{x_blit_pos[tex.row],y_blit_pos,tex.width,tex.height}


	  		sdl2.RenderCopy(ctx.renderer, tex.sdl_texture, nil, &dst);


	  		x_blit_pos[tex.row]+=tex.width
	  	}


	  	sdl2.RenderPresent(ctx.renderer);

	  	if save_copy == true {
	  		save_copy = false

	  		log.infof("blit pos: %v\n",x_blit_pos);


	  		sshot := sdl2.CreateRGBSurface(0, i32(tex_width), i32(tex_height), 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	  		sdl2.RenderReadPixels(ctx.renderer, nil, u32(sdl2.PixelFormatEnum.ARGB8888), sshot.pixels, sshot.pitch);

	  		savefilename := strings.concatenate({filename,".bmp"})

			sdl2.SaveBMP(sshot, strings.clone_to_cstring(savefilename));
			sdl2.FreeSurface(sshot);
	  	}

	}


}
