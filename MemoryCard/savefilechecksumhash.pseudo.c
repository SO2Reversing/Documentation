uint GenerateHash(int pbuf,uint index,uint seed)

{
  uint value;
  
  value = *(ushort *)(index * 2 + pbuf) & 0x7fff;
  if (seed == 0xffff) {
    seed = tickRand(0x10);
  }
  value = value ^ value >> 8;
  return ((~index & 0xf ^ seed) << 4 | value & 0xf ^ (value & 0xff) >> 4 ^ seed) & 0xff;
}


int MemcardChecksum(undefined4 param_1,byte *buf,int Len)

{
  int checksum;
  int loop_i;
  
  loop_i = 0;
  checksum = 0;
  if (0 < Len) {
    do {
      loop_i = loop_i + 1;
      checksum = checksum + (uint)*buf;
      buf = buf + 1;
    } while (loop_i < Len);
  }
  return checksum;
}
