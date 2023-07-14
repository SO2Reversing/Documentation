
It looks like the "Scene" files have the header 03000000

looking at file 3207 - uses renas bedroom as the BG - maybe this is the debug room
its comprised of a header, then 7 SLZ files:

1 - header    
2 - 0x1C - ?   
3 - 0x0410 - Maybe BG Layout Info   
4 - 0x0430 - BG IMG   
5 - 0xEAE8 - BG IMG   
6 - 0x01137C - Referenced in Header - ?   
7 - 0x016870 - Possible Glyph Alphabet   
8 - 0x017C24 - Referenced in Header - Sprite Sheets   

Some of these files are the actual BG IMG  
E.G. the files split at address 0xEAE8 and 0x0430  
There is another file that *seems* to hold animation and sprite data which is at the address 0x017C24  
Then there is another file that seems to hold the glyph information 0x016870  


Set a beak point at 8005e220

or at 8005e4cc
or at 8005e3d8


8005e1e0 - v0/24 = glyph index

set break point at 8005e1ac - a1-1 = glpyh index
