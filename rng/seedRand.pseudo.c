void seedRand(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 1;
  iVar1 = 0x15;
  rand_num55_8002b544 = param_1;
  for (iVar2 = 1; iVar2 < 0x37; iVar2 = iVar2 + 1) {
    *(int *)(&rand_num0_8002b468 + (iVar1 % 0x37) * 4) = iVar3;
    iVar3 = param_1 - iVar3;
    param_1 = *(int *)(&rand_num0_8002b468 + (iVar1 % 0x37) * 4);
    iVar1 = iVar1 + 0x15;
  }
  refresh_randnums();
  refresh_randnums();
  refresh_randnums();
  rand_idx_8002b464 = 0x37;
  return;
}
