undefined4 SLZDecompMode1(undefined4 param_1,byte *pSLZBuf,undefined4 *dst)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte *pbVar4;
  undefined4 *puVar5;
  uint pos;
  uint len;
  undefined4 uVar6;
  int loop_i;
  undefined4 uVar7;
  undefined4 uVar8;
  uint tokens;
  int num_tokens;
  
  tokens = 0;
  num_tokens = 1;
  while( true ) {
    while( true ) {
      num_tokens = num_tokens + -1;
      tokens = (int)tokens >> 1;
      if (num_tokens == 0) {
        num_tokens = 8;
        tokens = (uint)*pSLZBuf;
        pSLZBuf = pSLZBuf + 1;
      }
      if ((tokens & 1) == 0) break;
      bVar3 = *pSLZBuf;
      pSLZBuf = pSLZBuf + 1;
      *(byte *)dst = bVar3;
      dst = (undefined4 *)((int)dst + 1);
    }
    pos = (uint)*pSLZBuf | (pSLZBuf[1] & 0xf) << 8;
                    /* NOTE: min length of 3 implied, so len 0 = 3, len 15 = 18 */
    len = (uint)(pSLZBuf[1] >> 4);
    if (pos == 0) break;
    if (pos < 16) {
      loop_i = 0;
      if (len != 0xfffffffd) {
        do {
          loop_i = loop_i + 1;
          *(byte *)dst = *(byte *)((int)dst - pos);
          dst = (undefined4 *)((int)dst + 1);
        } while (loop_i < (int)(len + 3));
      }
    }
    else {
      switch(len) {
      case 0:
        pbVar4 = (byte *)((int)dst - pos);
        bVar3 = pbVar4[1];
        bVar2 = pbVar4[2];
        *(byte *)dst = *pbVar4;
        *(byte *)((int)dst + 1) = bVar3;
        *(byte *)((int)dst + 2) = bVar2;
        dst = (undefined4 *)((int)dst + 3);
        break;
      case 1:
        *dst = *(undefined4 *)((int)dst - pos);
        dst = dst + 1;
        break;
      case 2:
        bVar3 = *(byte *)((undefined4 *)((int)dst - pos) + 1);
        *dst = *(undefined4 *)((int)dst - pos);
        *(byte *)(dst + 1) = bVar3;
        dst = (undefined4 *)((int)dst + 5);
        break;
      case 3:
        puVar5 = (undefined4 *)((int)dst - pos);
        bVar3 = *(byte *)(puVar5 + 1);
        bVar2 = *(byte *)((int)puVar5 + 5);
        *dst = *puVar5;
        *(byte *)(dst + 1) = bVar3;
        *(byte *)((int)dst + 5) = bVar2;
        dst = (undefined4 *)((int)dst + 6);
        break;
      case 4:
        puVar5 = (undefined4 *)((int)dst - pos);
        bVar3 = *(byte *)(puVar5 + 1);
        bVar2 = *(byte *)((int)puVar5 + 5);
        bVar1 = *(byte *)((int)puVar5 + 6);
        *dst = *puVar5;
        *(byte *)(dst + 1) = bVar3;
        *(byte *)((int)dst + 5) = bVar2;
        *(byte *)((int)dst + 6) = bVar1;
        dst = (undefined4 *)((int)dst + 7);
        break;
      case 5:
        uVar6 = ((undefined4 *)((int)dst - pos))[1];
        *dst = *(undefined4 *)((int)dst - pos);
        dst[1] = uVar6;
        dst = dst + 2;
        break;
      case 6:
        puVar5 = (undefined4 *)((int)dst - pos);
        uVar6 = puVar5[1];
        bVar3 = *(byte *)(puVar5 + 2);
        *dst = *puVar5;
        dst[1] = uVar6;
        *(byte *)(dst + 2) = bVar3;
        dst = (undefined4 *)((int)dst + 9);
        break;
      case 7:
        puVar5 = (undefined4 *)((int)dst - pos);
        uVar6 = puVar5[1];
        bVar3 = *(byte *)(puVar5 + 2);
        bVar2 = *(byte *)((int)puVar5 + 9);
        *dst = *puVar5;
        dst[1] = uVar6;
        *(byte *)(dst + 2) = bVar3;
        *(byte *)((int)dst + 9) = bVar2;
        dst = (undefined4 *)((int)dst + 10);
        break;
      case 8:
        puVar5 = (undefined4 *)((int)dst - pos);
        uVar6 = puVar5[1];
        bVar3 = *(byte *)(puVar5 + 2);
        bVar2 = *(byte *)((int)puVar5 + 9);
        *dst = *puVar5;
        dst[1] = uVar6;
        *(byte *)(dst + 2) = bVar3;
        *(byte *)((int)dst + 9) = bVar2;
        *(byte *)((int)dst + 10) = *(byte *)((int)puVar5 + 10);
        dst = (undefined4 *)((int)dst + 0xb);
        break;
      case 9:
        puVar5 = (undefined4 *)((int)dst - pos);
        uVar6 = puVar5[1];
        uVar7 = puVar5[2];
        *dst = *puVar5;
        dst[1] = uVar6;
        dst[2] = uVar7;
        dst = dst + 3;
        break;
      case 10:
        puVar5 = (undefined4 *)((int)dst - pos);
        uVar6 = puVar5[1];
        uVar7 = puVar5[2];
        bVar3 = *(byte *)(puVar5 + 3);
        *dst = *puVar5;
        dst[1] = uVar6;
        dst[2] = uVar7;
        *(byte *)(dst + 3) = bVar3;
        dst = (undefined4 *)((int)dst + 0xd);
        break;
      case 0xb:
        puVar5 = (undefined4 *)((int)dst - pos);
        uVar6 = puVar5[1];
        uVar7 = puVar5[2];
        bVar3 = *(byte *)(puVar5 + 3);
        *dst = *puVar5;
        dst[1] = uVar6;
        dst[2] = uVar7;
        *(byte *)(dst + 3) = bVar3;
        *(byte *)((int)dst + 0xd) = *(byte *)((int)puVar5 + 0xd);
        dst = (undefined4 *)((int)dst + 0xe);
        break;
      case 0xc:
        puVar5 = (undefined4 *)((int)dst - pos);
        uVar6 = puVar5[1];
        uVar7 = puVar5[2];
        bVar3 = *(byte *)(puVar5 + 3);
        *dst = *puVar5;
        dst[1] = uVar6;
        dst[2] = uVar7;
        *(byte *)(dst + 3) = bVar3;
        bVar3 = *(byte *)((int)puVar5 + 0xe);
        *(byte *)((int)dst + 0xd) = *(byte *)((int)puVar5 + 0xd);
        *(byte *)((int)dst + 0xe) = bVar3;
        dst = (undefined4 *)((int)dst + 0xf);
        break;
      case 0xd:
        puVar5 = (undefined4 *)((int)dst - pos);
        uVar6 = puVar5[1];
        uVar7 = puVar5[2];
        uVar8 = puVar5[3];
        *dst = *puVar5;
        dst[1] = uVar6;
        dst[2] = uVar7;
        dst[3] = uVar8;
        dst = dst + 4;
        break;
      case 0xe:
        puVar5 = (undefined4 *)((int)dst - pos);
        uVar6 = puVar5[1];
        uVar7 = puVar5[2];
        uVar8 = puVar5[3];
        *dst = *puVar5;
        dst[1] = uVar6;
        dst[2] = uVar7;
        dst[3] = uVar8;
        *(byte *)(dst + 4) = *(byte *)(puVar5 + 4);
        dst = (undefined4 *)((int)dst + 0x11);
        break;
      case 0xf:
        puVar5 = (undefined4 *)((int)dst - pos);
        uVar6 = puVar5[1];
        uVar7 = puVar5[2];
        uVar8 = puVar5[3];
        *dst = *puVar5;
        dst[1] = uVar6;
        dst[2] = uVar7;
        dst[3] = uVar8;
        bVar3 = *(byte *)((int)puVar5 + 0x11);
        *(byte *)(dst + 4) = *(byte *)(puVar5 + 4);
        *(byte *)((int)dst + 0x11) = bVar3;
        dst = (undefined4 *)((int)dst + 0x12);
      }
    }
    pSLZBuf = pSLZBuf + 2;
  }
  return 1;
}
