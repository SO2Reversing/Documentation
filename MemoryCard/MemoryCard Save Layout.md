# Memory Card Save File

The memory card save file has 896 Header Bytes.

Entries marked with a ? are assumptions, unknown or unconfirmed

The save file data grows, and is not a fixed size.

|hex offset | Bytes (start:end inclusive) |  Data  |
| -| -----| ----- |
|0000| 0:3 | Always ['S','C',0x13,0x01] |
|0004| 4:95 | Null terminated custom string format (?) |
|| 96:99 | 32bit word - (?) |
|| 100:103 | 32bit word - (?) |
|| 104:108 | 32bit word - (?) |
|| 108:111 | 32bit word - (?) |
|| 112:115 | 32bit word - (?) |
|| 116:119 | 32bit word - (?) |
|| 120:123 | 32bit word - (?) |
|| 124:127 | 32bit word - (?) |
|0060| 128:511 | 384 byte array of data - Same across saves (Hash?) |
|0200| 512:527 | "STAR OCEAN 03/01" |
|0210| 528:531 | Checksum 2 - 128byte header checksum |
|0214| 532:535 | Checksum 1 - full save checksum |
|0218| 536:537 | always 0x5555 |
|021A| 538:539 | 16bit Save Data Length(?) save data is aligned to 128byte sectors, remainder of sector filled with hash(?)|
|| 540:543 | Game Time in Minutes |
|| 544:547 | Number of Battles |
|| (?)      | (?)
|0260| 608:895| Header End |
|0380| 896:Len | Main Save Data |

## Checksum Calculation


```c
int MemcardChecksum(byte *buf,int Len){
  
  int Checksum = 0;
  
  for (i = 0; i < len; i++) {
    Checksum += (uint)buf[i];
  }
  
  return Checksum;
}
```

Before the checksums are calculated both checksums and bytes 536:537 (0x5555) are cleared and set to 0.

#### Checksum 1 is calculated first:
The checksum is the sum of all bytes from the begining of the file to the length stored at 021A.

Checksum 1 is then written back.


```c

*(uint32_t*)savebuf[0x0210] = 0;
*(uint32_t*)savebuf[0x0214] = 0;
*(uint16_t*)savebuf[0x0218] = 0;

*(uint32_t*)savebuf[0x021A] = (uint32_t)savelength;

*(uint32_t*)savebuf[0x0214] = MemcardChecksum(savebuf,savebuf[0x021A])

```


#### Checksum 2 is then calculated:
Checksum 2 includes the checksum 1 bytes.


```c
*(uint32_t*)savebuf[0x0210] = MemcardChecksum(savebuf[0x0200],0x80);
*(uint16_t*)savebuf[0x0218] = 0x5555;

```




## Checksum Failure

If checksum 2 fails then the save will appear in the load menu with the text "this save file is corrupt", and will not even give the option to load.  

Checksum 1 is checked after the save has been loaded into memory, if checksum 1 fails, a message will show after the blue loading bar completes, saying "unable to load save data corrupt".
