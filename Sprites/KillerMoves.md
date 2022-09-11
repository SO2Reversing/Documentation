sprite header

28 00 00 00  
 first word in file - maybe Identifier  

44 00 00 00  
second word maybe header section size or image dimension?  

E4 00 00 00   
third word maybe header section size or total image dimension?  
offset to info? looks like next byte is number of sprites in file?  

E0 01 00 00   
forth word maybe header sections size  
seems to be the number of bytes of the first section of the header  
00 80 FF FF - starts after e.g. E0 01 00 00 number of bytes  

00 80 FF FF - looks to be image layout  
multiple images of different dimensions are stored in a single sprite file so there is a layout used that describes each image size and start offset?  
each layout is 3 words long  
e.g.  
00 18 2D 00 | 0C 00 2B 00 | 00 00 00 00  
or  
02 08 06 00 | 04 00 03 00 | 10 0B 00 00  

first word looks like its read as bytes  
byte 1: maybe sprite group? maybe pallet index?  
byte 2: sprite width  
byte 3: sprite height  
byte 4: ??  


second word - unknown? looks to be related to width and height  
first half of word related to width e.g. if width is 36 then its 20, if width is 24 or 32 its 12 varies by file?  
second half is related to width - looks like always width - 2? varies by file?  
This is likely to be the sprite origin.  

third word  
This looks like offset from the begining of the image data section in number of bytes  


Final header section is 80 00 00 00 | 00 00 85 0C  
Final section is 260 bytes contains multiple pallets
Pallet is XBGR1555 16-bit typical psx  

Image data starts now  

