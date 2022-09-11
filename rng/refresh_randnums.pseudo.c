void refresh_randnums(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = 1;
  piVar1 = (int *)&rand_num0_8002b468;
  piVar3 = &rand_num32_8002b4e8;
  do {
    piVar1 = piVar1 + 1;
    iVar2 = *piVar3;
    piVar3 = piVar3 + 1;
    iVar4 = iVar4 + 1;
    *piVar1 = *piVar1 - iVar2;
  } while (iVar4 < 0x19);
  iVar4 = 0x19;
  piVar1 = (int *)&rand_num0_8002b468;
  piVar3 = &rand_num25_8002b4cc;
  do {
    piVar1 = piVar1 + 1;
    iVar4 = iVar4 + 1;
    *piVar3 = *piVar3 - *piVar1;
    piVar3 = piVar3 + 1;
  } while (iVar4 < 0x38);
  return;
}
