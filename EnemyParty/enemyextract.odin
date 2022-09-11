package main

import "core:os"
import "core:log"
import "core:slice"
import "core:fmt"
import "core:mem"
import "core:strings"

main :: proc() {
	context.logger = log.create_console_logger()

	dirh, _ := os.open("1405-1968 - Enemy Party")

	fileinfo, _ := os.read_dir(dirh, 1000)

	enemy_map := make(map[string][]byte)

	for file in fileinfo {
		//log.infof("%v",file.name)
		data, ok := os.read_entire_file(file.fullpath)
		data_u32 := slice.reinterpret([]u32,data)
		data32_ptr := 0

		for sections := 0; sections < 3; {
			if(data_u32[data32_ptr] == 0xFFFFFFFF) {
				sections += 1
			}
			data32_ptr += 1
		}

		data32_ptr += 3 //skip first enemy

		data8_ptr := data32_ptr*4


		num_enemies := 1
		for {
			if(data[data8_ptr] == 0x00){
				data32_ptr += 1
				data8_ptr = data32_ptr*4
				break
			}
			num_enemies += 1
			data32_ptr += 3
			data8_ptr = data32_ptr*4
		}


		for i := 0; i < num_enemies; i+=1 {

			enemydata := data[data8_ptr:data8_ptr+92]

			enemyname := string(cstring(&enemydata[76]))


			if enemyname in enemy_map {
				map_data := enemy_map[enemyname]
				if mem.compare(map_data,enemydata) != 0 {
					new_name := strings.concatenate([]string{enemyname," variant"})
					enemy_map[new_name] = enemydata
				}
			}
			else {
				enemy_map[enemyname] = enemydata
			}

			data8_ptr += 92

		}

	}
	
	//しようはんい
	//しようこうか

	fmt.println("Name, HP, MP, EXP, FOL, DRP1, DRP2, ATK, DEF, DEX, AGI")
	for name,em_data in enemy_map {
		em_data_i32 := slice.reinterpret([]i32,em_data)
		em_data_u16 := slice.reinterpret([]u16,em_data)
		fmt.printf("%s, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i\n",name,em_data_i32[0],em_data_i32[1],em_data_i32[2],em_data_i32[3],em_data_u16[12],em_data_u16[13],em_data_u16[14],em_data_u16[15],em_data_u16[16],em_data_u16[19])
	}
}
