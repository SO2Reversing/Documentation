void DecryptFileTable(int pFileTable)

{
  undefined4 *ReadBuf;
  undefined4 uVar1;
  int FileTableDst;
  undefined4 *FileTable;
  int pDstBuf;
  undefined4 *dataptr;
  uint Key;
  uint TempKey;
  int loop_i;
  undefined auStack24 [4];
  undefined *local_14;
  
  *(undefined4 *)(pFileTable + 0x5a04) = 1;
  *(undefined4 *)(pFileTable + 4) = 0x600;
  local_14 = &DAT_8002a840;
  FUN_80011a94(pFileTable,auStack24,pFileTable);
  CDSeekFromTableIndex(pFileTable,0);
  ReadBuf = (undefined4 *)maybe_malloc(0x6000);
  ReadFile(pFileTable,ReadBuf,0x6000);
  do {
    dataptr = (undefined4 *)(pFileTable + 4);
  } while (*(int *)(pFileTable + 0x5a04) != 0);
  FileTableDst = 0; //This is used as loop_i, then resused as the FileTable Destination Ptr
  FileTable = ReadBuf;
  do {
    uVar1 = *FileTable;
    FileTable = FileTable + 1;
    FileTableDst = FileTableDst + 1;
    *dataptr = uVar1;
    dataptr = dataptr + 1;
  } while (FileTableDst < 0x1680);
  maybeDelete(ReadBuf);
  FUN_80011aac(pFileTable);
  Key = 0x13578642;
  loop_i = 0;
  FileTableDst = pFileTable;
  do {
    pDstBuf = pFileTable + loop_i;
    loop_i = loop_i + 1;
    TempKey = Key ^ Key << 1;
    *(uint *)(FileTableDst + 4) = *(uint *)(FileTableDst + 4) ^ Key;
    FileTableDst = FileTableDst + 4;
    Key = ~TempKey ^ 0x13578642;
    *(byte *)(pDstBuf + 0x4804) = *(byte *)(pDstBuf + 0x4804) ^ (byte)TempKey;
  } while (loop_i < 0x1200);
  return;
}
