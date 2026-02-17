; PROJ5.EXE Disassembly
; File size: 119952 bytes
; Code starts at file offset: 0x1E00
; Code size: 112272 bytes

00000000  BA D3 18                  mov      dx, 0x18d3
00000003  2E 89 16 6D 02            mov      word ptr cs:[0x26d], dx
00000008  B4 30                     mov      ah, 0x30
0000000A  CD 21                     int      0x21
0000000C  8B 2E 02 00               mov      bp, word ptr [2]
00000010  8B 1E 2C 00               mov      bx, word ptr [0x2c]
00000014  8E DA                     mov      ds, dx
00000016  A3 7C 00                  mov      word ptr [0x7c], ax
00000019  8C 06 7A 00               mov      word ptr [0x7a], es
0000001D  89 1E 76 00               mov      word ptr [0x76], bx
00000021  89 2E 8E 00               mov      word ptr [0x8e], bp
00000025  E8 50 01                  call     0x178
00000028  A1 76 00                  mov      ax, word ptr [0x76]
0000002B  8E C0                     mov      es, ax
0000002D  33 C0                     xor      ax, ax
0000002F  8B D8                     mov      bx, ax
00000031  8B F8                     mov      di, ax
00000033  B9 FF 7F                  mov      cx, 0x7fff
00000036  FC                        cld      
00000037  F2 AE                     repne scasb al, byte ptr es:[di]
00000039  E3 43                     jcxz     0x7e
0000003B  43                        inc      bx
0000003C  26 38 05                  cmp      byte ptr es:[di], al
0000003F  75 F6                     jne      0x37
00000041  80 CD 80                  or       ch, 0x80
00000044  F7 D9                     neg      cx
00000046  89 0E 74 00               mov      word ptr [0x74], cx
0000004A  B9 02 00                  mov      cx, 2
0000004D  D3 E3                     shl      bx, cl
0000004F  83 C3 10                  add      bx, 0x10
00000052  83 E3 F0                  and      bx, 0xfff0
00000055  89 1E 78 00               mov      word ptr [0x78], bx
00000059  8C D2                     mov      dx, ss
0000005B  2B EA                     sub      bp, dx
0000005D  BF D3 18                  mov      di, 0x18d3
00000060  8E C7                     mov      es, di
00000062  26 8B 3E F4 26            mov      di, word ptr es:[0x26f4]
00000067  81 FF 00 02               cmp      di, 0x200
0000006B  73 08                     jae      0x75
0000006D  BF 00 02                  mov      di, 0x200
00000070  26 89 3E F4 26            mov      word ptr es:[0x26f4], di
00000075  B1 04                     mov      cl, 4
00000077  D3 EF                     shr      di, cl
00000079  47                        inc      di
0000007A  3B EF                     cmp      bp, di
0000007C  73 05                     jae      0x83
0000007E  90                        nop      
0000007F  0E                        push     cs
00000080  E8 36 4D                  call     0x4db9
00000083  8B DF                     mov      bx, di
00000085  03 DA                     add      bx, dx
00000087  89 1E 86 00               mov      word ptr [0x86], bx
0000008B  89 1E 8A 00               mov      word ptr [0x8a], bx
0000008F  A1 7A 00                  mov      ax, word ptr [0x7a]
00000092  2B D8                     sub      bx, ax
00000094  8E C0                     mov      es, ax
00000096  B4 4A                     mov      ah, 0x4a
00000098  57                        push     di
00000099  CD 21                     int      0x21
0000009B  5F                        pop      di
0000009C  D3 E7                     shl      di, cl
0000009E  FA                        cli      
0000009F  8E D2                     mov      ss, dx
000000A1  8B E7                     mov      sp, di
000000A3  FB                        sti      
000000A4  B8 D3 18                  mov      ax, 0x18d3
000000A7  8E C0                     mov      es, ax
000000A9  26 89 3E F4 26            mov      word ptr es:[0x26f4], di
000000AE  33 C0                     xor      ax, ax
000000B0  2E 8E 06 6D 02            mov      es, word ptr cs:[0x26d]
000000B5  BF 60 29                  mov      di, 0x2960
000000B8  B9 CA 58                  mov      cx, 0x58ca
000000BB  2B CF                     sub      cx, di
000000BD  FC                        cld      
000000BE  F3 AA                     rep stosb byte ptr es:[di], al
000000C0  83 3E 74 21 14            cmp      word ptr [0x2174], 0x14
000000C5  76 49                     jbe      0x110
000000C7  80 3E 7C 00 03            cmp      byte ptr [0x7c], 3
000000CC  72 42                     jb       0x110
000000CE  77 07                     ja       0xd7
000000D0  80 3E 7D 00 1E            cmp      byte ptr [0x7d], 0x1e
000000D5  72 39                     jb       0x110
000000D7  B8 01 58                  mov      ax, 0x5801
000000DA  BB 02 00                  mov      bx, 2
000000DD  CD 21                     int      0x21
000000DF  72 2A                     jb       0x10b
000000E1  B4 67                     mov      ah, 0x67
000000E3  8B 1E 74 21               mov      bx, word ptr [0x2174]
000000E7  CD 21                     int      0x21
000000E9  72 20                     jb       0x10b
000000EB  B4 48                     mov      ah, 0x48
000000ED  BB 01 00                  mov      bx, 1
000000F0  CD 21                     int      0x21
000000F2  72 17                     jb       0x10b
000000F4  40                        inc      ax
000000F5  A3 8E 00                  mov      word ptr [0x8e], ax
000000F8  48                        dec      ax
000000F9  8E C0                     mov      es, ax
000000FB  B4 49                     mov      ah, 0x49
000000FD  CD 21                     int      0x21
000000FF  72 0A                     jb       0x10b
00000101  B8 01 58                  mov      ax, 0x5801
00000104  BB 00 00                  mov      bx, 0
00000107  CD 21                     int      0x21
00000109  73 05                     jae      0x110
0000010B  90                        nop      
0000010C  0E                        push     cs
0000010D  E8 A9 4C                  call     0x4db9
00000110  33 ED                     xor      bp, bp
00000112  55                        push     bp
00000113  90                        nop      
00000114  0E                        push     cs
00000115  E8 43 55                  call     0x565b
00000118  58                        pop      ax
00000119  2E 8E 06 6D 02            mov      es, word ptr cs:[0x26d]
0000011E  BE 18 29                  mov      si, 0x2918
00000121  BF 48 29                  mov      di, 0x2948
00000124  E8 C1 00                  call     0x1e8
00000127  FF 36 72 00               push     word ptr [0x72]
0000012B  FF 36 70 00               push     word ptr [0x70]
0000012F  FF 36 6E 00               push     word ptr [0x6e]
00000133  FF 36 6C 00               push     word ptr [0x6c]
00000137  FF 36 6A 00               push     word ptr [0x6a]
0000013B  9A 0E 00 28 09            lcall    0x928, 0xe
00000140  50                        push     ax
00000141  90                        nop      
00000142  0E                        push     cs
00000143  E8 28 4C                  call     0x4d6e
00000146  2E 8E 06 6D 02            mov      es, word ptr cs:[0x26d]
0000014B  56                        push     si
0000014C  57                        push     di
0000014D  BE 48 29                  mov      si, 0x2948
00000150  BF 60 29                  mov      di, 0x2960
00000153  E8 D6 00                  call     0x22c
00000156  5F                        pop      di
00000157  5E                        pop      si
00000158  CB                        retf     
00000159  CB                        retf     
0000015A  8B EC                     mov      bp, sp
0000015C  B4 4C                     mov      ah, 0x4c
0000015E  8A 46 04                  mov      al, byte ptr [bp + 4]
00000161  CD 21                     int      0x21
00000163  BA 4B 00                  mov      dx, 0x4b
00000166  1E                        push     ds
00000167  52                        push     dx
00000168  90                        nop      
00000169  0E                        push     cs
0000016A  E8 62 4A                  call     0x4bcf
0000016D  5A                        pop      dx
0000016E  1F                        pop      ds
0000016F  B8 03 00                  mov      ax, 3
00000172  50                        push     ax
00000173  90                        nop      
00000174  0E                        push     cs
00000175  E8 09 4C                  call     0x4d81
00000178  1E                        push     ds
00000179  B8 00 35                  mov      ax, 0x3500
0000017C  CD 21                     int      0x21
0000017E  89 1E 5A 00               mov      word ptr [0x5a], bx
00000182  8C 06 5C 00               mov      word ptr [0x5c], es
00000186  B8 04 35                  mov      ax, 0x3504
00000189  CD 21                     int      0x21
0000018B  89 1E 5E 00               mov      word ptr [0x5e], bx
0000018F  8C 06 60 00               mov      word ptr [0x60], es
00000193  B8 05 35                  mov      ax, 0x3505
00000196  CD 21                     int      0x21
00000198  89 1E 62 00               mov      word ptr [0x62], bx
0000019C  8C 06 64 00               mov      word ptr [0x64], es
000001A0  B8 06 35                  mov      ax, 0x3506
000001A3  CD 21                     int      0x21
000001A5  89 1E 66 00               mov      word ptr [0x66], bx
000001A9  8C 06 68 00               mov      word ptr [0x68], es
000001AD  B8 00 25                  mov      ax, 0x2500
000001B0  8C CA                     mov      dx, cs
000001B2  8E DA                     mov      ds, dx
000001B4  BA 63 01                  mov      dx, 0x163
000001B7  CD 21                     int      0x21
000001B9  1F                        pop      ds
000001BA  C3                        ret      
000001BB  1E                        push     ds
000001BC  B8 00 25                  mov      ax, 0x2500
000001BF  C5 16 5A 00               lds      dx, ptr [0x5a]
000001C3  CD 21                     int      0x21
000001C5  1F                        pop      ds
000001C6  1E                        push     ds
000001C7  B8 04 25                  mov      ax, 0x2504
000001CA  C5 16 5E 00               lds      dx, ptr [0x5e]
000001CE  CD 21                     int      0x21
000001D0  1F                        pop      ds
000001D1  1E                        push     ds
000001D2  B8 05 25                  mov      ax, 0x2505
000001D5  C5 16 62 00               lds      dx, ptr [0x62]
000001D9  CD 21                     int      0x21
000001DB  1F                        pop      ds
000001DC  1E                        push     ds
000001DD  B8 06 25                  mov      ax, 0x2506
000001E0  C5 16 66 00               lds      dx, ptr [0x66]
000001E4  CD 21                     int      0x21
000001E6  1F                        pop      ds
000001E7  CB                        retf     
000001E8  B8 00 01                  mov      ax, 0x100
000001EB  8B D7                     mov      dx, di
000001ED  8B DE                     mov      bx, si
000001EF  3B DF                     cmp      bx, di
000001F1  74 19                     je       0x20c
000001F3  26 80 3F FF               cmp      byte ptr es:[bx], 0xff
000001F7  74 0E                     je       0x207
000001F9  26 8A 4F 01               mov      cl, byte ptr es:[bx + 1]
000001FD  32 ED                     xor      ch, ch
000001FF  3B C8                     cmp      cx, ax
00000201  73 04                     jae      0x207
00000203  8B C1                     mov      ax, cx
00000205  8B D3                     mov      dx, bx
00000207  83 C3 06                  add      bx, 6
0000020A  EB E3                     jmp      0x1ef
0000020C  3B D7                     cmp      dx, di
0000020E  74 1B                     je       0x22b
00000210  8B DA                     mov      bx, dx
00000212  26 80 3F 00               cmp      byte ptr es:[bx], 0
00000216  26 C6 07 FF               mov      byte ptr es:[bx], 0xff
0000021A  06                        push     es
0000021B  74 07                     je       0x224
0000021D  26 FF 5F 02               lcall    es:[bx + 2]
00000221  07                        pop      es
00000222  EB C4                     jmp      0x1e8
00000224  26 FF 57 02               call     word ptr es:[bx + 2]
00000228  07                        pop      es
00000229  EB BD                     jmp      0x1e8
0000022B  C3                        ret      
0000022C  B4 00                     mov      ah, 0
0000022E  8B D7                     mov      dx, di
00000230  8B DE                     mov      bx, si
00000232  3B DF                     cmp      bx, di
00000234  74 17                     je       0x24d
00000236  26 80 3F FF               cmp      byte ptr es:[bx], 0xff
0000023A  74 0C                     je       0x248
0000023C  26 38 67 01               cmp      byte ptr es:[bx + 1], ah
00000240  72 06                     jb       0x248
00000242  26 8A 67 01               mov      ah, byte ptr es:[bx + 1]
00000246  8B D3                     mov      dx, bx
00000248  83 C3 06                  add      bx, 6
0000024B  EB E5                     jmp      0x232
0000024D  3B D7                     cmp      dx, di
0000024F  74 1B                     je       0x26c
00000251  8B DA                     mov      bx, dx
00000253  26 80 3F 00               cmp      byte ptr es:[bx], 0
00000257  26 C6 07 FF               mov      byte ptr es:[bx], 0xff
0000025B  06                        push     es
0000025C  74 07                     je       0x265
0000025E  26 FF 5F 02               lcall    es:[bx + 2]
00000262  07                        pop      es
00000263  EB C7                     jmp      0x22c
00000265  26 FF 57 02               call     word ptr es:[bx + 2]
00000269  07                        pop      es
0000026A  EB C0                     jmp      0x22c
0000026C  C3                        ret      
0000026D  00 00                     add      byte ptr [bx + si], al
0000026F  04 C0                     add      al, 0xc0
00000271  00 00                     add      byte ptr [bx + si], al
00000273  00 00                     add      byte ptr [bx + si], al
00000275  00 00                     add      byte ptr [bx + si], al
00000277  00 00                     add      byte ptr [bx + si], al
00000279  00 00                     add      byte ptr [bx + si], al
0000027B  00 00                     add      byte ptr [bx + si], al
0000027D  00 00                     add      byte ptr [bx + si], al
0000027F  00 00                     add      byte ptr [bx + si], al
00000281  00 00                     add      byte ptr [bx + si], al
00000283  00 00                     add      byte ptr [bx + si], al
00000285  00 00                     add      byte ptr [bx + si], al
00000287  00 00                     add      byte ptr [bx + si], al
00000289  00 00                     add      byte ptr [bx + si], al
0000028B  00 00                     add      byte ptr [bx + si], al
0000028D  00 00                     add      byte ptr [bx + si], al
0000028F  00 00                     add      byte ptr [bx + si], al
00000291  00 00                     add      byte ptr [bx + si], al
00000293  00 00                     add      byte ptr [bx + si], al
00000295  00 00                     add      byte ptr [bx + si], al
00000297  00 00                     add      byte ptr [bx + si], al
00000299  00 00                     add      byte ptr [bx + si], al
0000029B  00 00                     add      byte ptr [bx + si], al
0000029D  00 00                     add      byte ptr [bx + si], al
0000029F  00 00                     add      byte ptr [bx + si], al
000002A1  00 00                     add      byte ptr [bx + si], al
000002A3  00 00                     add      byte ptr [bx + si], al
000002A5  00 00                     add      byte ptr [bx + si], al
000002A7  00 00                     add      byte ptr [bx + si], al
000002A9  00 00                     add      byte ptr [bx + si], al
000002AB  80 7F 50 32               cmp      byte ptr [bx + 0x50], 0x32
000002AF  C0 E6 F0                  shl      dh, 0xf0
000002B2  B0 20                     mov      al, 0x20
000002B4  E6 A0                     out      0xa0, al
000002B6  E6 20                     out      0x20, al
000002B8  58                        pop      ax
000002B9  CD 02                     int      2
000002BB  CF                        iret     
000002BC  50                        push     ax
000002BD  B8 60 1E                  mov      ax, 0x1e60
000002C0  9A 3F 00 B2 17            lcall    0x17b2, 0x3f
000002C5  72 1B                     jb       0x2e2
000002C7  58                        pop      ax
000002C8  83 EC 04                  sub      sp, 4
000002CB  53                        push     bx
000002CC  8B DC                     mov      bx, sp
000002CE  50                        push     ax
000002CF  2E A1 A3 02               mov      ax, word ptr cs:[0x2a3]
000002D3  36 89 47 04               mov      word ptr ss:[bx + 4], ax
000002D7  2E A1 A1 02               mov      ax, word ptr cs:[0x2a1]
000002DB  36 89 47 02               mov      word ptr ss:[bx + 2], ax
000002DF  58                        pop      ax
000002E0  5B                        pop      bx
000002E1  CB                        retf     
000002E2  93                        xchg     bx, ax
000002E3  B8 D3 18                  mov      ax, 0x18d3
000002E6  8E D8                     mov      ds, ax
000002E8  E8 E1 0B                  call     0xecc
000002EB  58                        pop      ax
000002EC  CF                        iret     
000002ED  1E                        push     ds
000002EE  56                        push     si
000002EF  57                        push     di
000002F0  B8 65 00                  mov      ax, 0x65
000002F3  36 A3 2F 00               mov      word ptr ss:[0x2f], ax
000002F7  05 C0 00                  add      ax, 0xc0
000002FA  36 A3 31 00               mov      word ptr ss:[0x31], ax
000002FE  A1 FC 1B                  mov      ax, word ptr [0x1bfc]
00000301  36 A3 27 00               mov      word ptr ss:[0x27], ax
00000305  1E                        push     ds
00000306  0E                        push     cs
00000307  1F                        pop      ds
00000308  8C D8                     mov      ax, ds
0000030A  36 33 06 27 00            xor      ax, word ptr ss:[0x27]
0000030F  8E D8                     mov      ds, ax
00000311  B8 34 35                  mov      ax, 0x3534
00000314  B9 0B 00                  mov      cx, 0xb
00000317  BF 71 02                  mov      di, 0x271
0000031A  CD 21                     int      0x21
0000031C  89 1D                     mov      word ptr [di], bx
0000031E  8C 45 02                  mov      word ptr [di + 2], es
00000321  83 C7 04                  add      di, 4
00000324  40                        inc      ax
00000325  E2 F3                     loop     0x31a
00000327  B8 75 35                  mov      ax, 0x3575
0000032A  CD 21                     int      0x21
0000032C  89 1D                     mov      word ptr [di], bx
0000032E  8C 45 02                  mov      word ptr [di + 2], es
00000331  83 C7 04                  add      di, 4
00000334  B8 02 35                  mov      ax, 0x3502
00000337  CD 21                     int      0x21
00000339  89 1D                     mov      word ptr [di], bx
0000033B  8C 45 02                  mov      word ptr [di + 2], es
0000033E  1F                        pop      ds
0000033F  B8 D3 18                  mov      ax, 0x18d3
00000342  8E D8                     mov      ds, ax
00000344  BB FF FF                  mov      bx, 0xffff
00000347  5F                        pop      di
00000348  5E                        pop      si
00000349  0B DB                     or       bx, bx
0000034B  74 64                     je       0x3b1
0000034D  54                        push     sp
0000034E  59                        pop      cx
0000034F  3B CC                     cmp      cx, sp
00000351  75 24                     jne      0x377
00000353  0B DB                     or       bx, bx
00000355  7F 06                     jg       0x35d
00000357  CD 11                     int      0x11
00000359  24 02                     and      al, 2
0000035B  74 52                     je       0x3af
0000035D  DB E3                     fninit   
0000035F  2E D9 06 A9 02            fld      dword ptr cs:[0x2a9]
00000364  D9 E0                     fchs     
00000366  2E D8 1E A9 02            fcomp    dword ptr cs:[0x2a9]
0000036B  9B                        wait     
0000036C  DF E0                     fnstsw   ax
0000036E  9E                        sahf     
0000036F  B0 02                     mov      al, 2
00000371  74 3C                     je       0x3af
00000373  FE C0                     inc      al
00000375  EB 38                     jmp      0x3af
00000377  DB E3                     fninit   
00000379  C7 06 00 1C 00 00         mov      word ptr [0x1c00], 0
0000037F  D9 3E 00 1C               fnstcw   word ptr [0x1c00]
00000383  B9 14 00                  mov      cx, 0x14
00000386  E2 FE                     loop     0x386
00000388  8B 0E 00 1C               mov      cx, word ptr [0x1c00]
0000038C  81 E1 3F 0F               and      cx, 0xf3f
00000390  81 F9 3F 03               cmp      cx, 0x33f
00000394  75 19                     jne      0x3af
00000396  C7 06 00 1C FF FF         mov      word ptr [0x1c00], 0xffff
0000039C  DD 3E 00 1C               fnstsw   word ptr [0x1c00]
000003A0  B9 14 00                  mov      cx, 0x14
000003A3  E2 FE                     loop     0x3a3
000003A5  F7 06 00 1C BF B8         test     word ptr [0x1c00], 0xb8bf
000003AB  75 02                     jne      0x3af
000003AD  FE C0                     inc      al
000003AF  98                        cwde     
000003B0  93                        xchg     bx, ax
000003B1  89 1E 00 1C               mov      word ptr [0x1c00], bx
000003B5  36 88 1E 26 00            mov      byte ptr ss:[0x26], bl
000003BA  1F                        pop      ds
000003BB  1E                        push     ds
000003BC  55                        push     bp
000003BD  8B EC                     mov      bp, sp
000003BF  83 EC 08                  sub      sp, 8
000003C2  BB D3 18                  mov      bx, 0x18d3
000003C5  8E DB                     mov      ds, bx
000003C7  83 3E 00 1C 00            cmp      word ptr [0x1c00], 0
000003CC  C7 46 F8 E0 04            mov      word ptr [bp - 8], 0x4e0
000003D1  C7 46 FA B2 17            mov      word ptr [bp - 6], 0x17b2
000003D6  C7 46 FC A3 05            mov      word ptr [bp - 4], 0x5a3
000003DB  C7 46 FE B2 17            mov      word ptr [bp - 2], 0x17b2
000003E0  B8 34 25                  mov      ax, 0x2534
000003E3  B9 0A 00                  mov      cx, 0xa
000003E6  C5 56 F8                  lds      dx, ptr [bp - 8]
000003E9  CD 21                     int      0x21
000003EB  40                        inc      ax
000003EC  E2 FB                     loop     0x3e9
000003EE  B8 3E 25                  mov      ax, 0x253e
000003F1  C5 56 FC                  lds      dx, ptr [bp - 4]
000003F4  CD 21                     int      0x21
000003F6  B8 02 25                  mov      ax, 0x2502
000003F9  0E                        push     cs
000003FA  1F                        pop      ds
000003FB  BA BC 02                  mov      dx, 0x2bc
000003FE  CD 21                     int      0x21
00000400  8E DB                     mov      ds, bx
00000402  83 3E 00 1C 00            cmp      word ptr [0x1c00], 0
00000407  74 14                     je       0x41d
00000409  A1 7C 00                  mov      ax, word ptr [0x7c]
0000040C  86 E0                     xchg     al, ah
0000040E  3D 03 14                  cmp      ax, 0x1403
00000411  75 0A                     jne      0x41d
00000413  B8 75 25                  mov      ax, 0x2575
00000416  0E                        push     cs
00000417  1F                        pop      ds
00000418  BA AD 02                  mov      dx, 0x2ad
0000041B  CD 21                     int      0x21
0000041D  8E DB                     mov      ds, bx
0000041F  CD 37                     int      0x37
00000421  E3 36                     jcxz     0x459
00000423  C7 06 41 00 00 00         mov      word ptr [0x41], 0
00000429  36 C7 06 43 00 00 00      mov      word ptr ss:[0x43], 0
00000430  A1 FA 1B                  mov      ax, word ptr [0x1bfa]
00000433  89 46 F8                  mov      word ptr [bp - 8], ax
00000436  83 3E 00 1C 03            cmp      word ptr [0x1c00], 3
0000043B  7C 04                     jl       0x441
0000043D  83 4E F8 02               or       word ptr [bp - 8], 2
00000441  56                        push     si
00000442  9B                        wait     
00000443  D9 6E F8                  fldcw    word ptr [bp - 8]
00000446  5E                        pop      si
00000447  8B 46 F8                  mov      ax, word ptr [bp - 8]
0000044A  36 21 06 22 00            and      word ptr ss:[0x22], ax
0000044F  33 C0                     xor      ax, ax
00000451  99                        cdq      
00000452  8B E5                     mov      sp, bp
00000454  5D                        pop      bp
00000455  1F                        pop      ds
00000456  C3                        ret      
00000457  1E                        push     ds
00000458  B8 D3 18                  mov      ax, 0x18d3
0000045B  8E D8                     mov      ds, ax
0000045D  83 3E 00 1C 00            cmp      word ptr [0x1c00], 0
00000462  7C 28                     jl       0x48c
00000464  9B                        wait     
00000465  DB E3                     fninit   
00000467  B8 34 25                  mov      ax, 0x2534
0000046A  BB 71 02                  mov      bx, 0x271
0000046D  B9 0B 00                  mov      cx, 0xb
00000470  2E C5 17                  lds      dx, ptr cs:[bx]
00000473  CD 21                     int      0x21
00000475  83 C3 04                  add      bx, 4
00000478  40                        inc      ax
00000479  E2 F5                     loop     0x470
0000047B  B8 75 25                  mov      ax, 0x2575
0000047E  2E C5 17                  lds      dx, ptr cs:[bx]
00000481  CD 21                     int      0x21
00000483  B8 02 25                  mov      ax, 0x2502
00000486  2E C5 57 04               lds      dx, ptr cs:[bx + 4]
0000048A  CD 21                     int      0x21
0000048C  1F                        pop      ds
0000048D  C3                        ret      
0000048E  B8 02 00                  mov      ax, 2
00000491  CB                        retf     
00000492  55                        push     bp
00000493  8B EC                     mov      bp, sp
00000495  33 C0                     xor      ax, ax
00000497  50                        push     ax
00000498  50                        push     ax
00000499  FF 76 08                  push     word ptr [bp + 8]
0000049C  FF 76 06                  push     word ptr [bp + 6]
0000049F  90                        nop      
000004A0  0E                        push     cs
000004A1  E8 D1 00                  call     0x575
000004A4  83 C4 08                  add      sp, 8
000004A7  EB 00                     jmp      0x4a9
000004A9  5D                        pop      bp
000004AA  CB                        retf     
000004AB  55                        push     bp
000004AC  8B EC                     mov      bp, sp
000004AE  16                        push     ss
000004AF  8D 46 06                  lea      ax, [bp + 6]
000004B2  50                        push     ax
000004B3  FF 76 0E                  push     word ptr [bp + 0xe]
000004B6  FF 76 12                  push     word ptr [bp + 0x12]
000004B9  FF 76 10                  push     word ptr [bp + 0x10]
000004BC  B0 67                     mov      al, 0x67
000004BE  50                        push     ax
000004BF  B0 00                     mov      al, 0
000004C1  50                        push     ax
000004C2  B8 06 00                  mov      ax, 6
000004C5  50                        push     ax
000004C6  E8 B1 3C                  call     0x417a
000004C9  8B 56 12                  mov      dx, word ptr [bp + 0x12]
000004CC  8B 46 10                  mov      ax, word ptr [bp + 0x10]
000004CF  EB 00                     jmp      0x4d1
000004D1  5D                        pop      bp
000004D2  CB                        retf     
000004D3  55                        push     bp
000004D4  8B EC                     mov      bp, sp
000004D6  56                        push     si
000004D7  C4 5E 04                  les      bx, ptr [bp + 4]
000004DA  26 8B 57 02               mov      dx, word ptr es:[bx + 2]
000004DE  26 8B 37                  mov      si, word ptr es:[bx]
000004E1  26 FF 07                  inc      word ptr es:[bx]
000004E4  8E C2                     mov      es, dx
000004E6  26 8A 04                  mov      al, byte ptr es:[si]
000004E9  98                        cwde     
000004EA  8B C8                     mov      cx, ax
000004EC  0B C0                     or       ax, ax
000004EE  75 05                     jne      0x4f5
000004F0  B8 FF FF                  mov      ax, 0xffff
000004F3  EB 02                     jmp      0x4f7
000004F5  8B C1                     mov      ax, cx
000004F7  EB 00                     jmp      0x4f9
000004F9  5E                        pop      si
000004FA  5D                        pop      bp
000004FB  C3                        ret      
000004FC  55                        push     bp
000004FD  8B EC                     mov      bp, sp
000004FF  C4 5E 06                  les      bx, ptr [bp + 6]
00000502  26 FF 0F                  dec      word ptr es:[bx]
00000505  5D                        pop      bp
00000506  C3                        ret      
00000507  55                        push     bp
00000508  8B EC                     mov      bp, sp
0000050A  83 EC 0E                  sub      sp, 0xe
0000050D  C7 46 FE 00 00            mov      word ptr [bp - 2], 0
00000512  16                        push     ss
00000513  8D 46 FC                  lea      ax, [bp - 4]
00000516  50                        push     ax
00000517  16                        push     ss
00000518  8D 46 FE                  lea      ax, [bp - 2]
0000051B  50                        push     ax
0000051C  B8 FF 7F                  mov      ax, 0x7fff
0000051F  50                        push     ax
00000520  16                        push     ss
00000521  8D 46 06                  lea      ax, [bp + 6]
00000524  50                        push     ax
00000525  B8 FC 04                  mov      ax, 0x4fc
00000528  50                        push     ax
00000529  B8 D3 04                  mov      ax, 0x4d3
0000052C  50                        push     ax
0000052D  E8 4E 3C                  call     0x417e
00000530  83 C4 12                  add      sp, 0x12
00000533  9B                        wait     
00000534  DB 7E F2                  fstp     xword ptr [bp - 0xe]
00000537  90                        nop      
00000538  9B                        wait     
00000539  83 7E FC 00               cmp      word ptr [bp - 4], 0
0000053D  7F 08                     jg       0x547
0000053F  8B 46 FE                  mov      ax, word ptr [bp - 2]
00000542  29 46 06                  sub      word ptr [bp + 6], ax
00000545  EB 0C                     jmp      0x553
00000547  83 7E FC 02               cmp      word ptr [bp - 4], 2
0000054B  75 06                     jne      0x553
0000054D  C7 06 7E 00 22 00         mov      word ptr [0x7e], 0x22
00000553  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
00000556  0B 46 0C                  or       ax, word ptr [bp + 0xc]
00000559  74 10                     je       0x56b
0000055B  C4 5E 0A                  les      bx, ptr [bp + 0xa]
0000055E  8B 56 08                  mov      dx, word ptr [bp + 8]
00000561  8B 46 06                  mov      ax, word ptr [bp + 6]
00000564  26 89 57 02               mov      word ptr es:[bx + 2], dx
00000568  26 89 07                  mov      word ptr es:[bx], ax
0000056B  9B                        wait     
0000056C  DB 6E F2                  fld      xword ptr [bp - 0xe]
0000056F  EB 00                     jmp      0x571
00000571  8B E5                     mov      sp, bp
00000573  5D                        pop      bp
00000574  CB                        retf     
00000575  55                        push     bp
00000576  8B EC                     mov      bp, sp
00000578  B8 01 00                  mov      ax, 1
0000057B  50                        push     ax
0000057C  FF 76 0C                  push     word ptr [bp + 0xc]
0000057F  FF 76 0A                  push     word ptr [bp + 0xa]
00000582  FF 76 08                  push     word ptr [bp + 8]
00000585  FF 76 06                  push     word ptr [bp + 6]
00000588  0E                        push     cs
00000589  E8 7B FF                  call     0x507
0000058C  83 C4 08                  add      sp, 8
0000058F  83 EC 0A                  sub      sp, 0xa
00000592  9B                        wait     
00000593  DB 7E F4                  fstp     xword ptr [bp - 0xc]
00000596  9B                        wait     
00000597  DD 06 06 1C               fld      qword ptr [0x1c06]
0000059B  83 EC 08                  sub      sp, 8
0000059E  9B                        wait     
0000059F  DD 5E EC                  fstp     qword ptr [bp - 0x14]
000005A2  90                        nop      
000005A3  9B                        wait     
000005A4  E8 04 00                  call     0x5ab
000005A7  EB 00                     jmp      0x5a9
000005A9  5D                        pop      bp
000005AA  CB                        retf     
000005AB  55                        push     bp
000005AC  8B EC                     mov      bp, sp
000005AE  83 EC 0C                  sub      sp, 0xc
000005B1  33 C9                     xor      cx, cx
000005B3  B8 FE 43                  mov      ax, 0x43fe
000005B6  BB CD 3B                  mov      bx, 0x3bcd
000005B9  83 7E 16 00               cmp      word ptr [bp + 0x16], 0
000005BD  75 06                     jne      0x5c5
000005BF  B8 7E 40                  mov      ax, 0x407e
000005C2  BB 6A 3F                  mov      bx, 0x3f6a
000005C5  8B 56 14                  mov      dx, word ptr [bp + 0x14]
000005C8  D1 E2                     shl      dx, 1
000005CA  D1 D1                     rcl      cx, 1
000005CC  D1 EA                     shr      dx, 1
000005CE  81 FA FF 7F               cmp      dx, 0x7fff
000005D2  74 6F                     je       0x643
000005D4  3B D0                     cmp      dx, ax
000005D6  74 08                     je       0x5e0
000005D8  7E 3F                     jle      0x619
000005DA  9B                        wait     
000005DB  DD 46 04                  fld      qword ptr [bp + 4]
000005DE  EB 50                     jmp      0x630
000005E0  9B                        wait     
000005E1  D9 7E FE                  fnstcw   word ptr [bp - 2]
000005E4  B8 00 0C                  mov      ax, 0xc00
000005E7  90                        nop      
000005E8  9B                        wait     
000005E9  0B 46 FE                  or       ax, word ptr [bp - 2]
000005EC  89 46 FC                  mov      word ptr [bp - 4], ax
000005EF  9B                        wait     
000005F0  D9 6E FC                  fldcw    word ptr [bp - 4]
000005F3  9B                        wait     
000005F4  DB 6E 0C                  fld      xword ptr [bp + 0xc]
000005F7  83 7E 16 00               cmp      word ptr [bp + 0x16], 0
000005FB  75 0A                     jne      0x607
000005FD  9B                        wait     
000005FE  D9 5E 04                  fstp     dword ptr [bp + 4]
00000601  9B                        wait     
00000602  D9 46 04                  fld      dword ptr [bp + 4]
00000605  EB 08                     jmp      0x60f
00000607  9B                        wait     
00000608  DD 5E 04                  fstp     qword ptr [bp + 4]
0000060B  9B                        wait     
0000060C  DD 46 04                  fld      qword ptr [bp + 4]
0000060F  9B                        wait     
00000610  D9 6E FE                  fldcw    word ptr [bp - 2]
00000613  8B E5                     mov      sp, bp
00000615  5D                        pop      bp
00000616  C2 14 00                  ret      0x14
00000619  8B C2                     mov      ax, dx
0000061B  0B 46 12                  or       ax, word ptr [bp + 0x12]
0000061E  0B 46 10                  or       ax, word ptr [bp + 0x10]
00000621  0B 46 0E                  or       ax, word ptr [bp + 0xe]
00000624  0B 46 0C                  or       ax, word ptr [bp + 0xc]
00000627  74 1A                     je       0x643
00000629  3B D3                     cmp      dx, bx
0000062B  7D 16                     jge      0x643
0000062D  9B                        wait     
0000062E  D9 EE                     fldz     
00000630  0B C9                     or       cx, cx
00000632  74 03                     je       0x637
00000634  9B                        wait     
00000635  D9 E0                     fchs     
00000637  C7 06 7E 00 22 00         mov      word ptr [0x7e], 0x22
0000063D  8B E5                     mov      sp, bp
0000063F  5D                        pop      bp
00000640  C2 14 00                  ret      0x14
00000643  83 7E 16 00               cmp      word ptr [bp + 0x16], 0
00000647  74 0E                     je       0x657
00000649  9B                        wait     
0000064A  DB 6E 0C                  fld      xword ptr [bp + 0xc]
0000064D  9B                        wait     
0000064E  DD 5E F4                  fstp     qword ptr [bp - 0xc]
00000651  9B                        wait     
00000652  DD 46 F4                  fld      qword ptr [bp - 0xc]
00000655  EB 0C                     jmp      0x663
00000657  9B                        wait     
00000658  DB 6E 0C                  fld      xword ptr [bp + 0xc]
0000065B  9B                        wait     
0000065C  D9 5E F4                  fstp     dword ptr [bp - 0xc]
0000065F  9B                        wait     
00000660  D9 46 F4                  fld      dword ptr [bp - 0xc]
00000663  EB 00                     jmp      0x665
00000665  8B E5                     mov      sp, bp
00000667  5D                        pop      bp
00000668  C2 14 00                  ret      0x14
0000066B  55                        push     bp
0000066C  8B EC                     mov      bp, sp
0000066E  B0 5F                     mov      al, 0x5f
00000670  22 C2                     and      al, dl
00000672  3C 47                     cmp      al, 0x47
00000674  75 0E                     jne      0x684
00000676  26 80 7F FF 30            cmp      byte ptr es:[bx - 1], 0x30
0000067B  75 07                     jne      0x684
0000067D  4B                        dec      bx
0000067E  3B D9                     cmp      bx, cx
00000680  77 F4                     ja       0x676
00000682  EB 07                     jmp      0x68b
00000684  26 38 77 FF               cmp      byte ptr es:[bx - 1], dh
00000688  75 01                     jne      0x68b
0000068A  4B                        dec      bx
0000068B  EB 00                     jmp      0x68d
0000068D  5D                        pop      bp
0000068E  C3                        ret      
0000068F  55                        push     bp
00000690  8B EC                     mov      bp, sp
00000692  83 EC 32                  sub      sp, 0x32
00000695  56                        push     si
00000696  57                        push     di
00000697  C4 1E 82 25               les      bx, ptr [0x2582]
0000069B  26 8A 07                  mov      al, byte ptr es:[bx]
0000069E  88 46 FB                  mov      byte ptr [bp - 5], al
000006A1  06                        push     es
000006A2  8B 46 0E                  mov      ax, word ptr [bp + 0xe]
000006A5  3D 28 00                  cmp      ax, 0x28
000006A8  76 06                     jbe      0x6b0
000006AA  B8 28 00                  mov      ax, 0x28
000006AD  89 46 0E                  mov      word ptr [bp + 0xe], ax
000006B0  89 46 FC                  mov      word ptr [bp - 4], ax
000006B3  8A 56 08                  mov      dl, byte ptr [bp + 8]
000006B6  80 E2 DF                  and      dl, 0xdf
000006B9  80 FA 46                  cmp      dl, 0x46
000006BC  75 0B                     jne      0x6c9
000006BE  F7 D8                     neg      ax
000006C0  7E 10                     jle      0x6d2
000006C2  2B C0                     sub      ax, ax
000006C4  89 46 0E                  mov      word ptr [bp + 0xe], ax
000006C7  EB 09                     jmp      0x6d2
000006C9  0B C0                     or       ax, ax
000006CB  7F 05                     jg       0x6d2
000006CD  B8 01 00                  mov      ax, 1
000006D0  EB 09                     jmp      0x6db
000006D2  80 FA 45                  cmp      dl, 0x45
000006D5  75 04                     jne      0x6db
000006D7  40                        inc      ax
000006D8  FF 46 0E                  inc      word ptr [bp + 0xe]
000006DB  FF 76 12                  push     word ptr [bp + 0x12]
000006DE  FF 76 10                  push     word ptr [bp + 0x10]
000006E1  50                        push     ax
000006E2  16                        push     ss
000006E3  8D 5E FE                  lea      bx, [bp - 2]
000006E6  53                        push     bx
000006E7  16                        push     ss
000006E8  8D 76 CE                  lea      si, [bp - 0x32]
000006EB  56                        push     si
000006EC  8B 46 04                  mov      ax, word ptr [bp + 4]
000006EF  50                        push     ax
000006F0  E8 EB 04                  call     0xbde
000006F3  93                        xchg     bx, ax
000006F4  C4 7E 0A                  les      di, ptr [bp + 0xa]
000006F7  FC                        cld      
000006F8  81 FB FF 7F               cmp      bx, 0x7fff
000006FC  74 08                     je       0x706
000006FE  81 FB FE 7F               cmp      bx, 0x7ffe
00000702  74 15                     je       0x719
00000704  EB 25                     jmp      0x72b
00000706  B8 2B 49                  mov      ax, 0x492b
00000709  83 7E FE 00               cmp      word ptr [bp - 2], 0
0000070D  74 02                     je       0x711
0000070F  40                        inc      ax
00000710  40                        inc      ax
00000711  AB                        stosw    word ptr es:[di], ax
00000712  B8 4E 46                  mov      ax, 0x464e
00000715  AB                        stosw    word ptr es:[di], ax
00000716  E9 13 01                  jmp      0x82c
00000719  B8 2B 4E                  mov      ax, 0x4e2b
0000071C  83 7E FE 00               cmp      word ptr [bp - 2], 0
00000720  74 02                     je       0x724
00000722  40                        inc      ax
00000723  40                        inc      ax
00000724  AB                        stosw    word ptr es:[di], ax
00000725  B0 41                     mov      al, 0x41
00000727  AB                        stosw    word ptr es:[di], ax
00000728  E9 01 01                  jmp      0x82c
0000072B  80 7E FE 00               cmp      byte ptr [bp - 2], 0
0000072F  74 03                     je       0x734
00000731  B0 2D                     mov      al, 0x2d
00000733  AA                        stosb    byte ptr es:[di], al
00000734  8A 56 08                  mov      dl, byte ptr [bp + 8]
00000737  80 E2 5F                  and      dl, 0x5f
0000073A  80 FA 46                  cmp      dl, 0x46
0000073D  74 16                     je       0x755
0000073F  80 FA 45                  cmp      dl, 0x45
00000742  74 79                     je       0x7bd
00000744  83 FB FD                  cmp      bx, -3
00000747  7C 74                     jl       0x7bd
00000749  8B 46 0E                  mov      ax, word ptr [bp + 0xe]
0000074C  0B C0                     or       ax, ax
0000074E  75 01                     jne      0x751
00000750  40                        inc      ax
00000751  3B D8                     cmp      bx, ax
00000753  7F 68                     jg       0x7bd
00000755  83 FB 28                  cmp      bx, 0x28
00000758  7F 63                     jg       0x7bd
0000075A  0B DB                     or       bx, bx
0000075C  7F 11                     jg       0x76f
0000075E  8A 66 FB                  mov      ah, byte ptr [bp - 5]
00000761  B0 30                     mov      al, 0x30
00000763  AB                        stosw    word ptr es:[di], ax
00000764  B9 01 00                  mov      cx, 1
00000767  74 09                     je       0x772
00000769  B0 30                     mov      al, 0x30
0000076B  AA                        stosb    byte ptr es:[di], al
0000076C  43                        inc      bx
0000076D  75 FC                     jne      0x76b
0000076F  B9 00 00                  mov      cx, 0
00000772  36 AC                     lodsb    al, byte ptr ss:[si]
00000774  0A C0                     or       al, al
00000776  74 0B                     je       0x783
00000778  AA                        stosb    byte ptr es:[di], al
00000779  4B                        dec      bx
0000077A  75 F6                     jne      0x772
0000077C  8A 46 FB                  mov      al, byte ptr [bp - 5]
0000077F  AA                        stosb    byte ptr es:[di], al
00000780  41                        inc      cx
00000781  EB EF                     jmp      0x772
00000783  8B 46 0E                  mov      ax, word ptr [bp + 0xe]
00000786  03 4E FC                  add      cx, word ptr [bp - 4]
00000789  3B C1                     cmp      ax, cx
0000078B  76 0D                     jbe      0x79a
0000078D  2B C1                     sub      ax, cx
0000078F  8B C8                     mov      cx, ax
00000791  03 D8                     add      bx, ax
00000793  B0 30                     mov      al, 0x30
00000795  F3 AA                     rep stosb byte ptr es:[di], al
00000797  4B                        dec      bx
00000798  74 19                     je       0x7b3
0000079A  4B                        dec      bx
0000079B  74 16                     je       0x7b3
0000079D  80 7E 06 00               cmp      byte ptr [bp + 6], 0
000007A1  75 10                     jne      0x7b3
000007A3  8A 56 08                  mov      dl, byte ptr [bp + 8]
000007A6  8B 4E 0A                  mov      cx, word ptr [bp + 0xa]
000007A9  87 DF                     xchg     di, bx
000007AB  8A 76 FB                  mov      dh, byte ptr [bp - 5]
000007AE  E8 BA FE                  call     0x66b
000007B1  87 FB                     xchg     bx, di
000007B3  3B 7E 0A                  cmp      di, word ptr [bp + 0xa]
000007B6  75 03                     jne      0x7bb
000007B8  B0 30                     mov      al, 0x30
000007BA  AA                        stosb    byte ptr es:[di], al
000007BB  EB 6F                     jmp      0x82c
000007BD  36 AD                     lodsw    ax, word ptr ss:[si]
000007BF  AA                        stosb    byte ptr es:[di], al
000007C0  8A 46 FB                  mov      al, byte ptr [bp - 5]
000007C3  0A E4                     or       ah, ah
000007C5  75 09                     jne      0x7d0
000007C7  80 7E 06 00               cmp      byte ptr [bp + 6], 0
000007CB  74 23                     je       0x7f0
000007CD  AA                        stosb    byte ptr es:[di], al
000007CE  EB 20                     jmp      0x7f0
000007D0  AA                        stosb    byte ptr es:[di], al
000007D1  8A C4                     mov      al, ah
000007D3  AA                        stosb    byte ptr es:[di], al
000007D4  36 AC                     lodsb    al, byte ptr ss:[si]
000007D6  0A C0                     or       al, al
000007D8  75 F9                     jne      0x7d3
000007DA  80 7E 06 00               cmp      byte ptr [bp + 6], 0
000007DE  75 10                     jne      0x7f0
000007E0  8A 56 08                  mov      dl, byte ptr [bp + 8]
000007E3  8B 4E 0A                  mov      cx, word ptr [bp + 0xa]
000007E6  87 DF                     xchg     di, bx
000007E8  8A 76 FB                  mov      dh, byte ptr [bp - 5]
000007EB  E8 7D FE                  call     0x66b
000007EE  87 FB                     xchg     bx, di
000007F0  B0 20                     mov      al, 0x20
000007F2  22 46 08                  and      al, byte ptr [bp + 8]
000007F5  0C 45                     or       al, 0x45
000007F7  AA                        stosb    byte ptr es:[di], al
000007F8  B8 2B 2D                  mov      ax, 0x2d2b
000007FB  4B                        dec      bx
000007FC  7D 04                     jge      0x802
000007FE  86 C4                     xchg     ah, al
00000800  F7 DB                     neg      bx
00000802  AA                        stosb    byte ptr es:[di], al
00000803  93                        xchg     bx, ax
00000804  B9 30 30                  mov      cx, 0x3030
00000807  3D 63 00                  cmp      ax, 0x63
0000080A  76 19                     jbe      0x825
0000080C  3D E7 03                  cmp      ax, 0x3e7
0000080F  76 0A                     jbe      0x81b
00000811  99                        cdq      
00000812  BB E8 03                  mov      bx, 0x3e8
00000815  F7 F3                     div      bx
00000817  02 C1                     add      al, cl
00000819  AA                        stosb    byte ptr es:[di], al
0000081A  92                        xchg     dx, ax
0000081B  B3 64                     mov      bl, 0x64
0000081D  F6 F3                     div      bl
0000081F  02 C1                     add      al, cl
00000821  AA                        stosb    byte ptr es:[di], al
00000822  86 C4                     xchg     ah, al
00000824  98                        cwde     
00000825  B3 0A                     mov      bl, 0xa
00000827  F6 F3                     div      bl
00000829  03 C1                     add      ax, cx
0000082B  AB                        stosw    word ptr es:[di], ax
0000082C  32 C0                     xor      al, al
0000082E  AA                        stosb    byte ptr es:[di], al
0000082F  07                        pop      es
00000830  EB 00                     jmp      0x832
00000832  5F                        pop      di
00000833  5E                        pop      si
00000834  8B E5                     mov      sp, bp
00000836  5D                        pop      bp
00000837  C2 10 00                  ret      0x10
0000083A  55                        push     bp
0000083B  8B EC                     mov      bp, sp
0000083D  5D                        pop      bp
0000083E  C3                        ret      
0000083F  55                        push     bp
00000840  8B EC                     mov      bp, sp
00000842  83 EC 1A                  sub      sp, 0x1a
00000845  56                        push     si
00000846  57                        push     di
00000847  C6 46 FB 00               mov      byte ptr [bp - 5], 0
0000084B  C6 46 FA 01               mov      byte ptr [bp - 6], 1
0000084F  C6 46 F9 00               mov      byte ptr [bp - 7], 0
00000853  C6 46 F8 00               mov      byte ptr [bp - 8], 0
00000857  C6 46 F7 00               mov      byte ptr [bp - 9], 0
0000085B  C7 46 F4 00 00            mov      word ptr [bp - 0xc], 0
00000860  C7 46 F2 01 00            mov      word ptr [bp - 0xe], 1
00000865  9B                        wait     
00000866  D9 EE                     fldz     
00000868  9B                        wait     
00000869  DB 7E E8                  fstp     xword ptr [bp - 0x18]
0000086C  90                        nop      
0000086D  9B                        wait     
0000086E  C4 1E 82 25               les      bx, ptr [0x2582]
00000872  26 8A 07                  mov      al, byte ptr es:[bx]
00000875  88 46 E7                  mov      byte ptr [bp - 0x19], al
00000878  BE 00 80                  mov      si, 0x8000
0000087B  BF FE FF                  mov      di, 0xfffe
0000087E  FF 46 F4                  inc      word ptr [bp - 0xc]
00000881  FF 76 0A                  push     word ptr [bp + 0xa]
00000884  FF 76 08                  push     word ptr [bp + 8]
00000887  FF 56 04                  call     word ptr [bp + 4]
0000088A  59                        pop      cx
0000088B  59                        pop      cx
0000088C  0B C0                     or       ax, ax
0000088E  7D 03                     jge      0x893
00000890  E9 82 00                  jmp      0x915
00000893  98                        cwde     
00000894  93                        xchg     bx, ax
00000895  F6 C3 80                  test     bl, 0x80
00000898  75 07                     jne      0x8a1
0000089A  F6 87 BF 25 01            test     byte ptr [bx + 0x25bf], 1
0000089F  75 DD                     jne      0x87e
000008A1  93                        xchg     bx, ax
000008A2  FF 4E 0C                  dec      word ptr [bp + 0xc]
000008A5  7C 69                     jl       0x910
000008A7  3C 2B                     cmp      al, 0x2b
000008A9  74 07                     je       0x8b2
000008AB  3C 2D                     cmp      al, 0x2d
000008AD  75 35                     jne      0x8e4
000008AF  FE 46 FB                  inc      byte ptr [bp - 5]
000008B2  FE 46 F9                  inc      byte ptr [bp - 7]
000008B5  FF 4E 0C                  dec      word ptr [bp + 0xc]
000008B8  7C 56                     jl       0x910
000008BA  FF 46 F4                  inc      word ptr [bp - 0xc]
000008BD  FF 76 0A                  push     word ptr [bp + 0xa]
000008C0  FF 76 08                  push     word ptr [bp + 8]
000008C3  FF 56 04                  call     word ptr [bp + 4]
000008C6  59                        pop      cx
000008C7  59                        pop      cx
000008C8  80 7E FA 01               cmp      byte ptr [bp - 6], 1
000008CC  75 16                     jne      0x8e4
000008CE  80 7E F9 00               cmp      byte ptr [bp - 7], 0
000008D2  74 10                     je       0x8e4
000008D4  3C 49                     cmp      al, 0x49
000008D6  74 06                     je       0x8de
000008D8  3C 4E                     cmp      al, 0x4e
000008DA  74 05                     je       0x8e1
000008DC  EB 06                     jmp      0x8e4
000008DE  E9 E0 01                  jmp      0xac1
000008E1  E9 1F 02                  jmp      0xb03
000008E4  C6 46 FA 00               mov      byte ptr [bp - 6], 0
000008E8  3A 46 E7                  cmp      al, byte ptr [bp - 0x19]
000008EB  74 32                     je       0x91f
000008ED  3C 39                     cmp      al, 0x39
000008EF  77 2B                     ja       0x91c
000008F1  3C 30                     cmp      al, 0x30
000008F3  72 27                     jb       0x91c
000008F5  2C 30                     sub      al, 0x30
000008F7  98                        cwde     
000008F8  47                        inc      di
000008F9  7F 34                     jg       0x92f
000008FB  88 46 E8                  mov      byte ptr [bp - 0x18], al
000008FE  BF 01 00                  mov      di, 1
00000901  0A C0                     or       al, al
00000903  75 B0                     jne      0x8b5
00000905  F7 DF                     neg      di
00000907  81 FE 00 80               cmp      si, 0x8000
0000090B  74 A8                     je       0x8b5
0000090D  4E                        dec      si
0000090E  EB A5                     jmp      0x8b5
00000910  B0 65                     mov      al, 0x65
00000912  E9 90 00                  jmp      0x9a5
00000915  C7 46 F2 FF FF            mov      word ptr [bp - 0xe], 0xffff
0000091A  EB 6D                     jmp      0x989
0000091C  E9 86 00                  jmp      0x9a5
0000091F  81 FE 00 80               cmp      si, 0x8000
00000923  75 ED                     jne      0x912
00000925  2B F6                     sub      si, si
00000927  0B FF                     or       di, di
00000929  7E 8A                     jle      0x8b5
0000092B  8B F7                     mov      si, di
0000092D  EB 86                     jmp      0x8b5
0000092F  83 FF 05                  cmp      di, 5
00000932  77 14                     ja       0x948
00000934  93                        xchg     bx, ax
00000935  B8 0A 00                  mov      ax, 0xa
00000938  F7 66 E8                  mul      word ptr [bp - 0x18]
0000093B  03 C3                     add      ax, bx
0000093D  12 D6                     adc      dl, dh
0000093F  89 46 E8                  mov      word ptr [bp - 0x18], ax
00000942  89 56 EA                  mov      word ptr [bp - 0x16], dx
00000945  E9 6D FF                  jmp      0x8b5
00000948  83 FF 12                  cmp      di, 0x12
0000094B  77 34                     ja       0x981
0000094D  93                        xchg     bx, ax
0000094E  B8 0A 00                  mov      ax, 0xa
00000951  F7 66 EE                  mul      word ptr [bp - 0x12]
00000954  89 46 EE                  mov      word ptr [bp - 0x12], ax
00000957  B8 0A 00                  mov      ax, 0xa
0000095A  F7 66 EC                  mul      word ptr [bp - 0x14]
0000095D  89 46 EC                  mov      word ptr [bp - 0x14], ax
00000960  52                        push     dx
00000961  B8 0A 00                  mov      ax, 0xa
00000964  F7 66 EA                  mul      word ptr [bp - 0x16]
00000967  89 46 EA                  mov      word ptr [bp - 0x16], ax
0000096A  52                        push     dx
0000096B  B8 0A 00                  mov      ax, 0xa
0000096E  F7 66 E8                  mul      word ptr [bp - 0x18]
00000971  03 C3                     add      ax, bx
00000973  89 46 E8                  mov      word ptr [bp - 0x18], ax
00000976  11 56 EA                  adc      word ptr [bp - 0x16], dx
00000979  5A                        pop      dx
0000097A  11 56 EC                  adc      word ptr [bp - 0x14], dx
0000097D  5A                        pop      dx
0000097E  11 56 EE                  adc      word ptr [bp - 0x12], dx
00000981  E9 31 FF                  jmp      0x8b5
00000984  C7 46 F2 00 00            mov      word ptr [bp - 0xe], 0
00000989  83 7E 0C 00               cmp      word ptr [bp + 0xc], 0
0000098D  7C 10                     jl       0x99f
0000098F  FF 76 0A                  push     word ptr [bp + 0xa]
00000992  FF 76 08                  push     word ptr [bp + 8]
00000995  50                        push     ax
00000996  FF 56 06                  call     word ptr [bp + 6]
00000999  83 C4 06                  add      sp, 6
0000099C  FF 4E F4                  dec      word ptr [bp - 0xc]
0000099F  9B                        wait     
000009A0  D9 EE                     fldz     
000009A2  E9 FE 00                  jmp      0xaa3
000009A5  83 FF FE                  cmp      di, -2
000009A8  74 DA                     je       0x984
000009AA  81 FE 00 80               cmp      si, 0x8000
000009AE  75 02                     jne      0x9b2
000009B0  8B F7                     mov      si, di
000009B2  89 7E FC                  mov      word ptr [bp - 4], di
000009B5  89 76 FE                  mov      word ptr [bp - 2], si
000009B8  2B FF                     sub      di, di
000009BA  3C 45                     cmp      al, 0x45
000009BC  74 04                     je       0x9c2
000009BE  3C 65                     cmp      al, 0x65
000009C0  75 52                     jne      0xa14
000009C2  FF 4E 0C                  dec      word ptr [bp + 0xc]
000009C5  7C 5D                     jl       0xa24
000009C7  FF 46 F4                  inc      word ptr [bp - 0xc]
000009CA  FF 76 0A                  push     word ptr [bp + 0xa]
000009CD  FF 76 08                  push     word ptr [bp + 8]
000009D0  FF 56 04                  call     word ptr [bp + 4]
000009D3  59                        pop      cx
000009D4  59                        pop      cx
000009D5  3C 2B                     cmp      al, 0x2b
000009D7  74 07                     je       0x9e0
000009D9  3C 2D                     cmp      al, 0x2d
000009DB  75 16                     jne      0x9f3
000009DD  FE 46 F8                  inc      byte ptr [bp - 8]
000009E0  FF 4E 0C                  dec      word ptr [bp + 0xc]
000009E3  7C 3F                     jl       0xa24
000009E5  FF 46 F4                  inc      word ptr [bp - 0xc]
000009E8  FF 76 0A                  push     word ptr [bp + 0xa]
000009EB  FF 76 08                  push     word ptr [bp + 8]
000009EE  FF 56 04                  call     word ptr [bp + 4]
000009F1  59                        pop      cx
000009F2  59                        pop      cx
000009F3  3C 39                     cmp      al, 0x39
000009F5  77 1D                     ja       0xa14
000009F7  2C 30                     sub      al, 0x30
000009F9  72 17                     jb       0xa12
000009FB  98                        cwde     
000009FC  97                        xchg     di, ax
000009FD  BA 0A 00                  mov      dx, 0xa
00000A00  F7 E2                     mul      dx
00000A02  03 F8                     add      di, ax
00000A04  81 FF 44 13               cmp      di, 0x1344
00000A08  7E D6                     jle      0x9e0
00000A0A  33 FF                     xor      di, di
00000A0C  C6 46 F7 01               mov      byte ptr [bp - 9], 1
00000A10  EB CE                     jmp      0x9e0
00000A12  04 30                     add      al, 0x30
00000A14  FF 76 0A                  push     word ptr [bp + 0xa]
00000A17  FF 76 08                  push     word ptr [bp + 8]
00000A1A  50                        push     ax
00000A1B  FF 56 06                  call     word ptr [bp + 6]
00000A1E  83 C4 06                  add      sp, 6
00000A21  FF 4E F4                  dec      word ptr [bp - 0xc]
00000A24  F6 46 F8 FF               test     byte ptr [bp - 8], 0xff
00000A28  74 05                     je       0xa2f
00000A2A  F7 DF                     neg      di
00000A2C  F6 5E F7                  neg      byte ptr [bp - 9]
00000A2F  8B 5E FC                  mov      bx, word ptr [bp - 4]
00000A32  0B DB                     or       bx, bx
00000A34  7D 05                     jge      0xa3b
00000A36  9B                        wait     
00000A37  D9 EE                     fldz     
00000A39  EB 68                     jmp      0xaa3
00000A3B  8B 4E FE                  mov      cx, word ptr [bp - 2]
00000A3E  8B C1                     mov      ax, cx
00000A40  03 C7                     add      ax, di
00000A42  80 7E F7 01               cmp      byte ptr [bp - 9], 1
00000A46  74 0B                     je       0xa53
00000A48  80 7E F7 FF               cmp      byte ptr [bp - 9], 0xff
00000A4C  75 24                     jne      0xa72
00000A4E  9B                        wait     
00000A4F  D9 EE                     fldz     
00000A51  EB 18                     jmp      0xa6b
00000A53  B8 FF FF                  mov      ax, 0xffff
00000A56  89 46 E8                  mov      word ptr [bp - 0x18], ax
00000A59  89 46 EA                  mov      word ptr [bp - 0x16], ax
00000A5C  89 46 EC                  mov      word ptr [bp - 0x14], ax
00000A5F  89 46 EE                  mov      word ptr [bp - 0x12], ax
00000A62  C7 46 F0 FE 7F            mov      word ptr [bp - 0x10], 0x7ffe
00000A67  9B                        wait     
00000A68  DB 6E E8                  fld      xword ptr [bp - 0x18]
00000A6B  C7 46 F2 02 00            mov      word ptr [bp - 0xe], 2
00000A70  EB 31                     jmp      0xaa3
00000A72  8B C3                     mov      ax, bx
00000A74  83 FB 12                  cmp      bx, 0x12
00000A77  76 03                     jbe      0xa7c
00000A79  BB 12 00                  mov      bx, 0x12
00000A7C  03 C1                     add      ax, cx
00000A7E  2B CB                     sub      cx, bx
00000A80  03 F9                     add      di, cx
00000A82  9B                        wait     
00000A83  DF 6E E8                  fild     qword ptr [bp - 0x18]
00000A86  8B C7                     mov      ax, di
00000A88  0B C0                     or       ax, ax
00000A8A  74 17                     je       0xaa3
00000A8C  7D 02                     jge      0xa90
00000A8E  F7 D8                     neg      ax
00000A90  50                        push     ax
00000A91  90                        nop      
00000A92  0E                        push     cs
00000A93  E8 5E 03                  call     0xdf4
00000A96  58                        pop      ax
00000A97  0B FF                     or       di, di
00000A99  7D 05                     jge      0xaa0
00000A9B  9B                        wait     
00000A9C  DE F9                     fdivp    st(1)
00000A9E  EB 03                     jmp      0xaa3
00000AA0  9B                        wait     
00000AA1  DE C9                     fmulp    st(1)
00000AA3  80 7E FB 00               cmp      byte ptr [bp - 5], 0
00000AA7  74 03                     je       0xaac
00000AA9  9B                        wait     
00000AAA  D9 E0                     fchs     
00000AAC  C4 7E 0E                  les      di, ptr [bp + 0xe]
00000AAF  8B 5E F4                  mov      bx, word ptr [bp - 0xc]
00000AB2  26 01 1D                  add      word ptr es:[di], bx
00000AB5  C4 7E 12                  les      di, ptr [bp + 0x12]
00000AB8  8B 5E F2                  mov      bx, word ptr [bp - 0xe]
00000ABB  26 89 1D                  mov      word ptr es:[di], bx
00000ABE  E9 8D 00                  jmp      0xb4e
00000AC1  FF 46 F4                  inc      word ptr [bp - 0xc]
00000AC4  FF 76 0A                  push     word ptr [bp + 0xa]
00000AC7  FF 76 08                  push     word ptr [bp + 8]
00000ACA  FF 56 04                  call     word ptr [bp + 4]
00000ACD  59                        pop      cx
00000ACE  59                        pop      cx
00000ACF  FF 4E 0C                  dec      word ptr [bp + 0xc]
00000AD2  7C 72                     jl       0xb46
00000AD4  3C 4E                     cmp      al, 0x4e
00000AD6  75 6E                     jne      0xb46
00000AD8  FF 46 F4                  inc      word ptr [bp - 0xc]
00000ADB  FF 76 0A                  push     word ptr [bp + 0xa]
00000ADE  FF 76 08                  push     word ptr [bp + 8]
00000AE1  FF 56 04                  call     word ptr [bp + 4]
00000AE4  59                        pop      cx
00000AE5  59                        pop      cx
00000AE6  FF 4E 0C                  dec      word ptr [bp + 0xc]
00000AE9  7C 5B                     jl       0xb46
00000AEB  3C 46                     cmp      al, 0x46
00000AED  75 57                     jne      0xb46
00000AEF  80 7E FB 00               cmp      byte ptr [bp - 5], 0
00000AF3  74 07                     je       0xafc
00000AF5  9B                        wait     
00000AF6  D9 06 40 1C               fld      dword ptr [0x1c40]
00000AFA  EB 05                     jmp      0xb01
00000AFC  9B                        wait     
00000AFD  D9 06 3C 1C               fld      dword ptr [0x1c3c]
00000B01  EB A9                     jmp      0xaac
00000B03  FF 46 F4                  inc      word ptr [bp - 0xc]
00000B06  FF 76 0A                  push     word ptr [bp + 0xa]
00000B09  FF 76 08                  push     word ptr [bp + 8]
00000B0C  FF 56 04                  call     word ptr [bp + 4]
00000B0F  59                        pop      cx
00000B10  59                        pop      cx
00000B11  FF 4E 0C                  dec      word ptr [bp + 0xc]
00000B14  7C 30                     jl       0xb46
00000B16  3C 41                     cmp      al, 0x41
00000B18  75 2C                     jne      0xb46
00000B1A  FF 46 F4                  inc      word ptr [bp - 0xc]
00000B1D  FF 76 0A                  push     word ptr [bp + 0xa]
00000B20  FF 76 08                  push     word ptr [bp + 8]
00000B23  FF 56 04                  call     word ptr [bp + 4]
00000B26  59                        pop      cx
00000B27  59                        pop      cx
00000B28  FF 4E 0C                  dec      word ptr [bp + 0xc]
00000B2B  7C 19                     jl       0xb46
00000B2D  3C 4E                     cmp      al, 0x4e
00000B2F  75 15                     jne      0xb46
00000B31  80 7E FB 00               cmp      byte ptr [bp - 5], 0
00000B35  74 07                     je       0xb3e
00000B37  9B                        wait     
00000B38  D9 06 48 1C               fld      dword ptr [0x1c48]
00000B3C  EB 05                     jmp      0xb43
00000B3E  9B                        wait     
00000B3F  D9 06 44 1C               fld      dword ptr [0x1c44]
00000B43  E9 66 FF                  jmp      0xaac
00000B46  C7 46 F2 00 00            mov      word ptr [bp - 0xe], 0
00000B4B  E9 36 FE                  jmp      0x984
00000B4E  5F                        pop      di
00000B4F  5E                        pop      si
00000B50  8B E5                     mov      sp, bp
00000B52  5D                        pop      bp
00000B53  C3                        ret      
00000B54  55                        push     bp
00000B55  8B EC                     mov      bp, sp
00000B57  9B                        wait     
00000B58  DD D8                     fstp     st(0)
00000B5A  5D                        pop      bp
00000B5B  C3                        ret      
00000B5C  55                        push     bp
00000B5D  8B EC                     mov      bp, sp
00000B5F  83 EC 0A                  sub      sp, 0xa
00000B62  56                        push     si
00000B63  8B 76 08                  mov      si, word ptr [bp + 8]
00000B66  9B                        wait     
00000B67  DB 7E F6                  fstp     xword ptr [bp - 0xa]
00000B6A  F7 C6 04 00               test     si, 4
00000B6E  74 29                     je       0xb99
00000B70  B8 01 00                  mov      ax, 1
00000B73  50                        push     ax
00000B74  9B                        wait     
00000B75  DB 6E F6                  fld      xword ptr [bp - 0xa]
00000B78  83 EC 0A                  sub      sp, 0xa
00000B7B  9B                        wait     
00000B7C  DB 7E E8                  fstp     xword ptr [bp - 0x18]
00000B7F  9B                        wait     
00000B80  DD 06 06 1C               fld      qword ptr [0x1c06]
00000B84  83 EC 08                  sub      sp, 8
00000B87  9B                        wait     
00000B88  DD 5E E0                  fstp     qword ptr [bp - 0x20]
00000B8B  90                        nop      
00000B8C  9B                        wait     
00000B8D  E8 1B FA                  call     0x5ab
00000B90  C4 5E 04                  les      bx, ptr [bp + 4]
00000B93  9B                        wait     
00000B94  26 DD 1F                  fstp     qword ptr es:[bx]
00000B97  EB 39                     jmp      0xbd2
00000B99  F7 C6 08 00               test     si, 8
00000B9D  74 0D                     je       0xbac
00000B9F  C4 5E 04                  les      bx, ptr [bp + 4]
00000BA2  9B                        wait     
00000BA3  DB 6E F6                  fld      xword ptr [bp - 0xa]
00000BA6  9B                        wait     
00000BA7  26 DB 3F                  fstp     xword ptr es:[bx]
00000BAA  EB 26                     jmp      0xbd2
00000BAC  33 C0                     xor      ax, ax
00000BAE  50                        push     ax
00000BAF  9B                        wait     
00000BB0  DB 6E F6                  fld      xword ptr [bp - 0xa]
00000BB3  83 EC 0A                  sub      sp, 0xa
00000BB6  9B                        wait     
00000BB7  DB 7E E8                  fstp     xword ptr [bp - 0x18]
00000BBA  9B                        wait     
00000BBB  DD 06 4C 1C               fld      qword ptr [0x1c4c]
00000BBF  83 EC 08                  sub      sp, 8
00000BC2  9B                        wait     
00000BC3  DD 5E E0                  fstp     qword ptr [bp - 0x20]
00000BC6  90                        nop      
00000BC7  9B                        wait     
00000BC8  E8 E0 F9                  call     0x5ab
00000BCB  C4 5E 04                  les      bx, ptr [bp + 4]
00000BCE  9B                        wait     
00000BCF  26 D9 1F                  fstp     dword ptr es:[bx]
00000BD2  90                        nop      
00000BD3  9B                        wait     
00000BD4  5E                        pop      si
00000BD5  8B E5                     mov      sp, bp
00000BD7  5D                        pop      bp
00000BD8  C3                        ret      
00000BD9  55                        push     bp
00000BDA  8B EC                     mov      bp, sp
00000BDC  5D                        pop      bp
00000BDD  CB                        retf     
00000BDE  55                        push     bp
00000BDF  8B EC                     mov      bp, sp
00000BE1  83 EC 10                  sub      sp, 0x10
00000BE4  56                        push     si
00000BE5  57                        push     di
00000BE6  C7 46 FE 00 80            mov      word ptr [bp - 2], 0x8000
00000BEB  C7 46 FC 0A 00            mov      word ptr [bp - 4], 0xa
00000BF0  06                        push     es
00000BF1  C4 7E 10                  les      di, ptr [bp + 0x10]
00000BF4  B8 FF 7F                  mov      ax, 0x7fff
00000BF7  8B 5E 04                  mov      bx, word ptr [bp + 4]
00000BFA  26 8B 09                  mov      cx, word ptr es:[bx + di]
00000BFD  21 4E FE                  and      word ptr [bp - 2], cx
00000C00  26 21 01                  and      word ptr es:[bx + di], ax
00000C03  D1 EB                     shr      bx, 1
00000C05  D1 EB                     shr      bx, 1
00000C07  D1 E3                     shl      bx, 1
00000C09  2E FF A7 0E 0C            jmp      word ptr cs:[bx + 0xc0e]
00000C0E  14 0C                     adc      al, 0xc
00000C10  1A 0C                     sbb      cl, byte ptr [si]
00000C12  20 0C                     and      byte ptr [si], cl
00000C14  9B                        wait     
00000C15  26 D9 05                  fld      dword ptr es:[di]
00000C18  EB 17                     jmp      0xc31
00000C1A  9B                        wait     
00000C1B  26 DD 05                  fld      qword ptr es:[di]
00000C1E  EB 11                     jmp      0xc31
00000C20  26 23 45 08               and      ax, word ptr es:[di + 8]
00000C24  3D FF 7F                  cmp      ax, 0x7fff
00000C27  74 04                     je       0xc2d
00000C29  26 80 25 F0               and      byte ptr es:[di], 0xf0
00000C2D  9B                        wait     
00000C2E  26 DB 2D                  fld      xword ptr es:[di]
00000C31  33 DB                     xor      bx, bx
00000C33  D1 E1                     shl      cx, 1
00000C35  D1 D3                     rcl      bx, 1
00000C37  C4 7E 0A                  les      di, ptr [bp + 0xa]
00000C3A  26 89 1D                  mov      word ptr es:[di], bx
00000C3D  9B                        wait     
00000C3E  D9 E5                     fxam     
00000C40  9B                        wait     
00000C41  DD 7E FA                  fnstsw   word ptr [bp - 6]
00000C44  90                        nop      
00000C45  9B                        wait     
00000C46  8B 46 FA                  mov      ax, word ptr [bp - 6]
00000C49  80 E4 47                  and      ah, 0x47
00000C4C  80 FC 40                  cmp      ah, 0x40
00000C4F  74 16                     je       0xc67
00000C51  80 FC 05                  cmp      ah, 5
00000C54  74 0C                     je       0xc62
00000C56  80 FC 01                  cmp      ah, 1
00000C59  74 02                     je       0xc5d
00000C5B  EB 38                     jmp      0xc95
00000C5D  BA FE 7F                  mov      dx, 0x7ffe
00000C60  EB 2D                     jmp      0xc8f
00000C62  BA FF 7F                  mov      dx, 0x7fff
00000C65  EB 28                     jmp      0xc8f
00000C67  BA 01 00                  mov      dx, 1
00000C6A  B0 30                     mov      al, 0x30
00000C6C  C4 7E 0A                  les      di, ptr [bp + 0xa]
00000C6F  26 C7 05 00 00            mov      word ptr es:[di], 0
00000C74  8B 4E 0E                  mov      cx, word ptr [bp + 0xe]
00000C77  0B C9                     or       cx, cx
00000C79  7F 03                     jg       0xc7e
00000C7B  F7 D9                     neg      cx
00000C7D  41                        inc      cx
00000C7E  83 F9 28                  cmp      cx, 0x28
00000C81  76 03                     jbe      0xc86
00000C83  B9 28 00                  mov      cx, 0x28
00000C86  FC                        cld      
00000C87  C4 7E 06                  les      di, ptr [bp + 6]
00000C8A  F3 AA                     rep stosb byte ptr es:[di], al
00000C8C  32 C0                     xor      al, al
00000C8E  AA                        stosb    byte ptr es:[di], al
00000C8F  9B                        wait     
00000C90  DD D8                     fstp     st(0)
00000C92  E9 45 01                  jmp      0xdda
00000C95  9B                        wait     
00000C96  D9 C0                     fld      st(0)
00000C98  9B                        wait     
00000C99  DB 7E F0                  fstp     xword ptr [bp - 0x10]
00000C9C  90                        nop      
00000C9D  9B                        wait     
00000C9E  8B 46 F8                  mov      ax, word ptr [bp - 8]
00000CA1  2D FF 3F                  sub      ax, 0x3fff
00000CA4  BA 10 4D                  mov      dx, 0x4d10
00000CA7  F7 EA                     imul     dx
00000CA9  93                        xchg     bx, ax
00000CAA  B4 4D                     mov      ah, 0x4d
00000CAC  8A 46 F7                  mov      al, byte ptr [bp - 9]
00000CAF  D0 E0                     shl      al, 1
00000CB1  F6 E4                     mul      ah
00000CB3  03 C3                     add      ax, bx
00000CB5  83 D2 00                  adc      dx, 0
00000CB8  F7 D8                     neg      ax
00000CBA  83 D2 00                  adc      dx, 0
00000CBD  8B 46 0E                  mov      ax, word ptr [bp + 0xe]
00000CC0  0B C0                     or       ax, ax
00000CC2  7F 06                     jg       0xcca
00000CC4  F7 D8                     neg      ax
00000CC6  03 C2                     add      ax, dx
00000CC8  7C 9D                     jl       0xc67
00000CCA  3D 12 00                  cmp      ax, 0x12
00000CCD  7E 03                     jle      0xcd2
00000CCF  B8 12 00                  mov      ax, 0x12
00000CD2  8B D8                     mov      bx, ax
00000CD4  2B C2                     sub      ax, dx
00000CD6  74 28                     je       0xd00
00000CD8  8B F0                     mov      si, ax
00000CDA  7D 02                     jge      0xcde
00000CDC  F7 D8                     neg      ax
00000CDE  3D 44 13                  cmp      ax, 0x1344
00000CE1  7E 03                     jle      0xce6
00000CE3  B8 44 13                  mov      ax, 0x1344
00000CE6  50                        push     ax
00000CE7  90                        nop      
00000CE8  0E                        push     cs
00000CE9  E8 08 01                  call     0xdf4
00000CEC  58                        pop      ax
00000CED  0B F6                     or       si, si
00000CEF  7F 07                     jg       0xcf8
00000CF1  9B                        wait     
00000CF2  DE F9                     fdivp    st(1)
00000CF4  03 C6                     add      ax, si
00000CF6  EB DE                     jmp      0xcd6
00000CF8  9B                        wait     
00000CF9  DE C9                     fmulp    st(1)
00000CFB  96                        xchg     si, ax
00000CFC  2B C6                     sub      ax, si
00000CFE  EB D6                     jmp      0xcd6
00000D00  53                        push     bx
00000D01  90                        nop      
00000D02  0E                        push     cs
00000D03  E8 EE 00                  call     0xdf4
00000D06  58                        pop      ax
00000D07  9B                        wait     
00000D08  D8 D9                     fcomp    st(1)
00000D0A  9B                        wait     
00000D0B  DD 7E FA                  fnstsw   word ptr [bp - 6]
00000D0E  90                        nop      
00000D0F  9B                        wait     
00000D10  F6 46 FB 45               test     byte ptr [bp - 5], 0x45
00000D14  74 14                     je       0xd2a
00000D16  42                        inc      dx
00000D17  43                        inc      bx
00000D18  83 FB 12                  cmp      bx, 0x12
00000D1B  77 06                     ja       0xd23
00000D1D  83 7E 0E 00               cmp      word ptr [bp + 0xe], 0
00000D21  7E 2D                     jle      0xd50
00000D23  9B                        wait     
00000D24  DE 76 FC                  fidiv    word ptr [bp - 4]
00000D27  4B                        dec      bx
00000D28  EB 26                     jmp      0xd50
00000D2A  8B C3                     mov      ax, bx
00000D2C  48                        dec      ax
00000D2D  50                        push     ax
00000D2E  90                        nop      
00000D2F  0E                        push     cs
00000D30  E8 C1 00                  call     0xdf4
00000D33  58                        pop      ax
00000D34  9B                        wait     
00000D35  D8 D9                     fcomp    st(1)
00000D37  9B                        wait     
00000D38  DD 7E FA                  fnstsw   word ptr [bp - 6]
00000D3B  90                        nop      
00000D3C  9B                        wait     
00000D3D  F6 46 FB 41               test     byte ptr [bp - 5], 0x41
00000D41  75 0D                     jne      0xd50
00000D43  4A                        dec      dx
00000D44  4B                        dec      bx
00000D45  83 7E 0E 00               cmp      word ptr [bp + 0xe], 0
00000D49  7E 05                     jle      0xd50
00000D4B  9B                        wait     
00000D4C  DE 4E FC                  fimul    word ptr [bp - 4]
00000D4F  43                        inc      bx
00000D50  0B DB                     or       bx, bx
00000D52  7C 25                     jl       0xd79
00000D54  9B                        wait     
00000D55  D9 FC                     frndint  
00000D57  9B                        wait     
00000D58  DF 76 F0                  fbstp    tbyte ptr [bp - 0x10]
00000D5B  C4 7E 06                  les      di, ptr [bp + 6]
00000D5E  03 FB                     add      di, bx
00000D60  57                        push     di
00000D61  32 C0                     xor      al, al
00000D63  FD                        std      
00000D64  AA                        stosb    byte ptr es:[di], al
00000D65  8D 76 F0                  lea      si, [bp - 0x10]
00000D68  B9 04 00                  mov      cx, 4
00000D6B  90                        nop      
00000D6C  9B                        wait     
00000D6D  0B DB                     or       bx, bx
00000D6F  75 0F                     jne      0xd80
00000D71  36 8A 2C                  mov      ch, byte ptr ss:[si]
00000D74  80 F5 01                  xor      ch, 1
00000D77  74 22                     je       0xd9b
00000D79  9B                        wait     
00000D7A  D9 EE                     fldz     
00000D7C  5F                        pop      di
00000D7D  E9 E7 FE                  jmp      0xc67
00000D80  36 8A 04                  mov      al, byte ptr ss:[si]
00000D83  46                        inc      si
00000D84  8A E0                     mov      ah, al
00000D86  D2 EC                     shr      ah, cl
00000D88  24 0F                     and      al, 0xf
00000D8A  05 30 30                  add      ax, 0x3030
00000D8D  AA                        stosb    byte ptr es:[di], al
00000D8E  0A E8                     or       ch, al
00000D90  4B                        dec      bx
00000D91  74 08                     je       0xd9b
00000D93  8A C4                     mov      al, ah
00000D95  AA                        stosb    byte ptr es:[di], al
00000D96  0A E8                     or       ch, al
00000D98  4B                        dec      bx
00000D99  75 E5                     jne      0xd80
00000D9B  5B                        pop      bx
00000D9C  80 E5 0F                  and      ch, 0xf
00000D9F  75 11                     jne      0xdb2
00000DA1  42                        inc      dx
00000DA2  83 7E 0E 00               cmp      word ptr [bp + 0xe], 0
00000DA6  7F 04                     jg       0xdac
00000DA8  26 C6 07 30               mov      byte ptr es:[bx], 0x30
00000DAC  43                        inc      bx
00000DAD  26 C6 45 01 31            mov      byte ptr es:[di + 1], 0x31
00000DB2  8B 4E 0E                  mov      cx, word ptr [bp + 0xe]
00000DB5  0B C9                     or       cx, cx
00000DB7  7F 04                     jg       0xdbd
00000DB9  F7 D9                     neg      cx
00000DBB  03 CA                     add      cx, dx
00000DBD  83 F9 28                  cmp      cx, 0x28
00000DC0  76 03                     jbe      0xdc5
00000DC2  B9 28 00                  mov      cx, 0x28
00000DC5  26 C6 07 00               mov      byte ptr es:[bx], 0
00000DC9  8B C3                     mov      ax, bx
00000DCB  2B 46 06                  sub      ax, word ptr [bp + 6]
00000DCE  2B C8                     sub      cx, ax
00000DD0  76 08                     jbe      0xdda
00000DD2  26 C7 07 30 00            mov      word ptr es:[bx], 0x30
00000DD7  43                        inc      bx
00000DD8  E2 F8                     loop     0xdd2
00000DDA  FC                        cld      
00000DDB  C4 7E 10                  les      di, ptr [bp + 0x10]
00000DDE  8B 5E 04                  mov      bx, word ptr [bp + 4]
00000DE1  8B 4E FE                  mov      cx, word ptr [bp - 2]
00000DE4  26 09 09                  or       word ptr es:[bx + di], cx
00000DE7  07                        pop      es
00000DE8  8B C2                     mov      ax, dx
00000DEA  EB 00                     jmp      0xdec
00000DEC  5F                        pop      di
00000DED  5E                        pop      si
00000DEE  8B E5                     mov      sp, bp
00000DF0  5D                        pop      bp
00000DF1  C2 10 00                  ret      0x10
00000DF4  55                        push     bp
00000DF5  8B EC                     mov      bp, sp
00000DF7  FF 76 06                  push     word ptr [bp + 6]
00000DFA  E8 04 00                  call     0xe01
00000DFD  EB 00                     jmp      0xdff
00000DFF  5D                        pop      bp
00000E00  CB                        retf     
00000E01  55                        push     bp
00000E02  8B EC                     mov      bp, sp
00000E04  56                        push     si
00000E05  8B 46 04                  mov      ax, word ptr [bp + 4]
00000E08  3D BC EC                  cmp      ax, 0xecbc
00000E0B  7D 06                     jge      0xe13
00000E0D  9B                        wait     
00000E0E  D9 EE                     fldz     
00000E10  E9 B2 00                  jmp      0xec5
00000E13  3D 44 13                  cmp      ax, 0x1344
00000E16  7E 08                     jle      0xe20
00000E18  9B                        wait     
00000E19  D9 06 D0 1C               fld      dword ptr [0x1cd0]
00000E1D  E9 A5 00                  jmp      0xec5
00000E20  0B C0                     or       ax, ax
00000E22  75 06                     jne      0xe2a
00000E24  9B                        wait     
00000E25  D9 E8                     fld1     
00000E27  E9 9B 00                  jmp      0xec5
00000E2A  0B C0                     or       ax, ax
00000E2C  7D 02                     jge      0xe30
00000E2E  F7 D8                     neg      ax
00000E30  BE 07 00                  mov      si, 7
00000E33  23 F0                     and      si, ax
00000E35  D1 E6                     shl      si, 1
00000E37  D1 E6                     shl      si, 1
00000E39  9B                        wait     
00000E3A  D9 84 54 1C               fld      dword ptr [si + 0x1c54]
00000E3E  D1 E8                     shr      ax, 1
00000E40  D1 E8                     shr      ax, 1
00000E42  D1 E8                     shr      ax, 1
00000E44  D1 E8                     shr      ax, 1
00000E46  73 05                     jae      0xe4d
00000E48  9B                        wait     
00000E49  D8 0E 74 1C               fmul     dword ptr [0x1c74]
00000E4D  75 02                     jne      0xe51
00000E4F  EB 69                     jmp      0xeba
00000E51  D1 E8                     shr      ax, 1
00000E53  73 05                     jae      0xe5a
00000E55  9B                        wait     
00000E56  DC 0E 78 1C               fmul     qword ptr [0x1c78]
00000E5A  D1 E8                     shr      ax, 1
00000E5C  73 08                     jae      0xe66
00000E5E  9B                        wait     
00000E5F  DB 2E 80 1C               fld      xword ptr [0x1c80]
00000E63  9B                        wait     
00000E64  DE C9                     fmulp    st(1)
00000E66  D1 E8                     shr      ax, 1
00000E68  73 08                     jae      0xe72
00000E6A  9B                        wait     
00000E6B  DB 2E 8A 1C               fld      xword ptr [0x1c8a]
00000E6F  9B                        wait     
00000E70  DE C9                     fmulp    st(1)
00000E72  D1 E8                     shr      ax, 1
00000E74  73 08                     jae      0xe7e
00000E76  9B                        wait     
00000E77  DB 2E 94 1C               fld      xword ptr [0x1c94]
00000E7B  9B                        wait     
00000E7C  DE C9                     fmulp    st(1)
00000E7E  D1 E8                     shr      ax, 1
00000E80  73 08                     jae      0xe8a
00000E82  9B                        wait     
00000E83  DB 2E 9E 1C               fld      xword ptr [0x1c9e]
00000E87  9B                        wait     
00000E88  DE C9                     fmulp    st(1)
00000E8A  D1 E8                     shr      ax, 1
00000E8C  73 08                     jae      0xe96
00000E8E  9B                        wait     
00000E8F  DB 2E A8 1C               fld      xword ptr [0x1ca8]
00000E93  9B                        wait     
00000E94  DE C9                     fmulp    st(1)
00000E96  D1 E8                     shr      ax, 1
00000E98  73 08                     jae      0xea2
00000E9A  9B                        wait     
00000E9B  DB 2E B2 1C               fld      xword ptr [0x1cb2]
00000E9F  9B                        wait     
00000EA0  DE C9                     fmulp    st(1)
00000EA2  D1 E8                     shr      ax, 1
00000EA4  73 08                     jae      0xeae
00000EA6  9B                        wait     
00000EA7  DB 2E BC 1C               fld      xword ptr [0x1cbc]
00000EAB  9B                        wait     
00000EAC  DE C9                     fmulp    st(1)
00000EAE  D1 E8                     shr      ax, 1
00000EB0  73 08                     jae      0xeba
00000EB2  9B                        wait     
00000EB3  DB 2E C6 1C               fld      xword ptr [0x1cc6]
00000EB7  9B                        wait     
00000EB8  DE C9                     fmulp    st(1)
00000EBA  F6 46 05 80               test     byte ptr [bp + 5], 0x80
00000EBE  74 05                     je       0xec5
00000EC0  9B                        wait     
00000EC1  D8 3E 54 1C               fdivr    dword ptr [0x1c54]
00000EC5  EB 00                     jmp      0xec7
00000EC7  5E                        pop      si
00000EC8  5D                        pop      bp
00000EC9  C2 02 00                  ret      2
00000ECC  55                        push     bp
00000ECD  8B EC                     mov      bp, sp
00000ECF  83 EC 08                  sub      sp, 8
00000ED2  8C 56 FE                  mov      word ptr [bp - 2], ss
00000ED5  89 5E FC                  mov      word ptr [bp - 4], bx
00000ED8  A1 B0 58                  mov      ax, word ptr [0x58b0]
00000EDB  0B 06 B2 58               or       ax, word ptr [0x58b2]
00000EDF  74 67                     je       0xf48
00000EE1  33 C0                     xor      ax, ax
00000EE3  50                        push     ax
00000EE4  50                        push     ax
00000EE5  B8 08 00                  mov      ax, 8
00000EE8  50                        push     ax
00000EE9  FF 1E B0 58               lcall    [0x58b0]
00000EED  83 C4 06                  add      sp, 6
00000EF0  89 56 FA                  mov      word ptr [bp - 6], dx
00000EF3  89 46 F8                  mov      word ptr [bp - 8], ax
00000EF6  52                        push     dx
00000EF7  50                        push     ax
00000EF8  B8 08 00                  mov      ax, 8
00000EFB  50                        push     ax
00000EFC  FF 1E B0 58               lcall    [0x58b0]
00000F00  83 C4 06                  add      sp, 6
00000F03  83 7E FA 00               cmp      word ptr [bp - 6], 0
00000F07  75 06                     jne      0xf0f
00000F09  83 7E F8 01               cmp      word ptr [bp - 8], 1
00000F0D  74 35                     je       0xf44
00000F0F  8B 46 F8                  mov      ax, word ptr [bp - 8]
00000F12  0B 46 FA                  or       ax, word ptr [bp - 6]
00000F15  75 02                     jne      0xf19
00000F17  EB 2F                     jmp      0xf48
00000F19  33 C0                     xor      ax, ax
00000F1B  50                        push     ax
00000F1C  50                        push     ax
00000F1D  B8 08 00                  mov      ax, 8
00000F20  50                        push     ax
00000F21  FF 1E B0 58               lcall    [0x58b0]
00000F25  83 C4 06                  add      sp, 6
00000F28  C4 5E FC                  les      bx, ptr [bp - 4]
00000F2B  B8 06 00                  mov      ax, 6
00000F2E  26 F7 2F                  imul     word ptr es:[bx]
00000F31  8B D8                     mov      bx, ax
00000F33  FF B7 CE 1C               push     word ptr [bx + 0x1cce]
00000F37  B8 08 00                  mov      ax, 8
00000F3A  50                        push     ax
00000F3B  FF 5E F8                  lcall    [bp - 8]
00000F3E  59                        pop      cx
00000F3F  59                        pop      cx
00000F40  8B E5                     mov      sp, bp
00000F42  5D                        pop      bp
00000F43  C3                        ret      
00000F44  8B E5                     mov      sp, bp
00000F46  5D                        pop      bp
00000F47  C3                        ret      
00000F48  C4 5E FC                  les      bx, ptr [bp - 4]
00000F4B  B8 06 00                  mov      ax, 6
00000F4E  26 F7 2F                  imul     word ptr es:[bx]
00000F51  8B D8                     mov      bx, ax
00000F53  FF B7 D2 1C               push     word ptr [bx + 0x1cd2]
00000F57  FF B7 D0 1C               push     word ptr [bx + 0x1cd0]
00000F5B  1E                        push     ds
00000F5C  B8 53 1D                  mov      ax, 0x1d53
00000F5F  50                        push     ax
00000F60  1E                        push     ds
00000F61  B8 B4 1D                  mov      ax, 0x1db4
00000F64  50                        push     ax
00000F65  90                        nop      
00000F66  0E                        push     cs
00000F67  E8 72 1B                  call     0x2adc
00000F6A  83 C4 0C                  add      sp, 0xc
00000F6D  90                        nop      
00000F6E  0E                        push     cs
00000F6F  E8 58 3D                  call     0x4cca
00000F72  8B E5                     mov      sp, bp
00000F74  5D                        pop      bp
00000F75  C3                        ret      
00000F76  55                        push     bp
00000F77  8B EC                     mov      bp, sp
00000F79  83 EC 0A                  sub      sp, 0xa
00000F7C  9B                        wait     
00000F7D  D9 7E FE                  fnstcw   word ptr [bp - 2]
00000F80  90                        nop      
00000F81  9B                        wait     
00000F82  8A 46 FF                  mov      al, byte ptr [bp - 1]
00000F85  80 4E FF 0C               or       byte ptr [bp - 1], 0xc
00000F89  9B                        wait     
00000F8A  D9 6E FE                  fldcw    word ptr [bp - 2]
00000F8D  9B                        wait     
00000F8E  DF 7E F6                  fistp    qword ptr [bp - 0xa]
00000F91  88 46 FF                  mov      byte ptr [bp - 1], al
00000F94  9B                        wait     
00000F95  D9 6E FE                  fldcw    word ptr [bp - 2]
00000F98  8B 46 F6                  mov      ax, word ptr [bp - 0xa]
00000F9B  8B 56 F8                  mov      dx, word ptr [bp - 8]
00000F9E  8B E5                     mov      sp, bp
00000FA0  5D                        pop      bp
00000FA1  CB                        retf     
00000FA2  55                        push     bp
00000FA3  8B EC                     mov      bp, sp
00000FA5  56                        push     si
00000FA6  57                        push     di
00000FA7  8A 66 06                  mov      ah, byte ptr [bp + 6]
00000FAA  8A 46 10                  mov      al, byte ptr [bp + 0x10]
00000FAD  C4 5E 12                  les      bx, ptr [bp + 0x12]
00000FB0  8B 4E 0C                  mov      cx, word ptr [bp + 0xc]
00000FB3  D1 E9                     shr      cx, 1
00000FB5  D1 E9                     shr      cx, 1
00000FB7  80 E1 C0                  and      cl, 0xc0
00000FBA  02 4E 0E                  add      cl, byte ptr [bp + 0xe]
00000FBD  8A 6E 0C                  mov      ch, byte ptr [bp + 0xc]
00000FC0  8A 76 0A                  mov      dh, byte ptr [bp + 0xa]
00000FC3  8A 56 08                  mov      dl, byte ptr [bp + 8]
00000FC6  CD 13                     int      0x13
00000FC8  80 7E 06 08               cmp      byte ptr [bp + 6], 8
00000FCC  75 0A                     jne      0xfd8
00000FCE  C4 5E 12                  les      bx, ptr [bp + 0x12]
00000FD1  26 89 0F                  mov      word ptr es:[bx], cx
00000FD4  26 89 57 02               mov      word ptr es:[bx + 2], dx
00000FD8  8A C4                     mov      al, ah
00000FDA  B4 00                     mov      ah, 0
00000FDC  5F                        pop      di
00000FDD  5E                        pop      si
00000FDE  5D                        pop      bp
00000FDF  CB                        retf     
00000FE0  55                        push     bp
00000FE1  8B EC                     mov      bp, sp
00000FE3  56                        push     si
00000FE4  57                        push     di
00000FE5  32 C0                     xor      al, al
00000FE7  8A 66 06                  mov      ah, byte ptr [bp + 6]
00000FEA  CD 16                     int      0x16
00000FEC  74 0F                     je       0xffd
00000FEE  F6 46 06 01               test     byte ptr [bp + 6], 1
00000FF2  74 11                     je       0x1005
00000FF4  0B C0                     or       ax, ax
00000FF6  75 0D                     jne      0x1005
00000FF8  B8 FF FF                  mov      ax, 0xffff
00000FFB  EB 08                     jmp      0x1005
00000FFD  F6 46 06 01               test     byte ptr [bp + 6], 1
00001001  74 02                     je       0x1005
00001003  33 C0                     xor      ax, ax
00001005  5F                        pop      di
00001006  5E                        pop      si
00001007  5D                        pop      bp
00001008  CB                        retf     
00001009  55                        push     bp
0000100A  8B EC                     mov      bp, sp
0000100C  56                        push     si
0000100D  57                        push     di
0000100E  A0 78 1D                  mov      al, byte ptr [0x1d78]
00001011  B4 00                     mov      ah, 0
00001013  8B 56 04                  mov      dx, word ptr [bp + 4]
00001016  4A                        dec      dx
00001017  F7 EA                     imul     dx
00001019  03 46 06                  add      ax, word ptr [bp + 6]
0000101C  48                        dec      ax
0000101D  03 C0                     add      ax, ax
0000101F  03 06 7B 1D               add      ax, word ptr [0x1d7b]
00001023  8B 16 7D 1D               mov      dx, word ptr [0x1d7d]
00001027  5F                        pop      di
00001028  5E                        pop      si
00001029  5D                        pop      bp
0000102A  C2 04 00                  ret      4
0000102D  55                        push     bp
0000102E  8B EC                     mov      bp, sp
00001030  83 EC 02                  sub      sp, 2
00001033  56                        push     si
00001034  57                        push     di
00001035  A0 7A 1D                  mov      al, byte ptr [0x1d7a]
00001038  B4 00                     mov      ah, 0
0000103A  89 46 FE                  mov      word ptr [bp - 2], ax
0000103D  1E                        push     ds
0000103E  8B 4E 04                  mov      cx, word ptr [bp + 4]
00001041  E3 5A                     jcxz     0x109d
00001043  C4 7E 0A                  les      di, ptr [bp + 0xa]
00001046  C5 76 06                  lds      si, ptr [bp + 6]
00001049  FC                        cld      
0000104A  3B F7                     cmp      si, di
0000104C  73 0A                     jae      0x1058
0000104E  8B C1                     mov      ax, cx
00001050  48                        dec      ax
00001051  D1 E0                     shl      ax, 1
00001053  03 F0                     add      si, ax
00001055  03 F8                     add      di, ax
00001057  FD                        std      
00001058  83 7E FE 00               cmp      word ptr [bp - 2], 0
0000105C  75 04                     jne      0x1062
0000105E  F3 A5                     rep movsw word ptr es:[di], word ptr [si]
00001060  EB 3B                     jmp      0x109d
00001062  BA DA 03                  mov      dx, 0x3da
00001065  8C C0                     mov      ax, es
00001067  8C DB                     mov      bx, ds
00001069  3B C3                     cmp      ax, bx
0000106B  74 11                     je       0x107e
0000106D  FA                        cli      
0000106E  EC                        in       al, dx
0000106F  D0 C8                     ror      al, 1
00001071  72 FB                     jb       0x106e
00001073  EC                        in       al, dx
00001074  D0 C8                     ror      al, 1
00001076  73 FB                     jae      0x1073
00001078  A5                        movsw    word ptr es:[di], word ptr [si]
00001079  FB                        sti      
0000107A  E2 F1                     loop     0x106d
0000107C  EB 1F                     jmp      0x109d
0000107E  FA                        cli      
0000107F  EC                        in       al, dx
00001080  D0 C8                     ror      al, 1
00001082  72 FB                     jb       0x107f
00001084  EC                        in       al, dx
00001085  D0 C8                     ror      al, 1
00001087  73 FB                     jae      0x1084
00001089  AD                        lodsw    ax, word ptr [si]
0000108A  FB                        sti      
0000108B  8B D8                     mov      bx, ax
0000108D  EC                        in       al, dx
0000108E  D0 C8                     ror      al, 1
00001090  72 FB                     jb       0x108d
00001092  EC                        in       al, dx
00001093  D0 C8                     ror      al, 1
00001095  73 FB                     jae      0x1092
00001097  8B C3                     mov      ax, bx
00001099  AB                        stosw    word ptr es:[di], ax
0000109A  FB                        sti      
0000109B  E2 E1                     loop     0x107e
0000109D  FC                        cld      
0000109E  1F                        pop      ds
0000109F  5F                        pop      di
000010A0  5E                        pop      si
000010A1  8B E5                     mov      sp, bp
000010A3  5D                        pop      bp
000010A4  C2 0A 00                  ret      0xa
000010A7  55                        push     bp
000010A8  8B EC                     mov      bp, sp
000010AA  83 EC 08                  sub      sp, 8
000010AD  56                        push     si
000010AE  57                        push     di
000010AF  C6 46 FB 00               mov      byte ptr [bp - 5], 0
000010B3  E8 38 06                  call     0x16ee
000010B6  B4 00                     mov      ah, 0
000010B8  89 46 FE                  mov      word ptr [bp - 2], ax
000010BB  E8 30 06                  call     0x16ee
000010BE  B1 08                     mov      cl, 8
000010C0  D3 E8                     shr      ax, cl
000010C2  B4 00                     mov      ah, 0
000010C4  89 46 FC                  mov      word ptr [bp - 4], ax
000010C7  E9 DA 00                  jmp      0x11a4
000010CA  C4 5E 0A                  les      bx, ptr [bp + 0xa]
000010CD  FF 46 0A                  inc      word ptr [bp + 0xa]
000010D0  26 8A 07                  mov      al, byte ptr es:[bx]
000010D3  88 46 FB                  mov      byte ptr [bp - 5], al
000010D6  B4 00                     mov      ah, 0
000010D8  2D 07 00                  sub      ax, 7
000010DB  8B D8                     mov      bx, ax
000010DD  83 FB 06                  cmp      bx, 6
000010E0  77 2E                     ja       0x1110
000010E2  03 DB                     add      bx, bx
000010E4  2E FF A7 CB 11            jmp      word ptr cs:[bx + 0x11cb]
000010E9  B4 0E                     mov      ah, 0xe
000010EB  B0 07                     mov      al, 7
000010ED  E8 79 06                  call     0x1769
000010F0  EB 74                     jmp      0x1166
000010F2  A0 70 1D                  mov      al, byte ptr [0x1d70]
000010F5  B4 00                     mov      ah, 0
000010F7  3B 46 FE                  cmp      ax, word ptr [bp - 2]
000010FA  7D 6A                     jge      0x1166
000010FC  FF 4E FE                  dec      word ptr [bp - 2]
000010FF  EB 65                     jmp      0x1166
00001101  A0 70 1D                  mov      al, byte ptr [0x1d70]
00001104  B4 00                     mov      ah, 0
00001106  89 46 FE                  mov      word ptr [bp - 2], ax
00001109  EB 5B                     jmp      0x1166
0000110B  FF 46 FC                  inc      word ptr [bp - 4]
0000110E  EB 56                     jmp      0x1166
00001110  80 3E 79 1D 00            cmp      byte ptr [0x1d79], 0
00001115  75 2E                     jne      0x1145
00001117  83 3E 80 1D 00            cmp      word ptr [0x1d80], 0
0000111C  74 27                     je       0x1145
0000111E  8A 26 74 1D               mov      ah, byte ptr [0x1d74]
00001122  8A 46 FB                  mov      al, byte ptr [bp - 5]
00001125  89 46 F8                  mov      word ptr [bp - 8], ax
00001128  8B 46 FE                  mov      ax, word ptr [bp - 2]
0000112B  40                        inc      ax
0000112C  50                        push     ax
0000112D  8B 46 FC                  mov      ax, word ptr [bp - 4]
00001130  40                        inc      ax
00001131  50                        push     ax
00001132  E8 D4 FE                  call     0x1009
00001135  52                        push     dx
00001136  50                        push     ax
00001137  16                        push     ss
00001138  8D 46 F8                  lea      ax, [bp - 8]
0000113B  50                        push     ax
0000113C  B8 01 00                  mov      ax, 1
0000113F  50                        push     ax
00001140  E8 EA FE                  call     0x102d
00001143  EB 1E                     jmp      0x1163
00001145  8A 56 FE                  mov      dl, byte ptr [bp - 2]
00001148  8A 76 FC                  mov      dh, byte ptr [bp - 4]
0000114B  B4 02                     mov      ah, 2
0000114D  B7 00                     mov      bh, 0
0000114F  E8 17 06                  call     0x1769
00001152  8A 1E 74 1D               mov      bl, byte ptr [0x1d74]
00001156  8A 46 FB                  mov      al, byte ptr [bp - 5]
00001159  B4 09                     mov      ah, 9
0000115B  B7 00                     mov      bh, 0
0000115D  B9 01 00                  mov      cx, 1
00001160  E8 06 06                  call     0x1769
00001163  FF 46 FE                  inc      word ptr [bp - 2]
00001166  A0 72 1D                  mov      al, byte ptr [0x1d72]
00001169  B4 00                     mov      ah, 0
0000116B  3B 46 FE                  cmp      ax, word ptr [bp - 2]
0000116E  7D 0E                     jge      0x117e
00001170  A0 70 1D                  mov      al, byte ptr [0x1d70]
00001173  B4 00                     mov      ah, 0
00001175  89 46 FE                  mov      word ptr [bp - 2], ax
00001178  A1 6E 1D                  mov      ax, word ptr [0x1d6e]
0000117B  01 46 FC                  add      word ptr [bp - 4], ax
0000117E  A0 73 1D                  mov      al, byte ptr [0x1d73]
00001181  B4 00                     mov      ah, 0
00001183  3B 46 FC                  cmp      ax, word ptr [bp - 4]
00001186  7D 1C                     jge      0x11a4
00001188  B0 06                     mov      al, 6
0000118A  50                        push     ax
0000118B  A0 70 1D                  mov      al, byte ptr [0x1d70]
0000118E  50                        push     ax
0000118F  A0 71 1D                  mov      al, byte ptr [0x1d71]
00001192  50                        push     ax
00001193  A0 72 1D                  mov      al, byte ptr [0x1d72]
00001196  50                        push     ax
00001197  A0 73 1D                  mov      al, byte ptr [0x1d73]
0000119A  50                        push     ax
0000119B  B0 01                     mov      al, 1
0000119D  50                        push     ax
0000119E  E8 E0 03                  call     0x1581
000011A1  FF 4E FC                  dec      word ptr [bp - 4]
000011A4  8B 46 08                  mov      ax, word ptr [bp + 8]
000011A7  FF 4E 08                  dec      word ptr [bp + 8]
000011AA  0B C0                     or       ax, ax
000011AC  74 03                     je       0x11b1
000011AE  E9 19 FF                  jmp      0x10ca
000011B1  8A 56 FE                  mov      dl, byte ptr [bp - 2]
000011B4  8A 76 FC                  mov      dh, byte ptr [bp - 4]
000011B7  B4 02                     mov      ah, 2
000011B9  B7 00                     mov      bh, 0
000011BB  E8 AB 05                  call     0x1769
000011BE  8A 46 FB                  mov      al, byte ptr [bp - 5]
000011C1  B4 00                     mov      ah, 0
000011C3  5F                        pop      di
000011C4  5E                        pop      si
000011C5  8B E5                     mov      sp, bp
000011C7  5D                        pop      bp
000011C8  C2 0A 00                  ret      0xa
000011CB  E9 10 F2                  jmp      0x3de
000011CE  10 10                     adc      byte ptr [bx + si], dl
000011D0  11 0B                     adc      word ptr [bp + di], cx
000011D2  11 10                     adc      word ptr [bx + si], dx
000011D4  11 10                     adc      word ptr [bx + si], dx
000011D6  11 01                     adc      word ptr [bx + di], ax
000011D8  11 55 8B                  adc      word ptr [di - 0x75], dx
000011DB  EC                        in       al, dx
000011DC  56                        push     si
000011DD  57                        push     di
000011DE  B8 A7 10                  mov      ax, 0x10a7
000011E1  50                        push     ax
000011E2  33 C0                     xor      ax, ax
000011E4  50                        push     ax
000011E5  50                        push     ax
000011E6  FF 76 08                  push     word ptr [bp + 8]
000011E9  FF 76 06                  push     word ptr [bp + 6]
000011EC  8D 46 0A                  lea      ax, [bp + 0xa]
000011EF  50                        push     ax
000011F0  E8 A8 0E                  call     0x209b
000011F3  5F                        pop      di
000011F4  5E                        pop      si
000011F5  5D                        pop      bp
000011F6  CB                        retf     
000011F7  55                        push     bp
000011F8  8B EC                     mov      bp, sp
000011FA  83 EC 04                  sub      sp, 4
000011FD  56                        push     si
000011FE  57                        push     di
000011FF  FF 76 06                  push     word ptr [bp + 6]
00001202  FF 76 08                  push     word ptr [bp + 8]
00001205  FF 76 0A                  push     word ptr [bp + 0xa]
00001208  FF 76 0C                  push     word ptr [bp + 0xc]
0000120B  E8 F4 02                  call     0x1502
0000120E  0B C0                     or       ax, ax
00001210  75 04                     jne      0x1216
00001212  33 C0                     xor      ax, ax
00001214  EB 3F                     jmp      0x1255
00001216  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
00001219  2B 46 06                  sub      ax, word ptr [bp + 6]
0000121C  40                        inc      ax
0000121D  89 46 FC                  mov      word ptr [bp - 4], ax
00001220  8B 46 08                  mov      ax, word ptr [bp + 8]
00001223  89 46 FE                  mov      word ptr [bp - 2], ax
00001226  EB 22                     jmp      0x124a
00001228  FF 76 10                  push     word ptr [bp + 0x10]
0000122B  FF 76 0E                  push     word ptr [bp + 0xe]
0000122E  FF 76 06                  push     word ptr [bp + 6]
00001231  FF 76 FE                  push     word ptr [bp - 2]
00001234  E8 D2 FD                  call     0x1009
00001237  52                        push     dx
00001238  50                        push     ax
00001239  FF 76 FC                  push     word ptr [bp - 4]
0000123C  E8 85 02                  call     0x14c4
0000123F  8B 46 FC                  mov      ax, word ptr [bp - 4]
00001242  03 C0                     add      ax, ax
00001244  01 46 0E                  add      word ptr [bp + 0xe], ax
00001247  FF 46 FE                  inc      word ptr [bp - 2]
0000124A  8B 46 FE                  mov      ax, word ptr [bp - 2]
0000124D  3B 46 0C                  cmp      ax, word ptr [bp + 0xc]
00001250  7E D6                     jle      0x1228
00001252  B8 01 00                  mov      ax, 1
00001255  5F                        pop      di
00001256  5E                        pop      si
00001257  8B E5                     mov      sp, bp
00001259  5D                        pop      bp
0000125A  CB                        retf     
0000125B  55                        push     bp
0000125C  8B EC                     mov      bp, sp
0000125E  83 EC 04                  sub      sp, 4
00001261  56                        push     si
00001262  57                        push     di
00001263  FF 76 06                  push     word ptr [bp + 6]
00001266  FF 76 08                  push     word ptr [bp + 8]
00001269  FF 76 0A                  push     word ptr [bp + 0xa]
0000126C  FF 76 0C                  push     word ptr [bp + 0xc]
0000126F  E8 90 02                  call     0x1502
00001272  0B C0                     or       ax, ax
00001274  75 04                     jne      0x127a
00001276  33 C0                     xor      ax, ax
00001278  EB 3F                     jmp      0x12b9
0000127A  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
0000127D  2B 46 06                  sub      ax, word ptr [bp + 6]
00001280  40                        inc      ax
00001281  89 46 FC                  mov      word ptr [bp - 4], ax
00001284  8B 46 08                  mov      ax, word ptr [bp + 8]
00001287  89 46 FE                  mov      word ptr [bp - 2], ax
0000128A  EB 22                     jmp      0x12ae
0000128C  FF 76 06                  push     word ptr [bp + 6]
0000128F  FF 76 FE                  push     word ptr [bp - 2]
00001292  E8 74 FD                  call     0x1009
00001295  52                        push     dx
00001296  50                        push     ax
00001297  FF 76 10                  push     word ptr [bp + 0x10]
0000129A  FF 76 0E                  push     word ptr [bp + 0xe]
0000129D  FF 76 FC                  push     word ptr [bp - 4]
000012A0  E8 21 02                  call     0x14c4
000012A3  8B 46 FC                  mov      ax, word ptr [bp - 4]
000012A6  03 C0                     add      ax, ax
000012A8  01 46 0E                  add      word ptr [bp + 0xe], ax
000012AB  FF 46 FE                  inc      word ptr [bp - 2]
000012AE  8B 46 FE                  mov      ax, word ptr [bp - 2]
000012B1  3B 46 0C                  cmp      ax, word ptr [bp + 0xc]
000012B4  7E D6                     jle      0x128c
000012B6  B8 01 00                  mov      ax, 1
000012B9  5F                        pop      di
000012BA  5E                        pop      si
000012BB  8B E5                     mov      sp, bp
000012BD  5D                        pop      bp
000012BE  CB                        retf     
000012BF  55                        push     bp
000012C0  8B EC                     mov      bp, sp
000012C2  83 EC 06                  sub      sp, 6
000012C5  56                        push     si
000012C6  57                        push     di
000012C7  FF 76 06                  push     word ptr [bp + 6]
000012CA  FF 76 08                  push     word ptr [bp + 8]
000012CD  FF 76 0A                  push     word ptr [bp + 0xa]
000012D0  FF 76 0C                  push     word ptr [bp + 0xc]
000012D3  E8 2C 02                  call     0x1502
000012D6  0B C0                     or       ax, ax
000012D8  74 21                     je       0x12fb
000012DA  FF 76 0E                  push     word ptr [bp + 0xe]
000012DD  FF 76 10                  push     word ptr [bp + 0x10]
000012E0  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
000012E3  2B 46 06                  sub      ax, word ptr [bp + 6]
000012E6  03 46 0E                  add      ax, word ptr [bp + 0xe]
000012E9  50                        push     ax
000012EA  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
000012ED  2B 46 08                  sub      ax, word ptr [bp + 8]
000012F0  03 46 10                  add      ax, word ptr [bp + 0x10]
000012F3  50                        push     ax
000012F4  E8 0B 02                  call     0x1502
000012F7  0B C0                     or       ax, ax
000012F9  75 04                     jne      0x12ff
000012FB  33 C0                     xor      ax, ax
000012FD  EB 62                     jmp      0x1361
000012FF  8B 56 08                  mov      dx, word ptr [bp + 8]
00001302  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
00001305  89 46 FE                  mov      word ptr [bp - 2], ax
00001308  C7 46 FC 01 00            mov      word ptr [bp - 4], 1
0000130D  8B 46 08                  mov      ax, word ptr [bp + 8]
00001310  3B 46 10                  cmp      ax, word ptr [bp + 0x10]
00001313  7D 0B                     jge      0x1320
00001315  8B 56 0C                  mov      dx, word ptr [bp + 0xc]
00001318  89 46 FE                  mov      word ptr [bp - 2], ax
0000131B  C7 46 FC FF FF            mov      word ptr [bp - 4], 0xffff
00001320  89 56 FA                  mov      word ptr [bp - 6], dx
00001323  EB 2E                     jmp      0x1353
00001325  FF 76 0E                  push     word ptr [bp + 0xe]
00001328  8B 46 FA                  mov      ax, word ptr [bp - 6]
0000132B  2B 46 08                  sub      ax, word ptr [bp + 8]
0000132E  03 46 10                  add      ax, word ptr [bp + 0x10]
00001331  50                        push     ax
00001332  E8 D4 FC                  call     0x1009
00001335  52                        push     dx
00001336  50                        push     ax
00001337  FF 76 06                  push     word ptr [bp + 6]
0000133A  FF 76 FA                  push     word ptr [bp - 6]
0000133D  E8 C9 FC                  call     0x1009
00001340  52                        push     dx
00001341  50                        push     ax
00001342  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
00001345  2B 46 06                  sub      ax, word ptr [bp + 6]
00001348  40                        inc      ax
00001349  50                        push     ax
0000134A  E8 77 01                  call     0x14c4
0000134D  8B 46 FC                  mov      ax, word ptr [bp - 4]
00001350  01 46 FA                  add      word ptr [bp - 6], ax
00001353  8B 46 FE                  mov      ax, word ptr [bp - 2]
00001356  03 46 FC                  add      ax, word ptr [bp - 4]
00001359  3B 46 FA                  cmp      ax, word ptr [bp - 6]
0000135C  75 C7                     jne      0x1325
0000135E  B8 01 00                  mov      ax, 1
00001361  5F                        pop      di
00001362  5E                        pop      si
00001363  8B E5                     mov      sp, bp
00001365  5D                        pop      bp
00001366  CB                        retf     
00001367  55                        push     bp
00001368  8B EC                     mov      bp, sp
0000136A  56                        push     si
0000136B  57                        push     di
0000136C  16                        push     ss
0000136D  8D 46 06                  lea      ax, [bp + 6]
00001370  50                        push     ax
00001371  B8 01 00                  mov      ax, 1
00001374  50                        push     ax
00001375  33 C0                     xor      ax, ax
00001377  50                        push     ax
00001378  50                        push     ax
00001379  E8 2B FD                  call     0x10a7
0000137C  5F                        pop      di
0000137D  5E                        pop      si
0000137E  5D                        pop      bp
0000137F  CB                        retf     
00001380  55                        push     bp
00001381  8B EC                     mov      bp, sp
00001383  83 EC 04                  sub      sp, 4
00001386  56                        push     si
00001387  57                        push     di
00001388  8B 46 04                  mov      ax, word ptr [bp + 4]
0000138B  D1 E8                     shr      ax, 1
0000138D  8B C8                     mov      cx, ax
0000138F  A0 78 1D                  mov      al, byte ptr [0x1d78]
00001392  B4 00                     mov      ah, 0
00001394  89 46 FC                  mov      word ptr [bp - 4], ax
00001397  50                        push     ax
00001398  8B C1                     mov      ax, cx
0000139A  33 D2                     xor      dx, dx
0000139C  5B                        pop      bx
0000139D  F7 F3                     div      bx
0000139F  8A D8                     mov      bl, al
000013A1  B4 00                     mov      ah, 0
000013A3  F7 6E FC                  imul     word ptr [bp - 4]
000013A6  8A D1                     mov      dl, cl
000013A8  2A D0                     sub      dl, al
000013AA  88 56 FF                  mov      byte ptr [bp - 1], dl
000013AD  8A E3                     mov      ah, bl
000013AF  8A 46 FF                  mov      al, byte ptr [bp - 1]
000013B2  5F                        pop      di
000013B3  5E                        pop      si
000013B4  8B E5                     mov      sp, bp
000013B6  5D                        pop      bp
000013B7  C2 04 00                  ret      4
000013BA  55                        push     bp
000013BB  8B EC                     mov      bp, sp
000013BD  56                        push     si
000013BE  57                        push     di
000013BF  C4 5E 08                  les      bx, ptr [bp + 8]
000013C2  26 8B 17                  mov      dx, word ptr es:[bx]
000013C5  C4 5E 04                  les      bx, ptr [bp + 4]
000013C8  26 3B 17                  cmp      dx, word ptr es:[bx]
000013CB  74 0D                     je       0x13da
000013CD  B7 00                     mov      bh, 0
000013CF  B4 02                     mov      ah, 2
000013D1  E8 95 03                  call     0x1769
000013D4  C4 5E 04                  les      bx, ptr [bp + 4]
000013D7  26 89 17                  mov      word ptr es:[bx], dx
000013DA  FE C2                     inc      dl
000013DC  3A 16 78 1D               cmp      dl, byte ptr [0x1d78]
000013E0  72 04                     jb       0x13e6
000013E2  FE C6                     inc      dh
000013E4  B2 00                     mov      dl, 0
000013E6  C4 5E 08                  les      bx, ptr [bp + 8]
000013E9  26 89 17                  mov      word ptr es:[bx], dx
000013EC  5F                        pop      di
000013ED  5E                        pop      si
000013EE  5D                        pop      bp
000013EF  C2 08 00                  ret      8
000013F2  55                        push     bp
000013F3  8B EC                     mov      bp, sp
000013F5  83 EC 0E                  sub      sp, 0xe
000013F8  56                        push     si
000013F9  57                        push     di
000013FA  E8 F1 02                  call     0x16ee
000013FD  89 46 F6                  mov      word ptr [bp - 0xa], ax
00001400  89 46 F8                  mov      word ptr [bp - 8], ax
00001403  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
00001406  3B 06 7D 1D               cmp      ax, word ptr [0x1d7d]
0000140A  75 05                     jne      0x1411
0000140C  B8 01 00                  mov      ax, 1
0000140F  EB 02                     jmp      0x1413
00001411  33 C0                     xor      ax, ax
00001413  89 46 F4                  mov      word ptr [bp - 0xc], ax
00001416  0B C0                     or       ax, ax
00001418  74 0C                     je       0x1426
0000141A  FF 76 0C                  push     word ptr [bp + 0xc]
0000141D  FF 76 0A                  push     word ptr [bp + 0xa]
00001420  E8 5D FF                  call     0x1380
00001423  89 46 FC                  mov      word ptr [bp - 4], ax
00001426  8B 46 08                  mov      ax, word ptr [bp + 8]
00001429  3B 06 7D 1D               cmp      ax, word ptr [0x1d7d]
0000142D  75 05                     jne      0x1434
0000142F  B8 01 00                  mov      ax, 1
00001432  EB 02                     jmp      0x1436
00001434  33 C0                     xor      ax, ax
00001436  89 46 F2                  mov      word ptr [bp - 0xe], ax
00001439  0B C0                     or       ax, ax
0000143B  74 6B                     je       0x14a8
0000143D  FF 76 08                  push     word ptr [bp + 8]
00001440  FF 76 06                  push     word ptr [bp + 6]
00001443  E8 3A FF                  call     0x1380
00001446  89 46 FA                  mov      word ptr [bp - 6], ax
00001449  EB 5D                     jmp      0x14a8
0000144B  83 7E F2 00               cmp      word ptr [bp - 0xe], 0
0000144F  74 19                     je       0x146a
00001451  16                        push     ss
00001452  8D 46 FA                  lea      ax, [bp - 6]
00001455  50                        push     ax
00001456  16                        push     ss
00001457  8D 46 F8                  lea      ax, [bp - 8]
0000145A  50                        push     ax
0000145B  E8 5C FF                  call     0x13ba
0000145E  B7 00                     mov      bh, 0
00001460  B4 08                     mov      ah, 8
00001462  E8 04 03                  call     0x1769
00001465  89 46 FE                  mov      word ptr [bp - 2], ax
00001468  EB 0D                     jmp      0x1477
0000146A  C4 5E 06                  les      bx, ptr [bp + 6]
0000146D  26 8B 07                  mov      ax, word ptr es:[bx]
00001470  89 46 FE                  mov      word ptr [bp - 2], ax
00001473  83 46 06 02               add      word ptr [bp + 6], 2
00001477  83 7E F4 00               cmp      word ptr [bp - 0xc], 0
0000147B  74 1E                     je       0x149b
0000147D  16                        push     ss
0000147E  8D 46 FC                  lea      ax, [bp - 4]
00001481  50                        push     ax
00001482  16                        push     ss
00001483  8D 46 F8                  lea      ax, [bp - 8]
00001486  50                        push     ax
00001487  E8 30 FF                  call     0x13ba
0000148A  8B 46 FE                  mov      ax, word ptr [bp - 2]
0000148D  8A DC                     mov      bl, ah
0000148F  B9 01 00                  mov      cx, 1
00001492  B7 00                     mov      bh, 0
00001494  B4 09                     mov      ah, 9
00001496  E8 D0 02                  call     0x1769
00001499  EB 0D                     jmp      0x14a8
0000149B  C4 5E 0A                  les      bx, ptr [bp + 0xa]
0000149E  8B 46 FE                  mov      ax, word ptr [bp - 2]
000014A1  26 89 07                  mov      word ptr es:[bx], ax
000014A4  83 46 0A 02               add      word ptr [bp + 0xa], 2
000014A8  8B 46 04                  mov      ax, word ptr [bp + 4]
000014AB  FF 4E 04                  dec      word ptr [bp + 4]
000014AE  0B C0                     or       ax, ax
000014B0  75 99                     jne      0x144b
000014B2  8B 56 F6                  mov      dx, word ptr [bp - 0xa]
000014B5  B7 00                     mov      bh, 0
000014B7  B4 02                     mov      ah, 2
000014B9  E8 AD 02                  call     0x1769
000014BC  5F                        pop      di
000014BD  5E                        pop      si
000014BE  8B E5                     mov      sp, bp
000014C0  5D                        pop      bp
000014C1  C2 0A 00                  ret      0xa
000014C4  55                        push     bp
000014C5  8B EC                     mov      bp, sp
000014C7  56                        push     si
000014C8  57                        push     di
000014C9  8B 46 04                  mov      ax, word ptr [bp + 4]
000014CC  80 3E 79 1D 00            cmp      byte ptr [0x1d79], 0
000014D1  75 19                     jne      0x14ec
000014D3  83 3E 80 1D 00            cmp      word ptr [0x1d80], 0
000014D8  74 12                     je       0x14ec
000014DA  FF 76 0C                  push     word ptr [bp + 0xc]
000014DD  FF 76 0A                  push     word ptr [bp + 0xa]
000014E0  FF 76 08                  push     word ptr [bp + 8]
000014E3  FF 76 06                  push     word ptr [bp + 6]
000014E6  50                        push     ax
000014E7  E8 43 FB                  call     0x102d
000014EA  EB 10                     jmp      0x14fc
000014EC  FF 76 0C                  push     word ptr [bp + 0xc]
000014EF  FF 76 0A                  push     word ptr [bp + 0xa]
000014F2  FF 76 08                  push     word ptr [bp + 8]
000014F5  FF 76 06                  push     word ptr [bp + 6]
000014F8  50                        push     ax
000014F9  E8 F6 FE                  call     0x13f2
000014FC  5F                        pop      di
000014FD  5E                        pop      si
000014FE  5D                        pop      bp
000014FF  C2 0A 00                  ret      0xa
00001502  55                        push     bp
00001503  8B EC                     mov      bp, sp
00001505  56                        push     si
00001506  57                        push     di
00001507  8B 5E 0A                  mov      bx, word ptr [bp + 0xa]
0000150A  A0 78 1D                  mov      al, byte ptr [0x1d78]
0000150D  B4 00                     mov      ah, 0
0000150F  8B C8                     mov      cx, ax
00001511  A0 77 1D                  mov      al, byte ptr [0x1d77]
00001514  B4 00                     mov      ah, 0
00001516  8B D0                     mov      dx, ax
00001518  3B D9                     cmp      bx, cx
0000151A  77 37                     ja       0x1553
0000151C  39 4E 06                  cmp      word ptr [bp + 6], cx
0000151F  77 32                     ja       0x1553
00001521  3B 5E 06                  cmp      bx, word ptr [bp + 6]
00001524  7F 2D                     jg       0x1553
00001526  39 56 08                  cmp      word ptr [bp + 8], dx
00001529  77 28                     ja       0x1553
0000152B  39 56 04                  cmp      word ptr [bp + 4], dx
0000152E  77 23                     ja       0x1553
00001530  8B 46 08                  mov      ax, word ptr [bp + 8]
00001533  3B 46 04                  cmp      ax, word ptr [bp + 4]
00001536  7F 1B                     jg       0x1553
00001538  0B DB                     or       bx, bx
0000153A  7E 17                     jle      0x1553
0000153C  83 7E 06 00               cmp      word ptr [bp + 6], 0
00001540  7E 11                     jle      0x1553
00001542  83 7E 08 00               cmp      word ptr [bp + 8], 0
00001546  7E 0B                     jle      0x1553
00001548  83 7E 04 00               cmp      word ptr [bp + 4], 0
0000154C  7E 05                     jle      0x1553
0000154E  B8 01 00                  mov      ax, 1
00001551  EB 02                     jmp      0x1555
00001553  33 C0                     xor      ax, ax
00001555  5F                        pop      di
00001556  5E                        pop      si
00001557  5D                        pop      bp
00001558  C2 08 00                  ret      8
0000155B  55                        push     bp
0000155C  8B EC                     mov      bp, sp
0000155E  56                        push     si
0000155F  57                        push     di
00001560  8B 56 06                  mov      dx, word ptr [bp + 6]
00001563  8A 2E 74 1D               mov      ch, byte ptr [0x1d74]
00001567  B1 20                     mov      cl, 0x20
00001569  EB 0B                     jmp      0x1576
0000156B  C4 5E 08                  les      bx, ptr [bp + 8]
0000156E  26 89 0F                  mov      word ptr es:[bx], cx
00001571  83 46 08 02               add      word ptr [bp + 8], 2
00001575  42                        inc      dx
00001576  3B 56 04                  cmp      dx, word ptr [bp + 4]
00001579  7E F0                     jle      0x156b
0000157B  5F                        pop      di
0000157C  5E                        pop      si
0000157D  5D                        pop      bp
0000157E  C2 08 00                  ret      8
00001581  55                        push     bp
00001582  8B EC                     mov      bp, sp
00001584  81 EC B4 00               sub      sp, 0xb4
00001588  56                        push     si
00001589  57                        push     di
0000158A  80 3E 79 1D 00            cmp      byte ptr [0x1d79], 0
0000158F  74 03                     je       0x1594
00001591  E9 39 01                  jmp      0x16cd
00001594  83 3E 80 1D 00            cmp      word ptr [0x1d80], 0
00001599  75 03                     jne      0x159e
0000159B  E9 2F 01                  jmp      0x16cd
0000159E  80 7E 04 01               cmp      byte ptr [bp + 4], 1
000015A2  74 03                     je       0x15a7
000015A4  E9 26 01                  jmp      0x16cd
000015A7  FE 46 0C                  inc      byte ptr [bp + 0xc]
000015AA  FE 46 0A                  inc      byte ptr [bp + 0xa]
000015AD  FE 46 08                  inc      byte ptr [bp + 8]
000015B0  FE 46 06                  inc      byte ptr [bp + 6]
000015B3  80 7E 0E 06               cmp      byte ptr [bp + 0xe], 6
000015B7  74 03                     je       0x15bc
000015B9  E9 82 00                  jmp      0x163e
000015BC  8A 46 0A                  mov      al, byte ptr [bp + 0xa]
000015BF  B4 00                     mov      ah, 0
000015C1  89 46 FE                  mov      word ptr [bp - 2], ax
000015C4  50                        push     ax
000015C5  8A 46 0C                  mov      al, byte ptr [bp + 0xc]
000015C8  B4 00                     mov      ah, 0
000015CA  89 46 FC                  mov      word ptr [bp - 4], ax
000015CD  50                        push     ax
000015CE  8A 46 06                  mov      al, byte ptr [bp + 6]
000015D1  B4 00                     mov      ah, 0
000015D3  50                        push     ax
000015D4  8A 46 08                  mov      al, byte ptr [bp + 8]
000015D7  B4 00                     mov      ah, 0
000015D9  50                        push     ax
000015DA  8B 46 FE                  mov      ax, word ptr [bp - 2]
000015DD  40                        inc      ax
000015DE  50                        push     ax
000015DF  FF 76 FC                  push     word ptr [bp - 4]
000015E2  90                        nop      
000015E3  0E                        push     cs
000015E4  E8 D8 FC                  call     0x12bf
000015E7  83 C4 0C                  add      sp, 0xc
000015EA  16                        push     ss
000015EB  8D 86 4C FF               lea      ax, [bp - 0xb4]
000015EF  50                        push     ax
000015F0  8A 46 06                  mov      al, byte ptr [bp + 6]
000015F3  B4 00                     mov      ah, 0
000015F5  89 46 FA                  mov      word ptr [bp - 6], ax
000015F8  50                        push     ax
000015F9  8A 46 0C                  mov      al, byte ptr [bp + 0xc]
000015FC  B4 00                     mov      ah, 0
000015FE  89 46 F8                  mov      word ptr [bp - 8], ax
00001601  50                        push     ax
00001602  FF 76 FA                  push     word ptr [bp - 6]
00001605  50                        push     ax
00001606  90                        nop      
00001607  0E                        push     cs
00001608  E8 EC FB                  call     0x11f7
0000160B  83 C4 0C                  add      sp, 0xc
0000160E  16                        push     ss
0000160F  8D 86 4C FF               lea      ax, [bp - 0xb4]
00001613  50                        push     ax
00001614  8A 46 0C                  mov      al, byte ptr [bp + 0xc]
00001617  B4 00                     mov      ah, 0
00001619  50                        push     ax
0000161A  8A 46 08                  mov      al, byte ptr [bp + 8]
0000161D  B4 00                     mov      ah, 0
0000161F  50                        push     ax
00001620  E8 38 FF                  call     0x155b
00001623  16                        push     ss
00001624  8D 86 4C FF               lea      ax, [bp - 0xb4]
00001628  50                        push     ax
00001629  8A 46 06                  mov      al, byte ptr [bp + 6]
0000162C  B4 00                     mov      ah, 0
0000162E  89 46 F6                  mov      word ptr [bp - 0xa], ax
00001631  50                        push     ax
00001632  8A 46 08                  mov      al, byte ptr [bp + 8]
00001635  B4 00                     mov      ah, 0
00001637  50                        push     ax
00001638  FF 76 F6                  push     word ptr [bp - 0xa]
0000163B  E9 7F 00                  jmp      0x16bd
0000163E  8A 46 0A                  mov      al, byte ptr [bp + 0xa]
00001641  B4 00                     mov      ah, 0
00001643  89 46 F4                  mov      word ptr [bp - 0xc], ax
00001646  40                        inc      ax
00001647  50                        push     ax
00001648  8A 46 0C                  mov      al, byte ptr [bp + 0xc]
0000164B  B4 00                     mov      ah, 0
0000164D  89 46 F2                  mov      word ptr [bp - 0xe], ax
00001650  50                        push     ax
00001651  8A 46 06                  mov      al, byte ptr [bp + 6]
00001654  B4 00                     mov      ah, 0
00001656  48                        dec      ax
00001657  50                        push     ax
00001658  8A 46 08                  mov      al, byte ptr [bp + 8]
0000165B  B4 00                     mov      ah, 0
0000165D  50                        push     ax
0000165E  FF 76 F4                  push     word ptr [bp - 0xc]
00001661  FF 76 F2                  push     word ptr [bp - 0xe]
00001664  90                        nop      
00001665  0E                        push     cs
00001666  E8 56 FC                  call     0x12bf
00001669  83 C4 0C                  add      sp, 0xc
0000166C  16                        push     ss
0000166D  8D 86 4C FF               lea      ax, [bp - 0xb4]
00001671  50                        push     ax
00001672  8A 46 0A                  mov      al, byte ptr [bp + 0xa]
00001675  B4 00                     mov      ah, 0
00001677  89 46 F0                  mov      word ptr [bp - 0x10], ax
0000167A  50                        push     ax
0000167B  8A 46 0C                  mov      al, byte ptr [bp + 0xc]
0000167E  B4 00                     mov      ah, 0
00001680  89 46 EE                  mov      word ptr [bp - 0x12], ax
00001683  50                        push     ax
00001684  FF 76 F0                  push     word ptr [bp - 0x10]
00001687  50                        push     ax
00001688  90                        nop      
00001689  0E                        push     cs
0000168A  E8 6A FB                  call     0x11f7
0000168D  83 C4 0C                  add      sp, 0xc
00001690  16                        push     ss
00001691  8D 86 4C FF               lea      ax, [bp - 0xb4]
00001695  50                        push     ax
00001696  8A 46 0C                  mov      al, byte ptr [bp + 0xc]
00001699  B4 00                     mov      ah, 0
0000169B  50                        push     ax
0000169C  8A 46 08                  mov      al, byte ptr [bp + 8]
0000169F  B4 00                     mov      ah, 0
000016A1  50                        push     ax
000016A2  E8 B6 FE                  call     0x155b
000016A5  16                        push     ss
000016A6  8D 86 4C FF               lea      ax, [bp - 0xb4]
000016AA  50                        push     ax
000016AB  8A 46 0A                  mov      al, byte ptr [bp + 0xa]
000016AE  B4 00                     mov      ah, 0
000016B0  89 46 EC                  mov      word ptr [bp - 0x14], ax
000016B3  50                        push     ax
000016B4  8A 46 08                  mov      al, byte ptr [bp + 8]
000016B7  B4 00                     mov      ah, 0
000016B9  50                        push     ax
000016BA  FF 76 EC                  push     word ptr [bp - 0x14]
000016BD  8A 46 0C                  mov      al, byte ptr [bp + 0xc]
000016C0  B4 00                     mov      ah, 0
000016C2  50                        push     ax
000016C3  90                        nop      
000016C4  0E                        push     cs
000016C5  E8 93 FB                  call     0x125b
000016C8  83 C4 0C                  add      sp, 0xc
000016CB  EB 19                     jmp      0x16e6
000016CD  8A 3E 74 1D               mov      bh, byte ptr [0x1d74]
000016D1  8A 66 0E                  mov      ah, byte ptr [bp + 0xe]
000016D4  8A 46 04                  mov      al, byte ptr [bp + 4]
000016D7  8A 6E 0A                  mov      ch, byte ptr [bp + 0xa]
000016DA  8A 4E 0C                  mov      cl, byte ptr [bp + 0xc]
000016DD  8A 76 06                  mov      dh, byte ptr [bp + 6]
000016E0  8A 56 08                  mov      dl, byte ptr [bp + 8]
000016E3  E8 83 00                  call     0x1769
000016E6  5F                        pop      di
000016E7  5E                        pop      si
000016E8  8B E5                     mov      sp, bp
000016EA  5D                        pop      bp
000016EB  C2 0C 00                  ret      0xc
000016EE  56                        push     si
000016EF  57                        push     di
000016F0  B4 03                     mov      ah, 3
000016F2  B7 00                     mov      bh, 0
000016F4  E8 72 00                  call     0x1769
000016F7  8B C2                     mov      ax, dx
000016F9  5F                        pop      di
000016FA  5E                        pop      si
000016FB  C3                        ret      
000016FC  56                        push     si
000016FD  57                        push     di
000016FE  E8 ED FF                  call     0x16ee
00001701  B4 00                     mov      ah, 0
00001703  8A 16 70 1D               mov      dl, byte ptr [0x1d70]
00001707  B6 00                     mov      dh, 0
00001709  2B C2                     sub      ax, dx
0000170B  40                        inc      ax
0000170C  5F                        pop      di
0000170D  5E                        pop      si
0000170E  CB                        retf     
0000170F  56                        push     si
00001710  57                        push     di
00001711  E8 DA FF                  call     0x16ee
00001714  B1 08                     mov      cl, 8
00001716  D3 E8                     shr      ax, cl
00001718  B4 00                     mov      ah, 0
0000171A  8A 16 71 1D               mov      dl, byte ptr [0x1d71]
0000171E  B6 00                     mov      dh, 0
00001720  2B C2                     sub      ax, dx
00001722  40                        inc      ax
00001723  5F                        pop      di
00001724  5E                        pop      si
00001725  CB                        retf     
00001726  55                        push     bp
00001727  8B EC                     mov      bp, sp
00001729  56                        push     si
0000172A  57                        push     di
0000172B  EB 18                     jmp      0x1745
0000172D  C4 5E 04                  les      bx, ptr [bp + 4]
00001730  FF 46 04                  inc      word ptr [bp + 4]
00001733  26 8A 07                  mov      al, byte ptr es:[bx]
00001736  C4 5E 08                  les      bx, ptr [bp + 8]
00001739  FF 46 08                  inc      word ptr [bp + 8]
0000173C  26 3A 07                  cmp      al, byte ptr es:[bx]
0000173F  74 04                     je       0x1745
00001741  33 C0                     xor      ax, ax
00001743  EB 0C                     jmp      0x1751
00001745  C4 5E 04                  les      bx, ptr [bp + 4]
00001748  26 80 3F 00               cmp      byte ptr es:[bx], 0
0000174C  75 DF                     jne      0x172d
0000174E  B8 01 00                  mov      ax, 1
00001751  5F                        pop      di
00001752  5E                        pop      si
00001753  5D                        pop      bp
00001754  C2 08 00                  ret      8
00001757  56                        push     si
00001758  57                        push     di
00001759  B4 12                     mov      ah, 0x12
0000175B  B3 10                     mov      bl, 0x10
0000175D  E8 09 00                  call     0x1769
00001760  8A C3                     mov      al, bl
00001762  04 F0                     add      al, 0xf0
00001764  B4 00                     mov      ah, 0
00001766  5F                        pop      di
00001767  5E                        pop      si
00001768  C3                        ret      
00001769  56                        push     si
0000176A  57                        push     di
0000176B  55                        push     bp
0000176C  1E                        push     ds
0000176D  51                        push     cx
0000176E  B9 40 00                  mov      cx, 0x40
00001771  8E D9                     mov      ds, cx
00001773  59                        pop      cx
00001774  80 FC 00                  cmp      ah, 0
00001777  74 09                     je       0x1782
00001779  80 FC 0F                  cmp      ah, 0xf
0000177C  74 59                     je       0x17d7
0000177E  CD 10                     int      0x10
00001780  EB 71                     jmp      0x17f3
00001782  3C 02                     cmp      al, 2
00001784  74 04                     je       0x178a
00001786  3C 03                     cmp      al, 3
00001788  75 19                     jne      0x17a3
0000178A  50                        push     ax
0000178B  B8 00 1A                  mov      ax, 0x1a00
0000178E  CD 10                     int      0x10
00001790  3C 1A                     cmp      al, 0x1a
00001792  74 05                     je       0x1799
00001794  80 26 87 00 FE            and      byte ptr [0x87], 0xfe
00001799  B4 01                     mov      ah, 1
0000179B  B9 07 06                  mov      cx, 0x607
0000179E  CD 10                     int      0x10
000017A0  58                        pop      ax
000017A1  EB DB                     jmp      0x177e
000017A3  3C 40                     cmp      al, 0x40
000017A5  75 D7                     jne      0x177e
000017A7  B3 10                     mov      bl, 0x10
000017A9  B4 12                     mov      ah, 0x12
000017AB  CD 10                     int      0x10
000017AD  80 FB 10                  cmp      bl, 0x10
000017B0  74 41                     je       0x17f3
000017B2  B8 12 11                  mov      ax, 0x1112
000017B5  32 DB                     xor      bl, bl
000017B7  CD 10                     int      0x10
000017B9  B8 00 12                  mov      ax, 0x1200
000017BC  B3 20                     mov      bl, 0x20
000017BE  CD 10                     int      0x10
000017C0  B8 00 1A                  mov      ax, 0x1a00
000017C3  CD 10                     int      0x10
000017C5  3C 1A                     cmp      al, 0x1a
000017C7  74 2A                     je       0x17f3
000017C9  80 0E 87 00 01            or       byte ptr [0x87], 1
000017CE  B4 01                     mov      ah, 1
000017D0  B9 00 06                  mov      cx, 0x600
000017D3  CD 10                     int      0x10
000017D5  EB 1C                     jmp      0x17f3
000017D7  CD 10                     int      0x10
000017D9  3C 02                     cmp      al, 2
000017DB  74 04                     je       0x17e1
000017DD  3C 03                     cmp      al, 3
000017DF  75 12                     jne      0x17f3
000017E1  50                        push     ax
000017E2  E8 72 FF                  call     0x1757
000017E5  0A C0                     or       al, al
000017E7  58                        pop      ax
000017E8  74 09                     je       0x17f3
000017EA  80 3E 84 00 18            cmp      byte ptr [0x84], 0x18
000017EF  74 02                     je       0x17f3
000017F1  B0 40                     mov      al, 0x40
000017F3  1F                        pop      ds
000017F4  5D                        pop      bp
000017F5  5F                        pop      di
000017F6  5E                        pop      si
000017F7  C3                        ret      
000017F8  56                        push     si
000017F9  57                        push     di
000017FA  B4 0F                     mov      ah, 0xf
000017FC  E8 6A FF                  call     0x1769
000017FF  50                        push     ax
00001800  E8 16 00                  call     0x1819
00001803  59                        pop      cx
00001804  B4 08                     mov      ah, 8
00001806  B7 00                     mov      bh, 0
00001808  E8 5E FF                  call     0x1769
0000180B  80 E4 7F                  and      ah, 0x7f
0000180E  88 26 75 1D               mov      byte ptr [0x1d75], ah
00001812  88 26 74 1D               mov      byte ptr [0x1d74], ah
00001816  5F                        pop      di
00001817  5E                        pop      si
00001818  C3                        ret      
00001819  55                        push     bp
0000181A  8B EC                     mov      bp, sp
0000181C  56                        push     si
0000181D  57                        push     di
0000181E  8A 46 04                  mov      al, byte ptr [bp + 4]
00001821  A2 76 1D                  mov      byte ptr [0x1d76], al
00001824  B4 0F                     mov      ah, 0xf
00001826  E8 40 FF                  call     0x1769
00001829  88 26 78 1D               mov      byte ptr [0x1d78], ah
0000182D  3A 06 76 1D               cmp      al, byte ptr [0x1d76]
00001831  74 14                     je       0x1847
00001833  A0 76 1D                  mov      al, byte ptr [0x1d76]
00001836  B4 00                     mov      ah, 0
00001838  E8 2E FF                  call     0x1769
0000183B  B4 0F                     mov      ah, 0xf
0000183D  E8 29 FF                  call     0x1769
00001840  A2 76 1D                  mov      byte ptr [0x1d76], al
00001843  88 26 78 1D               mov      byte ptr [0x1d78], ah
00001847  80 3E 76 1D 03            cmp      byte ptr [0x1d76], 3
0000184C  76 13                     jbe      0x1861
0000184E  80 3E 76 1D 40            cmp      byte ptr [0x1d76], 0x40
00001853  73 0C                     jae      0x1861
00001855  80 3E 76 1D 07            cmp      byte ptr [0x1d76], 7
0000185A  74 05                     je       0x1861
0000185C  B8 01 00                  mov      ax, 1
0000185F  EB 02                     jmp      0x1863
00001861  33 C0                     xor      ax, ax
00001863  A2 79 1D                  mov      byte ptr [0x1d79], al
00001866  80 3E 76 1D 40            cmp      byte ptr [0x1d76], 0x40
0000186B  74 04                     je       0x1871
0000186D  B0 19                     mov      al, 0x19
0000186F  EB 0B                     jmp      0x187c
00001871  B8 40 00                  mov      ax, 0x40
00001874  8E C0                     mov      es, ax
00001876  26 A0 84 00               mov      al, byte ptr es:[0x84]
0000187A  FE C0                     inc      al
0000187C  A2 77 1D                  mov      byte ptr [0x1d77], al
0000187F  80 3E 76 1D 07            cmp      byte ptr [0x1d76], 7
00001884  74 20                     je       0x18a6
00001886  B8 00 F0                  mov      ax, 0xf000
00001889  BA EA FF                  mov      dx, 0xffea
0000188C  50                        push     ax
0000188D  52                        push     dx
0000188E  1E                        push     ds
0000188F  B8 82 1D                  mov      ax, 0x1d82
00001892  50                        push     ax
00001893  E8 90 FE                  call     0x1726
00001896  0B C0                     or       ax, ax
00001898  75 0C                     jne      0x18a6
0000189A  E8 BA FE                  call     0x1757
0000189D  0B C0                     or       ax, ax
0000189F  75 05                     jne      0x18a6
000018A1  B8 01 00                  mov      ax, 1
000018A4  EB 02                     jmp      0x18a8
000018A6  33 C0                     xor      ax, ax
000018A8  A2 7A 1D                  mov      byte ptr [0x1d7a], al
000018AB  80 3E 76 1D 07            cmp      byte ptr [0x1d76], 7
000018B0  75 05                     jne      0x18b7
000018B2  B8 00 B0                  mov      ax, 0xb000
000018B5  EB 03                     jmp      0x18ba
000018B7  B8 00 B8                  mov      ax, 0xb800
000018BA  A3 7D 1D                  mov      word ptr [0x1d7d], ax
000018BD  C7 06 7B 1D 00 00         mov      word ptr [0x1d7b], 0
000018C3  B0 00                     mov      al, 0
000018C5  A2 71 1D                  mov      byte ptr [0x1d71], al
000018C8  A2 70 1D                  mov      byte ptr [0x1d70], al
000018CB  A0 78 1D                  mov      al, byte ptr [0x1d78]
000018CE  04 FF                     add      al, 0xff
000018D0  A2 72 1D                  mov      byte ptr [0x1d72], al
000018D3  A0 77 1D                  mov      al, byte ptr [0x1d77]
000018D6  04 FF                     add      al, 0xff
000018D8  A2 73 1D                  mov      byte ptr [0x1d73], al
000018DB  5F                        pop      di
000018DC  5E                        pop      si
000018DD  5D                        pop      bp
000018DE  C3                        ret      
000018DF  56                        push     si
000018E0  57                        push     di
000018E1  80 3E 8A 1D 00            cmp      byte ptr [0x1d8a], 0
000018E6  74 0A                     je       0x18f2
000018E8  C6 06 8A 1D 00            mov      byte ptr [0x1d8a], 0
000018ED  A0 8B 1D                  mov      al, byte ptr [0x1d8b]
000018F0  EB 05                     jmp      0x18f7
000018F2  B8 00 07                  mov      ax, 0x700
000018F5  CD 21                     int      0x21
000018F7  B4 00                     mov      ah, 0
000018F9  5F                        pop      di
000018FA  5E                        pop      si
000018FB  CB                        retf     
000018FC  58                        pop      ax
000018FD  0E                        push     cs
000018FE  50                        push     ax
000018FF  55                        push     bp
00001900  8B EC                     mov      bp, sp
00001902  83 EC 02                  sub      sp, 2
00001905  56                        push     si
00001906  57                        push     di
00001907  80 3E 8A 1D 00            cmp      byte ptr [0x1d8a], 0
0000190C  74 09                     je       0x1917
0000190E  0E                        push     cs
0000190F  E8 CD FF                  call     0x18df
00001912  89 46 FE                  mov      word ptr [bp - 2], ax
00001915  EB 0E                     jmp      0x1925
00001917  0E                        push     cs
00001918  E8 C4 FF                  call     0x18df
0000191B  89 46 FE                  mov      word ptr [bp - 2], ax
0000191E  50                        push     ax
0000191F  90                        nop      
00001920  0E                        push     cs
00001921  E8 43 FA                  call     0x1367
00001924  59                        pop      cx
00001925  8B 46 FE                  mov      ax, word ptr [bp - 2]
00001928  5F                        pop      di
00001929  5E                        pop      si
0000192A  8B E5                     mov      sp, bp
0000192C  5D                        pop      bp
0000192D  CB                        retf     
0000192E  58                        pop      ax
0000192F  0E                        push     cs
00001930  50                        push     ax
00001931  55                        push     bp
00001932  8B EC                     mov      bp, sp
00001934  56                        push     si
00001935  57                        push     di
00001936  80 3E 8A 1D 00            cmp      byte ptr [0x1d8a], 0
0000193B  74 05                     je       0x1942
0000193D  B8 FF FF                  mov      ax, 0xffff
00001940  EB 0D                     jmp      0x194f
00001942  C6 06 8A 1D 01            mov      byte ptr [0x1d8a], 1
00001947  8A 46 06                  mov      al, byte ptr [bp + 6]
0000194A  A2 8B 1D                  mov      byte ptr [0x1d8b], al
0000194D  B4 00                     mov      ah, 0
0000194F  5F                        pop      di
00001950  5E                        pop      si
00001951  5D                        pop      bp
00001952  CB                        retf     
00001953  56                        push     si
00001954  57                        push     di
00001955  80 3E 8A 1D 00            cmp      byte ptr [0x1d8a], 0
0000195A  74 05                     je       0x1961
0000195C  B8 01 00                  mov      ax, 1
0000195F  EB 05                     jmp      0x1966
00001961  B4 0B                     mov      ah, 0xb
00001963  CD 21                     int      0x21
00001965  98                        cwde     
00001966  5F                        pop      di
00001967  5E                        pop      si
00001968  CB                        retf     
00001969  55                        push     bp
0000196A  8B EC                     mov      bp, sp
0000196C  83 EC 02                  sub      sp, 2
0000196F  56                        push     si
00001970  57                        push     di
00001971  FF 76 0C                  push     word ptr [bp + 0xc]
00001974  FF 76 0A                  push     word ptr [bp + 0xa]
00001977  90                        nop      
00001978  0E                        push     cs
00001979  E8 DA 02                  call     0x1c56
0000197C  59                        pop      cx
0000197D  59                        pop      cx
0000197E  89 46 FE                  mov      word ptr [bp - 2], ax
00001981  40                        inc      ax
00001982  50                        push     ax
00001983  FF 76 0C                  push     word ptr [bp + 0xc]
00001986  FF 76 0A                  push     word ptr [bp + 0xa]
00001989  FF 76 08                  push     word ptr [bp + 8]
0000198C  FF 76 06                  push     word ptr [bp + 6]
0000198F  90                        nop      
00001990  0E                        push     cs
00001991  E8 05 01                  call     0x1a99
00001994  83 C4 0A                  add      sp, 0xa
00001997  8B 56 08                  mov      dx, word ptr [bp + 8]
0000199A  8B 46 06                  mov      ax, word ptr [bp + 6]
0000199D  03 46 FE                  add      ax, word ptr [bp - 2]
000019A0  5F                        pop      di
000019A1  5E                        pop      si
000019A2  8B E5                     mov      sp, bp
000019A4  5D                        pop      bp
000019A5  CB                        retf     
000019A6  55                        push     bp
000019A7  8B EC                     mov      bp, sp
000019A9  83 EC 08                  sub      sp, 8
000019AC  56                        push     si
000019AD  57                        push     di
000019AE  8B 46 06                  mov      ax, word ptr [bp + 6]
000019B1  0B 46 08                  or       ax, word ptr [bp + 8]
000019B4  74 45                     je       0x19fb
000019B6  8B 56 08                  mov      dx, word ptr [bp + 8]
000019B9  8B 46 06                  mov      ax, word ptr [bp + 6]
000019BC  89 16 14 58               mov      word ptr [0x5814], dx
000019C0  A3 12 58                  mov      word ptr [0x5812], ax
000019C3  EB 36                     jmp      0x19fb
000019C5  8B 56 0C                  mov      dx, word ptr [bp + 0xc]
000019C8  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
000019CB  89 56 FE                  mov      word ptr [bp - 2], dx
000019CE  89 46 FC                  mov      word ptr [bp - 4], ax
000019D1  EB 12                     jmp      0x19e5
000019D3  C4 5E FC                  les      bx, ptr [bp - 4]
000019D6  26 8A 07                  mov      al, byte ptr es:[bx]
000019D9  C4 1E 12 58               les      bx, ptr [0x5812]
000019DD  26 3A 07                  cmp      al, byte ptr es:[bx]
000019E0  74 0C                     je       0x19ee
000019E2  FF 46 FC                  inc      word ptr [bp - 4]
000019E5  C4 5E FC                  les      bx, ptr [bp - 4]
000019E8  26 80 3F 00               cmp      byte ptr es:[bx], 0
000019EC  75 E5                     jne      0x19d3
000019EE  C4 5E FC                  les      bx, ptr [bp - 4]
000019F1  26 80 3F 00               cmp      byte ptr es:[bx], 0
000019F5  74 0E                     je       0x1a05
000019F7  FF 06 12 58               inc      word ptr [0x5812]
000019FB  C4 1E 12 58               les      bx, ptr [0x5812]
000019FF  26 80 3F 00               cmp      byte ptr es:[bx], 0
00001A03  75 C0                     jne      0x19c5
00001A05  C4 1E 12 58               les      bx, ptr [0x5812]
00001A09  26 80 3F 00               cmp      byte ptr es:[bx], 0
00001A0D  75 06                     jne      0x1a15
00001A0F  33 D2                     xor      dx, dx
00001A11  33 C0                     xor      ax, ax
00001A13  EB 56                     jmp      0x1a6b
00001A15  8B 16 14 58               mov      dx, word ptr [0x5814]
00001A19  A1 12 58                  mov      ax, word ptr [0x5812]
00001A1C  89 56 FA                  mov      word ptr [bp - 6], dx
00001A1F  89 46 F8                  mov      word ptr [bp - 8], ax
00001A22  EB 37                     jmp      0x1a5b
00001A24  8B 56 0C                  mov      dx, word ptr [bp + 0xc]
00001A27  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
00001A2A  89 56 FE                  mov      word ptr [bp - 2], dx
00001A2D  89 46 FC                  mov      word ptr [bp - 4], ax
00001A30  EB 1C                     jmp      0x1a4e
00001A32  C4 5E FC                  les      bx, ptr [bp - 4]
00001A35  26 8A 07                  mov      al, byte ptr es:[bx]
00001A38  C4 1E 12 58               les      bx, ptr [0x5812]
00001A3C  26 3A 07                  cmp      al, byte ptr es:[bx]
00001A3F  75 0A                     jne      0x1a4b
00001A41  26 C6 07 00               mov      byte ptr es:[bx], 0
00001A45  FF 06 12 58               inc      word ptr [0x5812]
00001A49  EB 1A                     jmp      0x1a65
00001A4B  FF 46 FC                  inc      word ptr [bp - 4]
00001A4E  C4 5E FC                  les      bx, ptr [bp - 4]
00001A51  26 80 3F 00               cmp      byte ptr es:[bx], 0
00001A55  75 DB                     jne      0x1a32
00001A57  FF 06 12 58               inc      word ptr [0x5812]
00001A5B  C4 1E 12 58               les      bx, ptr [0x5812]
00001A5F  26 80 3F 00               cmp      byte ptr es:[bx], 0
00001A63  75 BF                     jne      0x1a24
00001A65  8B 56 FA                  mov      dx, word ptr [bp - 6]
00001A68  8B 46 F8                  mov      ax, word ptr [bp - 8]
00001A6B  5F                        pop      di
00001A6C  5E                        pop      si
00001A6D  8B E5                     mov      sp, bp
00001A6F  5D                        pop      bp
00001A70  CB                        retf     
00001A71  55                        push     bp
00001A72  8B EC                     mov      bp, sp
00001A74  56                        push     si
00001A75  57                        push     di
00001A76  1E                        push     ds
00001A77  8B 46 0E                  mov      ax, word ptr [bp + 0xe]
00001A7A  8B C8                     mov      cx, ax
00001A7C  E3 14                     jcxz     0x1a92
00001A7E  C5 76 06                  lds      si, ptr [bp + 6]
00001A81  C4 7E 0A                  les      di, ptr [bp + 0xa]
00001A84  FC                        cld      
00001A85  F3 A6                     repe cmpsb byte ptr [si], byte ptr es:[di]
00001A87  8A 44 FF                  mov      al, byte ptr [si - 1]
00001A8A  32 E4                     xor      ah, ah
00001A8C  26 8A 4D FF               mov      cl, byte ptr es:[di - 1]
00001A90  32 ED                     xor      ch, ch
00001A92  1F                        pop      ds
00001A93  2B C1                     sub      ax, cx
00001A95  5F                        pop      di
00001A96  5E                        pop      si
00001A97  5D                        pop      bp
00001A98  CB                        retf     
00001A99  55                        push     bp
00001A9A  8B EC                     mov      bp, sp
00001A9C  56                        push     si
00001A9D  57                        push     di
00001A9E  8C DA                     mov      dx, ds
00001AA0  C4 7E 06                  les      di, ptr [bp + 6]
00001AA3  C5 76 0A                  lds      si, ptr [bp + 0xa]
00001AA6  8B 4E 0E                  mov      cx, word ptr [bp + 0xe]
00001AA9  D1 E9                     shr      cx, 1
00001AAB  FC                        cld      
00001AAC  F3 A5                     rep movsw word ptr es:[di], word ptr [si]
00001AAE  73 01                     jae      0x1ab1
00001AB0  A4                        movsb    byte ptr es:[di], byte ptr [si]
00001AB1  8E DA                     mov      ds, dx
00001AB3  8B 56 08                  mov      dx, word ptr [bp + 8]
00001AB6  8B 46 06                  mov      ax, word ptr [bp + 6]
00001AB9  5F                        pop      di
00001ABA  5E                        pop      si
00001ABB  5D                        pop      bp
00001ABC  CB                        retf     
00001ABD  55                        push     bp
00001ABE  8B EC                     mov      bp, sp
00001AC0  56                        push     si
00001AC1  57                        push     di
00001AC2  C4 7E 06                  les      di, ptr [bp + 6]
00001AC5  8B 4E 0A                  mov      cx, word ptr [bp + 0xa]
00001AC8  8A 46 0C                  mov      al, byte ptr [bp + 0xc]
00001ACB  8A E0                     mov      ah, al
00001ACD  FC                        cld      
00001ACE  F7 C7 01 00               test     di, 1
00001AD2  74 04                     je       0x1ad8
00001AD4  E3 09                     jcxz     0x1adf
00001AD6  AA                        stosb    byte ptr es:[di], al
00001AD7  49                        dec      cx
00001AD8  D1 E9                     shr      cx, 1
00001ADA  F3 AB                     rep stosw word ptr es:[di], ax
00001ADC  73 01                     jae      0x1adf
00001ADE  AA                        stosb    byte ptr es:[di], al
00001ADF  5F                        pop      di
00001AE0  5E                        pop      si
00001AE1  5D                        pop      bp
00001AE2  CB                        retf     
00001AE3  55                        push     bp
00001AE4  8B EC                     mov      bp, sp
00001AE6  56                        push     si
00001AE7  57                        push     di
00001AE8  8A 46 0A                  mov      al, byte ptr [bp + 0xa]
00001AEB  50                        push     ax
00001AEC  FF 76 0C                  push     word ptr [bp + 0xc]
00001AEF  FF 76 08                  push     word ptr [bp + 8]
00001AF2  FF 76 06                  push     word ptr [bp + 6]
00001AF5  0E                        push     cs
00001AF6  E8 C4 FF                  call     0x1abd
00001AF9  83 C4 08                  add      sp, 8
00001AFC  8B 56 08                  mov      dx, word ptr [bp + 8]
00001AFF  8B 46 06                  mov      ax, word ptr [bp + 6]
00001B02  5F                        pop      di
00001B03  5E                        pop      si
00001B04  5D                        pop      bp
00001B05  CB                        retf     
00001B06  55                        push     bp
00001B07  8B EC                     mov      bp, sp
00001B09  56                        push     si
00001B0A  57                        push     di
00001B0B  1E                        push     ds
00001B0C  8B 4E 0C                  mov      cx, word ptr [bp + 0xc]
00001B0F  8B 5E 0A                  mov      bx, word ptr [bp + 0xa]
00001B12  8B 56 08                  mov      dx, word ptr [bp + 8]
00001B15  8B 46 06                  mov      ax, word ptr [bp + 6]
00001B18  E8 93 30                  call     0x4bae
00001B1B  73 06                     jae      0x1b23
00001B1D  FD                        std      
00001B1E  B8 01 00                  mov      ax, 1
00001B21  EB 03                     jmp      0x1b26
00001B23  FC                        cld      
00001B24  33 C0                     xor      ax, ax
00001B26  C5 76 06                  lds      si, ptr [bp + 6]
00001B29  C4 7E 0A                  les      di, ptr [bp + 0xa]
00001B2C  8B 4E 0E                  mov      cx, word ptr [bp + 0xe]
00001B2F  0B C0                     or       ax, ax
00001B31  74 06                     je       0x1b39
00001B33  03 F1                     add      si, cx
00001B35  4E                        dec      si
00001B36  03 F9                     add      di, cx
00001B38  4F                        dec      di
00001B39  F7 C7 01 00               test     di, 1
00001B3D  74 04                     je       0x1b43
00001B3F  E3 11                     jcxz     0x1b52
00001B41  A4                        movsb    byte ptr es:[di], byte ptr [si]
00001B42  49                        dec      cx
00001B43  2B F0                     sub      si, ax
00001B45  2B F8                     sub      di, ax
00001B47  D1 E9                     shr      cx, 1
00001B49  F3 A5                     rep movsw word ptr es:[di], word ptr [si]
00001B4B  73 05                     jae      0x1b52
00001B4D  03 F0                     add      si, ax
00001B4F  03 F8                     add      di, ax
00001B51  A4                        movsb    byte ptr es:[di], byte ptr [si]
00001B52  FC                        cld      
00001B53  1F                        pop      ds
00001B54  5F                        pop      di
00001B55  5E                        pop      si
00001B56  5D                        pop      bp
00001B57  CB                        retf     
00001B58  55                        push     bp
00001B59  8B EC                     mov      bp, sp
00001B5B  56                        push     si
00001B5C  57                        push     di
00001B5D  FF 76 0E                  push     word ptr [bp + 0xe]
00001B60  FF 76 08                  push     word ptr [bp + 8]
00001B63  FF 76 06                  push     word ptr [bp + 6]
00001B66  FF 76 0C                  push     word ptr [bp + 0xc]
00001B69  FF 76 0A                  push     word ptr [bp + 0xa]
00001B6C  0E                        push     cs
00001B6D  E8 96 FF                  call     0x1b06
00001B70  83 C4 0A                  add      sp, 0xa
00001B73  8B 56 08                  mov      dx, word ptr [bp + 8]
00001B76  8B 46 06                  mov      ax, word ptr [bp + 6]
00001B79  5F                        pop      di
00001B7A  5E                        pop      si
00001B7B  5D                        pop      bp
00001B7C  CB                        retf     
00001B7D  55                        push     bp
00001B7E  8B EC                     mov      bp, sp
00001B80  56                        push     si
00001B81  57                        push     di
00001B82  FC                        cld      
00001B83  1E                        push     ds
00001B84  C4 7E 06                  les      di, ptr [bp + 6]
00001B87  8B D7                     mov      dx, di
00001B89  32 C0                     xor      al, al
00001B8B  B9 FF FF                  mov      cx, 0xffff
00001B8E  F2 AE                     repne scasb al, byte ptr es:[di]
00001B90  06                        push     es
00001B91  8D 75 FF                  lea      si, [di - 1]
00001B94  C4 7E 0A                  les      di, ptr [bp + 0xa]
00001B97  B9 FF FF                  mov      cx, 0xffff
00001B9A  F2 AE                     repne scasb al, byte ptr es:[di]
00001B9C  F7 D1                     not      cx
00001B9E  2B F9                     sub      di, cx
00001BA0  06                        push     es
00001BA1  1F                        pop      ds
00001BA2  07                        pop      es
00001BA3  87 F7                     xchg     di, si
00001BA5  F7 C6 01 00               test     si, 1
00001BA9  74 02                     je       0x1bad
00001BAB  A4                        movsb    byte ptr es:[di], byte ptr [si]
00001BAC  49                        dec      cx
00001BAD  D1 E9                     shr      cx, 1
00001BAF  F3 A5                     rep movsw word ptr es:[di], word ptr [si]
00001BB1  73 01                     jae      0x1bb4
00001BB3  A4                        movsb    byte ptr es:[di], byte ptr [si]
00001BB4  92                        xchg     dx, ax
00001BB5  8C C2                     mov      dx, es
00001BB7  1F                        pop      ds
00001BB8  5F                        pop      di
00001BB9  5E                        pop      si
00001BBA  5D                        pop      bp
00001BBB  CB                        retf     
00001BBC  55                        push     bp
00001BBD  8B EC                     mov      bp, sp
00001BBF  56                        push     si
00001BC0  57                        push     di
00001BC1  8C DA                     mov      dx, ds
00001BC3  FC                        cld      
00001BC4  33 C0                     xor      ax, ax
00001BC6  8B D8                     mov      bx, ax
00001BC8  C4 7E 0A                  les      di, ptr [bp + 0xa]
00001BCB  8B F7                     mov      si, di
00001BCD  32 C0                     xor      al, al
00001BCF  B9 FF FF                  mov      cx, 0xffff
00001BD2  F2 AE                     repne scasb al, byte ptr es:[di]
00001BD4  F7 D1                     not      cx
00001BD6  8B FE                     mov      di, si
00001BD8  C5 76 06                  lds      si, ptr [bp + 6]
00001BDB  F3 A6                     repe cmpsb byte ptr [si], byte ptr es:[di]
00001BDD  8A 44 FF                  mov      al, byte ptr [si - 1]
00001BE0  26 8A 5D FF               mov      bl, byte ptr es:[di - 1]
00001BE4  2B C3                     sub      ax, bx
00001BE6  8E DA                     mov      ds, dx
00001BE8  5F                        pop      di
00001BE9  5E                        pop      si
00001BEA  5D                        pop      bp
00001BEB  CB                        retf     
00001BEC  55                        push     bp
00001BED  8B EC                     mov      bp, sp
00001BEF  56                        push     si
00001BF0  57                        push     di
00001BF1  FC                        cld      
00001BF2  C4 7E 0A                  les      di, ptr [bp + 0xa]
00001BF5  8B F7                     mov      si, di
00001BF7  32 C0                     xor      al, al
00001BF9  B9 FF FF                  mov      cx, 0xffff
00001BFC  F2 AE                     repne scasb al, byte ptr es:[di]
00001BFE  F7 D1                     not      cx
00001C00  1E                        push     ds
00001C01  8C C0                     mov      ax, es
00001C03  8E D8                     mov      ds, ax
00001C05  C4 7E 06                  les      di, ptr [bp + 6]
00001C08  F3 A4                     rep movsb byte ptr es:[di], byte ptr [si]
00001C0A  1F                        pop      ds
00001C0B  8B 56 08                  mov      dx, word ptr [bp + 8]
00001C0E  8B 46 06                  mov      ax, word ptr [bp + 6]
00001C11  5F                        pop      di
00001C12  5E                        pop      si
00001C13  5D                        pop      bp
00001C14  CB                        retf     
00001C15  55                        push     bp
00001C16  8B EC                     mov      bp, sp
00001C18  56                        push     si
00001C19  57                        push     di
00001C1A  8C DA                     mov      dx, ds
00001C1C  FC                        cld      
00001C1D  C5 76 06                  lds      si, ptr [bp + 6]
00001C20  C4 7E 0A                  les      di, ptr [bp + 0xa]
00001C23  33 C0                     xor      ax, ax
00001C25  8B D8                     mov      bx, ax
00001C27  B9 7A 61                  mov      cx, 0x617a
00001C2A  AC                        lodsb    al, byte ptr [si]
00001C2B  26 8A 1D                  mov      bl, byte ptr es:[di]
00001C2E  0A C0                     or       al, al
00001C30  74 1C                     je       0x1c4e
00001C32  AE                        scasb    al, byte ptr es:[di]
00001C33  74 F5                     je       0x1c2a
00001C35  3A C5                     cmp      al, ch
00001C37  72 06                     jb       0x1c3f
00001C39  3A C1                     cmp      al, cl
00001C3B  77 02                     ja       0x1c3f
00001C3D  2C 20                     sub      al, 0x20
00001C3F  3A DD                     cmp      bl, ch
00001C41  72 07                     jb       0x1c4a
00001C43  3A D9                     cmp      bl, cl
00001C45  77 03                     ja       0x1c4a
00001C47  80 EB 20                  sub      bl, 0x20
00001C4A  3A C3                     cmp      al, bl
00001C4C  74 DC                     je       0x1c2a
00001C4E  2B C3                     sub      ax, bx
00001C50  8E DA                     mov      ds, dx
00001C52  5F                        pop      di
00001C53  5E                        pop      si
00001C54  5D                        pop      bp
00001C55  CB                        retf     
00001C56  55                        push     bp
00001C57  8B EC                     mov      bp, sp
00001C59  56                        push     si
00001C5A  57                        push     di
00001C5B  C4 7E 06                  les      di, ptr [bp + 6]
00001C5E  33 C0                     xor      ax, ax
00001C60  3B 46 08                  cmp      ax, word ptr [bp + 8]
00001C63  75 04                     jne      0x1c69
00001C65  3B C7                     cmp      ax, di
00001C67  74 0A                     je       0x1c73
00001C69  FC                        cld      
00001C6A  B9 FF FF                  mov      cx, 0xffff
00001C6D  F2 AE                     repne scasb al, byte ptr es:[di]
00001C6F  91                        xchg     cx, ax
00001C70  F7 D0                     not      ax
00001C72  48                        dec      ax
00001C73  5F                        pop      di
00001C74  5E                        pop      si
00001C75  5D                        pop      bp
00001C76  CB                        retf     
00001C77  55                        push     bp
00001C78  8B EC                     mov      bp, sp
00001C7A  56                        push     si
00001C7B  57                        push     di
00001C7C  C4 5E 0A                  les      bx, ptr [bp + 0xa]
00001C7F  26 80 3F 00               cmp      byte ptr es:[bx], 0
00001C83  75 08                     jne      0x1c8d
00001C85  8B 56 08                  mov      dx, word ptr [bp + 8]
00001C88  8B 46 06                  mov      ax, word ptr [bp + 6]
00001C8B  EB 52                     jmp      0x1cdf
00001C8D  1E                        push     ds
00001C8E  FC                        cld      
00001C8F  C4 7E 06                  les      di, ptr [bp + 6]
00001C92  06                        push     es
00001C93  8B DF                     mov      bx, di
00001C95  33 C0                     xor      ax, ax
00001C97  B9 FF FF                  mov      cx, 0xffff
00001C9A  F2 AE                     repne scasb al, byte ptr es:[di]
00001C9C  F7 D1                     not      cx
00001C9E  87 CA                     xchg     dx, cx
00001CA0  C4 7E 0A                  les      di, ptr [bp + 0xa]
00001CA3  06                        push     es
00001CA4  8B EF                     mov      bp, di
00001CA6  33 C0                     xor      ax, ax
00001CA8  B9 FF FF                  mov      cx, 0xffff
00001CAB  F2 AE                     repne scasb al, byte ptr es:[di]
00001CAD  41                        inc      cx
00001CAE  F7 D1                     not      cx
00001CB0  1F                        pop      ds
00001CB1  07                        pop      es
00001CB2  8B F5                     mov      si, bp
00001CB4  AC                        lodsb    al, byte ptr [si]
00001CB5  87 FB                     xchg     bx, di
00001CB7  87 CA                     xchg     dx, cx
00001CB9  F2 AE                     repne scasb al, byte ptr es:[di]
00001CBB  8B DF                     mov      bx, di
00001CBD  75 04                     jne      0x1cc3
00001CBF  3B CA                     cmp      cx, dx
00001CC1  73 09                     jae      0x1ccc
00001CC3  33 DB                     xor      bx, bx
00001CC5  8E C3                     mov      es, bx
00001CC7  BB 01 00                  mov      bx, 1
00001CCA  EB 0D                     jmp      0x1cd9
00001CCC  87 CA                     xchg     dx, cx
00001CCE  E3 09                     jcxz     0x1cd9
00001CD0  8B C1                     mov      ax, cx
00001CD2  49                        dec      cx
00001CD3  F3 A6                     repe cmpsb byte ptr [si], byte ptr es:[di]
00001CD5  8B C8                     mov      cx, ax
00001CD7  75 D9                     jne      0x1cb2
00001CD9  1F                        pop      ds
00001CDA  8B C3                     mov      ax, bx
00001CDC  48                        dec      ax
00001CDD  8C C2                     mov      dx, es
00001CDF  5F                        pop      di
00001CE0  5E                        pop      si
00001CE1  5D                        pop      bp
00001CE2  CB                        retf     
00001CE3  55                        push     bp
00001CE4  8B EC                     mov      bp, sp
00001CE6  56                        push     si
00001CE7  57                        push     di
00001CE8  C4 5E 06                  les      bx, ptr [bp + 6]
00001CEB  26 83 67 02 CF            and      word ptr es:[bx + 2], 0xffcf
00001CF0  5F                        pop      di
00001CF1  5E                        pop      si
00001CF2  5D                        pop      bp
00001CF3  CB                        retf     
00001CF4  55                        push     bp
00001CF5  8B EC                     mov      bp, sp
00001CF7  56                        push     si
00001CF8  57                        push     di
00001CF9  B4 19                     mov      ah, 0x19
00001CFB  CD 21                     int      0x21
00001CFD  B4 00                     mov      ah, 0
00001CFF  40                        inc      ax
00001D00  C4 5E 06                  les      bx, ptr [bp + 6]
00001D03  26 89 07                  mov      word ptr es:[bx], ax
00001D06  5F                        pop      di
00001D07  5E                        pop      si
00001D08  5D                        pop      bp
00001D09  CB                        retf     
00001D0A  55                        push     bp
00001D0B  8B EC                     mov      bp, sp
00001D0D  56                        push     si
00001D0E  57                        push     di
00001D0F  8A 56 06                  mov      dl, byte ptr [bp + 6]
00001D12  FE CA                     dec      dl
00001D14  B4 0E                     mov      ah, 0xe
00001D16  CD 21                     int      0x21
00001D18  B4 00                     mov      ah, 0
00001D1A  C4 5E 08                  les      bx, ptr [bp + 8]
00001D1D  26 89 07                  mov      word ptr es:[bx], ax
00001D20  5F                        pop      di
00001D21  5E                        pop      si
00001D22  5D                        pop      bp
00001D23  CB                        retf     
00001D24  55                        push     bp
00001D25  8B EC                     mov      bp, sp
00001D27  83 EC 02                  sub      sp, 2
00001D2A  56                        push     si
00001D2B  57                        push     di
00001D2C  16                        push     ss
00001D2D  8D 46 FE                  lea      ax, [bp - 2]
00001D30  50                        push     ax
00001D31  90                        nop      
00001D32  0E                        push     cs
00001D33  E8 BE FF                  call     0x1cf4
00001D36  59                        pop      cx
00001D37  59                        pop      cx
00001D38  8B 46 FE                  mov      ax, word ptr [bp - 2]
00001D3B  48                        dec      ax
00001D3C  5F                        pop      di
00001D3D  5E                        pop      si
00001D3E  8B E5                     mov      sp, bp
00001D40  5D                        pop      bp
00001D41  CB                        retf     
00001D42  55                        push     bp
00001D43  8B EC                     mov      bp, sp
00001D45  83 EC 02                  sub      sp, 2
00001D48  56                        push     si
00001D49  57                        push     di
00001D4A  16                        push     ss
00001D4B  8D 46 FE                  lea      ax, [bp - 2]
00001D4E  50                        push     ax
00001D4F  8B 46 06                  mov      ax, word ptr [bp + 6]
00001D52  40                        inc      ax
00001D53  50                        push     ax
00001D54  90                        nop      
00001D55  0E                        push     cs
00001D56  E8 B1 FF                  call     0x1d0a
00001D59  83 C4 06                  add      sp, 6
00001D5C  8B 46 FE                  mov      ax, word ptr [bp - 2]
00001D5F  5F                        pop      di
00001D60  5E                        pop      si
00001D61  8B E5                     mov      sp, bp
00001D63  5D                        pop      bp
00001D64  CB                        retf     
00001D65  55                        push     bp
00001D66  8B EC                     mov      bp, sp
00001D68  56                        push     si
00001D69  57                        push     di
00001D6A  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
00001D6D  0B 46 0C                  or       ax, word ptr [bp + 0xc]
00001D70  75 08                     jne      0x1d7a
00001D72  8C 5E 0C                  mov      word ptr [bp + 0xc], ds
00001D75  C7 46 0A 16 58            mov      word ptr [bp + 0xa], 0x5816
00001D7A  FF 76 04                  push     word ptr [bp + 4]
00001D7D  8B 46 06                  mov      ax, word ptr [bp + 6]
00001D80  0B 46 08                  or       ax, word ptr [bp + 8]
00001D83  75 07                     jne      0x1d8c
00001D85  8C DA                     mov      dx, ds
00001D87  B8 DE 21                  mov      ax, 0x21de
00001D8A  EB 06                     jmp      0x1d92
00001D8C  8B 56 08                  mov      dx, word ptr [bp + 8]
00001D8F  8B 46 06                  mov      ax, word ptr [bp + 6]
00001D92  52                        push     dx
00001D93  50                        push     ax
00001D94  FF 76 0C                  push     word ptr [bp + 0xc]
00001D97  FF 76 0A                  push     word ptr [bp + 0xa]
00001D9A  90                        nop      
00001D9B  0E                        push     cs
00001D9C  E8 CA FB                  call     0x1969
00001D9F  83 C4 08                  add      sp, 8
00001DA2  52                        push     dx
00001DA3  50                        push     ax
00001DA4  E8 8A 22                  call     0x4031
00001DA7  1E                        push     ds
00001DA8  B8 E2 21                  mov      ax, 0x21e2
00001DAB  50                        push     ax
00001DAC  FF 76 0C                  push     word ptr [bp + 0xc]
00001DAF  FF 76 0A                  push     word ptr [bp + 0xa]
00001DB2  90                        nop      
00001DB3  0E                        push     cs
00001DB4  E8 C6 FD                  call     0x1b7d
00001DB7  83 C4 08                  add      sp, 8
00001DBA  8B 56 0C                  mov      dx, word ptr [bp + 0xc]
00001DBD  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
00001DC0  5F                        pop      di
00001DC1  5E                        pop      si
00001DC2  5D                        pop      bp
00001DC3  C2 0A 00                  ret      0xa
00001DC6  56                        push     si
00001DC7  57                        push     di
00001DC8  B9 05 00                  mov      cx, 5
00001DCB  EB 24                     jmp      0x1df1
00001DCD  8B D9                     mov      bx, cx
00001DCF  03 DB                     add      bx, bx
00001DD1  C7 87 76 21 00 00         mov      word ptr [bx + 0x2176], 0
00001DD7  B8 14 00                  mov      ax, 0x14
00001DDA  F7 E9                     imul     cx
00001DDC  8B D0                     mov      dx, ax
00001DDE  8B D8                     mov      bx, ax
00001DE0  C6 87 90 1D FF            mov      byte ptr [bx + 0x1d90], 0xff
00001DE5  8B C2                     mov      ax, dx
00001DE7  05 8C 1D                  add      ax, 0x1d8c
00001DEA  8B DA                     mov      bx, dx
00001DEC  89 87 9E 1D               mov      word ptr [bx + 0x1d9e], ax
00001DF0  41                        inc      cx
00001DF1  3B 0E 74 21               cmp      cx, word ptr [0x2174]
00001DF5  72 D6                     jb       0x1dcd
00001DF7  A0 90 1D                  mov      al, byte ptr [0x1d90]
00001DFA  98                        cwde     
00001DFB  50                        push     ax
00001DFC  90                        nop      
00001DFD  0E                        push     cs
00001DFE  E8 D5 01                  call     0x1fd6
00001E01  59                        pop      cx
00001E02  0B C0                     or       ax, ax
00001E04  75 06                     jne      0x1e0c
00001E06  81 26 8E 1D FF FD         and      word ptr [0x1d8e], 0xfdff
00001E0C  B8 00 02                  mov      ax, 0x200
00001E0F  50                        push     ax
00001E10  F7 06 8E 1D 00 02         test     word ptr [0x1d8e], 0x200
00001E16  74 05                     je       0x1e1d
00001E18  B8 01 00                  mov      ax, 1
00001E1B  EB 02                     jmp      0x1e1f
00001E1D  33 C0                     xor      ax, ax
00001E1F  50                        push     ax
00001E20  33 C0                     xor      ax, ax
00001E22  50                        push     ax
00001E23  50                        push     ax
00001E24  1E                        push     ds
00001E25  B8 8C 1D                  mov      ax, 0x1d8c
00001E28  50                        push     ax
00001E29  90                        nop      
00001E2A  0E                        push     cs
00001E2B  E8 64 16                  call     0x3492
00001E2E  83 C4 0C                  add      sp, 0xc
00001E31  A0 A4 1D                  mov      al, byte ptr [0x1da4]
00001E34  98                        cwde     
00001E35  50                        push     ax
00001E36  90                        nop      
00001E37  0E                        push     cs
00001E38  E8 9B 01                  call     0x1fd6
00001E3B  59                        pop      cx
00001E3C  0B C0                     or       ax, ax
00001E3E  75 06                     jne      0x1e46
00001E40  81 26 A2 1D FF FD         and      word ptr [0x1da2], 0xfdff
00001E46  B8 00 02                  mov      ax, 0x200
00001E49  50                        push     ax
00001E4A  F7 06 A2 1D 00 02         test     word ptr [0x1da2], 0x200
00001E50  74 05                     je       0x1e57
00001E52  B8 02 00                  mov      ax, 2
00001E55  EB 02                     jmp      0x1e59
00001E57  33 C0                     xor      ax, ax
00001E59  50                        push     ax
00001E5A  33 C0                     xor      ax, ax
00001E5C  50                        push     ax
00001E5D  50                        push     ax
00001E5E  1E                        push     ds
00001E5F  B8 A0 1D                  mov      ax, 0x1da0
00001E62  50                        push     ax
00001E63  90                        nop      
00001E64  0E                        push     cs
00001E65  E8 2A 16                  call     0x3492
00001E68  83 C4 0C                  add      sp, 0xc
00001E6B  5F                        pop      di
00001E6C  5E                        pop      si
00001E6D  C3                        ret      
00001E6E  56                        push     si
00001E6F  57                        push     di
00001E70  F7 06 8E 1D 04 00         test     word ptr [0x1d8e], 4
00001E76  74 27                     je       0x1e9f
00001E78  1E                        push     ds
00001E79  B8 8C 1D                  mov      ax, 0x1d8c
00001E7C  50                        push     ax
00001E7D  90                        nop      
00001E7E  0E                        push     cs
00001E7F  E8 C9 07                  call     0x264b
00001E82  59                        pop      cx
00001E83  59                        pop      cx
00001E84  FF 36 96 1D               push     word ptr [0x1d96]
00001E88  FF 36 94 1D               push     word ptr [0x1d94]
00001E8C  90                        nop      
00001E8D  0E                        push     cs
00001E8E  E8 B7 27                  call     0x4648
00001E91  59                        pop      cx
00001E92  59                        pop      cx
00001E93  C7 06 8C 1D 00 00         mov      word ptr [0x1d8c], 0
00001E99  C7 06 92 1D 00 00         mov      word ptr [0x1d92], 0
00001E9F  F7 06 A2 1D 04 00         test     word ptr [0x1da2], 4
00001EA5  74 27                     je       0x1ece
00001EA7  1E                        push     ds
00001EA8  B8 A0 1D                  mov      ax, 0x1da0
00001EAB  50                        push     ax
00001EAC  90                        nop      
00001EAD  0E                        push     cs
00001EAE  E8 9A 07                  call     0x264b
00001EB1  59                        pop      cx
00001EB2  59                        pop      cx
00001EB3  FF 36 AA 1D               push     word ptr [0x1daa]
00001EB7  FF 36 A8 1D               push     word ptr [0x1da8]
00001EBB  90                        nop      
00001EBC  0E                        push     cs
00001EBD  E8 88 27                  call     0x4648
00001EC0  59                        pop      cx
00001EC1  59                        pop      cx
00001EC2  C7 06 A0 1D 00 00         mov      word ptr [0x1da0], 0
00001EC8  C7 06 A6 1D 00 00         mov      word ptr [0x1da6], 0
00001ECE  F7 06 DE 1D 04 00         test     word ptr [0x1dde], 4
00001ED4  74 27                     je       0x1efd
00001ED6  1E                        push     ds
00001ED7  B8 DC 1D                  mov      ax, 0x1ddc
00001EDA  50                        push     ax
00001EDB  90                        nop      
00001EDC  0E                        push     cs
00001EDD  E8 6B 07                  call     0x264b
00001EE0  59                        pop      cx
00001EE1  59                        pop      cx
00001EE2  FF 36 E6 1D               push     word ptr [0x1de6]
00001EE6  FF 36 E4 1D               push     word ptr [0x1de4]
00001EEA  90                        nop      
00001EEB  0E                        push     cs
00001EEC  E8 59 27                  call     0x4648
00001EEF  59                        pop      cx
00001EF0  59                        pop      cx
00001EF1  C7 06 DC 1D 00 00         mov      word ptr [0x1ddc], 0
00001EF7  C7 06 E2 1D 00 00         mov      word ptr [0x1de2], 0
00001EFD  F7 06 B6 1D 04 00         test     word ptr [0x1db6], 4
00001F03  74 27                     je       0x1f2c
00001F05  1E                        push     ds
00001F06  B8 B4 1D                  mov      ax, 0x1db4
00001F09  50                        push     ax
00001F0A  90                        nop      
00001F0B  0E                        push     cs
00001F0C  E8 3C 07                  call     0x264b
00001F0F  59                        pop      cx
00001F10  59                        pop      cx
00001F11  FF 36 BE 1D               push     word ptr [0x1dbe]
00001F15  FF 36 BC 1D               push     word ptr [0x1dbc]
00001F19  90                        nop      
00001F1A  0E                        push     cs
00001F1B  E8 2A 27                  call     0x4648
00001F1E  59                        pop      cx
00001F1F  59                        pop      cx
00001F20  C7 06 B4 1D 00 00         mov      word ptr [0x1db4], 0
00001F26  C7 06 BA 1D 00 00         mov      word ptr [0x1dba], 0
00001F2C  5F                        pop      di
00001F2D  5E                        pop      si
00001F2E  C3                        ret      
00001F2F  56                        push     si
00001F30  57                        push     di
00001F31  BA 02 00                  mov      dx, 2
00001F34  EB 0A                     jmp      0x1f40
00001F36  8B DA                     mov      bx, dx
00001F38  03 DB                     add      bx, bx
00001F3A  83 BF 76 21 00            cmp      word ptr [bx + 0x2176], 0
00001F3F  42                        inc      dx
00001F40  3B 16 74 21               cmp      dx, word ptr [0x2174]
00001F44  72 F0                     jb       0x1f36
00001F46  5F                        pop      di
00001F47  5E                        pop      si
00001F48  CB                        retf     
00001F49  55                        push     bp
00001F4A  8B EC                     mov      bp, sp
00001F4C  56                        push     si
00001F4D  57                        push     di
00001F4E  1E                        push     ds
00001F4F  B4 3B                     mov      ah, 0x3b
00001F51  C5 56 06                  lds      dx, ptr [bp + 6]
00001F54  CD 21                     int      0x21
00001F56  1F                        pop      ds
00001F57  72 04                     jb       0x1f5d
00001F59  33 C0                     xor      ax, ax
00001F5B  EB 04                     jmp      0x1f61
00001F5D  50                        push     ax
00001F5E  E8 23 00                  call     0x1f84
00001F61  5F                        pop      di
00001F62  5E                        pop      si
00001F63  5D                        pop      bp
00001F64  CB                        retf     
00001F65  55                        push     bp
00001F66  8B EC                     mov      bp, sp
00001F68  56                        push     si
00001F69  57                        push     di
00001F6A  1E                        push     ds
00001F6B  B4 47                     mov      ah, 0x47
00001F6D  8A 56 06                  mov      dl, byte ptr [bp + 6]
00001F70  C5 76 08                  lds      si, ptr [bp + 8]
00001F73  CD 21                     int      0x21
00001F75  1F                        pop      ds
00001F76  72 04                     jb       0x1f7c
00001F78  33 C0                     xor      ax, ax
00001F7A  EB 04                     jmp      0x1f80
00001F7C  50                        push     ax
00001F7D  E8 04 00                  call     0x1f84
00001F80  5F                        pop      di
00001F81  5E                        pop      si
00001F82  5D                        pop      bp
00001F83  CB                        retf     
00001F84  55                        push     bp
00001F85  8B EC                     mov      bp, sp
00001F87  56                        push     si
00001F88  57                        push     di
00001F89  8B 56 04                  mov      dx, word ptr [bp + 4]
00001F8C  0B D2                     or       dx, dx
00001F8E  7C 17                     jl       0x1fa7
00001F90  83 FA 58                  cmp      dx, 0x58
00001F93  7E 03                     jle      0x1f98
00001F95  BA 57 00                  mov      dx, 0x57
00001F98  89 16 E8 21               mov      word ptr [0x21e8], dx
00001F9C  8B DA                     mov      bx, dx
00001F9E  8A 87 EA 21               mov      al, byte ptr [bx + 0x21ea]
00001FA2  98                        cwde     
00001FA3  8B D0                     mov      dx, ax
00001FA5  EB 0E                     jmp      0x1fb5
00001FA7  F7 DA                     neg      dx
00001FA9  3B 16 6C 23               cmp      dx, word ptr [0x236c]
00001FAD  7F E6                     jg       0x1f95
00001FAF  C7 06 E8 21 FF FF         mov      word ptr [0x21e8], 0xffff
00001FB5  89 16 7E 00               mov      word ptr [0x7e], dx
00001FB9  B8 FF FF                  mov      ax, 0xffff
00001FBC  5F                        pop      di
00001FBD  5E                        pop      si
00001FBE  5D                        pop      bp
00001FBF  C2 02 00                  ret      2
00001FC2  55                        push     bp
00001FC3  8B EC                     mov      bp, sp
00001FC5  56                        push     si
00001FC6  57                        push     di
00001FC7  FF 76 04                  push     word ptr [bp + 4]
00001FCA  E8 B7 FF                  call     0x1f84
00001FCD  8B 46 04                  mov      ax, word ptr [bp + 4]
00001FD0  5F                        pop      di
00001FD1  5E                        pop      si
00001FD2  5D                        pop      bp
00001FD3  C2 02 00                  ret      2
00001FD6  55                        push     bp
00001FD7  8B EC                     mov      bp, sp
00001FD9  56                        push     si
00001FDA  57                        push     di
00001FDB  B8 00 44                  mov      ax, 0x4400
00001FDE  8B 5E 06                  mov      bx, word ptr [bp + 6]
00001FE1  CD 21                     int      0x21
00001FE3  92                        xchg     dx, ax
00001FE4  25 80 00                  and      ax, 0x80
00001FE7  5F                        pop      di
00001FE8  5E                        pop      si
00001FE9  5D                        pop      bp
00001FEA  CB                        retf     
00001FEB  55                        push     bp
00001FEC  8B EC                     mov      bp, sp
00001FEE  56                        push     si
00001FEF  57                        push     di
00001FF0  8B 5E 06                  mov      bx, word ptr [bp + 6]
00001FF3  03 DB                     add      bx, bx
00001FF5  81 A7 76 21 FF FD         and      word ptr [bx + 0x2176], 0xfdff
00001FFB  B4 42                     mov      ah, 0x42
00001FFD  8A 46 0C                  mov      al, byte ptr [bp + 0xc]
00002000  8B 5E 06                  mov      bx, word ptr [bp + 6]
00002003  8B 4E 0A                  mov      cx, word ptr [bp + 0xa]
00002006  8B 56 08                  mov      dx, word ptr [bp + 8]
00002009  CD 21                     int      0x21
0000200B  72 02                     jb       0x200f
0000200D  EB 05                     jmp      0x2014
0000200F  50                        push     ax
00002010  E8 71 FF                  call     0x1f84
00002013  99                        cdq      
00002014  5F                        pop      di
00002015  5E                        pop      si
00002016  5D                        pop      bp
00002017  CB                        retf     
00002018  55                        push     bp
00002019  8B EC                     mov      bp, sp
0000201B  56                        push     si
0000201C  57                        push     di
0000201D  8B 5E 06                  mov      bx, word ptr [bp + 6]
00002020  03 DB                     add      bx, bx
00002022  F7 87 76 21 02 00         test     word ptr [bx + 0x2176], 2
00002028  74 06                     je       0x2030
0000202A  B8 05 00                  mov      ax, 5
0000202D  50                        push     ax
0000202E  EB 14                     jmp      0x2044
00002030  1E                        push     ds
00002031  B4 3F                     mov      ah, 0x3f
00002033  8B 5E 06                  mov      bx, word ptr [bp + 6]
00002036  8B 4E 0C                  mov      cx, word ptr [bp + 0xc]
00002039  C5 56 08                  lds      dx, ptr [bp + 8]
0000203C  CD 21                     int      0x21
0000203E  1F                        pop      ds
0000203F  72 02                     jb       0x2043
00002041  EB 04                     jmp      0x2047
00002043  50                        push     ax
00002044  E8 3D FF                  call     0x1f84
00002047  5F                        pop      di
00002048  5E                        pop      si
00002049  5D                        pop      bp
0000204A  CB                        retf     
0000204B  55                        push     bp
0000204C  8B EC                     mov      bp, sp
0000204E  56                        push     si
0000204F  57                        push     di
00002050  FF 76 0C                  push     word ptr [bp + 0xc]
00002053  FF 76 0A                  push     word ptr [bp + 0xa]
00002056  FF 76 08                  push     word ptr [bp + 8]
00002059  FF 76 06                  push     word ptr [bp + 6]
0000205C  0E                        push     cs
0000205D  E8 B8 FF                  call     0x2018
00002060  83 C4 08                  add      sp, 8
00002063  5F                        pop      di
00002064  5E                        pop      si
00002065  5D                        pop      bp
00002066  CB                        retf     
00002067  55                        push     bp
00002068  8B EC                     mov      bp, sp
0000206A  56                        push     si
0000206B  57                        push     di
0000206C  1E                        push     ds
0000206D  B4 41                     mov      ah, 0x41
0000206F  C5 56 06                  lds      dx, ptr [bp + 6]
00002072  CD 21                     int      0x21
00002074  1F                        pop      ds
00002075  72 04                     jb       0x207b
00002077  33 C0                     xor      ax, ax
00002079  EB 04                     jmp      0x207f
0000207B  50                        push     ax
0000207C  E8 05 FF                  call     0x1f84
0000207F  5F                        pop      di
00002080  5E                        pop      si
00002081  5D                        pop      bp
00002082  CB                        retf     
00002083  8A C6                     mov      al, dh
00002085  E8 02 00                  call     0x208a
00002088  8A C2                     mov      al, dl
0000208A  D4 10                     aam      0x10
0000208C  86 E0                     xchg     al, ah
0000208E  E8 02 00                  call     0x2093
00002091  86 E0                     xchg     al, ah
00002093  04 90                     add      al, 0x90
00002095  27                        daa      
00002096  14 40                     adc      al, 0x40
00002098  27                        daa      
00002099  AA                        stosb    byte ptr es:[di], al
0000209A  C3                        ret      
0000209B  55                        push     bp
0000209C  8B EC                     mov      bp, sp
0000209E  81 EC 96 00               sub      sp, 0x96
000020A2  56                        push     si
000020A3  57                        push     di
000020A4  C7 46 EE 00 00            mov      word ptr [bp - 0x12], 0
000020A9  C7 46 EC 50 00            mov      word ptr [bp - 0x14], 0x50
000020AE  C7 46 EA 00 00            mov      word ptr [bp - 0x16], 0
000020B3  EB 4A                     jmp      0x20ff
000020B5  57                        push     di
000020B6  B9 FF FF                  mov      cx, 0xffff
000020B9  32 C0                     xor      al, al
000020BB  F2 AE                     repne scasb al, byte ptr es:[di]
000020BD  F7 D1                     not      cx
000020BF  49                        dec      cx
000020C0  5F                        pop      di
000020C1  C3                        ret      
000020C2  36 88 05                  mov      byte ptr ss:[di], al
000020C5  47                        inc      di
000020C6  FE 4E EC                  dec      byte ptr [bp - 0x14]
000020C9  75 33                     jne      0x20fe
000020CB  53                        push     bx
000020CC  51                        push     cx
000020CD  52                        push     dx
000020CE  06                        push     es
000020CF  8D 86 6A FF               lea      ax, [bp - 0x96]
000020D3  2B F8                     sub      di, ax
000020D5  16                        push     ss
000020D6  8D 86 6A FF               lea      ax, [bp - 0x96]
000020DA  50                        push     ax
000020DB  57                        push     di
000020DC  FF 76 0C                  push     word ptr [bp + 0xc]
000020DF  FF 76 0A                  push     word ptr [bp + 0xa]
000020E2  FF 56 0E                  call     word ptr [bp + 0xe]
000020E5  0B C0                     or       ax, ax
000020E7  75 05                     jne      0x20ee
000020E9  C7 46 EA 01 00            mov      word ptr [bp - 0x16], 1
000020EE  C7 46 EC 50 00            mov      word ptr [bp - 0x14], 0x50
000020F3  01 7E EE                  add      word ptr [bp - 0x12], di
000020F6  8D BE 6A FF               lea      di, [bp - 0x96]
000020FA  07                        pop      es
000020FB  5A                        pop      dx
000020FC  59                        pop      cx
000020FD  5B                        pop      bx
000020FE  C3                        ret      
000020FF  06                        push     es
00002100  FC                        cld      
00002101  8D BE 6A FF               lea      di, [bp - 0x96]
00002105  89 7E FC                  mov      word ptr [bp - 4], di
00002108  8B 7E FC                  mov      di, word ptr [bp - 4]
0000210B  C4 76 06                  les      si, ptr [bp + 6]
0000210E  26 AC                     lodsb    al, byte ptr es:[si]
00002110  0A C0                     or       al, al
00002112  74 12                     je       0x2126
00002114  3C 25                     cmp      al, 0x25
00002116  74 11                     je       0x2129
00002118  36 88 05                  mov      byte ptr ss:[di], al
0000211B  47                        inc      di
0000211C  FE 4E EC                  dec      byte ptr [bp - 0x14]
0000211F  7F ED                     jg       0x210e
00002121  E8 A7 FF                  call     0x20cb
00002124  EB E8                     jmp      0x210e
00002126  E9 E5 03                  jmp      0x250e
00002129  89 76 F0                  mov      word ptr [bp - 0x10], si
0000212C  26 AC                     lodsb    al, byte ptr es:[si]
0000212E  3C 25                     cmp      al, 0x25
00002130  74 E6                     je       0x2118
00002132  89 7E FC                  mov      word ptr [bp - 4], di
00002135  33 C9                     xor      cx, cx
00002137  89 4E F2                  mov      word ptr [bp - 0xe], cx
0000213A  C7 46 FE 20 00            mov      word ptr [bp - 2], 0x20
0000213F  88 4E F5                  mov      byte ptr [bp - 0xb], cl
00002142  C7 46 F8 FF FF            mov      word ptr [bp - 8], 0xffff
00002147  C7 46 F6 FF FF            mov      word ptr [bp - 0xa], 0xffff
0000214C  EB 02                     jmp      0x2150
0000214E  26 AC                     lodsb    al, byte ptr es:[si]
00002150  32 E4                     xor      ah, ah
00002152  8B D0                     mov      dx, ax
00002154  8B D8                     mov      bx, ax
00002156  80 EB 20                  sub      bl, 0x20
00002159  80 FB 60                  cmp      bl, 0x60
0000215C  73 13                     jae      0x2171
0000215E  8A 9F 4B 22               mov      bl, byte ptr [bx + 0x224b]
00002162  83 FB 17                  cmp      bx, 0x17
00002165  76 03                     jbe      0x216a
00002167  E9 90 03                  jmp      0x24fa
0000216A  03 DB                     add      bx, bx
0000216C  2E FF A7 2E 25            jmp      word ptr cs:[bx + 0x252e]
00002171  E9 86 03                  jmp      0x24fa
00002174  80 FD 00                  cmp      ch, 0
00002177  77 F8                     ja       0x2171
00002179  83 4E FE 01               or       word ptr [bp - 2], 1
0000217D  EB CF                     jmp      0x214e
0000217F  80 FD 00                  cmp      ch, 0
00002182  77 ED                     ja       0x2171
00002184  83 4E FE 02               or       word ptr [bp - 2], 2
00002188  EB C4                     jmp      0x214e
0000218A  80 FD 00                  cmp      ch, 0
0000218D  77 E2                     ja       0x2171
0000218F  80 7E F5 2B               cmp      byte ptr [bp - 0xb], 0x2b
00002193  74 03                     je       0x2198
00002195  88 56 F5                  mov      byte ptr [bp - 0xb], dl
00002198  EB B4                     jmp      0x214e
0000219A  83 66 FE DF               and      word ptr [bp - 2], 0xffdf
0000219E  EB 04                     jmp      0x21a4
000021A0  83 4E FE 20               or       word ptr [bp - 2], 0x20
000021A4  B5 05                     mov      ch, 5
000021A6  EB A6                     jmp      0x214e
000021A8  80 FD 00                  cmp      ch, 0
000021AB  77 4D                     ja       0x21fa
000021AD  F7 46 FE 02 00            test     word ptr [bp - 2], 2
000021B2  75 29                     jne      0x21dd
000021B4  83 4E FE 08               or       word ptr [bp - 2], 8
000021B8  B5 01                     mov      ch, 1
000021BA  EB 92                     jmp      0x214e
000021BC  E9 3B 03                  jmp      0x24fa
000021BF  8B 7E 04                  mov      di, word ptr [bp + 4]
000021C2  36 8B 05                  mov      ax, word ptr ss:[di]
000021C5  83 46 04 02               add      word ptr [bp + 4], 2
000021C9  80 FD 02                  cmp      ch, 2
000021CC  73 12                     jae      0x21e0
000021CE  0B C0                     or       ax, ax
000021D0  79 06                     jns      0x21d8
000021D2  F7 D8                     neg      ax
000021D4  83 4E FE 02               or       word ptr [bp - 2], 2
000021D8  89 46 F8                  mov      word ptr [bp - 8], ax
000021DB  B5 03                     mov      ch, 3
000021DD  E9 6E FF                  jmp      0x214e
000021E0  80 FD 04                  cmp      ch, 4
000021E3  75 D7                     jne      0x21bc
000021E5  89 46 F6                  mov      word ptr [bp - 0xa], ax
000021E8  FE C5                     inc      ch
000021EA  E9 61 FF                  jmp      0x214e
000021ED  80 FD 04                  cmp      ch, 4
000021F0  73 CA                     jae      0x21bc
000021F2  B5 04                     mov      ch, 4
000021F4  FF 46 F6                  inc      word ptr [bp - 0xa]
000021F7  E9 54 FF                  jmp      0x214e
000021FA  92                        xchg     dx, ax
000021FB  2C 30                     sub      al, 0x30
000021FD  98                        cwde     
000021FE  80 FD 02                  cmp      ch, 2
00002201  77 19                     ja       0x221c
00002203  B5 02                     mov      ch, 2
00002205  87 46 F8                  xchg     word ptr [bp - 8], ax
00002208  0B C0                     or       ax, ax
0000220A  7C D1                     jl       0x21dd
0000220C  D1 E0                     shl      ax, 1
0000220E  8B D0                     mov      dx, ax
00002210  D1 E0                     shl      ax, 1
00002212  D1 E0                     shl      ax, 1
00002214  03 C2                     add      ax, dx
00002216  01 46 F8                  add      word ptr [bp - 8], ax
00002219  E9 32 FF                  jmp      0x214e
0000221C  80 FD 04                  cmp      ch, 4
0000221F  75 9B                     jne      0x21bc
00002221  87 46 F6                  xchg     word ptr [bp - 0xa], ax
00002224  0B C0                     or       ax, ax
00002226  74 B5                     je       0x21dd
00002228  D1 E0                     shl      ax, 1
0000222A  8B D0                     mov      dx, ax
0000222C  D1 E0                     shl      ax, 1
0000222E  D1 E0                     shl      ax, 1
00002230  03 C2                     add      ax, dx
00002232  01 46 F6                  add      word ptr [bp - 0xa], ax
00002235  E9 16 FF                  jmp      0x214e
00002238  83 4E FE 10               or       word ptr [bp - 2], 0x10
0000223C  E9 65 FF                  jmp      0x21a4
0000223F  81 4E FE 00 01            or       word ptr [bp - 2], 0x100
00002244  83 66 FE EF               and      word ptr [bp - 2], 0xffef
00002248  E9 59 FF                  jmp      0x21a4
0000224B  B7 08                     mov      bh, 8
0000224D  EB 0A                     jmp      0x2259
0000224F  B7 0A                     mov      bh, 0xa
00002251  EB 06                     jmp      0x2259
00002253  B7 10                     mov      bh, 0x10
00002255  B3 E9                     mov      bl, 0xe9
00002257  02 DA                     add      bl, dl
00002259  C6 46 F5 00               mov      byte ptr [bp - 0xb], 0
0000225D  88 56 FB                  mov      byte ptr [bp - 5], dl
00002260  33 D2                     xor      dx, dx
00002262  88 56 FA                  mov      byte ptr [bp - 6], dl
00002265  8B 7E 04                  mov      di, word ptr [bp + 4]
00002268  36 8B 05                  mov      ax, word ptr ss:[di]
0000226B  EB 10                     jmp      0x227d
0000226D  B7 0A                     mov      bh, 0xa
0000226F  C6 46 FA 01               mov      byte ptr [bp - 6], 1
00002273  88 56 FB                  mov      byte ptr [bp - 5], dl
00002276  8B 7E 04                  mov      di, word ptr [bp + 4]
00002279  36 8B 05                  mov      ax, word ptr ss:[di]
0000227C  99                        cdq      
0000227D  47                        inc      di
0000227E  47                        inc      di
0000227F  89 76 06                  mov      word ptr [bp + 6], si
00002282  F7 46 FE 10 00            test     word ptr [bp - 2], 0x10
00002287  74 05                     je       0x228e
00002289  36 8B 15                  mov      dx, word ptr ss:[di]
0000228C  47                        inc      di
0000228D  47                        inc      di
0000228E  89 7E 04                  mov      word ptr [bp + 4], di
00002291  8D 7E BB                  lea      di, [bp - 0x45]
00002294  0B C0                     or       ax, ax
00002296  75 12                     jne      0x22aa
00002298  0B D2                     or       dx, dx
0000229A  75 0E                     jne      0x22aa
0000229C  83 7E F6 00               cmp      word ptr [bp - 0xa], 0
000022A0  75 0C                     jne      0x22ae
000022A2  36 C6 05 00               mov      byte ptr ss:[di], 0
000022A6  8B C7                     mov      ax, di
000022A8  EB 14                     jmp      0x22be
000022AA  83 4E FE 04               or       word ptr [bp - 2], 4
000022AE  52                        push     dx
000022AF  50                        push     ax
000022B0  16                        push     ss
000022B1  57                        push     di
000022B2  8A C7                     mov      al, bh
000022B4  98                        cwde     
000022B5  50                        push     ax
000022B6  8A 46 FA                  mov      al, byte ptr [bp - 6]
000022B9  50                        push     ax
000022BA  53                        push     bx
000022BB  E8 F1 1C                  call     0x3faf
000022BE  16                        push     ss
000022BF  07                        pop      es
000022C0  8B 56 F6                  mov      dx, word ptr [bp - 0xa]
000022C3  0B D2                     or       dx, dx
000022C5  7D 03                     jge      0x22ca
000022C7  E9 F4 00                  jmp      0x23be
000022CA  E9 FF 00                  jmp      0x23cc
000022CD  88 56 FB                  mov      byte ptr [bp - 5], dl
000022D0  89 76 06                  mov      word ptr [bp + 6], si
000022D3  8D 7E BA                  lea      di, [bp - 0x46]
000022D6  8B 5E 04                  mov      bx, word ptr [bp + 4]
000022D9  36 FF 37                  push     word ptr ss:[bx]
000022DC  43                        inc      bx
000022DD  43                        inc      bx
000022DE  89 5E 04                  mov      word ptr [bp + 4], bx
000022E1  F7 46 FE 20 00            test     word ptr [bp - 2], 0x20
000022E6  74 10                     je       0x22f8
000022E8  36 8B 17                  mov      dx, word ptr ss:[bx]
000022EB  43                        inc      bx
000022EC  43                        inc      bx
000022ED  89 5E 04                  mov      word ptr [bp + 4], bx
000022F0  16                        push     ss
000022F1  07                        pop      es
000022F2  E8 8E FD                  call     0x2083
000022F5  B0 3A                     mov      al, 0x3a
000022F7  AA                        stosb    byte ptr es:[di], al
000022F8  16                        push     ss
000022F9  07                        pop      es
000022FA  5A                        pop      dx
000022FB  E8 85 FD                  call     0x2083
000022FE  36 C6 05 00               mov      byte ptr ss:[di], 0
00002302  C6 46 FA 00               mov      byte ptr [bp - 6], 0
00002306  83 66 FE FB               and      word ptr [bp - 2], 0xfffb
0000230A  8D 4E BA                  lea      cx, [bp - 0x46]
0000230D  2B F9                     sub      di, cx
0000230F  87 CF                     xchg     di, cx
00002311  8B 56 F6                  mov      dx, word ptr [bp - 0xa]
00002314  3B D1                     cmp      dx, cx
00002316  7F 02                     jg       0x231a
00002318  8B D1                     mov      dx, cx
0000231A  E9 A1 00                  jmp      0x23be
0000231D  89 76 06                  mov      word ptr [bp + 6], si
00002320  88 56 FB                  mov      byte ptr [bp - 5], dl
00002323  8B 7E 04                  mov      di, word ptr [bp + 4]
00002326  36 8B 05                  mov      ax, word ptr ss:[di]
00002329  83 46 04 02               add      word ptr [bp + 4], 2
0000232D  16                        push     ss
0000232E  07                        pop      es
0000232F  8D 7E BB                  lea      di, [bp - 0x45]
00002332  32 E4                     xor      ah, ah
00002334  36 89 05                  mov      word ptr ss:[di], ax
00002337  B9 01 00                  mov      cx, 1
0000233A  E9 C4 00                  jmp      0x2401
0000233D  89 76 06                  mov      word ptr [bp + 6], si
00002340  88 56 FB                  mov      byte ptr [bp - 5], dl
00002343  8B 7E 04                  mov      di, word ptr [bp + 4]
00002346  F7 46 FE 20 00            test     word ptr [bp - 2], 0x20
0000234B  75 0D                     jne      0x235a
0000234D  36 8B 3D                  mov      di, word ptr ss:[di]
00002350  83 46 04 02               add      word ptr [bp + 4], 2
00002354  1E                        push     ds
00002355  07                        pop      es
00002356  0B FF                     or       di, di
00002358  EB 0B                     jmp      0x2365
0000235A  36 C4 3D                  les      di, ptr ss:[di]
0000235D  83 46 04 04               add      word ptr [bp + 4], 4
00002361  8C C0                     mov      ax, es
00002363  0B C7                     or       ax, di
00002365  75 05                     jne      0x236c
00002367  1E                        push     ds
00002368  07                        pop      es
00002369  BF 44 22                  mov      di, 0x2244
0000236C  E8 46 FD                  call     0x20b5
0000236F  3B 4E F6                  cmp      cx, word ptr [bp - 0xa]
00002372  76 03                     jbe      0x2377
00002374  8B 4E F6                  mov      cx, word ptr [bp - 0xa]
00002377  E9 87 00                  jmp      0x2401
0000237A  89 76 06                  mov      word ptr [bp + 6], si
0000237D  88 56 FB                  mov      byte ptr [bp - 5], dl
00002380  8B 7E 04                  mov      di, word ptr [bp + 4]
00002383  8B 4E F6                  mov      cx, word ptr [bp - 0xa]
00002386  0B C9                     or       cx, cx
00002388  7D 03                     jge      0x238d
0000238A  B9 06 00                  mov      cx, 6
0000238D  16                        push     ss
0000238E  57                        push     di
0000238F  51                        push     cx
00002390  16                        push     ss
00002391  8D 5E BB                  lea      bx, [bp - 0x45]
00002394  53                        push     bx
00002395  52                        push     dx
00002396  B8 01 00                  mov      ax, 1
00002399  23 46 FE                  and      ax, word ptr [bp - 2]
0000239C  50                        push     ax
0000239D  8B 46 FE                  mov      ax, word ptr [bp - 2]
000023A0  A9 00 01                  test     ax, 0x100
000023A3  74 09                     je       0x23ae
000023A5  B8 08 00                  mov      ax, 8
000023A8  83 46 04 0A               add      word ptr [bp + 4], 0xa
000023AC  EB 07                     jmp      0x23b5
000023AE  83 46 04 08               add      word ptr [bp + 4], 8
000023B2  B8 06 00                  mov      ax, 6
000023B5  50                        push     ax
000023B6  E8 C1 1D                  call     0x417a
000023B9  16                        push     ss
000023BA  07                        pop      es
000023BB  8D 7E BB                  lea      di, [bp - 0x45]
000023BE  F7 46 FE 08 00            test     word ptr [bp - 2], 8
000023C3  74 18                     je       0x23dd
000023C5  8B 56 F8                  mov      dx, word ptr [bp - 8]
000023C8  0B D2                     or       dx, dx
000023CA  7E 11                     jle      0x23dd
000023CC  E8 E6 FC                  call     0x20b5
000023CF  26 80 3D 2D               cmp      byte ptr es:[di], 0x2d
000023D3  75 01                     jne      0x23d6
000023D5  49                        dec      cx
000023D6  2B D1                     sub      dx, cx
000023D8  7E 03                     jle      0x23dd
000023DA  89 56 F2                  mov      word ptr [bp - 0xe], dx
000023DD  26 80 3D 2D               cmp      byte ptr es:[di], 0x2d
000023E1  74 0B                     je       0x23ee
000023E3  8A 46 F5                  mov      al, byte ptr [bp - 0xb]
000023E6  0A C0                     or       al, al
000023E8  74 14                     je       0x23fe
000023EA  4F                        dec      di
000023EB  26 88 05                  mov      byte ptr es:[di], al
000023EE  83 7E F2 00               cmp      word ptr [bp - 0xe], 0
000023F2  7E 0A                     jle      0x23fe
000023F4  8B 4E F6                  mov      cx, word ptr [bp - 0xa]
000023F7  0B C9                     or       cx, cx
000023F9  7D 03                     jge      0x23fe
000023FB  FF 4E F2                  dec      word ptr [bp - 0xe]
000023FE  E8 B4 FC                  call     0x20b5
00002401  8B F7                     mov      si, di
00002403  8B 7E FC                  mov      di, word ptr [bp - 4]
00002406  8B 5E F8                  mov      bx, word ptr [bp - 8]
00002409  B8 05 00                  mov      ax, 5
0000240C  23 46 FE                  and      ax, word ptr [bp - 2]
0000240F  3D 05 00                  cmp      ax, 5
00002412  75 13                     jne      0x2427
00002414  8A 66 FB                  mov      ah, byte ptr [bp - 5]
00002417  80 FC 6F                  cmp      ah, 0x6f
0000241A  75 0D                     jne      0x2429
0000241C  83 7E F2 00               cmp      word ptr [bp - 0xe], 0
00002420  7F 05                     jg       0x2427
00002422  C7 46 F2 01 00            mov      word ptr [bp - 0xe], 1
00002427  EB 1B                     jmp      0x2444
00002429  80 FC 78                  cmp      ah, 0x78
0000242C  74 05                     je       0x2433
0000242E  80 FC 58                  cmp      ah, 0x58
00002431  75 11                     jne      0x2444
00002433  83 4E FE 40               or       word ptr [bp - 2], 0x40
00002437  4B                        dec      bx
00002438  4B                        dec      bx
00002439  83 6E F2 02               sub      word ptr [bp - 0xe], 2
0000243D  7D 05                     jge      0x2444
0000243F  C7 46 F2 00 00            mov      word ptr [bp - 0xe], 0
00002444  03 4E F2                  add      cx, word ptr [bp - 0xe]
00002447  F7 46 FE 02 00            test     word ptr [bp - 2], 2
0000244C  75 0C                     jne      0x245a
0000244E  EB 06                     jmp      0x2456
00002450  B0 20                     mov      al, 0x20
00002452  E8 6D FC                  call     0x20c2
00002455  4B                        dec      bx
00002456  3B D9                     cmp      bx, cx
00002458  7F F6                     jg       0x2450
0000245A  F7 46 FE 40 00            test     word ptr [bp - 2], 0x40
0000245F  74 0B                     je       0x246c
00002461  B0 30                     mov      al, 0x30
00002463  E8 5C FC                  call     0x20c2
00002466  8A 46 FB                  mov      al, byte ptr [bp - 5]
00002469  E8 56 FC                  call     0x20c2
0000246C  8B 56 F2                  mov      dx, word ptr [bp - 0xe]
0000246F  0B D2                     or       dx, dx
00002471  7E 27                     jle      0x249a
00002473  2B CA                     sub      cx, dx
00002475  2B DA                     sub      bx, dx
00002477  26 8A 04                  mov      al, byte ptr es:[si]
0000247A  3C 2D                     cmp      al, 0x2d
0000247C  74 08                     je       0x2486
0000247E  3C 20                     cmp      al, 0x20
00002480  74 04                     je       0x2486
00002482  3C 2B                     cmp      al, 0x2b
00002484  75 07                     jne      0x248d
00002486  26 AC                     lodsb    al, byte ptr es:[si]
00002488  E8 37 FC                  call     0x20c2
0000248B  49                        dec      cx
0000248C  4B                        dec      bx
0000248D  87 CA                     xchg     dx, cx
0000248F  E3 07                     jcxz     0x2498
00002491  B0 30                     mov      al, 0x30
00002493  E8 2C FC                  call     0x20c2
00002496  E2 F9                     loop     0x2491
00002498  87 CA                     xchg     dx, cx
0000249A  E3 12                     jcxz     0x24ae
0000249C  2B D9                     sub      bx, cx
0000249E  26 AC                     lodsb    al, byte ptr es:[si]
000024A0  36 88 05                  mov      byte ptr ss:[di], al
000024A3  47                        inc      di
000024A4  FE 4E EC                  dec      byte ptr [bp - 0x14]
000024A7  7F 03                     jg       0x24ac
000024A9  E8 1F FC                  call     0x20cb
000024AC  E2 F0                     loop     0x249e
000024AE  0B DB                     or       bx, bx
000024B0  7E 09                     jle      0x24bb
000024B2  8B CB                     mov      cx, bx
000024B4  B0 20                     mov      al, 0x20
000024B6  E8 09 FC                  call     0x20c2
000024B9  E2 F9                     loop     0x24b4
000024BB  E9 4D FC                  jmp      0x210b
000024BE  89 76 06                  mov      word ptr [bp + 6], si
000024C1  8B 7E 04                  mov      di, word ptr [bp + 4]
000024C4  F7 46 FE 20 00            test     word ptr [bp - 2], 0x20
000024C9  75 0B                     jne      0x24d6
000024CB  36 8B 3D                  mov      di, word ptr ss:[di]
000024CE  83 46 04 02               add      word ptr [bp + 4], 2
000024D2  1E                        push     ds
000024D3  07                        pop      es
000024D4  EB 07                     jmp      0x24dd
000024D6  36 C4 3D                  les      di, ptr ss:[di]
000024D9  83 46 04 04               add      word ptr [bp + 4], 4
000024DD  B8 50 00                  mov      ax, 0x50
000024E0  2A 46 EC                  sub      al, byte ptr [bp - 0x14]
000024E3  03 46 EE                  add      ax, word ptr [bp - 0x12]
000024E6  26 89 05                  mov      word ptr es:[di], ax
000024E9  F7 46 FE 10 00            test     word ptr [bp - 2], 0x10
000024EE  74 07                     je       0x24f7
000024F0  47                        inc      di
000024F1  47                        inc      di
000024F2  26 C7 05 00 00            mov      word ptr es:[di], 0
000024F7  E9 0E FC                  jmp      0x2108
000024FA  8B 76 F0                  mov      si, word ptr [bp - 0x10]
000024FD  8E 46 08                  mov      es, word ptr [bp + 8]
00002500  8B 7E FC                  mov      di, word ptr [bp - 4]
00002503  B0 25                     mov      al, 0x25
00002505  E8 BA FB                  call     0x20c2
00002508  26 AC                     lodsb    al, byte ptr es:[si]
0000250A  0A C0                     or       al, al
0000250C  75 F7                     jne      0x2505
0000250E  80 7E EC 50               cmp      byte ptr [bp - 0x14], 0x50
00002512  7D 03                     jge      0x2517
00002514  E8 B4 FB                  call     0x20cb
00002517  07                        pop      es
00002518  83 7E EA 00               cmp      word ptr [bp - 0x16], 0
0000251C  74 05                     je       0x2523
0000251E  B8 FF FF                  mov      ax, 0xffff
00002521  EB 03                     jmp      0x2526
00002523  8B 46 EE                  mov      ax, word ptr [bp - 0x12]
00002526  5F                        pop      di
00002527  5E                        pop      si
00002528  8B E5                     mov      sp, bp
0000252A  5D                        pop      bp
0000252B  C2 0C 00                  ret      0xc
0000252E  8A 21                     mov      ah, byte ptr [bx + di]
00002530  74 21                     je       0x2553
00002532  BF 21 7F                  mov      di, 0x7f21
00002535  21 ED                     and      bp, bp
00002537  21 FA                     and      dx, di
00002539  21 38                     and      word ptr [bx + si], di
0000253B  22 3F                     and      bh, byte ptr [bx]
0000253D  22 44 22                  and      al, byte ptr [si + 0x22]
00002540  A8 21                     test     al, 0x21
00002542  6D                        insw     word ptr es:[di], dx
00002543  22 4B 22                  and      cl, byte ptr [bp + di + 0x22]
00002546  4F                        dec      di
00002547  22 53 22                  and      dl, byte ptr [bp + di + 0x22]
0000254A  CD 22                     int      0x22
0000254C  7A 23                     jp       0x2571
0000254E  1D 23 3D                  sbb      ax, 0x3d23
00002551  23 BE 24 FA               and      di, word ptr [bp - 0x5dc]
00002555  24 FA                     and      al, 0xfa
00002557  24 FA                     and      al, 0xfa
00002559  24 9A                     and      al, 0x9a
0000255B  21 A0 21 55               and      word ptr [bx + si + 0x5521], sp
0000255F  8B EC                     mov      bp, sp
00002561  56                        push     si
00002562  57                        push     di
00002563  8B 56 06                  mov      dx, word ptr [bp + 6]
00002566  3B 16 74 21               cmp      dx, word ptr [0x2174]
0000256A  72 09                     jb       0x2575
0000256C  B8 06 00                  mov      ax, 6
0000256F  50                        push     ax
00002570  E8 11 FA                  call     0x1f84
00002573  EB 11                     jmp      0x2586
00002575  8B DA                     mov      bx, dx
00002577  03 DB                     add      bx, bx
00002579  C7 87 76 21 00 00         mov      word ptr [bx + 0x2176], 0
0000257F  52                        push     dx
00002580  90                        nop      
00002581  0E                        push     cs
00002582  E8 50 12                  call     0x37d5
00002585  59                        pop      cx
00002586  5F                        pop      di
00002587  5E                        pop      si
00002588  5D                        pop      bp
00002589  CB                        retf     
0000258A  55                        push     bp
0000258B  8B EC                     mov      bp, sp
0000258D  83 EC 02                  sub      sp, 2
00002590  56                        push     si
00002591  57                        push     di
00002592  C7 46 FE FF FF            mov      word ptr [bp - 2], 0xffff
00002597  8B 46 06                  mov      ax, word ptr [bp + 6]
0000259A  0B 46 08                  or       ax, word ptr [bp + 8]
0000259D  75 03                     jne      0x25a2
0000259F  E9 A0 00                  jmp      0x2642
000025A2  C4 5E 06                  les      bx, ptr [bp + 6]
000025A5  26 8B 47 12               mov      ax, word ptr es:[bx + 0x12]
000025A9  3B 46 06                  cmp      ax, word ptr [bp + 6]
000025AC  74 03                     je       0x25b1
000025AE  E9 91 00                  jmp      0x2642
000025B1  C4 5E 06                  les      bx, ptr [bp + 6]
000025B4  26 83 7F 06 00            cmp      word ptr es:[bx + 6], 0
000025B9  74 2F                     je       0x25ea
000025BB  26 83 3F 00               cmp      word ptr es:[bx], 0
000025BF  7D 0F                     jge      0x25d0
000025C1  FF 76 08                  push     word ptr [bp + 8]
000025C4  53                        push     bx
000025C5  90                        nop      
000025C6  0E                        push     cs
000025C7  E8 81 00                  call     0x264b
000025CA  59                        pop      cx
000025CB  59                        pop      cx
000025CC  0B C0                     or       ax, ax
000025CE  75 72                     jne      0x2642
000025D0  C4 5E 06                  les      bx, ptr [bp + 6]
000025D3  26 F7 47 02 04 00         test     word ptr es:[bx + 2], 4
000025D9  74 0F                     je       0x25ea
000025DB  26 FF 77 0A               push     word ptr es:[bx + 0xa]
000025DF  26 FF 77 08               push     word ptr es:[bx + 8]
000025E3  90                        nop      
000025E4  0E                        push     cs
000025E5  E8 60 20                  call     0x4648
000025E8  59                        pop      cx
000025E9  59                        pop      cx
000025EA  C4 5E 06                  les      bx, ptr [bp + 6]
000025ED  26 80 7F 04 00            cmp      byte ptr es:[bx + 4], 0
000025F2  7C 0F                     jl       0x2603
000025F4  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
000025F8  98                        cwde     
000025F9  50                        push     ax
000025FA  90                        nop      
000025FB  0E                        push     cs
000025FC  E8 5F FF                  call     0x255e
000025FF  59                        pop      cx
00002600  89 46 FE                  mov      word ptr [bp - 2], ax
00002603  C4 5E 06                  les      bx, ptr [bp + 6]
00002606  26 C7 47 02 00 00         mov      word ptr es:[bx + 2], 0
0000260C  26 C7 47 06 00 00         mov      word ptr es:[bx + 6], 0
00002612  26 C7 07 00 00            mov      word ptr es:[bx], 0
00002617  26 C6 47 04 FF            mov      byte ptr es:[bx + 4], 0xff
0000261C  26 83 7F 10 00            cmp      word ptr es:[bx + 0x10], 0
00002621  74 1F                     je       0x2642
00002623  33 C0                     xor      ax, ax
00002625  50                        push     ax
00002626  50                        push     ax
00002627  50                        push     ax
00002628  50                        push     ax
00002629  26 FF 77 10               push     word ptr es:[bx + 0x10]
0000262D  E8 35 F7                  call     0x1d65
00002630  52                        push     dx
00002631  50                        push     ax
00002632  90                        nop      
00002633  0E                        push     cs
00002634  E8 30 FA                  call     0x2067
00002637  59                        pop      cx
00002638  59                        pop      cx
00002639  C4 5E 06                  les      bx, ptr [bp + 6]
0000263C  26 C7 47 10 00 00         mov      word ptr es:[bx + 0x10], 0
00002642  8B 46 FE                  mov      ax, word ptr [bp - 2]
00002645  5F                        pop      di
00002646  5E                        pop      si
00002647  8B E5                     mov      sp, bp
00002649  5D                        pop      bp
0000264A  CB                        retf     
0000264B  55                        push     bp
0000264C  8B EC                     mov      bp, sp
0000264E  83 EC 02                  sub      sp, 2
00002651  56                        push     si
00002652  57                        push     di
00002653  8B 46 06                  mov      ax, word ptr [bp + 6]
00002656  0B 46 08                  or       ax, word ptr [bp + 8]
00002659  75 08                     jne      0x2663
0000265B  90                        nop      
0000265C  0E                        push     cs
0000265D  E8 C0 01                  call     0x2820
00002660  E9 BB 00                  jmp      0x271e
00002663  C4 5E 06                  les      bx, ptr [bp + 6]
00002666  26 8B 47 12               mov      ax, word ptr es:[bx + 0x12]
0000266A  3B 46 06                  cmp      ax, word ptr [bp + 6]
0000266D  74 03                     je       0x2672
0000266F  E9 A7 00                  jmp      0x2719
00002672  C4 5E 06                  les      bx, ptr [bp + 6]
00002675  26 83 3F 00               cmp      word ptr es:[bx], 0
00002679  7C 52                     jl       0x26cd
0000267B  26 F7 47 02 08 00         test     word ptr es:[bx + 2], 8
00002681  75 1B                     jne      0x269e
00002683  26 8B 57 0E               mov      dx, word ptr es:[bx + 0xe]
00002687  8B 46 06                  mov      ax, word ptr [bp + 6]
0000268A  05 05 00                  add      ax, 5
0000268D  3B 56 08                  cmp      dx, word ptr [bp + 8]
00002690  74 03                     je       0x2695
00002692  E9 89 00                  jmp      0x271e
00002695  26 39 47 0C               cmp      word ptr es:[bx + 0xc], ax
00002699  74 03                     je       0x269e
0000269B  E9 80 00                  jmp      0x271e
0000269E  C4 5E 06                  les      bx, ptr [bp + 6]
000026A1  26 C7 07 00 00            mov      word ptr es:[bx], 0
000026A6  26 8B 57 0E               mov      dx, word ptr es:[bx + 0xe]
000026AA  8B 46 06                  mov      ax, word ptr [bp + 6]
000026AD  05 05 00                  add      ax, 5
000026B0  3B 56 08                  cmp      dx, word ptr [bp + 8]
000026B3  75 69                     jne      0x271e
000026B5  26 39 47 0C               cmp      word ptr es:[bx + 0xc], ax
000026B9  75 63                     jne      0x271e
000026BB  26 8B 57 0A               mov      dx, word ptr es:[bx + 0xa]
000026BF  26 8B 47 08               mov      ax, word ptr es:[bx + 8]
000026C3  26 89 57 0E               mov      word ptr es:[bx + 0xe], dx
000026C7  26 89 47 0C               mov      word ptr es:[bx + 0xc], ax
000026CB  EB 51                     jmp      0x271e
000026CD  C4 5E 06                  les      bx, ptr [bp + 6]
000026D0  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
000026D4  26 03 07                  add      ax, word ptr es:[bx]
000026D7  40                        inc      ax
000026D8  89 46 FE                  mov      word ptr [bp - 2], ax
000026DB  26 29 07                  sub      word ptr es:[bx], ax
000026DE  FF 76 FE                  push     word ptr [bp - 2]
000026E1  8B 5E 06                  mov      bx, word ptr [bp + 6]
000026E4  26 8B 57 0A               mov      dx, word ptr es:[bx + 0xa]
000026E8  26 8B 47 08               mov      ax, word ptr es:[bx + 8]
000026EC  26 89 57 0E               mov      word ptr es:[bx + 0xe], dx
000026F0  26 89 47 0C               mov      word ptr es:[bx + 0xc], ax
000026F4  52                        push     dx
000026F5  50                        push     ax
000026F6  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
000026FA  98                        cwde     
000026FB  50                        push     ax
000026FC  90                        nop      
000026FD  0E                        push     cs
000026FE  E8 B6 0E                  call     0x35b7
00002701  83 C4 08                  add      sp, 8
00002704  3B 46 FE                  cmp      ax, word ptr [bp - 2]
00002707  74 15                     je       0x271e
00002709  C4 5E 06                  les      bx, ptr [bp + 6]
0000270C  26 F7 47 02 00 02         test     word ptr es:[bx + 2], 0x200
00002712  75 0A                     jne      0x271e
00002714  26 83 4F 02 10            or       word ptr es:[bx + 2], 0x10
00002719  B8 FF FF                  mov      ax, 0xffff
0000271C  EB 02                     jmp      0x2720
0000271E  33 C0                     xor      ax, ax
00002720  5F                        pop      di
00002721  5E                        pop      si
00002722  8B E5                     mov      sp, bp
00002724  5D                        pop      bp
00002725  CB                        retf     
00002726  55                        push     bp
00002727  8B EC                     mov      bp, sp
00002729  83 EC 04                  sub      sp, 4
0000272C  56                        push     si
0000272D  57                        push     di
0000272E  33 C9                     xor      cx, cx
00002730  8B 56 08                  mov      dx, word ptr [bp + 8]
00002733  8B 46 06                  mov      ax, word ptr [bp + 6]
00002736  89 56 FE                  mov      word ptr [bp - 2], dx
00002739  89 46 FC                  mov      word ptr [bp - 4], ax
0000273C  EB 09                     jmp      0x2747
0000273E  C4 5E FC                  les      bx, ptr [bp - 4]
00002741  26 88 0F                  mov      byte ptr es:[bx], cl
00002744  FF 46 FC                  inc      word ptr [bp - 4]
00002747  83 F9 0A                  cmp      cx, 0xa
0000274A  74 39                     je       0x2785
0000274C  FF 4E 0A                  dec      word ptr [bp + 0xa]
0000274F  7E 34                     jle      0x2785
00002751  C4 5E 0C                  les      bx, ptr [bp + 0xc]
00002754  26 FF 0F                  dec      word ptr es:[bx]
00002757  7C 18                     jl       0x2771
00002759  8B 5E 0C                  mov      bx, word ptr [bp + 0xc]
0000275C  26 8B 57 0E               mov      dx, word ptr es:[bx + 0xe]
00002760  26 8B 77 0C               mov      si, word ptr es:[bx + 0xc]
00002764  26 FF 47 0C               inc      word ptr es:[bx + 0xc]
00002768  8E C2                     mov      es, dx
0000276A  26 8A 04                  mov      al, byte ptr es:[si]
0000276D  B4 00                     mov      ah, 0
0000276F  EB 0D                     jmp      0x277e
00002771  FF 76 0E                  push     word ptr [bp + 0xe]
00002774  FF 76 0C                  push     word ptr [bp + 0xc]
00002777  90                        nop      
00002778  0E                        push     cs
00002779  E8 33 12                  call     0x39af
0000277C  59                        pop      cx
0000277D  59                        pop      cx
0000277E  8B C8                     mov      cx, ax
00002780  3D FF FF                  cmp      ax, 0xffff
00002783  75 B9                     jne      0x273e
00002785  83 F9 FF                  cmp      cx, -1
00002788  75 16                     jne      0x27a0
0000278A  8B 56 FE                  mov      dx, word ptr [bp - 2]
0000278D  8B 46 FC                  mov      ax, word ptr [bp - 4]
00002790  3B 56 08                  cmp      dx, word ptr [bp + 8]
00002793  75 0B                     jne      0x27a0
00002795  3B 46 06                  cmp      ax, word ptr [bp + 6]
00002798  75 06                     jne      0x27a0
0000279A  33 D2                     xor      dx, dx
0000279C  33 C0                     xor      ax, ax
0000279E  EB 1E                     jmp      0x27be
000027A0  C4 5E FC                  les      bx, ptr [bp - 4]
000027A3  26 C6 07 00               mov      byte ptr es:[bx], 0
000027A7  C4 5E 0C                  les      bx, ptr [bp + 0xc]
000027AA  26 F7 47 02 10 00         test     word ptr es:[bx + 2], 0x10
000027B0  74 06                     je       0x27b8
000027B2  33 D2                     xor      dx, dx
000027B4  33 C0                     xor      ax, ax
000027B6  EB 06                     jmp      0x27be
000027B8  8B 56 08                  mov      dx, word ptr [bp + 8]
000027BB  8B 46 06                  mov      ax, word ptr [bp + 6]
000027BE  5F                        pop      di
000027BF  5E                        pop      si
000027C0  8B E5                     mov      sp, bp
000027C2  5D                        pop      bp
000027C3  CB                        retf     
000027C4  55                        push     bp
000027C5  8B EC                     mov      bp, sp
000027C7  83 EC 08                  sub      sp, 8
000027CA  56                        push     si
000027CB  57                        push     di
000027CC  C7 46 F8 00 00            mov      word ptr [bp - 8], 0
000027D1  A1 74 21                  mov      ax, word ptr [0x2174]
000027D4  89 46 FA                  mov      word ptr [bp - 6], ax
000027D7  8C 5E FE                  mov      word ptr [bp - 2], ds
000027DA  C7 46 FC 8C 1D            mov      word ptr [bp - 4], 0x1d8c
000027DF  EB 23                     jmp      0x2804
000027E1  C4 5E FC                  les      bx, ptr [bp - 4]
000027E4  26 F7 47 02 03 00         test     word ptr es:[bx + 2], 3
000027EA  74 14                     je       0x2800
000027EC  26 83 3F 00               cmp      word ptr es:[bx], 0
000027F0  74 0E                     je       0x2800
000027F2  FF 76 FE                  push     word ptr [bp - 2]
000027F5  53                        push     bx
000027F6  90                        nop      
000027F7  0E                        push     cs
000027F8  E8 50 FE                  call     0x264b
000027FB  59                        pop      cx
000027FC  59                        pop      cx
000027FD  FF 46 F8                  inc      word ptr [bp - 8]
00002800  83 46 FC 14               add      word ptr [bp - 4], 0x14
00002804  8B 46 FA                  mov      ax, word ptr [bp - 6]
00002807  FF 4E FA                  dec      word ptr [bp - 6]
0000280A  0B C0                     or       ax, ax
0000280C  75 D3                     jne      0x27e1
0000280E  8B 46 F8                  mov      ax, word ptr [bp - 8]
00002811  5F                        pop      di
00002812  5E                        pop      si
00002813  8B E5                     mov      sp, bp
00002815  5D                        pop      bp
00002816  CB                        retf     
00002817  56                        push     si
00002818  57                        push     di
00002819  0E                        push     cs
0000281A  E8 A7 FF                  call     0x27c4
0000281D  5F                        pop      di
0000281E  5E                        pop      si
0000281F  CB                        retf     
00002820  55                        push     bp
00002821  8B EC                     mov      bp, sp
00002823  83 EC 0A                  sub      sp, 0xa
00002826  56                        push     si
00002827  57                        push     di
00002828  C7 46 F8 00 00            mov      word ptr [bp - 8], 0
0000282D  A1 74 21                  mov      ax, word ptr [0x2174]
00002830  89 46 FA                  mov      word ptr [bp - 6], ax
00002833  8C 5E FE                  mov      word ptr [bp - 2], ds
00002836  C7 46 FC 8C 1D            mov      word ptr [bp - 4], 0x1d8c
0000283B  EB 59                     jmp      0x2896
0000283D  C4 5E FC                  les      bx, ptr [bp - 4]
00002840  26 83 3F 00               cmp      word ptr es:[bx], 0
00002844  7D 4C                     jge      0x2892
00002846  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
0000284A  26 03 07                  add      ax, word ptr es:[bx]
0000284D  40                        inc      ax
0000284E  89 46 F6                  mov      word ptr [bp - 0xa], ax
00002851  26 29 07                  sub      word ptr es:[bx], ax
00002854  FF 76 F6                  push     word ptr [bp - 0xa]
00002857  8B 5E FC                  mov      bx, word ptr [bp - 4]
0000285A  26 8B 57 0A               mov      dx, word ptr es:[bx + 0xa]
0000285E  26 8B 47 08               mov      ax, word ptr es:[bx + 8]
00002862  26 89 57 0E               mov      word ptr es:[bx + 0xe], dx
00002866  26 89 47 0C               mov      word ptr es:[bx + 0xc], ax
0000286A  52                        push     dx
0000286B  50                        push     ax
0000286C  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00002870  98                        cwde     
00002871  50                        push     ax
00002872  90                        nop      
00002873  0E                        push     cs
00002874  E8 40 0D                  call     0x35b7
00002877  83 C4 08                  add      sp, 8
0000287A  3B 46 F6                  cmp      ax, word ptr [bp - 0xa]
0000287D  74 10                     je       0x288f
0000287F  C4 5E FC                  les      bx, ptr [bp - 4]
00002882  26 F7 47 02 00 02         test     word ptr es:[bx + 2], 0x200
00002888  75 05                     jne      0x288f
0000288A  26 83 4F 02 10            or       word ptr es:[bx + 2], 0x10
0000288F  FF 46 F8                  inc      word ptr [bp - 8]
00002892  83 46 FC 14               add      word ptr [bp - 4], 0x14
00002896  8B 46 FA                  mov      ax, word ptr [bp - 6]
00002899  FF 4E FA                  dec      word ptr [bp - 6]
0000289C  0B C0                     or       ax, ax
0000289E  75 9D                     jne      0x283d
000028A0  8B 46 F8                  mov      ax, word ptr [bp - 8]
000028A3  5F                        pop      di
000028A4  5E                        pop      si
000028A5  8B E5                     mov      sp, bp
000028A7  5D                        pop      bp
000028A8  CB                        retf     
000028A9  55                        push     bp
000028AA  8B EC                     mov      bp, sp
000028AC  83 EC 04                  sub      sp, 4
000028AF  56                        push     si
000028B0  57                        push     di
000028B1  C7 46 FE 00 00            mov      word ptr [bp - 2], 0
000028B6  C4 5E 0C                  les      bx, ptr [bp + 0xc]
000028B9  FF 46 0C                  inc      word ptr [bp + 0xc]
000028BC  26 8A 17                  mov      dl, byte ptr es:[bx]
000028BF  8A C2                     mov      al, dl
000028C1  3C 72                     cmp      al, 0x72
000028C3  75 0A                     jne      0x28cf
000028C5  B9 01 00                  mov      cx, 1
000028C8  C7 46 FC 01 00            mov      word ptr [bp - 4], 1
000028CD  EB 1C                     jmp      0x28eb
000028CF  80 FA 77                  cmp      dl, 0x77
000028D2  75 05                     jne      0x28d9
000028D4  B9 02 03                  mov      cx, 0x302
000028D7  EB 08                     jmp      0x28e1
000028D9  80 FA 61                  cmp      dl, 0x61
000028DC  75 68                     jne      0x2946
000028DE  B9 02 09                  mov      cx, 0x902
000028E1  C7 46 FE 80 00            mov      word ptr [bp - 2], 0x80
000028E6  C7 46 FC 02 00            mov      word ptr [bp - 4], 2
000028EB  C4 5E 0C                  les      bx, ptr [bp + 0xc]
000028EE  26 8A 17                  mov      dl, byte ptr es:[bx]
000028F1  FF 46 0C                  inc      word ptr [bp + 0xc]
000028F4  80 FA 2B                  cmp      dl, 0x2b
000028F7  74 13                     je       0x290c
000028F9  C4 5E 0C                  les      bx, ptr [bp + 0xc]
000028FC  26 80 3F 2B               cmp      byte ptr es:[bx], 0x2b
00002900  75 25                     jne      0x2927
00002902  80 FA 74                  cmp      dl, 0x74
00002905  74 05                     je       0x290c
00002907  80 FA 62                  cmp      dl, 0x62
0000290A  75 1B                     jne      0x2927
0000290C  80 FA 2B                  cmp      dl, 0x2b
0000290F  75 06                     jne      0x2917
00002911  C4 5E 0C                  les      bx, ptr [bp + 0xc]
00002914  26 8A 17                  mov      dl, byte ptr es:[bx]
00002917  83 E1 FC                  and      cx, 0xfffc
0000291A  83 C9 04                  or       cx, 4
0000291D  C7 46 FE 80 01            mov      word ptr [bp - 2], 0x180
00002922  C7 46 FC 03 00            mov      word ptr [bp - 4], 3
00002927  80 FA 74                  cmp      dl, 0x74
0000292A  75 06                     jne      0x2932
0000292C  81 C9 00 40               or       cx, 0x4000
00002930  EB 2B                     jmp      0x295d
00002932  80 FA 62                  cmp      dl, 0x62
00002935  75 06                     jne      0x293d
00002937  81 C9 00 80               or       cx, 0x8000
0000293B  EB 1C                     jmp      0x2959
0000293D  80 FA 2B                  cmp      dl, 0x2b
00002940  74 08                     je       0x294a
00002942  0A D2                     or       dl, dl
00002944  74 04                     je       0x294a
00002946  33 C0                     xor      ax, ax
00002948  EB 31                     jmp      0x297b
0000294A  A1 DA 21                  mov      ax, word ptr [0x21da]
0000294D  25 00 C0                  and      ax, 0xc000
00002950  0B C8                     or       cx, ax
00002952  8B C1                     mov      ax, cx
00002954  A9 00 80                  test     ax, 0x8000
00002957  74 04                     je       0x295d
00002959  83 4E FC 40               or       word ptr [bp - 4], 0x40
0000295D  C7 06 16 27 00 00         mov      word ptr [0x2716], 0
00002963  C7 06 14 27 21 37         mov      word ptr [0x2714], 0x3721
00002969  C4 5E 08                  les      bx, ptr [bp + 8]
0000296C  26 89 0F                  mov      word ptr es:[bx], cx
0000296F  C4 5E 04                  les      bx, ptr [bp + 4]
00002972  8B 46 FE                  mov      ax, word ptr [bp - 2]
00002975  26 89 07                  mov      word ptr es:[bx], ax
00002978  8B 46 FC                  mov      ax, word ptr [bp - 4]
0000297B  5F                        pop      di
0000297C  5E                        pop      si
0000297D  8B E5                     mov      sp, bp
0000297F  5D                        pop      bp
00002980  C2 0C 00                  ret      0xc
00002983  55                        push     bp
00002984  8B EC                     mov      bp, sp
00002986  83 EC 04                  sub      sp, 4
00002989  56                        push     si
0000298A  57                        push     di
0000298B  FF 76 08                  push     word ptr [bp + 8]
0000298E  FF 76 06                  push     word ptr [bp + 6]
00002991  16                        push     ss
00002992  8D 46 FE                  lea      ax, [bp - 2]
00002995  50                        push     ax
00002996  16                        push     ss
00002997  8D 46 FC                  lea      ax, [bp - 4]
0000299A  50                        push     ax
0000299B  E8 0B FF                  call     0x28a9
0000299E  C4 5E 0E                  les      bx, ptr [bp + 0xe]
000029A1  26 89 47 02               mov      word ptr es:[bx + 2], ax
000029A5  0B C0                     or       ax, ax
000029A7  74 2A                     je       0x29d3
000029A9  26 80 7F 04 00            cmp      byte ptr es:[bx + 4], 0
000029AE  7D 33                     jge      0x29e3
000029B0  FF 76 FC                  push     word ptr [bp - 4]
000029B3  8B 46 FE                  mov      ax, word ptr [bp - 2]
000029B6  0B 46 04                  or       ax, word ptr [bp + 4]
000029B9  50                        push     ax
000029BA  FF 76 0C                  push     word ptr [bp + 0xc]
000029BD  FF 76 0A                  push     word ptr [bp + 0xa]
000029C0  90                        nop      
000029C1  0E                        push     cs
000029C2  E8 4F 11                  call     0x3b14
000029C5  83 C4 08                  add      sp, 8
000029C8  C4 5E 0E                  les      bx, ptr [bp + 0xe]
000029CB  26 88 47 04               mov      byte ptr es:[bx + 4], al
000029CF  0A C0                     or       al, al
000029D1  7D 10                     jge      0x29e3
000029D3  C4 5E 0E                  les      bx, ptr [bp + 0xe]
000029D6  26 C6 47 04 FF            mov      byte ptr es:[bx + 4], 0xff
000029DB  26 C7 47 02 00 00         mov      word ptr es:[bx + 2], 0
000029E1  EB 56                     jmp      0x2a39
000029E3  C4 5E 0E                  les      bx, ptr [bp + 0xe]
000029E6  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
000029EA  98                        cwde     
000029EB  50                        push     ax
000029EC  90                        nop      
000029ED  0E                        push     cs
000029EE  E8 E5 F5                  call     0x1fd6
000029F1  59                        pop      cx
000029F2  0B C0                     or       ax, ax
000029F4  74 09                     je       0x29ff
000029F6  C4 5E 0E                  les      bx, ptr [bp + 0xe]
000029F9  26 81 4F 02 00 02         or       word ptr es:[bx + 2], 0x200
000029FF  B8 00 02                  mov      ax, 0x200
00002A02  50                        push     ax
00002A03  C4 5E 0E                  les      bx, ptr [bp + 0xe]
00002A06  26 F7 47 02 00 02         test     word ptr es:[bx + 2], 0x200
00002A0C  74 05                     je       0x2a13
00002A0E  B8 01 00                  mov      ax, 1
00002A11  EB 02                     jmp      0x2a15
00002A13  33 C0                     xor      ax, ax
00002A15  50                        push     ax
00002A16  33 C0                     xor      ax, ax
00002A18  50                        push     ax
00002A19  50                        push     ax
00002A1A  FF 76 10                  push     word ptr [bp + 0x10]
00002A1D  FF 76 0E                  push     word ptr [bp + 0xe]
00002A20  90                        nop      
00002A21  0E                        push     cs
00002A22  E8 6D 0A                  call     0x3492
00002A25  83 C4 0C                  add      sp, 0xc
00002A28  0B C0                     or       ax, ax
00002A2A  74 13                     je       0x2a3f
00002A2C  FF 76 10                  push     word ptr [bp + 0x10]
00002A2F  FF 76 0E                  push     word ptr [bp + 0xe]
00002A32  90                        nop      
00002A33  0E                        push     cs
00002A34  E8 53 FB                  call     0x258a
00002A37  59                        pop      cx
00002A38  59                        pop      cx
00002A39  33 D2                     xor      dx, dx
00002A3B  33 C0                     xor      ax, ax
00002A3D  EB 0F                     jmp      0x2a4e
00002A3F  C4 5E 0E                  les      bx, ptr [bp + 0xe]
00002A42  26 C7 47 10 00 00         mov      word ptr es:[bx + 0x10], 0
00002A48  8B 56 10                  mov      dx, word ptr [bp + 0x10]
00002A4B  8B 46 0E                  mov      ax, word ptr [bp + 0xe]
00002A4E  5F                        pop      di
00002A4F  5E                        pop      si
00002A50  8B E5                     mov      sp, bp
00002A52  5D                        pop      bp
00002A53  C2 0E 00                  ret      0xe
00002A56  55                        push     bp
00002A57  8B EC                     mov      bp, sp
00002A59  83 EC 04                  sub      sp, 4
00002A5C  56                        push     si
00002A5D  57                        push     di
00002A5E  8C 5E FE                  mov      word ptr [bp - 2], ds
00002A61  C7 46 FC 8C 1D            mov      word ptr [bp - 4], 0x1d8c
00002A66  C4 5E FC                  les      bx, ptr [bp - 4]
00002A69  26 80 7F 04 00            cmp      byte ptr es:[bx + 4], 0
00002A6E  7C 17                     jl       0x2a87
00002A70  8B 46 FC                  mov      ax, word ptr [bp - 4]
00002A73  83 46 FC 14               add      word ptr [bp - 4], 0x14
00002A77  50                        push     ax
00002A78  B8 14 00                  mov      ax, 0x14
00002A7B  F7 2E 74 21               imul     word ptr [0x2174]
00002A7F  05 8C 1D                  add      ax, 0x1d8c
00002A82  5A                        pop      dx
00002A83  3B D0                     cmp      dx, ax
00002A85  72 DF                     jb       0x2a66
00002A87  C4 5E FC                  les      bx, ptr [bp - 4]
00002A8A  26 80 7F 04 00            cmp      byte ptr es:[bx + 4], 0
00002A8F  7C 06                     jl       0x2a97
00002A91  33 D2                     xor      dx, dx
00002A93  33 C0                     xor      ax, ax
00002A95  EB 06                     jmp      0x2a9d
00002A97  8B 56 FE                  mov      dx, word ptr [bp - 2]
00002A9A  8B 46 FC                  mov      ax, word ptr [bp - 4]
00002A9D  5F                        pop      di
00002A9E  5E                        pop      si
00002A9F  8B E5                     mov      sp, bp
00002AA1  5D                        pop      bp
00002AA2  C3                        ret      
00002AA3  55                        push     bp
00002AA4  8B EC                     mov      bp, sp
00002AA6  83 EC 04                  sub      sp, 4
00002AA9  56                        push     si
00002AAA  57                        push     di
00002AAB  E8 A8 FF                  call     0x2a56
00002AAE  89 56 FE                  mov      word ptr [bp - 2], dx
00002AB1  89 46 FC                  mov      word ptr [bp - 4], ax
00002AB4  0B C2                     or       ax, dx
00002AB6  75 06                     jne      0x2abe
00002AB8  33 D2                     xor      dx, dx
00002ABA  33 C0                     xor      ax, ax
00002ABC  EB 18                     jmp      0x2ad6
00002ABE  FF 76 FE                  push     word ptr [bp - 2]
00002AC1  FF 76 FC                  push     word ptr [bp - 4]
00002AC4  FF 76 08                  push     word ptr [bp + 8]
00002AC7  FF 76 06                  push     word ptr [bp + 6]
00002ACA  FF 76 0C                  push     word ptr [bp + 0xc]
00002ACD  FF 76 0A                  push     word ptr [bp + 0xa]
00002AD0  33 C0                     xor      ax, ax
00002AD2  50                        push     ax
00002AD3  E8 AD FE                  call     0x2983
00002AD6  5F                        pop      di
00002AD7  5E                        pop      si
00002AD8  8B E5                     mov      sp, bp
00002ADA  5D                        pop      bp
00002ADB  CB                        retf     
00002ADC  55                        push     bp
00002ADD  8B EC                     mov      bp, sp
00002ADF  56                        push     si
00002AE0  57                        push     di
00002AE1  B8 1F 32                  mov      ax, 0x321f
00002AE4  50                        push     ax
00002AE5  FF 76 08                  push     word ptr [bp + 8]
00002AE8  FF 76 06                  push     word ptr [bp + 6]
00002AEB  FF 76 0C                  push     word ptr [bp + 0xc]
00002AEE  FF 76 0A                  push     word ptr [bp + 0xa]
00002AF1  8D 46 0E                  lea      ax, [bp + 0xe]
00002AF4  50                        push     ax
00002AF5  E8 A3 F5                  call     0x209b
00002AF8  5F                        pop      di
00002AF9  5E                        pop      si
00002AFA  5D                        pop      bp
00002AFB  CB                        retf     
00002AFC  55                        push     bp
00002AFD  8B EC                     mov      bp, sp
00002AFF  83 EC 02                  sub      sp, 2
00002B02  56                        push     si
00002B03  57                        push     di
00002B04  8B 46 06                  mov      ax, word ptr [bp + 6]
00002B07  0B 46 08                  or       ax, word ptr [bp + 8]
00002B0A  74 14                     je       0x2b20
00002B0C  FF 76 08                  push     word ptr [bp + 8]
00002B0F  FF 76 06                  push     word ptr [bp + 6]
00002B12  90                        nop      
00002B13  0E                        push     cs
00002B14  E8 3F F1                  call     0x1c56
00002B17  59                        pop      cx
00002B18  59                        pop      cx
00002B19  89 46 FE                  mov      word ptr [bp - 2], ax
00002B1C  0B C0                     or       ax, ax
00002B1E  75 04                     jne      0x2b24
00002B20  33 C0                     xor      ax, ax
00002B22  EB 27                     jmp      0x2b4b
00002B24  FF 76 08                  push     word ptr [bp + 8]
00002B27  FF 76 06                  push     word ptr [bp + 6]
00002B2A  FF 76 FE                  push     word ptr [bp - 2]
00002B2D  FF 76 0C                  push     word ptr [bp + 0xc]
00002B30  FF 76 0A                  push     word ptr [bp + 0xa]
00002B33  E8 E9 06                  call     0x321f
00002B36  0B C0                     or       ax, ax
00002B38  74 0E                     je       0x2b48
00002B3A  C4 5E 06                  les      bx, ptr [bp + 6]
00002B3D  03 5E FE                  add      bx, word ptr [bp - 2]
00002B40  26 8A 47 FF               mov      al, byte ptr es:[bx - 1]
00002B44  B4 00                     mov      ah, 0
00002B46  EB 03                     jmp      0x2b4b
00002B48  B8 FF FF                  mov      ax, 0xffff
00002B4B  5F                        pop      di
00002B4C  5E                        pop      si
00002B4D  8B E5                     mov      sp, bp
00002B4F  5D                        pop      bp
00002B50  CB                        retf     
00002B51  55                        push     bp
00002B52  8B EC                     mov      bp, sp
00002B54  83 EC 04                  sub      sp, 4
00002B57  56                        push     si
00002B58  57                        push     di
00002B59  E9 00 01                  jmp      0x2c5c
00002B5C  FF 46 08                  inc      word ptr [bp + 8]
00002B5F  C4 5E 04                  les      bx, ptr [bp + 4]
00002B62  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
00002B66  3B 46 08                  cmp      ax, word ptr [bp + 8]
00002B69  76 05                     jbe      0x2b70
00002B6B  8B 46 08                  mov      ax, word ptr [bp + 8]
00002B6E  EB 07                     jmp      0x2b77
00002B70  C4 5E 04                  les      bx, ptr [bp + 4]
00002B73  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
00002B77  89 46 FE                  mov      word ptr [bp - 2], ax
00002B7A  C4 5E 04                  les      bx, ptr [bp + 4]
00002B7D  26 F7 47 02 40 00         test     word ptr es:[bx + 2], 0x40
00002B83  75 03                     jne      0x2b88
00002B85  E9 8C 00                  jmp      0x2c14
00002B88  26 83 7F 06 00            cmp      word ptr es:[bx + 6], 0
00002B8D  75 03                     jne      0x2b92
00002B8F  E9 82 00                  jmp      0x2c14
00002B92  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
00002B96  3B 46 08                  cmp      ax, word ptr [bp + 8]
00002B99  73 79                     jae      0x2c14
00002B9B  26 83 3F 00               cmp      word ptr es:[bx], 0
00002B9F  75 73                     jne      0x2c14
00002BA1  FF 4E 08                  dec      word ptr [bp + 8]
00002BA4  C7 46 FE 00 00            mov      word ptr [bp - 2], 0
00002BA9  EB 12                     jmp      0x2bbd
00002BAB  C4 5E 04                  les      bx, ptr [bp + 4]
00002BAE  83 C3 06                  add      bx, 6
00002BB1  89 5E FC                  mov      word ptr [bp - 4], bx
00002BB4  26 8B 07                  mov      ax, word ptr es:[bx]
00002BB7  01 46 FE                  add      word ptr [bp - 2], ax
00002BBA  29 46 08                  sub      word ptr [bp + 8], ax
00002BBD  C4 5E 04                  les      bx, ptr [bp + 4]
00002BC0  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
00002BC4  3B 46 08                  cmp      ax, word ptr [bp + 8]
00002BC7  76 E2                     jbe      0x2bab
00002BC9  FF 76 FE                  push     word ptr [bp - 2]
00002BCC  FF 76 0C                  push     word ptr [bp + 0xc]
00002BCF  FF 76 0A                  push     word ptr [bp + 0xa]
00002BD2  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00002BD6  98                        cwde     
00002BD7  50                        push     ax
00002BD8  90                        nop      
00002BD9  0E                        push     cs
00002BDA  E8 3B F4                  call     0x2018
00002BDD  83 C4 08                  add      sp, 8
00002BE0  8B D0                     mov      dx, ax
00002BE2  83 FA FF                  cmp      dx, -1
00002BE5  75 0A                     jne      0x2bf1
00002BE7  33 D2                     xor      dx, dx
00002BE9  C4 5E 04                  les      bx, ptr [bp + 4]
00002BEC  26 83 4F 02 10            or       word ptr es:[bx + 2], 0x10
00002BF1  01 56 0A                  add      word ptr [bp + 0xa], dx
00002BF4  3B 56 FE                  cmp      dx, word ptr [bp - 2]
00002BF7  74 63                     je       0x2c5c
00002BF9  8B 46 FE                  mov      ax, word ptr [bp - 2]
00002BFC  2B C2                     sub      ax, dx
00002BFE  01 46 08                  add      word ptr [bp + 8], ax
00002C01  C4 5E 04                  les      bx, ptr [bp + 4]
00002C04  26 83 4F 02 20            or       word ptr es:[bx + 2], 0x20
00002C09  EB 5A                     jmp      0x2c65
00002C0B  C4 5E 0A                  les      bx, ptr [bp + 0xa]
00002C0E  26 88 17                  mov      byte ptr es:[bx], dl
00002C11  FF 46 0A                  inc      word ptr [bp + 0xa]
00002C14  FF 4E 08                  dec      word ptr [bp + 8]
00002C17  8B 46 08                  mov      ax, word ptr [bp + 8]
00002C1A  0B C0                     or       ax, ax
00002C1C  74 39                     je       0x2c57
00002C1E  FF 4E FE                  dec      word ptr [bp - 2]
00002C21  74 34                     je       0x2c57
00002C23  C4 5E 04                  les      bx, ptr [bp + 4]
00002C26  26 FF 0F                  dec      word ptr es:[bx]
00002C29  7C 18                     jl       0x2c43
00002C2B  8B 5E 04                  mov      bx, word ptr [bp + 4]
00002C2E  26 8B 57 0E               mov      dx, word ptr es:[bx + 0xe]
00002C32  26 8B 77 0C               mov      si, word ptr es:[bx + 0xc]
00002C36  26 FF 47 0C               inc      word ptr es:[bx + 0xc]
00002C3A  8E C2                     mov      es, dx
00002C3C  26 8A 04                  mov      al, byte ptr es:[si]
00002C3F  B4 00                     mov      ah, 0
00002C41  EB 0D                     jmp      0x2c50
00002C43  FF 76 06                  push     word ptr [bp + 6]
00002C46  FF 76 04                  push     word ptr [bp + 4]
00002C49  90                        nop      
00002C4A  0E                        push     cs
00002C4B  E8 61 0D                  call     0x39af
00002C4E  59                        pop      cx
00002C4F  59                        pop      cx
00002C50  8B D0                     mov      dx, ax
00002C52  3D FF FF                  cmp      ax, 0xffff
00002C55  75 B4                     jne      0x2c0b
00002C57  83 FA FF                  cmp      dx, -1
00002C5A  74 A5                     je       0x2c01
00002C5C  83 7E 08 00               cmp      word ptr [bp + 8], 0
00002C60  74 03                     je       0x2c65
00002C62  E9 F7 FE                  jmp      0x2b5c
00002C65  8B 46 08                  mov      ax, word ptr [bp + 8]
00002C68  5F                        pop      di
00002C69  5E                        pop      si
00002C6A  8B E5                     mov      sp, bp
00002C6C  5D                        pop      bp
00002C6D  C2 0A 00                  ret      0xa
00002C70  55                        push     bp
00002C71  8B EC                     mov      bp, sp
00002C73  83 EC 06                  sub      sp, 6
00002C76  56                        push     si
00002C77  57                        push     di
00002C78  83 7E 0A 00               cmp      word ptr [bp + 0xa], 0
00002C7C  75 05                     jne      0x2c83
00002C7E  33 C0                     xor      ax, ax
00002C80  E9 81 00                  jmp      0x2d04
00002C83  8B 5E 0A                  mov      bx, word ptr [bp + 0xa]
00002C86  33 C9                     xor      cx, cx
00002C88  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
00002C8B  33 D2                     xor      dx, dx
00002C8D  E8 08 13                  call     0x3f98
00002C90  89 56 FC                  mov      word ptr [bp - 4], dx
00002C93  89 46 FA                  mov      word ptr [bp - 6], ax
00002C96  83 FA 01                  cmp      dx, 1
00002C99  77 26                     ja       0x2cc1
00002C9B  72 04                     jb       0x2ca1
00002C9D  0B C0                     or       ax, ax
00002C9F  73 20                     jae      0x2cc1
00002CA1  FF 76 08                  push     word ptr [bp + 8]
00002CA4  FF 76 06                  push     word ptr [bp + 6]
00002CA7  FF 76 FA                  push     word ptr [bp - 6]
00002CAA  FF 76 10                  push     word ptr [bp + 0x10]
00002CAD  FF 76 0E                  push     word ptr [bp + 0xe]
00002CB0  E8 9E FE                  call     0x2b51
00002CB3  8B 56 FA                  mov      dx, word ptr [bp - 6]
00002CB6  2B D0                     sub      dx, ax
00002CB8  52                        push     dx
00002CB9  33 D2                     xor      dx, dx
00002CBB  58                        pop      ax
00002CBC  F7 76 0A                  div      word ptr [bp + 0xa]
00002CBF  EB 43                     jmp      0x2d04
00002CC1  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
00002CC4  40                        inc      ax
00002CC5  89 46 FE                  mov      word ptr [bp - 2], ax
00002CC8  EB 14                     jmp      0x2cde
00002CCA  8B 5E 0A                  mov      bx, word ptr [bp + 0xa]
00002CCD  33 C9                     xor      cx, cx
00002CCF  8B 56 08                  mov      dx, word ptr [bp + 8]
00002CD2  8B 46 06                  mov      ax, word ptr [bp + 6]
00002CD5  E8 4E 1E                  call     0x4b26
00002CD8  89 56 08                  mov      word ptr [bp + 8], dx
00002CDB  89 46 06                  mov      word ptr [bp + 6], ax
00002CDE  FF 4E FE                  dec      word ptr [bp - 2]
00002CE1  8B 46 FE                  mov      ax, word ptr [bp - 2]
00002CE4  0B C0                     or       ax, ax
00002CE6  74 16                     je       0x2cfe
00002CE8  FF 76 08                  push     word ptr [bp + 8]
00002CEB  FF 76 06                  push     word ptr [bp + 6]
00002CEE  FF 76 0A                  push     word ptr [bp + 0xa]
00002CF1  FF 76 10                  push     word ptr [bp + 0x10]
00002CF4  FF 76 0E                  push     word ptr [bp + 0xe]
00002CF7  E8 57 FE                  call     0x2b51
00002CFA  0B C0                     or       ax, ax
00002CFC  74 CC                     je       0x2cca
00002CFE  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
00002D01  2B 46 FE                  sub      ax, word ptr [bp - 2]
00002D04  5F                        pop      di
00002D05  5E                        pop      si
00002D06  8B E5                     mov      sp, bp
00002D08  5D                        pop      bp
00002D09  CB                        retf     
00002D0A  55                        push     bp
00002D0B  8B EC                     mov      bp, sp
00002D0D  83 EC 06                  sub      sp, 6
00002D10  56                        push     si
00002D11  57                        push     di
00002D12  C4 5E 04                  les      bx, ptr [bp + 4]
00002D15  26 83 3F 00               cmp      word ptr es:[bx], 0
00002D19  7D 0C                     jge      0x2d27
00002D1B  26 8B 4F 06               mov      cx, word ptr es:[bx + 6]
00002D1F  26 03 0F                  add      cx, word ptr es:[bx]
00002D22  41                        inc      cx
00002D23  8B C1                     mov      ax, cx
00002D25  EB 0D                     jmp      0x2d34
00002D27  C4 5E 04                  les      bx, ptr [bp + 4]
00002D2A  26 8B 07                  mov      ax, word ptr es:[bx]
00002D2D  99                        cdq      
00002D2E  33 C2                     xor      ax, dx
00002D30  2B C2                     sub      ax, dx
00002D32  8B C8                     mov      cx, ax
00002D34  89 46 FE                  mov      word ptr [bp - 2], ax
00002D37  C4 5E 04                  les      bx, ptr [bp + 4]
00002D3A  26 F7 47 02 40 00         test     word ptr es:[bx + 2], 0x40
00002D40  75 47                     jne      0x2d89
00002D42  C4 5E 04                  les      bx, ptr [bp + 4]
00002D45  26 8B 57 0E               mov      dx, word ptr es:[bx + 0xe]
00002D49  26 8B 47 0C               mov      ax, word ptr es:[bx + 0xc]
00002D4D  89 56 FC                  mov      word ptr [bp - 4], dx
00002D50  89 46 FA                  mov      word ptr [bp - 6], ax
00002D53  26 83 3F 00               cmp      word ptr es:[bx], 0
00002D57  7D 29                     jge      0x2d82
00002D59  EB 0F                     jmp      0x2d6a
00002D5B  FF 4E FA                  dec      word ptr [bp - 6]
00002D5E  C4 5E FA                  les      bx, ptr [bp - 6]
00002D61  26 80 3F 0A               cmp      byte ptr es:[bx], 0xa
00002D65  75 03                     jne      0x2d6a
00002D67  FF 46 FE                  inc      word ptr [bp - 2]
00002D6A  8B C1                     mov      ax, cx
00002D6C  49                        dec      cx
00002D6D  0B C0                     or       ax, ax
00002D6F  75 EA                     jne      0x2d5b
00002D71  EB 16                     jmp      0x2d89
00002D73  C4 5E FA                  les      bx, ptr [bp - 6]
00002D76  FF 46 FA                  inc      word ptr [bp - 6]
00002D79  26 80 3F 0A               cmp      byte ptr es:[bx], 0xa
00002D7D  75 03                     jne      0x2d82
00002D7F  FF 46 FE                  inc      word ptr [bp - 2]
00002D82  8B C1                     mov      ax, cx
00002D84  49                        dec      cx
00002D85  0B C0                     or       ax, ax
00002D87  75 EA                     jne      0x2d73
00002D89  8B 46 FE                  mov      ax, word ptr [bp - 2]
00002D8C  5F                        pop      di
00002D8D  5E                        pop      si
00002D8E  8B E5                     mov      sp, bp
00002D90  5D                        pop      bp
00002D91  C2 04 00                  ret      4
00002D94  55                        push     bp
00002D95  8B EC                     mov      bp, sp
00002D97  56                        push     si
00002D98  57                        push     di
00002D99  FF 76 08                  push     word ptr [bp + 8]
00002D9C  FF 76 06                  push     word ptr [bp + 6]
00002D9F  90                        nop      
00002DA0  0E                        push     cs
00002DA1  E8 A7 F8                  call     0x264b
00002DA4  59                        pop      cx
00002DA5  59                        pop      cx
00002DA6  0B C0                     or       ax, ax
00002DA8  74 05                     je       0x2daf
00002DAA  B8 FF FF                  mov      ax, 0xffff
00002DAD  EB 66                     jmp      0x2e15
00002DAF  83 7E 0E 01               cmp      word ptr [bp + 0xe], 1
00002DB3  75 17                     jne      0x2dcc
00002DB5  C4 5E 06                  les      bx, ptr [bp + 6]
00002DB8  26 83 3F 00               cmp      word ptr es:[bx], 0
00002DBC  7E 0E                     jle      0x2dcc
00002DBE  FF 76 08                  push     word ptr [bp + 8]
00002DC1  53                        push     bx
00002DC2  E8 45 FF                  call     0x2d0a
00002DC5  99                        cdq      
00002DC6  29 46 0A                  sub      word ptr [bp + 0xa], ax
00002DC9  19 56 0C                  sbb      word ptr [bp + 0xc], dx
00002DCC  C4 5E 06                  les      bx, ptr [bp + 6]
00002DCF  26 81 67 02 5F FE         and      word ptr es:[bx + 2], 0xfe5f
00002DD5  8B 5E 06                  mov      bx, word ptr [bp + 6]
00002DD8  26 C7 07 00 00            mov      word ptr es:[bx], 0
00002DDD  26 8B 57 0A               mov      dx, word ptr es:[bx + 0xa]
00002DE1  26 8B 47 08               mov      ax, word ptr es:[bx + 8]
00002DE5  26 89 57 0E               mov      word ptr es:[bx + 0xe], dx
00002DE9  26 89 47 0C               mov      word ptr es:[bx + 0xc], ax
00002DED  FF 76 0E                  push     word ptr [bp + 0xe]
00002DF0  FF 76 0C                  push     word ptr [bp + 0xc]
00002DF3  FF 76 0A                  push     word ptr [bp + 0xa]
00002DF6  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00002DFA  98                        cwde     
00002DFB  50                        push     ax
00002DFC  90                        nop      
00002DFD  0E                        push     cs
00002DFE  E8 EA F1                  call     0x1feb
00002E01  83 C4 08                  add      sp, 8
00002E04  83 FA FF                  cmp      dx, -1
00002E07  75 0A                     jne      0x2e13
00002E09  3D FF FF                  cmp      ax, 0xffff
00002E0C  75 05                     jne      0x2e13
00002E0E  B8 FF FF                  mov      ax, 0xffff
00002E11  EB 02                     jmp      0x2e15
00002E13  33 C0                     xor      ax, ax
00002E15  5F                        pop      di
00002E16  5E                        pop      si
00002E17  5D                        pop      bp
00002E18  CB                        retf     
00002E19  55                        push     bp
00002E1A  8B EC                     mov      bp, sp
00002E1C  83 EC 08                  sub      sp, 8
00002E1F  56                        push     si
00002E20  57                        push     di
00002E21  B8 01 00                  mov      ax, 1
00002E24  50                        push     ax
00002E25  33 C0                     xor      ax, ax
00002E27  50                        push     ax
00002E28  50                        push     ax
00002E29  C4 5E 06                  les      bx, ptr [bp + 6]
00002E2C  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00002E30  98                        cwde     
00002E31  50                        push     ax
00002E32  90                        nop      
00002E33  0E                        push     cs
00002E34  E8 B4 F1                  call     0x1feb
00002E37  83 C4 08                  add      sp, 8
00002E3A  89 56 FE                  mov      word ptr [bp - 2], dx
00002E3D  89 46 FC                  mov      word ptr [bp - 4], ax
00002E40  83 FA FF                  cmp      dx, -1
00002E43  75 08                     jne      0x2e4d
00002E45  3D FF FF                  cmp      ax, 0xffff
00002E48  75 03                     jne      0x2e4d
00002E4A  E9 A2 00                  jmp      0x2eef
00002E4D  C4 5E 06                  les      bx, ptr [bp + 6]
00002E50  26 83 3F 00               cmp      word ptr es:[bx], 0
00002E54  7C 03                     jl       0x2e59
00002E56  E9 86 00                  jmp      0x2edf
00002E59  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00002E5D  98                        cwde     
00002E5E  03 C0                     add      ax, ax
00002E60  8B D8                     mov      bx, ax
00002E62  F7 87 76 21 00 08         test     word ptr [bx + 0x2176], 0x800
00002E68  74 63                     je       0x2ecd
00002E6A  B8 02 00                  mov      ax, 2
00002E6D  50                        push     ax
00002E6E  33 C0                     xor      ax, ax
00002E70  50                        push     ax
00002E71  50                        push     ax
00002E72  C4 5E 06                  les      bx, ptr [bp + 6]
00002E75  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00002E79  98                        cwde     
00002E7A  50                        push     ax
00002E7B  90                        nop      
00002E7C  0E                        push     cs
00002E7D  E8 6B F1                  call     0x1feb
00002E80  83 C4 08                  add      sp, 8
00002E83  89 56 FA                  mov      word ptr [bp - 6], dx
00002E86  89 46 F8                  mov      word ptr [bp - 8], ax
00002E89  83 FA FF                  cmp      dx, -1
00002E8C  75 07                     jne      0x2e95
00002E8E  3D FF FF                  cmp      ax, 0xffff
00002E91  75 02                     jne      0x2e95
00002E93  EB 60                     jmp      0x2ef5
00002E95  33 C0                     xor      ax, ax
00002E97  50                        push     ax
00002E98  FF 76 FE                  push     word ptr [bp - 2]
00002E9B  FF 76 FC                  push     word ptr [bp - 4]
00002E9E  C4 5E 06                  les      bx, ptr [bp + 6]
00002EA1  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00002EA5  98                        cwde     
00002EA6  50                        push     ax
00002EA7  90                        nop      
00002EA8  0E                        push     cs
00002EA9  E8 3F F1                  call     0x1feb
00002EAC  83 C4 08                  add      sp, 8
00002EAF  83 FA FF                  cmp      dx, -1
00002EB2  75 0D                     jne      0x2ec1
00002EB4  3D FF FF                  cmp      ax, 0xffff
00002EB7  75 08                     jne      0x2ec1
00002EB9  BA FF FF                  mov      dx, 0xffff
00002EBC  B8 FF FF                  mov      ax, 0xffff
00002EBF  EB 34                     jmp      0x2ef5
00002EC1  8B 56 FA                  mov      dx, word ptr [bp - 6]
00002EC4  8B 46 F8                  mov      ax, word ptr [bp - 8]
00002EC7  89 56 FE                  mov      word ptr [bp - 2], dx
00002ECA  89 46 FC                  mov      word ptr [bp - 4], ax
00002ECD  FF 76 08                  push     word ptr [bp + 8]
00002ED0  FF 76 06                  push     word ptr [bp + 6]
00002ED3  E8 34 FE                  call     0x2d0a
00002ED6  99                        cdq      
00002ED7  01 46 FC                  add      word ptr [bp - 4], ax
00002EDA  11 56 FE                  adc      word ptr [bp - 2], dx
00002EDD  EB 10                     jmp      0x2eef
00002EDF  FF 76 08                  push     word ptr [bp + 8]
00002EE2  FF 76 06                  push     word ptr [bp + 6]
00002EE5  E8 22 FE                  call     0x2d0a
00002EE8  99                        cdq      
00002EE9  29 46 FC                  sub      word ptr [bp - 4], ax
00002EEC  19 56 FE                  sbb      word ptr [bp - 2], dx
00002EEF  8B 56 FE                  mov      dx, word ptr [bp - 2]
00002EF2  8B 46 FC                  mov      ax, word ptr [bp - 4]
00002EF5  5F                        pop      di
00002EF6  5E                        pop      si
00002EF7  8B E5                     mov      sp, bp
00002EF9  5D                        pop      bp
00002EFA  CB                        retf     
00002EFB  55                        push     bp
00002EFC  8B EC                     mov      bp, sp
00002EFE  83 EC 06                  sub      sp, 6
00002F01  56                        push     si
00002F02  57                        push     di
00002F03  83 7E 0A 00               cmp      word ptr [bp + 0xa], 0
00002F07  75 03                     jne      0x2f0c
00002F09  E9 7F 00                  jmp      0x2f8b
00002F0C  8B 5E 0A                  mov      bx, word ptr [bp + 0xa]
00002F0F  33 C9                     xor      cx, cx
00002F11  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
00002F14  33 D2                     xor      dx, dx
00002F16  E8 7F 10                  call     0x3f98
00002F19  89 56 FC                  mov      word ptr [bp - 4], dx
00002F1C  89 46 FA                  mov      word ptr [bp - 6], ax
00002F1F  83 FA 01                  cmp      dx, 1
00002F22  77 1F                     ja       0x2f43
00002F24  72 04                     jb       0x2f2a
00002F26  0B C0                     or       ax, ax
00002F28  73 19                     jae      0x2f43
00002F2A  FF 76 08                  push     word ptr [bp + 8]
00002F2D  FF 76 06                  push     word ptr [bp + 6]
00002F30  FF 76 FA                  push     word ptr [bp - 6]
00002F33  FF 76 10                  push     word ptr [bp + 0x10]
00002F36  FF 76 0E                  push     word ptr [bp + 0xe]
00002F39  E8 E3 02                  call     0x321f
00002F3C  33 D2                     xor      dx, dx
00002F3E  F7 76 0A                  div      word ptr [bp + 0xa]
00002F41  EB 4B                     jmp      0x2f8e
00002F43  C7 46 FE 00 00            mov      word ptr [bp - 2], 0
00002F48  EB 39                     jmp      0x2f83
00002F4A  FF 76 08                  push     word ptr [bp + 8]
00002F4D  FF 76 06                  push     word ptr [bp + 6]
00002F50  FF 76 0A                  push     word ptr [bp + 0xa]
00002F53  FF 76 10                  push     word ptr [bp + 0x10]
00002F56  FF 76 0E                  push     word ptr [bp + 0xe]
00002F59  E8 C3 02                  call     0x321f
00002F5C  33 D2                     xor      dx, dx
00002F5E  0B D2                     or       dx, dx
00002F60  75 05                     jne      0x2f67
00002F62  3B 46 0A                  cmp      ax, word ptr [bp + 0xa]
00002F65  74 05                     je       0x2f6c
00002F67  8B 46 FE                  mov      ax, word ptr [bp - 2]
00002F6A  EB 22                     jmp      0x2f8e
00002F6C  8B 5E 0A                  mov      bx, word ptr [bp + 0xa]
00002F6F  33 C9                     xor      cx, cx
00002F71  8B 56 08                  mov      dx, word ptr [bp + 8]
00002F74  8B 46 06                  mov      ax, word ptr [bp + 6]
00002F77  E8 AC 1B                  call     0x4b26
00002F7A  89 56 08                  mov      word ptr [bp + 8], dx
00002F7D  89 46 06                  mov      word ptr [bp + 6], ax
00002F80  FF 46 FE                  inc      word ptr [bp - 2]
00002F83  8B 46 FE                  mov      ax, word ptr [bp - 2]
00002F86  3B 46 0C                  cmp      ax, word ptr [bp + 0xc]
00002F89  72 BF                     jb       0x2f4a
00002F8B  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
00002F8E  5F                        pop      di
00002F8F  5E                        pop      si
00002F90  8B E5                     mov      sp, bp
00002F92  5D                        pop      bp
00002F93  CB                        retf     
00002F94  55                        push     bp
00002F95  8B EC                     mov      bp, sp
00002F97  83 EC 04                  sub      sp, 4
00002F9A  56                        push     si
00002F9B  57                        push     di
00002F9C  A1 7E 00                  mov      ax, word ptr [0x7e]
00002F9F  3B 06 6C 23               cmp      ax, word ptr [0x236c]
00002FA3  7D 1F                     jge      0x2fc4
00002FA5  83 3E 7E 00 00            cmp      word ptr [0x7e], 0
00002FAA  7C 18                     jl       0x2fc4
00002FAC  8B 1E 7E 00               mov      bx, word ptr [0x7e]
00002FB0  B1 02                     mov      cl, 2
00002FB2  D3 E3                     shl      bx, cl
00002FB4  8B 97 AE 22               mov      dx, word ptr [bx + 0x22ae]
00002FB8  8B 87 AC 22               mov      ax, word ptr [bx + 0x22ac]
00002FBC  89 56 FE                  mov      word ptr [bp - 2], dx
00002FBF  89 46 FC                  mov      word ptr [bp - 4], ax
00002FC2  EB 08                     jmp      0x2fcc
00002FC4  8C 5E FE                  mov      word ptr [bp - 2], ds
00002FC7  C7 46 FC 69 25            mov      word ptr [bp - 4], 0x2569
00002FCC  8B 46 06                  mov      ax, word ptr [bp + 6]
00002FCF  0B 46 08                  or       ax, word ptr [bp + 8]
00002FD2  74 2C                     je       0x3000
00002FD4  C4 5E 06                  les      bx, ptr [bp + 6]
00002FD7  26 80 3F 00               cmp      byte ptr es:[bx], 0
00002FDB  74 23                     je       0x3000
00002FDD  1E                        push     ds
00002FDE  B8 B4 1D                  mov      ax, 0x1db4
00002FE1  50                        push     ax
00002FE2  FF 76 08                  push     word ptr [bp + 8]
00002FE5  53                        push     bx
00002FE6  90                        nop      
00002FE7  0E                        push     cs
00002FE8  E8 11 FB                  call     0x2afc
00002FEB  83 C4 08                  add      sp, 8
00002FEE  1E                        push     ds
00002FEF  B8 B4 1D                  mov      ax, 0x1db4
00002FF2  50                        push     ax
00002FF3  1E                        push     ds
00002FF4  B8 77 25                  mov      ax, 0x2577
00002FF7  50                        push     ax
00002FF8  90                        nop      
00002FF9  0E                        push     cs
00002FFA  E8 FF FA                  call     0x2afc
00002FFD  83 C4 08                  add      sp, 8
00003000  1E                        push     ds
00003001  B8 B4 1D                  mov      ax, 0x1db4
00003004  50                        push     ax
00003005  FF 76 FE                  push     word ptr [bp - 2]
00003008  FF 76 FC                  push     word ptr [bp - 4]
0000300B  90                        nop      
0000300C  0E                        push     cs
0000300D  E8 EC FA                  call     0x2afc
00003010  83 C4 08                  add      sp, 8
00003013  1E                        push     ds
00003014  B8 B4 1D                  mov      ax, 0x1db4
00003017  50                        push     ax
00003018  1E                        push     ds
00003019  B8 7A 25                  mov      ax, 0x257a
0000301C  50                        push     ax
0000301D  90                        nop      
0000301E  0E                        push     cs
0000301F  E8 DA FA                  call     0x2afc
00003022  83 C4 08                  add      sp, 8
00003025  5F                        pop      di
00003026  5E                        pop      si
00003027  8B E5                     mov      sp, bp
00003029  5D                        pop      bp
0000302A  CB                        retf     
0000302B  55                        push     bp
0000302C  8B EC                     mov      bp, sp
0000302E  56                        push     si
0000302F  57                        push     di
00003030  B8 1F 32                  mov      ax, 0x321f
00003033  50                        push     ax
00003034  1E                        push     ds
00003035  B8 A0 1D                  mov      ax, 0x1da0
00003038  50                        push     ax
00003039  FF 76 08                  push     word ptr [bp + 8]
0000303C  FF 76 06                  push     word ptr [bp + 6]
0000303F  8D 46 0A                  lea      ax, [bp + 0xa]
00003042  50                        push     ax
00003043  E8 55 F0                  call     0x209b
00003046  5F                        pop      di
00003047  5E                        pop      si
00003048  5D                        pop      bp
00003049  CB                        retf     
0000304A  55                        push     bp
0000304B  8B EC                     mov      bp, sp
0000304D  56                        push     si
0000304E  57                        push     di
0000304F  C4 5E 08                  les      bx, ptr [bp + 8]
00003052  26 FF 0F                  dec      word ptr es:[bx]
00003055  FF 76 0A                  push     word ptr [bp + 0xa]
00003058  FF 76 08                  push     word ptr [bp + 8]
0000305B  8A 46 06                  mov      al, byte ptr [bp + 6]
0000305E  98                        cwde     
0000305F  50                        push     ax
00003060  90                        nop      
00003061  0E                        push     cs
00003062  E8 07 00                  call     0x306c
00003065  83 C4 06                  add      sp, 6
00003068  5F                        pop      di
00003069  5E                        pop      si
0000306A  5D                        pop      bp
0000306B  CB                        retf     
0000306C  55                        push     bp
0000306D  8B EC                     mov      bp, sp
0000306F  56                        push     si
00003070  57                        push     di
00003071  8A 46 06                  mov      al, byte ptr [bp + 6]
00003074  A2 24 58                  mov      byte ptr [0x5824], al
00003077  C4 5E 08                  les      bx, ptr [bp + 8]
0000307A  26 83 3F FF               cmp      word ptr es:[bx], -1
0000307E  7D 50                     jge      0x30d0
00003080  26 FF 07                  inc      word ptr es:[bx]
00003083  8B 5E 08                  mov      bx, word ptr [bp + 8]
00003086  26 8B 57 0E               mov      dx, word ptr es:[bx + 0xe]
0000308A  26 8B 77 0C               mov      si, word ptr es:[bx + 0xc]
0000308E  26 FF 47 0C               inc      word ptr es:[bx + 0xc]
00003092  A0 24 58                  mov      al, byte ptr [0x5824]
00003095  8E C2                     mov      es, dx
00003097  26 88 04                  mov      byte ptr es:[si], al
0000309A  C4 5E 08                  les      bx, ptr [bp + 8]
0000309D  26 F7 47 02 08 00         test     word ptr es:[bx + 2], 8
000030A3  75 03                     jne      0x30a8
000030A5  E9 56 01                  jmp      0x31fe
000030A8  80 3E 24 58 0A            cmp      byte ptr [0x5824], 0xa
000030AD  74 0A                     je       0x30b9
000030AF  80 3E 24 58 0D            cmp      byte ptr [0x5824], 0xd
000030B4  74 03                     je       0x30b9
000030B6  E9 45 01                  jmp      0x31fe
000030B9  FF 76 0A                  push     word ptr [bp + 0xa]
000030BC  FF 76 08                  push     word ptr [bp + 8]
000030BF  90                        nop      
000030C0  0E                        push     cs
000030C1  E8 87 F5                  call     0x264b
000030C4  59                        pop      cx
000030C5  59                        pop      cx
000030C6  0B C0                     or       ax, ax
000030C8  75 03                     jne      0x30cd
000030CA  E9 31 01                  jmp      0x31fe
000030CD  E9 29 01                  jmp      0x31f9
000030D0  C4 5E 08                  les      bx, ptr [bp + 8]
000030D3  26 F7 47 02 90 00         test     word ptr es:[bx + 2], 0x90
000030D9  75 08                     jne      0x30e3
000030DB  26 F7 47 02 02 00         test     word ptr es:[bx + 2], 2
000030E1  75 0B                     jne      0x30ee
000030E3  C4 5E 08                  les      bx, ptr [bp + 8]
000030E6  26 83 4F 02 10            or       word ptr es:[bx + 2], 0x10
000030EB  E9 0B 01                  jmp      0x31f9
000030EE  C4 5E 08                  les      bx, ptr [bp + 8]
000030F1  26 81 4F 02 00 01         or       word ptr es:[bx + 2], 0x100
000030F7  8B 5E 08                  mov      bx, word ptr [bp + 8]
000030FA  26 83 7F 06 00            cmp      word ptr es:[bx + 6], 0
000030FF  74 6E                     je       0x316f
00003101  26 83 3F 00               cmp      word ptr es:[bx], 0
00003105  74 12                     je       0x3119
00003107  FF 76 0A                  push     word ptr [bp + 0xa]
0000310A  53                        push     bx
0000310B  90                        nop      
0000310C  0E                        push     cs
0000310D  E8 3B F5                  call     0x264b
00003110  59                        pop      cx
00003111  59                        pop      cx
00003112  0B C0                     or       ax, ax
00003114  74 03                     je       0x3119
00003116  E9 E0 00                  jmp      0x31f9
00003119  C4 5E 08                  les      bx, ptr [bp + 8]
0000311C  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
00003120  F7 D8                     neg      ax
00003122  26 89 07                  mov      word ptr es:[bx], ax
00003125  26 8B 57 0E               mov      dx, word ptr es:[bx + 0xe]
00003129  26 8B 77 0C               mov      si, word ptr es:[bx + 0xc]
0000312D  26 FF 47 0C               inc      word ptr es:[bx + 0xc]
00003131  A0 24 58                  mov      al, byte ptr [0x5824]
00003134  8E C2                     mov      es, dx
00003136  26 88 04                  mov      byte ptr es:[si], al
00003139  C4 5E 08                  les      bx, ptr [bp + 8]
0000313C  26 F7 47 02 08 00         test     word ptr es:[bx + 2], 8
00003142  75 03                     jne      0x3147
00003144  E9 B7 00                  jmp      0x31fe
00003147  80 3E 24 58 0A            cmp      byte ptr [0x5824], 0xa
0000314C  74 0A                     je       0x3158
0000314E  80 3E 24 58 0D            cmp      byte ptr [0x5824], 0xd
00003153  74 03                     je       0x3158
00003155  E9 A6 00                  jmp      0x31fe
00003158  FF 76 0A                  push     word ptr [bp + 0xa]
0000315B  FF 76 08                  push     word ptr [bp + 8]
0000315E  90                        nop      
0000315F  0E                        push     cs
00003160  E8 E8 F4                  call     0x264b
00003163  59                        pop      cx
00003164  59                        pop      cx
00003165  0B C0                     or       ax, ax
00003167  75 03                     jne      0x316c
00003169  E9 92 00                  jmp      0x31fe
0000316C  E9 8A 00                  jmp      0x31f9
0000316F  C4 5E 08                  les      bx, ptr [bp + 8]
00003172  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00003176  98                        cwde     
00003177  03 C0                     add      ax, ax
00003179  8B D8                     mov      bx, ax
0000317B  F7 87 76 21 00 08         test     word ptr [bx + 0x2176], 0x800
00003181  74 19                     je       0x319c
00003183  B8 02 00                  mov      ax, 2
00003186  50                        push     ax
00003187  33 C0                     xor      ax, ax
00003189  50                        push     ax
0000318A  50                        push     ax
0000318B  C4 5E 08                  les      bx, ptr [bp + 8]
0000318E  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00003192  98                        cwde     
00003193  50                        push     ax
00003194  90                        nop      
00003195  0E                        push     cs
00003196  E8 52 EE                  call     0x1feb
00003199  83 C4 08                  add      sp, 8
0000319C  80 3E 24 58 0A            cmp      byte ptr [0x5824], 0xa
000031A1  75 27                     jne      0x31ca
000031A3  C4 5E 08                  les      bx, ptr [bp + 8]
000031A6  26 F7 47 02 40 00         test     word ptr es:[bx + 2], 0x40
000031AC  75 1C                     jne      0x31ca
000031AE  B8 01 00                  mov      ax, 1
000031B1  50                        push     ax
000031B2  1E                        push     ds
000031B3  B8 7C 25                  mov      ax, 0x257c
000031B6  50                        push     ax
000031B7  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
000031BB  98                        cwde     
000031BC  50                        push     ax
000031BD  90                        nop      
000031BE  0E                        push     cs
000031BF  E8 37 0C                  call     0x3df9
000031C2  83 C4 08                  add      sp, 8
000031C5  3D 01 00                  cmp      ax, 1
000031C8  75 1F                     jne      0x31e9
000031CA  B8 01 00                  mov      ax, 1
000031CD  50                        push     ax
000031CE  1E                        push     ds
000031CF  B8 24 58                  mov      ax, 0x5824
000031D2  50                        push     ax
000031D3  C4 5E 08                  les      bx, ptr [bp + 8]
000031D6  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
000031DA  98                        cwde     
000031DB  50                        push     ax
000031DC  90                        nop      
000031DD  0E                        push     cs
000031DE  E8 18 0C                  call     0x3df9
000031E1  83 C4 08                  add      sp, 8
000031E4  3D 01 00                  cmp      ax, 1
000031E7  74 15                     je       0x31fe
000031E9  C4 5E 08                  les      bx, ptr [bp + 8]
000031EC  26 F7 47 02 00 02         test     word ptr es:[bx + 2], 0x200
000031F2  75 0A                     jne      0x31fe
000031F4  26 83 4F 02 10            or       word ptr es:[bx + 2], 0x10
000031F9  B8 FF FF                  mov      ax, 0xffff
000031FC  EB 05                     jmp      0x3203
000031FE  A0 24 58                  mov      al, byte ptr [0x5824]
00003201  B4 00                     mov      ah, 0
00003203  5F                        pop      di
00003204  5E                        pop      si
00003205  5D                        pop      bp
00003206  CB                        retf     
00003207  55                        push     bp
00003208  8B EC                     mov      bp, sp
0000320A  56                        push     si
0000320B  57                        push     di
0000320C  1E                        push     ds
0000320D  B8 A0 1D                  mov      ax, 0x1da0
00003210  50                        push     ax
00003211  FF 76 06                  push     word ptr [bp + 6]
00003214  0E                        push     cs
00003215  E8 54 FE                  call     0x306c
00003218  83 C4 06                  add      sp, 6
0000321B  5F                        pop      di
0000321C  5E                        pop      si
0000321D  5D                        pop      bp
0000321E  CB                        retf     
0000321F  55                        push     bp
00003220  8B EC                     mov      bp, sp
00003222  83 EC 02                  sub      sp, 2
00003225  56                        push     si
00003226  57                        push     di
00003227  8B 46 08                  mov      ax, word ptr [bp + 8]
0000322A  89 46 FE                  mov      word ptr [bp - 2], ax
0000322D  C4 5E 04                  les      bx, ptr [bp + 4]
00003230  26 F7 47 02 08 00         test     word ptr es:[bx + 2], 8
00003236  74 2F                     je       0x3267
00003238  EB 20                     jmp      0x325a
0000323A  FF 76 06                  push     word ptr [bp + 6]
0000323D  FF 76 04                  push     word ptr [bp + 4]
00003240  C4 5E 0A                  les      bx, ptr [bp + 0xa]
00003243  FF 46 0A                  inc      word ptr [bp + 0xa]
00003246  26 8A 07                  mov      al, byte ptr es:[bx]
00003249  98                        cwde     
0000324A  50                        push     ax
0000324B  0E                        push     cs
0000324C  E8 1D FE                  call     0x306c
0000324F  83 C4 06                  add      sp, 6
00003252  3D FF FF                  cmp      ax, 0xffff
00003255  75 03                     jne      0x325a
00003257  E9 C8 01                  jmp      0x3422
0000325A  8B 46 08                  mov      ax, word ptr [bp + 8]
0000325D  FF 4E 08                  dec      word ptr [bp + 8]
00003260  0B C0                     or       ax, ax
00003262  75 D6                     jne      0x323a
00003264  E9 BF 01                  jmp      0x3426
00003267  C4 5E 04                  les      bx, ptr [bp + 4]
0000326A  26 F7 47 02 40 00         test     word ptr es:[bx + 2], 0x40
00003270  75 03                     jne      0x3275
00003272  E9 31 01                  jmp      0x33a6
00003275  26 83 7F 06 00            cmp      word ptr es:[bx + 6], 0
0000327A  75 03                     jne      0x327f
0000327C  E9 D6 00                  jmp      0x3355
0000327F  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
00003283  3B 46 08                  cmp      ax, word ptr [bp + 8]
00003286  73 6A                     jae      0x32f2
00003288  26 83 3F 00               cmp      word ptr es:[bx], 0
0000328C  74 12                     je       0x32a0
0000328E  FF 76 06                  push     word ptr [bp + 6]
00003291  53                        push     bx
00003292  90                        nop      
00003293  0E                        push     cs
00003294  E8 B4 F3                  call     0x264b
00003297  59                        pop      cx
00003298  59                        pop      cx
00003299  0B C0                     or       ax, ax
0000329B  74 03                     je       0x32a0
0000329D  E9 82 01                  jmp      0x3422
000032A0  C4 5E 04                  les      bx, ptr [bp + 4]
000032A3  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
000032A7  98                        cwde     
000032A8  03 C0                     add      ax, ax
000032AA  8B D8                     mov      bx, ax
000032AC  F7 87 76 21 00 08         test     word ptr [bx + 0x2176], 0x800
000032B2  74 19                     je       0x32cd
000032B4  B8 02 00                  mov      ax, 2
000032B7  50                        push     ax
000032B8  33 C0                     xor      ax, ax
000032BA  50                        push     ax
000032BB  50                        push     ax
000032BC  C4 5E 04                  les      bx, ptr [bp + 4]
000032BF  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
000032C3  98                        cwde     
000032C4  50                        push     ax
000032C5  90                        nop      
000032C6  0E                        push     cs
000032C7  E8 21 ED                  call     0x1feb
000032CA  83 C4 08                  add      sp, 8
000032CD  FF 76 08                  push     word ptr [bp + 8]
000032D0  FF 76 0C                  push     word ptr [bp + 0xc]
000032D3  FF 76 0A                  push     word ptr [bp + 0xa]
000032D6  C4 5E 04                  les      bx, ptr [bp + 4]
000032D9  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
000032DD  98                        cwde     
000032DE  50                        push     ax
000032DF  90                        nop      
000032E0  0E                        push     cs
000032E1  E8 15 0B                  call     0x3df9
000032E4  83 C4 08                  add      sp, 8
000032E7  3B 46 08                  cmp      ax, word ptr [bp + 8]
000032EA  75 03                     jne      0x32ef
000032EC  E9 37 01                  jmp      0x3426
000032EF  E9 30 01                  jmp      0x3422
000032F2  C4 5E 04                  les      bx, ptr [bp + 4]
000032F5  26 8B 07                  mov      ax, word ptr es:[bx]
000032F8  03 46 08                  add      ax, word ptr [bp + 8]
000032FB  7C 26                     jl       0x3323
000032FD  26 83 3F 00               cmp      word ptr es:[bx], 0
00003301  75 0C                     jne      0x330f
00003303  B8 FF FF                  mov      ax, 0xffff
00003306  26 2B 47 06               sub      ax, word ptr es:[bx + 6]
0000330A  26 89 07                  mov      word ptr es:[bx], ax
0000330D  EB 14                     jmp      0x3323
0000330F  FF 76 06                  push     word ptr [bp + 6]
00003312  FF 76 04                  push     word ptr [bp + 4]
00003315  90                        nop      
00003316  0E                        push     cs
00003317  E8 31 F3                  call     0x264b
0000331A  59                        pop      cx
0000331B  59                        pop      cx
0000331C  0B C0                     or       ax, ax
0000331E  74 03                     je       0x3323
00003320  E9 FF 00                  jmp      0x3422
00003323  FF 76 08                  push     word ptr [bp + 8]
00003326  FF 76 0C                  push     word ptr [bp + 0xc]
00003329  FF 76 0A                  push     word ptr [bp + 0xa]
0000332C  C4 5E 04                  les      bx, ptr [bp + 4]
0000332F  26 FF 77 0E               push     word ptr es:[bx + 0xe]
00003333  26 FF 77 0C               push     word ptr es:[bx + 0xc]
00003337  90                        nop      
00003338  0E                        push     cs
00003339  E8 5D E7                  call     0x1a99
0000333C  83 C4 0A                  add      sp, 0xa
0000333F  C4 5E 04                  les      bx, ptr [bp + 4]
00003342  26 8B 07                  mov      ax, word ptr es:[bx]
00003345  03 46 08                  add      ax, word ptr [bp + 8]
00003348  26 89 07                  mov      word ptr es:[bx], ax
0000334B  8B 46 08                  mov      ax, word ptr [bp + 8]
0000334E  26 01 47 0C               add      word ptr es:[bx + 0xc], ax
00003352  E9 D1 00                  jmp      0x3426
00003355  C4 5E 04                  les      bx, ptr [bp + 4]
00003358  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
0000335C  98                        cwde     
0000335D  03 C0                     add      ax, ax
0000335F  8B D8                     mov      bx, ax
00003361  F7 87 76 21 00 08         test     word ptr [bx + 0x2176], 0x800
00003367  74 19                     je       0x3382
00003369  B8 02 00                  mov      ax, 2
0000336C  50                        push     ax
0000336D  33 C0                     xor      ax, ax
0000336F  50                        push     ax
00003370  50                        push     ax
00003371  C4 5E 04                  les      bx, ptr [bp + 4]
00003374  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00003378  98                        cwde     
00003379  50                        push     ax
0000337A  90                        nop      
0000337B  0E                        push     cs
0000337C  E8 6C EC                  call     0x1feb
0000337F  83 C4 08                  add      sp, 8
00003382  FF 76 08                  push     word ptr [bp + 8]
00003385  FF 76 0C                  push     word ptr [bp + 0xc]
00003388  FF 76 0A                  push     word ptr [bp + 0xa]
0000338B  C4 5E 04                  les      bx, ptr [bp + 4]
0000338E  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00003392  98                        cwde     
00003393  50                        push     ax
00003394  90                        nop      
00003395  0E                        push     cs
00003396  E8 60 0A                  call     0x3df9
00003399  83 C4 08                  add      sp, 8
0000339C  3B 46 08                  cmp      ax, word ptr [bp + 8]
0000339F  75 03                     jne      0x33a4
000033A1  E9 82 00                  jmp      0x3426
000033A4  EB 7C                     jmp      0x3422
000033A6  C4 5E 04                  les      bx, ptr [bp + 4]
000033A9  26 83 7F 06 00            cmp      word ptr es:[bx + 6], 0
000033AE  74 53                     je       0x3403
000033B0  EB 45                     jmp      0x33f7
000033B2  C4 5E 04                  les      bx, ptr [bp + 4]
000033B5  26 FF 07                  inc      word ptr es:[bx]
000033B8  7D 21                     jge      0x33db
000033BA  8B 5E 04                  mov      bx, word ptr [bp + 4]
000033BD  26 8B 57 0E               mov      dx, word ptr es:[bx + 0xe]
000033C1  26 8B 77 0C               mov      si, word ptr es:[bx + 0xc]
000033C5  26 FF 47 0C               inc      word ptr es:[bx + 0xc]
000033C9  C4 5E 0A                  les      bx, ptr [bp + 0xa]
000033CC  FF 46 0A                  inc      word ptr [bp + 0xa]
000033CF  26 8A 07                  mov      al, byte ptr es:[bx]
000033D2  8E C2                     mov      es, dx
000033D4  26 88 04                  mov      byte ptr es:[si], al
000033D7  B4 00                     mov      ah, 0
000033D9  EB 17                     jmp      0x33f2
000033DB  FF 76 06                  push     word ptr [bp + 6]
000033DE  FF 76 04                  push     word ptr [bp + 4]
000033E1  C4 5E 0A                  les      bx, ptr [bp + 0xa]
000033E4  FF 46 0A                  inc      word ptr [bp + 0xa]
000033E7  26 8A 07                  mov      al, byte ptr es:[bx]
000033EA  50                        push     ax
000033EB  0E                        push     cs
000033EC  E8 5B FC                  call     0x304a
000033EF  83 C4 06                  add      sp, 6
000033F2  3D FF FF                  cmp      ax, 0xffff
000033F5  74 2B                     je       0x3422
000033F7  8B 46 08                  mov      ax, word ptr [bp + 8]
000033FA  FF 4E 08                  dec      word ptr [bp + 8]
000033FD  0B C0                     or       ax, ax
000033FF  75 B1                     jne      0x33b2
00003401  EB 23                     jmp      0x3426
00003403  FF 76 08                  push     word ptr [bp + 8]
00003406  FF 76 0C                  push     word ptr [bp + 0xc]
00003409  FF 76 0A                  push     word ptr [bp + 0xa]
0000340C  C4 5E 04                  les      bx, ptr [bp + 4]
0000340F  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00003413  98                        cwde     
00003414  50                        push     ax
00003415  90                        nop      
00003416  0E                        push     cs
00003417  E8 9D 01                  call     0x35b7
0000341A  83 C4 08                  add      sp, 8
0000341D  3B 46 08                  cmp      ax, word ptr [bp + 8]
00003420  74 04                     je       0x3426
00003422  33 C0                     xor      ax, ax
00003424  EB 03                     jmp      0x3429
00003426  8B 46 FE                  mov      ax, word ptr [bp - 2]
00003429  5F                        pop      di
0000342A  5E                        pop      si
0000342B  8B E5                     mov      sp, bp
0000342D  5D                        pop      bp
0000342E  C2 0A 00                  ret      0xa
00003431  55                        push     bp
00003432  8B EC                     mov      bp, sp
00003434  83 EC 02                  sub      sp, 2
00003437  56                        push     si
00003438  57                        push     di
00003439  8B 46 06                  mov      ax, word ptr [bp + 6]
0000343C  0B 46 08                  or       ax, word ptr [bp + 8]
0000343F  75 04                     jne      0x3445
00003441  33 C0                     xor      ax, ax
00003443  EB 47                     jmp      0x348c
00003445  FF 76 08                  push     word ptr [bp + 8]
00003448  FF 76 06                  push     word ptr [bp + 6]
0000344B  90                        nop      
0000344C  0E                        push     cs
0000344D  E8 06 E8                  call     0x1c56
00003450  59                        pop      cx
00003451  59                        pop      cx
00003452  89 46 FE                  mov      word ptr [bp - 2], ax
00003455  FF 76 08                  push     word ptr [bp + 8]
00003458  FF 76 06                  push     word ptr [bp + 6]
0000345B  50                        push     ax
0000345C  1E                        push     ds
0000345D  B8 A0 1D                  mov      ax, 0x1da0
00003460  50                        push     ax
00003461  E8 BB FD                  call     0x321f
00003464  3B 46 FE                  cmp      ax, word ptr [bp - 2]
00003467  74 05                     je       0x346e
00003469  B8 FF FF                  mov      ax, 0xffff
0000346C  EB 1E                     jmp      0x348c
0000346E  1E                        push     ds
0000346F  B8 A0 1D                  mov      ax, 0x1da0
00003472  50                        push     ax
00003473  B8 0A 00                  mov      ax, 0xa
00003476  50                        push     ax
00003477  90                        nop      
00003478  0E                        push     cs
00003479  E8 F0 FB                  call     0x306c
0000347C  83 C4 06                  add      sp, 6
0000347F  3D 0A 00                  cmp      ax, 0xa
00003482  74 05                     je       0x3489
00003484  B8 FF FF                  mov      ax, 0xffff
00003487  EB 03                     jmp      0x348c
00003489  B8 0A 00                  mov      ax, 0xa
0000348C  5F                        pop      di
0000348D  5E                        pop      si
0000348E  8B E5                     mov      sp, bp
00003490  5D                        pop      bp
00003491  CB                        retf     
00003492  55                        push     bp
00003493  8B EC                     mov      bp, sp
00003495  56                        push     si
00003496  57                        push     di
00003497  C4 5E 06                  les      bx, ptr [bp + 6]
0000349A  26 8B 47 12               mov      ax, word ptr es:[bx + 0x12]
0000349E  3B 46 06                  cmp      ax, word ptr [bp + 6]
000034A1  74 03                     je       0x34a6
000034A3  E9 DB 00                  jmp      0x3581
000034A6  83 7E 0E 02               cmp      word ptr [bp + 0xe], 2
000034AA  7E 03                     jle      0x34af
000034AC  E9 D2 00                  jmp      0x3581
000034AF  81 7E 10 FF 7F            cmp      word ptr [bp + 0x10], 0x7fff
000034B4  76 03                     jbe      0x34b9
000034B6  E9 C8 00                  jmp      0x3581
000034B9  83 3E 80 25 00            cmp      word ptr [0x2580], 0
000034BE  75 0F                     jne      0x34cf
000034C0  81 7E 06 A0 1D            cmp      word ptr [bp + 6], 0x1da0
000034C5  75 08                     jne      0x34cf
000034C7  C7 06 80 25 01 00         mov      word ptr [0x2580], 1
000034CD  EB 14                     jmp      0x34e3
000034CF  83 3E 7E 25 00            cmp      word ptr [0x257e], 0
000034D4  75 0D                     jne      0x34e3
000034D6  81 7E 06 8C 1D            cmp      word ptr [bp + 6], 0x1d8c
000034DB  75 06                     jne      0x34e3
000034DD  C7 06 7E 25 01 00         mov      word ptr [0x257e], 1
000034E3  C4 5E 06                  les      bx, ptr [bp + 6]
000034E6  26 83 3F 00               cmp      word ptr es:[bx], 0
000034EA  74 14                     je       0x3500
000034EC  B8 01 00                  mov      ax, 1
000034EF  50                        push     ax
000034F0  33 C0                     xor      ax, ax
000034F2  50                        push     ax
000034F3  50                        push     ax
000034F4  FF 76 08                  push     word ptr [bp + 8]
000034F7  53                        push     bx
000034F8  90                        nop      
000034F9  0E                        push     cs
000034FA  E8 97 F8                  call     0x2d94
000034FD  83 C4 0A                  add      sp, 0xa
00003500  C4 5E 06                  les      bx, ptr [bp + 6]
00003503  26 F7 47 02 04 00         test     word ptr es:[bx + 2], 4
00003509  74 0F                     je       0x351a
0000350B  26 FF 77 0A               push     word ptr es:[bx + 0xa]
0000350F  26 FF 77 08               push     word ptr es:[bx + 8]
00003513  90                        nop      
00003514  0E                        push     cs
00003515  E8 30 11                  call     0x4648
00003518  59                        pop      cx
00003519  59                        pop      cx
0000351A  C4 5E 06                  les      bx, ptr [bp + 6]
0000351D  26 83 67 02 F3            and      word ptr es:[bx + 2], 0xfff3
00003522  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003525  26 C7 47 06 00 00         mov      word ptr es:[bx + 6], 0
0000352B  8B 56 08                  mov      dx, word ptr [bp + 8]
0000352E  8B 46 06                  mov      ax, word ptr [bp + 6]
00003531  05 05 00                  add      ax, 5
00003534  26 89 57 0A               mov      word ptr es:[bx + 0xa], dx
00003538  26 89 47 08               mov      word ptr es:[bx + 8], ax
0000353C  26 89 57 0E               mov      word ptr es:[bx + 0xe], dx
00003540  26 89 47 0C               mov      word ptr es:[bx + 0xc], ax
00003544  83 7E 0E 02               cmp      word ptr [bp + 0xe], 2
00003548  74 67                     je       0x35b1
0000354A  83 7E 10 00               cmp      word ptr [bp + 0x10], 0
0000354E  76 61                     jbe      0x35b1
00003550  C7 06 12 27 00 00         mov      word ptr [0x2712], 0
00003556  C7 06 10 27 6B 37         mov      word ptr [0x2710], 0x376b
0000355C  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
0000355F  0B 46 0C                  or       ax, word ptr [bp + 0xc]
00003562  75 22                     jne      0x3586
00003564  FF 76 10                  push     word ptr [bp + 0x10]
00003567  90                        nop      
00003568  0E                        push     cs
00003569  E8 E6 11                  call     0x4752
0000356C  59                        pop      cx
0000356D  89 56 0C                  mov      word ptr [bp + 0xc], dx
00003570  89 46 0A                  mov      word ptr [bp + 0xa], ax
00003573  0B C2                     or       ax, dx
00003575  74 0A                     je       0x3581
00003577  C4 5E 06                  les      bx, ptr [bp + 6]
0000357A  26 83 4F 02 04            or       word ptr es:[bx + 2], 4
0000357F  EB 05                     jmp      0x3586
00003581  B8 FF FF                  mov      ax, 0xffff
00003584  EB 2D                     jmp      0x35b3
00003586  C4 5E 06                  les      bx, ptr [bp + 6]
00003589  8B 56 0C                  mov      dx, word ptr [bp + 0xc]
0000358C  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
0000358F  26 89 57 0E               mov      word ptr es:[bx + 0xe], dx
00003593  26 89 47 0C               mov      word ptr es:[bx + 0xc], ax
00003597  26 89 57 0A               mov      word ptr es:[bx + 0xa], dx
0000359B  26 89 47 08               mov      word ptr es:[bx + 8], ax
0000359F  8B 46 10                  mov      ax, word ptr [bp + 0x10]
000035A2  26 89 47 06               mov      word ptr es:[bx + 6], ax
000035A6  83 7E 0E 01               cmp      word ptr [bp + 0xe], 1
000035AA  75 05                     jne      0x35b1
000035AC  26 83 4F 02 08            or       word ptr es:[bx + 2], 8
000035B1  33 C0                     xor      ax, ax
000035B3  5F                        pop      di
000035B4  5E                        pop      si
000035B5  5D                        pop      bp
000035B6  CB                        retf     
000035B7  55                        push     bp
000035B8  8B EC                     mov      bp, sp
000035BA  81 EC 90 00               sub      sp, 0x90
000035BE  56                        push     si
000035BF  57                        push     di
000035C0  8B 46 06                  mov      ax, word ptr [bp + 6]
000035C3  3B 06 74 21               cmp      ax, word ptr [0x2174]
000035C7  72 0A                     jb       0x35d3
000035C9  B8 06 00                  mov      ax, 6
000035CC  50                        push     ax
000035CD  E8 B4 E9                  call     0x1f84
000035D0  E9 48 01                  jmp      0x371b
000035D3  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
000035D6  40                        inc      ax
000035D7  3D 02 00                  cmp      ax, 2
000035DA  73 05                     jae      0x35e1
000035DC  33 C0                     xor      ax, ax
000035DE  E9 3A 01                  jmp      0x371b
000035E1  8B 5E 06                  mov      bx, word ptr [bp + 6]
000035E4  03 DB                     add      bx, bx
000035E6  F7 87 76 21 00 08         test     word ptr [bx + 0x2176], 0x800
000035EC  74 13                     je       0x3601
000035EE  B8 02 00                  mov      ax, 2
000035F1  50                        push     ax
000035F2  33 C0                     xor      ax, ax
000035F4  50                        push     ax
000035F5  50                        push     ax
000035F6  FF 76 06                  push     word ptr [bp + 6]
000035F9  90                        nop      
000035FA  0E                        push     cs
000035FB  E8 ED E9                  call     0x1feb
000035FE  83 C4 08                  add      sp, 8
00003601  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003604  03 DB                     add      bx, bx
00003606  F7 87 76 21 00 40         test     word ptr [bx + 0x2176], 0x4000
0000360C  75 17                     jne      0x3625
0000360E  FF 76 0C                  push     word ptr [bp + 0xc]
00003611  FF 76 0A                  push     word ptr [bp + 0xa]
00003614  FF 76 08                  push     word ptr [bp + 8]
00003617  FF 76 06                  push     word ptr [bp + 6]
0000361A  90                        nop      
0000361B  0E                        push     cs
0000361C  E8 DA 07                  call     0x3df9
0000361F  83 C4 08                  add      sp, 8
00003622  E9 F6 00                  jmp      0x371b
00003625  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003628  03 DB                     add      bx, bx
0000362A  81 A7 76 21 FF FD         and      word ptr [bx + 0x2176], 0xfdff
00003630  8B 56 0A                  mov      dx, word ptr [bp + 0xa]
00003633  8B 46 08                  mov      ax, word ptr [bp + 8]
00003636  89 56 F4                  mov      word ptr [bp - 0xc], dx
00003639  89 46 F2                  mov      word ptr [bp - 0xe], ax
0000363C  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
0000363F  89 46 F8                  mov      word ptr [bp - 8], ax
00003642  EB 7D                     jmp      0x36c1
00003644  FF 4E F8                  dec      word ptr [bp - 8]
00003647  C4 5E F2                  les      bx, ptr [bp - 0xe]
0000364A  FF 46 F2                  inc      word ptr [bp - 0xe]
0000364D  26 8A 07                  mov      al, byte ptr es:[bx]
00003650  88 46 F7                  mov      byte ptr [bp - 9], al
00003653  3C 0A                     cmp      al, 0xa
00003655  75 0A                     jne      0x3661
00003657  C4 5E FA                  les      bx, ptr [bp - 6]
0000365A  26 C6 07 0D               mov      byte ptr es:[bx], 0xd
0000365E  FF 46 FA                  inc      word ptr [bp - 6]
00003661  C4 5E FA                  les      bx, ptr [bp - 6]
00003664  8A 46 F7                  mov      al, byte ptr [bp - 9]
00003667  26 88 07                  mov      byte ptr es:[bx], al
0000366A  FF 46 FA                  inc      word ptr [bp - 6]
0000366D  8D 86 70 FF               lea      ax, [bp - 0x90]
00003671  8B 56 FA                  mov      dx, word ptr [bp - 6]
00003674  33 DB                     xor      bx, bx
00003676  2B D0                     sub      dx, ax
00003678  83 DB 00                  sbb      bx, 0
0000367B  0B DB                     or       bx, bx
0000367D  7C 4C                     jl       0x36cb
0000367F  75 06                     jne      0x3687
00003681  81 FA 80 00               cmp      dx, 0x80
00003685  72 44                     jb       0x36cb
00003687  8D 86 70 FF               lea      ax, [bp - 0x90]
0000368B  8B 56 FA                  mov      dx, word ptr [bp - 6]
0000368E  33 DB                     xor      bx, bx
00003690  2B D0                     sub      dx, ax
00003692  83 DB 00                  sbb      bx, 0
00003695  89 56 FE                  mov      word ptr [bp - 2], dx
00003698  52                        push     dx
00003699  16                        push     ss
0000369A  50                        push     ax
0000369B  FF 76 06                  push     word ptr [bp + 6]
0000369E  90                        nop      
0000369F  0E                        push     cs
000036A0  E8 56 07                  call     0x3df9
000036A3  83 C4 08                  add      sp, 8
000036A6  8B D0                     mov      dx, ax
000036A8  3B 46 FE                  cmp      ax, word ptr [bp - 2]
000036AB  74 14                     je       0x36c1
000036AD  83 FA FF                  cmp      dx, -1
000036B0  75 05                     jne      0x36b7
000036B2  B8 FF FF                  mov      ax, 0xffff
000036B5  EB 5F                     jmp      0x3716
000036B7  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
000036BA  2B 46 F8                  sub      ax, word ptr [bp - 8]
000036BD  03 C2                     add      ax, dx
000036BF  EB 52                     jmp      0x3713
000036C1  8D 86 70 FF               lea      ax, [bp - 0x90]
000036C5  8C 56 FC                  mov      word ptr [bp - 4], ss
000036C8  89 46 FA                  mov      word ptr [bp - 6], ax
000036CB  83 7E F8 00               cmp      word ptr [bp - 8], 0
000036CF  74 03                     je       0x36d4
000036D1  E9 70 FF                  jmp      0x3644
000036D4  8D 86 70 FF               lea      ax, [bp - 0x90]
000036D8  8B 56 FA                  mov      dx, word ptr [bp - 6]
000036DB  33 DB                     xor      bx, bx
000036DD  2B D0                     sub      dx, ax
000036DF  83 DB 00                  sbb      bx, 0
000036E2  89 56 FE                  mov      word ptr [bp - 2], dx
000036E5  8B C2                     mov      ax, dx
000036E7  0B C0                     or       ax, ax
000036E9  76 2D                     jbe      0x3718
000036EB  52                        push     dx
000036EC  16                        push     ss
000036ED  8D 86 70 FF               lea      ax, [bp - 0x90]
000036F1  50                        push     ax
000036F2  FF 76 06                  push     word ptr [bp + 6]
000036F5  90                        nop      
000036F6  0E                        push     cs
000036F7  E8 FF 06                  call     0x3df9
000036FA  83 C4 08                  add      sp, 8
000036FD  8B D0                     mov      dx, ax
000036FF  3B 46 FE                  cmp      ax, word ptr [bp - 2]
00003702  74 14                     je       0x3718
00003704  83 FA FF                  cmp      dx, -1
00003707  75 05                     jne      0x370e
00003709  B8 FF FF                  mov      ax, 0xffff
0000370C  EB 08                     jmp      0x3716
0000370E  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
00003711  03 C2                     add      ax, dx
00003713  2B 46 FE                  sub      ax, word ptr [bp - 2]
00003716  EB 03                     jmp      0x371b
00003718  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
0000371B  5F                        pop      di
0000371C  5E                        pop      si
0000371D  8B E5                     mov      sp, bp
0000371F  5D                        pop      bp
00003720  CB                        retf     
00003721  55                        push     bp
00003722  8B EC                     mov      bp, sp
00003724  83 EC 06                  sub      sp, 6
00003727  56                        push     si
00003728  57                        push     di
00003729  C7 46 FA 00 00            mov      word ptr [bp - 6], 0
0000372E  8C 5E FE                  mov      word ptr [bp - 2], ds
00003731  C7 46 FC 8C 1D            mov      word ptr [bp - 4], 0x1d8c
00003736  EB 24                     jmp      0x375c
00003738  C4 5E FC                  les      bx, ptr [bp - 4]
0000373B  26 F7 47 02 03 00         test     word ptr es:[bx + 2], 3
00003741  74 12                     je       0x3755
00003743  26 83 7F 10 00            cmp      word ptr es:[bx + 0x10], 0
00003748  74 0B                     je       0x3755
0000374A  FF 76 FE                  push     word ptr [bp - 2]
0000374D  53                        push     bx
0000374E  90                        nop      
0000374F  0E                        push     cs
00003750  E8 37 EE                  call     0x258a
00003753  59                        pop      cx
00003754  59                        pop      cx
00003755  83 46 FC 14               add      word ptr [bp - 4], 0x14
00003759  FF 46 FA                  inc      word ptr [bp - 6]
0000375C  8B 46 FA                  mov      ax, word ptr [bp - 6]
0000375F  3B 06 74 21               cmp      ax, word ptr [0x2174]
00003763  72 D3                     jb       0x3738
00003765  5F                        pop      di
00003766  5E                        pop      si
00003767  8B E5                     mov      sp, bp
00003769  5D                        pop      bp
0000376A  CB                        retf     
0000376B  55                        push     bp
0000376C  8B EC                     mov      bp, sp
0000376E  83 EC 06                  sub      sp, 6
00003771  56                        push     si
00003772  57                        push     di
00003773  C7 46 FA 00 00            mov      word ptr [bp - 6], 0
00003778  8C 5E FE                  mov      word ptr [bp - 2], ds
0000377B  C7 46 FC 8C 1D            mov      word ptr [bp - 4], 0x1d8c
00003780  EB 23                     jmp      0x37a5
00003782  C4 5E FC                  les      bx, ptr [bp - 4]
00003785  26 F7 47 02 03 00         test     word ptr es:[bx + 2], 3
0000378B  74 11                     je       0x379e
0000378D  26 83 3F 00               cmp      word ptr es:[bx], 0
00003791  7D 0B                     jge      0x379e
00003793  FF 76 FE                  push     word ptr [bp - 2]
00003796  53                        push     bx
00003797  90                        nop      
00003798  0E                        push     cs
00003799  E8 AF EE                  call     0x264b
0000379C  59                        pop      cx
0000379D  59                        pop      cx
0000379E  83 46 FC 14               add      word ptr [bp - 4], 0x14
000037A2  FF 46 FA                  inc      word ptr [bp - 6]
000037A5  8B 46 FA                  mov      ax, word ptr [bp - 6]
000037A8  3B 06 74 21               cmp      ax, word ptr [0x2174]
000037AC  72 D4                     jb       0x3782
000037AE  5F                        pop      di
000037AF  5E                        pop      si
000037B0  8B E5                     mov      sp, bp
000037B2  5D                        pop      bp
000037B3  CB                        retf     
000037B4  55                        push     bp
000037B5  8B EC                     mov      bp, sp
000037B7  56                        push     si
000037B8  57                        push     di
000037B9  1E                        push     ds
000037BA  8B 4E 0C                  mov      cx, word ptr [bp + 0xc]
000037BD  B4 43                     mov      ah, 0x43
000037BF  8A 46 0A                  mov      al, byte ptr [bp + 0xa]
000037C2  C5 56 06                  lds      dx, ptr [bp + 6]
000037C5  CD 21                     int      0x21
000037C7  1F                        pop      ds
000037C8  72 03                     jb       0x37cd
000037CA  91                        xchg     cx, ax
000037CB  EB 04                     jmp      0x37d1
000037CD  50                        push     ax
000037CE  E8 B3 E7                  call     0x1f84
000037D1  5F                        pop      di
000037D2  5E                        pop      si
000037D3  5D                        pop      bp
000037D4  CB                        retf     
000037D5  55                        push     bp
000037D6  8B EC                     mov      bp, sp
000037D8  56                        push     si
000037D9  57                        push     di
000037DA  B4 3E                     mov      ah, 0x3e
000037DC  8B 5E 06                  mov      bx, word ptr [bp + 6]
000037DF  CD 21                     int      0x21
000037E1  72 0C                     jb       0x37ef
000037E3  03 DB                     add      bx, bx
000037E5  C7 87 76 21 00 00         mov      word ptr [bx + 0x2176], 0
000037EB  33 C0                     xor      ax, ax
000037ED  EB 04                     jmp      0x37f3
000037EF  50                        push     ax
000037F0  E8 91 E7                  call     0x1f84
000037F3  5F                        pop      di
000037F4  5E                        pop      si
000037F5  5D                        pop      bp
000037F6  CB                        retf     
000037F7  55                        push     bp
000037F8  8B EC                     mov      bp, sp
000037FA  56                        push     si
000037FB  57                        push     di
000037FC  FF 76 06                  push     word ptr [bp + 6]
000037FF  0E                        push     cs
00003800  E8 D2 FF                  call     0x37d5
00003803  59                        pop      cx
00003804  5F                        pop      di
00003805  5E                        pop      si
00003806  5D                        pop      bp
00003807  CB                        retf     
00003808  55                        push     bp
00003809  8B EC                     mov      bp, sp
0000380B  83 EC 04                  sub      sp, 4
0000380E  56                        push     si
0000380F  57                        push     di
00003810  8B 46 06                  mov      ax, word ptr [bp + 6]
00003813  3B 06 74 21               cmp      ax, word ptr [0x2174]
00003817  72 06                     jb       0x381f
00003819  B8 06 00                  mov      ax, 6
0000381C  50                        push     ax
0000381D  EB 5E                     jmp      0x387d
0000381F  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003822  03 DB                     add      bx, bx
00003824  F7 87 76 21 00 02         test     word ptr [bx + 0x2176], 0x200
0000382A  74 05                     je       0x3831
0000382C  B8 01 00                  mov      ax, 1
0000382F  EB 4F                     jmp      0x3880
00003831  B8 00 44                  mov      ax, 0x4400
00003834  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003837  CD 21                     int      0x21
00003839  72 41                     jb       0x387c
0000383B  F6 C2 80                  test     dl, 0x80
0000383E  75 38                     jne      0x3878
00003840  B8 01 42                  mov      ax, 0x4201
00003843  33 C9                     xor      cx, cx
00003845  8B D1                     mov      dx, cx
00003847  CD 21                     int      0x21
00003849  72 31                     jb       0x387c
0000384B  52                        push     dx
0000384C  50                        push     ax
0000384D  B8 02 42                  mov      ax, 0x4202
00003850  33 C9                     xor      cx, cx
00003852  8B D1                     mov      dx, cx
00003854  CD 21                     int      0x21
00003856  89 46 FC                  mov      word ptr [bp - 4], ax
00003859  89 56 FE                  mov      word ptr [bp - 2], dx
0000385C  5A                        pop      dx
0000385D  59                        pop      cx
0000385E  72 1C                     jb       0x387c
00003860  B8 00 42                  mov      ax, 0x4200
00003863  CD 21                     int      0x21
00003865  72 15                     jb       0x387c
00003867  3B 56 FE                  cmp      dx, word ptr [bp - 2]
0000386A  72 0C                     jb       0x3878
0000386C  77 05                     ja       0x3873
0000386E  3B 46 FC                  cmp      ax, word ptr [bp - 4]
00003871  72 05                     jb       0x3878
00003873  B8 01 00                  mov      ax, 1
00003876  EB 08                     jmp      0x3880
00003878  33 C0                     xor      ax, ax
0000387A  EB 04                     jmp      0x3880
0000387C  50                        push     ax
0000387D  E8 04 E7                  call     0x1f84
00003880  5F                        pop      di
00003881  5E                        pop      si
00003882  8B E5                     mov      sp, bp
00003884  5D                        pop      bp
00003885  CB                        retf     
00003886  55                        push     bp
00003887  8B EC                     mov      bp, sp
00003889  56                        push     si
0000388A  57                        push     di
0000388B  1E                        push     ds
0000388C  B4 2F                     mov      ah, 0x2f
0000388E  CD 21                     int      0x21
00003890  06                        push     es
00003891  53                        push     bx
00003892  B4 1A                     mov      ah, 0x1a
00003894  C5 56 0A                  lds      dx, ptr [bp + 0xa]
00003897  CD 21                     int      0x21
00003899  B4 4E                     mov      ah, 0x4e
0000389B  8B 4E 0E                  mov      cx, word ptr [bp + 0xe]
0000389E  C5 56 06                  lds      dx, ptr [bp + 6]
000038A1  CD 21                     int      0x21
000038A3  9C                        pushf    
000038A4  59                        pop      cx
000038A5  93                        xchg     bx, ax
000038A6  B4 1A                     mov      ah, 0x1a
000038A8  5A                        pop      dx
000038A9  1F                        pop      ds
000038AA  CD 21                     int      0x21
000038AC  51                        push     cx
000038AD  9D                        popf     
000038AE  1F                        pop      ds
000038AF  72 04                     jb       0x38b5
000038B1  33 C0                     xor      ax, ax
000038B3  EB 04                     jmp      0x38b9
000038B5  53                        push     bx
000038B6  E8 CB E6                  call     0x1f84
000038B9  5F                        pop      di
000038BA  5E                        pop      si
000038BB  5D                        pop      bp
000038BC  CB                        retf     
000038BD  55                        push     bp
000038BE  8B EC                     mov      bp, sp
000038C0  56                        push     si
000038C1  57                        push     di
000038C2  1E                        push     ds
000038C3  B4 2F                     mov      ah, 0x2f
000038C5  CD 21                     int      0x21
000038C7  06                        push     es
000038C8  53                        push     bx
000038C9  B4 1A                     mov      ah, 0x1a
000038CB  C5 56 06                  lds      dx, ptr [bp + 6]
000038CE  CD 21                     int      0x21
000038D0  B4 4F                     mov      ah, 0x4f
000038D2  CD 21                     int      0x21
000038D4  9C                        pushf    
000038D5  59                        pop      cx
000038D6  93                        xchg     bx, ax
000038D7  B4 1A                     mov      ah, 0x1a
000038D9  5A                        pop      dx
000038DA  1F                        pop      ds
000038DB  CD 21                     int      0x21
000038DD  51                        push     cx
000038DE  9D                        popf     
000038DF  1F                        pop      ds
000038E0  72 04                     jb       0x38e6
000038E2  33 C0                     xor      ax, ax
000038E4  EB 04                     jmp      0x38ea
000038E6  53                        push     bx
000038E7  E8 9A E6                  call     0x1f84
000038EA  5F                        pop      di
000038EB  5E                        pop      si
000038EC  5D                        pop      bp
000038ED  CB                        retf     
000038EE  55                        push     bp
000038EF  8B EC                     mov      bp, sp
000038F1  83 EC 06                  sub      sp, 6
000038F4  56                        push     si
000038F5  57                        push     di
000038F6  C7 46 FA 32 00            mov      word ptr [bp - 6], 0x32
000038FB  8C 5E FE                  mov      word ptr [bp - 2], ds
000038FE  C7 46 FC 8C 1D            mov      word ptr [bp - 4], 0x1d8c
00003903  EB 1E                     jmp      0x3923
00003905  C4 5E FC                  les      bx, ptr [bp - 4]
00003908  26 8B 47 02               mov      ax, word ptr es:[bx + 2]
0000390C  25 00 03                  and      ax, 0x300
0000390F  3D 00 03                  cmp      ax, 0x300
00003912  75 0B                     jne      0x391f
00003914  FF 76 FE                  push     word ptr [bp - 2]
00003917  53                        push     bx
00003918  90                        nop      
00003919  0E                        push     cs
0000391A  E8 2E ED                  call     0x264b
0000391D  59                        pop      cx
0000391E  59                        pop      cx
0000391F  83 46 FC 14               add      word ptr [bp - 4], 0x14
00003923  8B 46 FA                  mov      ax, word ptr [bp - 6]
00003926  FF 4E FA                  dec      word ptr [bp - 6]
00003929  0B C0                     or       ax, ax
0000392B  75 D8                     jne      0x3905
0000392D  5F                        pop      di
0000392E  5E                        pop      si
0000392F  8B E5                     mov      sp, bp
00003931  5D                        pop      bp
00003932  C3                        ret      
00003933  55                        push     bp
00003934  8B EC                     mov      bp, sp
00003936  56                        push     si
00003937  57                        push     di
00003938  C4 5E 04                  les      bx, ptr [bp + 4]
0000393B  26 F7 47 02 00 02         test     word ptr es:[bx + 2], 0x200
00003941  74 03                     je       0x3946
00003943  E8 A8 FF                  call     0x38ee
00003946  C4 5E 04                  les      bx, ptr [bp + 4]
00003949  26 FF 77 06               push     word ptr es:[bx + 6]
0000394D  26 8B 57 0A               mov      dx, word ptr es:[bx + 0xa]
00003951  26 8B 47 08               mov      ax, word ptr es:[bx + 8]
00003955  26 89 57 0E               mov      word ptr es:[bx + 0xe], dx
00003959  26 89 47 0C               mov      word ptr es:[bx + 0xc], ax
0000395D  52                        push     dx
0000395E  50                        push     ax
0000395F  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00003963  98                        cwde     
00003964  50                        push     ax
00003965  90                        nop      
00003966  0E                        push     cs
00003967  E8 BE 03                  call     0x3d28
0000396A  83 C4 08                  add      sp, 8
0000396D  C4 5E 04                  les      bx, ptr [bp + 4]
00003970  26 89 07                  mov      word ptr es:[bx], ax
00003973  0B C0                     or       ax, ax
00003975  7E 09                     jle      0x3980
00003977  26 83 67 02 DF            and      word ptr es:[bx + 2], 0xffdf
0000397C  33 C0                     xor      ax, ax
0000397E  EB 29                     jmp      0x39a9
00003980  C4 5E 04                  les      bx, ptr [bp + 4]
00003983  26 83 3F 00               cmp      word ptr es:[bx], 0
00003987  75 10                     jne      0x3999
00003989  26 8B 47 02               mov      ax, word ptr es:[bx + 2]
0000398D  25 7F FE                  and      ax, 0xfe7f
00003990  0D 20 00                  or       ax, 0x20
00003993  26 89 47 02               mov      word ptr es:[bx + 2], ax
00003997  EB 0D                     jmp      0x39a6
00003999  C4 5E 04                  les      bx, ptr [bp + 4]
0000399C  26 C7 07 00 00            mov      word ptr es:[bx], 0
000039A1  26 83 4F 02 10            or       word ptr es:[bx + 2], 0x10
000039A6  B8 FF FF                  mov      ax, 0xffff
000039A9  5F                        pop      di
000039AA  5E                        pop      si
000039AB  5D                        pop      bp
000039AC  C2 04 00                  ret      4
000039AF  55                        push     bp
000039B0  8B EC                     mov      bp, sp
000039B2  56                        push     si
000039B3  57                        push     di
000039B4  C4 5E 06                  les      bx, ptr [bp + 6]
000039B7  26 FF 07                  inc      word ptr es:[bx]
000039BA  FF 76 08                  push     word ptr [bp + 8]
000039BD  FF 76 06                  push     word ptr [bp + 6]
000039C0  0E                        push     cs
000039C1  E8 09 00                  call     0x39cd
000039C4  59                        pop      cx
000039C5  59                        pop      cx
000039C6  5F                        pop      di
000039C7  5E                        pop      si
000039C8  5D                        pop      bp
000039C9  CB                        retf     
000039CA  58                        pop      ax
000039CB  0E                        push     cs
000039CC  50                        push     ax
000039CD  55                        push     bp
000039CE  8B EC                     mov      bp, sp
000039D0  56                        push     si
000039D1  57                        push     di
000039D2  8B 46 06                  mov      ax, word ptr [bp + 6]
000039D5  0B 46 08                  or       ax, word ptr [bp + 8]
000039D8  75 03                     jne      0x39dd
000039DA  E9 CA 00                  jmp      0x3aa7
000039DD  C4 5E 06                  les      bx, ptr [bp + 6]
000039E0  26 83 3F 00               cmp      word ptr es:[bx], 0
000039E4  7E 05                     jle      0x39eb
000039E6  26 FF 0F                  dec      word ptr es:[bx]
000039E9  EB 48                     jmp      0x3a33
000039EB  C4 5E 06                  les      bx, ptr [bp + 6]
000039EE  26 83 3F 00               cmp      word ptr es:[bx], 0
000039F2  7C 10                     jl       0x3a04
000039F4  26 F7 47 02 10 01         test     word ptr es:[bx + 2], 0x110
000039FA  75 08                     jne      0x3a04
000039FC  26 F7 47 02 01 00         test     word ptr es:[bx + 2], 1
00003A02  75 0B                     jne      0x3a0f
00003A04  C4 5E 06                  les      bx, ptr [bp + 6]
00003A07  26 83 4F 02 10            or       word ptr es:[bx + 2], 0x10
00003A0C  E9 98 00                  jmp      0x3aa7
00003A0F  C4 5E 06                  les      bx, ptr [bp + 6]
00003A12  26 81 4F 02 80 00         or       word ptr es:[bx + 2], 0x80
00003A18  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003A1B  26 83 7F 06 00            cmp      word ptr es:[bx + 6], 0
00003A20  74 2A                     je       0x3a4c
00003A22  FF 76 08                  push     word ptr [bp + 8]
00003A25  53                        push     bx
00003A26  E8 0A FF                  call     0x3933
00003A29  0B C0                     or       ax, ax
00003A2B  75 7A                     jne      0x3aa7
00003A2D  C4 5E 06                  les      bx, ptr [bp + 6]
00003A30  26 FF 0F                  dec      word ptr es:[bx]
00003A33  C4 5E 06                  les      bx, ptr [bp + 6]
00003A36  26 8B 57 0E               mov      dx, word ptr es:[bx + 0xe]
00003A3A  26 8B 77 0C               mov      si, word ptr es:[bx + 0xc]
00003A3E  26 FF 47 0C               inc      word ptr es:[bx + 0xc]
00003A42  8E C2                     mov      es, dx
00003A44  26 8A 04                  mov      al, byte ptr es:[si]
00003A47  B4 00                     mov      ah, 0
00003A49  E9 7F 00                  jmp      0x3acb
00003A4C  C4 5E 06                  les      bx, ptr [bp + 6]
00003A4F  26 F7 47 02 00 02         test     word ptr es:[bx + 2], 0x200
00003A55  74 03                     je       0x3a5a
00003A57  E8 94 FE                  call     0x38ee
00003A5A  B8 01 00                  mov      ax, 1
00003A5D  50                        push     ax
00003A5E  1E                        push     ds
00003A5F  B8 26 58                  mov      ax, 0x5826
00003A62  50                        push     ax
00003A63  C4 5E 06                  les      bx, ptr [bp + 6]
00003A66  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00003A6A  98                        cwde     
00003A6B  50                        push     ax
00003A6C  90                        nop      
00003A6D  0E                        push     cs
00003A6E  E8 B7 02                  call     0x3d28
00003A71  83 C4 08                  add      sp, 8
00003A74  0B C0                     or       ax, ax
00003A76  75 34                     jne      0x3aac
00003A78  C4 5E 06                  les      bx, ptr [bp + 6]
00003A7B  26 8A 47 04               mov      al, byte ptr es:[bx + 4]
00003A7F  98                        cwde     
00003A80  50                        push     ax
00003A81  90                        nop      
00003A82  0E                        push     cs
00003A83  E8 82 FD                  call     0x3808
00003A86  59                        pop      cx
00003A87  3D 01 00                  cmp      ax, 1
00003A8A  74 0A                     je       0x3a96
00003A8C  C4 5E 06                  les      bx, ptr [bp + 6]
00003A8F  26 83 4F 02 10            or       word ptr es:[bx + 2], 0x10
00003A94  EB 11                     jmp      0x3aa7
00003A96  C4 5E 06                  les      bx, ptr [bp + 6]
00003A99  26 8B 47 02               mov      ax, word ptr es:[bx + 2]
00003A9D  25 7F FE                  and      ax, 0xfe7f
00003AA0  0D 20 00                  or       ax, 0x20
00003AA3  26 89 47 02               mov      word ptr es:[bx + 2], ax
00003AA7  B8 FF FF                  mov      ax, 0xffff
00003AAA  EB 1F                     jmp      0x3acb
00003AAC  80 3E 26 58 0D            cmp      byte ptr [0x5826], 0xd
00003AB1  75 0B                     jne      0x3abe
00003AB3  C4 5E 06                  les      bx, ptr [bp + 6]
00003AB6  26 F7 47 02 40 00         test     word ptr es:[bx + 2], 0x40
00003ABC  74 8E                     je       0x3a4c
00003ABE  C4 5E 06                  les      bx, ptr [bp + 6]
00003AC1  26 83 67 02 DF            and      word ptr es:[bx + 2], 0xffdf
00003AC6  A0 26 58                  mov      al, byte ptr [0x5826]
00003AC9  B4 00                     mov      ah, 0
00003ACB  5F                        pop      di
00003ACC  5E                        pop      si
00003ACD  5D                        pop      bp
00003ACE  CB                        retf     
00003ACF  56                        push     si
00003AD0  57                        push     di
00003AD1  1E                        push     ds
00003AD2  B8 8C 1D                  mov      ax, 0x1d8c
00003AD5  50                        push     ax
00003AD6  0E                        push     cs
00003AD7  E8 F3 FE                  call     0x39cd
00003ADA  59                        pop      cx
00003ADB  59                        pop      cx
00003ADC  5F                        pop      di
00003ADD  5E                        pop      si
00003ADE  CB                        retf     
00003ADF  55                        push     bp
00003AE0  8B EC                     mov      bp, sp
00003AE2  56                        push     si
00003AE3  57                        push     di
00003AE4  1E                        push     ds
00003AE5  8B 4E 04                  mov      cx, word ptr [bp + 4]
00003AE8  B4 3C                     mov      ah, 0x3c
00003AEA  C5 56 06                  lds      dx, ptr [bp + 6]
00003AED  CD 21                     int      0x21
00003AEF  1F                        pop      ds
00003AF0  72 02                     jb       0x3af4
00003AF2  EB 04                     jmp      0x3af8
00003AF4  50                        push     ax
00003AF5  E8 8C E4                  call     0x1f84
00003AF8  5F                        pop      di
00003AF9  5E                        pop      si
00003AFA  5D                        pop      bp
00003AFB  C2 06 00                  ret      6
00003AFE  55                        push     bp
00003AFF  8B EC                     mov      bp, sp
00003B01  56                        push     si
00003B02  57                        push     di
00003B03  8B 5E 04                  mov      bx, word ptr [bp + 4]
00003B06  2B C9                     sub      cx, cx
00003B08  2B D2                     sub      dx, dx
00003B0A  B4 40                     mov      ah, 0x40
00003B0C  CD 21                     int      0x21
00003B0E  5F                        pop      di
00003B0F  5E                        pop      si
00003B10  5D                        pop      bp
00003B11  C2 02 00                  ret      2
00003B14  55                        push     bp
00003B15  8B EC                     mov      bp, sp
00003B17  83 EC 08                  sub      sp, 8
00003B1A  56                        push     si
00003B1B  57                        push     di
00003B1C  F7 46 0A 00 C0            test     word ptr [bp + 0xa], 0xc000
00003B21  75 09                     jne      0x3b2c
00003B23  A1 DA 21                  mov      ax, word ptr [0x21da]
00003B26  25 00 C0                  and      ax, 0xc000
00003B29  09 46 0A                  or       word ptr [bp + 0xa], ax
00003B2C  A1 7E 00                  mov      ax, word ptr [0x7e]
00003B2F  89 46 FA                  mov      word ptr [bp - 6], ax
00003B32  33 C0                     xor      ax, ax
00003B34  50                        push     ax
00003B35  FF 76 08                  push     word ptr [bp + 8]
00003B38  FF 76 06                  push     word ptr [bp + 6]
00003B3B  90                        nop      
00003B3C  0E                        push     cs
00003B3D  E8 74 FC                  call     0x37b4
00003B40  83 C4 06                  add      sp, 6
00003B43  89 46 FE                  mov      word ptr [bp - 2], ax
00003B46  83 7E FE FF               cmp      word ptr [bp - 2], -1
00003B4A  75 0D                     jne      0x3b59
00003B4C  83 3E E8 21 02            cmp      word ptr [0x21e8], 2
00003B51  74 06                     je       0x3b59
00003B53  FF 36 E8 21               push     word ptr [0x21e8]
00003B57  EB 63                     jmp      0x3bbc
00003B59  8B 46 FA                  mov      ax, word ptr [bp - 6]
00003B5C  A3 7E 00                  mov      word ptr [0x7e], ax
00003B5F  F7 46 0A 00 01            test     word ptr [bp + 0xa], 0x100
00003B64  75 02                     jne      0x3b68
00003B66  EB 7E                     jmp      0x3be6
00003B68  A1 DC 21                  mov      ax, word ptr [0x21dc]
00003B6B  21 46 0C                  and      word ptr [bp + 0xc], ax
00003B6E  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
00003B71  A9 80 01                  test     ax, 0x180
00003B74  75 07                     jne      0x3b7d
00003B76  B8 01 00                  mov      ax, 1
00003B79  50                        push     ax
00003B7A  E8 07 E4                  call     0x1f84
00003B7D  83 7E FE FF               cmp      word ptr [bp - 2], -1
00003B81  75 2E                     jne      0x3bb1
00003B83  F7 46 0C 80 00            test     word ptr [bp + 0xc], 0x80
00003B88  74 04                     je       0x3b8e
00003B8A  33 C0                     xor      ax, ax
00003B8C  EB 03                     jmp      0x3b91
00003B8E  B8 01 00                  mov      ax, 1
00003B91  89 46 FE                  mov      word ptr [bp - 2], ax
00003B94  F7 46 0A F0 00            test     word ptr [bp + 0xa], 0xf0
00003B99  74 32                     je       0x3bcd
00003B9B  FF 76 08                  push     word ptr [bp + 8]
00003B9E  FF 76 06                  push     word ptr [bp + 6]
00003BA1  33 C0                     xor      ax, ax
00003BA3  50                        push     ax
00003BA4  E8 38 FF                  call     0x3adf
00003BA7  89 46 F8                  mov      word ptr [bp - 8], ax
00003BAA  0B C0                     or       ax, ax
00003BAC  7D 14                     jge      0x3bc2
00003BAE  E9 02 01                  jmp      0x3cb3
00003BB1  F7 46 0A 00 04            test     word ptr [bp + 0xa], 0x400
00003BB6  74 2E                     je       0x3be6
00003BB8  B8 50 00                  mov      ax, 0x50
00003BBB  50                        push     ax
00003BBC  E8 C5 E3                  call     0x1f84
00003BBF  E9 F4 00                  jmp      0x3cb6
00003BC2  FF 76 F8                  push     word ptr [bp - 8]
00003BC5  90                        nop      
00003BC6  0E                        push     cs
00003BC7  E8 0B FC                  call     0x37d5
00003BCA  59                        pop      cx
00003BCB  EB 19                     jmp      0x3be6
00003BCD  FF 76 08                  push     word ptr [bp + 8]
00003BD0  FF 76 06                  push     word ptr [bp + 6]
00003BD3  FF 76 FE                  push     word ptr [bp - 2]
00003BD6  E8 06 FF                  call     0x3adf
00003BD9  89 46 F8                  mov      word ptr [bp - 8], ax
00003BDC  0B C0                     or       ax, ax
00003BDE  7C 03                     jl       0x3be3
00003BE0  E9 8C 00                  jmp      0x3c6f
00003BE3  E9 CD 00                  jmp      0x3cb3
00003BE6  FF 76 0A                  push     word ptr [bp + 0xa]
00003BE9  FF 76 08                  push     word ptr [bp + 8]
00003BEC  FF 76 06                  push     word ptr [bp + 6]
00003BEF  90                        nop      
00003BF0  0E                        push     cs
00003BF1  E8 C8 00                  call     0x3cbc
00003BF4  83 C4 06                  add      sp, 6
00003BF7  89 46 F8                  mov      word ptr [bp - 8], ax
00003BFA  0B C0                     or       ax, ax
00003BFC  7C 71                     jl       0x3c6f
00003BFE  33 C0                     xor      ax, ax
00003C00  50                        push     ax
00003C01  FF 76 F8                  push     word ptr [bp - 8]
00003C04  90                        nop      
00003C05  0E                        push     cs
00003C06  E8 4C 02                  call     0x3e55
00003C09  59                        pop      cx
00003C0A  59                        pop      cx
00003C0B  89 46 FC                  mov      word ptr [bp - 4], ax
00003C0E  A9 80 00                  test     ax, 0x80
00003C11  74 27                     je       0x3c3a
00003C13  81 4E 0A 00 20            or       word ptr [bp + 0xa], 0x2000
00003C18  F7 46 0A 00 80            test     word ptr [bp + 0xa], 0x8000
00003C1D  74 28                     je       0x3c47
00003C1F  25 FF 00                  and      ax, 0xff
00003C22  0D 20 00                  or       ax, 0x20
00003C25  33 D2                     xor      dx, dx
00003C27  52                        push     dx
00003C28  50                        push     ax
00003C29  B8 01 00                  mov      ax, 1
00003C2C  50                        push     ax
00003C2D  FF 76 F8                  push     word ptr [bp - 8]
00003C30  90                        nop      
00003C31  0E                        push     cs
00003C32  E8 20 02                  call     0x3e55
00003C35  83 C4 08                  add      sp, 8
00003C38  EB 0D                     jmp      0x3c47
00003C3A  F7 46 0A 00 02            test     word ptr [bp + 0xa], 0x200
00003C3F  74 06                     je       0x3c47
00003C41  FF 76 F8                  push     word ptr [bp - 8]
00003C44  E8 B7 FE                  call     0x3afe
00003C47  F7 46 FE 01 00            test     word ptr [bp - 2], 1
00003C4C  74 21                     je       0x3c6f
00003C4E  F7 46 0A 00 01            test     word ptr [bp + 0xa], 0x100
00003C53  74 1A                     je       0x3c6f
00003C55  F7 46 0A F0 00            test     word ptr [bp + 0xa], 0xf0
00003C5A  74 13                     je       0x3c6f
00003C5C  B8 01 00                  mov      ax, 1
00003C5F  50                        push     ax
00003C60  50                        push     ax
00003C61  FF 76 08                  push     word ptr [bp + 8]
00003C64  FF 76 06                  push     word ptr [bp + 6]
00003C67  90                        nop      
00003C68  0E                        push     cs
00003C69  E8 48 FB                  call     0x37b4
00003C6C  83 C4 08                  add      sp, 8
00003C6F  83 7E F8 00               cmp      word ptr [bp - 8], 0
00003C73  7C 3E                     jl       0x3cb3
00003C75  C7 06 1A 27 00 00         mov      word ptr [0x271a], 0
00003C7B  C7 06 18 27 2F 1F         mov      word ptr [0x2718], 0x1f2f
00003C81  F7 46 0A 00 03            test     word ptr [bp + 0xa], 0x300
00003C86  74 05                     je       0x3c8d
00003C88  B8 00 10                  mov      ax, 0x1000
00003C8B  EB 02                     jmp      0x3c8f
00003C8D  33 C0                     xor      ax, ax
00003C8F  8B 56 0A                  mov      dx, word ptr [bp + 0xa]
00003C92  81 E2 FF F8               and      dx, 0xf8ff
00003C96  0B C2                     or       ax, dx
00003C98  50                        push     ax
00003C99  F7 46 FE 01 00            test     word ptr [bp - 2], 1
00003C9E  74 04                     je       0x3ca4
00003CA0  33 C0                     xor      ax, ax
00003CA2  EB 03                     jmp      0x3ca7
00003CA4  B8 00 01                  mov      ax, 0x100
00003CA7  5A                        pop      dx
00003CA8  0B D0                     or       dx, ax
00003CAA  8B 5E F8                  mov      bx, word ptr [bp - 8]
00003CAD  03 DB                     add      bx, bx
00003CAF  89 97 76 21               mov      word ptr [bx + 0x2176], dx
00003CB3  8B 46 F8                  mov      ax, word ptr [bp - 8]
00003CB6  5F                        pop      di
00003CB7  5E                        pop      si
00003CB8  8B E5                     mov      sp, bp
00003CBA  5D                        pop      bp
00003CBB  CB                        retf     
00003CBC  55                        push     bp
00003CBD  8B EC                     mov      bp, sp
00003CBF  83 EC 02                  sub      sp, 2
00003CC2  56                        push     si
00003CC3  57                        push     di
00003CC4  B0 01                     mov      al, 1
00003CC6  8B 4E 0A                  mov      cx, word ptr [bp + 0xa]
00003CC9  F7 C1 02 00               test     cx, 2
00003CCD  75 0A                     jne      0x3cd9
00003CCF  B0 02                     mov      al, 2
00003CD1  F7 C1 04 00               test     cx, 4
00003CD5  75 02                     jne      0x3cd9
00003CD7  B0 00                     mov      al, 0
00003CD9  1E                        push     ds
00003CDA  C5 56 06                  lds      dx, ptr [bp + 6]
00003CDD  B1 F0                     mov      cl, 0xf0
00003CDF  22 4E 0A                  and      cl, byte ptr [bp + 0xa]
00003CE2  0A C1                     or       al, cl
00003CE4  B4 3D                     mov      ah, 0x3d
00003CE6  CD 21                     int      0x21
00003CE8  1F                        pop      ds
00003CE9  72 1A                     jb       0x3d05
00003CEB  89 46 FE                  mov      word ptr [bp - 2], ax
00003CEE  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
00003CF1  25 FF B8                  and      ax, 0xb8ff
00003CF4  0D 00 80                  or       ax, 0x8000
00003CF7  8B 5E FE                  mov      bx, word ptr [bp - 2]
00003CFA  03 DB                     add      bx, bx
00003CFC  89 87 76 21               mov      word ptr [bx + 0x2176], ax
00003D00  8B 46 FE                  mov      ax, word ptr [bp - 2]
00003D03  EB 04                     jmp      0x3d09
00003D05  50                        push     ax
00003D06  E8 7B E2                  call     0x1f84
00003D09  5F                        pop      di
00003D0A  5E                        pop      si
00003D0B  8B E5                     mov      sp, bp
00003D0D  5D                        pop      bp
00003D0E  CB                        retf     
00003D0F  55                        push     bp
00003D10  8B EC                     mov      bp, sp
00003D12  56                        push     si
00003D13  57                        push     di
00003D14  FF 76 0A                  push     word ptr [bp + 0xa]
00003D17  FF 76 08                  push     word ptr [bp + 8]
00003D1A  FF 76 06                  push     word ptr [bp + 6]
00003D1D  0E                        push     cs
00003D1E  E8 9B FF                  call     0x3cbc
00003D21  83 C4 06                  add      sp, 6
00003D24  5F                        pop      di
00003D25  5E                        pop      si
00003D26  5D                        pop      bp
00003D27  CB                        retf     
00003D28  55                        push     bp
00003D29  8B EC                     mov      bp, sp
00003D2B  83 EC 04                  sub      sp, 4
00003D2E  56                        push     si
00003D2F  57                        push     di
00003D30  8B 46 06                  mov      ax, word ptr [bp + 6]
00003D33  3B 06 74 21               cmp      ax, word ptr [0x2174]
00003D37  72 0A                     jb       0x3d43
00003D39  B8 06 00                  mov      ax, 6
00003D3C  50                        push     ax
00003D3D  E8 44 E2                  call     0x1f84
00003D40  E9 B0 00                  jmp      0x3df3
00003D43  8B 46 0C                  mov      ax, word ptr [bp + 0xc]
00003D46  40                        inc      ax
00003D47  3D 02 00                  cmp      ax, 2
00003D4A  72 0D                     jb       0x3d59
00003D4C  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003D4F  03 DB                     add      bx, bx
00003D51  F7 87 76 21 00 02         test     word ptr [bx + 0x2176], 0x200
00003D57  74 05                     je       0x3d5e
00003D59  33 C0                     xor      ax, ax
00003D5B  E9 95 00                  jmp      0x3df3
00003D5E  FF 76 0C                  push     word ptr [bp + 0xc]
00003D61  FF 76 0A                  push     word ptr [bp + 0xa]
00003D64  FF 76 08                  push     word ptr [bp + 8]
00003D67  FF 76 06                  push     word ptr [bp + 6]
00003D6A  90                        nop      
00003D6B  0E                        push     cs
00003D6C  E8 A9 E2                  call     0x2018
00003D6F  83 C4 08                  add      sp, 8
00003D72  89 46 FE                  mov      word ptr [bp - 2], ax
00003D75  40                        inc      ax
00003D76  3D 02 00                  cmp      ax, 2
00003D79  72 0D                     jb       0x3d88
00003D7B  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003D7E  03 DB                     add      bx, bx
00003D80  F7 87 76 21 00 40         test     word ptr [bx + 0x2176], 0x4000
00003D86  75 05                     jne      0x3d8d
00003D88  8B 46 FE                  mov      ax, word ptr [bp - 2]
00003D8B  EB 66                     jmp      0x3df3
00003D8D  8B 4E FE                  mov      cx, word ptr [bp - 2]
00003D90  C4 76 08                  les      si, ptr [bp + 8]
00003D93  8B FE                     mov      di, si
00003D95  8B DE                     mov      bx, si
00003D97  FC                        cld      
00003D98  26 AC                     lodsb    al, byte ptr es:[si]
00003D9A  3C 1A                     cmp      al, 0x1a
00003D9C  74 30                     je       0x3dce
00003D9E  3C 0D                     cmp      al, 0xd
00003DA0  74 05                     je       0x3da7
00003DA2  AA                        stosb    byte ptr es:[di], al
00003DA3  E2 F3                     loop     0x3d98
00003DA5  EB 1F                     jmp      0x3dc6
00003DA7  E2 EF                     loop     0x3d98
00003DA9  06                        push     es
00003DAA  53                        push     bx
00003DAB  B8 01 00                  mov      ax, 1
00003DAE  50                        push     ax
00003DAF  8D 46 FD                  lea      ax, [bp - 3]
00003DB2  16                        push     ss
00003DB3  50                        push     ax
00003DB4  FF 76 06                  push     word ptr [bp + 6]
00003DB7  90                        nop      
00003DB8  0E                        push     cs
00003DB9  E8 8F E2                  call     0x204b
00003DBC  83 C4 08                  add      sp, 8
00003DBF  5B                        pop      bx
00003DC0  07                        pop      es
00003DC1  FC                        cld      
00003DC2  8A 46 FD                  mov      al, byte ptr [bp - 3]
00003DC5  AA                        stosb    byte ptr es:[di], al
00003DC6  3B FB                     cmp      di, bx
00003DC8  75 02                     jne      0x3dcc
00003DCA  EB 92                     jmp      0x3d5e
00003DCC  EB 22                     jmp      0x3df0
00003DCE  53                        push     bx
00003DCF  B8 01 00                  mov      ax, 1
00003DD2  50                        push     ax
00003DD3  F7 D9                     neg      cx
00003DD5  1B C0                     sbb      ax, ax
00003DD7  50                        push     ax
00003DD8  51                        push     cx
00003DD9  FF 76 06                  push     word ptr [bp + 6]
00003DDC  90                        nop      
00003DDD  0E                        push     cs
00003DDE  E8 0A E2                  call     0x1feb
00003DE1  83 C4 08                  add      sp, 8
00003DE4  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003DE7  03 DB                     add      bx, bx
00003DE9  81 8F 76 21 00 02         or       word ptr [bx + 0x2176], 0x200
00003DEF  5B                        pop      bx
00003DF0  2B FB                     sub      di, bx
00003DF2  97                        xchg     di, ax
00003DF3  5F                        pop      di
00003DF4  5E                        pop      si
00003DF5  8B E5                     mov      sp, bp
00003DF7  5D                        pop      bp
00003DF8  CB                        retf     
00003DF9  55                        push     bp
00003DFA  8B EC                     mov      bp, sp
00003DFC  56                        push     si
00003DFD  57                        push     di
00003DFE  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003E01  03 DB                     add      bx, bx
00003E03  F7 87 76 21 01 00         test     word ptr [bx + 0x2176], 1
00003E09  74 06                     je       0x3e11
00003E0B  B8 05 00                  mov      ax, 5
00003E0E  50                        push     ax
00003E0F  EB 21                     jmp      0x3e32
00003E11  1E                        push     ds
00003E12  B4 40                     mov      ah, 0x40
00003E14  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003E17  8B 4E 0C                  mov      cx, word ptr [bp + 0xc]
00003E1A  C5 56 08                  lds      dx, ptr [bp + 8]
00003E1D  CD 21                     int      0x21
00003E1F  1F                        pop      ds
00003E20  72 0F                     jb       0x3e31
00003E22  50                        push     ax
00003E23  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003E26  03 DB                     add      bx, bx
00003E28  81 8F 76 21 00 10         or       word ptr [bx + 0x2176], 0x1000
00003E2E  58                        pop      ax
00003E2F  EB 04                     jmp      0x3e35
00003E31  50                        push     ax
00003E32  E8 4F E1                  call     0x1f84
00003E35  5F                        pop      di
00003E36  5E                        pop      si
00003E37  5D                        pop      bp
00003E38  CB                        retf     
00003E39  55                        push     bp
00003E3A  8B EC                     mov      bp, sp
00003E3C  56                        push     si
00003E3D  57                        push     di
00003E3E  FF 76 0C                  push     word ptr [bp + 0xc]
00003E41  FF 76 0A                  push     word ptr [bp + 0xa]
00003E44  FF 76 08                  push     word ptr [bp + 8]
00003E47  FF 76 06                  push     word ptr [bp + 6]
00003E4A  0E                        push     cs
00003E4B  E8 AB FF                  call     0x3df9
00003E4E  83 C4 08                  add      sp, 8
00003E51  5F                        pop      di
00003E52  5E                        pop      si
00003E53  5D                        pop      bp
00003E54  CB                        retf     
00003E55  55                        push     bp
00003E56  8B EC                     mov      bp, sp
00003E58  56                        push     si
00003E59  57                        push     di
00003E5A  1E                        push     ds
00003E5B  C5 56 0A                  lds      dx, ptr [bp + 0xa]
00003E5E  B4 44                     mov      ah, 0x44
00003E60  8A 46 08                  mov      al, byte ptr [bp + 8]
00003E63  8B 5E 06                  mov      bx, word ptr [bp + 6]
00003E66  8B 4E 0E                  mov      cx, word ptr [bp + 0xe]
00003E69  CD 21                     int      0x21
00003E6B  1F                        pop      ds
00003E6C  72 0C                     jb       0x3e7a
00003E6E  83 7E 08 00               cmp      word ptr [bp + 8], 0
00003E72  75 04                     jne      0x3e78
00003E74  8B C2                     mov      ax, dx
00003E76  EB 06                     jmp      0x3e7e
00003E78  EB 04                     jmp      0x3e7e
00003E7A  50                        push     ax
00003E7B  E8 06 E1                  call     0x1f84
00003E7E  5F                        pop      di
00003E7F  5E                        pop      si
00003E80  5D                        pop      bp
00003E81  CB                        retf     
00003E82  56                        push     si
00003E83  57                        push     di
00003E84  8C DA                     mov      dx, ds
00003E86  B8 82 25                  mov      ax, 0x2582
00003E89  5F                        pop      di
00003E8A  5E                        pop      si
00003E8B  CB                        retf     
00003E8C  55                        push     bp
00003E8D  8B EC                     mov      bp, sp
00003E8F  56                        push     si
00003E90  57                        push     di
00003E91  FC                        cld      
00003E92  1E                        push     ds
00003E93  C5 76 06                  lds      si, ptr [bp + 6]
00003E96  8B D6                     mov      dx, si
00003E98  EB 0B                     jmp      0x3ea5
00003E9A  2C 41                     sub      al, 0x41
00003E9C  3C 19                     cmp      al, 0x19
00003E9E  77 05                     ja       0x3ea5
00003EA0  04 61                     add      al, 0x61
00003EA2  88 44 FF                  mov      byte ptr [si - 1], al
00003EA5  AC                        lodsb    al, byte ptr [si]
00003EA6  22 C0                     and      al, al
00003EA8  75 F0                     jne      0x3e9a
00003EAA  92                        xchg     dx, ax
00003EAB  8C DA                     mov      dx, ds
00003EAD  1F                        pop      ds
00003EAE  5F                        pop      di
00003EAF  5E                        pop      si
00003EB0  5D                        pop      bp
00003EB1  CB                        retf     
00003EB2  56                        push     si
00003EB3  96                        xchg     si, ax
00003EB4  92                        xchg     dx, ax
00003EB5  85 C0                     test     ax, ax
00003EB7  74 02                     je       0x3ebb
00003EB9  F7 E3                     mul      bx
00003EBB  E3 05                     jcxz     0x3ec2
00003EBD  91                        xchg     cx, ax
00003EBE  F7 E6                     mul      si
00003EC0  03 C1                     add      ax, cx
00003EC2  96                        xchg     si, ax
00003EC3  F7 E3                     mul      bx
00003EC5  03 D6                     add      dx, si
00003EC7  5E                        pop      si
00003EC8  CB                        retf     
00003EC9  59                        pop      cx
00003ECA  0E                        push     cs
00003ECB  51                        push     cx
00003ECC  33 C9                     xor      cx, cx
00003ECE  EB 16                     jmp      0x3ee6
00003ED0  59                        pop      cx
00003ED1  0E                        push     cs
00003ED2  51                        push     cx
00003ED3  B9 01 00                  mov      cx, 1
00003ED6  EB 0E                     jmp      0x3ee6
00003ED8  59                        pop      cx
00003ED9  0E                        push     cs
00003EDA  51                        push     cx
00003EDB  B9 02 00                  mov      cx, 2
00003EDE  EB 06                     jmp      0x3ee6
00003EE0  59                        pop      cx
00003EE1  0E                        push     cs
00003EE2  51                        push     cx
00003EE3  B9 03 00                  mov      cx, 3
00003EE6  55                        push     bp
00003EE7  56                        push     si
00003EE8  57                        push     di
00003EE9  8B EC                     mov      bp, sp
00003EEB  8B F9                     mov      di, cx
00003EED  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
00003EF0  8B 56 0C                  mov      dx, word ptr [bp + 0xc]
00003EF3  8B 5E 0E                  mov      bx, word ptr [bp + 0xe]
00003EF6  8B 4E 10                  mov      cx, word ptr [bp + 0x10]
00003EF9  0B C9                     or       cx, cx
00003EFB  75 08                     jne      0x3f05
00003EFD  0B D2                     or       dx, dx
00003EFF  74 69                     je       0x3f6a
00003F01  0B DB                     or       bx, bx
00003F03  74 65                     je       0x3f6a
00003F05  F7 C7 01 00               test     di, 1
00003F09  75 1C                     jne      0x3f27
00003F0B  0B D2                     or       dx, dx
00003F0D  79 0A                     jns      0x3f19
00003F0F  F7 DA                     neg      dx
00003F11  F7 D8                     neg      ax
00003F13  83 DA 00                  sbb      dx, 0
00003F16  83 CF 0C                  or       di, 0xc
00003F19  0B C9                     or       cx, cx
00003F1B  79 0A                     jns      0x3f27
00003F1D  F7 D9                     neg      cx
00003F1F  F7 DB                     neg      bx
00003F21  83 D9 00                  sbb      cx, 0
00003F24  83 F7 04                  xor      di, 4
00003F27  8B E9                     mov      bp, cx
00003F29  B9 20 00                  mov      cx, 0x20
00003F2C  57                        push     di
00003F2D  33 FF                     xor      di, di
00003F2F  33 F6                     xor      si, si
00003F31  D1 E0                     shl      ax, 1
00003F33  D1 D2                     rcl      dx, 1
00003F35  D1 D6                     rcl      si, 1
00003F37  D1 D7                     rcl      di, 1
00003F39  3B FD                     cmp      di, bp
00003F3B  72 0B                     jb       0x3f48
00003F3D  77 04                     ja       0x3f43
00003F3F  3B F3                     cmp      si, bx
00003F41  72 05                     jb       0x3f48
00003F43  2B F3                     sub      si, bx
00003F45  1B FD                     sbb      di, bp
00003F47  40                        inc      ax
00003F48  E2 E7                     loop     0x3f31
00003F4A  5B                        pop      bx
00003F4B  F7 C3 02 00               test     bx, 2
00003F4F  74 06                     je       0x3f57
00003F51  8B C6                     mov      ax, si
00003F53  8B D7                     mov      dx, di
00003F55  D1 EB                     shr      bx, 1
00003F57  F7 C3 04 00               test     bx, 4
00003F5B  74 07                     je       0x3f64
00003F5D  F7 DA                     neg      dx
00003F5F  F7 D8                     neg      ax
00003F61  83 DA 00                  sbb      dx, 0
00003F64  5F                        pop      di
00003F65  5E                        pop      si
00003F66  5D                        pop      bp
00003F67  CA 08 00                  retf     8
00003F6A  F7 F3                     div      bx
00003F6C  F7 C7 02 00               test     di, 2
00003F70  74 01                     je       0x3f73
00003F72  92                        xchg     dx, ax
00003F73  33 D2                     xor      dx, dx
00003F75  EB ED                     jmp      0x3f64
00003F77  5B                        pop      bx
00003F78  0E                        push     cs
00003F79  53                        push     bx
00003F7A  80 F9 10                  cmp      cl, 0x10
00003F7D  73 10                     jae      0x3f8f
00003F7F  8B D8                     mov      bx, ax
00003F81  D3 E0                     shl      ax, cl
00003F83  D3 E2                     shl      dx, cl
00003F85  F6 D9                     neg      cl
00003F87  80 C1 10                  add      cl, 0x10
00003F8A  D3 EB                     shr      bx, cl
00003F8C  0B D3                     or       dx, bx
00003F8E  CB                        retf     
00003F8F  80 E9 10                  sub      cl, 0x10
00003F92  92                        xchg     dx, ax
00003F93  33 C0                     xor      ax, ax
00003F95  D3 E2                     shl      dx, cl
00003F97  CB                        retf     
00003F98  56                        push     si
00003F99  96                        xchg     si, ax
00003F9A  92                        xchg     dx, ax
00003F9B  85 C0                     test     ax, ax
00003F9D  74 02                     je       0x3fa1
00003F9F  F7 E3                     mul      bx
00003FA1  E3 05                     jcxz     0x3fa8
00003FA3  91                        xchg     cx, ax
00003FA4  F7 E6                     mul      si
00003FA6  03 C1                     add      ax, cx
00003FA8  96                        xchg     si, ax
00003FA9  F7 E3                     mul      bx
00003FAB  03 D6                     add      dx, si
00003FAD  5E                        pop      si
00003FAE  C3                        ret      
00003FAF  55                        push     bp
00003FB0  8B EC                     mov      bp, sp
00003FB2  83 EC 22                  sub      sp, 0x22
00003FB5  56                        push     si
00003FB6  57                        push     di
00003FB7  06                        push     es
00003FB8  C4 7E 0A                  les      di, ptr [bp + 0xa]
00003FBB  8B 5E 08                  mov      bx, word ptr [bp + 8]
00003FBE  83 FB 24                  cmp      bx, 0x24
00003FC1  77 5C                     ja       0x401f
00003FC3  80 FB 02                  cmp      bl, 2
00003FC6  72 57                     jb       0x401f
00003FC8  8B 46 0E                  mov      ax, word ptr [bp + 0xe]
00003FCB  8B 4E 10                  mov      cx, word ptr [bp + 0x10]
00003FCE  0B C9                     or       cx, cx
00003FD0  7D 12                     jge      0x3fe4
00003FD2  80 7E 06 00               cmp      byte ptr [bp + 6], 0
00003FD6  74 0C                     je       0x3fe4
00003FD8  26 C6 05 2D               mov      byte ptr es:[di], 0x2d
00003FDC  47                        inc      di
00003FDD  F7 D9                     neg      cx
00003FDF  F7 D8                     neg      ax
00003FE1  83 D9 00                  sbb      cx, 0
00003FE4  8D 76 DE                  lea      si, [bp - 0x22]
00003FE7  E3 10                     jcxz     0x3ff9
00003FE9  91                        xchg     cx, ax
00003FEA  2B D2                     sub      dx, dx
00003FEC  F7 F3                     div      bx
00003FEE  91                        xchg     cx, ax
00003FEF  F7 F3                     div      bx
00003FF1  36 88 14                  mov      byte ptr ss:[si], dl
00003FF4  46                        inc      si
00003FF5  E3 0A                     jcxz     0x4001
00003FF7  EB F0                     jmp      0x3fe9
00003FF9  2B D2                     sub      dx, dx
00003FFB  F7 F3                     div      bx
00003FFD  36 88 14                  mov      byte ptr ss:[si], dl
00004000  46                        inc      si
00004001  0B C0                     or       ax, ax
00004003  75 F4                     jne      0x3ff9
00004005  8D 4E DE                  lea      cx, [bp - 0x22]
00004008  F7 D9                     neg      cx
0000400A  03 CE                     add      cx, si
0000400C  FC                        cld      
0000400D  4E                        dec      si
0000400E  36 8A 04                  mov      al, byte ptr ss:[si]
00004011  2C 0A                     sub      al, 0xa
00004013  73 04                     jae      0x4019
00004015  04 3A                     add      al, 0x3a
00004017  EB 03                     jmp      0x401c
00004019  02 46 04                  add      al, byte ptr [bp + 4]
0000401C  AA                        stosb    byte ptr es:[di], al
0000401D  E2 EE                     loop     0x400d
0000401F  B0 00                     mov      al, 0
00004021  AA                        stosb    byte ptr es:[di], al
00004022  07                        pop      es
00004023  8B 56 0C                  mov      dx, word ptr [bp + 0xc]
00004026  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
00004029  5F                        pop      di
0000402A  5E                        pop      si
0000402B  8B E5                     mov      sp, bp
0000402D  5D                        pop      bp
0000402E  C2 0E 00                  ret      0xe
00004031  55                        push     bp
00004032  8B EC                     mov      bp, sp
00004034  56                        push     si
00004035  57                        push     di
00004036  33 C0                     xor      ax, ax
00004038  50                        push     ax
00004039  FF 76 08                  push     word ptr [bp + 8]
0000403C  FF 76 06                  push     word ptr [bp + 6]
0000403F  FF 76 04                  push     word ptr [bp + 4]
00004042  B8 0A 00                  mov      ax, 0xa
00004045  50                        push     ax
00004046  B0 00                     mov      al, 0
00004048  50                        push     ax
00004049  B0 61                     mov      al, 0x61
0000404B  50                        push     ax
0000404C  E8 60 FF                  call     0x3faf
0000404F  5F                        pop      di
00004050  5E                        pop      si
00004051  5D                        pop      bp
00004052  C2 06 00                  ret      6
00004055  55                        push     bp
00004056  8B EC                     mov      bp, sp
00004058  56                        push     si
00004059  57                        push     di
0000405A  8B 5E 06                  mov      bx, word ptr [bp + 6]
0000405D  8B 4E 0C                  mov      cx, word ptr [bp + 0xc]
00004060  83 F9 0A                  cmp      cx, 0xa
00004063  75 05                     jne      0x406a
00004065  8B C3                     mov      ax, bx
00004067  99                        cdq      
00004068  EB 04                     jmp      0x406e
0000406A  8B C3                     mov      ax, bx
0000406C  33 D2                     xor      dx, dx
0000406E  52                        push     dx
0000406F  50                        push     ax
00004070  FF 76 0A                  push     word ptr [bp + 0xa]
00004073  FF 76 08                  push     word ptr [bp + 8]
00004076  51                        push     cx
00004077  B0 01                     mov      al, 1
00004079  50                        push     ax
0000407A  B0 61                     mov      al, 0x61
0000407C  50                        push     ax
0000407D  E8 2F FF                  call     0x3faf
00004080  5F                        pop      di
00004081  5E                        pop      si
00004082  5D                        pop      bp
00004083  CB                        retf     
00004084  55                        push     bp
00004085  8B EC                     mov      bp, sp
00004087  56                        push     si
00004088  57                        push     di
00004089  FF 76 08                  push     word ptr [bp + 8]
0000408C  FF 76 06                  push     word ptr [bp + 6]
0000408F  FF 76 0C                  push     word ptr [bp + 0xc]
00004092  FF 76 0A                  push     word ptr [bp + 0xa]
00004095  FF 76 0E                  push     word ptr [bp + 0xe]
00004098  B0 00                     mov      al, 0
0000409A  50                        push     ax
0000409B  B0 61                     mov      al, 0x61
0000409D  50                        push     ax
0000409E  E8 0E FF                  call     0x3faf
000040A1  5F                        pop      di
000040A2  5E                        pop      si
000040A3  5D                        pop      bp
000040A4  CB                        retf     
000040A5  55                        push     bp
000040A6  8B EC                     mov      bp, sp
000040A8  56                        push     si
000040A9  57                        push     di
000040AA  8B 46 0E                  mov      ax, word ptr [bp + 0xe]
000040AD  FF 76 08                  push     word ptr [bp + 8]
000040B0  FF 76 06                  push     word ptr [bp + 6]
000040B3  FF 76 0C                  push     word ptr [bp + 0xc]
000040B6  FF 76 0A                  push     word ptr [bp + 0xa]
000040B9  50                        push     ax
000040BA  3D 0A 00                  cmp      ax, 0xa
000040BD  75 05                     jne      0x40c4
000040BF  B8 01 00                  mov      ax, 1
000040C2  EB 02                     jmp      0x40c6
000040C4  33 C0                     xor      ax, ax
000040C6  50                        push     ax
000040C7  B0 61                     mov      al, 0x61
000040C9  50                        push     ax
000040CA  E8 E2 FE                  call     0x3faf
000040CD  5F                        pop      di
000040CE  5E                        pop      si
000040CF  5D                        pop      bp
000040D0  CB                        retf     
000040D1  55                        push     bp
000040D2  8B EC                     mov      bp, sp
000040D4  56                        push     si
000040D5  57                        push     di
000040D6  06                        push     es
000040D7  55                        push     bp
000040D8  C4 76 06                  les      si, ptr [bp + 6]
000040DB  FC                        cld      
000040DC  2B C0                     sub      ax, ax
000040DE  99                        cdq      
000040DF  B9 0A 00                  mov      cx, 0xa
000040E2  B7 00                     mov      bh, 0
000040E4  BF BF 25                  mov      di, 0x25bf
000040E7  26 8A 1C                  mov      bl, byte ptr es:[si]
000040EA  46                        inc      si
000040EB  F6 01 01                  test     byte ptr [bx + di], 1
000040EE  75 F7                     jne      0x40e7
000040F0  BD 00 00                  mov      bp, 0
000040F3  80 FB 2B                  cmp      bl, 0x2b
000040F6  74 06                     je       0x40fe
000040F8  80 FB 2D                  cmp      bl, 0x2d
000040FB  75 05                     jne      0x4102
000040FD  45                        inc      bp
000040FE  26 8A 1C                  mov      bl, byte ptr es:[si]
00004101  46                        inc      si
00004102  80 FB 39                  cmp      bl, 0x39
00004105  77 2F                     ja       0x4136
00004107  80 EB 30                  sub      bl, 0x30
0000410A  72 2A                     jb       0x4136
0000410C  F7 E1                     mul      cx
0000410E  03 C3                     add      ax, bx
00004110  12 D6                     adc      dl, dh
00004112  74 EA                     je       0x40fe
00004114  EB 12                     jmp      0x4128
00004116  8B FA                     mov      di, dx
00004118  B9 0A 00                  mov      cx, 0xa
0000411B  F7 E1                     mul      cx
0000411D  97                        xchg     di, ax
0000411E  87 D1                     xchg     cx, dx
00004120  F7 E2                     mul      dx
00004122  92                        xchg     dx, ax
00004123  97                        xchg     di, ax
00004124  03 C3                     add      ax, bx
00004126  13 D1                     adc      dx, cx
00004128  26 8A 1C                  mov      bl, byte ptr es:[si]
0000412B  46                        inc      si
0000412C  80 FB 39                  cmp      bl, 0x39
0000412F  77 05                     ja       0x4136
00004131  80 EB 30                  sub      bl, 0x30
00004134  73 E0                     jae      0x4116
00004136  4D                        dec      bp
00004137  7C 07                     jl       0x4140
00004139  F7 DA                     neg      dx
0000413B  F7 D8                     neg      ax
0000413D  83 DA 00                  sbb      dx, 0
00004140  5D                        pop      bp
00004141  07                        pop      es
00004142  5F                        pop      di
00004143  5E                        pop      si
00004144  5D                        pop      bp
00004145  CB                        retf     
00004146  55                        push     bp
00004147  8B EC                     mov      bp, sp
00004149  56                        push     si
0000414A  57                        push     di
0000414B  FF 76 08                  push     word ptr [bp + 8]
0000414E  FF 76 06                  push     word ptr [bp + 6]
00004151  0E                        push     cs
00004152  E8 7C FF                  call     0x40d1
00004155  59                        pop      cx
00004156  59                        pop      cx
00004157  5F                        pop      di
00004158  5E                        pop      si
00004159  5D                        pop      bp
0000415A  CB                        retf     
0000415B  BA C2 26                  mov      dx, 0x26c2
0000415E  EB 03                     jmp      0x4163
00004160  BA C7 26                  mov      dx, 0x26c7
00004163  B9 05 00                  mov      cx, 5
00004166  B4 40                     mov      ah, 0x40
00004168  BB 02 00                  mov      bx, 2
0000416B  CD 21                     int      0x21
0000416D  B9 27 00                  mov      cx, 0x27
00004170  BA CC 26                  mov      dx, 0x26cc
00004173  B4 40                     mov      ah, 0x40
00004175  CD 21                     int      0x21
00004177  E9 50 0B                  jmp      0x4cca
0000417A  FF 26 08 29               jmp      word ptr [0x2908]
0000417E  FF 26 0C 29               jmp      word ptr [0x290c]
00004182  FF 26 0E 29               jmp      word ptr [0x290e]
00004186  FF 26 10 29               jmp      word ptr [0x2910]
0000418A  52                        push     dx
0000418B  43                        inc      bx
0000418C  00 00                     add      byte ptr [bx + si], al
0000418E  04 00                     add      al, 0
00004190  FA                        cli      
00004191  FF 00                     inc      word ptr [bx + si]
00004193  00 00                     add      byte ptr [bx + si], al
00004195  00 00                     add      byte ptr [bx + si], al
00004197  00 00                     add      byte ptr [bx + si], al
00004199  00 00                     add      byte ptr [bx + si], al
0000419B  00 DC                     add      ah, bl
0000419D  FF 00                     inc      word ptr [bx + si]
0000419F  00 05                     add      byte ptr [di], al
000041A1  00 00                     add      byte ptr [bx + si], al
000041A3  00 8A 41 55               add      byte ptr [bp + si + 0x5541], cl
000041A7  8B EC                     mov      bp, sp
000041A9  83 EC 24                  sub      sp, 0x24
000041AC  56                        push     si
000041AD  57                        push     di
000041AE  B8 00 00                  mov      ax, 0
000041B1  BB 98 41                  mov      bx, 0x4198
000041B4  90                        nop      
000041B5  0E                        push     cs
000041B6  E8 DA 1A                  call     0x5c93
000041B9  33 C0                     xor      ax, ax
000041BB  50                        push     ax
000041BC  50                        push     ax
000041BD  50                        push     ax
000041BE  50                        push     ax
000041BF  B8 05 00                  mov      ax, 5
000041C2  50                        push     ax
000041C3  B8 00 00                  mov      ax, 0
000041C6  50                        push     ax
000041C7  B8 2A 42                  mov      ax, 0x422a
000041CA  50                        push     ax
000041CB  33 C0                     xor      ax, ax
000041CD  50                        push     ax
000041CE  50                        push     ax
000041CF  C7 46 E8 06 00            mov      word ptr [bp - 0x18], 6
000041D4  1E                        push     ds
000041D5  B8 F6 26                  mov      ax, 0x26f6
000041D8  50                        push     ax
000041D9  16                        push     ss
000041DA  8D 46 FA                  lea      ax, [bp - 6]
000041DD  50                        push     ax
000041DE  90                        nop      
000041DF  0E                        push     cs
000041E0  E8 BC 17                  call     0x599f
000041E3  83 C4 08                  add      sp, 8
000041E6  A1 FA 26                  mov      ax, word ptr [0x26fa]
000041E9  89 46 FE                  mov      word ptr [bp - 2], ax
000041EC  90                        nop      
000041ED  0E                        push     cs
000041EE  E8 96 1A                  call     0x5c87
000041F1  8B D8                     mov      bx, ax
000041F3  8E C2                     mov      es, dx
000041F5  26 83 07 01               add      word ptr es:[bx], 1
000041F9  26 83 57 02 00            adc      word ptr es:[bx + 2], 0
000041FE  8D 46 FA                  lea      ax, [bp - 6]
00004201  16                        push     ss
00004202  50                        push     ax
00004203  0E                        push     cs
00004204  B8 52 43                  mov      ax, 0x4352
00004207  50                        push     ax
00004208  90                        nop      
00004209  0E                        push     cs
0000420A  E8 B6 29                  call     0x6bc3
0000420D  83 C4 1A                  add      sp, 0x1a
00004210  5F                        pop      di
00004211  5E                        pop      si
00004212  8B E5                     mov      sp, bp
00004214  5D                        pop      bp
00004215  CB                        retf     
00004216  56                        push     si
00004217  57                        push     di
00004218  B8 00 00                  mov      ax, 0
0000421B  50                        push     ax
0000421C  B8 A6 41                  mov      ax, 0x41a6
0000421F  50                        push     ax
00004220  90                        nop      
00004221  0E                        push     cs
00004222  E8 21 02                  call     0x4446
00004225  59                        pop      cx
00004226  59                        pop      cx
00004227  5F                        pop      di
00004228  5E                        pop      si
00004229  CB                        retf     
0000422A  55                        push     bp
0000422B  8B EC                     mov      bp, sp
0000422D  56                        push     si
0000422E  57                        push     di
0000422F  FF 76 0C                  push     word ptr [bp + 0xc]
00004232  FF 76 0A                  push     word ptr [bp + 0xa]
00004235  FF 76 08                  push     word ptr [bp + 8]
00004238  FF 76 06                  push     word ptr [bp + 6]
0000423B  90                        nop      
0000423C  0E                        push     cs
0000423D  E8 5F 17                  call     0x599f
00004240  83 C4 08                  add      sp, 8
00004243  C4 5E 0A                  les      bx, ptr [bp + 0xa]
00004246  26 8B 47 04               mov      ax, word ptr es:[bx + 4]
0000424A  C4 5E 06                  les      bx, ptr [bp + 6]
0000424D  26 89 47 04               mov      word ptr es:[bx + 4], ax
00004251  90                        nop      
00004252  0E                        push     cs
00004253  E8 31 1A                  call     0x5c87
00004256  8B D8                     mov      bx, ax
00004258  8E C2                     mov      es, dx
0000425A  26 83 07 01               add      word ptr es:[bx], 1
0000425E  26 83 57 02 00            adc      word ptr es:[bx + 2], 0
00004263  8B 56 08                  mov      dx, word ptr [bp + 8]
00004266  8B 46 06                  mov      ax, word ptr [bp + 6]
00004269  5F                        pop      di
0000426A  5E                        pop      si
0000426B  5D                        pop      bp
0000426C  CB                        retf     
0000426D  52                        push     dx
0000426E  43                        inc      bx
0000426F  00 00                     add      byte ptr [bx + si], al
00004271  00 00                     add      byte ptr [bx + si], al
00004273  F6 26 D3 18               mul      byte ptr [0x18d3]
00004277  18 43 00                  sbb      byte ptr [bp + di], al
0000427A  00 04                     add      byte ptr [si], al
0000427C  00 FC                     add      ah, bh
0000427E  FF 00                     inc      word ptr [bx + si]
00004280  00 00                     add      byte ptr [bx + si], al
00004282  00 00                     add      byte ptr [bx + si], al
00004284  00 00                     add      byte ptr [bx + si], al
00004286  00 00                     add      byte ptr [bx + si], al
00004288  00 DE                     add      dh, bl
0000428A  FF 00                     inc      word ptr [bx + si]
0000428C  00 05                     add      byte ptr [di], al
0000428E  00 00                     add      byte ptr [bx + si], al
00004290  00 6D 42                  add      byte ptr [di + 0x42], ch
00004293  55                        push     bp
00004294  8B EC                     mov      bp, sp
00004296  83 EC 22                  sub      sp, 0x22
00004299  56                        push     si
0000429A  57                        push     di
0000429B  B8 00 00                  mov      ax, 0
0000429E  BB 85 42                  mov      bx, 0x4285
000042A1  90                        nop      
000042A2  0E                        push     cs
000042A3  E8 ED 19                  call     0x5c93
000042A6  C7 46 EA 06 00            mov      word ptr [bp - 0x16], 6
000042AB  33 C0                     xor      ax, ax
000042AD  50                        push     ax
000042AE  1E                        push     ds
000042AF  B8 FC 26                  mov      ax, 0x26fc
000042B2  50                        push     ax
000042B3  16                        push     ss
000042B4  8D 46 FC                  lea      ax, [bp - 4]
000042B7  50                        push     ax
000042B8  9A E9 00 0E 18            lcall    0x180e, 0xe9
000042BD  83 C4 08                  add      sp, 8
000042C0  8D 46 FC                  lea      ax, [bp - 4]
000042C3  16                        push     ss
000042C4  50                        push     ax
000042C5  1E                        push     ds
000042C6  B8 F6 26                  mov      ax, 0x26f6
000042C9  50                        push     ax
000042CA  90                        nop      
000042CB  0E                        push     cs
000042CC  E8 DA 13                  call     0x56a9
000042CF  83 C4 0A                  add      sp, 0xa
000042D2  B8 02 00                  mov      ax, 2
000042D5  50                        push     ax
000042D6  16                        push     ss
000042D7  8D 46 FC                  lea      ax, [bp - 4]
000042DA  50                        push     ax
000042DB  9A 05 03 0E 18            lcall    0x180e, 0x305
000042E0  83 C4 06                  add      sp, 6
000042E3  FF 76 DE                  push     word ptr [bp - 0x22]
000042E6  90                        nop      
000042E7  0E                        push     cs
000042E8  E8 17 1A                  call     0x5d02
000042EB  5F                        pop      di
000042EC  5E                        pop      si
000042ED  8B E5                     mov      sp, bp
000042EF  5D                        pop      bp
000042F0  CB                        retf     
000042F1  56                        push     si
000042F2  57                        push     di
000042F3  90                        nop      
000042F4  0E                        push     cs
000042F5  E8 8F 19                  call     0x5c87
000042F8  8B D8                     mov      bx, ax
000042FA  8E C2                     mov      es, dx
000042FC  26 83 2F 01               sub      word ptr es:[bx], 1
00004300  26 83 5F 02 00            sbb      word ptr es:[bx + 2], 0
00004305  33 C0                     xor      ax, ax
00004307  50                        push     ax
00004308  1E                        push     ds
00004309  B8 F6 26                  mov      ax, 0x26f6
0000430C  50                        push     ax
0000430D  90                        nop      
0000430E  0E                        push     cs
0000430F  E8 38 17                  call     0x5a4a
00004312  83 C4 06                  add      sp, 6
00004315  5F                        pop      di
00004316  5E                        pop      si
00004317  CB                        retf     
00004318  04 00                     add      al, 0
0000431A  03 00                     add      ax, word ptr [bx + si]
0000431C  26 00 FF                  add      bh, bh
0000431F  FF 03                     inc      word ptr [bp + di]
00004321  00 2E 00 32               add      byte ptr [0x3200], ch
00004325  00 00                     add      byte ptr [bx + si], al
00004327  00 00                     add      byte ptr [bx + si], al
00004329  00 00                     add      byte ptr [bx + si], al
0000432B  00 00                     add      byte ptr [bx + si], al
0000432D  00 00                     add      byte ptr [bx + si], al
0000432F  00 00                     add      byte ptr [bx + si], al
00004331  00 01                     add      byte ptr [bx + di], al
00004333  00 01                     add      byte ptr [bx + di], al
00004335  00 05                     add      byte ptr [di], al
00004337  03 0E 18 05               add      cx, word ptr [0x518]
0000433B  00 36 00 73               add      byte ptr [0x7300], dh
0000433F  74 72                     je       0x43b3
00004341  69 6E 67 00 00            imul     bp, word ptr [bp + 0x67], 0
00004346  00 00                     add      byte ptr [bx + si], al
00004348  00 00                     add      byte ptr [bx + si], al
0000434A  00 00                     add      byte ptr [bx + si], al
0000434C  00 00                     add      byte ptr [bx + si], al
0000434E  00 00                     add      byte ptr [bx + si], al
00004350  00 00                     add      byte ptr [bx + si], al
00004352  06                        push     es
00004353  00 03                     add      byte ptr [bp + di], al
00004355  00 26 00 FF               add      byte ptr [0xff00], ah
00004359  FF 07                     inc      word ptr [bx]
0000435B  00 2E 00 3A               add      byte ptr [0x3a00], ch
0000435F  00 00                     add      byte ptr [bx + si], al
00004361  00 00                     add      byte ptr [bx + si], al
00004363  00 00                     add      byte ptr [bx + si], al
00004365  00 00                     add      byte ptr [bx + si], al
00004367  00 00                     add      byte ptr [bx + si], al
00004369  00 00                     add      byte ptr [bx + si], al
0000436B  00 02                     add      byte ptr [bp + si], al
0000436D  00 02                     add      byte ptr [bp + si], al
0000436F  00 94 43 00               add      byte ptr [si + 0x43], dl
00004373  00 05                     add      byte ptr [di], al
00004375  00 3E 00 78               add      byte ptr [0x7800], bh
00004379  61                        popaw    
0000437A  6C                        insb     byte ptr es:[di], dx
0000437B  6C                        insb     byte ptr es:[di], dx
0000437C  6F                        outsw    dx, word ptr [si]
0000437D  63 00                     arpl     word ptr [bx + si], ax
0000437F  00 E2                     add      dl, ah
00004381  43                        inc      bx
00004382  00 00                     add      byte ptr [bx + si], al
00004384  00 00                     add      byte ptr [bx + si], al
00004386  03 00                     add      ax, word ptr [bx + si]
00004388  00 00                     add      byte ptr [bx + si], al
0000438A  00 00                     add      byte ptr [bx + si], al
0000438C  00 00                     add      byte ptr [bx + si], al
0000438E  00 00                     add      byte ptr [bx + si], al
00004390  00 00                     add      byte ptr [bx + si], al
00004392  00 00                     add      byte ptr [bx + si], al
00004394  55                        push     bp
00004395  8B EC                     mov      bp, sp
00004397  56                        push     si
00004398  57                        push     di
00004399  8B 46 06                  mov      ax, word ptr [bp + 6]
0000439C  0B 46 08                  or       ax, word ptr [bp + 8]
0000439F  74 3B                     je       0x43dc
000043A1  90                        nop      
000043A2  0E                        push     cs
000043A3  E8 E1 18                  call     0x5c87
000043A6  8B D8                     mov      bx, ax
000043A8  8E C2                     mov      es, dx
000043AA  26 83 2F 01               sub      word ptr es:[bx], 1
000043AE  26 83 5F 02 00            sbb      word ptr es:[bx + 2], 0
000043B3  33 C0                     xor      ax, ax
000043B5  50                        push     ax
000043B6  FF 76 08                  push     word ptr [bp + 8]
000043B9  FF 76 06                  push     word ptr [bp + 6]
000043BC  90                        nop      
000043BD  0E                        push     cs
000043BE  E8 89 16                  call     0x5a4a
000043C1  83 C4 06                  add      sp, 6
000043C4  F7 46 0A 01 00            test     word ptr [bp + 0xa], 1
000043C9  74 0F                     je       0x43da
000043CB  FF 76 08                  push     word ptr [bp + 8]
000043CE  FF 76 06                  push     word ptr [bp + 6]
000043D1  90                        nop      
000043D2  0E                        push     cs
000043D3  E8 44 00                  call     0x441a
000043D6  59                        pop      cx
000043D7  59                        pop      cx
000043D8  EB 04                     jmp      0x43de
000043DA  EB 02                     jmp      0x43de
000043DC  33 C0                     xor      ax, ax
000043DE  5F                        pop      di
000043DF  5E                        pop      si
000043E0  5D                        pop      bp
000043E1  CB                        retf     
000043E2  04 00                     add      al, 0
000043E4  03 00                     add      ax, word ptr [bx + si]
000043E6  26 00 FF                  add      bh, bh
000043E9  FF 03                     inc      word ptr [bp + di]
000043EB  00 2C                     add      byte ptr [si], ch
000043ED  00 30                     add      byte ptr [bx + si], dh
000043EF  00 00                     add      byte ptr [bx + si], al
000043F1  00 00                     add      byte ptr [bx + si], al
000043F3  00 00                     add      byte ptr [bx + si], al
000043F5  00 00                     add      byte ptr [bx + si], al
000043F7  00 00                     add      byte ptr [bx + si], al
000043F9  00 00                     add      byte ptr [bx + si], al
000043FB  00 01                     add      byte ptr [bx + di], al
000043FD  00 01                     add      byte ptr [bx + di], al
000043FF  00 4A 5A                  add      byte ptr [bp + si + 0x5a], cl
00004402  00 00                     add      byte ptr [bx + si], al
00004404  05 00 34                  add      ax, 0x3400
00004407  00 78 6D                  add      byte ptr [bx + si + 0x6d], bh
0000440A  73 67                     jae      0x4473
0000440C  00 00                     add      byte ptr [bx + si], al
0000440E  00 00                     add      byte ptr [bx + si], al
00004410  00 00                     add      byte ptr [bx + si], al
00004412  00 00                     add      byte ptr [bx + si], al
00004414  00 00                     add      byte ptr [bx + si], al
00004416  00 00                     add      byte ptr [bx + si], al
00004418  00 00                     add      byte ptr [bx + si], al
0000441A  55                        push     bp
0000441B  8B EC                     mov      bp, sp
0000441D  56                        push     si
0000441E  57                        push     di
0000441F  FF 76 08                  push     word ptr [bp + 8]
00004422  FF 76 06                  push     word ptr [bp + 6]
00004425  90                        nop      
00004426  0E                        push     cs
00004427  E8 1E 02                  call     0x4648
0000442A  59                        pop      cx
0000442B  59                        pop      cx
0000442C  5F                        pop      di
0000442D  5E                        pop      si
0000442E  5D                        pop      bp
0000442F  CB                        retf     
00004430  55                        push     bp
00004431  8B EC                     mov      bp, sp
00004433  56                        push     si
00004434  57                        push     di
00004435  FF 76 08                  push     word ptr [bp + 8]
00004438  FF 76 06                  push     word ptr [bp + 6]
0000443B  90                        nop      
0000443C  0E                        push     cs
0000443D  E8 DA FF                  call     0x441a
00004440  59                        pop      cx
00004441  59                        pop      cx
00004442  5F                        pop      di
00004443  5E                        pop      si
00004444  5D                        pop      bp
00004445  CB                        retf     
00004446  55                        push     bp
00004447  8B EC                     mov      bp, sp
00004449  83 EC 04                  sub      sp, 4
0000444C  56                        push     si
0000444D  57                        push     di
0000444E  8B 16 2A 58               mov      dx, word ptr [0x582a]
00004452  A1 28 58                  mov      ax, word ptr [0x5828]
00004455  89 56 FE                  mov      word ptr [bp - 2], dx
00004458  89 46 FC                  mov      word ptr [bp - 4], ax
0000445B  8B 56 08                  mov      dx, word ptr [bp + 8]
0000445E  8B 46 06                  mov      ax, word ptr [bp + 6]
00004461  89 16 2A 58               mov      word ptr [0x582a], dx
00004465  A3 28 58                  mov      word ptr [0x5828], ax
00004468  8B 56 FE                  mov      dx, word ptr [bp - 2]
0000446B  8B 46 FC                  mov      ax, word ptr [bp - 4]
0000446E  5F                        pop      di
0000446F  5E                        pop      si
00004470  8B E5                     mov      sp, bp
00004472  5D                        pop      bp
00004473  CB                        retf     
00004474  56                        push     si
00004475  57                        push     di
00004476  B8 40 00                  mov      ax, 0x40
00004479  50                        push     ax
0000447A  90                        nop      
0000447B  0E                        push     cs
0000447C  E8 D3 02                  call     0x4752
0000447F  59                        pop      cx
00004480  89 16 2E 58               mov      word ptr [0x582e], dx
00004484  A3 2C 58                  mov      word ptr [0x582c], ax
00004487  5F                        pop      di
00004488  5E                        pop      si
00004489  CB                        retf     
0000448A  56                        push     si
0000448B  57                        push     di
0000448C  A1 2C 58                  mov      ax, word ptr [0x582c]
0000448F  0B 06 2E 58               or       ax, word ptr [0x582e]
00004493  74 1B                     je       0x44b0
00004495  FF 36 2E 58               push     word ptr [0x582e]
00004499  FF 36 2C 58               push     word ptr [0x582c]
0000449D  90                        nop      
0000449E  0E                        push     cs
0000449F  E8 A6 01                  call     0x4648
000044A2  59                        pop      cx
000044A3  59                        pop      cx
000044A4  C7 06 2E 58 00 00         mov      word ptr [0x582e], 0
000044AA  C7 06 2C 58 00 00         mov      word ptr [0x582c], 0
000044B0  5F                        pop      di
000044B1  5E                        pop      si
000044B2  CB                        retf     
000044B3  55                        push     bp
000044B4  8B EC                     mov      bp, sp
000044B6  83 EC 04                  sub      sp, 4
000044B9  56                        push     si
000044BA  57                        push     di
000044BB  C7 46 FE 00 00            mov      word ptr [bp - 2], 0
000044C0  C7 46 FC 00 00            mov      word ptr [bp - 4], 0
000044C5  83 7E 06 00               cmp      word ptr [bp + 6], 0
000044C9  74 05                     je       0x44d0
000044CB  8B 46 06                  mov      ax, word ptr [bp + 6]
000044CE  EB 03                     jmp      0x44d3
000044D0  B8 01 00                  mov      ax, 1
000044D3  89 46 06                  mov      word ptr [bp + 6], ax
000044D6  EB 08                     jmp      0x44e0
000044D8  0E                        push     cs
000044D9  E8 AE FF                  call     0x448a
000044DC  FF 1E 28 58               lcall    [0x5828]
000044E0  FF 76 06                  push     word ptr [bp + 6]
000044E3  90                        nop      
000044E4  0E                        push     cs
000044E5  E8 6A 02                  call     0x4752
000044E8  59                        pop      cx
000044E9  89 56 FE                  mov      word ptr [bp - 2], dx
000044EC  89 46 FC                  mov      word ptr [bp - 4], ax
000044EF  0B C2                     or       ax, dx
000044F1  75 09                     jne      0x44fc
000044F3  A1 28 58                  mov      ax, word ptr [0x5828]
000044F6  0B 06 2A 58               or       ax, word ptr [0x582a]
000044FA  75 DC                     jne      0x44d8
000044FC  8B 56 FE                  mov      dx, word ptr [bp - 2]
000044FF  8B 46 FC                  mov      ax, word ptr [bp - 4]
00004502  5F                        pop      di
00004503  5E                        pop      si
00004504  8B E5                     mov      sp, bp
00004506  5D                        pop      bp
00004507  CB                        retf     
00004508  00 00                     add      byte ptr [bx + si], al
0000450A  00 00                     add      byte ptr [bx + si], al
0000450C  00 00                     add      byte ptr [bx + si], al
0000450E  00 00                     add      byte ptr [bx + si], al
00004510  00 00                     add      byte ptr [bx + si], al
00004512  00 00                     add      byte ptr [bx + si], al
00004514  2E 3B 16 08 45            cmp      dx, word ptr cs:[0x4508]
00004519  74 37                     je       0x4552
0000451B  8E DA                     mov      ds, dx
0000451D  8E 1E 02 00               mov      ds, word ptr [2]
00004521  83 3E 02 00 00            cmp      word ptr [2], 0
00004526  74 07                     je       0x452f
00004528  2E 8C 1E 0A 45            mov      word ptr cs:[0x450a], ds
0000452D  EB 38                     jmp      0x4567
0000452F  8C D8                     mov      ax, ds
00004531  2E 3B 06 08 45            cmp      ax, word ptr cs:[0x4508]
00004536  74 15                     je       0x454d
00004538  A1 08 00                  mov      ax, word ptr [8]
0000453B  2E A3 0A 45               mov      word ptr cs:[0x450a], ax
0000453F  1E                        push     ds
00004540  33 C0                     xor      ax, ax
00004542  50                        push     ax
00004543  E8 A2 00                  call     0x45e8
00004546  2E 8E 1E 0E 45            mov      ds, word ptr cs:[0x450e]
0000454B  EB 23                     jmp      0x4570
0000454D  2E 8B 16 08 45            mov      dx, word ptr cs:[0x4508]
00004552  2E C7 06 08 45 00 00      mov      word ptr cs:[0x4508], 0
00004559  2E C7 06 0A 45 00 00      mov      word ptr cs:[0x450a], 0
00004560  2E C7 06 0C 45 00 00      mov      word ptr cs:[0x450c], 0
00004567  2E 8E 1E 0E 45            mov      ds, word ptr cs:[0x450e]
0000456C  52                        push     dx
0000456D  33 C0                     xor      ax, ax
0000456F  50                        push     ax
00004570  E8 55 04                  call     0x49c8
00004573  83 C4 04                  add      sp, 4
00004576  C3                        ret      
00004577  8E DA                     mov      ds, dx
00004579  1E                        push     ds
0000457A  8E 06 02 00               mov      es, word ptr [2]
0000457E  C7 06 02 00 00 00         mov      word ptr [2], 0
00004584  8C 06 08 00               mov      word ptr [8], es
00004588  2E 3B 16 08 45            cmp      dx, word ptr cs:[0x4508]
0000458D  74 2E                     je       0x45bd
0000458F  26 83 3E 02 00 00         cmp      word ptr es:[2], 0
00004595  75 26                     jne      0x45bd
00004597  A1 00 00                  mov      ax, word ptr [0]
0000459A  5B                        pop      bx
0000459B  06                        push     es
0000459C  26 01 06 00 00            add      word ptr es:[0], ax
000045A1  8C C1                     mov      cx, es
000045A3  03 D0                     add      dx, ax
000045A5  8E C2                     mov      es, dx
000045A7  26 83 3E 02 00 00         cmp      word ptr es:[2], 0
000045AD  75 07                     jne      0x45b6
000045AF  26 89 0E 08 00            mov      word ptr es:[8], cx
000045B4  EB 0A                     jmp      0x45c0
000045B6  26 89 0E 02 00            mov      word ptr es:[2], cx
000045BB  EB 03                     jmp      0x45c0
000045BD  E8 51 00                  call     0x4611
000045C0  07                        pop      es
000045C1  8C C0                     mov      ax, es
000045C3  26 03 06 00 00            add      ax, word ptr es:[0]
000045C8  8E D8                     mov      ds, ax
000045CA  83 3E 02 00 00            cmp      word ptr [2], 0
000045CF  74 01                     je       0x45d2
000045D1  C3                        ret      
000045D2  A1 00 00                  mov      ax, word ptr [0]
000045D5  26 01 06 00 00            add      word ptr es:[0], ax
000045DA  8C C0                     mov      ax, es
000045DC  8C DB                     mov      bx, ds
000045DE  03 1E 00 00               add      bx, word ptr [0]
000045E2  8E C3                     mov      es, bx
000045E4  26 A3 02 00               mov      word ptr es:[2], ax
000045E8  8C DB                     mov      bx, ds
000045EA  3B 1E 06 00               cmp      bx, word ptr [6]
000045EE  74 19                     je       0x4609
000045F0  8E 06 06 00               mov      es, word ptr [6]
000045F4  8E 1E 04 00               mov      ds, word ptr [4]
000045F8  8C 06 06 00               mov      word ptr [6], es
000045FC  26 8C 1E 04 00            mov      word ptr es:[4], ds
00004601  2E 8C 1E 0C 45            mov      word ptr cs:[0x450c], ds
00004606  8E DB                     mov      ds, bx
00004608  C3                        ret      
00004609  2E C7 06 0C 45 00 00      mov      word ptr cs:[0x450c], 0
00004610  C3                        ret      
00004611  2E A1 0C 45               mov      ax, word ptr cs:[0x450c]
00004615  0B C0                     or       ax, ax
00004617  74 21                     je       0x463a
00004619  8C D3                     mov      bx, ss
0000461B  9C                        pushf    
0000461C  FA                        cli      
0000461D  8E D0                     mov      ss, ax
0000461F  36 8E 06 06 00            mov      es, word ptr ss:[6]
00004624  36 8C 1E 06 00            mov      word ptr ss:[6], ds
00004629  8C 16 04 00               mov      word ptr [4], ss
0000462D  8E D3                     mov      ss, bx
0000462F  9D                        popf     
00004630  26 8C 1E 04 00            mov      word ptr es:[4], ds
00004635  8C 06 06 00               mov      word ptr [6], es
00004639  C3                        ret      
0000463A  2E 8C 1E 0C 45            mov      word ptr cs:[0x450c], ds
0000463F  8C 1E 04 00               mov      word ptr [4], ds
00004643  8C 1E 06 00               mov      word ptr [6], ds
00004647  C3                        ret      
00004648  55                        push     bp
00004649  8B EC                     mov      bp, sp
0000464B  56                        push     si
0000464C  57                        push     di
0000464D  2E 8C 1E 0E 45            mov      word ptr cs:[0x450e], ds
00004652  8B 56 08                  mov      dx, word ptr [bp + 8]
00004655  0B D2                     or       dx, dx
00004657  74 0F                     je       0x4668
00004659  2E 3B 16 0A 45            cmp      dx, word ptr cs:[0x450a]
0000465E  75 05                     jne      0x4665
00004660  E8 B1 FE                  call     0x4514
00004663  EB 03                     jmp      0x4668
00004665  E8 0F FF                  call     0x4577
00004668  2E 8E 1E 0E 45            mov      ds, word ptr cs:[0x450e]
0000466D  5F                        pop      di
0000466E  5E                        pop      si
0000466F  5D                        pop      bp
00004670  CB                        retf     
00004671  50                        push     ax
00004672  2E 8E 1E 0E 45            mov      ds, word ptr cs:[0x450e]
00004677  33 C0                     xor      ax, ax
00004679  50                        push     ax
0000467A  50                        push     ax
0000467B  E8 8D 03                  call     0x4a0b
0000467E  83 C4 04                  add      sp, 4
00004681  25 0F 00                  and      ax, 0xf
00004684  74 14                     je       0x469a
00004686  BA 10 00                  mov      dx, 0x10
00004689  2B D0                     sub      dx, ax
0000468B  33 C0                     xor      ax, ax
0000468D  2E 8E 1E 0E 45            mov      ds, word ptr cs:[0x450e]
00004692  50                        push     ax
00004693  52                        push     dx
00004694  E8 74 03                  call     0x4a0b
00004697  83 C4 04                  add      sp, 4
0000469A  58                        pop      ax
0000469B  50                        push     ax
0000469C  33 DB                     xor      bx, bx
0000469E  8A DC                     mov      bl, ah
000046A0  B1 04                     mov      cl, 4
000046A2  D3 EB                     shr      bx, cl
000046A4  D3 E0                     shl      ax, cl
000046A6  2E 8E 1E 0E 45            mov      ds, word ptr cs:[0x450e]
000046AB  53                        push     bx
000046AC  50                        push     ax
000046AD  E8 5B 03                  call     0x4a0b
000046B0  83 C4 04                  add      sp, 4
000046B3  5B                        pop      bx
000046B4  3D FF FF                  cmp      ax, 0xffff
000046B7  74 18                     je       0x46d1
000046B9  2E 89 16 08 45            mov      word ptr cs:[0x4508], dx
000046BE  2E 89 16 0A 45            mov      word ptr cs:[0x450a], dx
000046C3  8E DA                     mov      ds, dx
000046C5  89 1E 00 00               mov      word ptr [0], bx
000046C9  89 16 02 00               mov      word ptr [2], dx
000046CD  B8 04 00                  mov      ax, 4
000046D0  C3                        ret      
000046D1  33 C0                     xor      ax, ax
000046D3  99                        cdq      
000046D4  C3                        ret      
000046D5  50                        push     ax
000046D6  33 DB                     xor      bx, bx
000046D8  8A DC                     mov      bl, ah
000046DA  B1 04                     mov      cl, 4
000046DC  D3 EB                     shr      bx, cl
000046DE  D3 E0                     shl      ax, cl
000046E0  2E 8E 1E 0E 45            mov      ds, word ptr cs:[0x450e]
000046E5  53                        push     bx
000046E6  50                        push     ax
000046E7  E8 21 03                  call     0x4a0b
000046EA  83 C4 04                  add      sp, 4
000046ED  5B                        pop      bx
000046EE  3D FF FF                  cmp      ax, 0xffff
000046F1  74 38                     je       0x472b
000046F3  25 0F 00                  and      ax, 0xf
000046F6  75 18                     jne      0x4710
000046F8  2E 8B 0E 0A 45            mov      cx, word ptr cs:[0x450a]
000046FD  2E 89 16 0A 45            mov      word ptr cs:[0x450a], dx
00004702  8E DA                     mov      ds, dx
00004704  89 1E 00 00               mov      word ptr [0], bx
00004708  89 0E 02 00               mov      word ptr [2], cx
0000470C  B8 04 00                  mov      ax, 4
0000470F  C3                        ret      
00004710  53                        push     bx
00004711  52                        push     dx
00004712  F7 D8                     neg      ax
00004714  05 10 00                  add      ax, 0x10
00004717  33 DB                     xor      bx, bx
00004719  53                        push     bx
0000471A  50                        push     ax
0000471B  E8 ED 02                  call     0x4a0b
0000471E  83 C4 04                  add      sp, 4
00004721  5A                        pop      dx
00004722  5B                        pop      bx
00004723  3D FF FF                  cmp      ax, 0xffff
00004726  74 03                     je       0x472b
00004728  42                        inc      dx
00004729  EB CD                     jmp      0x46f8
0000472B  33 C0                     xor      ax, ax
0000472D  99                        cdq      
0000472E  C3                        ret      
0000472F  8B DA                     mov      bx, dx
00004731  29 06 00 00               sub      word ptr [0], ax
00004735  03 16 00 00               add      dx, word ptr [0]
00004739  8E DA                     mov      ds, dx
0000473B  A3 00 00                  mov      word ptr [0], ax
0000473E  89 1E 02 00               mov      word ptr [2], bx
00004742  8B DA                     mov      bx, dx
00004744  03 1E 00 00               add      bx, word ptr [0]
00004748  8E DB                     mov      ds, bx
0000474A  89 16 02 00               mov      word ptr [2], dx
0000474E  B8 04 00                  mov      ax, 4
00004751  C3                        ret      
00004752  55                        push     bp
00004753  8B EC                     mov      bp, sp
00004755  33 D2                     xor      dx, dx
00004757  8B 46 06                  mov      ax, word ptr [bp + 6]
0000475A  EB 09                     jmp      0x4765
0000475C  55                        push     bp
0000475D  8B EC                     mov      bp, sp
0000475F  8B 56 08                  mov      dx, word ptr [bp + 8]
00004762  8B 46 06                  mov      ax, word ptr [bp + 6]
00004765  8B C8                     mov      cx, ax
00004767  0B CA                     or       cx, dx
00004769  56                        push     si
0000476A  57                        push     di
0000476B  2E 8C 1E 0E 45            mov      word ptr cs:[0x450e], ds
00004770  74 5E                     je       0x47d0
00004772  05 13 00                  add      ax, 0x13
00004775  83 D2 00                  adc      dx, 0
00004778  72 41                     jb       0x47bb
0000477A  F7 C2 F0 FF               test     dx, 0xfff0
0000477E  75 3B                     jne      0x47bb
00004780  B1 04                     mov      cl, 4
00004782  D3 E8                     shr      ax, cl
00004784  D3 E2                     shl      dx, cl
00004786  0A E2                     or       ah, dl
00004788  2E 8B 16 08 45            mov      dx, word ptr cs:[0x4508]
0000478D  0B D2                     or       dx, dx
0000478F  74 20                     je       0x47b1
00004791  2E 8B 16 0C 45            mov      dx, word ptr cs:[0x450c]
00004796  0B D2                     or       dx, dx
00004798  74 12                     je       0x47ac
0000479A  8B DA                     mov      bx, dx
0000479C  8E DA                     mov      ds, dx
0000479E  39 06 00 00               cmp      word ptr [0], ax
000047A2  73 1C                     jae      0x47c0
000047A4  8B 16 06 00               mov      dx, word ptr [6]
000047A8  3B D3                     cmp      dx, bx
000047AA  75 F0                     jne      0x479c
000047AC  E8 26 FF                  call     0x46d5
000047AF  EB 1F                     jmp      0x47d0
000047B1  E8 BD FE                  call     0x4671
000047B4  EB 1A                     jmp      0x47d0
000047B6  E8 76 FF                  call     0x472f
000047B9  EB 15                     jmp      0x47d0
000047BB  33 C0                     xor      ax, ax
000047BD  99                        cdq      
000047BE  EB 10                     jmp      0x47d0
000047C0  77 F4                     ja       0x47b6
000047C2  E8 23 FE                  call     0x45e8
000047C5  8B 1E 08 00               mov      bx, word ptr [8]
000047C9  89 1E 02 00               mov      word ptr [2], bx
000047CD  B8 04 00                  mov      ax, 4
000047D0  2E 8E 1E 0E 45            mov      ds, word ptr cs:[0x450e]
000047D5  5F                        pop      di
000047D6  5E                        pop      si
000047D7  5D                        pop      bp
000047D8  CB                        retf     
000047D9  53                        push     bx
000047DA  2E 8B 36 10 45            mov      si, word ptr cs:[0x4510]
000047DF  56                        push     si
000047E0  2E 8B 36 12 45            mov      si, word ptr cs:[0x4512]
000047E5  56                        push     si
000047E6  0E                        push     cs
000047E7  E8 72 FF                  call     0x475c
000047EA  83 C4 04                  add      sp, 4
000047ED  0B D2                     or       dx, dx
000047EF  75 02                     jne      0x47f3
000047F1  5B                        pop      bx
000047F2  C3                        ret      
000047F3  1F                        pop      ds
000047F4  8E C2                     mov      es, dx
000047F6  06                        push     es
000047F7  1E                        push     ds
000047F8  53                        push     bx
000047F9  8B 16 00 00               mov      dx, word ptr [0]
000047FD  FC                        cld      
000047FE  4A                        dec      dx
000047FF  BF 04 00                  mov      di, 4
00004802  8B F7                     mov      si, di
00004804  B9 06 00                  mov      cx, 6
00004807  F3 A5                     rep movsw word ptr es:[di], word ptr [si]
00004809  0B D2                     or       dx, dx
0000480B  74 37                     je       0x4844
0000480D  8C C0                     mov      ax, es
0000480F  40                        inc      ax
00004810  8E C0                     mov      es, ax
00004812  8C D8                     mov      ax, ds
00004814  40                        inc      ax
00004815  8E D8                     mov      ds, ax
00004817  33 FF                     xor      di, di
00004819  8B F7                     mov      si, di
0000481B  8B CA                     mov      cx, dx
0000481D  81 F9 00 10               cmp      cx, 0x1000
00004821  76 03                     jbe      0x4826
00004823  B9 00 10                  mov      cx, 0x1000
00004826  D1 E1                     shl      cx, 1
00004828  D1 E1                     shl      cx, 1
0000482A  D1 E1                     shl      cx, 1
0000482C  F3 A5                     rep movsw word ptr es:[di], word ptr [si]
0000482E  81 EA 00 10               sub      dx, 0x1000
00004832  76 10                     jbe      0x4844
00004834  8C C0                     mov      ax, es
00004836  05 00 10                  add      ax, 0x1000
00004839  8E C0                     mov      es, ax
0000483B  8C D8                     mov      ax, ds
0000483D  05 00 10                  add      ax, 0x1000
00004840  8E D8                     mov      ds, ax
00004842  EB D3                     jmp      0x4817
00004844  2E 8E 1E 0E 45            mov      ds, word ptr cs:[0x450e]
00004849  0E                        push     cs
0000484A  E8 FB FD                  call     0x4648
0000484D  83 C4 04                  add      sp, 4
00004850  5A                        pop      dx
00004851  B8 04 00                  mov      ax, 4
00004854  C3                        ret      
00004855  2E 3B 1E 0A 45            cmp      bx, word ptr cs:[0x450a]
0000485A  74 45                     je       0x48a1
0000485C  8B FB                     mov      di, bx
0000485E  03 F8                     add      di, ax
00004860  8E C7                     mov      es, di
00004862  8B F1                     mov      si, cx
00004864  2B F0                     sub      si, ax
00004866  26 89 36 00 00            mov      word ptr es:[0], si
0000486B  26 89 1E 02 00            mov      word ptr es:[2], bx
00004870  06                        push     es
00004871  50                        push     ax
00004872  8E C3                     mov      es, bx
00004874  26 A3 00 00               mov      word ptr es:[0], ax
00004878  8B D3                     mov      dx, bx
0000487A  03 D1                     add      dx, cx
0000487C  8E C2                     mov      es, dx
0000487E  26 83 3E 02 00 00         cmp      word ptr es:[2], 0
00004884  74 07                     je       0x488d
00004886  26 89 3E 02 00            mov      word ptr es:[2], di
0000488B  EB 05                     jmp      0x4892
0000488D  26 89 3E 08 00            mov      word ptr es:[8], di
00004892  8B F3                     mov      si, bx
00004894  0E                        push     cs
00004895  E8 B0 FD                  call     0x4648
00004898  83 C4 04                  add      sp, 4
0000489B  8B D6                     mov      dx, si
0000489D  B8 04 00                  mov      ax, 4
000048A0  C3                        ret      
000048A1  53                        push     bx
000048A2  8E C3                     mov      es, bx
000048A4  26 A3 00 00               mov      word ptr es:[0], ax
000048A8  03 D8                     add      bx, ax
000048AA  53                        push     bx
000048AB  33 C0                     xor      ax, ax
000048AD  50                        push     ax
000048AE  E8 17 01                  call     0x49c8
000048B1  83 C4 04                  add      sp, 4
000048B4  5A                        pop      dx
000048B5  B8 04 00                  mov      ax, 4
000048B8  C3                        ret      
000048B9  55                        push     bp
000048BA  8B EC                     mov      bp, sp
000048BC  33 D2                     xor      dx, dx
000048BE  EB 06                     jmp      0x48c6
000048C0  55                        push     bp
000048C1  8B EC                     mov      bp, sp
000048C3  8B 56 0C                  mov      dx, word ptr [bp + 0xc]
000048C6  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
000048C9  8B 5E 08                  mov      bx, word ptr [bp + 8]
000048CC  56                        push     si
000048CD  57                        push     di
000048CE  2E 8C 1E 0E 45            mov      word ptr cs:[0x450e], ds
000048D3  2E 89 16 10 45            mov      word ptr cs:[0x4510], dx
000048D8  2E A3 12 45               mov      word ptr cs:[0x4512], ax
000048DC  0B DB                     or       bx, bx
000048DE  74 3A                     je       0x491a
000048E0  8B C8                     mov      cx, ax
000048E2  0B CA                     or       cx, dx
000048E4  74 3F                     je       0x4925
000048E6  05 13 00                  add      ax, 0x13
000048E9  83 D2 00                  adc      dx, 0
000048EC  72 40                     jb       0x492e
000048EE  F7 C2 F0 FF               test     dx, 0xfff0
000048F2  75 3A                     jne      0x492e
000048F4  B1 04                     mov      cl, 4
000048F6  D3 E8                     shr      ax, cl
000048F8  D3 E2                     shl      dx, cl
000048FA  0A E2                     or       ah, dl
000048FC  8E C3                     mov      es, bx
000048FE  26 8B 0E 00 00            mov      cx, word ptr es:[0]
00004903  3B C8                     cmp      cx, ax
00004905  72 0E                     jb       0x4915
00004907  77 07                     ja       0x4910
00004909  8B D3                     mov      dx, bx
0000490B  B8 04 00                  mov      ax, 4
0000490E  EB 21                     jmp      0x4931
00004910  E8 42 FF                  call     0x4855
00004913  EB 1C                     jmp      0x4931
00004915  E8 C1 FE                  call     0x47d9
00004918  EB 17                     jmp      0x4931
0000491A  52                        push     dx
0000491B  50                        push     ax
0000491C  0E                        push     cs
0000491D  E8 3C FE                  call     0x475c
00004920  83 C4 04                  add      sp, 4
00004923  EB 0C                     jmp      0x4931
00004925  53                        push     bx
00004926  50                        push     ax
00004927  0E                        push     cs
00004928  E8 1D FD                  call     0x4648
0000492B  83 C4 04                  add      sp, 4
0000492E  33 C0                     xor      ax, ax
00004930  99                        cdq      
00004931  2E 8E 1E 0E 45            mov      ds, word ptr cs:[0x450e]
00004936  5F                        pop      di
00004937  5E                        pop      si
00004938  5D                        pop      bp
00004939  CB                        retf     
0000493A  55                        push     bp
0000493B  8B EC                     mov      bp, sp
0000493D  83 EC 02                  sub      sp, 2
00004940  56                        push     si
00004941  57                        push     di
00004942  8B 46 06                  mov      ax, word ptr [bp + 6]
00004945  40                        inc      ax
00004946  89 46 FE                  mov      word ptr [bp - 2], ax
00004949  A1 7A 00                  mov      ax, word ptr [0x7a]
0000494C  29 46 FE                  sub      word ptr [bp - 2], ax
0000494F  8B 46 FE                  mov      ax, word ptr [bp - 2]
00004952  05 3F 00                  add      ax, 0x3f
00004955  B1 06                     mov      cl, 6
00004957  D3 E8                     shr      ax, cl
00004959  89 46 FE                  mov      word ptr [bp - 2], ax
0000495C  3B 06 0A 27               cmp      ax, word ptr [0x270a]
00004960  74 3C                     je       0x499e
00004962  B1 06                     mov      cl, 6
00004964  D3 66 FE                  shl      word ptr [bp - 2], cl
00004967  8B 16 8E 00               mov      dx, word ptr [0x8e]
0000496B  8B 46 FE                  mov      ax, word ptr [bp - 2]
0000496E  03 06 7A 00               add      ax, word ptr [0x7a]
00004972  3B C2                     cmp      ax, dx
00004974  76 09                     jbe      0x497f
00004976  8B C2                     mov      ax, dx
00004978  2B 06 7A 00               sub      ax, word ptr [0x7a]
0000497C  89 46 FE                  mov      word ptr [bp - 2], ax
0000497F  FF 76 FE                  push     word ptr [bp - 2]
00004982  FF 36 7A 00               push     word ptr [0x7a]
00004986  90                        nop      
00004987  0E                        push     cs
00004988  E8 5F 01                  call     0x4aea
0000498B  59                        pop      cx
0000498C  59                        pop      cx
0000498D  8B D0                     mov      dx, ax
0000498F  83 FA FF                  cmp      dx, -1
00004992  75 1C                     jne      0x49b0
00004994  8B 46 FE                  mov      ax, word ptr [bp - 2]
00004997  B1 06                     mov      cl, 6
00004999  D3 E8                     shr      ax, cl
0000499B  A3 0A 27                  mov      word ptr [0x270a], ax
0000499E  8B 56 06                  mov      dx, word ptr [bp + 6]
000049A1  8B 46 04                  mov      ax, word ptr [bp + 4]
000049A4  89 16 8A 00               mov      word ptr [0x8a], dx
000049A8  A3 88 00                  mov      word ptr [0x88], ax
000049AB  B8 01 00                  mov      ax, 1
000049AE  EB 10                     jmp      0x49c0
000049B0  A1 7A 00                  mov      ax, word ptr [0x7a]
000049B3  03 C2                     add      ax, dx
000049B5  A3 8E 00                  mov      word ptr [0x8e], ax
000049B8  C7 06 8C 00 00 00         mov      word ptr [0x8c], 0
000049BE  33 C0                     xor      ax, ax
000049C0  5F                        pop      di
000049C1  5E                        pop      si
000049C2  8B E5                     mov      sp, bp
000049C4  5D                        pop      bp
000049C5  C2 04 00                  ret      4
000049C8  55                        push     bp
000049C9  8B EC                     mov      bp, sp
000049CB  56                        push     si
000049CC  57                        push     di
000049CD  8B 0E 86 00               mov      cx, word ptr [0x86]
000049D1  8B 1E 84 00               mov      bx, word ptr [0x84]
000049D5  8B 56 06                  mov      dx, word ptr [bp + 6]
000049D8  8B 46 04                  mov      ax, word ptr [bp + 4]
000049DB  E8 D0 01                  call     0x4bae
000049DE  72 20                     jb       0x4a00
000049E0  8B 0E 8E 00               mov      cx, word ptr [0x8e]
000049E4  8B 1E 8C 00               mov      bx, word ptr [0x8c]
000049E8  8B 56 06                  mov      dx, word ptr [bp + 6]
000049EB  8B 46 04                  mov      ax, word ptr [bp + 4]
000049EE  E8 BD 01                  call     0x4bae
000049F1  77 0D                     ja       0x4a00
000049F3  FF 76 06                  push     word ptr [bp + 6]
000049F6  FF 76 04                  push     word ptr [bp + 4]
000049F9  E8 3E FF                  call     0x493a
000049FC  0B C0                     or       ax, ax
000049FE  75 05                     jne      0x4a05
00004A00  B8 FF FF                  mov      ax, 0xffff
00004A03  EB 02                     jmp      0x4a07
00004A05  33 C0                     xor      ax, ax
00004A07  5F                        pop      di
00004A08  5E                        pop      si
00004A09  5D                        pop      bp
00004A0A  C3                        ret      
00004A0B  55                        push     bp
00004A0C  8B EC                     mov      bp, sp
00004A0E  83 EC 08                  sub      sp, 8
00004A11  56                        push     si
00004A12  57                        push     di
00004A13  A1 8A 00                  mov      ax, word ptr [0x8a]
00004A16  33 D2                     xor      dx, dx
00004A18  B1 04                     mov      cl, 4
00004A1A  E8 5A F5                  call     0x3f77
00004A1D  03 06 88 00               add      ax, word ptr [0x88]
00004A21  83 D2 00                  adc      dx, 0
00004A24  03 46 04                  add      ax, word ptr [bp + 4]
00004A27  13 56 06                  adc      dx, word ptr [bp + 6]
00004A2A  83 FA 0F                  cmp      dx, 0xf
00004A2D  7C 07                     jl       0x4a36
00004A2F  7F 55                     jg       0x4a86
00004A31  3D FF FF                  cmp      ax, 0xffff
00004A34  77 50                     ja       0x4a86
00004A36  8B 16 8A 00               mov      dx, word ptr [0x8a]
00004A3A  A1 88 00                  mov      ax, word ptr [0x88]
00004A3D  8B 4E 06                  mov      cx, word ptr [bp + 6]
00004A40  8B 5E 04                  mov      bx, word ptr [bp + 4]
00004A43  E8 E0 00                  call     0x4b26
00004A46  89 56 FE                  mov      word ptr [bp - 2], dx
00004A49  89 46 FC                  mov      word ptr [bp - 4], ax
00004A4C  8B 0E 86 00               mov      cx, word ptr [0x86]
00004A50  8B 1E 84 00               mov      bx, word ptr [0x84]
00004A54  E8 57 01                  call     0x4bae
00004A57  72 2D                     jb       0x4a86
00004A59  8B 0E 8E 00               mov      cx, word ptr [0x8e]
00004A5D  8B 1E 8C 00               mov      bx, word ptr [0x8c]
00004A61  8B 56 FE                  mov      dx, word ptr [bp - 2]
00004A64  8B 46 FC                  mov      ax, word ptr [bp - 4]
00004A67  E8 44 01                  call     0x4bae
00004A6A  77 1A                     ja       0x4a86
00004A6C  8B 16 8A 00               mov      dx, word ptr [0x8a]
00004A70  A1 88 00                  mov      ax, word ptr [0x88]
00004A73  89 56 FA                  mov      word ptr [bp - 6], dx
00004A76  89 46 F8                  mov      word ptr [bp - 8], ax
00004A79  FF 76 FE                  push     word ptr [bp - 2]
00004A7C  FF 76 FC                  push     word ptr [bp - 4]
00004A7F  E8 B8 FE                  call     0x493a
00004A82  0B C0                     or       ax, ax
00004A84  75 08                     jne      0x4a8e
00004A86  BA FF FF                  mov      dx, 0xffff
00004A89  B8 FF FF                  mov      ax, 0xffff
00004A8C  EB 06                     jmp      0x4a94
00004A8E  8B 56 FA                  mov      dx, word ptr [bp - 6]
00004A91  8B 46 F8                  mov      ax, word ptr [bp - 8]
00004A94  5F                        pop      di
00004A95  5E                        pop      si
00004A96  8B E5                     mov      sp, bp
00004A98  5D                        pop      bp
00004A99  C3                        ret      
00004A9A  55                        push     bp
00004A9B  8B EC                     mov      bp, sp
00004A9D  83 EC 04                  sub      sp, 4
00004AA0  56                        push     si
00004AA1  57                        push     di
00004AA2  C7 46 FE 00 00            mov      word ptr [bp - 2], 0
00004AA7  C7 46 FC 00 00            mov      word ptr [bp - 4], 0
00004AAC  8B 16 8E 00               mov      dx, word ptr [0x8e]
00004AB0  A1 8C 00                  mov      ax, word ptr [0x8c]
00004AB3  8B 0E 8A 00               mov      cx, word ptr [0x8a]
00004AB7  8B 1E 88 00               mov      bx, word ptr [0x88]
00004ABB  E8 C8 00                  call     0x4b86
00004ABE  89 56 FE                  mov      word ptr [bp - 2], dx
00004AC1  89 46 FC                  mov      word ptr [bp - 4], ax
00004AC4  83 7E FE 00               cmp      word ptr [bp - 2], 0
00004AC8  72 10                     jb       0x4ada
00004ACA  77 06                     ja       0x4ad2
00004ACC  83 7E FC 10               cmp      word ptr [bp - 4], 0x10
00004AD0  76 08                     jbe      0x4ada
00004AD2  83 6E FC 10               sub      word ptr [bp - 4], 0x10
00004AD6  83 5E FE 00               sbb      word ptr [bp - 2], 0
00004ADA  83 66 FC F0               and      word ptr [bp - 4], 0xfff0
00004ADE  8B 56 FE                  mov      dx, word ptr [bp - 2]
00004AE1  8B 46 FC                  mov      ax, word ptr [bp - 4]
00004AE4  5F                        pop      di
00004AE5  5E                        pop      si
00004AE6  8B E5                     mov      sp, bp
00004AE8  5D                        pop      bp
00004AE9  CB                        retf     
00004AEA  55                        push     bp
00004AEB  8B EC                     mov      bp, sp
00004AED  56                        push     si
00004AEE  57                        push     di
00004AEF  B4 4A                     mov      ah, 0x4a
00004AF1  8B 5E 08                  mov      bx, word ptr [bp + 8]
00004AF4  8E 46 06                  mov      es, word ptr [bp + 6]
00004AF7  CD 21                     int      0x21
00004AF9  72 05                     jb       0x4b00
00004AFB  B8 FF FF                  mov      ax, 0xffff
00004AFE  EB 06                     jmp      0x4b06
00004B00  53                        push     bx
00004B01  50                        push     ax
00004B02  E8 7F D4                  call     0x1f84
00004B05  58                        pop      ax
00004B06  5F                        pop      di
00004B07  5E                        pop      si
00004B08  5D                        pop      bp
00004B09  CB                        retf     
00004B0A  55                        push     bp
00004B0B  8B EC                     mov      bp, sp
00004B0D  56                        push     si
00004B0E  57                        push     di
00004B0F  1E                        push     ds
00004B10  C5 76 06                  lds      si, ptr [bp + 6]
00004B13  C4 7E 0A                  les      di, ptr [bp + 0xa]
00004B16  FC                        cld      
00004B17  D1 E9                     shr      cx, 1
00004B19  F3 A5                     rep movsw word ptr es:[di], word ptr [si]
00004B1B  13 C9                     adc      cx, cx
00004B1D  F3 A4                     rep movsb byte ptr es:[di], byte ptr [si]
00004B1F  1F                        pop      ds
00004B20  5F                        pop      di
00004B21  5E                        pop      si
00004B22  5D                        pop      bp
00004B23  CA 08 00                  retf     8
00004B26  07                        pop      es
00004B27  0E                        push     cs
00004B28  06                        push     es
00004B29  0B C9                     or       cx, cx
00004B2B  7D 0C                     jge      0x4b39
00004B2D  F7 D3                     not      bx
00004B2F  F7 D1                     not      cx
00004B31  83 C3 01                  add      bx, 1
00004B34  83 D1 00                  adc      cx, 0
00004B37  EB 2F                     jmp      0x4b68
00004B39  03 C3                     add      ax, bx
00004B3B  73 04                     jae      0x4b41
00004B3D  81 C2 00 10               add      dx, 0x1000
00004B41  8A E9                     mov      ch, cl
00004B43  B1 04                     mov      cl, 4
00004B45  D2 E5                     shl      ch, cl
00004B47  02 F5                     add      dh, ch
00004B49  8A E8                     mov      ch, al
00004B4B  D3 E8                     shr      ax, cl
00004B4D  03 D0                     add      dx, ax
00004B4F  8A C5                     mov      al, ch
00004B51  25 0F 00                  and      ax, 0xf
00004B54  CB                        retf     
00004B55  07                        pop      es
00004B56  0E                        push     cs
00004B57  06                        push     es
00004B58  0B C9                     or       cx, cx
00004B5A  7D 0C                     jge      0x4b68
00004B5C  F7 D3                     not      bx
00004B5E  F7 D1                     not      cx
00004B60  83 C3 01                  add      bx, 1
00004B63  83 D1 00                  adc      cx, 0
00004B66  EB D1                     jmp      0x4b39
00004B68  2B C3                     sub      ax, bx
00004B6A  73 04                     jae      0x4b70
00004B6C  81 EA 00 10               sub      dx, 0x1000
00004B70  8A F9                     mov      bh, cl
00004B72  B1 04                     mov      cl, 4
00004B74  D2 E7                     shl      bh, cl
00004B76  32 DB                     xor      bl, bl
00004B78  2B D3                     sub      dx, bx
00004B7A  8A E8                     mov      ch, al
00004B7C  D3 E8                     shr      ax, cl
00004B7E  03 D0                     add      dx, ax
00004B80  8A C5                     mov      al, ch
00004B82  25 0F 00                  and      ax, 0xf
00004B85  CB                        retf     
00004B86  07                        pop      es
00004B87  0E                        push     cs
00004B88  06                        push     es
00004B89  57                        push     di
00004B8A  8B F9                     mov      di, cx
00004B8C  8A EE                     mov      ch, dh
00004B8E  B1 04                     mov      cl, 4
00004B90  D3 E2                     shl      dx, cl
00004B92  D2 ED                     shr      ch, cl
00004B94  03 D0                     add      dx, ax
00004B96  80 D5 00                  adc      ch, 0
00004B99  8B C7                     mov      ax, di
00004B9B  D3 E7                     shl      di, cl
00004B9D  D2 EC                     shr      ah, cl
00004B9F  03 DF                     add      bx, di
00004BA1  80 D4 00                  adc      ah, 0
00004BA4  2B D3                     sub      dx, bx
00004BA6  1A EC                     sbb      ch, ah
00004BA8  8A C5                     mov      al, ch
00004BAA  98                        cwde     
00004BAB  92                        xchg     dx, ax
00004BAC  5F                        pop      di
00004BAD  CB                        retf     
00004BAE  51                        push     cx
00004BAF  8A E8                     mov      ch, al
00004BB1  B1 04                     mov      cl, 4
00004BB3  D3 E8                     shr      ax, cl
00004BB5  03 D0                     add      dx, ax
00004BB7  8A C5                     mov      al, ch
00004BB9  8A E3                     mov      ah, bl
00004BBB  D3 EB                     shr      bx, cl
00004BBD  59                        pop      cx
00004BBE  03 CB                     add      cx, bx
00004BC0  8A DC                     mov      bl, ah
00004BC2  25 0F 00                  and      ax, 0xf
00004BC5  83 E3 0F                  and      bx, 0xf
00004BC8  3B D1                     cmp      dx, cx
00004BCA  75 02                     jne      0x4bce
00004BCC  3B C3                     cmp      ax, bx
00004BCE  C3                        ret      
00004BCF  55                        push     bp
00004BD0  8B EC                     mov      bp, sp
00004BD2  56                        push     si
00004BD3  57                        push     di
00004BD4  FF 76 08                  push     word ptr [bp + 8]
00004BD7  FF 76 06                  push     word ptr [bp + 6]
00004BDA  90                        nop      
00004BDB  0E                        push     cs
00004BDC  E8 77 D0                  call     0x1c56
00004BDF  59                        pop      cx
00004BE0  59                        pop      cx
00004BE1  50                        push     ax
00004BE2  FF 76 08                  push     word ptr [bp + 8]
00004BE5  FF 76 06                  push     word ptr [bp + 6]
00004BE8  A0 B8 1D                  mov      al, byte ptr [0x1db8]
00004BEB  98                        cwde     
00004BEC  50                        push     ax
00004BED  90                        nop      
00004BEE  0E                        push     cs
00004BEF  E8 07 F2                  call     0x3df9
00004BF2  83 C4 08                  add      sp, 8
00004BF5  5F                        pop      di
00004BF6  5E                        pop      si
00004BF7  5D                        pop      bp
00004BF8  CB                        retf     
00004BF9  9C                        pushf    
00004BFA  5B                        pop      bx
00004BFB  B8 FF 0F                  mov      ax, 0xfff
00004BFE  23 C3                     and      ax, bx
00004C00  50                        push     ax
00004C01  9D                        popf     
00004C02  9C                        pushf    
00004C03  58                        pop      ax
00004C04  25 00 F0                  and      ax, 0xf000
00004C07  3D 00 F0                  cmp      ax, 0xf000
00004C0A  C7 06 0C 27 00 00         mov      word ptr [0x270c], 0
00004C10  74 42                     je       0x4c54
00004C12  81 CB 00 F0               or       bx, 0xf000
00004C16  53                        push     bx
00004C17  9D                        popf     
00004C18  9C                        pushf    
00004C19  58                        pop      ax
00004C1A  25 00 F0                  and      ax, 0xf000
00004C1D  C7 06 0C 27 02 00         mov      word ptr [0x270c], 2
00004C23  74 2F                     je       0x4c54
00004C25  66 8B D4                  mov      edx, esp
00004C28  83 E4 FC                  and      sp, 0xfffc
00004C2B  66 9C                     pushfd   
00004C2D  66 58                     pop      eax
00004C2F  66 8B C8                  mov      ecx, eax
00004C32  66 35 00 00 04 00         xor      eax, 0x40000
00004C38  66 50                     push     eax
00004C3A  66 9D                     popfd    
00004C3C  66 9C                     pushfd   
00004C3E  66 58                     pop      eax
00004C40  66 33 C1                  xor      eax, ecx
00004C43  C7 06 0C 27 03 00         mov      word ptr [0x270c], 3
00004C49  66 8B E2                  mov      esp, edx
00004C4C  74 06                     je       0x4c54
00004C4E  C7 06 0C 27 04 00         mov      word ptr [0x270c], 4
00004C54  C3                        ret      
00004C55  55                        push     bp
00004C56  8B EC                     mov      bp, sp
00004C58  56                        push     si
00004C59  57                        push     di
00004C5A  FF 76 06                  push     word ptr [bp + 6]
00004C5D  90                        nop      
00004C5E  0E                        push     cs
00004C5F  E8 0C 01                  call     0x4d6e
00004C62  59                        pop      cx
00004C63  5F                        pop      di
00004C64  5E                        pop      si
00004C65  5D                        pop      bp
00004C66  CB                        retf     
00004C67  55                        push     bp
00004C68  8B EC                     mov      bp, sp
00004C6A  56                        push     si
00004C6B  57                        push     di
00004C6C  FF 76 08                  push     word ptr [bp + 8]
00004C6F  FF 76 06                  push     word ptr [bp + 6]
00004C72  90                        nop      
00004C73  0E                        push     cs
00004C74  E8 D1 F9                  call     0x4648
00004C77  59                        pop      cx
00004C78  59                        pop      cx
00004C79  5F                        pop      di
00004C7A  5E                        pop      si
00004C7B  5D                        pop      bp
00004C7C  CB                        retf     
00004C7D  55                        push     bp
00004C7E  8B EC                     mov      bp, sp
00004C80  56                        push     si
00004C81  57                        push     di
00004C82  FF 76 06                  push     word ptr [bp + 6]
00004C85  90                        nop      
00004C86  0E                        push     cs
00004C87  E8 C8 FA                  call     0x4752
00004C8A  59                        pop      cx
00004C8B  5F                        pop      di
00004C8C  5E                        pop      si
00004C8D  5D                        pop      bp
00004C8E  CB                        retf     
00004C8F  55                        push     bp
00004C90  8B EC                     mov      bp, sp
00004C92  56                        push     si
00004C93  57                        push     di
00004C94  8B 5E 06                  mov      bx, word ptr [bp + 6]
00004C97  B8 DD 34                  mov      ax, 0x34dd
00004C9A  BA 12 00                  mov      dx, 0x12
00004C9D  3B D3                     cmp      dx, bx
00004C9F  73 1A                     jae      0x4cbb
00004CA1  F7 F3                     div      bx
00004CA3  8B D8                     mov      bx, ax
00004CA5  E4 61                     in       al, 0x61
00004CA7  A8 03                     test     al, 3
00004CA9  75 08                     jne      0x4cb3
00004CAB  0C 03                     or       al, 3
00004CAD  E6 61                     out      0x61, al
00004CAF  B0 B6                     mov      al, 0xb6
00004CB1  E6 43                     out      0x43, al
00004CB3  8A C3                     mov      al, bl
00004CB5  E6 42                     out      0x42, al
00004CB7  8A C7                     mov      al, bh
00004CB9  E6 42                     out      0x42, al
00004CBB  5F                        pop      di
00004CBC  5E                        pop      si
00004CBD  5D                        pop      bp
00004CBE  CB                        retf     
00004CBF  56                        push     si
00004CC0  57                        push     di
00004CC1  E4 61                     in       al, 0x61
00004CC3  24 FC                     and      al, 0xfc
00004CC5  E6 61                     out      0x61, al
00004CC7  5F                        pop      di
00004CC8  5E                        pop      si
00004CC9  CB                        retf     
00004CCA  56                        push     si
00004CCB  57                        push     di
00004CCC  B8 16 00                  mov      ax, 0x16
00004CCF  50                        push     ax
00004CD0  90                        nop      
00004CD1  0E                        push     cs
00004CD2  E8 EF 04                  call     0x51c4
00004CD5  59                        pop      cx
00004CD6  90                        nop      
00004CD7  0E                        push     cs
00004CD8  E8 DE 00                  call     0x4db9
00004CDB  5F                        pop      di
00004CDC  5E                        pop      si
00004CDD  CB                        retf     
00004CDE  55                        push     bp
00004CDF  8B EC                     mov      bp, sp
00004CE1  56                        push     si
00004CE2  57                        push     di
00004CE3  83 3E 0E 27 20            cmp      word ptr [0x270e], 0x20
00004CE8  75 05                     jne      0x4cef
00004CEA  B8 01 00                  mov      ax, 1
00004CED  EB 1C                     jmp      0x4d0b
00004CEF  8B 1E 0E 27               mov      bx, word ptr [0x270e]
00004CF3  B1 02                     mov      cl, 2
00004CF5  D3 E3                     shl      bx, cl
00004CF7  8B 56 08                  mov      dx, word ptr [bp + 8]
00004CFA  8B 46 06                  mov      ax, word ptr [bp + 6]
00004CFD  89 97 32 58               mov      word ptr [bx + 0x5832], dx
00004D01  89 87 30 58               mov      word ptr [bx + 0x5830], ax
00004D05  FF 06 0E 27               inc      word ptr [0x270e]
00004D09  33 C0                     xor      ax, ax
00004D0B  5F                        pop      di
00004D0C  5E                        pop      si
00004D0D  5D                        pop      bp
00004D0E  CB                        retf     
00004D0F  56                        push     si
00004D10  57                        push     di
00004D11  5F                        pop      di
00004D12  5E                        pop      si
00004D13  CB                        retf     
00004D14  55                        push     bp
00004D15  8B EC                     mov      bp, sp
00004D17  56                        push     si
00004D18  57                        push     di
00004D19  83 7E 08 00               cmp      word ptr [bp + 8], 0
00004D1D  75 22                     jne      0x4d41
00004D1F  EB 10                     jmp      0x4d31
00004D21  FF 0E 0E 27               dec      word ptr [0x270e]
00004D25  8B 1E 0E 27               mov      bx, word ptr [0x270e]
00004D29  B1 02                     mov      cl, 2
00004D2B  D3 E3                     shl      bx, cl
00004D2D  FF 9F 30 58               lcall    [bx + 0x5830]
00004D31  83 3E 0E 27 00            cmp      word ptr [0x270e], 0
00004D36  75 E9                     jne      0x4d21
00004D38  90                        nop      
00004D39  0E                        push     cs
00004D3A  E8 09 B4                  call     0x146
00004D3D  FF 1E 10 27               lcall    [0x2710]
00004D41  90                        nop      
00004D42  0E                        push     cs
00004D43  E8 75 B4                  call     0x1bb
00004D46  90                        nop      
00004D47  0E                        push     cs
00004D48  E8 0E B4                  call     0x159
00004D4B  83 7E 06 00               cmp      word ptr [bp + 6], 0
00004D4F  75 17                     jne      0x4d68
00004D51  83 7E 08 00               cmp      word ptr [bp + 8], 0
00004D55  75 08                     jne      0x4d5f
00004D57  FF 1E 14 27               lcall    [0x2714]
00004D5B  FF 1E 18 27               lcall    [0x2718]
00004D5F  FF 76 04                  push     word ptr [bp + 4]
00004D62  90                        nop      
00004D63  0E                        push     cs
00004D64  E8 F3 B3                  call     0x15a
00004D67  59                        pop      cx
00004D68  5F                        pop      di
00004D69  5E                        pop      si
00004D6A  5D                        pop      bp
00004D6B  C2 06 00                  ret      6
00004D6E  55                        push     bp
00004D6F  8B EC                     mov      bp, sp
00004D71  56                        push     si
00004D72  57                        push     di
00004D73  33 C0                     xor      ax, ax
00004D75  50                        push     ax
00004D76  50                        push     ax
00004D77  FF 76 06                  push     word ptr [bp + 6]
00004D7A  E8 97 FF                  call     0x4d14
00004D7D  5F                        pop      di
00004D7E  5E                        pop      si
00004D7F  5D                        pop      bp
00004D80  CB                        retf     
00004D81  55                        push     bp
00004D82  8B EC                     mov      bp, sp
00004D84  56                        push     si
00004D85  57                        push     di
00004D86  B8 01 00                  mov      ax, 1
00004D89  50                        push     ax
00004D8A  33 C0                     xor      ax, ax
00004D8C  50                        push     ax
00004D8D  FF 76 06                  push     word ptr [bp + 6]
00004D90  E8 81 FF                  call     0x4d14
00004D93  5F                        pop      di
00004D94  5E                        pop      si
00004D95  5D                        pop      bp
00004D96  CB                        retf     
00004D97  56                        push     si
00004D98  57                        push     di
00004D99  33 C0                     xor      ax, ax
00004D9B  50                        push     ax
00004D9C  B8 01 00                  mov      ax, 1
00004D9F  50                        push     ax
00004DA0  33 C0                     xor      ax, ax
00004DA2  50                        push     ax
00004DA3  E8 6E FF                  call     0x4d14
00004DA6  5F                        pop      di
00004DA7  5E                        pop      si
00004DA8  CB                        retf     
00004DA9  56                        push     si
00004DAA  57                        push     di
00004DAB  B8 01 00                  mov      ax, 1
00004DAE  50                        push     ax
00004DAF  50                        push     ax
00004DB0  33 C0                     xor      ax, ax
00004DB2  50                        push     ax
00004DB3  E8 5E FF                  call     0x4d14
00004DB6  5F                        pop      di
00004DB7  5E                        pop      si
00004DB8  CB                        retf     
00004DB9  56                        push     si
00004DBA  57                        push     di
00004DBB  1E                        push     ds
00004DBC  B8 1C 27                  mov      ax, 0x271c
00004DBF  50                        push     ax
00004DC0  90                        nop      
00004DC1  0E                        push     cs
00004DC2  E8 0A FE                  call     0x4bcf
00004DC5  59                        pop      cx
00004DC6  59                        pop      cx
00004DC7  B8 03 00                  mov      ax, 3
00004DCA  50                        push     ax
00004DCB  90                        nop      
00004DCC  0E                        push     cs
00004DCD  E8 B1 FF                  call     0x4d81
00004DD0  59                        pop      cx
00004DD1  5F                        pop      di
00004DD2  5E                        pop      si
00004DD3  CB                        retf     
00004DD4  55                        push     bp
00004DD5  8B EC                     mov      bp, sp
00004DD7  56                        push     si
00004DD8  57                        push     di
00004DD9  B4 35                     mov      ah, 0x35
00004DDB  8A 46 06                  mov      al, byte ptr [bp + 6]
00004DDE  CD 21                     int      0x21
00004DE0  93                        xchg     bx, ax
00004DE1  8C C2                     mov      dx, es
00004DE3  5F                        pop      di
00004DE4  5E                        pop      si
00004DE5  5D                        pop      bp
00004DE6  CB                        retf     
00004DE7  55                        push     bp
00004DE8  8B EC                     mov      bp, sp
00004DEA  56                        push     si
00004DEB  57                        push     di
00004DEC  B4 25                     mov      ah, 0x25
00004DEE  8A 46 06                  mov      al, byte ptr [bp + 6]
00004DF1  1E                        push     ds
00004DF2  C5 56 08                  lds      dx, ptr [bp + 8]
00004DF5  CD 21                     int      0x21
00004DF7  1F                        pop      ds
00004DF8  5F                        pop      di
00004DF9  5E                        pop      si
00004DFA  5D                        pop      bp
00004DFB  CB                        retf     
00004DFC  55                        push     bp
00004DFD  8B EC                     mov      bp, sp
00004DFF  56                        push     si
00004E00  57                        push     di
00004E01  8C C3                     mov      bx, es
00004E03  C4 76 06                  les      si, ptr [bp + 6]
00004E06  26 89 1C                  mov      word ptr es:[si], bx
00004E09  8B 46 04                  mov      ax, word ptr [bp + 4]
00004E0C  26 89 44 02               mov      word ptr es:[si + 2], ax
00004E10  26 8C 54 04               mov      word ptr es:[si + 4], ss
00004E14  26 8C 5C 06               mov      word ptr es:[si + 6], ds
00004E18  8E C3                     mov      es, bx
00004E1A  5F                        pop      di
00004E1B  5E                        pop      si
00004E1C  5D                        pop      bp
00004E1D  CB                        retf     
00004E1E  50                        push     ax
00004E1F  53                        push     bx
00004E20  51                        push     cx
00004E21  52                        push     dx
00004E22  06                        push     es
00004E23  1E                        push     ds
00004E24  56                        push     si
00004E25  57                        push     di
00004E26  55                        push     bp
00004E27  BD D3 18                  mov      bp, 0x18d3
00004E2A  8E DD                     mov      ds, bp
00004E2C  8B EC                     mov      bp, sp
00004E2E  83 EC 04                  sub      sp, 4
00004E31  C4 5E 12                  les      bx, ptr [bp + 0x12]
00004E34  26 80 3F 62               cmp      byte ptr es:[bx], 0x62
00004E38  74 07                     je       0x4e41
00004E3A  9C                        pushf    
00004E3B  FF 1E B4 58               lcall    [0x58b4]
00004E3F  EB 53                     jmp      0x4e94
00004E41  8B 16 4E 27               mov      dx, word ptr [0x274e]
00004E45  A1 4C 27                  mov      ax, word ptr [0x274c]
00004E48  89 56 FE                  mov      word ptr [bp - 2], dx
00004E4B  89 46 FC                  mov      word ptr [bp - 4], ax
00004E4E  0B D2                     or       dx, dx
00004E50  75 05                     jne      0x4e57
00004E52  3D 01 00                  cmp      ax, 1
00004E55  74 3D                     je       0x4e94
00004E57  8B 46 FC                  mov      ax, word ptr [bp - 4]
00004E5A  0B 46 FE                  or       ax, word ptr [bp - 2]
00004E5D  74 0C                     je       0x4e6b
00004E5F  83 7E FE FF               cmp      word ptr [bp - 2], -1
00004E63  75 10                     jne      0x4e75
00004E65  83 7E FC FF               cmp      word ptr [bp - 4], -1
00004E69  75 0A                     jne      0x4e75
00004E6B  B8 01 00                  mov      ax, 1
00004E6E  50                        push     ax
00004E6F  90                        nop      
00004E70  0E                        push     cs
00004E71  E8 0D FF                  call     0x4d81
00004E74  59                        pop      cx
00004E75  C7 06 4E 27 00 00         mov      word ptr [0x274e], 0
00004E7B  C7 06 4C 27 00 00         mov      word ptr [0x274c], 0
00004E81  16                        push     ss
00004E82  8D 46 00                  lea      ax, [bp]
00004E85  50                        push     ax
00004E86  B8 0A 00                  mov      ax, 0xa
00004E89  50                        push     ax
00004E8A  B8 0B 00                  mov      ax, 0xb
00004E8D  50                        push     ax
00004E8E  FF 5E FC                  lcall    [bp - 4]
00004E91  83 C4 08                  add      sp, 8
00004E94  8B E5                     mov      sp, bp
00004E96  5D                        pop      bp
00004E97  5F                        pop      di
00004E98  5E                        pop      si
00004E99  1F                        pop      ds
00004E9A  07                        pop      es
00004E9B  5A                        pop      dx
00004E9C  59                        pop      cx
00004E9D  5B                        pop      bx
00004E9E  58                        pop      ax
00004E9F  CF                        iret     
00004EA0  50                        push     ax
00004EA1  53                        push     bx
00004EA2  51                        push     cx
00004EA3  52                        push     dx
00004EA4  06                        push     es
00004EA5  1E                        push     ds
00004EA6  56                        push     si
00004EA7  57                        push     di
00004EA8  55                        push     bp
00004EA9  BD D3 18                  mov      bp, 0x18d3
00004EAC  8E DD                     mov      ds, bp
00004EAE  8B EC                     mov      bp, sp
00004EB0  83 EC 04                  sub      sp, 4
00004EB3  8B 16 46 27               mov      dx, word ptr [0x2746]
00004EB7  A1 44 27                  mov      ax, word ptr [0x2744]
00004EBA  89 56 FE                  mov      word ptr [bp - 2], dx
00004EBD  89 46 FC                  mov      word ptr [bp - 4], ax
00004EC0  0B D2                     or       dx, dx
00004EC2  75 05                     jne      0x4ec9
00004EC4  3D 01 00                  cmp      ax, 1
00004EC7  74 3D                     je       0x4f06
00004EC9  8B 46 FC                  mov      ax, word ptr [bp - 4]
00004ECC  0B 46 FE                  or       ax, word ptr [bp - 2]
00004ECF  74 0C                     je       0x4edd
00004ED1  83 7E FE FF               cmp      word ptr [bp - 2], -1
00004ED5  75 10                     jne      0x4ee7
00004ED7  83 7E FC FF               cmp      word ptr [bp - 4], -1
00004EDB  75 0A                     jne      0x4ee7
00004EDD  B8 01 00                  mov      ax, 1
00004EE0  50                        push     ax
00004EE1  90                        nop      
00004EE2  0E                        push     cs
00004EE3  E8 9B FE                  call     0x4d81
00004EE6  59                        pop      cx
00004EE7  C7 06 46 27 00 00         mov      word ptr [0x2746], 0
00004EED  C7 06 44 27 00 00         mov      word ptr [0x2744], 0
00004EF3  16                        push     ss
00004EF4  8D 46 00                  lea      ax, [bp]
00004EF7  50                        push     ax
00004EF8  B8 14 00                  mov      ax, 0x14
00004EFB  50                        push     ax
00004EFC  B8 04 00                  mov      ax, 4
00004EFF  50                        push     ax
00004F00  FF 5E FC                  lcall    [bp - 4]
00004F03  83 C4 08                  add      sp, 8
00004F06  8B E5                     mov      sp, bp
00004F08  5D                        pop      bp
00004F09  5F                        pop      di
00004F0A  5E                        pop      si
00004F0B  1F                        pop      ds
00004F0C  07                        pop      es
00004F0D  5A                        pop      dx
00004F0E  59                        pop      cx
00004F0F  5B                        pop      bx
00004F10  58                        pop      ax
00004F11  CF                        iret     
00004F12  50                        push     ax
00004F13  53                        push     bx
00004F14  51                        push     cx
00004F15  52                        push     dx
00004F16  06                        push     es
00004F17  1E                        push     ds
00004F18  56                        push     si
00004F19  57                        push     di
00004F1A  55                        push     bp
00004F1B  BD D3 18                  mov      bp, 0x18d3
00004F1E  8E DD                     mov      ds, bp
00004F20  8B EC                     mov      bp, sp
00004F22  83 EC 04                  sub      sp, 4
00004F25  8B 16 4A 27               mov      dx, word ptr [0x274a]
00004F29  A1 48 27                  mov      ax, word ptr [0x2748]
00004F2C  89 56 FE                  mov      word ptr [bp - 2], dx
00004F2F  89 46 FC                  mov      word ptr [bp - 4], ax
00004F32  0B D2                     or       dx, dx
00004F34  75 05                     jne      0x4f3b
00004F36  3D 01 00                  cmp      ax, 1
00004F39  74 3D                     je       0x4f78
00004F3B  8B 46 FC                  mov      ax, word ptr [bp - 4]
00004F3E  0B 46 FE                  or       ax, word ptr [bp - 2]
00004F41  74 0C                     je       0x4f4f
00004F43  83 7E FE FF               cmp      word ptr [bp - 2], -1
00004F47  75 10                     jne      0x4f59
00004F49  83 7E FC FF               cmp      word ptr [bp - 4], -1
00004F4D  75 0A                     jne      0x4f59
00004F4F  B8 01 00                  mov      ax, 1
00004F52  50                        push     ax
00004F53  90                        nop      
00004F54  0E                        push     cs
00004F55  E8 29 FE                  call     0x4d81
00004F58  59                        pop      cx
00004F59  C7 06 4A 27 00 00         mov      word ptr [0x274a], 0
00004F5F  C7 06 48 27 00 00         mov      word ptr [0x2748], 0
00004F65  16                        push     ss
00004F66  8D 46 00                  lea      ax, [bp]
00004F69  50                        push     ax
00004F6A  B8 7F 00                  mov      ax, 0x7f
00004F6D  50                        push     ax
00004F6E  B8 08 00                  mov      ax, 8
00004F71  50                        push     ax
00004F72  FF 5E FC                  lcall    [bp - 4]
00004F75  83 C4 08                  add      sp, 8
00004F78  8B E5                     mov      sp, bp
00004F7A  5D                        pop      bp
00004F7B  5F                        pop      di
00004F7C  5E                        pop      si
00004F7D  1F                        pop      ds
00004F7E  07                        pop      es
00004F7F  5A                        pop      dx
00004F80  59                        pop      cx
00004F81  5B                        pop      bx
00004F82  58                        pop      ax
00004F83  CF                        iret     
00004F84  50                        push     ax
00004F85  53                        push     bx
00004F86  51                        push     cx
00004F87  52                        push     dx
00004F88  06                        push     es
00004F89  1E                        push     ds
00004F8A  56                        push     si
00004F8B  57                        push     di
00004F8C  55                        push     bp
00004F8D  BD D3 18                  mov      bp, 0x18d3
00004F90  8E DD                     mov      ds, bp
00004F92  8B EC                     mov      bp, sp
00004F94  83 EC 04                  sub      sp, 4
00004F97  8B 16 4A 27               mov      dx, word ptr [0x274a]
00004F9B  A1 48 27                  mov      ax, word ptr [0x2748]
00004F9E  89 56 FE                  mov      word ptr [bp - 2], dx
00004FA1  89 46 FC                  mov      word ptr [bp - 4], ax
00004FA4  0B D2                     or       dx, dx
00004FA6  75 05                     jne      0x4fad
00004FA8  3D 01 00                  cmp      ax, 1
00004FAB  74 3D                     je       0x4fea
00004FAD  8B 46 FC                  mov      ax, word ptr [bp - 4]
00004FB0  0B 46 FE                  or       ax, word ptr [bp - 2]
00004FB3  74 0C                     je       0x4fc1
00004FB5  83 7E FE FF               cmp      word ptr [bp - 2], -1
00004FB9  75 10                     jne      0x4fcb
00004FBB  83 7E FC FF               cmp      word ptr [bp - 4], -1
00004FBF  75 0A                     jne      0x4fcb
00004FC1  B8 01 00                  mov      ax, 1
00004FC4  50                        push     ax
00004FC5  90                        nop      
00004FC6  0E                        push     cs
00004FC7  E8 B7 FD                  call     0x4d81
00004FCA  59                        pop      cx
00004FCB  C7 06 4A 27 00 00         mov      word ptr [0x274a], 0
00004FD1  C7 06 48 27 00 00         mov      word ptr [0x2748], 0
00004FD7  16                        push     ss
00004FD8  8D 46 00                  lea      ax, [bp]
00004FDB  50                        push     ax
00004FDC  B8 7E 00                  mov      ax, 0x7e
00004FDF  50                        push     ax
00004FE0  B8 08 00                  mov      ax, 8
00004FE3  50                        push     ax
00004FE4  FF 5E FC                  lcall    [bp - 4]
00004FE7  83 C4 08                  add      sp, 8
00004FEA  8B E5                     mov      sp, bp
00004FEC  5D                        pop      bp
00004FED  5F                        pop      di
00004FEE  5E                        pop      si
00004FEF  1F                        pop      ds
00004FF0  07                        pop      es
00004FF1  5A                        pop      dx
00004FF2  59                        pop      cx
00004FF3  5B                        pop      bx
00004FF4  58                        pop      ax
00004FF5  CF                        iret     
00004FF6  50                        push     ax
00004FF7  53                        push     bx
00004FF8  51                        push     cx
00004FF9  52                        push     dx
00004FFA  06                        push     es
00004FFB  1E                        push     ds
00004FFC  56                        push     si
00004FFD  57                        push     di
00004FFE  55                        push     bp
00004FFF  BD D3 18                  mov      bp, 0x18d3
00005002  8E DD                     mov      ds, bp
00005004  8B EC                     mov      bp, sp
00005006  83 EC 04                  sub      sp, 4
00005009  8B 16 42 27               mov      dx, word ptr [0x2742]
0000500D  A1 40 27                  mov      ax, word ptr [0x2740]
00005010  89 56 FE                  mov      word ptr [bp - 2], dx
00005013  89 46 FC                  mov      word ptr [bp - 4], ax
00005016  0B D2                     or       dx, dx
00005018  75 05                     jne      0x501f
0000501A  3D 01 00                  cmp      ax, 1
0000501D  74 46                     je       0x5065
0000501F  8B 46 FC                  mov      ax, word ptr [bp - 4]
00005022  0B 46 FE                  or       ax, word ptr [bp - 2]
00005025  74 0C                     je       0x5033
00005027  83 7E FE FF               cmp      word ptr [bp - 2], -1
0000502B  75 10                     jne      0x503d
0000502D  83 7E FC FF               cmp      word ptr [bp - 4], -1
00005031  75 0A                     jne      0x503d
00005033  B8 01 00                  mov      ax, 1
00005036  50                        push     ax
00005037  90                        nop      
00005038  0E                        push     cs
00005039  E8 45 FD                  call     0x4d81
0000503C  59                        pop      cx
0000503D  C7 06 42 27 00 00         mov      word ptr [0x2742], 0
00005043  C7 06 40 27 00 00         mov      word ptr [0x2740], 0
00005049  FF 36 BA 58               push     word ptr [0x58ba]
0000504D  FF 36 B8 58               push     word ptr [0x58b8]
00005051  B8 23 00                  mov      ax, 0x23
00005054  50                        push     ax
00005055  90                        nop      
00005056  0E                        push     cs
00005057  E8 8D FD                  call     0x4de7
0000505A  83 C4 06                  add      sp, 6
0000505D  B8 02 00                  mov      ax, 2
00005060  50                        push     ax
00005061  FF 5E FC                  lcall    [bp - 4]
00005064  59                        pop      cx
00005065  8B E5                     mov      sp, bp
00005067  5D                        pop      bp
00005068  5F                        pop      di
00005069  5E                        pop      si
0000506A  1F                        pop      ds
0000506B  07                        pop      es
0000506C  5A                        pop      dx
0000506D  59                        pop      cx
0000506E  5B                        pop      bx
0000506F  58                        pop      ax
00005070  CF                        iret     
00005071  55                        push     bp
00005072  8B EC                     mov      bp, sp
00005074  56                        push     si
00005075  57                        push     di
00005076  33 D2                     xor      dx, dx
00005078  8B DA                     mov      bx, dx
0000507A  8A 87 58 27               mov      al, byte ptr [bx + 0x2758]
0000507E  B4 00                     mov      ah, 0
00005080  3B 46 06                  cmp      ax, word ptr [bp + 6]
00005083  75 04                     jne      0x5089
00005085  8B C2                     mov      ax, dx
00005087  EB 09                     jmp      0x5092
00005089  42                        inc      dx
0000508A  83 FA 06                  cmp      dx, 6
0000508D  7C E9                     jl       0x5078
0000508F  B8 FF FF                  mov      ax, 0xffff
00005092  5F                        pop      di
00005093  5E                        pop      si
00005094  5D                        pop      bp
00005095  CB                        retf     
00005096  55                        push     bp
00005097  8B EC                     mov      bp, sp
00005099  83 EC 06                  sub      sp, 6
0000509C  56                        push     si
0000509D  57                        push     di
0000509E  80 3E 3E 27 00            cmp      byte ptr [0x273e], 0
000050A3  75 11                     jne      0x50b6
000050A5  C7 06 B2 58 00 00         mov      word ptr [0x58b2], 0
000050AB  C7 06 B0 58 96 50         mov      word ptr [0x58b0], 0x5096
000050B1  C6 06 3E 27 01            mov      byte ptr [0x273e], 1
000050B6  FF 76 06                  push     word ptr [bp + 6]
000050B9  0E                        push     cs
000050BA  E8 B4 FF                  call     0x5071
000050BD  59                        pop      cx
000050BE  89 46 FE                  mov      word ptr [bp - 2], ax
000050C1  3D FF FF                  cmp      ax, 0xffff
000050C4  75 0F                     jne      0x50d5
000050C6  C7 06 7E 00 13 00         mov      word ptr [0x7e], 0x13
000050CC  BA FF FF                  mov      dx, 0xffff
000050CF  B8 FF FF                  mov      ax, 0xffff
000050D2  E9 E9 00                  jmp      0x51be
000050D5  8B 5E FE                  mov      bx, word ptr [bp - 2]
000050D8  B1 02                     mov      cl, 2
000050DA  D3 E3                     shl      bx, cl
000050DC  8B 97 42 27               mov      dx, word ptr [bx + 0x2742]
000050E0  8B 87 40 27               mov      ax, word ptr [bx + 0x2740]
000050E4  89 56 FC                  mov      word ptr [bp - 4], dx
000050E7  89 46 FA                  mov      word ptr [bp - 6], ax
000050EA  8B 5E FE                  mov      bx, word ptr [bp - 2]
000050ED  D3 E3                     shl      bx, cl
000050EF  8B 56 0A                  mov      dx, word ptr [bp + 0xa]
000050F2  8B 46 08                  mov      ax, word ptr [bp + 8]
000050F5  89 97 42 27               mov      word ptr [bx + 0x2742], dx
000050F9  89 87 40 27               mov      word ptr [bx + 0x2740], ax
000050FD  83 7E 06 02               cmp      word ptr [bp + 6], 2
00005101  75 3C                     jne      0x513f
00005103  80 3E 3D 27 00            cmp      byte ptr [0x273d], 0
00005108  75 16                     jne      0x5120
0000510A  B8 23 00                  mov      ax, 0x23
0000510D  50                        push     ax
0000510E  90                        nop      
0000510F  0E                        push     cs
00005110  E8 C1 FC                  call     0x4dd4
00005113  59                        pop      cx
00005114  89 16 BA 58               mov      word ptr [0x58ba], dx
00005118  A3 B8 58                  mov      word ptr [0x58b8], ax
0000511B  C6 06 3D 27 01            mov      byte ptr [0x273d], 1
00005120  8B 46 08                  mov      ax, word ptr [bp + 8]
00005123  0B 46 0A                  or       ax, word ptr [bp + 0xa]
00005126  75 0A                     jne      0x5132
00005128  FF 36 BA 58               push     word ptr [0x58ba]
0000512C  FF 36 B8 58               push     word ptr [0x58b8]
00005130  EB 08                     jmp      0x513a
00005132  B8 00 00                  mov      ax, 0
00005135  50                        push     ax
00005136  B8 F6 4F                  mov      ax, 0x4ff6
00005139  50                        push     ax
0000513A  B8 23 00                  mov      ax, 0x23
0000513D  EB 70                     jmp      0x51af
0000513F  83 7E 06 08               cmp      word ptr [bp + 6], 8
00005143  75 20                     jne      0x5165
00005145  B8 00 00                  mov      ax, 0
00005148  50                        push     ax
00005149  B8 12 4F                  mov      ax, 0x4f12
0000514C  50                        push     ax
0000514D  33 C0                     xor      ax, ax
0000514F  50                        push     ax
00005150  90                        nop      
00005151  0E                        push     cs
00005152  E8 92 FC                  call     0x4de7
00005155  83 C4 06                  add      sp, 6
00005158  B8 00 00                  mov      ax, 0
0000515B  50                        push     ax
0000515C  B8 84 4F                  mov      ax, 0x4f84
0000515F  50                        push     ax
00005160  B8 04 00                  mov      ax, 4
00005163  EB 4A                     jmp      0x51af
00005165  83 7E 06 0B               cmp      word ptr [bp + 6], 0xb
00005169  75 33                     jne      0x519e
0000516B  80 3E 3C 27 00            cmp      byte ptr [0x273c], 0
00005170  75 46                     jne      0x51b8
00005172  B8 05 00                  mov      ax, 5
00005175  50                        push     ax
00005176  90                        nop      
00005177  0E                        push     cs
00005178  E8 59 FC                  call     0x4dd4
0000517B  59                        pop      cx
0000517C  89 16 B6 58               mov      word ptr [0x58b6], dx
00005180  A3 B4 58                  mov      word ptr [0x58b4], ax
00005183  B8 00 00                  mov      ax, 0
00005186  50                        push     ax
00005187  B8 1E 4E                  mov      ax, 0x4e1e
0000518A  50                        push     ax
0000518B  B8 05 00                  mov      ax, 5
0000518E  50                        push     ax
0000518F  90                        nop      
00005190  0E                        push     cs
00005191  E8 53 FC                  call     0x4de7
00005194  83 C4 06                  add      sp, 6
00005197  C6 06 3C 27 01            mov      byte ptr [0x273c], 1
0000519C  EB 1A                     jmp      0x51b8
0000519E  83 7E 06 04               cmp      word ptr [bp + 6], 4
000051A2  75 14                     jne      0x51b8
000051A4  B8 00 00                  mov      ax, 0
000051A7  50                        push     ax
000051A8  B8 A0 4E                  mov      ax, 0x4ea0
000051AB  50                        push     ax
000051AC  B8 06 00                  mov      ax, 6
000051AF  50                        push     ax
000051B0  90                        nop      
000051B1  0E                        push     cs
000051B2  E8 32 FC                  call     0x4de7
000051B5  83 C4 06                  add      sp, 6
000051B8  8B 56 FC                  mov      dx, word ptr [bp - 4]
000051BB  8B 46 FA                  mov      ax, word ptr [bp - 6]
000051BE  5F                        pop      di
000051BF  5E                        pop      si
000051C0  8B E5                     mov      sp, bp
000051C2  5D                        pop      bp
000051C3  CB                        retf     
000051C4  55                        push     bp
000051C5  8B EC                     mov      bp, sp
000051C7  83 EC 06                  sub      sp, 6
000051CA  56                        push     si
000051CB  57                        push     di
000051CC  FF 76 06                  push     word ptr [bp + 6]
000051CF  0E                        push     cs
000051D0  E8 9E FE                  call     0x5071
000051D3  59                        pop      cx
000051D4  89 46 FE                  mov      word ptr [bp - 2], ax
000051D7  3D FF FF                  cmp      ax, 0xffff
000051DA  75 05                     jne      0x51e1
000051DC  B8 01 00                  mov      ax, 1
000051DF  EB 74                     jmp      0x5255
000051E1  8B 5E FE                  mov      bx, word ptr [bp - 2]
000051E4  B1 02                     mov      cl, 2
000051E6  D3 E3                     shl      bx, cl
000051E8  8B 97 42 27               mov      dx, word ptr [bx + 0x2742]
000051EC  8B 87 40 27               mov      ax, word ptr [bx + 0x2740]
000051F0  89 56 FC                  mov      word ptr [bp - 4], dx
000051F3  89 46 FA                  mov      word ptr [bp - 6], ax
000051F6  0B D2                     or       dx, dx
000051F8  75 05                     jne      0x51ff
000051FA  3D 01 00                  cmp      ax, 1
000051FD  74 54                     je       0x5253
000051FF  8B 46 FA                  mov      ax, word ptr [bp - 6]
00005202  0B 46 FC                  or       ax, word ptr [bp - 4]
00005205  75 27                     jne      0x522e
00005207  8B 46 06                  mov      ax, word ptr [bp + 6]
0000520A  3D 02 00                  cmp      ax, 2
0000520D  74 0A                     je       0x5219
0000520F  3D 16 00                  cmp      ax, 0x16
00005212  75 0E                     jne      0x5222
00005214  90                        nop      
00005215  0E                        push     cs
00005216  E8 A0 FB                  call     0x4db9
00005219  33 C0                     xor      ax, ax
0000521B  CD 23                     int      0x23
0000521D  B8 03 4C                  mov      ax, 0x4c03
00005220  CD 21                     int      0x21
00005222  B8 01 00                  mov      ax, 1
00005225  50                        push     ax
00005226  90                        nop      
00005227  0E                        push     cs
00005228  E8 56 FB                  call     0x4d81
0000522B  59                        pop      cx
0000522C  EB 25                     jmp      0x5253
0000522E  8B 5E FE                  mov      bx, word ptr [bp - 2]
00005231  B1 02                     mov      cl, 2
00005233  D3 E3                     shl      bx, cl
00005235  C7 87 42 27 00 00         mov      word ptr [bx + 0x2742], 0
0000523B  C7 87 40 27 00 00         mov      word ptr [bx + 0x2740], 0
00005241  8B 5E FE                  mov      bx, word ptr [bp - 2]
00005244  8A 87 5E 27               mov      al, byte ptr [bx + 0x275e]
00005248  B4 00                     mov      ah, 0
0000524A  50                        push     ax
0000524B  FF 76 06                  push     word ptr [bp + 6]
0000524E  FF 5E FA                  lcall    [bp - 6]
00005251  59                        pop      cx
00005252  59                        pop      cx
00005253  33 C0                     xor      ax, ax
00005255  5F                        pop      di
00005256  5E                        pop      si
00005257  8B E5                     mov      sp, bp
00005259  5D                        pop      bp
0000525A  CB                        retf     
0000525B  55                        push     bp
0000525C  8B EC                     mov      bp, sp
0000525E  83 EC 08                  sub      sp, 8
00005261  56                        push     si
00005262  57                        push     di
00005263  16                        push     ss
00005264  8D 46 F8                  lea      ax, [bp - 8]
00005267  50                        push     ax
00005268  90                        nop      
00005269  0E                        push     cs
0000526A  E8 8F FB                  call     0x4dfc
0000526D  59                        pop      cx
0000526E  59                        pop      cx
0000526F  16                        push     ss
00005270  8D 46 F8                  lea      ax, [bp - 8]
00005273  50                        push     ax
00005274  FF 76 0E                  push     word ptr [bp + 0xe]
00005277  FF 76 0C                  push     word ptr [bp + 0xc]
0000527A  FF 76 0A                  push     word ptr [bp + 0xa]
0000527D  FF 76 08                  push     word ptr [bp + 8]
00005280  FF 76 06                  push     word ptr [bp + 6]
00005283  0E                        push     cs
00005284  E8 09 00                  call     0x5290
00005287  83 C4 0E                  add      sp, 0xe
0000528A  5F                        pop      di
0000528B  5E                        pop      si
0000528C  8B E5                     mov      sp, bp
0000528E  5D                        pop      bp
0000528F  CB                        retf     
00005290  55                        push     bp
00005291  8B EC                     mov      bp, sp
00005293  83 EC 0E                  sub      sp, 0xe
00005296  56                        push     si
00005297  57                        push     di
00005298  1E                        push     ds
00005299  8D 4E F2                  lea      cx, [bp - 0xe]
0000529C  89 4E FC                  mov      word ptr [bp - 4], cx
0000529F  8C 56 FE                  mov      word ptr [bp - 2], ss
000052A2  C6 46 F2 55               mov      byte ptr [bp - 0xe], 0x55
000052A6  C6 46 F3 CD               mov      byte ptr [bp - 0xd], 0xcd
000052AA  8B 46 06                  mov      ax, word ptr [bp + 6]
000052AD  88 46 F4                  mov      byte ptr [bp - 0xc], al
000052B0  C7 46 F5 5D CB            mov      word ptr [bp - 0xb], 0xcb5d
000052B5  3C 25                     cmp      al, 0x25
000052B7  72 15                     jb       0x52ce
000052B9  3C 26                     cmp      al, 0x26
000052BB  77 11                     ja       0x52ce
000052BD  C6 46 F5 36               mov      byte ptr [bp - 0xb], 0x36
000052C1  C7 46 F6 8F 06            mov      word ptr [bp - 0xa], 0x68f
000052C6  89 4E F8                  mov      word ptr [bp - 8], cx
000052C9  C7 46 FA 5D CB            mov      word ptr [bp - 6], 0xcb5d
000052CE  C5 76 10                  lds      si, ptr [bp + 0x10]
000052D1  FF 34                     push     word ptr [si]
000052D3  FF 74 06                  push     word ptr [si + 6]
000052D6  C5 76 08                  lds      si, ptr [bp + 8]
000052D9  8B 04                     mov      ax, word ptr [si]
000052DB  8B 5C 02                  mov      bx, word ptr [si + 2]
000052DE  8B 4C 04                  mov      cx, word ptr [si + 4]
000052E1  8B 54 06                  mov      dx, word ptr [si + 6]
000052E4  8B 7C 0A                  mov      di, word ptr [si + 0xa]
000052E7  8B 74 08                  mov      si, word ptr [si + 8]
000052EA  1F                        pop      ds
000052EB  07                        pop      es
000052EC  F8                        clc      
000052ED  FF 5E FC                  lcall    [bp - 4]
000052F0  9C                        pushf    
000052F1  9C                        pushf    
000052F2  56                        push     si
000052F3  1E                        push     ds
000052F4  06                        push     es
000052F5  C5 76 10                  lds      si, ptr [bp + 0x10]
000052F8  8F 04                     pop      word ptr [si]
000052FA  8F 44 06                  pop      word ptr [si + 6]
000052FD  C5 76 0C                  lds      si, ptr [bp + 0xc]
00005300  8F 44 08                  pop      word ptr [si + 8]
00005303  8F 44 0E                  pop      word ptr [si + 0xe]
00005306  8F 44 0C                  pop      word ptr [si + 0xc]
00005309  83 64 0C 01               and      word ptr [si + 0xc], 1
0000530D  89 7C 0A                  mov      word ptr [si + 0xa], di
00005310  89 54 06                  mov      word ptr [si + 6], dx
00005313  89 4C 04                  mov      word ptr [si + 4], cx
00005316  89 5C 02                  mov      word ptr [si + 2], bx
00005319  89 04                     mov      word ptr [si], ax
0000531B  1F                        pop      ds
0000531C  74 06                     je       0x5324
0000531E  50                        push     ax
0000531F  50                        push     ax
00005320  E8 61 CC                  call     0x1f84
00005323  58                        pop      ax
00005324  5F                        pop      di
00005325  5E                        pop      si
00005326  8B E5                     mov      sp, bp
00005328  5D                        pop      bp
00005329  CB                        retf     
0000532A  56                        push     si
0000532B  57                        push     di
0000532C  5F                        pop      di
0000532D  5E                        pop      si
0000532E  C3                        ret      
0000532F  56                        push     si
00005330  57                        push     di
00005331  9C                        pushf    
00005332  FA                        cli      
00005333  B0 00                     mov      al, 0
00005335  E6 43                     out      0x43, al
00005337  E8 F0 FF                  call     0x532a
0000533A  E4 40                     in       al, 0x40
0000533C  8A D8                     mov      bl, al
0000533E  E8 E9 FF                  call     0x532a
00005341  E4 40                     in       al, 0x40
00005343  8A F8                     mov      bh, al
00005345  F7 D3                     not      bx
00005347  9D                        popf     
00005348  8B C3                     mov      ax, bx
0000534A  5F                        pop      di
0000534B  5E                        pop      si
0000534C  C3                        ret      
0000534D  55                        push     bp
0000534E  8B EC                     mov      bp, sp
00005350  83 EC 02                  sub      sp, 2
00005353  56                        push     si
00005354  57                        push     di
00005355  C7 46 FE 00 00            mov      word ptr [bp - 2], 0
0000535A  E8 D2 FF                  call     0x532f
0000535D  A9 01 00                  test     ax, 1
00005360  75 0E                     jne      0x5370
00005362  C7 06 66 27 00 00         mov      word ptr [0x2766], 0
00005368  C7 06 64 27 A9 04         mov      word ptr [0x2764], 0x4a9
0000536E  EB 09                     jmp      0x5379
00005370  FF 46 FE                  inc      word ptr [bp - 2]
00005373  83 7E FE 64               cmp      word ptr [bp - 2], 0x64
00005377  7C E1                     jl       0x535a
00005379  5F                        pop      di
0000537A  5E                        pop      si
0000537B  8B E5                     mov      sp, bp
0000537D  5D                        pop      bp
0000537E  CB                        retf     
0000537F  55                        push     bp
00005380  8B EC                     mov      bp, sp
00005382  83 EC 06                  sub      sp, 6
00005385  56                        push     si
00005386  57                        push     di
00005387  E8 A5 FF                  call     0x532f
0000538A  89 46 FA                  mov      word ptr [bp - 6], ax
0000538D  33 D2                     xor      dx, dx
0000538F  8B 5E 06                  mov      bx, word ptr [bp + 6]
00005392  33 C9                     xor      cx, cx
00005394  50                        push     ax
00005395  52                        push     dx
00005396  8B 16 66 27               mov      dx, word ptr [0x2766]
0000539A  A1 64 27                  mov      ax, word ptr [0x2764]
0000539D  E8 F8 EB                  call     0x3f98
000053A0  5B                        pop      bx
000053A1  59                        pop      cx
000053A2  03 C8                     add      cx, ax
000053A4  13 DA                     adc      bx, dx
000053A6  89 5E FE                  mov      word ptr [bp - 2], bx
000053A9  89 4E FC                  mov      word ptr [bp - 4], cx
000053AC  EB 19                     jmp      0x53c7
000053AE  3B 5E FA                  cmp      bx, word ptr [bp - 6]
000053B1  73 11                     jae      0x53c4
000053B3  83 7E FE 01               cmp      word ptr [bp - 2], 1
000053B7  77 08                     ja       0x53c1
000053B9  72 1F                     jb       0x53da
000053BB  83 7E FC 00               cmp      word ptr [bp - 4], 0
000053BF  72 19                     jb       0x53da
000053C1  FF 4E FE                  dec      word ptr [bp - 2]
000053C4  89 5E FA                  mov      word ptr [bp - 6], bx
000053C7  E8 65 FF                  call     0x532f
000053CA  8B D8                     mov      bx, ax
000053CC  33 D2                     xor      dx, dx
000053CE  3B 56 FE                  cmp      dx, word ptr [bp - 2]
000053D1  72 DB                     jb       0x53ae
000053D3  75 05                     jne      0x53da
000053D5  3B 46 FC                  cmp      ax, word ptr [bp - 4]
000053D8  72 D4                     jb       0x53ae
000053DA  5F                        pop      di
000053DB  5E                        pop      si
000053DC  8B E5                     mov      sp, bp
000053DE  5D                        pop      bp
000053DF  CB                        retf     
000053E0  55                        push     bp
000053E1  8B EC                     mov      bp, sp
000053E3  56                        push     si
000053E4  57                        push     di
000053E5  B4 2A                     mov      ah, 0x2a
000053E7  CD 21                     int      0x21
000053E9  C4 5E 06                  les      bx, ptr [bp + 6]
000053EC  26 89 0F                  mov      word ptr es:[bx], cx
000053EF  26 89 57 02               mov      word ptr es:[bx + 2], dx
000053F3  5F                        pop      di
000053F4  5E                        pop      si
000053F5  5D                        pop      bp
000053F6  CB                        retf     
000053F7  55                        push     bp
000053F8  8B EC                     mov      bp, sp
000053FA  56                        push     si
000053FB  57                        push     di
000053FC  B4 2C                     mov      ah, 0x2c
000053FE  CD 21                     int      0x21
00005400  C4 5E 06                  les      bx, ptr [bp + 6]
00005403  26 89 0F                  mov      word ptr es:[bx], cx
00005406  26 89 57 02               mov      word ptr es:[bx + 2], dx
0000540A  5F                        pop      di
0000540B  5E                        pop      si
0000540C  5D                        pop      bp
0000540D  CB                        retf     
0000540E  56                        push     si
0000540F  57                        push     di
00005410  90                        nop      
00005411  0E                        push     cs
00005412  E8 B5 F8                  call     0x4cca
00005415  5F                        pop      di
00005416  5E                        pop      si
00005417  CB                        retf     
00005418  55                        push     bp
00005419  8B EC                     mov      bp, sp
0000541B  83 EC 04                  sub      sp, 4
0000541E  56                        push     si
0000541F  57                        push     di
00005420  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
00005425  26 8B 57 0C               mov      dx, word ptr es:[bx + 0xc]
00005429  26 8B 47 0A               mov      ax, word ptr es:[bx + 0xa]
0000542D  89 56 FE                  mov      word ptr [bp - 2], dx
00005430  89 46 FC                  mov      word ptr [bp - 4], ax
00005433  8B 46 06                  mov      ax, word ptr [bp + 6]
00005436  0B 46 08                  or       ax, word ptr [bp + 8]
00005439  74 13                     je       0x544e
0000543B  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
00005440  8B 56 08                  mov      dx, word ptr [bp + 8]
00005443  8B 46 06                  mov      ax, word ptr [bp + 6]
00005446  26 89 57 0C               mov      word ptr es:[bx + 0xc], dx
0000544A  26 89 47 0A               mov      word ptr es:[bx + 0xa], ax
0000544E  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
00005453  26 8C 5F 12               mov      word ptr es:[bx + 0x12], ds
00005457  8B 56 FE                  mov      dx, word ptr [bp - 2]
0000545A  8B 46 FC                  mov      ax, word ptr [bp - 4]
0000545D  5F                        pop      di
0000545E  5E                        pop      si
0000545F  8B E5                     mov      sp, bp
00005461  5D                        pop      bp
00005462  CB                        retf     
00005463  00 00                     add      byte ptr [bx + si], al
00005465  00 00                     add      byte ptr [bx + si], al
00005467  F1                        int1     
00005468  54                        push     sp
00005469  00 00                     add      byte ptr [bx + si], al
0000546B  00 00                     add      byte ptr [bx + si], al
0000546D  00 00                     add      byte ptr [bx + si], al
0000546F  00 00                     add      byte ptr [bx + si], al
00005471  00 00                     add      byte ptr [bx + si], al
00005473  00 00                     add      byte ptr [bx + si], al
00005475  00 00                     add      byte ptr [bx + si], al
00005477  00 00                     add      byte ptr [bx + si], al
00005479  00 00                     add      byte ptr [bx + si], al
0000547B  00 00                     add      byte ptr [bx + si], al
0000547D  00 00                     add      byte ptr [bx + si], al
0000547F  E2 FF                     loop     0x5480
00005481  00 00                     add      byte ptr [bx + si], al
00005483  03 00                     add      ax, word ptr [bx + si]
00005485  63 54 00                  arpl     word ptr [si], dx
00005488  00 00                     add      byte ptr [bx + si], al
0000548A  00 04                     add      byte ptr [si], al
0000548C  00 55 8B                  add      byte ptr [di - 0x75], dl
0000548F  EC                        in       al, dx
00005490  83 EC 26                  sub      sp, 0x26
00005493  56                        push     si
00005494  57                        push     di
00005495  B8 00 00                  mov      ax, 0
00005498  BB 7B 54                  mov      bx, 0x547b
0000549B  90                        nop      
0000549C  0E                        push     cs
0000549D  E8 F3 07                  call     0x5c93
000054A0  8C 5E DE                  mov      word ptr [bp - 0x22], ds
000054A3  90                        nop      
000054A4  0E                        push     cs
000054A5  E8 1C D3                  call     0x27c4
000054A8  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
000054AD  26 8B 57 0C               mov      dx, word ptr es:[bx + 0xc]
000054B1  26 8B 47 0A               mov      ax, word ptr es:[bx + 0xa]
000054B5  89 56 DC                  mov      word ptr [bp - 0x24], dx
000054B8  89 46 DA                  mov      word ptr [bp - 0x26], ax
000054BB  C7 46 EE 06 00            mov      word ptr [bp - 0x12], 6
000054C0  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
000054C5  26 83 7F 12 00            cmp      word ptr es:[bx + 0x12], 0
000054CA  75 09                     jne      0x54d5
000054CC  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
000054D1  26 8C 5F 12               mov      word ptr es:[bx + 0x12], ds
000054D5  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
000054DA  26 8B 47 12               mov      ax, word ptr es:[bx + 0x12]
000054DE  89 46 E0                  mov      word ptr [bp - 0x20], ax
000054E1  8E 5E E0                  mov      ds, word ptr [bp - 0x20]
000054E4  FF 5E DA                  lcall    [bp - 0x26]
000054E7  8E 5E DE                  mov      ds, word ptr [bp - 0x22]
000054EA  C7 46 EE 00 00            mov      word ptr [bp - 0x12], 0
000054EF  EB 08                     jmp      0x54f9
000054F1  8E 5E DE                  mov      ds, word ptr [bp - 0x22]
000054F4  90                        nop      
000054F5  0E                        push     cs
000054F6  E8 92 1E                  call     0x738b
000054F9  90                        nop      
000054FA  0E                        push     cs
000054FB  E8 CC F7                  call     0x4cca
000054FE  FF 76 E2                  push     word ptr [bp - 0x1e]
00005501  90                        nop      
00005502  0E                        push     cs
00005503  E8 FC 07                  call     0x5d02
00005506  5F                        pop      di
00005507  5E                        pop      si
00005508  8B E5                     mov      sp, bp
0000550A  5D                        pop      bp
0000550B  CB                        retf     
0000550C  56                        push     si
0000550D  57                        push     di
0000550E  0E                        push     cs
0000550F  E8 7B FF                  call     0x548d
00005512  5F                        pop      di
00005513  5E                        pop      si
00005514  CB                        retf     
00005515  55                        push     bp
00005516  8B EC                     mov      bp, sp
00005518  83 EC 04                  sub      sp, 4
0000551B  56                        push     si
0000551C  57                        push     di
0000551D  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
00005522  26 8B 57 10               mov      dx, word ptr es:[bx + 0x10]
00005526  26 8B 47 0E               mov      ax, word ptr es:[bx + 0xe]
0000552A  89 56 FE                  mov      word ptr [bp - 2], dx
0000552D  89 46 FC                  mov      word ptr [bp - 4], ax
00005530  8B 46 06                  mov      ax, word ptr [bp + 6]
00005533  0B 46 08                  or       ax, word ptr [bp + 8]
00005536  74 13                     je       0x554b
00005538  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
0000553D  8B 56 08                  mov      dx, word ptr [bp + 8]
00005540  8B 46 06                  mov      ax, word ptr [bp + 6]
00005543  26 89 57 10               mov      word ptr es:[bx + 0x10], dx
00005547  26 89 47 0E               mov      word ptr es:[bx + 0xe], ax
0000554B  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
00005550  26 8C 5F 14               mov      word ptr es:[bx + 0x14], ds
00005554  8B 56 FE                  mov      dx, word ptr [bp - 2]
00005557  8B 46 FC                  mov      ax, word ptr [bp - 4]
0000555A  5F                        pop      di
0000555B  5E                        pop      si
0000555C  8B E5                     mov      sp, bp
0000555E  5D                        pop      bp
0000555F  CB                        retf     
00005560  55                        push     bp
00005561  8B EC                     mov      bp, sp
00005563  83 EC 06                  sub      sp, 6
00005566  56                        push     si
00005567  57                        push     di
00005568  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
0000556D  26 8B 57 10               mov      dx, word ptr es:[bx + 0x10]
00005571  26 8B 47 0E               mov      ax, word ptr es:[bx + 0xe]
00005575  89 56 FC                  mov      word ptr [bp - 4], dx
00005578  89 46 FA                  mov      word ptr [bp - 6], ax
0000557B  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
00005580  26 83 7F 14 00            cmp      word ptr es:[bx + 0x14], 0
00005585  75 09                     jne      0x5590
00005587  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
0000558C  26 8C 5F 14               mov      word ptr es:[bx + 0x14], ds
00005590  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
00005595  26 8B 47 14               mov      ax, word ptr es:[bx + 0x14]
00005599  89 46 FE                  mov      word ptr [bp - 2], ax
0000559C  1E                        push     ds
0000559D  8E 5E FE                  mov      ds, word ptr [bp - 2]
000055A0  FF 5E FA                  lcall    [bp - 6]
000055A3  1F                        pop      ds
000055A4  90                        nop      
000055A5  0E                        push     cs
000055A6  E8 21 F7                  call     0x4cca
000055A9  5F                        pop      di
000055AA  5E                        pop      si
000055AB  8B E5                     mov      sp, bp
000055AD  5D                        pop      bp
000055AE  CB                        retf     
000055AF  55                        push     bp
000055B0  8B EC                     mov      bp, sp
000055B2  83 EC 08                  sub      sp, 8
000055B5  56                        push     si
000055B6  57                        push     di
000055B7  8B 46 06                  mov      ax, word ptr [bp + 6]
000055BA  0B 46 08                  or       ax, word ptr [bp + 8]
000055BD  75 04                     jne      0x55c3
000055BF  33 C0                     xor      ax, ax
000055C1  EB 3A                     jmp      0x55fd
000055C3  C4 5E 06                  les      bx, ptr [bp + 6]
000055C6  03 5E 0A                  add      bx, word ptr [bp + 0xa]
000055C9  26 8B 07                  mov      ax, word ptr es:[bx]
000055CC  8C 5E FE                  mov      word ptr [bp - 2], ds
000055CF  89 46 FC                  mov      word ptr [bp - 4], ax
000055D2  C4 5E FC                  les      bx, ptr [bp - 4]
000055D5  8B 56 FE                  mov      dx, word ptr [bp - 2]
000055D8  8B 46 FC                  mov      ax, word ptr [bp - 4]
000055DB  26 2B 47 FE               sub      ax, word ptr es:[bx - 2]
000055DF  89 56 FE                  mov      word ptr [bp - 2], dx
000055E2  89 46 FC                  mov      word ptr [bp - 4], ax
000055E5  C4 5E FC                  les      bx, ptr [bp - 4]
000055E8  26 8B 57 FA               mov      dx, word ptr es:[bx - 6]
000055EC  26 8B 47 F8               mov      ax, word ptr es:[bx - 8]
000055F0  89 56 FA                  mov      word ptr [bp - 6], dx
000055F3  89 46 F8                  mov      word ptr [bp - 8], ax
000055F6  C4 5E F8                  les      bx, ptr [bp - 8]
000055F9  26 8B 47 1A               mov      ax, word ptr es:[bx + 0x1a]
000055FD  5F                        pop      di
000055FE  5E                        pop      si
000055FF  8B E5                     mov      sp, bp
00005601  5D                        pop      bp
00005602  CB                        retf     
00005603  55                        push     bp
00005604  8B EC                     mov      bp, sp
00005606  83 EC 08                  sub      sp, 8
00005609  56                        push     si
0000560A  57                        push     di
0000560B  8B 46 06                  mov      ax, word ptr [bp + 6]
0000560E  0B 46 08                  or       ax, word ptr [bp + 8]
00005611  75 04                     jne      0x5617
00005613  33 C0                     xor      ax, ax
00005615  EB 3E                     jmp      0x5655
00005617  C4 5E 06                  les      bx, ptr [bp + 6]
0000561A  03 5E 0A                  add      bx, word ptr [bp + 0xa]
0000561D  26 8B 57 02               mov      dx, word ptr es:[bx + 2]
00005621  26 8B 07                  mov      ax, word ptr es:[bx]
00005624  89 56 FE                  mov      word ptr [bp - 2], dx
00005627  89 46 FC                  mov      word ptr [bp - 4], ax
0000562A  C4 5E FC                  les      bx, ptr [bp - 4]
0000562D  8B 56 FE                  mov      dx, word ptr [bp - 2]
00005630  8B 46 FC                  mov      ax, word ptr [bp - 4]
00005633  26 2B 47 FE               sub      ax, word ptr es:[bx - 2]
00005637  89 56 FE                  mov      word ptr [bp - 2], dx
0000563A  89 46 FC                  mov      word ptr [bp - 4], ax
0000563D  C4 5E FC                  les      bx, ptr [bp - 4]
00005640  26 8B 57 FA               mov      dx, word ptr es:[bx - 6]
00005644  26 8B 47 F8               mov      ax, word ptr es:[bx - 8]
00005648  89 56 FA                  mov      word ptr [bp - 6], dx
0000564B  89 46 F8                  mov      word ptr [bp - 8], ax
0000564E  C4 5E F8                  les      bx, ptr [bp - 8]
00005651  26 8B 47 1A               mov      ax, word ptr es:[bx + 0x1a]
00005655  5F                        pop      di
00005656  5E                        pop      si
00005657  8B E5                     mov      sp, bp
00005659  5D                        pop      bp
0000565A  CB                        retf     
0000565B  56                        push     si
0000565C  57                        push     di
0000565D  36 C7 06 12 00 00 00      mov      word ptr ss:[0x12], 0
00005664  36 C7 06 10 00 00 00      mov      word ptr ss:[0x10], 0
0000566B  36 8C 1E 18 00            mov      word ptr ss:[0x18], ds
00005670  36 C7 06 16 00 68 27      mov      word ptr ss:[0x16], 0x2768
00005677  36 C7 06 1A 00 ED FE      mov      word ptr ss:[0x1a], 0xfeed
0000567E  8C D8                     mov      ax, ds
00005680  A3 7C 27                  mov      word ptr [0x277c], ax
00005683  A3 7A 27                  mov      word ptr [0x277a], ax
00005686  36 8B 16 18 00            mov      dx, word ptr ss:[0x18]
0000568B  36 A1 16 00               mov      ax, word ptr ss:[0x16]
0000568F  05 A8 00                  add      ax, 0xa8
00005692  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
00005697  26 89 57 22               mov      word ptr es:[bx + 0x22], dx
0000569B  26 89 47 20               mov      word ptr es:[bx + 0x20], ax
0000569F  36 C7 06 14 00 FF FF      mov      word ptr ss:[0x14], 0xffff
000056A6  5F                        pop      di
000056A7  5E                        pop      si
000056A8  CB                        retf     
000056A9  55                        push     bp
000056AA  8B EC                     mov      bp, sp
000056AC  56                        push     si
000056AD  57                        push     di
000056AE  8B 46 06                  mov      ax, word ptr [bp + 6]
000056B1  0B 46 08                  or       ax, word ptr [bp + 8]
000056B4  75 14                     jne      0x56ca
000056B6  B8 06 00                  mov      ax, 6
000056B9  50                        push     ax
000056BA  90                        nop      
000056BB  0E                        push     cs
000056BC  E8 F4 ED                  call     0x44b3
000056BF  59                        pop      cx
000056C0  89 56 08                  mov      word ptr [bp + 8], dx
000056C3  89 46 06                  mov      word ptr [bp + 6], ax
000056C6  0B C2                     or       ax, dx
000056C8  74 1E                     je       0x56e8
000056CA  FF 76 0C                  push     word ptr [bp + 0xc]
000056CD  FF 76 0A                  push     word ptr [bp + 0xa]
000056D0  FF 76 08                  push     word ptr [bp + 8]
000056D3  FF 76 06                  push     word ptr [bp + 6]
000056D6  90                        nop      
000056D7  0E                        push     cs
000056D8  E8 F9 01                  call     0x58d4
000056DB  83 C4 08                  add      sp, 8
000056DE  C4 5E 06                  les      bx, ptr [bp + 6]
000056E1  8B 46 0E                  mov      ax, word ptr [bp + 0xe]
000056E4  26 89 47 04               mov      word ptr es:[bx + 4], ax
000056E8  90                        nop      
000056E9  0E                        push     cs
000056EA  E8 9A 05                  call     0x5c87
000056ED  8B D8                     mov      bx, ax
000056EF  8E C2                     mov      es, dx
000056F1  26 83 07 01               add      word ptr es:[bx], 1
000056F5  26 83 57 02 00            adc      word ptr es:[bx + 2], 0
000056FA  8B 56 08                  mov      dx, word ptr [bp + 8]
000056FD  8B 46 06                  mov      ax, word ptr [bp + 6]
00005700  5F                        pop      di
00005701  5E                        pop      si
00005702  5D                        pop      bp
00005703  CB                        retf     
00005704  E8 57 00                  call     0x575e
00005707  00 00                     add      byte ptr [bx + si], al
00005709  00 00                     add      byte ptr [bx + si], al
0000570B  00 E8                     add      al, ch
0000570D  57                        push     di
0000570E  00 00                     add      byte ptr [bx + si], al
00005710  04 00                     add      al, 0
00005712  FA                        cli      
00005713  FF 00                     inc      word ptr [bx + si]
00005715  00 00                     add      byte ptr [bx + si], al
00005717  00 00                     add      byte ptr [bx + si], al
00005719  00 04                     add      byte ptr [si], al
0000571B  57                        push     di
0000571C  00 00                     add      byte ptr [bx + si], al
0000571E  DC FF                     fdiv     st(7), st(0)
00005720  00 00                     add      byte ptr [bx + si], al
00005722  05 00 00                  add      ax, 0
00005725  00 0C                     add      byte ptr [si], cl
00005727  57                        push     di
00005728  55                        push     bp
00005729  8B EC                     mov      bp, sp
0000572B  83 EC 28                  sub      sp, 0x28
0000572E  56                        push     si
0000572F  57                        push     di
00005730  B8 00 00                  mov      ax, 0
00005733  BB 1A 57                  mov      bx, 0x571a
00005736  90                        nop      
00005737  0E                        push     cs
00005738  E8 58 05                  call     0x5c93
0000573B  33 C0                     xor      ax, ax
0000573D  50                        push     ax
0000573E  50                        push     ax
0000573F  50                        push     ax
00005740  50                        push     ax
00005741  B8 05 00                  mov      ax, 5
00005744  50                        push     ax
00005745  B8 00 00                  mov      ax, 0
00005748  50                        push     ax
00005749  B8 A5 57                  mov      ax, 0x57a5
0000574C  50                        push     ax
0000574D  33 C0                     xor      ax, ax
0000574F  50                        push     ax
00005750  50                        push     ax
00005751  C7 46 E8 06 00            mov      word ptr [bp - 0x18], 6
00005756  8B 56 08                  mov      dx, word ptr [bp + 8]
00005759  8B 46 06                  mov      ax, word ptr [bp + 6]
0000575C  89 56 DA                  mov      word ptr [bp - 0x26], dx
0000575F  89 46 D8                  mov      word ptr [bp - 0x28], ax
00005762  52                        push     dx
00005763  50                        push     ax
00005764  16                        push     ss
00005765  8D 46 FA                  lea      ax, [bp - 6]
00005768  50                        push     ax
00005769  90                        nop      
0000576A  0E                        push     cs
0000576B  E8 31 02                  call     0x599f
0000576E  83 C4 08                  add      sp, 8
00005771  C4 5E D8                  les      bx, ptr [bp - 0x28]
00005774  26 8B 47 04               mov      ax, word ptr es:[bx + 4]
00005778  89 46 FE                  mov      word ptr [bp - 2], ax
0000577B  90                        nop      
0000577C  0E                        push     cs
0000577D  E8 07 05                  call     0x5c87
00005780  8B D8                     mov      bx, ax
00005782  8E C2                     mov      es, dx
00005784  26 83 07 01               add      word ptr es:[bx], 1
00005788  26 83 57 02 00            adc      word ptr es:[bx + 2], 0
0000578D  8D 46 FA                  lea      ax, [bp - 6]
00005790  16                        push     ss
00005791  50                        push     ax
00005792  0E                        push     cs
00005793  B8 E8 57                  mov      ax, 0x57e8
00005796  50                        push     ax
00005797  90                        nop      
00005798  0E                        push     cs
00005799  E8 27 14                  call     0x6bc3
0000579C  83 C4 1A                  add      sp, 0x1a
0000579F  5F                        pop      di
000057A0  5E                        pop      si
000057A1  8B E5                     mov      sp, bp
000057A3  5D                        pop      bp
000057A4  CB                        retf     
000057A5  55                        push     bp
000057A6  8B EC                     mov      bp, sp
000057A8  56                        push     si
000057A9  57                        push     di
000057AA  FF 76 0C                  push     word ptr [bp + 0xc]
000057AD  FF 76 0A                  push     word ptr [bp + 0xa]
000057B0  FF 76 08                  push     word ptr [bp + 8]
000057B3  FF 76 06                  push     word ptr [bp + 6]
000057B6  90                        nop      
000057B7  0E                        push     cs
000057B8  E8 E4 01                  call     0x599f
000057BB  83 C4 08                  add      sp, 8
000057BE  C4 5E 0A                  les      bx, ptr [bp + 0xa]
000057C1  26 8B 47 04               mov      ax, word ptr es:[bx + 4]
000057C5  C4 5E 06                  les      bx, ptr [bp + 6]
000057C8  26 89 47 04               mov      word ptr es:[bx + 4], ax
000057CC  90                        nop      
000057CD  0E                        push     cs
000057CE  E8 B6 04                  call     0x5c87
000057D1  8B D8                     mov      bx, ax
000057D3  8E C2                     mov      es, dx
000057D5  26 83 07 01               add      word ptr es:[bx], 1
000057D9  26 83 57 02 00            adc      word ptr es:[bx + 2], 0
000057DE  8B 56 08                  mov      dx, word ptr [bp + 8]
000057E1  8B 46 06                  mov      ax, word ptr [bp + 6]
000057E4  5F                        pop      di
000057E5  5E                        pop      si
000057E6  5D                        pop      bp
000057E7  CB                        retf     
000057E8  06                        push     es
000057E9  00 03                     add      byte ptr [bp + di], al
000057EB  00 26 00 FF               add      byte ptr [0xff00], ah
000057EF  FF 07                     inc      word ptr [bx]
000057F1  00 2E 00 3A               add      byte ptr [0x3a00], ch
000057F5  00 00                     add      byte ptr [bx + si], al
000057F7  00 00                     add      byte ptr [bx + si], al
000057F9  00 00                     add      byte ptr [bx + si], al
000057FB  00 00                     add      byte ptr [bx + si], al
000057FD  00 00                     add      byte ptr [bx + si], al
000057FF  00 00                     add      byte ptr [bx + si], al
00005801  00 02                     add      byte ptr [bp + si], al
00005803  00 02                     add      byte ptr [bp + si], al
00005805  00 2A                     add      byte ptr [bp + si], ch
00005807  58                        pop      ax
00005808  00 00                     add      byte ptr [bx + si], al
0000580A  05 00 3E                  add      ax, 0x3e00
0000580D  00 78 61                  add      byte ptr [bx + si + 0x61], bh
00005810  6C                        insb     byte ptr es:[di], dx
00005811  6C                        insb     byte ptr es:[di], dx
00005812  6F                        outsw    dx, word ptr [si]
00005813  63 00                     arpl     word ptr [bx + si], ax
00005815  00 78 58                  add      byte ptr [bx + si + 0x58], bh
00005818  00 00                     add      byte ptr [bx + si], al
0000581A  00 00                     add      byte ptr [bx + si], al
0000581C  03 00                     add      ax, word ptr [bx + si]
0000581E  00 00                     add      byte ptr [bx + si], al
00005820  00 00                     add      byte ptr [bx + si], al
00005822  00 00                     add      byte ptr [bx + si], al
00005824  00 00                     add      byte ptr [bx + si], al
00005826  00 00                     add      byte ptr [bx + si], al
00005828  00 00                     add      byte ptr [bx + si], al
0000582A  55                        push     bp
0000582B  8B EC                     mov      bp, sp
0000582D  56                        push     si
0000582E  57                        push     di
0000582F  8B 46 06                  mov      ax, word ptr [bp + 6]
00005832  0B 46 08                  or       ax, word ptr [bp + 8]
00005835  74 3B                     je       0x5872
00005837  90                        nop      
00005838  0E                        push     cs
00005839  E8 4B 04                  call     0x5c87
0000583C  8B D8                     mov      bx, ax
0000583E  8E C2                     mov      es, dx
00005840  26 83 2F 01               sub      word ptr es:[bx], 1
00005844  26 83 5F 02 00            sbb      word ptr es:[bx + 2], 0
00005849  33 C0                     xor      ax, ax
0000584B  50                        push     ax
0000584C  FF 76 08                  push     word ptr [bp + 8]
0000584F  FF 76 06                  push     word ptr [bp + 6]
00005852  90                        nop      
00005853  0E                        push     cs
00005854  E8 F3 01                  call     0x5a4a
00005857  83 C4 06                  add      sp, 6
0000585A  F7 46 0A 01 00            test     word ptr [bp + 0xa], 1
0000585F  74 0F                     je       0x5870
00005861  FF 76 08                  push     word ptr [bp + 8]
00005864  FF 76 06                  push     word ptr [bp + 6]
00005867  90                        nop      
00005868  0E                        push     cs
00005869  E8 AE EB                  call     0x441a
0000586C  59                        pop      cx
0000586D  59                        pop      cx
0000586E  EB 04                     jmp      0x5874
00005870  EB 02                     jmp      0x5874
00005872  33 C0                     xor      ax, ax
00005874  5F                        pop      di
00005875  5E                        pop      si
00005876  5D                        pop      bp
00005877  CB                        retf     
00005878  04 00                     add      al, 0
0000587A  03 00                     add      ax, word ptr [bx + si]
0000587C  26 00 FF                  add      bh, bh
0000587F  FF 03                     inc      word ptr [bp + di]
00005881  00 2C                     add      byte ptr [si], ch
00005883  00 30                     add      byte ptr [bx + si], dh
00005885  00 00                     add      byte ptr [bx + si], al
00005887  00 00                     add      byte ptr [bx + si], al
00005889  00 00                     add      byte ptr [bx + si], al
0000588B  00 00                     add      byte ptr [bx + si], al
0000588D  00 00                     add      byte ptr [bx + si], al
0000588F  00 00                     add      byte ptr [bx + si], al
00005891  00 01                     add      byte ptr [bx + di], al
00005893  00 01                     add      byte ptr [bx + di], al
00005895  00 4A 5A                  add      byte ptr [bp + si + 0x5a], cl
00005898  00 00                     add      byte ptr [bx + si], al
0000589A  05 00 34                  add      ax, 0x3400
0000589D  00 78 6D                  add      byte ptr [bx + si + 0x6d], bh
000058A0  73 67                     jae      0x5909
000058A2  00 00                     add      byte ptr [bx + si], al
000058A4  00 00                     add      byte ptr [bx + si], al
000058A6  00 00                     add      byte ptr [bx + si], al
000058A8  00 00                     add      byte ptr [bx + si], al
000058AA  00 00                     add      byte ptr [bx + si], al
000058AC  00 00                     add      byte ptr [bx + si], al
000058AE  00 00                     add      byte ptr [bx + si], al
000058B0  3A 5C 00                  cmp      bl, byte ptr [si]
000058B3  00 87 20 FC               add      byte ptr [bx - 0x3e0], al
000058B7  FF 00                     inc      word ptr [bx + si]
000058B9  00 00                     add      byte ptr [bx + si], al
000058BB  00 00                     add      byte ptr [bx + si], al
000058BD  00 00                     add      byte ptr [bx + si], al
000058BF  00 00                     add      byte ptr [bx + si], al
000058C1  00 DE                     add      dh, bl
000058C3  FF 00                     inc      word ptr [bx + si]
000058C5  00 05                     add      byte ptr [di], al
000058C7  00 00                     add      byte ptr [bx + si], al
000058C9  00 FF                     add      bh, bh
000058CB  FF 06 00 05               inc      word ptr [0x500]
000058CF  00 00                     add      byte ptr [bx + si], al
000058D1  00 B0 58 55               add      byte ptr [bx + si + 0x5558], dh
000058D5  8B EC                     mov      bp, sp
000058D7  83 EC 22                  sub      sp, 0x22
000058DA  56                        push     si
000058DB  57                        push     di
000058DC  B8 00 00                  mov      ax, 0
000058DF  BB BE 58                  mov      bx, 0x58be
000058E2  90                        nop      
000058E3  0E                        push     cs
000058E4  E8 AC 03                  call     0x5c93
000058E7  8B 46 06                  mov      ax, word ptr [bp + 6]
000058EA  0B 46 08                  or       ax, word ptr [bp + 8]
000058ED  75 14                     jne      0x5903
000058EF  B8 04 00                  mov      ax, 4
000058F2  50                        push     ax
000058F3  90                        nop      
000058F4  0E                        push     cs
000058F5  E8 BB EB                  call     0x44b3
000058F8  59                        pop      cx
000058F9  89 56 08                  mov      word ptr [bp + 8], dx
000058FC  89 46 06                  mov      word ptr [bp + 6], ax
000058FF  0B C2                     or       ax, dx
00005901  74 52                     je       0x5955
00005903  B8 04 00                  mov      ax, 4
00005906  50                        push     ax
00005907  90                        nop      
00005908  0E                        push     cs
00005909  E8 A7 EB                  call     0x44b3
0000590C  59                        pop      cx
0000590D  89 56 FE                  mov      word ptr [bp - 2], dx
00005910  89 46 FC                  mov      word ptr [bp - 4], ax
00005913  0B C2                     or       ax, dx
00005915  74 2E                     je       0x5945
00005917  C7 46 EA 0E 00            mov      word ptr [bp - 0x16], 0xe
0000591C  FF 76 0C                  push     word ptr [bp + 0xc]
0000591F  FF 76 0A                  push     word ptr [bp + 0xa]
00005922  52                        push     dx
00005923  FF 76 FC                  push     word ptr [bp - 4]
00005926  9A 00 00 0E 18            lcall    0x180e, 0
0000592B  83 C4 08                  add      sp, 8
0000592E  90                        nop      
0000592F  0E                        push     cs
00005930  E8 54 03                  call     0x5c87
00005933  8B D8                     mov      bx, ax
00005935  8E C2                     mov      es, dx
00005937  26 83 2F 01               sub      word ptr es:[bx], 1
0000593B  26 83 5F 02 00            sbb      word ptr es:[bx + 2], 0
00005940  C7 46 EA 06 00            mov      word ptr [bp - 0x16], 6
00005945  8B 56 FE                  mov      dx, word ptr [bp - 2]
00005948  8B 46 FC                  mov      ax, word ptr [bp - 4]
0000594B  C4 5E 06                  les      bx, ptr [bp + 6]
0000594E  26 89 57 02               mov      word ptr es:[bx + 2], dx
00005952  26 89 07                  mov      word ptr es:[bx], ax
00005955  90                        nop      
00005956  0E                        push     cs
00005957  E8 2D 03                  call     0x5c87
0000595A  8B D8                     mov      bx, ax
0000595C  8E C2                     mov      es, dx
0000595E  26 83 07 01               add      word ptr es:[bx], 1
00005962  26 83 57 02 00            adc      word ptr es:[bx + 2], 0
00005967  FF 76 DE                  push     word ptr [bp - 0x22]
0000596A  90                        nop      
0000596B  0E                        push     cs
0000596C  E8 93 03                  call     0x5d02
0000596F  8B 56 08                  mov      dx, word ptr [bp + 8]
00005972  8B 46 06                  mov      ax, word ptr [bp + 6]
00005975  5F                        pop      di
00005976  5E                        pop      si
00005977  8B E5                     mov      sp, bp
00005979  5D                        pop      bp
0000597A  CB                        retf     
0000597B  3A 5C 00                  cmp      bl, byte ptr [si]
0000597E  00 87 20 FC               add      byte ptr [bx - 0x3e0], al
00005982  FF 00                     inc      word ptr [bx + si]
00005984  00 00                     add      byte ptr [bx + si], al
00005986  00 00                     add      byte ptr [bx + si], al
00005988  00 00                     add      byte ptr [bx + si], al
0000598A  00 00                     add      byte ptr [bx + si], al
0000598C  00 DE                     add      dh, bl
0000598E  FF 00                     inc      word ptr [bx + si]
00005990  00 05                     add      byte ptr [di], al
00005992  00 00                     add      byte ptr [bx + si], al
00005994  00 FF                     add      bh, bh
00005996  FF 06 00 05               inc      word ptr [0x500]
0000599A  00 00                     add      byte ptr [bx + si], al
0000599C  00 7B 59                  add      byte ptr [bp + di + 0x59], bh
0000599F  55                        push     bp
000059A0  8B EC                     mov      bp, sp
000059A2  83 EC 22                  sub      sp, 0x22
000059A5  56                        push     si
000059A6  57                        push     di
000059A7  B8 00 00                  mov      ax, 0
000059AA  BB 89 59                  mov      bx, 0x5989
000059AD  90                        nop      
000059AE  0E                        push     cs
000059AF  E8 E1 02                  call     0x5c93
000059B2  8B 46 06                  mov      ax, word ptr [bp + 6]
000059B5  0B 46 08                  or       ax, word ptr [bp + 8]
000059B8  75 14                     jne      0x59ce
000059BA  B8 04 00                  mov      ax, 4
000059BD  50                        push     ax
000059BE  90                        nop      
000059BF  0E                        push     cs
000059C0  E8 F0 EA                  call     0x44b3
000059C3  59                        pop      cx
000059C4  89 56 08                  mov      word ptr [bp + 8], dx
000059C7  89 46 06                  mov      word ptr [bp + 6], ax
000059CA  0B C2                     or       ax, dx
000059CC  74 56                     je       0x5a24
000059CE  B8 04 00                  mov      ax, 4
000059D1  50                        push     ax
000059D2  90                        nop      
000059D3  0E                        push     cs
000059D4  E8 DC EA                  call     0x44b3
000059D7  59                        pop      cx
000059D8  89 56 FE                  mov      word ptr [bp - 2], dx
000059DB  89 46 FC                  mov      word ptr [bp - 4], ax
000059DE  0B C2                     or       ax, dx
000059E0  74 32                     je       0x5a14
000059E2  C7 46 EA 0E 00            mov      word ptr [bp - 0x16], 0xe
000059E7  C4 5E 0A                  les      bx, ptr [bp + 0xa]
000059EA  26 FF 77 02               push     word ptr es:[bx + 2]
000059EE  26 FF 37                  push     word ptr es:[bx]
000059F1  52                        push     dx
000059F2  FF 76 FC                  push     word ptr [bp - 4]
000059F5  9A 00 00 0E 18            lcall    0x180e, 0
000059FA  83 C4 08                  add      sp, 8
000059FD  90                        nop      
000059FE  0E                        push     cs
000059FF  E8 85 02                  call     0x5c87
00005A02  8B D8                     mov      bx, ax
00005A04  8E C2                     mov      es, dx
00005A06  26 83 2F 01               sub      word ptr es:[bx], 1
00005A0A  26 83 5F 02 00            sbb      word ptr es:[bx + 2], 0
00005A0F  C7 46 EA 06 00            mov      word ptr [bp - 0x16], 6
00005A14  8B 56 FE                  mov      dx, word ptr [bp - 2]
00005A17  8B 46 FC                  mov      ax, word ptr [bp - 4]
00005A1A  C4 5E 06                  les      bx, ptr [bp + 6]
00005A1D  26 89 57 02               mov      word ptr es:[bx + 2], dx
00005A21  26 89 07                  mov      word ptr es:[bx], ax
00005A24  90                        nop      
00005A25  0E                        push     cs
00005A26  E8 5E 02                  call     0x5c87
00005A29  8B D8                     mov      bx, ax
00005A2B  8E C2                     mov      es, dx
00005A2D  26 83 07 01               add      word ptr es:[bx], 1
00005A31  26 83 57 02 00            adc      word ptr es:[bx + 2], 0
00005A36  FF 76 DE                  push     word ptr [bp - 0x22]
00005A39  90                        nop      
00005A3A  0E                        push     cs
00005A3B  E8 C4 02                  call     0x5d02
00005A3E  8B 56 08                  mov      dx, word ptr [bp + 8]
00005A41  8B 46 06                  mov      ax, word ptr [bp + 6]
00005A44  5F                        pop      di
00005A45  5E                        pop      si
00005A46  8B E5                     mov      sp, bp
00005A48  5D                        pop      bp
00005A49  CB                        retf     
00005A4A  55                        push     bp
00005A4B  8B EC                     mov      bp, sp
00005A4D  56                        push     si
00005A4E  57                        push     di
00005A4F  90                        nop      
00005A50  0E                        push     cs
00005A51  E8 33 02                  call     0x5c87
00005A54  8B D8                     mov      bx, ax
00005A56  8E C2                     mov      es, dx
00005A58  26 83 2F 01               sub      word ptr es:[bx], 1
00005A5C  26 83 5F 02 00            sbb      word ptr es:[bx + 2], 0
00005A61  8B 46 06                  mov      ax, word ptr [bp + 6]
00005A64  0B 46 08                  or       ax, word ptr [bp + 8]
00005A67  74 3C                     je       0x5aa5
00005A69  90                        nop      
00005A6A  0E                        push     cs
00005A6B  E8 19 02                  call     0x5c87
00005A6E  8B D8                     mov      bx, ax
00005A70  8E C2                     mov      es, dx
00005A72  26 83 07 01               add      word ptr es:[bx], 1
00005A76  26 83 57 02 00            adc      word ptr es:[bx + 2], 0
00005A7B  B8 03 00                  mov      ax, 3
00005A7E  50                        push     ax
00005A7F  C4 5E 06                  les      bx, ptr [bp + 6]
00005A82  26 FF 77 02               push     word ptr es:[bx + 2]
00005A86  26 FF 37                  push     word ptr es:[bx]
00005A89  9A 05 03 0E 18            lcall    0x180e, 0x305
00005A8E  83 C4 06                  add      sp, 6
00005A91  F7 46 0A 01 00            test     word ptr [bp + 0xa], 1
00005A96  74 0D                     je       0x5aa5
00005A98  FF 76 08                  push     word ptr [bp + 8]
00005A9B  FF 76 06                  push     word ptr [bp + 6]
00005A9E  90                        nop      
00005A9F  0E                        push     cs
00005AA0  E8 77 E9                  call     0x441a
00005AA3  59                        pop      cx
00005AA4  59                        pop      cx
00005AA5  5F                        pop      di
00005AA6  5E                        pop      si
00005AA7  5D                        pop      bp
00005AA8  CB                        retf     
00005AA9  02 5C 00                  add      bl, byte ptr [si]
00005AAC  00 00                     add      byte ptr [bx + si], al
00005AAE  00 00                     add      byte ptr [bx + si], al
00005AB0  00 02                     add      byte ptr [bp + si], al
00005AB2  5C                        pop      sp
00005AB3  00 00                     add      byte ptr [bx + si], al
00005AB5  04 00                     add      al, 0
00005AB7  FC                        cld      
00005AB8  FF 00                     inc      word ptr [bx + si]
00005ABA  00 00                     add      byte ptr [bx + si], al
00005ABC  00 00                     add      byte ptr [bx + si], al
00005ABE  00 A9 5A 00               add      byte ptr [bx + di + 0x5a], ch
00005AC2  00 DE                     add      dh, bl
00005AC4  FF 00                     inc      word ptr [bx + si]
00005AC6  00 05                     add      byte ptr [di], al
00005AC8  00 00                     add      byte ptr [bx + si], al
00005ACA  00 B1 5A 55               add      byte ptr [bx + di + 0x555a], dh
00005ACE  8B EC                     mov      bp, sp
00005AD0  83 EC 22                  sub      sp, 0x22
00005AD3  56                        push     si
00005AD4  57                        push     di
00005AD5  B8 00 00                  mov      ax, 0
00005AD8  BB BF 5A                  mov      bx, 0x5abf
00005ADB  90                        nop      
00005ADC  0E                        push     cs
00005ADD  E8 B3 01                  call     0x5c93
00005AE0  33 C0                     xor      ax, ax
00005AE2  50                        push     ax
00005AE3  50                        push     ax
00005AE4  50                        push     ax
00005AE5  50                        push     ax
00005AE6  B8 05 00                  mov      ax, 5
00005AE9  50                        push     ax
00005AEA  B8 00 00                  mov      ax, 0
00005AED  50                        push     ax
00005AEE  B8 9F 59                  mov      ax, 0x599f
00005AF1  50                        push     ax
00005AF2  33 C0                     xor      ax, ax
00005AF4  50                        push     ax
00005AF5  50                        push     ax
00005AF6  C7 46 EA 06 00            mov      word ptr [bp - 0x16], 6
00005AFB  FF 76 08                  push     word ptr [bp + 8]
00005AFE  FF 76 06                  push     word ptr [bp + 6]
00005B01  16                        push     ss
00005B02  8D 46 FC                  lea      ax, [bp - 4]
00005B05  50                        push     ax
00005B06  0E                        push     cs
00005B07  E8 95 FE                  call     0x599f
00005B0A  83 C4 08                  add      sp, 8
00005B0D  8D 46 FC                  lea      ax, [bp - 4]
00005B10  16                        push     ss
00005B11  50                        push     ax
00005B12  0E                        push     cs
00005B13  B8 02 5C                  mov      ax, 0x5c02
00005B16  50                        push     ax
00005B17  90                        nop      
00005B18  0E                        push     cs
00005B19  E8 A7 10                  call     0x6bc3
00005B1C  83 C4 1A                  add      sp, 0x1a
00005B1F  5F                        pop      di
00005B20  5E                        pop      si
00005B21  8B E5                     mov      sp, bp
00005B23  5D                        pop      bp
00005B24  CB                        retf     
00005B25  3A 5C 00                  cmp      bl, byte ptr [si]
00005B28  00 87 20 FC               add      byte ptr [bx - 0x3e0], al
00005B2C  FF 00                     inc      word ptr [bx + si]
00005B2E  00 00                     add      byte ptr [bx + si], al
00005B30  00 00                     add      byte ptr [bx + si], al
00005B32  00 00                     add      byte ptr [bx + si], al
00005B34  00 00                     add      byte ptr [bx + si], al
00005B36  00 DE                     add      dh, bl
00005B38  FF 00                     inc      word ptr [bx + si]
00005B3A  00 05                     add      byte ptr [di], al
00005B3C  00 00                     add      byte ptr [bx + si], al
00005B3E  00 FF                     add      bh, bh
00005B40  FF 06 00 05               inc      word ptr [0x500]
00005B44  00 00                     add      byte ptr [bx + si], al
00005B46  00 25                     add      byte ptr [di], ah
00005B48  5B                        pop      bx
00005B49  55                        push     bp
00005B4A  8B EC                     mov      bp, sp
00005B4C  83 EC 22                  sub      sp, 0x22
00005B4F  56                        push     si
00005B50  57                        push     di
00005B51  B8 00 00                  mov      ax, 0
00005B54  BB 33 5B                  mov      bx, 0x5b33
00005B57  90                        nop      
00005B58  0E                        push     cs
00005B59  E8 37 01                  call     0x5c93
00005B5C  8B 56 08                  mov      dx, word ptr [bp + 8]
00005B5F  8B 46 06                  mov      ax, word ptr [bp + 6]
00005B62  3B 56 0C                  cmp      dx, word ptr [bp + 0xc]
00005B65  75 05                     jne      0x5b6c
00005B67  3B 46 0A                  cmp      ax, word ptr [bp + 0xa]
00005B6A  74 7E                     je       0x5bea
00005B6C  90                        nop      
00005B6D  0E                        push     cs
00005B6E  E8 16 01                  call     0x5c87
00005B71  8B D8                     mov      bx, ax
00005B73  8E C2                     mov      es, dx
00005B75  26 83 07 01               add      word ptr es:[bx], 1
00005B79  26 83 57 02 00            adc      word ptr es:[bx + 2], 0
00005B7E  B8 03 00                  mov      ax, 3
00005B81  50                        push     ax
00005B82  C4 5E 06                  les      bx, ptr [bp + 6]
00005B85  26 FF 77 02               push     word ptr es:[bx + 2]
00005B89  26 FF 37                  push     word ptr es:[bx]
00005B8C  9A 05 03 0E 18            lcall    0x180e, 0x305
00005B91  83 C4 06                  add      sp, 6
00005B94  B8 04 00                  mov      ax, 4
00005B97  50                        push     ax
00005B98  90                        nop      
00005B99  0E                        push     cs
00005B9A  E8 16 E9                  call     0x44b3
00005B9D  59                        pop      cx
00005B9E  89 56 FE                  mov      word ptr [bp - 2], dx
00005BA1  89 46 FC                  mov      word ptr [bp - 4], ax
00005BA4  0B C2                     or       ax, dx
00005BA6  74 32                     je       0x5bda
00005BA8  C7 46 EA 0E 00            mov      word ptr [bp - 0x16], 0xe
00005BAD  C4 5E 0A                  les      bx, ptr [bp + 0xa]
00005BB0  26 FF 77 02               push     word ptr es:[bx + 2]
00005BB4  26 FF 37                  push     word ptr es:[bx]
00005BB7  52                        push     dx
00005BB8  FF 76 FC                  push     word ptr [bp - 4]
00005BBB  9A 00 00 0E 18            lcall    0x180e, 0
00005BC0  83 C4 08                  add      sp, 8
00005BC3  90                        nop      
00005BC4  0E                        push     cs
00005BC5  E8 BF 00                  call     0x5c87
00005BC8  8B D8                     mov      bx, ax
00005BCA  8E C2                     mov      es, dx
00005BCC  26 83 2F 01               sub      word ptr es:[bx], 1
00005BD0  26 83 5F 02 00            sbb      word ptr es:[bx + 2], 0
00005BD5  C7 46 EA 06 00            mov      word ptr [bp - 0x16], 6
00005BDA  8B 56 FE                  mov      dx, word ptr [bp - 2]
00005BDD  8B 46 FC                  mov      ax, word ptr [bp - 4]
00005BE0  C4 5E 06                  les      bx, ptr [bp + 6]
00005BE3  26 89 57 02               mov      word ptr es:[bx + 2], dx
00005BE7  26 89 07                  mov      word ptr es:[bx], ax
00005BEA  8B 56 08                  mov      dx, word ptr [bp + 8]
00005BED  8B 46 06                  mov      ax, word ptr [bp + 6]
00005BF0  52                        push     dx
00005BF1  50                        push     ax
00005BF2  FF 76 DE                  push     word ptr [bp - 0x22]
00005BF5  90                        nop      
00005BF6  0E                        push     cs
00005BF7  E8 08 01                  call     0x5d02
00005BFA  58                        pop      ax
00005BFB  5A                        pop      dx
00005BFC  5F                        pop      di
00005BFD  5E                        pop      si
00005BFE  8B E5                     mov      sp, bp
00005C00  5D                        pop      bp
00005C01  CB                        retf     
00005C02  04 00                     add      al, 0
00005C04  03 00                     add      ax, word ptr [bx + si]
00005C06  26 00 FF                  add      bh, bh
00005C09  FF 03                     inc      word ptr [bp + di]
00005C0B  00 2C                     add      byte ptr [si], ch
00005C0D  00 30                     add      byte ptr [bx + si], dh
00005C0F  00 00                     add      byte ptr [bx + si], al
00005C11  00 00                     add      byte ptr [bx + si], al
00005C13  00 00                     add      byte ptr [bx + si], al
00005C15  00 00                     add      byte ptr [bx + si], al
00005C17  00 00                     add      byte ptr [bx + si], al
00005C19  00 00                     add      byte ptr [bx + si], al
00005C1B  00 01                     add      byte ptr [bx + di], al
00005C1D  00 01                     add      byte ptr [bx + di], al
00005C1F  00 4A 5A                  add      byte ptr [bp + si + 0x5a], cl
00005C22  00 00                     add      byte ptr [bx + si], al
00005C24  05 00 34                  add      ax, 0x3400
00005C27  00 78 6D                  add      byte ptr [bx + si + 0x6d], bh
00005C2A  73 67                     jae      0x5c93
00005C2C  00 00                     add      byte ptr [bx + si], al
00005C2E  00 00                     add      byte ptr [bx + si], al
00005C30  00 00                     add      byte ptr [bx + si], al
00005C32  00 00                     add      byte ptr [bx + si], al
00005C34  00 00                     add      byte ptr [bx + si], al
00005C36  00 00                     add      byte ptr [bx + si], al
00005C38  00 00                     add      byte ptr [bx + si], al
00005C3A  04 00                     add      al, 0
00005C3C  10 20                     adc      byte ptr [bx + si], ah
00005C3E  0A 00                     or       al, byte ptr [bx + si]
00005C40  4D                        dec      bp
00005C41  5C                        pop      sp
00005C42  00 00                     add      byte ptr [bx + si], al
00005C44  73 74                     jae      0x5cba
00005C46  72 69                     jb       0x5cb1
00005C48  6E                        outsb    dx, byte ptr [si]
00005C49  67 20 2A                  and      byte ptr [edx], ch
00005C4C  00 04                     add      byte ptr [si], al
00005C4E  00 03                     add      byte ptr [bp + di], al
00005C50  00 26 00 FF               add      byte ptr [0xff00], ah
00005C54  FF 03                     inc      word ptr [bp + di]
00005C56  00 2E 00 32               add      byte ptr [0x3200], ch
00005C5A  00 00                     add      byte ptr [bx + si], al
00005C5C  00 00                     add      byte ptr [bx + si], al
00005C5E  00 00                     add      byte ptr [bx + si], al
00005C60  00 00                     add      byte ptr [bx + si], al
00005C62  00 00                     add      byte ptr [bx + si], al
00005C64  00 00                     add      byte ptr [bx + si], al
00005C66  00 01                     add      byte ptr [bx + di], al
00005C68  00 01                     add      byte ptr [bx + di], al
00005C6A  00 05                     add      byte ptr [di], al
00005C6C  03 0E 18 05               add      cx, word ptr [0x518]
00005C70  00 36 00 73               add      byte ptr [0x7300], dh
00005C74  74 72                     je       0x5ce8
00005C76  69 6E 67 00 00            imul     bp, word ptr [bp + 0x67], 0
00005C7B  00 00                     add      byte ptr [bx + si], al
00005C7D  00 00                     add      byte ptr [bx + si], al
00005C7F  00 00                     add      byte ptr [bx + si], al
00005C81  00 00                     add      byte ptr [bx + si], al
00005C83  00 00                     add      byte ptr [bx + si], al
00005C85  00 00                     add      byte ptr [bx + si], al
00005C87  8C D2                     mov      dx, ss
00005C89  B8 10 00                  mov      ax, 0x10
00005C8C  CB                        retf     
00005C8D  8C D2                     mov      dx, ss
00005C8F  B8 14 00                  mov      ax, 0x14
00005C92  CB                        retf     
00005C93  8E C0                     mov      es, ax
00005C95  8B D3                     mov      dx, bx
00005C97  8B CD                     mov      cx, bp
00005C99  26 8B 5F 04               mov      bx, word ptr es:[bx + 4]
00005C9D  03 D9                     add      bx, cx
00005C9F  36 89 57 06               mov      word ptr ss:[bx + 6], dx
00005CA3  36 89 47 08               mov      word ptr ss:[bx + 8], ax
00005CA7  8B C4                     mov      ax, sp
00005CA9  05 04 00                  add      ax, 4
00005CAC  36 89 47 0A               mov      word ptr ss:[bx + 0xa], ax
00005CB0  B8 D3 18                  mov      ax, 0x18d3
00005CB3  36 89 47 0E               mov      word ptr ss:[bx + 0xe], ax
00005CB7  36 89 77 10               mov      word ptr ss:[bx + 0x10], si
00005CBB  36 C7 47 02 BF 7A         mov      word ptr ss:[bx + 2], 0x7abf
00005CC1  36 C7 47 04 00 00         mov      word ptr ss:[bx + 4], 0
00005CC7  36 C7 47 0C 00 00         mov      word ptr ss:[bx + 0xc], 0
00005CCD  36 C7 47 12 00 00         mov      word ptr ss:[bx + 0x12], 0
00005CD3  53                        push     bx
00005CD4  0E                        push     cs
00005CD5  E8 AF FF                  call     0x5c87
00005CD8  5B                        pop      bx
00005CD9  93                        xchg     bx, ax
00005CDA  8E C2                     mov      es, dx
00005CDC  26 8B 0F                  mov      cx, word ptr es:[bx]
00005CDF  26 8B 57 02               mov      dx, word ptr es:[bx + 2]
00005CE3  8B D8                     mov      bx, ax
00005CE5  36 89 4F 1A               mov      word ptr ss:[bx + 0x1a], cx
00005CE9  36 89 57 1C               mov      word ptr ss:[bx + 0x1c], dx
00005CED  53                        push     bx
00005CEE  0E                        push     cs
00005CEF  E8 9B FF                  call     0x5c8d
00005CF2  5B                        pop      bx
00005CF3  93                        xchg     bx, ax
00005CF4  8E C2                     mov      es, dx
00005CF6  26 8B 0F                  mov      cx, word ptr es:[bx]
00005CF9  26 89 07                  mov      word ptr es:[bx], ax
00005CFC  8B D8                     mov      bx, ax
00005CFE  36 89 0F                  mov      word ptr ss:[bx], cx
00005D01  CB                        retf     
00005D02  55                        push     bp
00005D03  8B EC                     mov      bp, sp
00005D05  0E                        push     cs
00005D06  E8 84 FF                  call     0x5c8d
00005D09  8B 5E 06                  mov      bx, word ptr [bp + 6]
00005D0C  93                        xchg     bx, ax
00005D0D  8E C2                     mov      es, dx
00005D0F  26 89 07                  mov      word ptr es:[bx], ax
00005D12  5D                        pop      bp
00005D13  CA 02 00                  retf     2
00005D16  56                        push     si
00005D17  57                        push     di
00005D18  89 DC                     mov      sp, bx
00005D1A  89 CD                     mov      bp, cx
00005D1C  52                        push     dx
00005D1D  50                        push     ax
00005D1E  CB                        retf     
00005D1F  5F                        pop      di
00005D20  5E                        pop      si
00005D21  CB                        retf     
00005D22  55                        push     bp
00005D23  8B EC                     mov      bp, sp
00005D25  56                        push     si
00005D26  57                        push     di
00005D27  8B 46 06                  mov      ax, word ptr [bp + 6]
00005D2A  0B 46 08                  or       ax, word ptr [bp + 8]
00005D2D  75 07                     jne      0x5d36
00005D2F  8C DA                     mov      dx, ds
00005D31  B8 90 28                  mov      ax, 0x2890
00005D34  EB 0D                     jmp      0x5d43
00005D36  C4 5E 06                  les      bx, ptr [bp + 6]
00005D39  8B 56 08                  mov      dx, word ptr [bp + 8]
00005D3C  8B 46 06                  mov      ax, word ptr [bp + 6]
00005D3F  26 03 47 04               add      ax, word ptr es:[bx + 4]
00005D43  5F                        pop      di
00005D44  5E                        pop      si
00005D45  5D                        pop      bp
00005D46  CB                        retf     
00005D47  55                        push     bp
00005D48  8B EC                     mov      bp, sp
00005D4A  83 EC 0A                  sub      sp, 0xa
00005D4D  56                        push     si
00005D4E  57                        push     di
00005D4F  8B 56 08                  mov      dx, word ptr [bp + 8]
00005D52  8B 46 06                  mov      ax, word ptr [bp + 6]
00005D55  3B 56 0C                  cmp      dx, word ptr [bp + 0xc]
00005D58  75 05                     jne      0x5d5f
00005D5A  3B 46 0A                  cmp      ax, word ptr [bp + 0xa]
00005D5D  74 7D                     je       0x5ddc
00005D5F  C4 5E 06                  les      bx, ptr [bp + 6]
00005D62  26 8B 47 02               mov      ax, word ptr es:[bx + 2]
00005D66  C4 5E 0A                  les      bx, ptr [bp + 0xa]
00005D69  26 3B 47 02               cmp      ax, word ptr es:[bx + 2]
00005D6D  75 65                     jne      0x5dd4
00005D6F  C4 5E 06                  les      bx, ptr [bp + 6]
00005D72  26 8B 07                  mov      ax, word ptr es:[bx]
00005D75  C4 5E 0A                  les      bx, ptr [bp + 0xa]
00005D78  26 3B 07                  cmp      ax, word ptr es:[bx]
00005D7B  75 57                     jne      0x5dd4
00005D7D  C4 5E 06                  les      bx, ptr [bp + 6]
00005D80  26 8B 47 02               mov      ax, word ptr es:[bx + 2]
00005D84  C4 5E 0A                  les      bx, ptr [bp + 0xa]
00005D87  26 0B 47 02               or       ax, word ptr es:[bx + 2]
00005D8B  A9 80 00                  test     ax, 0x80
00005D8E  75 44                     jne      0x5dd4
00005D90  C4 5E 06                  les      bx, ptr [bp + 6]
00005D93  8B 56 08                  mov      dx, word ptr [bp + 8]
00005D96  8B 46 06                  mov      ax, word ptr [bp + 6]
00005D99  26 03 47 04               add      ax, word ptr es:[bx + 4]
00005D9D  89 56 FE                  mov      word ptr [bp - 2], dx
00005DA0  89 46 FC                  mov      word ptr [bp - 4], ax
00005DA3  C4 5E 0A                  les      bx, ptr [bp + 0xa]
00005DA6  8B 56 0C                  mov      dx, word ptr [bp + 0xc]
00005DA9  8B 46 0A                  mov      ax, word ptr [bp + 0xa]
00005DAC  26 03 47 04               add      ax, word ptr es:[bx + 4]
00005DB0  89 56 FA                  mov      word ptr [bp - 6], dx
00005DB3  89 46 F8                  mov      word ptr [bp - 8], ax
00005DB6  C4 5E FC                  les      bx, ptr [bp - 4]
00005DB9  26 8A 07                  mov      al, byte ptr es:[bx]
00005DBC  98                        cwde     
00005DBD  8B D0                     mov      dx, ax
00005DBF  FF 46 FC                  inc      word ptr [bp - 4]
00005DC2  C4 5E F8                  les      bx, ptr [bp - 8]
00005DC5  26 8A 07                  mov      al, byte ptr es:[bx]
00005DC8  98                        cwde     
00005DC9  89 46 F6                  mov      word ptr [bp - 0xa], ax
00005DCC  FF 46 F8                  inc      word ptr [bp - 8]
00005DCF  3B 56 F6                  cmp      dx, word ptr [bp - 0xa]
00005DD2  74 04                     je       0x5dd8
00005DD4  33 C0                     xor      ax, ax
00005DD6  EB 07                     jmp      0x5ddf
00005DD8  0B D2                     or       dx, dx
00005DDA  75 DA                     jne      0x5db6
00005DDC  B8 01 00                  mov      ax, 1
00005DDF  5F                        pop      di
00005DE0  5E                        pop      si
00005DE1  8B E5                     mov      sp, bp
00005DE3  5D                        pop      bp
00005DE4  CB                        retf     
00005DE5  55                        push     bp
00005DE6  8B EC                     mov      bp, sp
00005DE8  83 EC 0A                  sub      sp, 0xa
00005DEB  56                        push     si
00005DEC  57                        push     di
00005DED  C4 5E 04                  les      bx, ptr [bp + 4]
00005DF0  8B 56 06                  mov      dx, word ptr [bp + 6]
00005DF3  8B 46 04                  mov      ax, word ptr [bp + 4]
00005DF6  26 03 47 0C               add      ax, word ptr es:[bx + 0xc]
00005DFA  89 56 FE                  mov      word ptr [bp - 2], dx
00005DFD  89 46 FC                  mov      word ptr [bp - 4], ax
00005E00  C4 5E FC                  les      bx, ptr [bp - 4]
00005E03  26 8B 57 02               mov      dx, word ptr es:[bx + 2]
00005E07  26 8B 07                  mov      ax, word ptr es:[bx]
00005E0A  89 56 F8                  mov      word ptr [bp - 8], dx
00005E0D  89 46 F6                  mov      word ptr [bp - 0xa], ax
00005E10  8B 46 F6                  mov      ax, word ptr [bp - 0xa]
00005E13  0B 46 F8                  or       ax, word ptr [bp - 8]
00005E16  74 7E                     je       0x5e96
00005E18  C4 5E FC                  les      bx, ptr [bp - 4]
00005E1B  26 F7 47 06 08 00         test     word ptr es:[bx + 6], 8
00005E21  75 6C                     jne      0x5e8f
00005E23  83 7E 10 00               cmp      word ptr [bp + 0x10], 0
00005E27  74 14                     je       0x5e3d
00005E29  C4 5E FC                  les      bx, ptr [bp - 4]
00005E2C  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
00005E30  25 03 00                  and      ax, 3
00005E33  3D 03 00                  cmp      ax, 3
00005E36  75 05                     jne      0x5e3d
00005E38  B8 01 00                  mov      ax, 1
00005E3B  EB 02                     jmp      0x5e3f
00005E3D  33 C0                     xor      ax, ax
00005E3F  89 46 FA                  mov      word ptr [bp - 6], ax
00005E42  FF 76 F8                  push     word ptr [bp - 8]
00005E45  FF 76 F6                  push     word ptr [bp - 0xa]
00005E48  FF 76 0A                  push     word ptr [bp + 0xa]
00005E4B  FF 76 08                  push     word ptr [bp + 8]
00005E4E  0E                        push     cs
00005E4F  E8 F5 FE                  call     0x5d47
00005E52  83 C4 08                  add      sp, 8
00005E55  0B C0                     or       ax, ax
00005E57  74 09                     je       0x5e62
00005E59  83 7E FA 00               cmp      word ptr [bp - 6], 0
00005E5D  74 03                     je       0x5e62
00005E5F  E9 C5 00                  jmp      0x5f27
00005E62  C4 5E F6                  les      bx, ptr [bp - 0xa]
00005E65  26 F7 47 08 04 00         test     word ptr es:[bx + 8], 4
00005E6B  74 22                     je       0x5e8f
00005E6D  FF 76 FA                  push     word ptr [bp - 6]
00005E70  FF 76 0E                  push     word ptr [bp + 0xe]
00005E73  FF 76 0C                  push     word ptr [bp + 0xc]
00005E76  FF 76 0A                  push     word ptr [bp + 0xa]
00005E79  FF 76 08                  push     word ptr [bp + 8]
00005E7C  FF 76 F8                  push     word ptr [bp - 8]
00005E7F  FF 76 F6                  push     word ptr [bp - 0xa]
00005E82  E8 60 FF                  call     0x5de5
00005E85  83 C4 0E                  add      sp, 0xe
00005E88  0B C0                     or       ax, ax
00005E8A  74 03                     je       0x5e8f
00005E8C  E9 98 00                  jmp      0x5f27
00005E8F  83 46 FC 08               add      word ptr [bp - 4], 8
00005E93  E9 6A FF                  jmp      0x5e00
00005E96  C4 5E 04                  les      bx, ptr [bp + 4]
00005E99  8B 56 06                  mov      dx, word ptr [bp + 6]
00005E9C  8B 46 04                  mov      ax, word ptr [bp + 4]
00005E9F  26 03 47 0A               add      ax, word ptr es:[bx + 0xa]
00005EA3  89 56 FE                  mov      word ptr [bp - 2], dx
00005EA6  89 46 FC                  mov      word ptr [bp - 4], ax
00005EA9  C4 5E FC                  les      bx, ptr [bp - 4]
00005EAC  26 8B 57 02               mov      dx, word ptr es:[bx + 2]
00005EB0  26 8B 07                  mov      ax, word ptr es:[bx]
00005EB3  89 56 F8                  mov      word ptr [bp - 8], dx
00005EB6  89 46 F6                  mov      word ptr [bp - 0xa], ax
00005EB9  8B 46 F6                  mov      ax, word ptr [bp - 0xa]
00005EBC  0B 46 F8                  or       ax, word ptr [bp - 8]
00005EBF  74 72                     je       0x5f33
00005EC1  83 7E 10 00               cmp      word ptr [bp + 0x10], 0
00005EC5  74 14                     je       0x5edb
00005EC7  C4 5E FC                  les      bx, ptr [bp - 4]
00005ECA  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
00005ECE  25 03 00                  and      ax, 3
00005ED1  3D 03 00                  cmp      ax, 3
00005ED4  75 05                     jne      0x5edb
00005ED6  B8 01 00                  mov      ax, 1
00005ED9  EB 02                     jmp      0x5edd
00005EDB  33 C0                     xor      ax, ax
00005EDD  89 46 FA                  mov      word ptr [bp - 6], ax
00005EE0  FF 76 F8                  push     word ptr [bp - 8]
00005EE3  FF 76 F6                  push     word ptr [bp - 0xa]
00005EE6  FF 76 0A                  push     word ptr [bp + 0xa]
00005EE9  FF 76 08                  push     word ptr [bp + 8]
00005EEC  0E                        push     cs
00005EED  E8 57 FE                  call     0x5d47
00005EF0  83 C4 08                  add      sp, 8
00005EF3  0B C0                     or       ax, ax
00005EF5  74 06                     je       0x5efd
00005EF7  83 7E FA 00               cmp      word ptr [bp - 6], 0
00005EFB  75 2A                     jne      0x5f27
00005EFD  C4 5E F6                  les      bx, ptr [bp - 0xa]
00005F00  26 F7 47 08 04 00         test     word ptr es:[bx + 8], 4
00005F06  74 24                     je       0x5f2c
00005F08  FF 76 FA                  push     word ptr [bp - 6]
00005F0B  FF 76 0E                  push     word ptr [bp + 0xe]
00005F0E  FF 76 0C                  push     word ptr [bp + 0xc]
00005F11  FF 76 0A                  push     word ptr [bp + 0xa]
00005F14  FF 76 08                  push     word ptr [bp + 8]
00005F17  FF 76 F8                  push     word ptr [bp - 8]
00005F1A  FF 76 F6                  push     word ptr [bp - 0xa]
00005F1D  E8 C5 FE                  call     0x5de5
00005F20  83 C4 0E                  add      sp, 0xe
00005F23  0B C0                     or       ax, ax
00005F25  74 05                     je       0x5f2c
00005F27  B8 01 00                  mov      ax, 1
00005F2A  EB 09                     jmp      0x5f35
00005F2C  83 46 FC 08               add      word ptr [bp - 4], 8
00005F30  E9 76 FF                  jmp      0x5ea9
00005F33  33 C0                     xor      ax, ax
00005F35  5F                        pop      di
00005F36  5E                        pop      si
00005F37  8B E5                     mov      sp, bp
00005F39  5D                        pop      bp
00005F3A  C3                        ret      
00005F3B  55                        push     bp
00005F3C  8B EC                     mov      bp, sp
00005F3E  83 EC 04                  sub      sp, 4
00005F41  56                        push     si
00005F42  57                        push     di
00005F43  8B 4E 0C                  mov      cx, word ptr [bp + 0xc]
00005F46  8B 56 06                  mov      dx, word ptr [bp + 6]
00005F49  8B 46 04                  mov      ax, word ptr [bp + 4]
00005F4C  3B 56 0A                  cmp      dx, word ptr [bp + 0xa]
00005F4F  75 08                     jne      0x5f59
00005F51  3B 46 08                  cmp      ax, word ptr [bp + 8]
00005F54  75 03                     jne      0x5f59
00005F56  E9 17 01                  jmp      0x6070
00005F59  C4 5E 04                  les      bx, ptr [bp + 4]
00005F5C  26 8B 47 02               mov      ax, word ptr es:[bx + 2]
00005F60  89 46 FE                  mov      word ptr [bp - 2], ax
00005F63  C4 5E 08                  les      bx, ptr [bp + 8]
00005F66  26 8B 47 02               mov      ax, word ptr es:[bx + 2]
00005F6A  89 46 FC                  mov      word ptr [bp - 4], ax
00005F6D  8B 46 FE                  mov      ax, word ptr [bp - 2]
00005F70  23 46 FC                  and      ax, word ptr [bp - 4]
00005F73  A9 10 00                  test     ax, 0x10
00005F76  74 73                     je       0x5feb
00005F78  81 66 FE 00 33            and      word ptr [bp - 2], 0x3300
00005F7D  81 66 FC 00 33            and      word ptr [bp - 4], 0x3300
00005F82  8B 46 FE                  mov      ax, word ptr [bp - 2]
00005F85  3B 46 FC                  cmp      ax, word ptr [bp - 4]
00005F88  75 03                     jne      0x5f8d
00005F8A  E9 A4 00                  jmp      0x6031
00005F8D  0B C9                     or       cx, cx
00005F8F  74 03                     je       0x5f94
00005F91  E9 18 01                  jmp      0x60ac
00005F94  8B 46 FE                  mov      ax, word ptr [bp - 2]
00005F97  25 00 03                  and      ax, 0x300
00005F9A  8B 56 FC                  mov      dx, word ptr [bp - 4]
00005F9D  81 E2 00 03               and      dx, 0x300
00005FA1  3B C2                     cmp      ax, dx
00005FA3  74 25                     je       0x5fca
00005FA5  8B 46 FC                  mov      ax, word ptr [bp - 4]
00005FA8  25 00 03                  and      ax, 0x300
00005FAB  F7 D0                     not      ax
00005FAD  23 46 FE                  and      ax, word ptr [bp - 2]
00005FB0  A9 00 03                  test     ax, 0x300
00005FB3  74 03                     je       0x5fb8
00005FB5  E9 F4 00                  jmp      0x60ac
00005FB8  81 4E FE 00 03            or       word ptr [bp - 2], 0x300
00005FBD  81 4E FC 00 03            or       word ptr [bp - 4], 0x300
00005FC2  8B 46 FE                  mov      ax, word ptr [bp - 2]
00005FC5  3B 46 FC                  cmp      ax, word ptr [bp - 4]
00005FC8  74 67                     je       0x6031
00005FCA  8B 46 FE                  mov      ax, word ptr [bp - 2]
00005FCD  0D 00 30                  or       ax, 0x3000
00005FD0  8B 56 FC                  mov      dx, word ptr [bp - 4]
00005FD3  81 CA 00 30               or       dx, 0x3000
00005FD7  3B C2                     cmp      ax, dx
00005FD9  74 03                     je       0x5fde
00005FDB  E9 CE 00                  jmp      0x60ac
00005FDE  F7 46 FE 00 10            test     word ptr [bp - 2], 0x1000
00005FE3  75 03                     jne      0x5fe8
00005FE5  E9 C4 00                  jmp      0x60ac
00005FE8  E9 85 00                  jmp      0x6070
00005FEB  8B 46 FE                  mov      ax, word ptr [bp - 2]
00005FEE  23 46 FC                  and      ax, word ptr [bp - 4]
00005FF1  A9 00 04                  test     ax, 0x400
00005FF4  74 63                     je       0x6059
00005FF6  C4 5E 04                  les      bx, ptr [bp + 4]
00005FF9  26 8B 57 0C               mov      dx, word ptr es:[bx + 0xc]
00005FFD  26 8B 47 0A               mov      ax, word ptr es:[bx + 0xa]
00006001  C4 5E 08                  les      bx, ptr [bp + 8]
00006004  26 3B 57 0C               cmp      dx, word ptr es:[bx + 0xc]
00006008  75 06                     jne      0x6010
0000600A  26 3B 47 0A               cmp      ax, word ptr es:[bx + 0xa]
0000600E  74 21                     je       0x6031
00006010  0B C9                     or       cx, cx
00006012  74 03                     je       0x6017
00006014  E9 95 00                  jmp      0x60ac
00006017  C4 5E 04                  les      bx, ptr [bp + 4]
0000601A  26 8B 57 0C               mov      dx, word ptr es:[bx + 0xc]
0000601E  26 8B 47 0A               mov      ax, word ptr es:[bx + 0xa]
00006022  C4 5E 08                  les      bx, ptr [bp + 8]
00006025  26 0B 47 0A               or       ax, word ptr es:[bx + 0xa]
00006029  26 0B 57 0C               or       dx, word ptr es:[bx + 0xc]
0000602D  0B C2                     or       ax, dx
0000602F  75 7B                     jne      0x60ac
00006031  B9 01 00                  mov      cx, 1
00006034  C4 5E 04                  les      bx, ptr [bp + 4]
00006037  26 8B 57 08               mov      dx, word ptr es:[bx + 8]
0000603B  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
0000603F  89 56 06                  mov      word ptr [bp + 6], dx
00006042  89 46 04                  mov      word ptr [bp + 4], ax
00006045  C4 5E 08                  les      bx, ptr [bp + 8]
00006048  26 8B 57 08               mov      dx, word ptr es:[bx + 8]
0000604C  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
00006050  89 56 0A                  mov      word ptr [bp + 0xa], dx
00006053  89 46 08                  mov      word ptr [bp + 8], ax
00006056  E9 ED FE                  jmp      0x5f46
00006059  FF 76 0A                  push     word ptr [bp + 0xa]
0000605C  FF 76 08                  push     word ptr [bp + 8]
0000605F  FF 76 06                  push     word ptr [bp + 6]
00006062  FF 76 04                  push     word ptr [bp + 4]
00006065  0E                        push     cs
00006066  E8 DE FC                  call     0x5d47
00006069  83 C4 08                  add      sp, 8
0000606C  0B C0                     or       ax, ax
0000606E  74 05                     je       0x6075
00006070  B8 01 00                  mov      ax, 1
00006073  EB 39                     jmp      0x60ae
00006075  F7 46 FE 02 00            test     word ptr [bp - 2], 2
0000607A  74 30                     je       0x60ac
0000607C  F7 46 FC 01 00            test     word ptr [bp - 4], 1
00006081  74 29                     je       0x60ac
00006083  C4 5E 04                  les      bx, ptr [bp + 4]
00006086  26 F7 47 08 04 00         test     word ptr es:[bx + 8], 4
0000608C  74 1E                     je       0x60ac
0000608E  B8 01 00                  mov      ax, 1
00006091  50                        push     ax
00006092  FF 76 10                  push     word ptr [bp + 0x10]
00006095  FF 76 0E                  push     word ptr [bp + 0xe]
00006098  FF 76 0A                  push     word ptr [bp + 0xa]
0000609B  FF 76 08                  push     word ptr [bp + 8]
0000609E  FF 76 06                  push     word ptr [bp + 6]
000060A1  FF 76 04                  push     word ptr [bp + 4]
000060A4  E8 3E FD                  call     0x5de5
000060A7  83 C4 0E                  add      sp, 0xe
000060AA  EB 02                     jmp      0x60ae
000060AC  33 C0                     xor      ax, ax
000060AE  5F                        pop      di
000060AF  5E                        pop      si
000060B0  8B E5                     mov      sp, bp
000060B2  5D                        pop      bp
000060B3  C3                        ret      
000060B4  55                        push     bp
000060B5  8B EC                     mov      bp, sp
000060B7  83 EC 04                  sub      sp, 4
000060BA  56                        push     si
000060BB  57                        push     di
000060BC  FF 76 06                  push     word ptr [bp + 6]
000060BF  90                        nop      
000060C0  0E                        push     cs
000060C1  E8 8E E6                  call     0x4752
000060C4  59                        pop      cx
000060C5  89 56 FE                  mov      word ptr [bp - 2], dx
000060C8  89 46 FC                  mov      word ptr [bp - 4], ax
000060CB  8B 46 FC                  mov      ax, word ptr [bp - 4]
000060CE  0B 46 FE                  or       ax, word ptr [bp - 2]
000060D1  75 32                     jne      0x6105
000060D3  81 7E 06 80 00            cmp      word ptr [bp + 6], 0x80
000060D8  77 0D                     ja       0x60e7
000060DA  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
000060DF  26 F7 47 04 01 00         test     word ptr es:[bx + 4], 1
000060E5  74 05                     je       0x60ec
000060E7  90                        nop      
000060E8  0E                        push     cs
000060E9  E8 DE EB                  call     0x4cca
000060EC  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
000060F1  26 83 4F 04 01            or       word ptr es:[bx + 4], 1
000060F6  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
000060FB  26 8B 57 22               mov      dx, word ptr es:[bx + 0x22]
000060FF  26 8B 47 20               mov      ax, word ptr es:[bx + 0x20]
00006103  EB 06                     jmp      0x610b
00006105  8B 56 FE                  mov      dx, word ptr [bp - 2]
00006108  8B 46 FC                  mov      ax, word ptr [bp - 4]
0000610B  5F                        pop      di
0000610C  5E                        pop      si
0000610D  8B E5                     mov      sp, bp
0000610F  5D                        pop      bp
00006110  CB                        retf     
00006111  55                        push     bp
00006112  8B EC                     mov      bp, sp
00006114  56                        push     si
00006115  57                        push     di
00006116  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
0000611B  26 8B 57 22               mov      dx, word ptr es:[bx + 0x22]
0000611F  26 8B 47 20               mov      ax, word ptr es:[bx + 0x20]
00006123  3B 56 08                  cmp      dx, word ptr [bp + 8]
00006126  75 11                     jne      0x6139
00006128  3B 46 06                  cmp      ax, word ptr [bp + 6]
0000612B  75 0C                     jne      0x6139
0000612D  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
00006132  26 83 67 04 FE            and      word ptr es:[bx + 4], 0xfffe
00006137  EB 0D                     jmp      0x6146
00006139  FF 76 08                  push     word ptr [bp + 8]
0000613C  FF 76 06                  push     word ptr [bp + 6]
0000613F  90                        nop      
00006140  0E                        push     cs
00006141  E8 04 E5                  call     0x4648
00006144  59                        pop      cx
00006145  59                        pop      cx
00006146  5F                        pop      di
00006147  5E                        pop      si
00006148  5D                        pop      bp
00006149  CB                        retf     
0000614A  55                        push     bp
0000614B  8B EC                     mov      bp, sp
0000614D  83 EC 04                  sub      sp, 4
00006150  56                        push     si
00006151  57                        push     di
00006152  FF 76 0A                  push     word ptr [bp + 0xa]
00006155  FF 76 08                  push     word ptr [bp + 8]
00006158  33 C0                     xor      ax, ax
0000615A  50                        push     ax
0000615B  FF 76 0E                  push     word ptr [bp + 0xe]
0000615E  FF 76 0C                  push     word ptr [bp + 0xc]
00006161  FF 76 06                  push     word ptr [bp + 6]
00006164  FF 76 04                  push     word ptr [bp + 4]
00006167  E8 D1 FD                  call     0x5f3b
0000616A  83 C4 0E                  add      sp, 0xe
0000616D  0B C0                     or       ax, ax
0000616F  74 03                     je       0x6174
00006171  E9 A0 00                  jmp      0x6214
00006174  C4 5E 04                  les      bx, ptr [bp + 4]
00006177  26 8B 47 02               mov      ax, word ptr es:[bx + 2]
0000617B  89 46 FE                  mov      word ptr [bp - 2], ax
0000617E  C4 5E 0C                  les      bx, ptr [bp + 0xc]
00006181  26 8B 47 02               mov      ax, word ptr es:[bx + 2]
00006185  89 46 FC                  mov      word ptr [bp - 4], ax
00006188  F7 46 FC 20 00            test     word ptr [bp - 4], 0x20
0000618D  74 77                     je       0x6206
0000618F  FF 76 0A                  push     word ptr [bp + 0xa]
00006192  FF 76 08                  push     word ptr [bp + 8]
00006195  B8 01 00                  mov      ax, 1
00006198  50                        push     ax
00006199  C4 5E 0C                  les      bx, ptr [bp + 0xc]
0000619C  26 FF 77 08               push     word ptr es:[bx + 8]
000061A0  26 FF 77 06               push     word ptr es:[bx + 6]
000061A4  FF 76 06                  push     word ptr [bp + 6]
000061A7  FF 76 04                  push     word ptr [bp + 4]
000061AA  E8 8E FD                  call     0x5f3b
000061AD  83 C4 0E                  add      sp, 0xe
000061B0  0B C0                     or       ax, ax
000061B2  75 60                     jne      0x6214
000061B4  C4 5E 0C                  les      bx, ptr [bp + 0xc]
000061B7  26 8B 57 08               mov      dx, word ptr es:[bx + 8]
000061BB  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
000061BF  89 56 0E                  mov      word ptr [bp + 0xe], dx
000061C2  89 46 0C                  mov      word ptr [bp + 0xc], ax
000061C5  C4 5E 0C                  les      bx, ptr [bp + 0xc]
000061C8  26 8B 47 02               mov      ax, word ptr es:[bx + 2]
000061CC  89 46 FC                  mov      word ptr [bp - 4], ax
000061CF  F7 46 FC 10 00            test     word ptr [bp - 4], 0x10
000061D4  74 79                     je       0x624f
000061D6  FF 76 0A                  push     word ptr [bp + 0xa]
000061D9  FF 76 08                  push     word ptr [bp + 8]
000061DC  33 C0                     xor      ax, ax
000061DE  50                        push     ax
000061DF  FF 76 0E                  push     word ptr [bp + 0xe]
000061E2  FF 76 0C                  push     word ptr [bp + 0xc]
000061E5  FF 76 06                  push     word ptr [bp + 6]
000061E8  FF 76 04                  push     word ptr [bp + 4]
000061EB  E8 4D FD                  call     0x5f3b
000061EE  83 C4 0E                  add      sp, 0xe
000061F1  0B C0                     or       ax, ax
000061F3  75 1F                     jne      0x6214
000061F5  8B 46 FE                  mov      ax, word ptr [bp - 2]
000061F8  25 00 30                  and      ax, 0x3000
000061FB  8B 56 FC                  mov      dx, word ptr [bp - 4]
000061FE  81 E2 00 30               and      dx, 0x3000
00006202  3B C2                     cmp      ax, dx
00006204  75 49                     jne      0x624f
00006206  F7 46 FC 10 00            test     word ptr [bp - 4], 0x10
0000620B  74 42                     je       0x624f
0000620D  F7 46 10 01 00            test     word ptr [bp + 0x10], 1
00006212  74 05                     je       0x6219
00006214  B8 01 00                  mov      ax, 1
00006217  EB 38                     jmp      0x6251
00006219  F7 46 FE 10 00            test     word ptr [bp - 2], 0x10
0000621E  74 2F                     je       0x624f
00006220  F7 46 FE 00 20            test     word ptr [bp - 2], 0x2000
00006225  74 07                     je       0x622e
00006227  F7 46 FC 00 20            test     word ptr [bp - 4], 0x2000
0000622C  74 21                     je       0x624f
0000622E  F7 46 FC 40 00            test     word ptr [bp - 4], 0x40
00006233  74 1A                     je       0x624f
00006235  8B 46 FE                  mov      ax, word ptr [bp - 2]
00006238  25 00 03                  and      ax, 0x300
0000623B  8B 56 FC                  mov      dx, word ptr [bp - 4]
0000623E  81 E2 00 03               and      dx, 0x300
00006242  3B C2                     cmp      ax, dx
00006244  75 05                     jne      0x624b
00006246  B8 01 00                  mov      ax, 1
00006249  EB 02                     jmp      0x624d
0000624B  33 C0                     xor      ax, ax
0000624D  EB 02                     jmp      0x6251
0000624F  33 C0                     xor      ax, ax
00006251  5F                        pop      di
00006252  5E                        pop      si
00006253  8B E5                     mov      sp, bp
00006255  5D                        pop      bp
00006256  C3                        ret      
00006257  55                        push     bp
00006258  8B EC                     mov      bp, sp
0000625A  83 EC 04                  sub      sp, 4
0000625D  56                        push     si
0000625E  57                        push     di
0000625F  36 C4 1E 16 00            les      bx, ptr ss:[0x16]
00006264  26 8B 47 06               mov      ax, word ptr es:[bx + 6]
00006268  89 46 FE                  mov      word ptr [bp - 2], ax
0000626B  1E                        push     ds
0000626C  8E 5E FE                  mov      ds, word ptr [bp - 2]
0000626F  8B 46 10                  mov      ax, word ptr [bp + 0x10]
00006272  25 01 00                  and      ax, 1
00006275  89 46 FC                  mov      word ptr [bp - 4], ax
00006278  F7 46 10 04 00            test     word ptr [bp + 0x10], 4
0000627D  74 04                     je       0x6283
0000627F  83 4E FC 02               or       word ptr [bp - 4], 2
00006283  F7 46 10 02 00            test     word ptr [bp + 0x10], 2
00006288  74 0F                     je       0x6299
0000628A  83 4E FC 04               or       word ptr [bp - 4], 4
0000628E  F7 46 10 00 01            test     word ptr [bp + 0x10], 0x100
00006293  75 04                     jne      0x6299
00006295  83 4E FC 20               or       word ptr [bp - 4], 0x20
00006299  F7 46 10 20 00            test     word ptr [bp + 0x10], 0x20
0000629E  74 04                     je       0x62a4
000062A0  83 4E FC 08               or       word ptr [bp - 4], 8
000062A4  F7 46 10 80 00            test     word ptr [bp + 0x10], 0x80
000062A9  74 04                     je       0x62af
000062AB  83 4E FC 10               or       word ptr [bp - 4], 0x10
000062AF  F7 46 10 00 10            test     word ptr [bp + 0x10], 0x1000
000062B4  75 03                     jne      0x62b9
000062B6  E9 85 01                  jmp      0x643e
000062B9  8B 5E FC                  mov      bx, word ptr [bp - 4]
000062BC  83 FB 17                  cmp      bx, 0x17
000062BF  76 03                     jbe      0x62c4
000062C1  E9 80 02                  jmp      0x6544
000062C4  03 DB                     add      bx, bx
000062C6  2E FF A7 7B 65            jmp      word ptr cs:[bx + 0x657b]
000062CB  FF 76 08                  push     word ptr [bp + 8]
000062CE  33 C0                     xor      ax, ax
000062D0  50                        push     ax
000062D1  FF 76 04                  push     word ptr [bp + 4]
000062D4  FF 56 0C                  call     word ptr [bp + 0xc]
000062D7  83 C4 06                  add      sp, 6
000062DA  E9 67 02                  jmp      0x6544
000062DD  FF 76 08                  push     word ptr [bp + 8]
000062E0  33 C0                     xor      ax, ax
000062E2  50                        push     ax
000062E3  FF 76 04                  push     word ptr [bp + 4]
000062E6  FF 5E 0C                  lcall    [bp + 0xc]
000062E9  83 C4 06                  add      sp, 6
000062EC  E9 55 02                  jmp      0x6544
000062EF  FF 76 0A                  push     word ptr [bp + 0xa]
000062F2  FF 76 08                  push     word ptr [bp + 8]
000062F5  33 C0                     xor      ax, ax
000062F7  50                        push     ax
000062F8  FF 76 06                  push     word ptr [bp + 6]
000062FB  FF 76 04                  push     word ptr [bp + 4]
000062FE  FF 56 0C                  call     word ptr [bp + 0xc]
00006301  EB 12                     jmp      0x6315
00006303  FF 76 0A                  push     word ptr [bp + 0xa]
00006306  FF 76 08                  push     word ptr [bp + 8]
00006309  33 C0                     xor      ax, ax
0000630B  50                        push     ax
0000630C  FF 76 06                  push     word ptr [bp + 6]
0000630F  FF 76 04                  push     word ptr [bp + 4]
00006312  FF 5E 0C                  lcall    [bp + 0xc]
00006315  83 C4 0A                  add      sp, 0xa
00006318  E9 29 02                  jmp      0x6544
0000631B  33 C0                     xor      ax, ax
0000631D  50                        push     ax
0000631E  FF 76 08                  push     word ptr [bp + 8]
00006321  FF 76 04                  push     word ptr [bp + 4]
00006324  FF 56 0C                  call     word ptr [bp + 0xc]
00006327  E9 1A 02                  jmp      0x6544
0000632A  33 C0                     xor      ax, ax
0000632C  50                        push     ax
0000632D  FF 76 08                  push     word ptr [bp + 8]
00006330  FF 76 04                  push     word ptr [bp + 4]
00006333  FF 5E 0C                  lcall    [bp + 0xc]
00006336  E9 0B 02                  jmp      0x6544
00006339  33 C0                     xor      ax, ax
0000633B  50                        push     ax
0000633C  FF 76 0A                  push     word ptr [bp + 0xa]
0000633F  FF 76 08                  push     word ptr [bp + 8]
00006342  FF 76 06                  push     word ptr [bp + 6]
00006345  FF 76 04                  push     word ptr [bp + 4]
00006348  FF 56 0C                  call     word ptr [bp + 0xc]
0000634B  EB 12                     jmp      0x635f
0000634D  33 C0                     xor      ax, ax
0000634F  50                        push     ax
00006350  FF 76 0A                  push     word ptr [bp + 0xa]
00006353  FF 76 08                  push     word ptr [bp + 8]
00006356  FF 76 06                  push     word ptr [bp + 6]
00006359  FF 76 04                  push     word ptr [bp + 4]
0000635C  FF 5E 0C                  lcall    [bp + 0xc]
0000635F  E9 E2 01                  jmp      0x6544
00006362  8B 56 04                  mov      dx, word ptr [bp + 4]
00006365  8B 5E 08                  mov      bx, word ptr [bp + 8]
00006368  33 C0                     xor      ax, ax
0000636A  53                        push     bx
0000636B  5B                        pop      bx
0000636C  FF 56 0C                  call     word ptr [bp + 0xc]
0000636F  E9 D2 01                  jmp      0x6544
00006372  8B 56 04                  mov      dx, word ptr [bp + 4]
00006375  8B 5E 08                  mov      bx, word ptr [bp + 8]
00006378  33 C0                     xor      ax, ax
0000637A  53                        push     bx
0000637B  5B                        pop      bx
0000637C  FF 5E 0C                  lcall    [bp + 0xc]
0000637F  E9 C2 01                  jmp      0x6544
00006382  FF 76 0A                  push     word ptr [bp + 0xa]
00006385  FF 76 08                  push     word ptr [bp + 8]
00006388  FF 76 06                  push     word ptr [bp + 6]
0000638B  FF 76 04                  push     word ptr [bp + 4]
0000638E  33 C0                     xor      ax, ax
00006390  FF 56 0C                  call     word ptr [bp + 0xc]
00006393  EB 11                     jmp      0x63a6
00006395  FF 76 0A                  push     word ptr [bp + 0xa]
00006398  FF 76 08                  push     word ptr [bp + 8]
0000639B  FF 76 06                  push     word ptr [bp + 6]
0000639E  FF 76 04                  push     word ptr [bp + 4]
000063A1  33 C0                     xor      ax, ax
000063A3  FF 5E 0C                  lcall    [bp + 0xc]
000063A6  E9 9B 01                  jmp      0x6544
000063A9  8B 76 04                  mov      si, word ptr [bp + 4]
000063AC  FF 76 08                  push     word ptr [bp + 8]
000063AF  33 C0                     xor      ax, ax
000063B1  50                        push     ax
000063B2  FF 56 0C                  call     word ptr [bp + 0xc]
000063B5  EB 0C                     jmp      0x63c3
000063B7  8B 76 04                  mov      si, word ptr [bp + 4]
000063BA  FF 76 08                  push     word ptr [bp + 8]
000063BD  33 C0                     xor      ax, ax
000063BF  50                        push     ax
000063C0  FF 5E 0C                  lcall    [bp + 0xc]
000063C3  59                        pop      cx
000063C4  59                        pop      cx
000063C5  E9 7C 01                  jmp      0x6544
000063C8  1E                        push     ds
000063C9  C5 76 04                  lds      si, ptr [bp + 4]
000063CC  FF 76 0A                  push     word ptr [bp + 0xa]
000063CF  FF 76 08                  push     word ptr [bp + 8]
000063D2  33 C0                     xor      ax, ax
000063D4  50                        push     ax
000063D5  FF 56 0C                  call     word ptr [bp + 0xc]
000063D8  83 C4 06                  add      sp, 6
000063DB  1F                        pop      ds
000063DC  E9 65 01                  jmp      0x6544
000063DF  1E                        push     ds
000063E0  C5 76 04                  lds      si, ptr [bp + 4]
000063E3  FF 76 0A                  push     word ptr [bp + 0xa]
000063E6  FF 76 08                  push     word ptr [bp + 8]
000063E9  33 C0                     xor      ax, ax
000063EB  50                        push     ax
000063EC  FF 5E 0C                  lcall    [bp + 0xc]
000063EF  83 C4 06                  add      sp, 6
000063F2  1F                        pop      ds
000063F3  E9 4E 01                  jmp      0x6544
000063F6  8B 76 04                  mov      si, word ptr [bp + 4]
000063F9  33 C0                     xor      ax, ax
000063FB  50                        push     ax
000063FC  FF 76 08                  push     word ptr [bp + 8]
000063FF  FF 56 0C                  call     word ptr [bp + 0xc]
00006402  EB 0C                     jmp      0x6410
00006404  8B 76 04                  mov      si, word ptr [bp + 4]
00006407  33 C0                     xor      ax, ax
00006409  50                        push     ax
0000640A  FF 76 08                  push     word ptr [bp + 8]
0000640D  FF 5E 0C                  lcall    [bp + 0xc]
00006410  E9 31 01                  jmp      0x6544
00006413  1E                        push     ds
00006414  C5 76 04                  lds      si, ptr [bp + 4]
00006417  33 C0                     xor      ax, ax
00006419  50                        push     ax
0000641A  FF 76 0A                  push     word ptr [bp + 0xa]
0000641D  FF 76 08                  push     word ptr [bp + 8]
00006420  FF 56 0C                  call     word ptr [bp + 0xc]
00006423  1F                        pop      ds
00006424  E9 1D 01                  jmp      0x6544
00006427  1E                        push     ds
00006428  C5 76 04                  lds      si, ptr [bp + 4]
0000642B  33 C0                     xor      ax, ax
0000642D  50                        push     ax
0000642E  FF 76 0A                  push     word ptr [bp + 0xa]
00006431  FF 76 08                  push     word ptr [bp + 8]
00006434  FF 5E 0C                  lcall    [bp + 0xc]
00006437  1F                        pop      ds
00006438  E9 09 01                  jmp      0x6544
0000643B  E9 06 01                  jmp      0x6544
0000643E  8B 5E FC                  mov      bx, word ptr [bp - 4]
00006441  83 FB 17                  cmp      bx, 0x17
00006444  76 03                     jbe      0x6449
00006446  E9 FB 00                  jmp      0x6544
00006449  03 DB                     add      bx, bx
0000644B  2E FF A7 4B 65            jmp      word ptr cs:[bx + 0x654b]
00006450  FF 76 08                  push     word ptr [bp + 8]
00006453  FF 76 04                  push     word ptr [bp + 4]
00006456  FF 56 0C                  call     word ptr [bp + 0xc]
00006459  E9 67 FF                  jmp      0x63c3
0000645C  FF 76 08                  push     word ptr [bp + 8]
0000645F  FF 76 04                  push     word ptr [bp + 4]
00006462  E9 5B FF                  jmp      0x63c0
00006465  FF 76 0A                  push     word ptr [bp + 0xa]
00006468  FF 76 08                  push     word ptr [bp + 8]
0000646B  FF 76 06                  push     word ptr [bp + 6]
0000646E  FF 76 04                  push     word ptr [bp + 4]
00006471  FF 56 0C                  call     word ptr [bp + 0xc]
00006474  EB 0F                     jmp      0x6485
00006476  FF 76 0A                  push     word ptr [bp + 0xa]
00006479  FF 76 08                  push     word ptr [bp + 8]
0000647C  FF 76 06                  push     word ptr [bp + 6]
0000647F  FF 76 04                  push     word ptr [bp + 4]
00006482  FF 5E 0C                  lcall    [bp + 0xc]
00006485  83 C4 08                  add      sp, 8
00006488  E9 B9 00                  jmp      0x6544
0000648B  FF 76 08                  push     word ptr [bp + 8]
0000648E  FF 76 04                  push     word ptr [bp + 4]
00006491  E9 6B FF                  jmp      0x63ff
00006494  FF 76 08                  push     word ptr [bp + 8]
00006497  FF 76 04                  push     word ptr [bp + 4]
0000649A  E9 70 FF                  jmp      0x640d
0000649D  8B 46 04                  mov      ax, word ptr [bp + 4]
000064A0  8B 5E 08                  mov      bx, word ptr [bp + 8]
000064A3  53                        push     bx
000064A4  5B                        pop      bx
000064A5  FF 56 0C                  call     word ptr [bp + 0xc]
000064A8  E9 99 00                  jmp      0x6544
000064AB  8B 46 04                  mov      ax, word ptr [bp + 4]
000064AE  8B 5E 08                  mov      bx, word ptr [bp + 8]
000064B1  E9 C6 FE                  jmp      0x637a
000064B4  FF 76 0A                  push     word ptr [bp + 0xa]
000064B7  FF 76 08                  push     word ptr [bp + 8]
000064BA  FF 76 06                  push     word ptr [bp + 6]
000064BD  FF 76 04                  push     word ptr [bp + 4]
000064C0  E9 CD FE                  jmp      0x6390
000064C3  FF 76 0A                  push     word ptr [bp + 0xa]
000064C6  FF 76 08                  push     word ptr [bp + 8]
000064C9  FF 76 06                  push     word ptr [bp + 6]
000064CC  FF 76 04                  push     word ptr [bp + 4]
000064CF  E9 D1 FE                  jmp      0x63a3
000064D2  8B 76 04                  mov      si, word ptr [bp + 4]
000064D5  FF 76 08                  push     word ptr [bp + 8]
000064D8  FF 56 0C                  call     word ptr [bp + 0xc]
000064DB  59                        pop      cx
000064DC  EB 66                     jmp      0x6544
000064DE  8B 76 04                  mov      si, word ptr [bp + 4]
000064E1  FF 76 08                  push     word ptr [bp + 8]
000064E4  FF 5E 0C                  lcall    [bp + 0xc]
000064E7  59                        pop      cx
000064E8  EB 5A                     jmp      0x6544
000064EA  1E                        push     ds
000064EB  C5 76 04                  lds      si, ptr [bp + 4]
000064EE  FF 76 0A                  push     word ptr [bp + 0xa]
000064F1  FF 76 08                  push     word ptr [bp + 8]
000064F4  FF 56 0C                  call     word ptr [bp + 0xc]
000064F7  59                        pop      cx
000064F8  59                        pop      cx
000064F9  1F                        pop      ds
000064FA  EB 48                     jmp      0x6544
000064FC  1E                        push     ds
000064FD  C5 76 04                  lds      si, ptr [bp + 4]
00006500  FF 76 0A                  push     word ptr [bp + 0xa]
00006503  FF 76 08                  push     word ptr [bp + 8]
00006506  FF 5E 0C                  lcall    [bp + 0xc]
00006509  59                        pop      cx
0000650A  59                        pop      cx
0000650B  1F                        pop      ds
0000650C  EB 36                     jmp      0x6544
0000650E  8B 76 04                  mov      si, word ptr [bp + 4]
00006511  FF 76 08                  push     word ptr [bp + 8]
00006514  FF 56 0C                  call     word ptr [bp + 0xc]
00006517  EB 2B                     jmp      0x6544
00006519  8B 76 04                  mov      si, word ptr [bp + 4]
0000651C  FF 76 08                  push     word ptr [bp + 8]
0000651F  FF 5E 0C                  lcall    [bp + 0xc]
00006522  EB 20                     jmp      0x6544
00006524  1E                        push     ds
00006525  C5 76 04                  lds      si, ptr [bp + 4]
00006528  FF 76 0A                  push     word ptr [bp + 0xa]
0000652B  FF 76 08                  push     word ptr [bp + 8]
0000652E  FF 56 0C                  call     word ptr [bp + 0xc]
00006531  1F                        pop      ds
00006532  EB 10                     jmp      0x6544
00006534  1E                        push     ds
00006535  C5 76 04                  lds      si, ptr [bp + 4]
00006538  FF 76 0A                  push     word ptr [bp + 0xa]
0000653B  FF 76 08                  push     word ptr [bp + 8]
0000653E  FF 5E 0C                  lcall    [bp + 0xc]
00006541  1F                        pop      ds
00006542  EB 00                     jmp      0x6544
00006544  1F                        pop      ds
00006545  5F                        pop      di
00006546  5E                        pop      si
00006547  8B E5                     mov      sp, bp
00006549  5D                        pop      bp
0000654A  C3                        ret      
0000654B  50                        push     ax
0000654C  64 5C                     pop      sp
0000654E  64 65 64 76 64            jbe      0x65b7
00006553  8B 64 94                  mov      sp, word ptr [si - 0x6c]
00006556  64 B4 64                  mov      ah, 0x64
00006559  C3                        ret      
0000655A  64 9D                     popf     
0000655C  64 AB                     stosw    word ptr es:[di], ax
0000655E  64 B4 64                  mov      ah, 0x64
00006561  C3                        ret      
00006562  64 44                     inc      sp
00006564  65 44                     inc      sp
00006566  65 44                     inc      sp
00006568  65 44                     inc      sp
0000656A  65 D2 64 DE               shl      byte ptr gs:[si - 0x22], cl
0000656E  64 EA 64 FC 64 0E         ljmp     0xe64:0xfc64
00006574  65 19 65 24               sbb      word ptr gs:[di + 0x24], sp
00006578  65 34 65                  xor      al, 0x65
0000657B  CB                        retf     
