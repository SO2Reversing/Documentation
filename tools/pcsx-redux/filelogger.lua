function readWordPcsxMem (address)
    local len1 = PCSX.getMemPtr()[address]
    local len2 = PCSX.getMemPtr()[address+1]
    local len3 = PCSX.getMemPtr()[address+2]
    local len4 = PCSX.getMemPtr()[address+3]
    local size = bit.bor(bit.lshift(len4,24),bit.lshift(len3,16),bit.lshift(len2,8),len1)
    return size
end

bp_cd_seek = PCSX.addBreakpoint(0x80011670, 'Exec', 4, 'CD Seek to File Index', function()
    local index = PCSX.getRegisters().GPR.n.s3
    local ra = PCSX.getRegisters().GPR.n.ra
    local hexra = string.format("%08x", ra)
    print(hexra .. ':CD FILE SEEK: ' .. index)
end)

bp_cd_seek_file = PCSX.addBreakpoint(0x800119bc, 'Exec', 4, 'CD Seek Within File', function()
    local index = PCSX.getRegisters().GPR.n.a2
    local seek = PCSX.getRegisters().GPR.n.a1
    local ra = PCSX.getRegisters().GPR.n.ra
    local hexra = string.format("%08x", ra)
    local hexseek = string.format("%08x", seek*2048)
    print(hexra .. ':CD SEEK WITHIN FILE: ' .. index .. ' + ' .. hexseek)
end)

bp_cd_read = PCSX.addBreakpoint(0x800118b0, 'Exec', 4, 'CD Read', function()
    local dst = PCSX.getRegisters().GPR.n.a1
    local sp = PCSX.getRegisters().GPR.n.sp

    local size = readWordPcsxMem(0x2b568)
    local hexdst = string.format("%08x", dst)
    local hexsize = string.format("%08x", size)
    local hexdstend = string.format("%08x", dst+size)
    --local hexra = string.format("%08x", ra)

    local ra = readWordPcsxMem(sp - 0x80000000 + 0x10 + 0x18)
    local hexra = bit.tohex(ra)
    print(hexra .. ':CD READ S:E:L - ' .. hexdst .. ':' .. hexdstend .. ':' .. hexsize)
end)

bp_slz_decomp = PCSX.addBreakpoint(0x80012224, 'Exec', 4, 'SLZ Decomp', function()
    local src = PCSX.getRegisters().GPR.n.s0
    local dst = PCSX.getRegisters().GPR.n.s2
    local sp = PCSX.getRegisters().GPR.n.sp

    local srcMem = src - 0x80000000

    local srcSize = readWordPcsxMem(srcMem+4)
    local dstSize = readWordPcsxMem(srcMem+8)

    local hexsrc = string.format("%08x", src)
    local hexdst = string.format("%08x", dst)

    local hexsrcEnd = string.format("%08x", src+srcSize)
    local hexdstEnd = string.format("%08x", dst+dstSize)

    local hexsrcSize = string.format("%08x", srcSize)
    local hexdstSize = string.format("%08x", dstSize)
    local ra = readWordPcsxMem(sp - 0x80000000 + 0x28)
    local hexra = bit.tohex(ra)
    

    print(hexra .. ':SLZ SS:SE:SL DS:DE:DL - ' .. hexsrc .. ':' .. hexsrcEnd .. ':' .. hexsrcSize .. '-' .. hexdst .. ':' .. hexdstEnd .. ':' .. hexdstSize)
end
