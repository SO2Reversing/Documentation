undefined4 randnum(void)

{
  rand_idx_8002b464 = rand_idx_8002b464 + 1;
  if (0x37 < rand_idx_8002b464) {
    refresh_randnums();
    rand_idx_8002b464 = 1;
  }
  return *(undefined4 *)(&rand_num0_8002b468 + rand_idx_8002b464 * 4);
}
