
# Star Ocean 2 File Table

Star Ocean 2 stores all of its resources in one large file.  
This file is positioned at sector 450, or 00:06:00 in minutes:seconds:frames format, on the CD.  
The game loads 24,576 bytes at this location, however only uses the first 23,040 Bytes of this file.  
These first 23,040 Bytes (0x1680 words) contain an encrypted file table, that lists the location and the size of each file.  
This is needed to load or extract individual files from the large archive.  

Each file table entry requires 5 bytes. So with 23,040 bytes, there will be 4608 entries.  

The encrypted file table is split into 2 parts.  
The first part is a contiguous array of 4608 4byte words which stores the file position in BCD MM:SS:FF size MSB.  
The second part is a contiguous array of 4608 single bytes which stores the second LSB half of file size in sectors.  

Before this file table can be used it needs to be decrypted.  
The encryption is an XOR style encryption where a key value is used to encrypt and decrypt the data.
The encryption is symetric, so the same algorithm can be used to encrypt and decrypt the table.

The key used is 0x13578642.

When the table is decrypted the 2 parts of the table can be combined to give the location of the file and the size.

Table Part 1 - Read as a 32bit word
|Byte 1 MSB | Byte 2| Byte 3| Byte 4 LSB|
| ----- | ----- | ----- | ----- |
|  SIZE MSB |  FRAMES | SECONDS  | MINUTES  |

Table Part 2 - Read as a 8bit byte
|Byte  |
| ----- |
|  SIZE LSB |

The full size can be obtained by combining the two size bytes into a 16bit short:
```c
uint16_t size = (u32_FileTablePtr[i] & 0xFF000000) >> 16 | (uint16_t)u8_FileTablePtr[i];
```
  
  
#### An example of the decrypted filetable for disk 1 can be found here:  
[File Table Disk 1](https://github.com/SO2Reversing/Documentation/blob/main/FileTable/Disk1FileTable.csv)

The first index of the table is not used, and in the game code is written with the location of the encrypted filetable
  
  
  
#### A very basic example of opening the BIN file and inplace decrypting is shown below:

```c
FILE* fp = fopen("SO2.BIN", "rb");
uint32_t fs = 23040;
uint8_t* fb = (uint8_t*) malloc(fs);
fread(fb, 1, fs, fp);
fclose(fp);

uint32_t u8_offset = 18432;
uint32_t tableEntries = 4608;
uint32_t key = 0x13578642;
uint32_t sectorSize = 2048;

uint8_t* u8_FileTablePtr = fb + u8_offset;
uint32_t* u32_FileTablePtr = (uint32_t*)fb;

for (size_t i = 0; i < tableEntries; i++) {
    u32_FileTablePtr[i] ^= key;
    key ^= (key << 1);
    u8_FileTablePtr[i] ^= key;
    key ^= ~0x13578642;
}
```
    


