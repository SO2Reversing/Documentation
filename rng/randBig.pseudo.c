uint randBig(void)

{
  uint uVar1;
  
  uVar1 = randnum();
  return uVar1 & 0x7fff;
}
