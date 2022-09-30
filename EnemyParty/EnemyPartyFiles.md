First 32bit word is file offset for image slz  
second word is (?)  
image section ends with FF FF FF FF  
next section is substitute pallet offset only used in some files  
section ends with FF FF FF FF  
next section starts with file offset for slz  
Maybe this section is AI script?  
section ends with FF FF FF FF  

next section has 12 bytes for each enemy in the file

section ends with 00 00 01 00 (?)

then the enemy status section  


Each enemy in the party has 96 bytes which store their stats

rows with ? are unconfirmed  
offset - value - size  
0 - HP - 32bit  
4 - MP - 32  
8 - EXP - 32  
12 - FOL - 32  
16 - SIZE X - 16
18 - SIZE Y - 16
20 - HIT BOX X - 16 ?  
22 - HIT BOX Y - 16 ?  
24 - DROP 1 - 16  
27 - DROP 2 - 16  
28 - ATK - 16 ?  
30 - DEF - 16 ?  
32 - DEX - 16 ?  
34 - ?  
36 - ?  
38 - AGI - 16 ?  

