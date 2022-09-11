undefined4 SLZDecompMode2(undefined4 param_1,byte *pSLZBuf,undefined4 *dst,int param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  uint pos;
  uint pos2;
  uint len;
  undefined4 uVar7;
  int loop_i;
  ushort uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 *?uncompressed_size?;
  uint tokens;
  int num_tokens;
  
  tokens = 0;
  num_tokens = 1;
  ?uncompressed_size? = (undefined4 *)((int)dst + param_4);
LAB_80012774:
  do {
    while( true ) {
      while( true ) {
        num_tokens = num_tokens + -1;
        if (?uncompressed_size? <= dst) {
          return 1;
        }
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
      pos = (uint)*pSLZBuf;
      pos2 = pos | (pSLZBuf[1] & 0xf) << 8;
      len = (uint)(pSLZBuf[1] >> 4);
                    /* If length is 15, then break to use RLE */
      if (0x11 < len + 3) break;
      if (0xf < pos2) {
        switch(len) {
        case 0:
          pbVar5 = (byte *)((int)dst - pos2);
          bVar3 = pbVar5[1];
          bVar2 = pbVar5[2];
          *(byte *)dst = *pbVar5;
          *(byte *)((int)dst + 1) = bVar3;
          *(byte *)((int)dst + 2) = bVar2;
          dst = (undefined4 *)((int)dst + 3);
          break;
        case 1:
          *dst = *(undefined4 *)((int)dst - pos2);
          dst = dst + 1;
          break;
        case 2:
          bVar3 = *(byte *)((undefined4 *)((int)dst - pos2) + 1);
          *dst = *(undefined4 *)((int)dst - pos2);
          *(byte *)(dst + 1) = bVar3;
          dst = (undefined4 *)((int)dst + 5);
          break;
        case 3:
          puVar6 = (undefined4 *)((int)dst - pos2);
          bVar3 = *(byte *)(puVar6 + 1);
          bVar2 = *(byte *)((int)puVar6 + 5);
          *dst = *puVar6;
          *(byte *)(dst + 1) = bVar3;
          *(byte *)((int)dst + 5) = bVar2;
          dst = (undefined4 *)((int)dst + 6);
          break;
        case 4:
          puVar6 = (undefined4 *)((int)dst - pos2);
          bVar3 = *(byte *)(puVar6 + 1);
          bVar2 = *(byte *)((int)puVar6 + 5);
          bVar1 = *(byte *)((int)puVar6 + 6);
          *dst = *puVar6;
          *(byte *)(dst + 1) = bVar3;
          *(byte *)((int)dst + 5) = bVar2;
          *(byte *)((int)dst + 6) = bVar1;
          dst = (undefined4 *)((int)dst + 7);
          break;
        case 5:
          uVar7 = ((undefined4 *)((int)dst - pos2))[1];
          *dst = *(undefined4 *)((int)dst - pos2);
          dst[1] = uVar7;
          dst = dst + 2;
          break;
        case 6:
          puVar6 = (undefined4 *)((int)dst - pos2);
          uVar7 = puVar6[1];
          bVar3 = *(byte *)(puVar6 + 2);
          *dst = *puVar6;
          dst[1] = uVar7;
          *(byte *)(dst + 2) = bVar3;
          dst = (undefined4 *)((int)dst + 9);
          break;
        case 7:
          puVar6 = (undefined4 *)((int)dst - pos2);
          uVar7 = puVar6[1];
          bVar3 = *(byte *)(puVar6 + 2);
          bVar2 = *(byte *)((int)puVar6 + 9);
          *dst = *puVar6;
          dst[1] = uVar7;
          *(byte *)(dst + 2) = bVar3;
          *(byte *)((int)dst + 9) = bVar2;
          dst = (undefined4 *)((int)dst + 10);
          break;
        case 8:
          puVar6 = (undefined4 *)((int)dst - pos2);
          uVar7 = puVar6[1];
          bVar3 = *(byte *)(puVar6 + 2);
          bVar2 = *(byte *)((int)puVar6 + 9);
          *dst = *puVar6;
          dst[1] = uVar7;
          *(byte *)(dst + 2) = bVar3;
          *(byte *)((int)dst + 9) = bVar2;
          *(byte *)((int)dst + 10) = *(byte *)((int)puVar6 + 10);
          dst = (undefined4 *)((int)dst + 0xb);
          break;
        case 9:
          puVar6 = (undefined4 *)((int)dst - pos2);
          uVar7 = puVar6[1];
          uVar9 = puVar6[2];
          *dst = *puVar6;
          dst[1] = uVar7;
          dst[2] = uVar9;
          dst = dst + 3;
          break;
        case 10:
          puVar6 = (undefined4 *)((int)dst - pos2);
          uVar7 = puVar6[1];
          uVar9 = puVar6[2];
          bVar3 = *(byte *)(puVar6 + 3);
          *dst = *puVar6;
          dst[1] = uVar7;
          dst[2] = uVar9;
          *(byte *)(dst + 3) = bVar3;
          dst = (undefined4 *)((int)dst + 0xd);
          break;
        case 0xb:
          puVar6 = (undefined4 *)((int)dst - pos2);
          uVar7 = puVar6[1];
          uVar9 = puVar6[2];
          bVar3 = *(byte *)(puVar6 + 3);
          *dst = *puVar6;
          dst[1] = uVar7;
          dst[2] = uVar9;
          *(byte *)(dst + 3) = bVar3;
          *(byte *)((int)dst + 0xd) = *(byte *)((int)puVar6 + 0xd);
          dst = (undefined4 *)((int)dst + 0xe);
          break;
        case 0xc:
          puVar6 = (undefined4 *)((int)dst - pos2);
          uVar7 = puVar6[1];
          uVar9 = puVar6[2];
          bVar3 = *(byte *)(puVar6 + 3);
          *dst = *puVar6;
          dst[1] = uVar7;
          dst[2] = uVar9;
          *(byte *)(dst + 3) = bVar3;
          bVar3 = *(byte *)((int)puVar6 + 0xe);
          *(byte *)((int)dst + 0xd) = *(byte *)((int)puVar6 + 0xd);
          *(byte *)((int)dst + 0xe) = bVar3;
          dst = (undefined4 *)((int)dst + 0xf);
          break;
        case 0xd:
          puVar6 = (undefined4 *)((int)dst - pos2);
          uVar7 = puVar6[1];
          uVar9 = puVar6[2];
          uVar10 = puVar6[3];
          *dst = *puVar6;
          dst[1] = uVar7;
          dst[2] = uVar9;
          dst[3] = uVar10;
          dst = dst + 4;
          break;
        case 0xe:
          puVar6 = (undefined4 *)((int)dst - pos2);
          uVar7 = puVar6[1];
          uVar9 = puVar6[2];
          uVar10 = puVar6[3];
          *dst = *puVar6;
          dst[1] = uVar7;
          dst[2] = uVar9;
          dst[3] = uVar10;
          *(byte *)(dst + 4) = *(byte *)(puVar6 + 4);
          dst = (undefined4 *)((int)dst + 0x11);
        }
        goto switchD_800127fc_caseD_f;
      }
      loop_i = 0;
      if (len == 0xfffffffd) goto switchD_800127fc_caseD_f;
      do {
        loop_i = loop_i + 1;
        *(byte *)dst = *(byte *)((int)dst - pos2);
        dst = (undefined4 *)((int)dst + 1);
      } while (loop_i < (int)(len + 3));
      pSLZBuf = pSLZBuf + 2;
    }
    if (pos2 < 0x100) {
      pos = (uint)pSLZBuf[2];
      pSLZBuf = pSLZBuf + 1;
      pos2 = pos2 + 0x13;
    }
    else {
      pos2 = ((int)pos2 >> 8) + 3;
    }
    uVar8 = (ushort)pos | (ushort)(pos << 8);
    if (((uint)dst & 1) == 0) {
      loop_i = 0;
      if (0 < (int)(pos2 - 1)) {
        do {
          *(ushort *)dst = uVar8;
          loop_i = loop_i + 2;
          dst = (undefined4 *)((int)dst + 2);
        } while (loop_i < (int)(pos2 - 1));
      }
      bVar4 = loop_i < (int)pos2;
    }
    else {
      *(byte *)dst = (byte)pos;
      dst = (undefined4 *)((int)dst + 1);
      if ((pos2 & 1) != 0) {
        loop_i = 1;
        if (pos2 < 2) goto switchD_800127fc_caseD_f;
        do {
          *(ushort *)dst = uVar8;
          loop_i = loop_i + 2;
          dst = (undefined4 *)((int)dst + 2);
        } while (loop_i < (int)pos2);
        pSLZBuf = pSLZBuf + 2;
        goto LAB_80012774;
      }
      loop_i = 1;
      bVar4 = 1 < pos2;
      if (1 < (int)(pos2 - 1)) {
        do {
          *(ushort *)dst = uVar8;
          loop_i = loop_i + 2;
          dst = (undefined4 *)((int)dst + 2);
        } while (loop_i < (int)(pos2 - 1));
        bVar4 = loop_i < (int)pos2;
      }
    }
    if (bVar4) {
      *(byte *)dst = (byte)pos;
      dst = (undefined4 *)((int)dst + 1);
    }
switchD_800127fc_caseD_f:
    pSLZBuf = pSLZBuf + 2;
  } while( true );
}
