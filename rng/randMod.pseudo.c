uint RandMod(uint param_1)

{
  uint uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = randnum();
    uVar1 = uVar1 % param_1;
    if (param_1 == 0) {
      trap(0x1c00);
    }
  }
  return uVar1;
}
