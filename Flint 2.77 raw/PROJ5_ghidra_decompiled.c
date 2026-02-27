// Function: entry

/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */
/* WARNING: This function may have set the stack pointer */

void entry(void)

{
  char *pcVar1;
  undefined2 *puVar2;
  code *pcVar3;
  undefined2 uVar4;
  byte bVar5;
  uint uVar6;
  int iVar7;
  undefined2 uVar8;
  int extraout_DX;
  int iVar9;
  undefined2 extraout_DX_00;
  int iVar10;
  undefined *puVar11;
  int *piVar12;
  char *pcVar13;
  undefined *puVar14;
  undefined2 *puVar15;
  undefined2 unaff_ES;
  bool bVar16;
  undefined4 uVar17;
  
  puVar11 = (undefined *)0x80;
  DAT_1000_026d = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  pcVar3 = (code *)swi(0x21);
  uVar17 = (*pcVar3)();
  uVar4 = s_Borland_C_____Copyright_1994_Bor_28d3_0020._12_2_;
  iVar7 = DAT_28d3_0002;
  uVar8 = (undefined2)((ulong)uVar17 >> 0x10);
  *(undefined2 *)&DAT_28d3_007c = (int)uVar17;
  *(undefined2 *)&DAT_28d3_007a = unaff_ES;
  *(undefined2 *)&DAT_28d3_0076 = uVar4;
  *(int *)&DAT_28d3_008e = iVar7;
  *(undefined2 *)(puVar11 + -2) = 0x28;
  FUN_1000_0178();
  iVar10 = 0;
  pcVar13 = (char *)0x0;
  uVar6 = 0x7fff;
LAB_1000_0037:
  do {
    if (uVar6 != 0) {
      uVar6 = uVar6 - 1;
      pcVar1 = pcVar13;
      pcVar13 = pcVar13 + 1;
      if (*pcVar1 != '\0') goto LAB_1000_0037;
    }
    iVar9 = extraout_DX;
    if (uVar6 == 0) goto code_r0x0001007f;
    iVar10 = iVar10 + 1;
  } while (*pcVar13 != '\0');
  *(int *)&DAT_28d3_0074 = -(uVar6 | 0x8000);
  *(uint *)&DAT_28d3_0078 = iVar10 * 4 + 0x10U & 0xfff0;
  iVar9 = 0x2e60;
  if (DAT_28d3_26f4 < 0x200) {
    DAT_28d3_26f4 = (undefined *)0x200;
  }
  uVar6 = 4;
  bVar5 = 4;
  pcVar13 = (char *)(((uint)DAT_28d3_26f4 >> 4) + 1);
  if ((char *)(iVar7 + -0x2e60) < pcVar13) {
code_r0x0001007f:
    bVar5 = (byte)uVar6;
    *(undefined2 *)(puVar11 + -2) = 0x1000;
    *(undefined2 *)(puVar11 + -4) = 0x83;
    FUN_1000_4db9();
  }
  *(char **)&DAT_28d3_0086 = pcVar13 + iVar9;
  *(char **)&DAT_28d3_008a = pcVar13 + iVar9;
  piVar12 = (int *)(puVar11 + -2);
  *(char **)(puVar11 + -2) = pcVar13;
  pcVar3 = (code *)swi(0x21);
  (*pcVar3)();
  pcVar13 = DAT_1000_026d;
  puVar14 = (undefined *)(*piVar12 << (bVar5 & 0x1f));
  puVar15 = (undefined2 *)&DAT_28d3_2960;
  DAT_28d3_26f4 = puVar14;
  for (iVar7 = 0x2f6a; iVar7 != 0; iVar7 = iVar7 + -1) {
    puVar2 = puVar15;
    puVar15 = (undefined2 *)((int)puVar15 + 1);
    *(undefined *)puVar2 = 0;
  }
  if (0x14 < *(uint *)&DAT_28d3_2174) {
    bVar16 = *(byte *)&DAT_28d3_007c < 3;
    if ((!bVar16) &&
       ((3 < *(byte *)&DAT_28d3_007c || (bVar16 = *(byte *)&DAT_28d3_007d < 0x1e, !bVar16)))) {
      pcVar3 = (code *)swi(0x21);
      (*pcVar3)();
      if (!bVar16) {
        pcVar3 = (code *)swi(0x21);
        (*pcVar3)();
        if (!bVar16) {
          pcVar3 = (code *)swi(0x21);
          iVar7 = (*pcVar3)();
          if (!bVar16) {
            *(int *)&DAT_28d3_008e = iVar7 + 1;
            pcVar3 = (code *)swi(0x21);
            (*pcVar3)();
            if (!bVar16) {
              pcVar3 = (code *)swi(0x21);
              (*pcVar3)();
              if (!bVar16) goto LAB_1000_0110;
            }
          }
        }
      }
      *(undefined2 *)(puVar14 + -2) = 0x1000;
      *(undefined2 *)(puVar14 + -4) = 0x110;
      FUN_1000_4db9();
    }
  }
LAB_1000_0110:
  *(undefined2 *)(puVar14 + -2) = 0;
  *(undefined2 *)(puVar14 + -4) = 0x1000;
  *(undefined2 *)(puVar14 + -6) = 0x118;
  FUN_1000_565b();
  *(undefined2 *)(puVar14 + -2) = 0x127;
  FUN_1000_01e8();
  *(undefined2 *)(puVar14 + -2) = *(undefined2 *)&DAT_28d3_0072;
  *(undefined2 *)(puVar14 + -4) = *(undefined2 *)&DAT_28d3_0070;
  *(undefined2 *)(puVar14 + -6) = *(undefined2 *)&DAT_28d3_006e;
  *(undefined2 *)(puVar14 + -8) = *(undefined2 *)&DAT_28d3_006c;
  *(undefined2 *)(puVar14 + -10) = *(undefined2 *)&DAT_28d3_006a;
  *(undefined2 *)(puVar14 + -0xc) = 0x1000;
  *(undefined2 *)(puVar14 + -0xe) = 0x140;
  uVar4 = FUN_1928_000e();
  *(undefined2 *)(puVar14 + -0xc) = uVar4;
  *(undefined2 *)(puVar14 + -0xe) = 0x1928;
  *(undefined2 *)(puVar14 + -0x10) = 0x146;
  FUN_1000_4d6e();
  *(undefined2 *)(puVar14 + -0xe) = 0x2918;
  *(undefined2 *)(puVar14 + -0x10) = 0x2948;
  *(undefined2 *)(puVar14 + -0x12) = 0x156;
  FUN_1000_022c();
  return;
}



// Function: FUN_1000_0146

void __cdecl16far FUN_1000_0146(void)

{
  FUN_1000_022c();
  return;
}



// Function: FUN_1000_0159

void __cdecl16far FUN_1000_0159(void)

{
  return;
}



// Function: FUN_1000_015a

void FUN_1000_015a(void)

{
  code *pcVar1;
  undefined2 in_BX;
  undefined2 unaff_ES;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  FUN_1000_4bcf();
  FUN_1000_4d81();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  DAT_28d3_005a._0_2_ = in_BX;
  DAT_28d3_005a._2_2_ = unaff_ES;
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  DAT_28d3_005e = in_BX;
  DAT_28d3_0060 = unaff_ES;
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  DAT_28d3_0062 = in_BX;
  DAT_28d3_0064 = unaff_ES;
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  DAT_28d3_0066 = in_BX;
  DAT_28d3_0068 = unaff_ES;
  (*pcVar1)();
  return;
}



// Function: FUN_1000_0178

void __cdecl16near FUN_1000_0178(void)

{
  code *pcVar1;
  undefined2 in_BX;
  undefined2 unaff_ES;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  DAT_28d3_005a._0_2_ = in_BX;
  DAT_28d3_005a._2_2_ = unaff_ES;
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  DAT_28d3_005e = in_BX;
  DAT_28d3_0060 = unaff_ES;
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  DAT_28d3_0062 = in_BX;
  DAT_28d3_0064 = unaff_ES;
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  DAT_28d3_0066 = in_BX;
  DAT_28d3_0068 = unaff_ES;
  (*pcVar1)();
  return;
}



// Function: FUN_1000_01bb

void __cdecl16far FUN_1000_01bb(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



// Function: FUN_1000_01e8

void __cdecl16near FUN_1000_01e8(void)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  char *pcVar4;
  char *unaff_SI;
  char *unaff_DI;
  undefined2 unaff_ES;
  
  while( true ) {
    uVar2 = 0x100;
    pcVar3 = unaff_DI;
    for (pcVar4 = unaff_SI; pcVar4 != unaff_DI; pcVar4 = pcVar4 + 6) {
      if ((*pcVar4 != -1) && ((byte)pcVar4[1] < uVar2)) {
        uVar2 = (uint)(byte)pcVar4[1];
        pcVar3 = pcVar4;
      }
    }
    if (pcVar3 == unaff_DI) break;
    cVar1 = *pcVar3;
    *pcVar3 = -1;
    if (cVar1 == '\0') {
      (**(code **)(pcVar3 + 2))();
    }
    else {
      (**(code **)(pcVar3 + 2))(0x1000);
    }
  }
  return;
}



// Function: FUN_1000_022c

void __cdecl16near FUN_1000_022c(void)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  char *pcVar4;
  char *unaff_SI;
  char *unaff_DI;
  undefined2 unaff_ES;
  
  while( true ) {
    bVar2 = 0;
    pcVar3 = unaff_DI;
    for (pcVar4 = unaff_SI; pcVar4 != unaff_DI; pcVar4 = pcVar4 + 6) {
      if ((*pcVar4 != -1) && (bVar2 <= (byte)pcVar4[1])) {
        bVar2 = pcVar4[1];
        pcVar3 = pcVar4;
      }
    }
    if (pcVar3 == unaff_DI) break;
    cVar1 = *pcVar3;
    *pcVar3 = -1;
    if (cVar1 == '\0') {
      (**(code **)(pcVar3 + 2))();
    }
    else {
      (**(code **)(pcVar3 + 2))(0x1000);
    }
  }
  return;
}



// Function: FUN_1000_0492

void __cdecl16far FUN_1000_0492(undefined2 param_1,undefined2 param_2)

{
  FUN_1000_0575(param_1,param_2,0,0);
  return;
}



// Function: FUN_1000_04ab

undefined2 __cdecl16far FUN_1000_04ab(void)

{
  byte bVar1;
  undefined2 unaff_SS;
  undefined2 param_2;
  undefined2 param_3;
  undefined2 param_4;
  
  bVar1 = (byte)((uint)&stack0x0004 >> 8);
  thunk_FUN_1000_068f(6,(uint)bVar1 << 8,CONCAT11(bVar1,0x67),param_3,param_4,param_2,&stack0x0004,
                      unaff_SS);
  return param_3;
}



// Function: FUN_1000_04d3

int __cdecl16near FUN_1000_04d3(char **param_1)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  
  pcVar1 = ((char **)param_1)[1];
  pcVar2 = *param_1;
  *param_1 = *param_1 + 1;
  iVar3 = (int)*pcVar2;
  if (iVar3 == 0) {
    iVar3 = -1;
  }
  return iVar3;
}



// Function: FUN_1000_04fc

void __cdecl16near FUN_1000_04fc(undefined2 param_1_00,int *param_1)

{
  *param_1 = *param_1 + -1;
  return;
}



// Function: FUN_1000_0507

void __cdecl16far FUN_1000_0507(undefined2 param_1,undefined2 param_2,undefined2 *param_3)

{
  int local_6;
  
  thunk_FUN_1000_083f(0x4d3,0x4fc,&param_1);
  if ((0 < local_6) && (local_6 == 2)) {
    DAT_28d3_007e = 0x22;
  }
  if (((uint)(undefined2 *)param_3 | param_3._2_2_) != 0) {
    ((undefined2 *)param_3)[1] = param_2;
    *param_3 = param_1;
  }
  return;
}



// Function: FUN_1000_0575

void __cdecl16far FUN_1000_0575(void)

{
  unkbyte10 in_ST0;
  undefined2 uVar1;
  
  uVar1 = 1;
  FUN_1000_0507();
  FUN_1000_05ab(DAT_28d3_1c06,in_ST0,uVar1);
  return;
}



// Function: FUN_1000_05ab

void FUN_1000_05ab(void)

{
  uint uVar1;
  uint uVar2;
  uint param_2;
  uint in_stack_0000000c;
  uint in_stack_0000000e;
  uint in_stack_00000010;
  uint in_stack_00000012;
  int param_3;
  
  uVar1 = 0x43fe;
  uVar2 = 0x3bcd;
  if (param_3 == 0) {
    uVar1 = 0x407e;
    uVar2 = 0x3f6a;
  }
  in_stack_00000012 = in_stack_00000012 & 0x7fff;
  if (in_stack_00000012 != 0x7fff) {
    if (in_stack_00000012 == uVar1) {
      return;
    }
    if ((uVar1 < in_stack_00000012) ||
       (((in_stack_00000012 | in_stack_00000010 | in_stack_0000000e | in_stack_0000000c | param_2)
         != 0 && (in_stack_00000012 < uVar2)))) {
      DAT_28d3_007e = 0x22;
      return;
    }
  }
  return;
}



// Function: FUN_1000_066b

void __cdecl16near FUN_1000_066b(void)

{
  uint in_CX;
  byte in_DL;
  uint in_BX;
  undefined2 unaff_ES;
  
  if ((in_DL & 0x5f) == 0x47) {
    do {
      if (*(char *)(in_BX - 1) != '0') {
        return;
      }
      in_BX = in_BX - 1;
    } while (in_CX < in_BX);
  }
  return;
}



// Function: FUN_1000_068f

void FUN_1000_068f(undefined2 param_1,char param_2,byte param_3,int *param_4,uint param_5)

{
  undefined2 *puVar1;
  byte *pbVar2;
  int *piVar3;
  ulong uVar4;
  int iVar5;
  uint uVar6;
  byte bVar7;
  int iVar8;
  int *piVar9;
  undefined2 *puVar10;
  byte *pbVar11;
  int *piVar12;
  int *piVar13;
  undefined2 uVar14;
  undefined2 unaff_SS;
  undefined2 local_34;
  byte abStack_32 [43];
  byte local_7;
  uint local_6;
  int local_4;
  
  local_7 = *pbRam0002b2b2;
  if (0x28 < param_5) {
    param_5 = 0x28;
  }
  local_6 = param_5;
  if ((param_3 & 0xdf) == 0x46) {
    if (0x7fff < param_5) {
      param_5 = 0;
    }
LAB_1000_06d2:
    if ((param_3 & 0xdf) == 0x45) {
      param_5 = param_5 + 1;
    }
  }
  else if (0 < (int)param_5) goto LAB_1000_06d2;
  puVar10 = &local_34;
  iVar5 = FUN_1000_0bde(param_1,puVar10);
  uVar14 = (undefined2)((ulong)param_4 >> 0x10);
  piVar12 = (int *)param_4;
  if (iVar5 == 0x7fff) {
    iVar5 = 0x492b;
    if (local_4 != 0) {
      iVar5 = 0x492d;
    }
    *param_4 = iVar5;
    piVar9 = piVar12 + 2;
    piVar12[1] = 0x464e;
    goto LAB_1000_082c;
  }
  if (iVar5 == 0x7ffe) {
    iVar5 = 0x4e2b;
    if (local_4 != 0) {
      iVar5 = 0x4e2d;
    }
    *param_4 = iVar5;
    piVar9 = piVar12 + 2;
    piVar12[1] = CONCAT11((char)((uint)iVar5 >> 8),0x41);
    goto LAB_1000_082c;
  }
  piVar13 = piVar12;
  if ((char)local_4 != '\0') {
    piVar13 = (int *)((int)piVar12 + 1);
    *(byte *)param_4 = 0x2d;
  }
  if ((param_3 & 0x5f) == 0x46) {
LAB_1000_0755:
    if (iVar5 < 0x29) {
      if (iVar5 < 1) {
        piVar3 = piVar13;
        piVar13 = piVar13 + 1;
        *piVar3 = CONCAT11(local_7,0x30);
        iVar8 = 1;
        if (iVar5 != 0) {
          do {
            piVar3 = piVar13;
            piVar13 = (int *)((int)piVar13 + 1);
            *(byte *)piVar3 = 0x30;
            iVar5 = iVar5 + 1;
          } while (iVar5 != 0);
          goto LAB_1000_076f;
        }
      }
      else {
LAB_1000_076f:
        iVar8 = 0;
      }
      while( true ) {
        piVar9 = piVar13;
        puVar1 = puVar10;
        puVar10 = (undefined2 *)((int)puVar10 + 1);
        if (*(byte *)puVar1 == 0) break;
        *(byte *)piVar9 = *(byte *)puVar1;
        iVar5 = iVar5 + -1;
        piVar13 = (int *)((int)piVar9 + 1);
        if (iVar5 == 0) {
          *(byte *)(int *)((int)piVar9 + 1) = local_7;
          iVar8 = iVar8 + 1;
          piVar13 = piVar9 + 1;
        }
      }
      if (iVar8 + local_6 < param_5) {
        iVar8 = param_5 - (iVar8 + local_6);
        iVar5 = iVar5 + iVar8;
        for (; iVar8 != 0; iVar8 = iVar8 + -1) {
          piVar3 = piVar9;
          piVar9 = (int *)((int)piVar9 + 1);
          *(byte *)piVar3 = 0x30;
        }
        iVar5 = iVar5 + -1;
        if (iVar5 != 0) goto LAB_1000_079a;
      }
      else {
LAB_1000_079a:
        if ((iVar5 != 1) && (param_2 == '\0')) {
          FUN_1000_066b();
        }
      }
      if (piVar9 == piVar12) {
        piVar3 = piVar9;
        piVar9 = (int *)((int)piVar9 + 1);
        *(byte *)piVar3 = 0x30;
      }
      goto LAB_1000_082c;
    }
  }
  else if (((param_3 & 0x5f) != 0x45) && (-4 < iVar5)) {
    uVar6 = param_5;
    if (param_5 == 0) {
      uVar6 = 1;
    }
    if (iVar5 <= (int)uVar6) goto LAB_1000_0755;
  }
  pbVar11 = abStack_32;
  piVar12 = (int *)((int)piVar13 + 1);
  *(byte *)piVar13 = (byte)local_34;
  bVar7 = (byte)((uint)local_34 >> 8);
  if (bVar7 == 0) {
    if (param_2 != '\0') {
      piVar3 = piVar12;
      piVar12 = piVar13 + 1;
      *(byte *)piVar3 = local_7;
    }
  }
  else {
    piVar3 = piVar12;
    piVar12 = piVar13 + 1;
    *(byte *)piVar3 = local_7;
    do {
      piVar3 = piVar12;
      piVar12 = (int *)((int)piVar12 + 1);
      *(byte *)piVar3 = bVar7;
      pbVar2 = pbVar11;
      pbVar11 = pbVar11 + 1;
      bVar7 = *pbVar2;
    } while (bVar7 != 0);
    if (param_2 == '\0') {
      FUN_1000_066b();
    }
  }
  *(byte *)piVar12 = param_3 & 0x20 | 0x45;
  bVar7 = 0x2b;
  uVar6 = iVar5 - 1;
  if (iVar5 < 1) {
    bVar7 = 0x2d;
    uVar6 = -uVar6;
  }
  piVar13 = piVar12 + 1;
  *(byte *)((int)piVar12 + 1) = bVar7;
  if (99 < uVar6) {
    if (999 < uVar6) {
      uVar4 = (ulong)(int)uVar6;
      uVar6 = (uint)(uVar4 % 1000);
      piVar3 = piVar13;
      piVar13 = (int *)((int)piVar12 + 3);
      *(byte *)piVar3 = (char)(uVar4 / 1000) + 0x30;
    }
    piVar3 = piVar13;
    piVar13 = (int *)((int)piVar13 + 1);
    *(byte *)piVar3 = (char)(uVar6 / 100) + 0x30;
    uVar6 = (uint)(char)(uVar6 % 100);
  }
  piVar9 = piVar13 + 1;
  *piVar13 = CONCAT11((char)(uVar6 % 10),(char)(uVar6 / 10)) + 0x3030;
LAB_1000_082c:
  *(byte *)piVar9 = 0;
  return;
}



// Function: FUN_1000_083a

void __cdecl16near FUN_1000_083a(void)

{
  return;
}



// Function: FUN_1000_083f

uint __cdecl16near
FUN_1000_083f(code *param_1,code *param_2,undefined2 param_3,undefined2 param_4,int param_5,
             int *param_6,undefined2 *param_7)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  char cVar6;
  byte bVar7;
  byte bVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  bool bVar13;
  undefined2 local_10;
  int local_e;
  char local_b;
  
  bVar2 = true;
  bVar3 = false;
  bVar4 = false;
  local_b = '\0';
  local_e = 0;
  local_10 = 1;
  bVar8 = *pbRam0002b2b2;
  uVar10 = 0x8000;
  uVar11 = 0xfffe;
  do {
    local_e = local_e + 1;
    uVar9 = (*param_1)(param_3,param_4);
    if ((int)uVar9 < 0) {
      local_10 = 0xffff;
      goto LAB_1000_0989;
    }
    cVar6 = (char)uVar9;
    uVar9 = (uint)cVar6;
  } while (((uVar9 & 0x80) == 0) && ((*(byte *)(uVar9 + 0x25bf) & 1) != 0));
  iVar12 = param_5 + -1;
  if (0 < param_5) {
    if ((cVar6 != '+') && (iVar1 = local_e, cVar6 != '-')) goto LAB_1000_08e4;
    bVar3 = true;
    param_5 = iVar12;
    while (iVar12 = param_5 + -1, 0 < param_5) {
      iVar1 = local_e + 1;
      uVar9 = (*param_1)(param_3,param_4);
      if ((bVar2) && (bVar3)) {
        if ((char)uVar9 == 'I') {
          uVar9 = (*param_1)(param_3,param_4);
          iVar1 = param_5 + -2;
          iVar5 = local_e + 2;
          if ((iVar12 < 1) || ((char)uVar9 != 'N')) goto LAB_1000_0984;
          local_e = local_e + 3;
          uVar9 = (*param_1)(param_3,param_4);
          iVar1 = param_5 + -3;
          iVar5 = local_e;
          if ((iVar1 < 1) || ((char)uVar9 != 'F')) goto LAB_1000_0984;
          goto LAB_1000_0aac;
        }
        if ((char)uVar9 == 'N') {
          uVar9 = (*param_1)(param_3,param_4);
          iVar1 = param_5 + -2;
          iVar5 = local_e + 2;
          if ((iVar12 < 1) || ((char)uVar9 != 'A')) goto LAB_1000_0984;
          local_e = local_e + 3;
          uVar9 = (*param_1)(param_3,param_4);
          iVar1 = param_5 + -3;
          iVar5 = local_e;
          if ((iVar1 < 1) || ((char)uVar9 != 'N')) goto LAB_1000_0984;
          goto LAB_1000_0aac;
        }
      }
LAB_1000_08e4:
      local_e = iVar1;
      param_5 = iVar12;
      bVar2 = false;
      bVar7 = (byte)uVar9;
      if (bVar7 == bVar8) {
        if (uVar10 != 0x8000) goto LAB_1000_09a5;
        uVar10 = 0;
        if (0 < (int)uVar11) {
          uVar10 = uVar11;
        }
      }
      else {
        if ((0x39 < bVar7) || (bVar7 < 0x30)) goto LAB_1000_09a5;
        bVar13 = SCARRY2(uVar11,1);
        uVar11 = uVar11 + 1;
        if ((uVar11 == 0 || bVar13 != (int)uVar11 < 0) &&
           ((uVar11 = 1, bVar7 == 0x30 && (uVar11 = 0xffff, uVar10 != 0x8000)))) {
          uVar10 = uVar10 - 1;
        }
      }
    }
  }
  param_5 = iVar12;
  uVar9 = 0x65;
LAB_1000_09a5:
  iVar1 = param_5;
  iVar5 = local_e;
  if (uVar11 == 0xfffe) {
LAB_1000_0984:
    local_e = iVar5;
    param_5 = iVar1;
    local_10 = 0;
LAB_1000_0989:
    if (-1 < param_5) {
      uVar9 = (*param_2)(uVar9,param_3,param_4);
      local_e = local_e + -1;
    }
  }
  else {
    if (uVar10 == 0x8000) {
      uVar10 = uVar11;
    }
    iVar12 = 0;
    if (((char)uVar9 == 'E') || ((char)uVar9 == 'e')) {
      iVar1 = param_5 + -1;
      if (0 < param_5) {
        local_e = local_e + 1;
        uVar9 = (*param_1)(param_3,param_4);
        param_5 = iVar1;
        if ((char)uVar9 != '+') {
          if ((char)uVar9 != '-') goto LAB_1000_09f3;
          bVar4 = true;
        }
        while (0 < param_5) {
          local_e = local_e + 1;
          uVar9 = (*param_1)(param_3,param_4);
          param_5 = param_5 + -1;
LAB_1000_09f3:
          bVar8 = (byte)uVar9;
          if ((0x39 < bVar8) || (bVar8 < 0x30)) goto LAB_1000_0a14;
          uVar9 = iVar12 * 10;
          iVar12 = (int)(char)(bVar8 - 0x30) + uVar9;
          if (0x1344 < iVar12) {
            iVar12 = 0;
            local_b = '\x01';
          }
        }
      }
    }
    else {
LAB_1000_0a14:
      uVar9 = (*param_2)(uVar9,param_3,param_4);
      local_e = local_e + -1;
    }
    if (bVar4) {
      iVar12 = -iVar12;
      local_b = -local_b;
    }
    if (-1 < (int)uVar11) {
      uVar9 = uVar10 + iVar12;
      if (local_b == '\x01') {
        uVar9 = 0xffff;
      }
      else if (local_b != -1) {
        if (0x12 < uVar11) {
          uVar11 = 0x12;
        }
        uVar9 = iVar12 + (uVar10 - uVar11);
        if (uVar9 != 0) {
          if ((int)uVar9 < 0) {
            uVar9 = -uVar9;
          }
          FUN_1000_0df4();
        }
        goto LAB_1000_0aac;
      }
      local_10 = 2;
    }
  }
LAB_1000_0aac:
  *param_6 = *param_6 + local_e;
  *param_7 = local_10;
  return uVar9;
}



// Function: FUN_1000_0b54

void __cdecl16near FUN_1000_0b54(void)

{
  return;
}



// Function: FUN_1000_0b5c

void __cdecl16near FUN_1000_0b5c(unkbyte10 *param_1,uint param_2)

{
  unkbyte10 in_ST0;
  longdouble in_ST1;
  
  if ((param_2 & 4) == 0) {
    if ((param_2 & 8) == 0) {
      FUN_1000_05ab(DAT_28d3_1c4c,in_ST0,0);
      *(float *)param_1 = (float)in_ST1;
    }
    else {
      *param_1 = in_ST0;
    }
  }
  else {
    FUN_1000_05ab(DAT_28d3_1c06,in_ST0,1);
    *(double *)param_1 = (double)in_ST1;
  }
  return;
}



// Function: FUN_1000_0bd9

void __cdecl16far FUN_1000_0bd9(void)

{
  return;
}



// Function: FUN_1000_0bde

void FUN_1000_0bde(uint param_1)

{
  uint *puVar1;
  undefined4 param_2;
  
  puVar1 = (uint *)(param_1 + (int)param_2);
  *puVar1 = *puVar1 & 0x7fff;
                    /* WARNING: Could not recover jumptable at 0x00010c09. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)((param_1 >> 2) * 2 + 0xc0e))();
  return;
}



// Function: FUN_1000_0df4

void __cdecl16far FUN_1000_0df4(undefined2 param_1)

{
  FUN_1000_0e01(param_1);
  return;
}



// Function: FUN_1000_0e01

uint FUN_1000_0e01(uint param_1)

{
  if (((-0x1345 < (int)param_1) && ((int)param_1 < 0x1345)) && (param_1 != 0)) {
    if ((int)param_1 < 0) {
      param_1 = -param_1;
    }
    if (param_1 >> 4 == 0) {
      param_1 = 0;
    }
    else {
      param_1 = param_1 >> 0xd;
    }
  }
  return param_1;
}



// Function: FUN_1000_0ecc

void __cdecl16near FUN_1000_0ecc(void)

{
  code *pcVar1;
  int *in_BX;
  undefined2 unaff_SS;
  code *pcVar2;
  uint local_8 [2];
  
  stack0xfffa = (int *)CONCAT22(unaff_SS,in_BX);
  if (((uint)DAT_28d3_58b0 | DAT_28d3_58b2) != 0) {
    pcVar2 = (code *)(*DAT_28d3_58b0)(0x1000,8,0,0);
    local_8[0] = (uint)((ulong)pcVar2 >> 0x10);
    pcVar1 = (code *)pcVar2;
    (*DAT_28d3_58b0)(0x1000,8,pcVar2);
    if ((local_8[0] == 0) && (pcVar1 == (code *)((int)(undefined2 *)&DAT_28d3_0000 + 1))) {
      return;
    }
    if (((uint)pcVar1 | local_8[0]) != 0) {
      (*DAT_28d3_58b0)(0x1000,8,0,0);
      (*pcVar1)(0x1000,8,*(undefined2 *)(*stack0xfffa * 6 + 0x1cce));
      return;
    }
  }
  FUN_1000_2adc(0x1db4,(char *)s_String_reference_out_of_range_28d3_28cc + 7,
                (char *)s_Floating_point_error___s__28d3_1d53,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7,
                *(undefined2 *)((int)(undefined4 *)&DAT_28d3_1cd0 + *stack0xfffa * 6),
                *(undefined2 *)((int)(undefined4 *)&DAT_28d3_1cd0 + *stack0xfffa * 6 + 2));
  FUN_1000_4cca();
  return;
}



// Function: FUN_1000_0f76

undefined2 __cdecl16far FUN_1000_0f76(void)

{
  longdouble in_ST0;
  undefined2 local_c;
  
  local_c = (undefined2)(sqword)ROUND(in_ST0);
  return local_c;
}



// Function: FUN_1000_0fa2

undefined __cdecl16far
FUN_1000_0fa2(char param_1,undefined2 param_2,undefined2 param_3,uint param_4,char param_5,
             undefined2 param_6,undefined2 *param_7)

{
  code *pcVar1;
  undefined extraout_AH;
  undefined2 uVar2;
  undefined2 extraout_DX;
  
  uVar2 = CONCAT11((undefined)param_4,((byte)(param_4 >> 2) & 0xc0) + param_5);
  pcVar1 = (code *)swi(0x13);
  (*pcVar1)();
  if (param_1 == '\b') {
    *param_7 = uVar2;
    ((undefined2 *)param_7)[1] = extraout_DX;
  }
  return extraout_AH;
}



// Function: FUN_1000_0fe0

int __cdecl16far FUN_1000_0fe0(byte param_1)

{
  code *pcVar1;
  int iVar2;
  bool bVar3;
  
  bVar3 = true;
  pcVar1 = (code *)swi(0x16);
  iVar2 = (*pcVar1)();
  if (bVar3) {
    if ((param_1 & 1) != 0) {
      iVar2 = 0;
    }
  }
  else if (((param_1 & 1) != 0) && (iVar2 == 0)) {
    iVar2 = -1;
  }
  return iVar2;
}



// Function: FUN_1000_1009

undefined4 FUN_1000_1009(int param_1,int param_2)

{
  return CONCAT22(DAT_28d3_1d7d,
                  ((uint)DAT_28d3_1d78 * (param_1 + -1) + param_2 + -1) * 2 + DAT_28d3_1d7b);
}



// Function: FUN_1000_102d

uint FUN_1000_102d(int param_1,uint *param_2,uint *param_3)

{
  uint *puVar1;
  uint *puVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  uint *puVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  
  uVar4 = (uint)DAT_28d3_1d7a;
  uVar6 = uVar4;
  if (param_1 != 0) {
    uVar9 = (uint)((ulong)param_3 >> 0x10);
    puVar8 = (uint *)param_3;
    uVar10 = (uint)((ulong)param_2 >> 0x10);
    puVar7 = (uint *)param_2;
    bVar11 = puVar7 < puVar8;
    if (bVar11) {
      iVar5 = param_1 + -1;
      uVar6 = iVar5 * 2;
      puVar7 = puVar7 + iVar5;
      puVar8 = puVar8 + iVar5;
    }
    if (uVar4 == 0) {
      for (; param_1 != 0; param_1 = param_1 + -1) {
        puVar2 = puVar8;
        puVar8 = puVar8 + (uint)bVar11 * -2 + 1;
        puVar1 = puVar7;
        puVar7 = puVar7 + (uint)bVar11 * -2 + 1;
        *puVar2 = *puVar1;
      }
    }
    else {
      uVar6 = uVar9;
      if (uVar9 == uVar10) {
        do {
          do {
            bVar3 = in(0x3da);
          } while ((bool)(bVar3 & 1));
          do {
            bVar3 = in(0x3da);
          } while (!(bool)(bVar3 & 1));
          puVar1 = puVar7;
          puVar7 = puVar7 + (uint)bVar11 * -2 + 1;
          uVar6 = *puVar1;
          do {
            bVar3 = in(0x3da);
          } while ((bool)(bVar3 & 1));
          do {
            bVar3 = in(0x3da);
          } while (!(bool)(bVar3 & 1));
          puVar1 = puVar8;
          puVar8 = puVar8 + (uint)bVar11 * -2 + 1;
          *puVar1 = uVar6;
          param_1 = param_1 + -1;
        } while (param_1 != 0);
      }
      else {
        do {
          do {
            bVar3 = in(0x3da);
            uVar6 = uVar6 & 0xff00;
          } while ((bool)(bVar3 & 1));
          do {
            bVar3 = in(0x3da);
            uVar6 = CONCAT11((char)(uVar6 >> 8),bVar3 >> 1 | (bVar3 & 1) << 7);
          } while (!(bool)(bVar3 & 1));
          puVar2 = puVar8;
          puVar8 = puVar8 + (uint)bVar11 * -2 + 1;
          puVar1 = puVar7;
          puVar7 = puVar7 + (uint)bVar11 * -2 + 1;
          *puVar2 = *puVar1;
          param_1 = param_1 + -1;
        } while (param_1 != 0);
      }
    }
  }
  return uVar6;
}



// Function: FUN_1000_10a7

undefined FUN_1000_10a7(undefined2 param_1_00,undefined2 param_2_00,int param_1,undefined *param_2)

{
  int iVar1;
  undefined *puVar2;
  byte bVar3;
  undefined2 unaff_SS;
  undefined4 uVar4;
  undefined2 local_a;
  undefined local_7;
  uint local_6;
  uint local_4;
  
  local_7 = 0;
  bVar3 = FUN_1000_16ee();
  local_4 = (uint)bVar3;
  local_6 = FUN_1000_16ee();
  local_6 = local_6 >> 8;
  while (puVar2 = param_2, iVar1 = param_1 + -1, param_1 != 0) {
    param_2 = (undefined *)CONCAT22(param_2._2_2_,(undefined *)param_2 + 1);
    local_7 = *puVar2;
    switch(local_7) {
    case 7:
      FUN_1000_1769();
      break;
    case 8:
      if ((int)(uint)DAT_28d3_1d70 < (int)local_4) {
        local_4 = local_4 - 1;
      }
      break;
    default:
      if ((DAT_28d3_1d79 == '\0') && (DAT_28d3_1d80 != 0)) {
        local_a = CONCAT11(DAT_28d3_1d74,local_7);
        uVar4 = FUN_1000_1009(local_6 + 1,local_4 + 1);
        FUN_1000_102d(1,&local_a,unaff_SS,uVar4);
      }
      else {
        FUN_1000_1769();
        FUN_1000_1769();
      }
      local_4 = local_4 + 1;
      break;
    case 10:
      local_6 = local_6 + 1;
      break;
    case 0xd:
      local_4 = (uint)DAT_28d3_1d70;
    }
    if ((int)(uint)DAT_28d3_1d72 < (int)local_4) {
      local_4 = (uint)DAT_28d3_1d70;
      local_6 = local_6 + DAT_28d3_1d6e;
    }
    param_1 = iVar1;
    if ((int)(uint)DAT_28d3_1d73 < (int)local_6) {
      FUN_1000_1581(1,DAT_28d3_1d73,DAT_28d3_1d72,DAT_28d3_1d71,DAT_28d3_1d70,6);
      local_6 = local_6 - 1;
    }
  }
  FUN_1000_1769();
  return local_7;
}



// Function: FUN_1000_11f7

undefined2 __cdecl16far
FUN_1000_11f7(int param_1,int param_2,int param_3,int param_4,int param_5,undefined2 param_6)

{
  int iVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  int local_4;
  
  iVar1 = FUN_1000_1502(param_4,param_3,param_2,param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = (param_3 - param_1) + 1;
    for (local_4 = param_2; local_4 <= param_4; local_4 = local_4 + 1) {
      iVar4 = param_5;
      uVar2 = param_6;
      uVar3 = FUN_1000_1009(local_4,param_1);
      FUN_1000_14c4(iVar1,uVar3,iVar4,uVar2);
      param_5 = param_5 + iVar1 * 2;
    }
    uVar2 = 1;
  }
  return uVar2;
}



// Function: FUN_1000_125b

undefined2 __cdecl16far
FUN_1000_125b(int param_1,int param_2,int param_3,int param_4,int param_5,undefined2 param_6)

{
  int iVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int local_4;
  
  iVar1 = FUN_1000_1502(param_4,param_3,param_2,param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = (param_3 - param_1) + 1;
    for (local_4 = param_2; local_4 <= param_4; local_4 = local_4 + 1) {
      uVar3 = FUN_1000_1009(local_4,param_1);
      FUN_1000_14c4(iVar1,param_5,param_6,uVar3);
      param_5 = param_5 + iVar1 * 2;
    }
    uVar2 = 1;
  }
  return uVar2;
}



// Function: FUN_1000_12bf

undefined2 __cdecl16far
FUN_1000_12bf(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int local_8;
  int local_6;
  int local_4;
  
  iVar1 = FUN_1000_1502(param_4,param_3,param_2,param_1);
  if ((iVar1 == 0) ||
     (iVar1 = FUN_1000_1502((param_4 - param_2) + param_6,(param_3 - param_1) + param_5,param_6,
                            param_5), iVar1 == 0)) {
    uVar2 = 0;
  }
  else {
    local_4 = param_4;
    local_6 = 1;
    local_8 = param_2;
    if (param_2 < param_6) {
      local_4 = param_2;
      local_6 = -1;
      local_8 = param_4;
    }
    for (; local_4 + local_6 != local_8; local_8 = local_8 + local_6) {
      uVar3 = FUN_1000_1009((local_8 - param_2) + param_6,param_5);
      uVar4 = FUN_1000_1009(local_8,param_1);
      FUN_1000_14c4((param_3 - param_1) + 1,uVar4,uVar3);
    }
    uVar2 = 1;
  }
  return uVar2;
}



// Function: FUN_1000_1367

void __cdecl16far FUN_1000_1367(void)

{
  undefined2 unaff_SS;
  
  FUN_1000_10a7(0,0,1,&stack0x0004,unaff_SS);
  return;
}



// Function: FUN_1000_1380

undefined2 FUN_1000_1380(uint param_1)

{
  char cVar1;
  
  cVar1 = (char)((param_1 >> 1) / (uint)DAT_28d3_1d78);
  return CONCAT11(cVar1,(char)(param_1 >> 1) - cVar1 * DAT_28d3_1d78);
}



// Function: FUN_1000_13ba

void FUN_1000_13ba(int *param_1,int *param_2)

{
  byte bVar1;
  int extraout_DX;
  char cVar3;
  int iVar2;
  
  iVar2 = *param_2;
  if (iVar2 != *param_1) {
    FUN_1000_1769();
    *param_1 = extraout_DX;
    iVar2 = extraout_DX;
  }
  cVar3 = (char)((uint)iVar2 >> 8);
  bVar1 = (char)iVar2 + 1;
  iVar2 = CONCAT11(cVar3,bVar1);
  if (DAT_28d3_1d78 <= bVar1) {
    iVar2 = (uint)(byte)(cVar3 + 1) << 8;
  }
  *param_2 = iVar2;
  return;
}



// Function: FUN_1000_13f2

void FUN_1000_13f2(int param_1,undefined2 *param_2,undefined2 *param_4)

{
  undefined2 unaff_SS;
  bool bVar1;
  bool bVar2;
  undefined2 local_a;
  undefined2 local_8;
  undefined2 local_6;
  undefined2 local_4;
  
  local_a = FUN_1000_16ee();
  bVar1 = param_4._2_2_ == DAT_28d3_1d7d;
  if (bVar1) {
    local_6 = FUN_1000_1380((undefined2 *)param_4,param_4._2_2_);
  }
  bVar2 = param_2._2_2_ == DAT_28d3_1d7d;
  if (bVar2) {
    local_8 = FUN_1000_1380((undefined2 *)param_2,param_2._2_2_);
  }
  while (param_1 != 0) {
    if (bVar2) {
      FUN_1000_13ba(&local_a,unaff_SS,&local_8,unaff_SS);
      local_4 = FUN_1000_1769();
    }
    else {
      local_4 = *param_2;
      param_2 = (undefined2 *)CONCAT22(param_2._2_2_,(undefined2 *)param_2 + 1);
    }
    if (bVar1) {
      FUN_1000_13ba(&local_a,unaff_SS,&local_6,unaff_SS);
      FUN_1000_1769();
      param_1 = param_1 + -1;
    }
    else {
      *param_4 = local_4;
      param_4 = (undefined2 *)CONCAT22(param_4._2_2_,(undefined2 *)param_4 + 1);
      param_1 = param_1 + -1;
    }
  }
  FUN_1000_1769();
  return;
}



// Function: FUN_1000_14c4

void FUN_1000_14c4(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
                  undefined2 param_5)

{
  if ((DAT_28d3_1d79 == '\0') && (DAT_28d3_1d80 != 0)) {
    FUN_1000_102d(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    FUN_1000_13f2(param_1,param_2,param_3,param_4,param_5);
  }
  return;
}



// Function: FUN_1000_1502

undefined2 FUN_1000_1502(uint param_1,uint param_2,uint param_3,uint param_4)

{
  undefined2 uVar1;
  
  if ((((((DAT_28d3_1d78 < param_4) || (DAT_28d3_1d78 < param_2)) || ((int)param_2 < (int)param_4))
       || ((DAT_28d3_1d77 < param_3 || (DAT_28d3_1d77 < param_1)))) ||
      (((int)param_1 < (int)param_3 || (((int)param_4 < 1 || ((int)param_2 < 1)))))) ||
     (((int)param_3 < 1 || ((int)param_1 < 1)))) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



// Function: FUN_1000_155b

void FUN_1000_155b(int param_1,int param_2,undefined2 *param_3)

{
  undefined2 uVar1;
  
  uVar1 = CONCAT11(DAT_28d3_1d74,0x20);
  for (; param_2 <= param_1; param_2 = param_2 + 1) {
    *param_3 = uVar1;
    param_3 = (undefined2 *)CONCAT22(param_3._2_2_,(undefined2 *)param_3 + 1);
  }
  return;
}



// Function: FUN_1000_1581

void FUN_1000_1581(char param_1,char param_2,char param_3,char param_4,char param_5,char param_6)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  undefined2 unaff_SS;
  undefined local_b6 [160];
  uint local_16;
  uint local_14;
  uint local_12;
  uint local_10;
  uint local_e;
  uint local_c;
  uint local_a;
  uint local_8;
  uint local_6;
  uint local_4;
  
  if (((DAT_28d3_1d79 == '\0') && (DAT_28d3_1d80 != 0)) && (param_1 == '\x01')) {
    bVar1 = param_5 + 1;
    bVar2 = param_4 + 1;
    param_3 = param_3 + '\x01';
    bVar3 = param_2 + 1;
    if (param_6 == '\x06') {
      local_4 = (uint)bVar2;
      local_6 = (uint)bVar1;
      FUN_1000_12bf(local_6,local_4 + 1,param_3,bVar3,local_6,local_4);
      local_8 = (uint)bVar3;
      local_a = (uint)bVar1;
      FUN_1000_11f7(local_a,local_8,local_a,local_8,local_b6);
      FUN_1000_155b(param_3,bVar1,local_b6,unaff_SS);
      uVar4 = (uint)bVar3;
      local_c = uVar4;
    }
    else {
      local_e = (uint)bVar2;
      local_10 = (uint)bVar1;
      FUN_1000_12bf(local_10,local_e,param_3,bVar3 - 1,local_10,local_e + 1);
      local_12 = (uint)bVar2;
      local_14 = (uint)bVar1;
      FUN_1000_11f7(local_14,local_12,local_14,local_12,local_b6);
      FUN_1000_155b(param_3,bVar1,local_b6,unaff_SS);
      uVar4 = (uint)bVar2;
      local_16 = uVar4;
    }
    FUN_1000_125b(bVar1,uVar4,param_3,uVar4,local_b6);
  }
  else {
    FUN_1000_1769();
  }
  return;
}



// Function: FUN_1000_16ee

undefined2 __cdecl16near FUN_1000_16ee(void)

{
  undefined2 extraout_DX;
  
  FUN_1000_1769();
  return extraout_DX;
}



// Function: FUN_1000_1726

undefined2 FUN_1000_1726(char *param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  
  do {
    pcVar2 = param_2;
    pcVar1 = param_1;
    if (*param_1 == '\0') {
      return 1;
    }
    param_1 = (char *)CONCAT22(param_1._2_2_,(char *)param_1 + 1);
    param_2 = (char *)CONCAT22(param_2._2_2_,(char *)param_2 + 1);
  } while (*pcVar1 == *pcVar2);
  return 0;
}



// Function: FUN_1000_1757

char __cdecl16near FUN_1000_1757(void)

{
  char cVar1;
  
  cVar1 = '\x10';
  FUN_1000_1769();
  return cVar1 + -0x10;
}



// Function: FUN_1000_1769

char __cdecl16near FUN_1000_1769(void)

{
  code *pcVar1;
  char cVar2;
  char cVar3;
  undefined2 in_AX;
  
  cVar2 = (char)((uint)in_AX >> 8);
  if (cVar2 == '\0') {
    cVar2 = (char)in_AX;
    if ((cVar2 == '\x02') || (cVar2 == '\x03')) {
      pcVar1 = (code *)swi(0x10);
      cVar2 = (*pcVar1)((char *)s_String_reference_out_of_range_28d3_28cc + 7);
      if (cVar2 != '\x1a') {
        DAT_0000_0487 = DAT_0000_0487 & 0xfe;
      }
      pcVar1 = (code *)swi(0x10);
      (*pcVar1)();
    }
    else if (cVar2 == '@') {
      cVar3 = '\x10';
      pcVar1 = (code *)swi(0x10);
      cVar2 = (*pcVar1)();
      if (cVar3 == '\x10') {
        return cVar2;
      }
      pcVar1 = (code *)swi(0x10);
      (*pcVar1)();
      pcVar1 = (code *)swi(0x10);
      (*pcVar1)();
      pcVar1 = (code *)swi(0x10);
      cVar2 = (*pcVar1)();
      if (cVar2 == '\x1a') {
        return '\x1a';
      }
      DAT_0000_0487 = DAT_0000_0487 | 1;
      pcVar1 = (code *)swi(0x10);
      cVar2 = (*pcVar1)();
      return cVar2;
    }
  }
  else if (cVar2 == '\x0f') {
    pcVar1 = (code *)swi(0x10);
    cVar2 = (*pcVar1)();
    if ((cVar2 != '\x02') && (cVar2 != '\x03')) {
      return cVar2;
    }
    cVar3 = FUN_1000_1757();
    if (cVar3 == '\0') {
      return cVar2;
    }
    if (DAT_0000_0484 == '\x18') {
      return cVar2;
    }
    return '@';
  }
  pcVar1 = (code *)swi(0x10);
  cVar2 = (*pcVar1)();
  return cVar2;
}



// Function: FUN_1000_1819

void __cdecl16near FUN_1000_1819(byte param_1)

{
  undefined2 uVar1;
  int iVar2;
  
  DAT_28d3_1d76 = param_1;
  uVar1 = FUN_1000_1769();
  DAT_28d3_1d78 = (char)((uint)uVar1 >> 8);
  if ((byte)uVar1 != DAT_28d3_1d76) {
    FUN_1000_1769();
    uVar1 = FUN_1000_1769();
    DAT_28d3_1d76 = (byte)uVar1;
    DAT_28d3_1d78 = (char)((uint)uVar1 >> 8);
  }
  if (((DAT_28d3_1d76 < 4) || (0x3f < DAT_28d3_1d76)) || (DAT_28d3_1d76 == 7)) {
    DAT_28d3_1d79 = 0;
  }
  else {
    DAT_28d3_1d79 = 1;
  }
  if (DAT_28d3_1d76 == 0x40) {
    DAT_28d3_1d77 = DAT_0000_0484 + '\x01';
  }
  else {
    DAT_28d3_1d77 = '\x19';
  }
  if (DAT_28d3_1d76 != 7) {
    iVar2 = FUN_1000_1726(0x1d82,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0xffea,0xf000
                         );
    if (iVar2 == 0) {
      iVar2 = FUN_1000_1757();
      if (iVar2 == 0) {
        DAT_28d3_1d7a = 1;
        goto LAB_1000_18a8;
      }
    }
  }
  DAT_28d3_1d7a = 0;
LAB_1000_18a8:
  if (DAT_28d3_1d76 == 7) {
    DAT_28d3_1d7d = 0xb000;
  }
  else {
    DAT_28d3_1d7d = 0xb800;
  }
  DAT_28d3_1d7b = 0;
  DAT_28d3_1d71 = 0;
  DAT_28d3_1d70 = 0;
  DAT_28d3_1d72 = DAT_28d3_1d78 + -1;
  DAT_28d3_1d73 = DAT_28d3_1d77 + -1;
  return;
}



// Function: FUN_1000_18df

undefined __cdecl16far FUN_1000_18df(void)

{
  code *pcVar1;
  undefined uVar2;
  
  if (DAT_28d3_1d8a == '\0') {
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
  }
  else {
    DAT_28d3_1d8a = '\0';
    uVar2 = DAT_28d3_1d8b;
  }
  return uVar2;
}



// Function: FUN_1000_1953

int __cdecl16far FUN_1000_1953(void)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  
  if (DAT_28d3_1d8a == '\0') {
    pcVar1 = (code *)swi(0x21);
    cVar2 = (*pcVar1)();
    iVar3 = (int)cVar2;
  }
  else {
    iVar3 = 1;
  }
  return iVar3;
}



// Function: FUN_1000_1969

int __cdecl16far FUN_1000_1969(int param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  int iVar1;
  
  iVar1 = FUN_1000_1c56(param_3,param_4);
  FUN_1000_1a99(param_1,param_2,param_3,param_4,iVar1 + 1);
  return param_1 + iVar1;
}



// Function: FUN_1000_19a6

char * __cdecl16far FUN_1000_19a6(char *param_1,uint param_2,char *param_3,undefined2 param_4)

{
  char *pcVar1;
  undefined4 local_6;
  
  if (((uint)param_1 | param_2) != 0) {
    DAT_28d3_5812 = (char *)CONCAT22(param_2,param_1);
  }
  while (pcVar1 = (char *)DAT_28d3_5812, *DAT_28d3_5812 != '\0') {
    local_6 = (char *)CONCAT22(param_4,param_3);
    while ((*local_6 != '\0' && (*local_6 != *DAT_28d3_5812))) {
      local_6 = (char *)CONCAT22(local_6._2_2_,(char *)local_6 + 1);
    }
    if (*local_6 == '\0') break;
    DAT_28d3_5812 = (char *)CONCAT22(DAT_28d3_5812._2_2_,(char *)DAT_28d3_5812 + 1);
  }
  if (*DAT_28d3_5812 == '\0') {
    pcVar1 = (char *)0x0;
  }
  else {
    while (*DAT_28d3_5812 != '\0') {
      local_6 = (char *)CONCAT22(param_4,param_3);
      while (*local_6 != '\0') {
        if (*local_6 == *DAT_28d3_5812) {
          *DAT_28d3_5812 = '\0';
          DAT_28d3_5812 = (char *)CONCAT22(DAT_28d3_5812._2_2_,(char *)DAT_28d3_5812 + 1);
          return pcVar1;
        }
        local_6 = (char *)CONCAT22(local_6._2_2_,(char *)local_6 + 1);
      }
      DAT_28d3_5812 = (char *)CONCAT22(DAT_28d3_5812._2_2_,(char *)DAT_28d3_5812 + 1);
    }
  }
  return pcVar1;
}



// Function: FUN_1000_1a71

int __cdecl16far FUN_1000_1a71(char *param_1,char *param_2,uint param_3)

{
  char *pcVar1;
  char *pcVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  
  uVar3 = param_3;
  if (param_3 != 0) {
    uVar7 = (undefined2)((ulong)param_1 >> 0x10);
    pcVar4 = (char *)param_1;
    uVar6 = (undefined2)((ulong)param_2 >> 0x10);
    pcVar5 = (char *)param_2;
    do {
      if (param_3 == 0) break;
      param_3 = param_3 - 1;
      pcVar2 = pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar1 = pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (*pcVar1 == *pcVar2);
    param_3 = (uint)(byte)pcVar4[-1];
    uVar3 = (uint)(byte)pcVar5[-1];
  }
  return param_3 - uVar3;
}



// Function: FUN_1000_1a99

undefined2 * __cdecl16far FUN_1000_1a99(undefined2 *param_1,undefined2 *param_2,uint param_3)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  uint uVar3;
  undefined2 *puVar4;
  undefined2 *puVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  
  uVar6 = (undefined2)((ulong)param_1 >> 0x10);
  uVar7 = (undefined2)((ulong)param_2 >> 0x10);
  puVar4 = (undefined2 *)param_2;
  puVar5 = (undefined2 *)param_1;
  for (uVar3 = param_3 >> 1; uVar3 != 0; uVar3 = uVar3 - 1) {
    puVar2 = puVar5;
    puVar5 = puVar5 + 1;
    puVar1 = puVar4;
    puVar4 = puVar4 + 1;
    *puVar2 = *puVar1;
  }
  if ((param_3 & 1) != 0) {
    *(undefined *)puVar5 = *(undefined *)puVar4;
  }
  return (undefined2 *)param_1;
}



// Function: FUN_1000_1abd

void __cdecl16far FUN_1000_1abd(undefined2 *param_1,uint param_2,undefined param_3)

{
  undefined2 *puVar1;
  uint uVar2;
  undefined2 *puVar3;
  undefined2 uVar4;
  
  uVar4 = (undefined2)((ulong)param_1 >> 0x10);
  puVar3 = (undefined2 *)param_1;
  if (((ulong)param_1 & 1) != 0) {
    if (param_2 == 0) {
      return;
    }
    puVar3 = (undefined2 *)((int)puVar3 + 1);
    *(undefined *)param_1 = param_3;
    param_2 = param_2 - 1;
  }
  for (uVar2 = param_2 >> 1; uVar2 != 0; uVar2 = uVar2 - 1) {
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar1 = CONCAT11(param_3,param_3);
  }
  if ((param_2 & 1) != 0) {
    *(undefined *)puVar3 = param_3;
  }
  return;
}



// Function: FUN_1000_1ae3

undefined2 __cdecl16far
FUN_1000_1ae3(undefined2 param_1,undefined2 param_2,undefined param_3,undefined2 param_4)

{
  FUN_1000_1abd(param_1,param_2,param_4,param_3);
  return param_1;
}



// Function: FUN_1000_1b06

void __cdecl16far FUN_1000_1b06(undefined *param_1,undefined *param_3,uint param_5)

{
  undefined *puVar1;
  undefined2 *puVar2;
  undefined *puVar3;
  undefined2 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined *puVar7;
  undefined2 *puVar8;
  undefined *puVar9;
  undefined2 *puVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  byte in_CF;
  
  FUN_1000_4bae((char *)s_String_reference_out_of_range_28d3_28cc + 7);
  uVar5 = (uint)in_CF;
  uVar12 = (undefined2)((ulong)param_1 >> 0x10);
  puVar7 = (undefined *)param_1;
  uVar11 = (undefined2)((ulong)param_3 >> 0x10);
  puVar9 = (undefined *)param_3;
  if (uVar5 != 0) {
    puVar7 = puVar7 + (param_5 - 1);
    puVar9 = puVar9 + (param_5 - 1);
  }
  if (((uint)puVar9 & 1) != 0) {
    if (param_5 == 0) {
      return;
    }
    puVar3 = puVar9;
    puVar9 = puVar9 + (uint)in_CF * -2 + 1;
    puVar1 = puVar7;
    puVar7 = puVar7 + (uint)in_CF * -2 + 1;
    *puVar3 = *puVar1;
    param_5 = param_5 - 1;
  }
  puVar8 = (undefined2 *)(puVar7 + -uVar5);
  puVar10 = (undefined2 *)(puVar9 + -uVar5);
  for (uVar6 = param_5 >> 1; uVar6 != 0; uVar6 = uVar6 - 1) {
    puVar4 = puVar10;
    puVar10 = puVar10 + (uint)in_CF * -2 + 1;
    puVar2 = puVar8;
    puVar8 = puVar8 + (uint)in_CF * -2 + 1;
    *puVar4 = *puVar2;
  }
  if ((param_5 & 1) != 0) {
    *(undefined *)((int)puVar10 + uVar5) = *(undefined *)((int)puVar8 + uVar5);
  }
  return;
}



// Function: FUN_1000_1b58

undefined2 __cdecl16far
FUN_1000_1b58(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5)

{
  FUN_1000_1b06(param_3,param_4,param_1,param_2,param_5);
  return param_1;
}



// Function: FUN_1000_1b7d

undefined2 * __cdecl16far FUN_1000_1b7d(undefined2 *param_1,char *param_2)

{
  undefined2 *puVar1;
  char *pcVar2;
  undefined2 *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined2 *puVar7;
  char *pcVar8;
  undefined2 *puVar9;
  undefined2 *puVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  
  uVar11 = (undefined2)((ulong)param_1 >> 0x10);
  iVar4 = -1;
  puVar7 = (undefined2 *)param_1;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    puVar1 = puVar7;
    puVar7 = (undefined2 *)((int)puVar7 + 1);
  } while (*(char *)puVar1 != '\0');
  uVar12 = (undefined2)((ulong)param_2 >> 0x10);
  pcVar8 = (char *)param_2;
  uVar5 = 0xffff;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar2 = pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (*pcVar2 != '\0');
  uVar5 = ~uVar5;
  puVar9 = (undefined2 *)(pcVar8 + -uVar5);
  puVar10 = (undefined2 *)((int)puVar7 + -1);
  if (((uint)puVar9 & 1) != 0) {
    puVar1 = puVar9;
    puVar9 = (undefined2 *)((int)puVar9 + 1);
    *(undefined *)(undefined2 *)((int)puVar7 + -1) = *(undefined *)puVar1;
    uVar5 = uVar5 - 1;
    puVar10 = puVar7;
  }
  for (uVar6 = uVar5 >> 1; uVar6 != 0; uVar6 = uVar6 - 1) {
    puVar3 = puVar10;
    puVar10 = puVar10 + 1;
    puVar1 = puVar9;
    puVar9 = puVar9 + 1;
    *puVar3 = *puVar1;
  }
  if ((uVar5 & 1) != 0) {
    *(undefined *)puVar10 = *(undefined *)puVar9;
  }
  return (undefined2 *)param_1;
}



// Function: FUN_1000_1bbc

int __cdecl16far FUN_1000_1bbc(char *param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  
  uVar6 = (undefined2)((ulong)param_2 >> 0x10);
  pcVar5 = (char *)param_2;
  uVar3 = 0xffff;
  pcVar4 = pcVar5;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (*pcVar1 != '\0');
  uVar3 = ~uVar3;
  uVar7 = (undefined2)((ulong)param_1 >> 0x10);
  pcVar4 = (char *)param_1;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar2 = pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (*pcVar1 == *pcVar2);
  return (uint)(byte)pcVar4[-1] - (uint)(byte)pcVar5[-1];
}



// Function: FUN_1000_1bec

char * __cdecl16far FUN_1000_1bec(char *param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  undefined2 uVar6;
  
  uVar6 = (undefined2)((ulong)param_2 >> 0x10);
  pcVar4 = (char *)param_2;
  uVar3 = 0xffff;
  pcVar5 = pcVar4;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar1 = pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (*pcVar1 != '\0');
  pcVar5 = (char *)param_1;
  for (uVar3 = ~uVar3; uVar3 != 0; uVar3 = uVar3 - 1) {
    pcVar2 = pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
    *pcVar2 = *pcVar1;
  }
  return (char *)param_1;
}



// Function: FUN_1000_1c15

int __cdecl16far FUN_1000_1c15(byte *param_1,byte *param_2)

{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  byte *pbVar7;
  undefined2 uVar8;
  
  pbVar6 = (byte *)param_1;
  uVar8 = (undefined2)((ulong)param_2 >> 0x10);
  pbVar7 = (byte *)param_2;
  do {
    do {
      pbVar1 = pbVar6;
      pbVar6 = pbVar6 + 1;
      bVar2 = *pbVar1;
      bVar3 = *pbVar7;
      uVar5 = (uint)bVar3;
      uVar4 = (uint)bVar2;
      if (bVar2 == 0) goto LAB_1000_1c4e;
      pbVar1 = pbVar7;
      pbVar7 = pbVar7 + 1;
    } while (bVar2 == *pbVar1);
    if ((0x60 < bVar2) && (bVar2 < 0x7b)) {
      uVar4 = (uint)(byte)(bVar2 - 0x20);
    }
    if ((0x60 < bVar3) && (bVar3 < 0x7b)) {
      uVar5 = (uint)(byte)(bVar3 - 0x20);
    }
  } while ((char)uVar4 == (char)uVar5);
LAB_1000_1c4e:
  return uVar4 - uVar5;
}



// Function: FUN_1000_1c56

int __cdecl16far FUN_1000_1c56(char *param_1)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  
  iVar5 = (int)((ulong)param_1 >> 0x10);
  pcVar4 = (char *)param_1;
  iVar2 = 0;
  if ((iVar5 != 0) || (pcVar4 != (char *)0x0)) {
    uVar3 = 0xffff;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar1 = pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (*pcVar1 != '\0');
    iVar2 = ~uVar3 - 1;
  }
  return iVar2;
}



// Function: FUN_1000_1c77

char * __cdecl16far FUN_1000_1c77(char *param_1,char *param_3)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  bool bVar9;
  
  if (*param_3 != '\0') {
    uVar7 = (undefined2)((ulong)param_1 >> 0x10);
    uVar2 = 0xffff;
    pcVar5 = (char *)param_1;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar1 = pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (*pcVar1 != '\0');
    uVar2 = ~uVar2;
    uVar8 = (undefined2)((ulong)param_3 >> 0x10);
    iVar3 = -1;
    pcVar5 = (char *)param_3;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar1 = pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (*pcVar1 != '\0');
    bVar9 = iVar3 + 1U == 0;
    uVar4 = ~(iVar3 + 1U);
    do {
      do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar1 = (char *)param_1;
        param_1._0_2_ = (char *)param_1 + 1;
        bVar9 = *param_3 == *pcVar1;
      } while (!bVar9);
      if ((!bVar9) || (uVar2 < uVar4)) {
        param_1._0_2_ = (char *)((int)(undefined2 *)&DAT_28d3_0000 + 1);
        break;
      }
      if (uVar4 == 0) break;
      iVar3 = uVar4 - 1;
      bVar9 = iVar3 == 0;
      pcVar6 = (char *)param_1;
      pcVar5 = (char *)param_3;
      do {
        pcVar5 = pcVar5 + 1;
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar1 = pcVar6;
        pcVar6 = pcVar6 + 1;
        bVar9 = *pcVar5 == *pcVar1;
      } while (bVar9);
    } while (!bVar9);
    param_1._0_2_ = (char *)param_1 + -1;
  }
  return (char *)param_1;
}



// Function: FUN_1000_1ce3

void __cdecl16far FUN_1000_1ce3(undefined4 param_1)

{
  uint *puVar1;
  
  puVar1 = (uint *)((int)param_1 + 2);
  *puVar1 = *puVar1 & 0xffcf;
  return;
}



// Function: FUN_1000_1cf4

void __cdecl16far FUN_1000_1cf4(int *param_1)

{
  code *pcVar1;
  byte bVar2;
  
  pcVar1 = (code *)swi(0x21);
  bVar2 = (*pcVar1)();
  *param_1 = bVar2 + 1;
  return;
}



// Function: FUN_1000_1d0a

void __cdecl16far FUN_1000_1d0a(undefined2 param_1,uint *param_2)

{
  code *pcVar1;
  byte bVar2;
  
  pcVar1 = (code *)swi(0x21);
  bVar2 = (*pcVar1)();
  *param_2 = (uint)bVar2;
  return;
}



// Function: FUN_1000_1d24

int __cdecl16far FUN_1000_1d24(void)

{
  int local_4;
  
  FUN_1000_1cf4(&local_4);
  return local_4 + -1;
}



// Function: FUN_1000_1d42

undefined2 __cdecl16far FUN_1000_1d42(int param_1)

{
  undefined2 local_4;
  
  FUN_1000_1d0a(param_1 + 1,&local_4);
  return local_4;
}



// Function: FUN_1000_1d65

undefined4 FUN_1000_1d65(undefined2 param_1,uint param_2,char *param_3,uint param_4,char *param_5)

{
  undefined2 uVar1;
  
  if ((param_4 | (uint)param_5) == 0) {
    param_5 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    param_4 = 0x5816;
  }
  if ((param_2 | (uint)param_3) == 0) {
    param_3 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    param_2 = 0x21de;
  }
  uVar1 = FUN_1000_1969(param_4,param_5,param_2,param_3,param_1);
  FUN_1000_4031(uVar1,param_3,param_1);
  FUN_1000_1b7d(param_4,param_5,0x21e2,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  return CONCAT22(param_5,param_4);
}



// Function: FUN_1000_1f49

undefined2 __cdecl16far FUN_1000_1f49(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined in_CF;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if ((bool)in_CF) {
    uVar2 = FUN_1000_1f84(uVar2);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// Function: FUN_1000_1f65

undefined2 __cdecl16far FUN_1000_1f65(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined in_CF;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if ((bool)in_CF) {
    uVar2 = FUN_1000_1f84(uVar2);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// Function: FUN_1000_1f84

undefined2 FUN_1000_1f84(int param_1)

{
  if (param_1 < 0) {
    if (-iRam0002b09c == param_1 || -param_1 < iRam0002b09c) {
      DAT_28d3_007e = -param_1;
      DAT_28d3_21e8 = 0xffff;
      return 0xffff;
    }
  }
  else if (param_1 < 0x59) goto LAB_1000_1f98;
  param_1 = 0x57;
LAB_1000_1f98:
  DAT_28d3_21e8 = param_1;
  DAT_28d3_007e = (int)*(char *)(param_1 + 0x21ea);
  return 0xffff;
}



// Function: FUN_1000_1fc2

undefined2 FUN_1000_1fc2(undefined2 param_1)

{
  FUN_1000_1f84(param_1);
  return param_1;
}



// Function: FUN_1000_1fd6

uint __cdecl16far FUN_1000_1fd6(void)

{
  code *pcVar1;
  uint extraout_DX;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return extraout_DX & 0x80;
}



// Function: FUN_1000_1feb

void __cdecl16far FUN_1000_1feb(int param_1)

{
  uint *puVar1;
  code *pcVar2;
  undefined2 uVar3;
  bool bVar4;
  
  puVar1 = (uint *)(param_1 * 2 + 0x2176);
  bVar4 = false;
  *puVar1 = *puVar1 & 0xfdff;
  pcVar2 = (code *)swi(0x21);
  uVar3 = (*pcVar2)();
  if (bVar4) {
    FUN_1000_1f84(uVar3);
  }
  return;
}



// Function: FUN_1000_2018

void __cdecl16far FUN_1000_2018(int param_1)

{
  code *pcVar1;
  bool bVar2;
  undefined2 uVar3;
  
  bVar2 = false;
  if ((*(uint *)(param_1 * 2 + 0x2176) & 2) == 0) {
    pcVar1 = (code *)swi(0x21);
    uVar3 = (*pcVar1)();
    if (!bVar2) {
      return;
    }
  }
  else {
    uVar3 = 5;
  }
  FUN_1000_1f84(uVar3);
  return;
}



// Function: FUN_1000_204b

void __cdecl16far
FUN_1000_204b(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  FUN_1000_2018(param_1,param_2,param_3,param_4);
  return;
}



// Function: FUN_1000_2067

undefined2 __cdecl16far FUN_1000_2067(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined in_CF;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if ((bool)in_CF) {
    uVar2 = FUN_1000_1f84(uVar2);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// Function: FUN_1000_2083

void FUN_1000_2083(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte extraout_AH;
  char *unaff_DI;
  undefined2 unaff_ES;
  byte in_AF;
  
  FUN_1000_208a();
  FUN_1000_2093();
  in_AF = 9 < (extraout_AH + 0x90 & 0xf) | in_AF;
  bVar3 = extraout_AH + 0x90 + in_AF * '\x06';
  bVar2 = 0x90 < (bVar3 & 0xf0) | 0x6f < extraout_AH | in_AF * (0xf9 < bVar3);
  bVar3 = bVar3 + bVar2 * '`';
  bVar1 = bVar3 + 0x40;
  bVar4 = bVar1 + bVar2;
  in_AF = 9 < (bVar4 & 0xf) | in_AF;
  bVar4 = bVar4 + in_AF * '\x06';
  *unaff_DI = bVar4 + (0x90 < (bVar4 & 0xf0) |
                      (0xbf < bVar3 || CARRY1(bVar1,bVar2)) | in_AF * (0xf9 < bVar4)) * '`';
  return;
}



// Function: FUN_1000_208a

void FUN_1000_208a(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte extraout_AH;
  char *unaff_DI;
  undefined2 unaff_ES;
  byte in_AF;
  
  FUN_1000_2093();
  in_AF = 9 < (extraout_AH + 0x90 & 0xf) | in_AF;
  bVar3 = extraout_AH + 0x90 + in_AF * '\x06';
  bVar2 = 0x90 < (bVar3 & 0xf0) | 0x6f < extraout_AH | in_AF * (0xf9 < bVar3);
  bVar3 = bVar3 + bVar2 * '`';
  bVar1 = bVar3 + 0x40;
  bVar4 = bVar1 + bVar2;
  in_AF = 9 < (bVar4 & 0xf) | in_AF;
  bVar4 = bVar4 + in_AF * '\x06';
  *unaff_DI = bVar4 + (0x90 < (bVar4 & 0xf0) |
                      (0xbf < bVar3 || CARRY1(bVar1,bVar2)) | in_AF * (0xf9 < bVar4)) * '`';
  return;
}



// Function: FUN_1000_2093

void __cdecl16near FUN_1000_2093(void)

{
  byte bVar1;
  byte bVar2;
  byte in_AL;
  byte bVar4;
  byte bVar5;
  char *unaff_DI;
  undefined2 unaff_ES;
  byte in_AF;
  byte bVar3;
  
  bVar2 = 9 < (in_AL + 0x90 & 0xf) | in_AF;
  bVar4 = in_AL + 0x90 + bVar2 * '\x06';
  bVar3 = 0x90 < (bVar4 & 0xf0) | 0x6f < in_AL | bVar2 * (0xf9 < bVar4);
  bVar4 = bVar4 + bVar3 * '`';
  bVar1 = bVar4 + 0x40;
  bVar5 = bVar1 + bVar3;
  bVar2 = 9 < (bVar5 & 0xf) | bVar2;
  bVar5 = bVar5 + bVar2 * '\x06';
  *unaff_DI = bVar5 + (0x90 < (bVar5 & 0xf0) |
                      (0xbf < bVar4 || CARRY1(bVar1,bVar3)) | bVar2 * (0xf9 < bVar5)) * '`';
  return;
}



// Function: FUN_1000_209b

void FUN_1000_209b(void)

{
  undefined2 unaff_SI;
  
  FUN_1000_20ff(unaff_SI);
  return;
}



// Function: FUN_1000_20b5

void __cdecl16near FUN_1000_20b5(void)

{
  char *pcVar1;
  int iVar2;
  char *unaff_DI;
  undefined2 unaff_ES;
  
  iVar2 = -1;
  do {
    if (iVar2 == 0) {
      return;
    }
    iVar2 = iVar2 + -1;
    pcVar1 = unaff_DI;
    unaff_DI = unaff_DI + 1;
  } while (*pcVar1 != '\0');
  return;
}



// Function: FUN_1000_20c2

void __cdecl16near FUN_1000_20c2(void)

{
  char *pcVar1;
  undefined in_AL;
  int iVar2;
  int unaff_BP;
  undefined *unaff_DI;
  undefined2 unaff_SS;
  
  *unaff_DI = in_AL;
  pcVar1 = (char *)(unaff_BP + -0x14);
  *pcVar1 = *pcVar1 + -1;
  if (*pcVar1 == '\0') {
    iVar2 = (**(code **)(unaff_BP + 0xe))
                      (*(undefined2 *)(unaff_BP + 10),*(undefined2 *)(unaff_BP + 0xc),
                       unaff_DI + (1 - (unaff_BP + -0x96)),unaff_BP + -0x96);
    if (iVar2 == 0) {
      *(undefined2 *)(unaff_BP + -0x16) = 1;
    }
    *(undefined2 *)(unaff_BP + -0x14) = 0x50;
    *(int *)(unaff_BP + -0x12) =
         (int)(unaff_DI + (1 - (unaff_BP + -0x96)) + *(int *)(unaff_BP + -0x12));
  }
  return;
}



// Function: FUN_1000_20cb

void __cdecl16near FUN_1000_20cb(void)

{
  int iVar1;
  int unaff_BP;
  int unaff_DI;
  int iVar2;
  undefined2 unaff_SS;
  
  iVar2 = unaff_DI - (unaff_BP + -0x96);
  iVar1 = (**(code **)(unaff_BP + 0xe))
                    (*(undefined2 *)(unaff_BP + 10),*(undefined2 *)(unaff_BP + 0xc),iVar2,
                     unaff_BP + -0x96);
  if (iVar1 == 0) {
    *(undefined2 *)(unaff_BP + -0x16) = 1;
  }
  *(undefined2 *)(unaff_BP + -0x14) = 0x50;
  *(int *)(unaff_BP + -0x12) = *(int *)(unaff_BP + -0x12) + iVar2;
  return;
}



// Function: FUN_1000_20ff

/* WARNING (jumptable): Unable to track spacebase fully for stack */

undefined2 FUN_1000_20ff(void)

{
  char *pcVar1;
  uint *puVar2;
  undefined *puVar3;
  char cVar4;
  undefined2 *puVar5;
  uint uVar6;
  int *piVar7;
  char cVar8;
  char cVar9;
  uint *puVar10;
  undefined2 uVar11;
  uint uVar12;
  byte bVar15;
  int iVar13;
  int iVar14;
  int extraout_DX;
  int extraout_DX_00;
  int extraout_DX_01;
  int iVar16;
  int unaff_BP;
  char *pcVar17;
  char *pcVar18;
  int *piVar19;
  undefined *puVar20;
  uint *puVar21;
  int *piVar22;
  undefined2 uVar23;
  char *pcVar24;
  char *unaff_SS;
  
  *(int *)(unaff_BP + -4) = unaff_BP + -0x96;
LAB_1000_2108:
  pcVar18 = *(char **)(unaff_BP + -4);
LAB_1000_210b:
  uVar23 = (undefined2)((ulong)*(char **)(unaff_BP + 6) >> 0x10);
  pcVar24 = (char *)*(char **)(unaff_BP + 6);
LAB_1000_210e:
  pcVar17 = pcVar24 + 1;
  cVar9 = *pcVar24;
  if (cVar9 == '\0') goto LAB_1000_250e;
  if (cVar9 == '%') {
    *(char **)(unaff_BP + -0x10) = pcVar17;
    pcVar1 = pcVar17;
    pcVar17 = pcVar24 + 2;
    cVar9 = *pcVar1;
    if (cVar9 != '%') goto code_r0x00012132;
  }
  *pcVar18 = cVar9;
  pcVar18 = pcVar18 + 1;
  pcVar1 = (char *)(unaff_BP + -0x14);
  cVar9 = *pcVar1;
  *pcVar1 = *pcVar1 + -1;
  pcVar24 = pcVar17;
  if (*pcVar1 == '\0' || SBORROW1(cVar9,'\x01') != *pcVar1 < '\0') {
    FUN_1000_20cb();
  }
  goto LAB_1000_210e;
code_r0x00012132:
  *(char **)(unaff_BP + -4) = pcVar18;
  uVar12 = 0;
  *(undefined2 *)(unaff_BP + -0xe) = 0;
  *(undefined2 *)(unaff_BP + -2) = 0x20;
  *(undefined *)(unaff_BP + -0xb) = 0;
  *(undefined2 *)(unaff_BP + -8) = 0xffff;
  *(undefined2 *)(unaff_BP + -10) = 0xffff;
  do {
    if (0x5f < (byte)(cVar9 - 0x20U)) goto switchD_1000_216c_caseD_13;
    cVar4 = *(char *)((byte)(cVar9 - 0x20U) + 0x224b);
    cVar8 = cVar4 * '\x02';
    bVar15 = (byte)(uVar12 >> 8);
    pcVar24 = unaff_SS;
    switch(cVar4) {
    case '\0':
      if (bVar15 != 0) goto switchD_1000_216c_caseD_13;
      if (*(char *)(unaff_BP + -0xb) != '+') {
        *(char *)(unaff_BP + -0xb) = cVar9;
      }
      break;
    case '\x01':
      if (bVar15 != 0) goto switchD_1000_216c_caseD_13;
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 1;
      break;
    case '\x02':
      iVar16 = **(int **)(unaff_BP + 4);
      *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 2;
      if (bVar15 < 2) {
        if (iVar16 < 0) {
          iVar16 = -iVar16;
          *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 2;
        }
        *(int *)(unaff_BP + -8) = iVar16;
        uVar12 = 0x300;
      }
      else {
        if (bVar15 != 4) goto switchD_1000_216c_caseD_13;
        *(int *)(unaff_BP + -10) = iVar16;
        uVar12 = 0x500;
      }
      break;
    case '\x03':
      if (bVar15 != 0) goto switchD_1000_216c_caseD_13;
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 2;
      break;
    case '\x04':
      if (3 < bVar15) goto switchD_1000_216c_caseD_13;
      uVar12 = 0x400;
      *(int *)(unaff_BP + -10) = *(int *)(unaff_BP + -10) + 1;
      break;
    case '\x05':
switchD_1000_216c_caseD_5:
      if (bVar15 < 3) {
        uVar12 = 0x200;
        LOCK();
        iVar16 = *(int *)(unaff_BP + -8);
        *(int *)(unaff_BP + -8) = (int)(char)(cVar9 + -0x30);
        UNLOCK();
        if (-1 < iVar16) {
          *(int *)(unaff_BP + -8) = *(int *)(unaff_BP + -8) + iVar16 * 10;
        }
      }
      else {
        if (bVar15 != 4) {
switchD_1000_216c_caseD_13:
          pcVar18 = *(char **)(unaff_BP + -0x10);
          uVar23 = *(undefined2 *)(unaff_BP + 8);
          do {
            FUN_1000_20c2();
            pcVar1 = pcVar18;
            pcVar18 = pcVar18 + 1;
          } while (*pcVar1 != '\0');
LAB_1000_250e:
          if (*(char *)(unaff_BP + -0x14) < 'P') {
            FUN_1000_20cb();
          }
          if (*(int *)(unaff_BP + -0x16) == 0) {
            uVar23 = *(undefined2 *)(unaff_BP + -0x12);
          }
          else {
            uVar23 = 0xffff;
          }
          return uVar23;
        }
        LOCK();
        iVar16 = *(int *)(unaff_BP + -10);
        *(int *)(unaff_BP + -10) = (int)(char)(cVar9 + -0x30);
        UNLOCK();
        if (iVar16 != 0) {
          *(int *)(unaff_BP + -10) = *(int *)(unaff_BP + -10) + iVar16 * 10;
        }
      }
      break;
    case '\x06':
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 0x10;
      goto LAB_1000_21a4;
    case '\a':
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 0x100;
    case '\b':
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) & 0xffef;
      goto LAB_1000_21a4;
    case '\t':
      if (bVar15 != 0) goto switchD_1000_216c_caseD_5;
      if ((*(uint *)(unaff_BP + -2) & 2) == 0) {
        *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 8;
        uVar12 = 0x100;
      }
      break;
    case '\n':
      goto switchD_1000_216c_caseD_a;
    case '\v':
      uVar23 = CONCAT11(8,cVar8);
      goto LAB_1000_2259;
    case '\f':
      uVar23 = CONCAT11(10,cVar8);
      goto LAB_1000_2259;
    case '\r':
      uVar23 = CONCAT11(0x10,cVar9 + -0x17);
LAB_1000_2259:
      *(undefined *)(unaff_BP + -0xb) = 0;
      *(char *)(unaff_BP + -5) = cVar9;
      iVar13 = 0;
      *(undefined *)(unaff_BP + -6) = 0;
      piVar22 = *(int **)(unaff_BP + 4);
      iVar16 = *piVar22;
      goto LAB_1000_227d;
    case '\x0e':
      *(char *)(unaff_BP + -5) = cVar9;
      *(char **)(unaff_BP + 6) = pcVar17;
      puVar20 = (undefined *)(unaff_BP + -0x46);
      puVar5 = (undefined2 *)*(int *)(unaff_BP + 4);
      uVar23 = *puVar5;
      *(undefined2 **)(unaff_BP + 4) = puVar5 + 1;
      if ((*(uint *)(unaff_BP + -2) & 0x20) != 0) {
        *(undefined2 **)(unaff_BP + 4) = puVar5 + 2;
        FUN_1000_2083(uVar23);
        puVar3 = puVar20;
        puVar20 = (undefined *)(unaff_BP + -0x45);
        *puVar3 = 0x3a;
      }
      FUN_1000_2083();
      *puVar20 = 0;
      *(undefined *)(unaff_BP + -6) = 0;
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) & 0xfffb;
      puVar21 = (uint *)(unaff_BP + -0x46);
      uVar12 = (int)puVar20 - (int)puVar21;
      goto LAB_1000_23be;
    case '\x0f':
      *(char **)(unaff_BP + 6) = pcVar17;
      *(char *)(unaff_BP + -5) = cVar9;
      uVar23 = *(undefined2 *)(unaff_BP + 4);
      uVar12 = *(uint *)(unaff_BP + -10);
      if ((int)uVar12 < 0) {
        uVar12 = 6;
      }
      uVar6 = *(uint *)(unaff_BP + -2);
      if ((*(uint *)(unaff_BP + -2) & 0x100) == 0) {
        *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 8;
        uVar11 = 6;
      }
      else {
        uVar11 = 8;
        *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 10;
      }
      thunk_FUN_1000_068f(uVar11,uVar6 & 1,cVar9,unaff_BP + -0x45,unaff_SS,uVar12,uVar23,unaff_SS);
      puVar21 = (uint *)(unaff_BP + -0x45);
      goto LAB_1000_23be;
    case '\x10':
      *(char **)(unaff_BP + 6) = pcVar17;
      *(char *)(unaff_BP + -5) = cVar9;
      uVar12 = **(uint **)(unaff_BP + 4);
      *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 2;
      puVar21 = (uint *)(unaff_BP + -0x45);
      *puVar21 = uVar12 & 0xff;
      uVar12 = 1;
      goto LAB_1000_2401;
    case '\x11':
      *(char **)(unaff_BP + 6) = pcVar17;
      *(char *)(unaff_BP + -5) = cVar9;
      if ((*(uint *)(unaff_BP + -2) & 0x20) == 0) {
                    /* WARNING: Load size is inaccurate */
        puVar21 = *(uint **)*(undefined2 *)(unaff_BP + 4);
        *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 2;
        pcVar24 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
        puVar10 = puVar21;
      }
      else {
        puVar2 = *(uint **)*(undefined2 *)(unaff_BP + 4);
        pcVar24 = (char *)((ulong)puVar2 >> 0x10);
        puVar21 = (uint *)puVar2;
        *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 4;
        puVar10 = (uint *)((uint)pcVar24 | (uint)puVar21);
      }
      if (puVar10 == (uint *)0x0) {
        pcVar24 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
        puVar21 = (uint *)0x2244;
      }
      FUN_1000_20b5();
      if (*(uint *)(unaff_BP + -10) < uVar12) {
        uVar12 = *(uint *)(unaff_BP + -10);
      }
      goto LAB_1000_2401;
    case '\x12':
      *(char **)(unaff_BP + 6) = pcVar17;
      if ((*(uint *)(unaff_BP + -2) & 0x20) == 0) {
                    /* WARNING: Load size is inaccurate */
        piVar22 = *(int **)*(undefined2 *)(unaff_BP + 4);
        *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 2;
        pcVar18 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
      }
      else {
        piVar7 = *(int **)*(undefined2 *)(unaff_BP + 4);
        pcVar18 = (char *)((ulong)piVar7 >> 0x10);
        piVar22 = (int *)piVar7;
        *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 4;
      }
      *piVar22 = (uint)(byte)(0x50 - *(char *)(unaff_BP + -0x14)) + *(int *)(unaff_BP + -0x12);
      if ((*(uint *)(unaff_BP + -2) & 0x10) != 0) {
        piVar22[1] = 0;
      }
      goto LAB_1000_2108;
    default:
      goto switchD_1000_216c_caseD_13;
    case '\x16':
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) & 0xffdf;
      goto LAB_1000_21a4;
    case '\x17':
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 0x20;
LAB_1000_21a4:
      uVar12 = 0x500;
    }
    pcVar1 = pcVar17;
    pcVar17 = pcVar17 + 1;
    cVar9 = *pcVar1;
  } while( true );
switchD_1000_216c_caseD_a:
  uVar23 = CONCAT11(10,cVar8);
  *(undefined *)(unaff_BP + -6) = 1;
  *(char *)(unaff_BP + -5) = cVar9;
  piVar22 = *(int **)(unaff_BP + 4);
  iVar16 = *piVar22;
  iVar13 = iVar16 >> 0xf;
LAB_1000_227d:
  piVar19 = piVar22 + 1;
  *(char **)(unaff_BP + 6) = pcVar17;
  if ((*(uint *)(unaff_BP + -2) & 0x10) != 0) {
    iVar13 = *piVar19;
    piVar19 = piVar22 + 2;
  }
  *(int **)(unaff_BP + 4) = piVar19;
  puVar21 = (uint *)(unaff_BP + -0x45);
  if ((iVar16 == 0) && (iVar13 == 0)) {
    if (*(int *)(unaff_BP + -10) != 0) goto LAB_1000_22ae;
    *(char *)puVar21 = '\0';
  }
  else {
    *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 4;
LAB_1000_22ae:
    FUN_1000_3faf(uVar23,*(undefined *)(unaff_BP + -6),(char)((uint)uVar23 >> 8),puVar21,unaff_SS,
                  iVar16,iVar13);
  }
  if (*(int *)(unaff_BP + -10) < 0) {
LAB_1000_23be:
    if (((*(uint *)(unaff_BP + -2) & 8) != 0) && (0 < *(int *)(unaff_BP + -8))) goto LAB_1000_23cc;
  }
  else {
LAB_1000_23cc:
    FUN_1000_20b5();
    if (*(char *)puVar21 == '-') {
      uVar12 = uVar12 - 1;
    }
    if (extraout_DX - uVar12 != 0 && (int)uVar12 <= extraout_DX) {
      *(int *)(unaff_BP + -0xe) = extraout_DX - uVar12;
    }
  }
  if (*(char *)puVar21 != '-') {
    if (*(char *)(unaff_BP + -0xb) == '\0') goto LAB_1000_23fe;
    puVar21 = (uint *)((int)puVar21 + -1);
    *(char *)puVar21 = *(char *)(unaff_BP + -0xb);
  }
  if ((0 < *(int *)(unaff_BP + -0xe)) && (uVar12 = *(uint *)(unaff_BP + -10), (int)uVar12 < 0)) {
    *(int *)(unaff_BP + -0xe) = *(int *)(unaff_BP + -0xe) + -1;
  }
LAB_1000_23fe:
  FUN_1000_20b5();
LAB_1000_2401:
  pcVar18 = *(char **)(unaff_BP + -4);
  iVar16 = *(int *)(unaff_BP + -8);
  if ((*(uint *)(unaff_BP + -2) & 5) == 5) {
    cVar9 = *(char *)(unaff_BP + -5);
    if (cVar9 == 'o') {
      if (*(int *)(unaff_BP + -0xe) < 1) {
        *(undefined2 *)(unaff_BP + -0xe) = 1;
      }
    }
    else if ((cVar9 == 'x') || (cVar9 == 'X')) {
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 0x40;
      iVar16 = iVar16 + -2;
      piVar7 = (int *)(unaff_BP + -0xe);
      iVar13 = *piVar7;
      *piVar7 = *piVar7 + -2;
      if (SBORROW2(iVar13,2) != *piVar7 < 0) {
        *(undefined2 *)(unaff_BP + -0xe) = 0;
      }
    }
  }
  iVar13 = uVar12 + *(int *)(unaff_BP + -0xe);
  if ((*(uint *)(unaff_BP + -2) & 2) == 0) {
    for (; iVar13 < iVar16; iVar16 = iVar16 + -1) {
      FUN_1000_20c2();
    }
  }
  if ((*(uint *)(unaff_BP + -2) & 0x40) != 0) {
    FUN_1000_20c2();
    FUN_1000_20c2();
  }
  iVar14 = *(int *)(unaff_BP + -0xe);
  if (0 < iVar14) {
    iVar13 = iVar13 - iVar14;
    iVar16 = iVar16 - iVar14;
    cVar9 = *(char *)puVar21;
    if (((cVar9 == '-') || (cVar9 == ' ')) || (cVar9 == '+')) {
      puVar21 = (uint *)((int)puVar21 + 1);
      FUN_1000_20c2();
      iVar13 = iVar13 + -1;
      iVar16 = iVar16 + -1;
      iVar14 = extraout_DX_00;
    }
    for (; iVar14 != 0; iVar14 = iVar14 + -1) {
      FUN_1000_20c2();
      iVar13 = extraout_DX_01;
    }
  }
  if (iVar13 != 0) {
    iVar16 = iVar16 - iVar13;
    do {
      puVar2 = puVar21;
      puVar21 = (uint *)((int)puVar21 + 1);
      *pcVar18 = *(char *)puVar2;
      pcVar18 = pcVar18 + 1;
      pcVar1 = (char *)(unaff_BP + -0x14);
      cVar9 = *pcVar1;
      *pcVar1 = *pcVar1 + -1;
      if (*pcVar1 == '\0' || SBORROW1(cVar9,'\x01') != *pcVar1 < '\0') {
        FUN_1000_20cb();
      }
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
  }
  if (0 < iVar16) {
    do {
      FUN_1000_20c2();
      iVar16 = iVar16 + -1;
    } while (iVar16 != 0);
  }
  goto LAB_1000_210b;
}



// Function: FUN_1000_255e

void __cdecl16far FUN_1000_255e(uint param_1)

{
  if (param_1 < DAT_28d3_2174) {
    *(undefined2 *)(param_1 * 2 + 0x2176) = 0;
    FUN_1000_37d5(param_1);
  }
  else {
    FUN_1000_1f84(6);
  }
  return;
}



// Function: FUN_1000_258a

undefined2 __cdecl16far FUN_1000_258a(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 local_4;
  
  local_4 = 0xffff;
  if ((((uint)(int *)param_1 | param_1._2_2_) != 0) &&
     ((int *)((int *)param_1)[9] == (int *)param_1)) {
    if (((int *)param_1)[3] != 0) {
      if ((*param_1 < 0) && (iVar1 = FUN_1000_264b((int *)param_1,param_1._2_2_), iVar1 != 0)) {
        return 0xffff;
      }
      if ((((int *)param_1)[1] & 4U) != 0) {
        FUN_1000_4648(((int *)param_1)[4],((int *)param_1)[5]);
      }
    }
    if (-1 < *(char *)((int *)param_1 + 2)) {
      local_4 = FUN_1000_255e((int)*(char *)((int *)param_1 + 2));
    }
    ((int *)param_1)[1] = 0;
    ((int *)param_1)[3] = 0;
    *param_1 = 0;
    *(undefined *)((int *)param_1 + 2) = 0xff;
    if (((int *)param_1)[8] != 0) {
      uVar2 = FUN_1000_1d65(((int *)param_1)[8],0,0,0,0);
      FUN_1000_2067(uVar2);
      ((int *)param_1)[8] = 0;
    }
  }
  return local_4;
}



// Function: FUN_1000_264b

undefined2 __cdecl16far FUN_1000_264b(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (((uint)(int *)param_1 | param_1._2_2_) == 0) {
    FUN_1000_2820();
  }
  else {
    if ((int *)((int *)param_1)[9] != (int *)param_1) {
      return 0xffff;
    }
    if (*param_1 < 0) {
      iVar2 = ((int *)param_1)[3] + *param_1 + 1;
      *param_1 = *param_1 - iVar2;
      iVar3 = ((int *)param_1)[5];
      iVar1 = ((int *)param_1)[4];
      ((int *)param_1)[7] = iVar3;
      ((int *)param_1)[6] = iVar1;
      iVar3 = FUN_1000_35b7((int)*(char *)((int *)param_1 + 2),iVar1,iVar3,iVar2);
      if ((iVar3 != iVar2) && ((((int *)param_1)[1] & 0x200U) == 0)) {
        ((int *)param_1)[1] = ((int *)param_1)[1] | 0x10;
        return 0xffff;
      }
    }
    else if (((((int *)param_1)[1] & 8U) != 0) ||
            ((((int *)param_1)[7] == param_1._2_2_ &&
             (((int *)param_1)[6] == (int)(int *)param_1 + 5)))) {
      *param_1 = 0;
      if ((((int *)param_1)[7] == param_1._2_2_) && (((int *)param_1)[6] == (int)(int *)param_1 + 5)
         ) {
        iVar3 = ((int *)param_1)[4];
        ((int *)param_1)[7] = ((int *)param_1)[5];
        ((int *)param_1)[6] = iVar3;
      }
    }
  }
  return 0;
}



// Function: FUN_1000_2726

undefined * __cdecl16far FUN_1000_2726(undefined *param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  undefined2 uVar4;
  undefined4 local_6;
  
  uVar3 = 0;
  local_6 = (undefined *)CONCAT22(param_2,param_1);
  while( true ) {
    uVar4 = (undefined2)((ulong)param_4 >> 0x10);
    if ((uVar3 == 10) || (param_3 + -1 == 0 || param_3 < 1)) break;
    iVar1 = *param_4;
    *param_4 = *param_4 + -1;
    if (SBORROW2(iVar1,1) == *param_4 < 0) {
      iVar1 = ((int *)param_4)[7];
      pbVar2 = (byte *)((int *)param_4)[6];
      ((int *)param_4)[6] = ((int *)param_4)[6] + 1;
      uVar3 = (uint)*pbVar2;
    }
    else {
      uVar3 = FUN_1000_39af((int *)param_4,uVar4);
    }
    if (uVar3 == 0xffff) break;
    *local_6 = (char)uVar3;
    local_6 = (undefined *)CONCAT22(local_6._2_2_,(undefined *)local_6 + 1);
    param_3 = param_3 + -1;
  }
  if (((uVar3 == 0xffff) && (local_6._2_2_ == param_2)) && ((undefined *)local_6 == param_1)) {
    param_1 = (undefined *)0x0;
  }
  else {
    *local_6 = 0;
    if ((((int *)param_4)[1] & 0x10U) != 0) {
      param_1 = (undefined *)0x0;
    }
  }
  return param_1;
}



// Function: FUN_1000_27c4

int __cdecl16far FUN_1000_27c4(void)

{
  int *piVar1;
  undefined2 uVar2;
  int local_a;
  int local_8;
  int *local_6;
  
  local_a = 0;
  local_8 = DAT_28d3_2174;
  local_6 = (int *)0x28d31d8c;
  while (local_8 != 0) {
    uVar2 = (undefined2)((ulong)local_6 >> 0x10);
    piVar1 = (int *)local_6;
    if (((piVar1[1] & 3U) != 0) && (*local_6 != 0)) {
      FUN_1000_264b(piVar1,uVar2);
      local_a = local_a + 1;
    }
    local_6 = (int *)CONCAT22(uVar2,piVar1 + 10);
    local_8 = local_8 + -1;
  }
  return local_a;
}



// Function: FUN_1000_2820

int __cdecl16far FUN_1000_2820(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined2 uVar5;
  int local_a;
  int local_8;
  int *local_6;
  
  local_a = 0;
  local_8 = DAT_28d3_2174;
  local_6 = (int *)0x28d31d8c;
  while (local_8 != 0) {
    uVar5 = (undefined2)((ulong)local_6 >> 0x10);
    piVar4 = (int *)local_6;
    if (*local_6 < 0) {
      iVar2 = piVar4[3] + *local_6 + 1;
      *local_6 = *local_6 - iVar2;
      iVar3 = piVar4[5];
      iVar1 = piVar4[4];
      piVar4[7] = iVar3;
      piVar4[6] = iVar1;
      iVar3 = FUN_1000_35b7((int)*(char *)(piVar4 + 2),iVar1,iVar3,iVar2);
      if (iVar3 != iVar2) {
        if ((piVar4[1] & 0x200U) == 0) {
          piVar4[1] = piVar4[1] | 0x10;
        }
      }
      local_a = local_a + 1;
    }
    local_6 = (int *)CONCAT22(uVar5,piVar4 + 10);
    local_8 = local_8 + -1;
  }
  return local_a;
}



// Function: FUN_1000_28a9

uint FUN_1000_28a9(undefined2 *param_1,uint *param_2,char *param_3)

{
  char *pcVar1;
  char *pcVar2;
  uint uVar3;
  char cVar4;
  uint local_6;
  undefined2 local_4;
  
  pcVar2 = param_3;
  local_4 = 0;
  pcVar1 = (char *)param_3;
  param_3 = (char *)CONCAT22(param_3._2_2_,(char *)param_3 + 1);
  cVar4 = *pcVar2;
  if (cVar4 == 'r') {
    uVar3 = 1;
    local_6 = 1;
LAB_1000_28eb:
    cVar4 = *param_3;
    param_3 = (char *)CONCAT22(param_3._2_2_,pcVar1 + 2);
    if ((cVar4 == '+') || ((*param_3 == '+' && ((cVar4 == 't' || (cVar4 == 'b')))))) {
      if (cVar4 == '+') {
        cVar4 = *param_3;
      }
      uVar3 = uVar3 & 0xfffc | 4;
      local_4 = 0x180;
      local_6 = 3;
    }
    if (cVar4 == 't') {
      uVar3 = uVar3 | 0x4000;
    }
    else {
      if (cVar4 == 'b') {
        uVar3 = uVar3 | 0x8000;
      }
      else {
        if ((cVar4 != '+') && (cVar4 != '\0')) goto LAB_1000_2946;
        uVar3 = uVar3 | DAT_28d3_21da & 0xc000;
        if ((DAT_28d3_21da & 0x8000) == 0) goto LAB_1000_295d;
      }
      local_6 = local_6 | 0x40;
    }
LAB_1000_295d:
    DAT_28d3_2716 = 0x1000;
    DAT_28d3_2714 = 0x3721;
    *param_2 = uVar3;
    *param_1 = local_4;
  }
  else {
    if (cVar4 == 'w') {
      uVar3 = 0x302;
LAB_1000_28e1:
      local_4 = 0x80;
      local_6 = 2;
      goto LAB_1000_28eb;
    }
    if (cVar4 == 'a') {
      uVar3 = 0x902;
      goto LAB_1000_28e1;
    }
LAB_1000_2946:
    local_6 = 0;
  }
  return local_6;
}



// Function: FUN_1000_2983

undefined4
FUN_1000_2983(uint param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5,undefined4 param_6)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined2 local_6;
  uint local_4;
  
  iVar2 = FUN_1000_28a9(&local_6,unaff_SS,&local_4,unaff_SS,param_2,param_3);
  uVar4 = (undefined2)((ulong)param_6 >> 0x10);
  iVar3 = (int)param_6;
  *(int *)(iVar3 + 2) = iVar2;
  if (iVar2 == 0) {
LAB_1000_29d3:
    *(undefined *)(iVar3 + 4) = 0xff;
    *(undefined2 *)(iVar3 + 2) = 0;
  }
  else {
    if (*(char *)(iVar3 + 4) < '\0') {
      cVar1 = FUN_1000_3b14(param_4,param_5,local_4 | param_1,local_6);
      *(char *)(iVar3 + 4) = cVar1;
      if (cVar1 < '\0') goto LAB_1000_29d3;
    }
    iVar2 = FUN_1000_1fd6((int)*(char *)(iVar3 + 4));
    if (iVar2 != 0) {
      *(uint *)(iVar3 + 2) = *(uint *)(iVar3 + 2) | 0x200;
    }
    iVar2 = FUN_1000_3492(iVar3,uVar4,0,0,(*(uint *)(iVar3 + 2) & 0x200) != 0,0x200);
    if (iVar2 == 0) {
      *(undefined2 *)(iVar3 + 0x10) = 0;
      goto LAB_1000_2a4e;
    }
    FUN_1000_258a(iVar3,uVar4);
  }
  uVar4 = 0;
  iVar3 = 0;
LAB_1000_2a4e:
  return CONCAT22(uVar4,iVar3);
}



// Function: FUN_1000_2a56

undefined4 __cdecl16near FUN_1000_2a56(void)

{
  uint uVar1;
  bool bVar2;
  uint local_6;
  char *local_4;
  
  local_4 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  local_6 = 0x1d8c;
  do {
    if (*(char *)(local_6 + 4) < '\0') break;
    uVar1 = local_6 + 0x14;
    bVar2 = local_6 < DAT_28d3_2174 * 0x14 + 0x1d8cU;
    local_6 = uVar1;
  } while (bVar2);
  if (-1 < *(char *)(local_6 + 4)) {
    local_4 = (char *)0x0;
    local_6 = 0;
  }
  return CONCAT22(local_4,local_6);
}



// Function: FUN_1000_2aa3

undefined2 __cdecl16far
FUN_1000_2aa3(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  undefined2 uVar1;
  long lVar2;
  
  lVar2 = FUN_1000_2a56();
  if (lVar2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_1000_2983(0,param_3,param_4,param_1,param_2,lVar2);
  }
  return uVar1;
}



// Function: FUN_1000_2adc

void __cdecl16far
FUN_1000_2adc(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  FUN_1000_209b(&stack0x000c,param_3,param_4,param_1,param_2,0x321f);
  return;
}



// Function: FUN_1000_2afc

uint __cdecl16far FUN_1000_2afc(undefined4 param_1,undefined2 param_3,undefined2 param_4)

{
  int iVar1;
  int iVar2;
  
  if ((((uint)param_1 | param_1._2_2_) != 0) &&
     (iVar1 = FUN_1000_1c56((uint)param_1,param_1._2_2_), iVar1 != 0)) {
    iVar2 = FUN_1000_321f(param_3,param_4,iVar1,(uint)param_1,param_1._2_2_);
    if (iVar2 != 0) {
      return (uint)*(byte *)((uint)param_1 + iVar1 + -1);
    }
    return 0xffff;
  }
  return 0;
}



// Function: FUN_1000_2b51

uint FUN_1000_2b51(int *param_1,uint param_2,undefined *param_3)

{
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  uint in_DX;
  int *piVar4;
  undefined2 uVar5;
  uint local_4;
  
  do {
    while( true ) {
      if (param_2 == 0) {
        return 0;
      }
      uVar1 = param_2 + 1;
      uVar5 = (undefined2)((ulong)param_1 >> 0x10);
      piVar4 = (int *)param_1;
      local_4 = uVar1;
      if ((uint)piVar4[3] <= uVar1) {
        local_4 = piVar4[3];
      }
      if (((((piVar4[1] & 0x40U) != 0) && (piVar4[3] != 0)) && ((uint)piVar4[3] < uVar1)) &&
         (*param_1 == 0)) break;
      while ((param_2 = uVar1, param_2 = param_2 - 1, param_2 != 0 &&
             (local_4 = local_4 - 1, local_4 != 0))) {
        iVar2 = *param_1;
        *param_1 = *param_1 + -1;
        if (SBORROW2(iVar2,1) == *param_1 < 0) {
          iVar2 = piVar4[7];
          pbVar3 = (byte *)piVar4[6];
          piVar4[6] = piVar4[6] + 1;
          in_DX = (uint)*pbVar3;
        }
        else {
          in_DX = FUN_1000_39af(piVar4,uVar5);
        }
        if (in_DX == 0xffff) break;
        *param_3 = (char)in_DX;
        param_3 = (undefined *)CONCAT22(param_3._2_2_,(undefined *)param_3 + 1);
        uVar1 = param_2;
      }
      if (in_DX == 0xffff) goto LAB_1000_2c01;
    }
    local_4 = 0;
    for (; (uint)piVar4[3] <= param_2; param_2 = param_2 - piVar4[3]) {
      local_4 = local_4 + piVar4[3];
    }
    in_DX = FUN_1000_2018((int)*(char *)(piVar4 + 2),(undefined *)param_3,param_3._2_2_,local_4);
    if (in_DX == 0xffff) {
      in_DX = 0;
      piVar4[1] = piVar4[1] | 0x10;
    }
    param_3 = (undefined *)CONCAT22(param_3._2_2_,(undefined *)param_3 + in_DX);
  } while (in_DX == local_4);
  param_2 = param_2 + (local_4 - in_DX);
LAB_1000_2c01:
  piVar4[1] = piVar4[1] | 0x20;
  return param_2;
}



// Function: FUN_1000_2c70

uint __cdecl16far
FUN_1000_2c70(undefined2 param_1,undefined2 param_2,uint param_3,int param_4,undefined2 param_5,
             undefined2 param_6)

{
  int iVar1;
  ulong uVar2;
  int local_4;
  
  if (param_3 == 0) {
    param_3 = 0;
  }
  else {
    uVar2 = FUN_1000_3f98();
    if ((uVar2 < 0x20000) && ((int)(uVar2 >> 0x10) == 0)) {
      iVar1 = FUN_1000_2b51(param_5,param_6,(int)uVar2,param_1,param_2);
      param_3 = (uint)((int)uVar2 - iVar1) / param_3;
    }
    else {
      local_4 = param_4 + 1;
      while ((local_4 = local_4 + -1, local_4 != 0 &&
             (iVar1 = FUN_1000_2b51(param_5,param_6,param_3,param_1,param_2), iVar1 == 0))) {
        param_1 = FUN_1000_4b26();
      }
      param_3 = param_4 - local_4;
    }
  }
  return param_3;
}



// Function: FUN_1000_2d0a

int FUN_1000_2d0a(uint *param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  undefined2 uVar6;
  undefined4 local_8;
  int local_4;
  
  uVar6 = (undefined2)((ulong)param_1 >> 0x10);
  puVar5 = (uint *)param_1;
  if ((int)*param_1 < 0) {
    iVar2 = puVar5[3] + *param_1 + 1;
  }
  else {
    uVar4 = (int)*param_1 >> 0xf;
    iVar2 = (*param_1 ^ uVar4) - uVar4;
  }
  local_4 = iVar2;
  if ((puVar5[1] & 0x40) == 0) {
    local_8 = (char *)CONCAT22(puVar5[7],(char *)puVar5[6]);
    if ((int)*param_1 < 0) {
      while (iVar3 = iVar2 + -1, iVar2 != 0) {
        local_8 = (char *)CONCAT22(local_8._2_2_,(char *)local_8 + -1);
        iVar2 = iVar3;
        if (*local_8 == '\n') {
          local_4 = local_4 + 1;
        }
      }
    }
    else {
      while (pcVar1 = local_8, iVar3 = iVar2 + -1, iVar2 != 0) {
        local_8 = (char *)CONCAT22(local_8._2_2_,(char *)local_8 + 1);
        iVar2 = iVar3;
        if (*pcVar1 == '\n') {
          local_4 = local_4 + 1;
        }
      }
    }
  }
  return local_4;
}



// Function: FUN_1000_2d94

undefined2 __cdecl16far FUN_1000_2d94(int *param_1,uint param_3,int param_4,int param_5)

{
  int iVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  
  iVar1 = FUN_1000_264b((int *)param_1,param_1._2_2_);
  if (iVar1 == 0) {
    if ((param_5 == 1) && (0 < *param_1)) {
      uVar3 = FUN_1000_2d0a((int *)param_1,param_1._2_2_);
      bVar5 = param_3 < uVar3;
      param_3 = param_3 - uVar3;
      param_4 = (param_4 - ((int)uVar3 >> 0xf)) - (uint)bVar5;
    }
    ((int *)param_1)[1] = ((int *)param_1)[1] & 0xfe5f;
    *param_1 = 0;
    iVar1 = ((int *)param_1)[5];
    iVar4 = ((int *)param_1)[4];
    ((int *)param_1)[7] = iVar1;
    ((int *)param_1)[6] = iVar4;
    iVar4 = FUN_1000_1feb((int)*(char *)((int *)param_1 + 2),param_3,param_4,param_5);
    if ((iVar1 == -1) && (iVar4 == -1)) {
      uVar2 = 0xffff;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0xffff;
  }
  return uVar2;
}



// Function: FUN_1000_2e19

int __cdecl16far FUN_1000_2e19(int *param_1)

{
  int iVar1;
  int iVar2;
  int in_DX;
  int *piVar3;
  undefined2 uVar4;
  int local_6;
  
  uVar4 = (undefined2)((ulong)param_1 >> 0x10);
  piVar3 = (int *)param_1;
  iVar1 = FUN_1000_1feb((int)*(char *)(piVar3 + 2),0,0,1);
  if ((in_DX == -1) && (iVar1 == -1)) {
    iVar1 = -1;
  }
  else if (*param_1 < 0) {
    local_6 = iVar1;
    if ((*(uint *)(*(char *)(piVar3 + 2) * 2 + 0x2176) & 0x800) != 0) {
      iVar2 = in_DX;
      local_6 = FUN_1000_1feb((int)*(char *)(piVar3 + 2),0,0,2);
      if ((iVar2 == -1) && (local_6 == -1)) {
        return -1;
      }
      iVar1 = FUN_1000_1feb((int)*(char *)(piVar3 + 2),iVar1,in_DX,0);
      if ((iVar2 == -1) && (iVar1 == -1)) {
        return -1;
      }
    }
    iVar1 = FUN_1000_2d0a(piVar3,uVar4);
    iVar1 = local_6 + iVar1;
  }
  else {
    iVar2 = FUN_1000_2d0a(piVar3,uVar4);
    iVar1 = iVar1 - iVar2;
  }
  return iVar1;
}



// Function: FUN_1000_2efb

uint __cdecl16far
FUN_1000_2efb(undefined2 param_1,undefined2 param_2,uint param_3,uint param_4,undefined2 param_5,
             undefined2 param_6)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  uint local_4;
  
  uVar1 = param_4;
  if (param_3 != 0) {
    uVar3 = FUN_1000_3f98();
    if ((uVar3 < 0x20000) && ((int)(uVar3 >> 0x10) == 0)) {
      uVar1 = FUN_1000_321f(param_5,param_6,(int)uVar3,param_1,param_2);
      uVar1 = uVar1 / param_3;
    }
    else {
      local_4 = 0;
      while ((uVar1 = param_4, local_4 < param_4 &&
             (uVar2 = FUN_1000_321f(param_5,param_6,param_3,param_1,param_2), uVar1 = local_4,
             uVar2 == param_3))) {
        param_1 = FUN_1000_4b26();
        local_4 = local_4 + 1;
      }
    }
  }
  return uVar1;
}



// Function: FUN_1000_2f94

void __cdecl16far FUN_1000_2f94(char *param_1)

{
  undefined2 local_6;
  char *local_4;
  
  if ((DAT_28d3_007e < iRam0002b09c) && (-1 < DAT_28d3_007e)) {
    local_4 = *(char **)(DAT_28d3_007e * 4 + 0x22ae);
    local_6 = *(undefined2 *)(DAT_28d3_007e * 4 + 0x22ac);
  }
  else {
    local_4 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    local_6 = 0x2569;
  }
  if ((((uint)(char *)param_1 | param_1._2_2_) != 0) && (*param_1 != '\0')) {
    FUN_1000_2afc((char *)param_1,param_1._2_2_,0x1db4,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7);
    FUN_1000_2afc(0x2577,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0x1db4,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  FUN_1000_2afc(local_6,local_4,0x1db4,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_1000_2afc(0x257a,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0x1db4,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  return;
}



// Function: FUN_1000_302b

void __cdecl16far FUN_1000_302b(undefined2 param_1,undefined2 param_2)

{
  FUN_1000_209b(&stack0x0008,param_1,param_2,0x1da0,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7,0x321f);
  return;
}



// Function: FUN_1000_304a

void __cdecl16far FUN_1000_304a(char param_1,int *param_2)

{
  *param_2 = *param_2 + -1;
  FUN_1000_306c((int)param_1,(int *)param_2,param_2._2_2_);
  return;
}



// Function: FUN_1000_306c

uint __cdecl16far FUN_1000_306c(byte param_1,int *param_2)

{
  byte *pbVar1;
  int iVar2;
  undefined2 uVar3;
  
  DAT_28d3_5824 = param_1;
  uVar3 = (undefined2)((ulong)param_2 >> 0x10);
  if (*param_2 < -1) {
    *param_2 = *param_2 + 1;
    iVar2 = ((int *)param_2)[7];
    pbVar1 = (byte *)((int *)param_2)[6];
    ((int *)param_2)[6] = ((int *)param_2)[6] + 1;
    *pbVar1 = DAT_28d3_5824;
    if (((((int *)param_2)[1] & 8U) == 0) || ((DAT_28d3_5824 != 10 && (DAT_28d3_5824 != 0xd))))
    goto LAB_1000_31fe;
    iVar2 = FUN_1000_264b((int *)param_2,uVar3);
  }
  else {
    if (((((int *)param_2)[1] & 0x90U) != 0) || ((((int *)param_2)[1] & 2U) == 0)) {
      ((int *)param_2)[1] = ((int *)param_2)[1] | 0x10;
      return 0xffff;
    }
    ((int *)param_2)[1] = ((int *)param_2)[1] | 0x100;
    if (((int *)param_2)[3] == 0) {
      if ((*(uint *)(*(char *)((int *)param_2 + 2) * 2 + 0x2176) & 0x800) != 0) {
        FUN_1000_1feb((int)*(char *)((int *)param_2 + 2),0,0,2);
      }
      if (((((DAT_28d3_5824 == 10) && ((((int *)param_2)[1] & 0x40U) == 0)) &&
           (iVar2 = FUN_1000_3df9((int)*(char *)((int *)param_2 + 2),0x257c,
                                  (char *)s_String_reference_out_of_range_28d3_28cc + 7,1),
           iVar2 != 1)) ||
          (iVar2 = FUN_1000_3df9((int)*(char *)((int *)param_2 + 2),(undefined1 *)&DAT_28d3_5824,
                                 (char *)s_String_reference_out_of_range_28d3_28cc + 7,1),
          iVar2 != 1)) && ((((int *)param_2)[1] & 0x200U) == 0)) {
        ((int *)param_2)[1] = ((int *)param_2)[1] | 0x10;
        return 0xffff;
      }
      goto LAB_1000_31fe;
    }
    if ((*param_2 != 0) && (iVar2 = FUN_1000_264b((int *)param_2,uVar3), iVar2 != 0)) {
      return 0xffff;
    }
    *param_2 = -((int *)param_2)[3];
    iVar2 = ((int *)param_2)[7];
    pbVar1 = (byte *)((int *)param_2)[6];
    ((int *)param_2)[6] = ((int *)param_2)[6] + 1;
    *pbVar1 = DAT_28d3_5824;
    if (((((int *)param_2)[1] & 8U) == 0) || ((DAT_28d3_5824 != 10 && (DAT_28d3_5824 != 0xd))))
    goto LAB_1000_31fe;
    iVar2 = FUN_1000_264b((int *)param_2,uVar3);
  }
  if (iVar2 != 0) {
    return 0xffff;
  }
LAB_1000_31fe:
  return (uint)DAT_28d3_5824;
}



// Function: FUN_1000_3207

void __cdecl16far FUN_1000_3207(undefined2 param_1)

{
  FUN_1000_306c(param_1,0x1da0,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  return;
}



// Function: FUN_1000_321f

/* WARNING: Type propagation algorithm not settling */

uint FUN_1000_321f(int *param_1,uint param_2,byte *param_3)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  undefined2 uVar8;
  
  uVar6 = param_2;
  uVar8 = (undefined2)((ulong)param_1 >> 0x10);
  piVar7 = (int *)param_1;
  if ((piVar7[1] & 8U) == 0) {
    if ((piVar7[1] & 0x40U) == 0) {
      if (piVar7[3] != 0) {
        do {
          if (param_2 == 0) {
            return uVar6;
          }
          iVar4 = *param_1;
          *param_1 = *param_1 + 1;
          if (SCARRY2(iVar4,1) == *param_1 < 0) {
            uVar5 = FUN_1000_304a(*param_3,piVar7,uVar8);
          }
          else {
            iVar4 = piVar7[7];
            pbVar2 = (byte *)piVar7[6];
            piVar7[6] = piVar7[6] + 1;
            bVar1 = *param_3;
            *pbVar2 = bVar1;
            uVar5 = (uint)bVar1;
          }
          param_3 = (byte *)CONCAT22(param_3._2_2_,(byte *)param_3 + 1);
          param_2 = param_2 - 1;
        } while (uVar5 != 0xffff);
        return 0;
      }
      uVar6 = FUN_1000_35b7((int)*(char *)(piVar7 + 2),(byte *)param_3,param_3._2_2_,param_2);
    }
    else if (piVar7[3] == 0) {
      if ((*(uint *)(*(char *)(piVar7 + 2) * 2 + 0x2176) & 0x800) != 0) {
        FUN_1000_1feb((int)*(char *)(piVar7 + 2),0,0,2);
      }
      uVar6 = FUN_1000_3df9((int)*(char *)(piVar7 + 2),(byte *)param_3,param_3._2_2_,param_2);
    }
    else {
      if (param_2 <= (uint)piVar7[3]) {
        if (SCARRY2(*param_1,param_2) == (int)(*param_1 + param_2) < 0) {
          if (*param_1 == 0) {
            *param_1 = -1 - piVar7[3];
          }
          else {
            iVar4 = FUN_1000_264b(piVar7,uVar8);
            if (iVar4 != 0) {
              return 0;
            }
          }
        }
        FUN_1000_1a99(piVar7[6],piVar7[7],(byte *)param_3,param_3._2_2_,param_2);
        *param_1 = *param_1 + param_2;
        piVar7[6] = piVar7[6] + param_2;
        return param_2;
      }
      if ((*param_1 != 0) && (iVar4 = FUN_1000_264b(piVar7,uVar8), iVar4 != 0)) {
        return 0;
      }
      if ((*(uint *)(*(char *)(piVar7 + 2) * 2 + 0x2176) & 0x800) != 0) {
        FUN_1000_1feb((int)*(char *)(piVar7 + 2),0,0,2);
      }
      uVar6 = FUN_1000_3df9((int)*(char *)(piVar7 + 2),(byte *)param_3,param_3._2_2_,param_2);
    }
    if (uVar6 == param_2) {
      return param_2;
    }
  }
  else {
    do {
      pbVar3 = param_3;
      if (param_2 == 0) {
        return uVar6;
      }
      param_3 = (byte *)CONCAT22(param_3._2_2_,(byte *)param_3 + 1);
      iVar4 = FUN_1000_306c((int)(char)*pbVar3,piVar7,uVar8);
      param_2 = param_2 - 1;
    } while (iVar4 != -1);
  }
  return 0;
}



// Function: FUN_1000_3431

undefined2 __cdecl16far FUN_1000_3431(uint param_1,uint param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  
  if ((param_1 | param_2) == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_1000_1c56(param_1,param_2);
    iVar3 = FUN_1000_321f(0x1da0,(char *)s_String_reference_out_of_range_28d3_28cc + 7,iVar2,param_1
                          ,param_2);
    if (iVar3 == iVar2) {
      iVar2 = FUN_1000_306c(10,0x1da0,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
      if (iVar2 == 10) {
        uVar1 = 10;
      }
      else {
        uVar1 = 0xffff;
      }
    }
    else {
      uVar1 = 0xffff;
    }
  }
  return uVar1;
}



// Function: FUN_1000_3492

undefined2 __cdecl16far
FUN_1000_3492(int *param_1,uint param_2,uint param_3,int param_4,uint param_5)

{
  undefined2 uVar1;
  int *piVar2;
  uint uVar3;
  
  uVar3 = (uint)((ulong)param_1 >> 0x10);
  piVar2 = (int *)param_1;
  if ((((int *)piVar2[9] == piVar2) && (param_4 < 3)) && (param_5 < 0x8000)) {
    if ((iRam0002b2b0 == 0) && (piVar2 == (int *)0x1da0)) {
      iRam0002b2b0 = 1;
    }
    else if ((iRam0002b2ae == 0) && (piVar2 == (int *)0x1d8c)) {
      iRam0002b2ae = 1;
    }
    if (*param_1 != 0) {
      FUN_1000_2d94(piVar2,uVar3,0,0,1);
    }
    if ((piVar2[1] & 4U) != 0) {
      FUN_1000_4648(piVar2[4],piVar2[5]);
    }
    piVar2[1] = piVar2[1] & 0xfff3;
    piVar2[3] = 0;
    piVar2[5] = uVar3;
    piVar2[4] = (int)piVar2 + 5;
    piVar2[7] = uVar3;
    piVar2[6] = (int)piVar2 + 5;
    if ((param_4 != 2) && (param_5 != 0)) {
      DAT_28d3_2712 = 0x1000;
      DAT_28d3_2710 = 0x376b;
      if ((param_2 | param_3) == 0) {
        param_3 = uVar3;
        param_2 = FUN_1000_4752(param_5);
        if ((param_2 | param_3) == 0) goto LAB_1000_3581;
        piVar2[1] = piVar2[1] | 4;
      }
      piVar2[7] = param_3;
      piVar2[6] = param_2;
      piVar2[5] = param_3;
      piVar2[4] = param_2;
      piVar2[3] = param_5;
      if (param_4 == 1) {
        piVar2[1] = piVar2[1] | 8;
      }
    }
    uVar1 = 0;
  }
  else {
LAB_1000_3581:
    uVar1 = 0xffff;
  }
  return uVar1;
}



// Function: FUN_1000_35b7

int __cdecl16far FUN_1000_35b7(uint param_1,char *param_2,undefined2 param_3,int param_4)

{
  char *pcVar1;
  uint *puVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  undefined2 unaff_SS;
  char local_92 [130];
  undefined4 local_10;
  char local_b;
  int local_a;
  char *local_8;
  undefined2 uVar6;
  int local_4;
  
  if (param_1 < DAT_28d3_2174) {
    if (param_4 + 1U < 2) {
      iVar5 = 0;
    }
    else {
      if ((*(uint *)(param_1 * 2 + 0x2176) & 0x800) != 0) {
        FUN_1000_1feb(param_1,0,0,2);
      }
      if ((*(uint *)(param_1 * 2 + 0x2176) & 0x4000) == 0) {
        iVar5 = FUN_1000_3df9(param_1,param_2,param_3,param_4);
      }
      else {
        puVar2 = (uint *)(param_1 * 2 + 0x2176);
        *puVar2 = *puVar2 & 0xfdff;
        local_10 = (char *)CONCAT22(param_3,param_2);
        local_a = param_4;
        do {
          _local_8 = (char *)CONCAT22(unaff_SS,local_92);
          do {
            pcVar4 = local_10;
            if (local_a == 0) {
              local_4 = (int)local_8 - (int)local_92;
              if (local_4 == 0) {
                return param_4;
              }
              iVar5 = FUN_1000_3df9(param_1,local_92);
              if (iVar5 == local_4) {
                return param_4;
              }
              if (iVar5 == -1) {
                return -1;
              }
              iVar5 = param_4 + iVar5;
              goto LAB_1000_3713;
            }
            local_a = local_a + -1;
            local_10 = (char *)CONCAT22(local_10._2_2_,(char *)local_10 + 1);
            local_b = *pcVar4;
            if (local_b == '\n') {
              *_local_8 = '\r';
              uVar6 = (undefined2)((ulong)_local_8 >> 0x10);
              _local_8 = (char *)CONCAT22(uVar6,local_8 + 1);
            }
            *_local_8 = local_b;
            pcVar3 = local_8 + 1;
            uVar6 = (undefined2)((ulong)_local_8 >> 0x10);
            _local_8 = (char *)CONCAT22(uVar6,pcVar3);
            pcVar1 = local_92;
          } while ((pcVar3 < pcVar1) ||
                  ((pcVar3 >= pcVar1 && ((uint)((int)pcVar3 - (int)pcVar1) < 0x80))));
          local_4 = (int)pcVar3 - (int)local_92;
          iVar5 = FUN_1000_3df9(param_1,local_92);
        } while (iVar5 == local_4);
        if (iVar5 == -1) {
          iVar5 = -1;
        }
        else {
          iVar5 = (param_4 - local_a) + iVar5;
LAB_1000_3713:
          iVar5 = iVar5 - local_4;
        }
      }
    }
  }
  else {
    iVar5 = FUN_1000_1f84(6);
  }
  return iVar5;
}



// Function: FUN_1000_3721

void __cdecl16far FUN_1000_3721(void)

{
  uint local_8;
  int local_6;
  
  local_6 = 0x1d8c;
  for (local_8 = 0; local_8 < DAT_28d3_2174; local_8 = local_8 + 1) {
    if (((*(uint *)(local_6 + 2) & 3) != 0) && (*(int *)(local_6 + 0x10) != 0)) {
      FUN_1000_258a(local_6,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
    }
    local_6 = local_6 + 0x14;
  }
  return;
}



// Function: FUN_1000_376b

void __cdecl16far FUN_1000_376b(void)

{
  int *piVar1;
  undefined2 uVar2;
  uint local_8;
  int *local_6;
  
  local_6 = (int *)0x28d31d8c;
  for (local_8 = 0; local_8 < DAT_28d3_2174; local_8 = local_8 + 1) {
    uVar2 = (undefined2)((ulong)local_6 >> 0x10);
    piVar1 = (int *)local_6;
    if (((piVar1[1] & 3U) != 0) && (*local_6 < 0)) {
      FUN_1000_264b(piVar1,uVar2);
    }
    local_6 = (int *)CONCAT22(uVar2,piVar1 + 10);
  }
  return;
}



// Function: FUN_1000_37b4

undefined2 __cdecl16far FUN_1000_37b4(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined in_CF;
  undefined2 param_3;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if ((bool)in_CF) {
    param_3 = FUN_1000_1f84(uVar2);
  }
  return param_3;
}



// Function: FUN_1000_37d5

undefined2 __cdecl16far FUN_1000_37d5(int param_1)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined in_CF;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if ((bool)in_CF) {
    uVar2 = FUN_1000_1f84(uVar2);
  }
  else {
    *(undefined2 *)(param_1 * 2 + 0x2176) = 0;
    uVar2 = 0;
  }
  return uVar2;
}



// Function: FUN_1000_37f7

void __cdecl16far FUN_1000_37f7(undefined2 param_1)

{
  FUN_1000_37d5(param_1);
  return;
}



// Function: FUN_1000_3808

/* WARNING: Removing unreachable block (ram,0x0001386e) */

undefined2 __cdecl16far FUN_1000_3808(uint param_1)

{
  code *pcVar1;
  bool bVar2;
  ulong uVar3;
  undefined4 uVar4;
  ulong uVar5;
  undefined2 uVar6;
  
  if (param_1 < DAT_28d3_2174) {
    bVar2 = false;
    if ((*(uint *)(param_1 * 2 + 0x2176) & 0x200) != 0) {
      return 1;
    }
    pcVar1 = (code *)swi(0x21);
    uVar3 = (*pcVar1)();
    uVar6 = (undefined2)uVar3;
    if (!bVar2) {
      if ((uVar3 & 0x800000) != 0) {
        return 0;
      }
      bVar2 = false;
      pcVar1 = (code *)swi(0x21);
      uVar4 = (*pcVar1)();
      uVar6 = (undefined2)uVar4;
      if (!bVar2) {
        bVar2 = false;
        pcVar1 = (code *)swi(0x21);
        uVar3 = (*pcVar1)((int)((ulong)uVar4 >> 0x10));
        uVar6 = (undefined2)uVar3;
        if (!bVar2) {
          pcVar1 = (code *)swi(0x21);
          uVar5 = (*pcVar1)();
          uVar6 = (undefined2)uVar5;
          if (!bVar2) {
            if (uVar5 < uVar3) {
              return 0;
            }
            return 1;
          }
        }
      }
    }
  }
  else {
    uVar6 = 6;
  }
  uVar6 = FUN_1000_1f84(uVar6);
  return uVar6;
}



// Function: FUN_1000_3886

undefined2 __cdecl16far FUN_1000_3886(void)

{
  code *pcVar1;
  undefined2 uVar2;
  uint uVar3;
  byte in_CF;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  uVar3 = (uint)(in_CF & 1);
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if ((uVar3 & 1) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_1000_1f84();
  }
  return uVar2;
}



// Function: FUN_1000_38bd

undefined2 FUN_1000_38bd(void)

{
  code *pcVar1;
  undefined2 uVar2;
  uint uVar3;
  byte in_CF;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  uVar3 = (uint)(in_CF & 1);
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if ((uVar3 & 1) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_1000_1f84();
  }
  return uVar2;
}



// Function: FUN_1000_38ee

void __cdecl16near FUN_1000_38ee(void)

{
  int local_8;
  int local_6;
  
  local_8 = 0x32;
  local_6 = 0x1d8c;
  while (local_8 != 0) {
    if ((*(uint *)(local_6 + 2) & 0x300) == 0x300) {
      FUN_1000_264b(local_6,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
    }
    local_6 = local_6 + 0x14;
    local_8 = local_8 + -1;
  }
  return;
}



// Function: FUN_1000_3933

undefined2 FUN_1000_3933(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined2 uVar5;
  
  uVar5 = (undefined2)((ulong)param_1 >> 0x10);
  piVar4 = (int *)param_1;
  if ((piVar4[1] & 0x200U) != 0) {
    FUN_1000_38ee();
  }
  iVar3 = piVar4[3];
  iVar1 = piVar4[5];
  iVar2 = piVar4[4];
  piVar4[7] = iVar1;
  piVar4[6] = iVar2;
  iVar3 = FUN_1000_3d28((int)*(char *)(piVar4 + 2),iVar2,iVar1,iVar3);
  *param_1 = iVar3;
  if (iVar3 < 1) {
    if (*param_1 == 0) {
      piVar4[1] = piVar4[1] & 0xfe7fU | 0x20;
    }
    else {
      *param_1 = 0;
      piVar4[1] = piVar4[1] | 0x10;
    }
    uVar5 = 0xffff;
  }
  else {
    piVar4[1] = piVar4[1] & 0xffdf;
    uVar5 = 0;
  }
  return uVar5;
}



// Function: FUN_1000_39af

void __cdecl16far FUN_1000_39af(int *param_1)

{
  *param_1 = *param_1 + 1;
  FUN_1000_39cd((int *)param_1,param_1._2_2_);
  return;
}



// Function: FUN_1000_39cd

uint __cdecl16far FUN_1000_39cd(int *param_1)

{
  byte *pbVar1;
  int iVar2;
  
  if (((uint)(int *)param_1 | param_1._2_2_) != 0) {
    if (0 < *param_1) {
      *param_1 = *param_1 + -1;
LAB_1000_3a33:
      iVar2 = ((int *)param_1)[7];
      pbVar1 = (byte *)((int *)param_1)[6];
      ((int *)param_1)[6] = ((int *)param_1)[6] + 1;
      return (uint)*pbVar1;
    }
    if (((*param_1 < 0) || ((((int *)param_1)[1] & 0x110U) != 0)) ||
       ((((int *)param_1)[1] & 1U) == 0)) {
      ((int *)param_1)[1] = ((int *)param_1)[1] | 0x10;
    }
    else {
      ((int *)param_1)[1] = ((int *)param_1)[1] | 0x80;
      if (((int *)param_1)[3] == 0) {
        while( true ) {
          if ((((int *)param_1)[1] & 0x200U) != 0) {
            FUN_1000_38ee();
          }
          iVar2 = FUN_1000_3d28((int)*(char *)((int *)param_1 + 2),(undefined1 *)&DAT_28d3_5826,
                                (char *)s_String_reference_out_of_range_28d3_28cc + 7,1);
          if (iVar2 == 0) break;
          if ((DAT_28d3_5826 != 0xd) || ((((int *)param_1)[1] & 0x40U) != 0)) {
            ((int *)param_1)[1] = ((int *)param_1)[1] & 0xffdf;
            return (uint)DAT_28d3_5826;
          }
        }
        iVar2 = FUN_1000_3808((int)*(char *)((int *)param_1 + 2));
        if (iVar2 == 1) {
          ((int *)param_1)[1] = ((int *)param_1)[1] & 0xfe7fU | 0x20;
        }
        else {
          ((int *)param_1)[1] = ((int *)param_1)[1] | 0x10;
        }
      }
      else {
        iVar2 = FUN_1000_3933((int *)param_1,param_1._2_2_);
        if (iVar2 == 0) {
          *param_1 = *param_1 + -1;
          goto LAB_1000_3a33;
        }
      }
    }
  }
  return 0xffff;
}



// Function: FUN_1000_3adf

void FUN_1000_3adf(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined in_CF;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if ((bool)in_CF) {
    FUN_1000_1f84(uVar2);
  }
  return;
}



// Function: FUN_1000_3afe

void FUN_1000_3afe(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



// Function: FUN_1000_3b14

int __cdecl16far FUN_1000_3b14(undefined2 param_1,undefined2 param_2,uint param_3,uint param_4)

{
  undefined2 uVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint local_4;
  
  uVar1 = DAT_28d3_007e;
  if ((param_3 & 0xc000) == 0) {
    param_3 = param_3 | DAT_28d3_21da & 0xc000;
  }
  local_4 = FUN_1000_37b4(param_1,param_2,0);
  if ((local_4 == 0xffff) && (iVar3 = DAT_28d3_21e8, DAT_28d3_21e8 != 2)) {
LAB_1000_3bbc:
    iVar3 = FUN_1000_1f84(iVar3);
    return iVar3;
  }
  DAT_28d3_007e = uVar1;
  if ((param_3 & 0x100) != 0) {
    param_4 = param_4 & DAT_28d3_21dc;
    if ((param_4 & 0x180) == 0) {
      FUN_1000_1f84(1);
    }
    if (local_4 == 0xffff) {
      local_4 = (uint)((param_4 & 0x80) == 0);
      if ((param_3 & 0xf0) == 0) {
        iVar3 = FUN_1000_3adf(local_4,param_1,param_2);
        if (iVar3 < 0) {
          return iVar3;
        }
        goto LAB_1000_3c6f;
      }
      iVar3 = FUN_1000_3adf(0,param_1,param_2);
      if (iVar3 < 0) {
        return iVar3;
      }
      FUN_1000_37d5(iVar3);
    }
    else if ((param_3 & 0x400) != 0) {
      iVar3 = 0x50;
      goto LAB_1000_3bbc;
    }
  }
  iVar3 = FUN_1000_3cbc(param_1,param_2,param_3);
  if (-1 < iVar3) {
    bVar2 = FUN_1000_3e55(iVar3,0);
    if ((bVar2 & 0x80) == 0) {
      if ((param_3 & 0x200) != 0) {
        FUN_1000_3afe(iVar3);
      }
    }
    else {
      uVar4 = param_3 | 0x2000;
      uVar5 = param_3 & 0x8000;
      param_3 = uVar4;
      if (uVar5 != 0) {
        FUN_1000_3e55(iVar3,1,bVar2 | 0x20,0);
      }
    }
    if ((((local_4 & 1) != 0) && ((param_3 & 0x100) != 0)) && ((param_3 & 0xf0) != 0)) {
      FUN_1000_37b4(param_1,param_2,1,1);
    }
  }
LAB_1000_3c6f:
  if (-1 < iVar3) {
    DAT_28d3_271a = 0x1000;
    DAT_28d3_2718 = 0x1f2f;
    if ((param_3 & 0x300) == 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = 0x1000;
    }
    if ((local_4 & 1) == 0) {
      uVar5 = 0x100;
    }
    else {
      uVar5 = 0;
    }
    *(uint *)(iVar3 * 2 + 0x2176) = uVar4 | param_3 & 0xf8ff | uVar5;
  }
  return iVar3;
}



// Function: FUN_1000_3cbc

int __cdecl16far FUN_1000_3cbc(undefined2 param_1,undefined2 param_2_00,uint param_2)

{
  code *pcVar1;
  int iVar2;
  undefined2 unaff_SI;
  bool bVar3;
  
  bVar3 = false;
  pcVar1 = (code *)swi(0x21);
  iVar2 = (*pcVar1)();
  if (bVar3) {
    iVar2 = FUN_1000_1f84(iVar2);
  }
  else {
    *(uint *)(iVar2 * 2 + 0x2176) = param_2 & 0xb8ff | 0x8000;
  }
  return iVar2;
}



// Function: FUN_1000_3d0f

void __cdecl16far FUN_1000_3d0f(undefined2 param_1,undefined2 param_2,undefined2 param_3)

{
  FUN_1000_3cbc(param_1,param_2,param_3);
  return;
}



// Function: FUN_1000_3d28

int __cdecl16far FUN_1000_3d28(uint param_1,char *param_2,int param_4)

{
  uint *puVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  undefined2 uVar8;
  char local_5;
  int local_4;
  
  if (param_1 < DAT_28d3_2174) {
    if ((param_4 + 1U < 2) || ((*(uint *)(param_1 * 2 + 0x2176) & 0x200) != 0)) {
      iVar4 = 0;
    }
    else {
      do {
        local_4 = FUN_1000_2018(param_1,(char *)param_2,param_2._2_2_,param_4);
        if (local_4 + 1U < 2) {
          return local_4;
        }
        iVar4 = local_4;
        pcVar6 = (char *)param_2;
        pcVar3 = (char *)param_2;
        if ((*(uint *)(param_1 * 2 + 0x2176) & 0x4000) == 0) {
          return local_4;
        }
        do {
          while( true ) {
            pcVar7 = pcVar3;
            cVar2 = *pcVar6;
            pcVar5 = (char *)param_2;
            if (cVar2 == '\x1a') {
              FUN_1000_1feb(param_1,-iVar4,-(uint)(iVar4 != 0),1);
              puVar1 = (uint *)(param_1 * 2 + 0x2176);
              *puVar1 = *puVar1 | 0x200;
              goto LAB_1000_3df0;
            }
            if (cVar2 == '\r') break;
            *pcVar7 = cVar2;
            iVar4 = iVar4 + -1;
            pcVar6 = pcVar6 + 1;
            pcVar3 = pcVar7 + 1;
            if (iVar4 == 0) goto LAB_1000_3dc6;
          }
          iVar4 = iVar4 + -1;
          pcVar6 = pcVar6 + 1;
          pcVar3 = pcVar7;
        } while (iVar4 != 0);
        uVar8 = param_2._2_2_;
        FUN_1000_204b(param_1,&local_5);
        *pcVar7 = local_5;
LAB_1000_3dc6:
        pcVar7 = pcVar7 + 1;
      } while (pcVar7 == pcVar5);
LAB_1000_3df0:
      iVar4 = (int)pcVar7 - (int)pcVar5;
    }
  }
  else {
    iVar4 = FUN_1000_1f84(6);
  }
  return iVar4;
}



// Function: FUN_1000_3df9

undefined2 __cdecl16far FUN_1000_3df9(int param_1)

{
  uint *puVar1;
  code *pcVar2;
  bool bVar3;
  undefined2 uVar4;
  char *pcVar5;
  
  bVar3 = false;
  if ((*(uint *)(param_1 * 2 + 0x2176) & 1) == 0) {
    pcVar5 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    pcVar2 = (code *)swi(0x21);
    uVar4 = (*pcVar2)();
    if (!bVar3) {
      puVar1 = (uint *)(param_1 * 2 + 0x2176);
      *puVar1 = *puVar1 | 0x1000;
      return uVar4;
    }
  }
  else {
    uVar4 = 5;
  }
  uVar4 = FUN_1000_1f84(uVar4);
  return uVar4;
}



// Function: FUN_1000_3e39

void __cdecl16far
FUN_1000_3e39(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  FUN_1000_3df9(param_1,param_2,param_3,param_4);
  return;
}



// Function: FUN_1000_3e55

undefined2 __cdecl16far FUN_1000_3e55(undefined2 param_1,int param_2)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined in_CF;
  undefined4 uVar3;
  
  pcVar1 = (code *)swi(0x21);
  uVar3 = (*pcVar1)();
  uVar2 = (undefined2)uVar3;
  if ((bool)in_CF) {
    uVar2 = FUN_1000_1f84(uVar2);
  }
  else if (param_2 == 0) {
    uVar2 = (int)((ulong)uVar3 >> 0x10);
  }
  return uVar2;
}



// Function: FUN_1000_3e8c

char * __cdecl16far FUN_1000_3e8c(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  undefined2 uVar4;
  
  uVar4 = (undefined2)((ulong)param_1 >> 0x10);
  pcVar2 = (char *)param_1;
  while( true ) {
    pcVar3 = pcVar2;
    cVar1 = *pcVar3;
    if (cVar1 == '\0') break;
    pcVar2 = pcVar3 + 1;
    if ((byte)(cVar1 + 0xbfU) < 0x1a) {
      *pcVar3 = cVar1 + ' ';
    }
  }
  return (char *)param_1;
}



// Function: FUN_1000_3eb2

int __cdecl16far FUN_1000_3eb2(void)

{
  int in_AX;
  int in_BX;
  
  return in_AX * in_BX;
}



// Function: FUN_1000_3ecc

void FUN_1000_3ecc(void)

{
  FUN_1000_3ee6();
  return;
}



// Function: FUN_1000_3ed0

void FUN_1000_3ed0(void)

{
  FUN_1000_3ee6();
  return;
}



// Function: FUN_1000_3ee6

undefined4 __stdcall16far FUN_1000_3ee6(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint in_CX;
  int iVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  
  if ((param_4 == 0) && ((param_2 == 0 || (param_3 == 0)))) {
    uVar1 = (uint)(CONCAT22(param_2,param_1) / (ulong)param_3);
    if ((in_CX & 2) != 0) {
      uVar1 = (uint)(CONCAT22(param_2,param_1) % (ulong)param_3);
    }
    param_2 = 0;
  }
  else {
    if ((in_CX & 1) == 0) {
      if ((int)param_2 < 0) {
        bVar5 = param_1 != 0;
        param_1 = -param_1;
        param_2 = -(uint)bVar5 - param_2;
        in_CX = in_CX | 0xc;
      }
      if ((int)param_4 < 0) {
        bVar5 = param_3 != 0;
        param_3 = -param_3;
        param_4 = -(uint)bVar5 - param_4;
        in_CX = in_CX ^ 4;
      }
    }
    iVar2 = 0x20;
    uVar4 = 0;
    uVar3 = 0;
    do {
      bVar5 = (int)param_1 < 0;
      param_1 = param_1 * 2;
      bVar6 = (int)param_2 < 0;
      param_2 = param_2 << 1 | (uint)bVar5;
      bVar5 = (int)uVar3 < 0;
      uVar3 = uVar3 << 1 | (uint)bVar6;
      uVar4 = uVar4 << 1 | (uint)bVar5;
      if ((param_4 <= uVar4) && ((param_4 < uVar4 || (param_3 <= uVar3)))) {
        bVar5 = uVar3 < param_3;
        uVar3 = uVar3 - param_3;
        uVar4 = (uVar4 - param_4) - (uint)bVar5;
        param_1 = param_1 + 1;
      }
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    uVar1 = param_1;
    if ((in_CX & 2) != 0) {
      in_CX = in_CX >> 1;
      uVar1 = uVar3;
      param_2 = uVar4;
    }
    if ((in_CX & 4) != 0) {
      bVar5 = uVar1 != 0;
      uVar1 = -uVar1;
      param_2 = -(uint)bVar5 - param_2;
    }
  }
  return CONCAT22(param_2,uVar1);
}



// Function: FUN_1000_3f77

int __cdecl16far FUN_1000_3f77(void)

{
  int in_AX;
  byte in_CL;
  
  if (in_CL < 0x10) {
    return in_AX << (in_CL & 0x1f);
  }
  return 0;
}



// Function: FUN_1000_3f98

undefined4 __cdecl16near FUN_1000_3f98(void)

{
  uint in_AX;
  int in_CX;
  int in_DX;
  uint in_BX;
  
  if (in_DX != 0) {
    in_DX = in_DX * in_BX;
  }
  if (in_CX != 0) {
    in_DX = in_CX * in_AX + in_DX;
  }
  return CONCAT22((int)((ulong)in_AX * (ulong)in_BX >> 0x10) + in_DX,
                  (int)((ulong)in_AX * (ulong)in_BX));
}



// Function: FUN_1000_3faf

char * FUN_1000_3faf(char param_1,char param_2,uint param_3,char *param_4,uint param_5,uint param_6)

{
  char *pcVar1;
  byte bVar2;
  ulong uVar3;
  char cVar4;
  int iVar5;
  byte *pbVar6;
  char *pcVar7;
  undefined2 uVar8;
  undefined2 unaff_SS;
  bool bVar9;
  byte local_24 [34];
  
  uVar8 = (undefined2)((ulong)param_4 >> 0x10);
  pcVar7 = (char *)param_4;
  if ((param_3 < 0x25) && (1 < (byte)param_3)) {
    if (((int)param_6 < 0) && (param_2 != '\0')) {
      *param_4 = '-';
      pcVar7 = pcVar7 + 1;
      bVar9 = param_5 != 0;
      param_5 = -param_5;
      param_6 = -(uint)bVar9 - param_6;
    }
    pbVar6 = local_24;
    if (param_6 == 0) goto LAB_1000_3ff9;
    do {
      uVar3 = (ulong)param_6;
      param_6 = param_6 / param_3;
      uVar3 = uVar3 % (ulong)param_3 << 0x10 | (ulong)param_5;
      param_5 = (uint)(uVar3 / param_3);
      *pbVar6 = (byte)(uVar3 % (ulong)param_3);
      pbVar6 = pbVar6 + 1;
    } while (param_6 != 0);
    while (param_5 != 0) {
LAB_1000_3ff9:
      *pbVar6 = (byte)(param_5 % param_3);
      pbVar6 = pbVar6 + 1;
      param_5 = param_5 / param_3;
    }
    iVar5 = (int)pbVar6 - (int)local_24;
    do {
      pbVar6 = pbVar6 + -1;
      bVar2 = *pbVar6;
      if (bVar2 < 10) {
        cVar4 = bVar2 + 0x30;
      }
      else {
        cVar4 = (bVar2 - 10) + param_1;
      }
      pcVar1 = pcVar7;
      pcVar7 = pcVar7 + 1;
      *pcVar1 = cVar4;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  *pcVar7 = '\0';
  return param_4;
}



// Function: FUN_1000_4031

void FUN_1000_4031(undefined2 param_1,undefined2 param_2,undefined2 param_3)

{
  FUN_1000_3faf(0x61,0,10,param_1,param_2,param_3,0);
  return;
}



// Function: FUN_1000_4055

void __cdecl16far FUN_1000_4055(int param_1,undefined2 param_2,undefined2 param_3,int param_4)

{
  int iVar1;
  
  if (param_4 == 10) {
    iVar1 = param_1 >> 0xf;
  }
  else {
    iVar1 = 0;
  }
  FUN_1000_3faf(0x61,1,param_4,param_2,param_3,param_1,iVar1);
  return;
}



// Function: FUN_1000_4084

void __cdecl16far
FUN_1000_4084(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5)

{
  uint in_AX;
  
  FUN_1000_3faf(0x61,in_AX & 0xff00,param_5,param_3,param_4,param_1,param_2);
  return;
}



// Function: FUN_1000_40a5

void __cdecl16far
FUN_1000_40a5(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             int param_5)

{
  FUN_1000_3faf(0x61,param_5 == 10,param_5,param_3,param_4,param_1,param_2);
  return;
}



// Function: FUN_1000_40d1

uint __cdecl16far FUN_1000_40d1(byte *param_1)

{
  ulong uVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  byte *pbVar6;
  undefined2 uVar7;
  
  uVar7 = (undefined2)((ulong)param_1 >> 0x10);
  pbVar6 = (byte *)param_1;
  uVar3 = 0;
  do {
    bVar5 = *pbVar6;
    pbVar6 = pbVar6 + 1;
  } while ((*(byte *)(bVar5 + 0x25bf) & 1) != 0);
  bVar2 = false;
  if (bVar5 != 0x2b) {
    if (bVar5 != 0x2d) goto LAB_1000_4102;
    bVar2 = true;
  }
  do {
    bVar5 = *pbVar6;
    pbVar6 = pbVar6 + 1;
LAB_1000_4102:
    if ((0x39 < bVar5) || (bVar5 < 0x30)) goto LAB_1000_4136;
    uVar1 = (ulong)uVar3;
    uVar4 = (uint)(uVar1 * 10);
    uVar3 = uVar4 + (byte)(bVar5 - 0x30);
  } while ((char)((char)(uVar1 * 10 >> 0x10) + CARRY2(uVar4,(uint)(byte)(bVar5 - 0x30))) == '\0');
  while( true ) {
    bVar5 = *pbVar6;
    pbVar6 = pbVar6 + 1;
    if ((0x39 < bVar5) || (bVar5 < 0x30)) break;
    uVar3 = uVar3 * 10 + (uint)(byte)(bVar5 - 0x30);
  }
LAB_1000_4136:
  if (bVar2) {
    uVar3 = -uVar3;
  }
  return uVar3;
}



// Function: FUN_1000_4146

void __cdecl16far FUN_1000_4146(undefined2 param_1,undefined2 param_2)

{
  FUN_1000_40d1(param_1,param_2);
  return;
}



// Function: thunk_FUN_1000_068f

void thunk_FUN_1000_068f(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001417a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_28d3_2908)();
  return;
}



// Function: thunk_FUN_1000_083f

void __cdecl16near thunk_FUN_1000_083f(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001417e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_28d3_290c)();
  return;
}



// Function: FUN_1000_422a

int __cdecl16far FUN_1000_422a(undefined4 param_1,undefined4 param_3)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  undefined2 in_DX;
  
  FUN_1000_599f((int)param_1,param_1._2_2_,(int)param_3,param_3._2_2_);
  *(undefined2 *)((int)param_1 + 4) = *(undefined2 *)((int)param_3 + 4);
  puVar3 = (uint *)FUN_1000_5c87();
  puVar1 = puVar3;
  uVar2 = *puVar1;
  *puVar1 = *puVar1 + 1;
  puVar3[1] = puVar3[1] + (uint)(0xfffe < uVar2);
  return (int)param_1;
}



// Function: FUN_1000_441a

void __cdecl16far FUN_1000_441a(undefined2 param_1,undefined2 param_2)

{
  FUN_1000_4648(param_1,param_2);
  return;
}



// Function: FUN_1000_4430

void __cdecl16far FUN_1000_4430(undefined2 param_1,undefined2 param_2)

{
  FUN_1000_441a(param_1,param_2);
  return;
}



// Function: FUN_1000_4446

undefined2 __cdecl16far FUN_1000_4446(undefined2 param_1,undefined2 param_2)

{
  undefined2 uVar1;
  
  uVar1 = DAT_28d3_5828;
  DAT_28d3_582a = param_2;
  DAT_28d3_5828 = param_1;
  return uVar1;
}



// Function: FUN_1000_448a

void __cdecl16far FUN_1000_448a(void)

{
  if ((DAT_28d3_582c | DAT_28d3_582e) != 0) {
    FUN_1000_4648(DAT_28d3_582c,DAT_28d3_582e);
    DAT_28d3_582e = 0;
    DAT_28d3_582c = 0;
  }
  return;
}



// Function: FUN_1000_44b3

uint __cdecl16far FUN_1000_44b3(int param_1)

{
  uint uVar1;
  uint in_DX;
  uint extraout_DX;
  
  if (param_1 == 0) {
    param_1 = 1;
  }
  while ((uVar1 = FUN_1000_4752(param_1), (uVar1 | in_DX) == 0 &&
         (((uint)DAT_28d3_5828 | DAT_28d3_582a) != 0))) {
    FUN_1000_448a();
    (*DAT_28d3_5828)(0x1000);
    in_DX = extraout_DX;
  }
  return uVar1;
}



// Function: FUN_1000_4514

void __cdecl16near FUN_1000_4514(void)

{
  int in_DX;
  undefined2 uVar1;
  int iVar2;
  
  if (in_DX == DAT_1000_4508) {
LAB_1000_4552:
    DAT_1000_4508 = 0;
    DAT_1000_450a = 0;
    DAT_1000_450c = 0;
  }
  else {
    iVar2 = *(int *)&DAT_28d3_0002;
    DAT_1000_450a = iVar2;
    if (*(int *)&DAT_28d3_0002 == 0) {
      in_DX = DAT_1000_4508;
      if (iVar2 != DAT_1000_4508) {
        DAT_1000_450a = *(int *)((char *)s_NULL_CHECK_28d3_0004 + 4);
        uVar1 = 0;
        FUN_1000_45e8(0,iVar2);
        goto LAB_1000_4570;
      }
      goto LAB_1000_4552;
    }
  }
  uVar1 = 0;
  iVar2 = in_DX;
LAB_1000_4570:
  FUN_1000_49c8(uVar1,iVar2);
  return;
}



// Function: FUN_1000_4577

void __cdecl16near FUN_1000_4577(void)

{
  undefined2 uVar1;
  int in_DX;
  int iVar2;
  int iStack_2;
  
  iStack_2 = *(int *)&DAT_28d3_0002;
  *(undefined2 *)&DAT_28d3_0002 = 0;
  *(int *)((char *)s_NULL_CHECK_28d3_0004 + 4) = iStack_2;
  if ((in_DX == DAT_1000_4508) || (*(int *)&DAT_28d3_0002 != 0)) {
    FUN_1000_4611();
    iStack_2 = in_DX;
  }
  else {
    iVar2 = *(int *)0x0;
    *(int *)0x0 = *(int *)0x0 + iVar2;
    iVar2 = in_DX + iVar2;
    if (*(int *)&DAT_28d3_0002 == 0) {
      *(int *)((char *)s_NULL_CHECK_28d3_0004 + 4) = iStack_2;
    }
    else {
      *(int *)&DAT_28d3_0002 = iStack_2;
    }
  }
  iVar2 = iStack_2 + *(int *)0x0;
  if (*(int *)&DAT_28d3_0002 != 0) {
    return;
  }
  *(int *)0x0 = *(int *)0x0 + *(int *)0x0;
  *(int *)&DAT_28d3_0002 = iStack_2;
  if (iVar2 != *(int *)((char *)s_NULL_CHECK_28d3_0004 + 2)) {
    uVar1 = *(undefined2 *)((char *)s_NULL_CHECK_28d3_0004 + 2);
    DAT_1000_450c = *(undefined2 *)s_NULL_CHECK_28d3_0004;
    *(undefined2 *)((char *)s_NULL_CHECK_28d3_0004 + 2) = uVar1;
    *(undefined2 *)s_NULL_CHECK_28d3_0004 = DAT_1000_450c;
    return;
  }
  DAT_1000_450c = 0;
  return;
}



// Function: FUN_1000_45e8

void __cdecl16near FUN_1000_45e8(void)

{
  undefined2 uVar1;
  
  uVar1 = s_NULL_CHECK_28d3_0004._2_2_;
  DAT_1000_450c = s_NULL_CHECK_28d3_0004._0_2_;
  if ((char *)s_NULL_CHECK_28d3_0004._2_2_ != (char *)s_String_reference_out_of_range_28d3_28cc + 7)
  {
    *(undefined2 *)((char *)s_NULL_CHECK_28d3_0004 + 2) = s_NULL_CHECK_28d3_0004._2_2_;
    *(undefined2 *)s_NULL_CHECK_28d3_0004 = DAT_1000_450c;
    return;
  }
  DAT_1000_450c = 0;
  return;
}



// Function: FUN_1000_4611

void __cdecl16near FUN_1000_4611(void)

{
  undefined2 uVar1;
  
  s_NULL_CHECK_28d3_0004._0_2_ = DAT_1000_450c;
  if (DAT_1000_450c != (char *)0x0) {
    uVar1 = *(undefined2 *)((char *)s_NULL_CHECK_28d3_0004 + 2);
    *(char **)((char *)s_NULL_CHECK_28d3_0004 + 2) =
         (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    *(char **)s_NULL_CHECK_28d3_0004 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    s_NULL_CHECK_28d3_0004[2] = (char)uVar1;
    s_NULL_CHECK_28d3_0004[3] = SUB21(uVar1,1);
    return;
  }
  DAT_1000_450c = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  s_NULL_CHECK_28d3_0004._0_2_ = (int)(char *)s_String_reference_out_of_range_28d3_28cc + 7;
  s_NULL_CHECK_28d3_0004._2_2_ = (int)(char *)s_String_reference_out_of_range_28d3_28cc + 7;
  return;
}



// Function: FUN_1000_4648

void __cdecl16far FUN_1000_4648(undefined2 param_1_00,int param_1)

{
  DAT_1000_450e = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  if (param_1 != 0) {
    if (param_1 == DAT_1000_450a) {
      FUN_1000_4514();
    }
    else {
      FUN_1000_4577();
    }
  }
  return;
}



// Function: FUN_1000_4671

undefined2 __cdecl16near FUN_1000_4671(void)

{
  uint in_AX;
  uint uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_1000_4a0b(0,0);
  if ((uVar1 & 0xf) != 0) {
    FUN_1000_4a0b(0x10 - (uVar1 & 0xf),0);
  }
  uVar3 = FUN_1000_4a0b(in_AX << 4,in_AX >> 0xc);
  uVar2 = (undefined2)((ulong)uVar3 >> 0x10);
  if ((int)uVar3 != -1) {
    DAT_1000_4508 = uVar2;
    DAT_1000_450a = uVar2;
    *(uint *)0x0 = in_AX;
    *(undefined2 *)&DAT_28d3_0002 = uVar2;
    return 4;
  }
  return 0;
}



// Function: FUN_1000_46d5

undefined2 __cdecl16near FUN_1000_46d5(void)

{
  undefined2 uVar1;
  uint in_AX;
  int iVar2;
  int iVar3;
  ulong uVar4;
  
  uVar4 = FUN_1000_4a0b(in_AX << 4,in_AX >> 0xc);
  iVar3 = (int)(uVar4 >> 0x10);
  if ((uint)uVar4 == 0xffff) {
    return 0;
  }
  if ((uVar4 & 0xf) != 0) {
    iVar2 = FUN_1000_4a0b(0x10 - ((uint)uVar4 & 0xf),0);
    if (iVar2 == -1) {
      return 0;
    }
    iVar3 = iVar3 + 1;
  }
  uVar1 = DAT_1000_450a;
  DAT_1000_450a = iVar3;
  *(uint *)0x0 = in_AX;
  *(undefined2 *)&DAT_28d3_0002 = uVar1;
  return 4;
}



// Function: FUN_1000_472f

undefined2 __cdecl16near FUN_1000_472f(void)

{
  int in_AX;
  int in_DX;
  int iVar1;
  
  DAT_28d3_0000 = DAT_28d3_0000 - in_AX;
  iVar1 = in_DX + DAT_28d3_0000;
  *(int *)0x0 = in_AX;
  *(int *)&DAT_28d3_0002 = in_DX;
  *(int *)&DAT_28d3_0002 = iVar1;
  return 4;
}



// Function: FUN_1000_4752

/* WARNING: Removing unreachable block (ram,0x000147bb) */

uint __cdecl16far FUN_1000_4752(uint param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  
  DAT_1000_450e = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  if (param_1 != 0) {
    uVar2 = CONCAT11((byte)(param_1 + 0x13 >> 0xc) | (0xffec < param_1) << 4,
                     (char)(param_1 + 0x13 >> 4));
    if (DAT_1000_4508 == 0) {
      param_1 = FUN_1000_4671();
    }
    else {
      iVar3 = DAT_1000_450c;
      if (DAT_1000_450c != 0) {
        do {
          if (uVar2 <= *(uint *)0x0) {
            if (*(uint *)0x0 <= uVar2) {
              FUN_1000_45e8();
              *(undefined2 *)&DAT_28d3_0002 = *(undefined2 *)((char *)s_NULL_CHECK_28d3_0004 + 4);
              return 4;
            }
            uVar2 = FUN_1000_472f();
            return uVar2;
          }
          piVar1 = (int *)((char *)s_NULL_CHECK_28d3_0004 + 2);
          iVar3 = *piVar1;
        } while (*piVar1 != DAT_1000_450c);
      }
      param_1 = FUN_1000_46d5();
    }
  }
  return param_1;
}



// Function: FUN_1000_475c

uint __cdecl16far FUN_1000_475c(uint param_1,uint param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  
  DAT_1000_450e = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  if ((param_1 | param_2) != 0) {
    uVar2 = param_2 + (0xffec < param_1);
    if ((CARRY2(param_2,(uint)(0xffec < param_1))) || ((uVar2 & 0xfff0) != 0)) {
      param_1 = 0;
    }
    else {
      uVar2 = CONCAT11((byte)(param_1 + 0x13 >> 0xc) | (char)uVar2 * '\x10',
                       (char)(param_1 + 0x13 >> 4));
      if (DAT_1000_4508 == 0) {
        param_1 = FUN_1000_4671();
      }
      else {
        iVar3 = DAT_1000_450c;
        if (DAT_1000_450c != 0) {
          do {
            if (uVar2 <= *(uint *)0x0) {
              if (*(uint *)0x0 <= uVar2) {
                FUN_1000_45e8();
                *(undefined2 *)&DAT_28d3_0002 = *(undefined2 *)((char *)s_NULL_CHECK_28d3_0004 + 4);
                return 4;
              }
              uVar2 = FUN_1000_472f();
              return uVar2;
            }
            piVar1 = (int *)((char *)s_NULL_CHECK_28d3_0004 + 2);
            iVar3 = *piVar1;
          } while (*piVar1 != DAT_1000_450c);
        }
        param_1 = FUN_1000_46d5();
      }
    }
  }
  return param_1;
}



// Function: FUN_1000_47d9

undefined2 __cdecl16near FUN_1000_47d9(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int in_DX;
  uint uVar8;
  int in_BX;
  undefined2 *puVar9;
  undefined2 *puVar10;
  bool bVar11;
  int iVar12;
  
  iVar12 = in_BX;
  uVar3 = FUN_1000_475c(DAT_1000_4512,DAT_1000_4510);
  if (in_DX == 0) {
    return uVar3;
  }
  uVar8 = *(int *)0x0 - 1;
  puVar10 = (undefined2 *)s_NULL_CHECK_28d3_0004;
  puVar9 = (undefined2 *)s_NULL_CHECK_28d3_0004;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    puVar2 = puVar10;
    puVar10 = puVar10 + 1;
    puVar1 = puVar9;
    puVar9 = puVar9 + 1;
    *puVar2 = *puVar1;
  }
  if (uVar8 != 0) {
    iVar5 = in_DX + 1;
    iVar4 = iVar12 + 1;
    while( true ) {
      puVar10 = (undefined2 *)0x0;
      puVar9 = (undefined2 *)0x0;
      uVar6 = uVar8;
      if (0x1000 < uVar8) {
        uVar6 = 0x1000;
      }
      for (iVar7 = uVar6 << 3; iVar7 != 0; iVar7 = iVar7 + -1) {
        puVar2 = puVar10;
        puVar10 = puVar10 + 1;
        puVar1 = puVar9;
        puVar9 = puVar9 + 1;
        *puVar2 = *puVar1;
      }
      bVar11 = uVar8 < 0x1000;
      uVar8 = uVar8 - 0x1000;
      if (bVar11 || uVar8 == 0) break;
      iVar5 = iVar5 + 0x1000;
      iVar4 = iVar4 + 0x1000;
    }
  }
  FUN_1000_4648(in_BX,iVar12,in_DX);
  return 4;
}



// Function: FUN_1000_4855

undefined4 __cdecl16near FUN_1000_4855(void)

{
  int in_AX;
  int in_CX;
  int iVar1;
  int in_BX;
  int iVar2;
  
  if (in_BX != DAT_1000_450a) {
    iVar2 = in_BX + in_AX;
    *(int *)0x0 = in_CX - in_AX;
    *(int *)&DAT_28d3_0002 = in_BX;
    *(int *)0x0 = in_AX;
    iVar1 = in_BX + in_CX;
    if (*(int *)&DAT_28d3_0002 == 0) {
      *(int *)((char *)s_NULL_CHECK_28d3_0004 + 4) = iVar2;
    }
    else {
      *(int *)&DAT_28d3_0002 = iVar2;
    }
    FUN_1000_4648();
    return CONCAT22(in_BX,4);
  }
  *(int *)0x0 = in_AX;
  FUN_1000_49c8(0,in_BX + in_AX);
  return CONCAT22(in_BX,4);
}



// Function: FUN_1000_48b9

undefined2 __cdecl16far FUN_1000_48b9(undefined2 param_1_00,int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  undefined2 uVar3;
  
  DAT_1000_450e = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  DAT_1000_4510 = 0;
  DAT_1000_4512 = param_2;
  if (param_1 == 0) {
    uVar3 = FUN_1000_475c(param_2,0);
  }
  else if (param_2 == 0) {
    FUN_1000_4648(0,param_1);
    uVar3 = 0;
  }
  else {
    uVar2 = CONCAT11((byte)(param_2 + 0x13 >> 0xc) | (0xffec < param_2) << 4,
                     (char)(param_2 + 0x13 >> 4));
    uVar1 = *(uint *)0x0;
    if (uVar1 < uVar2) {
      uVar3 = FUN_1000_47d9();
    }
    else if (uVar1 < uVar2 || uVar1 == uVar2) {
      uVar3 = 4;
    }
    else {
      uVar3 = FUN_1000_4855();
    }
  }
  return uVar3;
}



// Function: FUN_1000_493a

undefined2 FUN_1000_493a(undefined2 param_1,int param_2)

{
  int iVar1;
  uint local_4;
  
  local_4 = (param_2 - DAT_28d3_007a) + 0x40;
  if (local_4 >> 6 != DAT_28d3_270a) {
    local_4 = local_4 & 0xffc0;
    if (DAT_28d3_008e < local_4 + DAT_28d3_007a) {
      local_4 = DAT_28d3_008e - DAT_28d3_007a;
    }
    iVar1 = FUN_1000_4aea(DAT_28d3_007a,local_4);
    if (iVar1 != -1) {
      DAT_28d3_008c = 0;
      DAT_28d3_008e = DAT_28d3_007a + iVar1;
      return 0;
    }
    DAT_28d3_270a = local_4 >> 6;
  }
  DAT_28d3_008a = param_2;
  DAT_28d3_0088 = param_1;
  return 1;
}



// Function: FUN_1000_49c8

undefined2 __cdecl16near FUN_1000_49c8(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  undefined in_CF;
  undefined in_ZF;
  
  FUN_1000_4bae();
  if (((!(bool)in_CF) && (FUN_1000_4bae(), (bool)in_CF || (bool)in_ZF)) &&
     (iVar1 = FUN_1000_493a(param_1,param_2), iVar1 != 0)) {
    return 0;
  }
  return 0xffff;
}



// Function: FUN_1000_4a0b

undefined4 __cdecl16near FUN_1000_4a0b(uint param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined2 uVar3;
  int iVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined uVar7;
  undefined uVar8;
  
  iVar4 = 0;
  uVar1 = FUN_1000_3f77();
  iVar2 = uVar1 + DAT_28d3_0088 + param_1;
  uVar1 = iVar4 + (uint)CARRY2(uVar1,DAT_28d3_0088) + param_2 +
          (uint)CARRY2(uVar1 + DAT_28d3_0088,param_1);
  uVar7 = uVar1 < 0xf;
  uVar8 = uVar1 == 0xf;
  if ((int)uVar1 < 0xf) {
LAB_1000_4a36:
    uVar5 = DAT_28d3_008a;
    uVar3 = FUN_1000_4b26();
    FUN_1000_4bae();
    if (((!(bool)uVar7) &&
        (FUN_1000_4bae(), uVar6 = DAT_28d3_008a, uVar1 = DAT_28d3_0088, (bool)uVar7 || (bool)uVar8))
       && (iVar2 = FUN_1000_493a(uVar3,uVar5), iVar2 != 0)) goto LAB_1000_4a94;
  }
  else if ((int)uVar1 < 0x10) {
    uVar7 = iVar2 != -1;
    uVar8 = iVar2 == -1;
    goto LAB_1000_4a36;
  }
  uVar6 = 0xffff;
  uVar1 = 0xffff;
LAB_1000_4a94:
  return CONCAT22(uVar6,uVar1);
}



// Function: FUN_1000_4a9a

uint __cdecl16far FUN_1000_4a9a(void)

{
  int iVar1;
  uint local_6;
  
  iVar1 = DAT_28d3_008e;
  local_6 = FUN_1000_4b86();
  if ((iVar1 != 0) || (0x10 < local_6)) {
    local_6 = local_6 - 0x10;
  }
  return local_6 & 0xfff0;
}



// Function: FUN_1000_4aea

undefined2 __cdecl16far FUN_1000_4aea(undefined2 param_1,undefined2 param_2)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined in_CF;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if ((bool)in_CF) {
    FUN_1000_1f84(uVar2);
  }
  else {
    param_2 = 0xffff;
  }
  return param_2;
}



// Function: FUN_1000_4b0a

void __stdcall16far FUN_1000_4b0a(undefined2 *param_1,undefined2 *param_2)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  uint in_CX;
  uint uVar3;
  undefined2 *puVar4;
  undefined2 *puVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  
  uVar7 = (undefined2)((ulong)param_1 >> 0x10);
  puVar4 = (undefined2 *)param_1;
  uVar6 = (undefined2)((ulong)param_2 >> 0x10);
  puVar5 = (undefined2 *)param_2;
  for (uVar3 = in_CX >> 1; uVar3 != 0; uVar3 = uVar3 - 1) {
    puVar2 = puVar5;
    puVar5 = puVar5 + 1;
    puVar1 = puVar4;
    puVar4 = puVar4 + 1;
    *puVar2 = *puVar1;
  }
  for (uVar3 = (uint)((in_CX & 1) != 0); uVar3 != 0; uVar3 = uVar3 - 1) {
    puVar2 = puVar5;
    puVar5 = (undefined2 *)((int)puVar5 + 1);
    puVar1 = puVar4;
    puVar4 = (undefined2 *)((int)puVar4 + 1);
    *(undefined *)puVar2 = *(undefined *)puVar1;
  }
  return;
}



// Function: FUN_1000_4b26

byte __cdecl16far FUN_1000_4b26(void)

{
  char in_AL;
  int in_CX;
  byte in_BL;
  
  if (in_CX < 0) {
    return in_AL - (~in_BL + 1) & 0xf;
  }
  return in_AL + in_BL & 0xf;
}



// Function: FUN_1000_4b86

int __cdecl16far FUN_1000_4b86(void)

{
  int in_AX;
  int in_CX;
  int in_DX;
  int in_BX;
  
  return (in_DX * 0x10 + in_AX) - (in_BX + in_CX * 0x10);
}



// Function: FUN_1000_4bae

uint __cdecl16near FUN_1000_4bae(void)

{
  uint in_AX;
  
  return in_AX & 0xf;
}



// Function: FUN_1000_4bcf

void __cdecl16far FUN_1000_4bcf(undefined2 param_1,undefined2 param_2)

{
  undefined2 uVar1;
  
  uVar1 = FUN_1000_1c56(param_1,param_2);
  FUN_1000_3df9((int)DAT_28d3_1db8,param_1,param_2,uVar1);
  return;
}



// Function: FUN_1000_4c55

void __cdecl16far FUN_1000_4c55(undefined2 param_1)

{
  FUN_1000_4d6e(param_1);
  return;
}



// Function: FUN_1000_4c67

void __cdecl16far FUN_1000_4c67(undefined2 param_1,undefined2 param_2)

{
  FUN_1000_4648(param_1,param_2);
  return;
}



// Function: FUN_1000_4c7d

void __cdecl16far FUN_1000_4c7d(undefined2 param_1)

{
  FUN_1000_4752(param_1);
  return;
}



// Function: FUN_1000_4c8f

undefined2 __cdecl16far FUN_1000_4c8f(uint param_1)

{
  byte bVar1;
  undefined2 uVar2;
  undefined uVar3;
  
  uVar2 = 0x34dd;
  if (0x12 < param_1) {
    uVar3 = (undefined)(0x1234dd / (ulong)param_1 >> 8);
    bVar1 = in(0x61);
    if ((bVar1 & 3) == 0) {
      out(0x61,bVar1 | 3);
      out(0x43,0xb6);
    }
    out(0x42,(char)(0x1234dd / (ulong)param_1));
    uVar2 = CONCAT11(uVar3,uVar3);
    out(0x42,uVar3);
  }
  return uVar2;
}



// Function: FUN_1000_4cbf

byte __cdecl16far FUN_1000_4cbf(void)

{
  byte bVar1;
  
  bVar1 = in(0x61);
  out(0x61,bVar1 & 0xfc);
  return bVar1 & 0xfc;
}



// Function: FUN_1000_4cca

void __cdecl16far FUN_1000_4cca(void)

{
  FUN_1000_51c4(0x16);
  FUN_1000_4db9();
  return;
}



// Function: FUN_1000_4cde

bool __cdecl16far FUN_1000_4cde(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = DAT_28d3_270e != 0x20;
  if (bVar2) {
    iVar1 = DAT_28d3_270e * 4;
    *(undefined2 *)(iVar1 + 0x5832) = param_2;
    *(undefined2 *)(iVar1 + 0x5830) = param_1;
    DAT_28d3_270e = DAT_28d3_270e + 1;
  }
  return !bVar2;
}



// Function: FUN_1000_4d0f

void __cdecl16far FUN_1000_4d0f(void)

{
  return;
}



// Function: FUN_1000_4d14

void FUN_1000_4d14(undefined2 param_1,int param_2,int param_3)

{
  code **ppcVar1;
  
  if (param_3 == 0) {
    while (DAT_28d3_270e != 0) {
      DAT_28d3_270e = DAT_28d3_270e + -1;
      ppcVar1 = (code **)(DAT_28d3_270e * 4 + 0x5830);
      (**ppcVar1)(0x1000);
    }
    FUN_1000_0146();
    (*DAT_28d3_2710)(0x1000);
  }
  FUN_1000_01bb();
  FUN_1000_0159();
  if (param_2 == 0) {
    if (param_3 == 0) {
      (*DAT_28d3_2714)(0x1000);
      (*DAT_28d3_2718)(0x1000);
    }
    FUN_1000_015a(0x1000,param_1);
  }
  return;
}



// Function: FUN_1000_4d6e

void __cdecl16far FUN_1000_4d6e(undefined2 param_1)

{
  FUN_1000_4d14(param_1,0,0);
  return;
}



// Function: FUN_1000_4d81

void __cdecl16far FUN_1000_4d81(undefined2 param_1)

{
  FUN_1000_4d14(param_1,0,1);
  return;
}



// Function: FUN_1000_4db9

void __cdecl16far FUN_1000_4db9(void)

{
  FUN_1000_4bcf((char *)s_Abnormal_program_termination_28d3_271c,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_1000_4d81(3);
  return;
}



// Function: FUN_1000_4dd4

undefined2 __cdecl16far FUN_1000_4dd4(void)

{
  code *pcVar1;
  undefined2 in_BX;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return in_BX;
}



// Function: FUN_1000_4de7

void __cdecl16far FUN_1000_4de7(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



// Function: FUN_1000_4dfc

void __cdecl16far FUN_1000_4dfc(undefined2 *param_1)

{
  undefined2 *puVar1;
  undefined2 unaff_ES;
  undefined2 uVar2;
  undefined2 unaff_SS;
  undefined2 in_stack_00000002;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  puVar1 = (undefined2 *)param_1;
  *param_1 = unaff_ES;
  puVar1[1] = in_stack_00000002;
  puVar1[2] = unaff_SS;
  puVar1[3] = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  return;
}



// Function: FUN_1000_5071

int __cdecl16far FUN_1000_5071(uint param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if ((byte)((undefined1 *)&DAT_28d3_2758)[iVar1] == param_1) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 6);
  return -1;
}



// Function: FUN_1000_5096

undefined2 __cdecl16far FUN_1000_5096(int param_1,uint param_2,uint param_3)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined1 *puVar4;
  uint uVar5;
  
  if (DAT_28d3_273e == '\0') {
    DAT_28d3_58b2 = 0x1000;
    DAT_28d3_58b0 = 0x5096;
    DAT_28d3_273e = '\x01';
  }
  iVar2 = FUN_1000_5071(param_1);
  if (iVar2 == -1) {
    DAT_28d3_007e = 0x13;
    return 0xffff;
  }
  uVar1 = *(undefined2 *)(iVar2 * 4 + 0x2740);
  *(uint *)(iVar2 * 4 + 0x2742) = param_3;
  *(uint *)(iVar2 * 4 + 0x2740) = param_2;
  if (param_1 == 2) {
    if (DAT_28d3_273d == '\0') {
      uVar5 = param_3;
      DAT_28d3_58b8 = (undefined1 *)FUN_1000_4dd4(0x23);
      DAT_28d3_273d = '\x01';
      DAT_28d3_58ba = uVar5;
    }
    puVar4 = DAT_28d3_58b8;
    uVar5 = DAT_28d3_58ba;
    if ((param_2 | param_3) != 0) {
      puVar4 = (undefined1 *)&DAT_28d3_4ff6;
      uVar5 = 0x1000;
    }
    uVar3 = 0x23;
  }
  else if (param_1 == 8) {
    FUN_1000_4de7(0,0x4f12,0x1000);
    uVar5 = 0x1000;
    puVar4 = (undefined1 *)0x4f84;
    uVar3 = 4;
  }
  else {
    if (param_1 == 0xb) {
      if (DAT_28d3_273c != '\0') {
        return uVar1;
      }
      DAT_28d3_58b4 = FUN_1000_4dd4(5);
      DAT_28d3_58b6 = param_3;
      FUN_1000_4de7(5,0x4e1e,0x1000);
      DAT_28d3_273c = 1;
      return uVar1;
    }
    if (param_1 != 4) {
      return uVar1;
    }
    uVar5 = 0x1000;
    puVar4 = (undefined1 *)0x4ea0;
    uVar3 = 6;
  }
  FUN_1000_4de7(uVar3,puVar4,uVar5);
  return uVar1;
}



// Function: FUN_1000_51c4

undefined2 __cdecl16far FUN_1000_51c4(int param_1)

{
  code *pcVar1;
  code *pcVar2;
  uint local_6;
  int local_4;
  
  local_4 = FUN_1000_5071(param_1);
  if (local_4 == -1) {
    return 1;
  }
  local_6 = *(uint *)(local_4 * 4 + 0x2742);
  pcVar1 = *(code **)(local_4 * 4 + 0x2740);
  if ((local_6 == 0) && (pcVar1 == (code *)((int)(undefined2 *)&DAT_28d3_0000 + 1U))) {
    return 0;
  }
  if (((uint)pcVar1 | local_6) != 0) {
    *(undefined2 *)(local_4 * 4 + 0x2742) = 0;
    *(undefined2 *)(local_4 * 4 + 0x2740) = 0;
    (*pcVar1)(0x1000,param_1,*(undefined *)(local_4 + 0x275e));
    return 0;
  }
  if (param_1 != 2) {
    if (param_1 != 0x16) goto LAB_1000_5222;
    FUN_1000_4db9();
  }
  pcVar2 = (code *)swi(0x23);
  (*pcVar2)();
  pcVar2 = (code *)swi(0x21);
  (*pcVar2)();
LAB_1000_5222:
  FUN_1000_4d81(1);
  return 0;
}



// Function: FUN_1000_525b

void __cdecl16far
FUN_1000_525b(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5)

{
  undefined local_a [8];
  
  FUN_1000_4dfc(local_a);
  FUN_1000_5290(param_1,param_2,param_3,param_4,param_5,local_a);
  return;
}



// Function: FUN_1000_5290

undefined2 __cdecl16far
FUN_1000_5290(byte param_1,undefined4 param_2,undefined2 *param_3,undefined2 *param_4)

{
  uint *puVar1;
  uint uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  char cVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  int iVar9;
  undefined2 *puVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  undefined2 uVar13;
  byte bVar14;
  byte bVar15;
  byte in_AF;
  byte bVar16;
  byte bVar17;
  byte in_TF;
  byte in_IF;
  byte bVar18;
  byte in_NT;
  undefined4 uVar19;
  undefined local_10;
  undefined local_f;
  byte local_e;
  undefined local_d [3];
  code *local_a;
  undefined2 local_8;
  code *local_6;
  
  local_6 = (code *)&local_10;
  local_10 = (code)0x55;
  local_f = 0xcd;
  local_e = param_1;
  local_d = (undefined  [3])CONCAT12(local_d[2],0xcb5d);
  bVar18 = SBORROW1(param_1,'%');
  cVar5 = param_1 - 0x25;
  bVar17 = cVar5 < '\0';
  bVar16 = cVar5 == '\0';
  bVar15 = (POPCOUNT(cVar5) & 1U) == 0;
  if (0x24 < param_1) {
    bVar18 = SBORROW1(param_1,'&');
    cVar5 = param_1 - 0x26;
    bVar17 = cVar5 < '\0';
    bVar16 = cVar5 == '\0';
    bVar15 = (POPCOUNT(cVar5) & 1U) == 0;
    if (param_1 < 0x26 || (bool)bVar16) {
      local_d = (undefined  [3])0x68f36;
      local_8 = 0xcb5d;
      local_a = local_6;
    }
  }
  uVar11 = (undefined2)((ulong)param_4 >> 0x10);
  uVar13 = *param_4;
  uVar3 = ((undefined2 *)param_4)[3];
  uVar12 = (undefined2)((ulong)param_2 >> 0x10);
  iVar9 = (int)param_2;
  uVar8 = *(undefined2 *)(iVar9 + 2);
  uVar7 = *(undefined2 *)(iVar9 + 4);
  uVar4 = *(undefined2 *)(iVar9 + 10);
  uVar12 = *(undefined2 *)(iVar9 + 8);
  bVar14 = 0;
  uVar19 = (*local_6)(0x1000,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  uVar6 = (undefined2)uVar19;
  *param_4 = uVar13;
  ((undefined2 *)param_4)[3] = uVar3;
  uVar13 = (undefined2)((ulong)param_3 >> 0x10);
  puVar10 = (undefined2 *)param_3;
  puVar10[4] = uVar12;
  puVar10[7] = (uint)(in_NT & 1) * 0x4000 | (uint)(bVar18 & 1) * 0x800 | (uint)(in_IF & 1) * 0x200 |
               (uint)(in_TF & 1) * 0x100 | (uint)(bVar17 & 1) * 0x80 | (uint)(bVar16 & 1) * 0x40 |
               (uint)(in_AF & 1) * 0x10 | (uint)(bVar15 & 1) * 4 | (uint)(bVar14 & 1);
  puVar10[6] = (uint)(in_NT & 1) * 0x4000 | (uint)(bVar18 & 1) * 0x800 | (uint)(in_IF & 1) * 0x200 |
               (uint)(in_TF & 1) * 0x100 | (uint)(bVar17 & 1) * 0x80 | (uint)(bVar16 & 1) * 0x40 |
               (uint)(in_AF & 1) * 0x10 | (uint)(bVar15 & 1) * 4 | (uint)(bVar14 & 1);
  puVar1 = puVar10 + 6;
  *puVar1 = *puVar1 & 1;
  uVar2 = *puVar1;
  puVar10[5] = uVar4;
  puVar10[3] = (int)((ulong)uVar19 >> 0x10);
  puVar10[2] = uVar7;
  puVar10[1] = uVar8;
  *param_3 = uVar6;
  if (uVar2 != 0) {
    FUN_1000_1f84(uVar6);
  }
  return uVar6;
}



// Function: FUN_1000_532a

void __cdecl16near FUN_1000_532a(void)

{
  return;
}



// Function: FUN_1000_532f

uint __cdecl16near FUN_1000_532f(void)

{
  undefined uVar1;
  undefined uVar2;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  
  out(0x43,0);
  FUN_1000_532a((uint)(in_NT & 1) * 0x4000 | (uint)(in_OF & 1) * 0x800 | (uint)(in_IF & 1) * 0x200 |
                (uint)(in_TF & 1) * 0x100 | (uint)(in_SF & 1) * 0x80 | (uint)(in_ZF & 1) * 0x40 |
                (uint)(in_AF & 1) * 0x10 | (uint)(in_PF & 1) * 4 | (uint)(in_CF & 1));
  uVar1 = in(0x40);
  FUN_1000_532a();
  uVar2 = in(0x40);
  return ~CONCAT11(uVar2,uVar1);
}



// Function: FUN_1000_534d

void __cdecl16far FUN_1000_534d(void)

{
  uint uVar1;
  int local_4;
  
  local_4 = 0;
  do {
    uVar1 = FUN_1000_532f();
    if ((uVar1 & 1) == 0) {
      DAT_28d3_2764 = 0x4a9;
      DAT_28d3_2766 = 0;
      return;
    }
    local_4 = local_4 + 1;
  } while (local_4 < 100);
  return;
}



// Function: FUN_1000_537f

void __cdecl16far FUN_1000_537f(void)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  long lVar4;
  uint local_8;
  uint local_4;
  
  uVar1 = FUN_1000_532f();
  lVar4 = FUN_1000_3f98();
  local_4 = (uint)(lVar4 + (ulong)uVar1 >> 0x10);
  local_8 = uVar1;
  do {
    uVar2 = FUN_1000_532f();
    if (local_4 == 0) {
      if (local_4 != 0) {
        return;
      }
      if ((uint)(lVar4 + (ulong)uVar1) <= uVar2) {
        return;
      }
    }
    bVar3 = uVar2 < local_8;
    local_8 = uVar2;
    if (bVar3) {
      if ((local_4 < 2) && (local_4 == 0)) {
        return;
      }
      local_4 = local_4 - 1;
    }
  } while( true );
}



// Function: FUN_1000_53e0

void __cdecl16far FUN_1000_53e0(undefined2 *param_1)

{
  code *pcVar1;
  undefined2 in_CX;
  undefined2 extraout_DX;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  *param_1 = in_CX;
  ((undefined2 *)param_1)[1] = extraout_DX;
  return;
}



// Function: FUN_1000_53f7

void __cdecl16far FUN_1000_53f7(undefined2 *param_1)

{
  code *pcVar1;
  undefined2 in_CX;
  undefined2 extraout_DX;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  *param_1 = in_CX;
  ((undefined2 *)param_1)[1] = extraout_DX;
  return;
}



// Function: FUN_1000_5418

undefined2 __cdecl16far FUN_1000_5418(uint param_1,uint param_2)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_SS;
  
  uVar1 = *(undefined2 *)((int)*(undefined4 *)0x16 + 10);
  if ((param_1 | param_2) != 0) {
    uVar3 = (undefined2)((ulong)*(undefined4 *)0x16 >> 0x10);
    iVar2 = (int)*(undefined4 *)0x16;
    *(uint *)(iVar2 + 0xc) = param_2;
    *(uint *)(iVar2 + 10) = param_1;
  }
  *(char **)((int)*(undefined4 *)0x16 + 0x12) =
       (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  return uVar1;
}



// Function: FUN_1000_548d

void __cdecl16far FUN_1000_548d(void)

{
  code *pcVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_SS;
  undefined2 local_26;
  char *local_24;
  undefined2 local_22;
  undefined2 local_20;
  undefined2 local_14;
  
  FUN_1000_5c93();
  local_24 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  FUN_1000_27c4();
  uVar3 = (undefined2)((ulong)*(undefined4 *)0x16 >> 0x10);
  iVar2 = (int)*(undefined4 *)0x16;
  local_26 = *(undefined2 *)(iVar2 + 0xc);
  pcVar1 = *(code **)(iVar2 + 10);
  local_14 = 6;
  if (*(int *)((int)*(undefined4 *)0x16 + 0x12) == 0) {
    *(char **)((int)*(undefined4 *)0x16 + 0x12) =
         (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  }
  local_22 = *(undefined2 *)((int)*(undefined4 *)0x16 + 0x12);
  (*pcVar1)(0x1000);
  local_14 = 0;
  FUN_1000_4cca();
  FUN_1000_5d02(local_20);
  return;
}



// Function: FUN_1000_5515

undefined2 __cdecl16far FUN_1000_5515(uint param_1,uint param_2)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_SS;
  
  uVar1 = *(undefined2 *)((int)*(undefined4 *)0x16 + 0xe);
  if ((param_1 | param_2) != 0) {
    uVar3 = (undefined2)((ulong)*(undefined4 *)0x16 >> 0x10);
    iVar2 = (int)*(undefined4 *)0x16;
    *(uint *)(iVar2 + 0x10) = param_2;
    *(uint *)(iVar2 + 0xe) = param_1;
  }
  *(char **)((int)*(undefined4 *)0x16 + 0x14) =
       (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  return uVar1;
}



// Function: FUN_1000_5560

void __cdecl16far FUN_1000_5560(void)

{
  code *pcVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_SS;
  undefined2 local_6;
  undefined2 local_4;
  
  uVar3 = (undefined2)((ulong)*(undefined4 *)0x16 >> 0x10);
  iVar2 = (int)*(undefined4 *)0x16;
  local_6 = *(undefined2 *)(iVar2 + 0x10);
  pcVar1 = *(code **)(iVar2 + 0xe);
  if (*(int *)((int)*(undefined4 *)0x16 + 0x14) == 0) {
    *(char **)((int)*(undefined4 *)0x16 + 0x14) =
         (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  }
  local_4 = *(undefined2 *)((int)*(undefined4 *)0x16 + 0x14);
  (*pcVar1)(0x1000,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_1000_4cca();
  return;
}



// Function: FUN_1000_55af

undefined2 __cdecl16far FUN_1000_55af(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  
  if (((uint)param_1 | param_1._2_2_) == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = *(int *)((uint)param_1 + param_2) - *(int *)(*(int *)((uint)param_1 + param_2) + -2);
    uVar1 = *(undefined2 *)(*(int *)(iVar2 + -8) + 0x1a);
  }
  return uVar1;
}



// Function: FUN_1000_5603

undefined2 __cdecl16far FUN_1000_5603(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  
  if (((uint)param_1 | param_1._2_2_) == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = ((int *)((uint)param_1 + param_2))[1];
    iVar3 = *(int *)((uint)param_1 + param_2);
    iVar3 = iVar3 - *(int *)(iVar3 + -2);
    uVar2 = *(undefined2 *)(*(int *)(iVar3 + -8) + 0x1a);
  }
  return uVar2;
}



// Function: FUN_1000_565b

void __cdecl16far FUN_1000_565b(void)

{
  int iVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_SS;
  
  *(undefined2 *)0x12 = 0;
  *(undefined2 *)0x10 = 0;
  *(char **)0x18 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  *(undefined2 *)0x16 = 0x2768;
  *(undefined2 *)0x1a = 0xfeed;
  DAT_28d3_277c = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  DAT_28d3_277a = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  iVar1 = *(int *)0x16;
  uVar3 = (undefined2)((ulong)*(undefined4 *)0x16 >> 0x10);
  iVar2 = (int)*(undefined4 *)0x16;
  *(undefined2 *)(iVar2 + 0x22) = *(undefined2 *)0x18;
  *(int *)(iVar2 + 0x20) = iVar1 + 0xa8;
  *(undefined2 *)0x14 = 0xffff;
  return;
}



// Function: FUN_1000_56a9

undefined2 __cdecl16far
FUN_1000_56a9(undefined4 param_1,undefined2 param_3,undefined2 param_4,undefined2 param_5)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  uint in_DX;
  
  if (((uint)param_1 | param_1._2_2_) == 0) {
    uVar2 = FUN_1000_44b3(6);
    param_1 = CONCAT22(in_DX,uVar2);
    if ((uVar2 | in_DX) == 0) goto code_r0x000156e9;
  }
  FUN_1000_58d4((uint)param_1,param_1._2_2_,param_3,param_4);
  *(undefined2 *)((uint)param_1 + 4) = param_5;
code_r0x000156e9:
  puVar3 = (uint *)FUN_1000_5c87();
  puVar1 = puVar3;
  uVar2 = *puVar1;
  *puVar1 = *puVar1 + 1;
  puVar3[1] = puVar3[1] + (uint)(0xfffe < uVar2);
  return (uint)param_1;
}



// Function: FUN_1000_5728

void FUN_1000_5728(undefined2 param_1,int param_2,undefined2 param_3)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  undefined2 uVar13;
  undefined auStack_8 [4];
  undefined2 uStack_4;
  
  FUN_1000_5c93();
  uVar13 = 0;
  uVar12 = 0;
  uVar11 = 0;
  uVar10 = 0;
  uVar9 = 5;
  uVar8 = 0x1000;
  uVar7 = 0x57a5;
  uVar6 = 0;
  uVar5 = 0;
  uVar4 = param_3;
  FUN_1000_599f(auStack_8);
  uStack_4 = *(undefined2 *)(param_2 + 4);
  puVar3 = (uint *)FUN_1000_5c87(uVar5,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13);
  puVar1 = puVar3;
  uVar2 = *puVar1;
  *puVar1 = *puVar1 + 1;
  puVar3[1] = puVar3[1] + (uint)(0xfffe < uVar2);
  FUN_1000_6bc3((undefined2 *)&DAT_28d3_57e8,0x1000,auStack_8);
  return;
}



// Function: caseD_0

void __cdecl16far switchD_1000:dd7c::caseD_0(void)

{
  uint *puVar1;
  uint uVar2;
  undefined2 uVar3;
  uint *puVar4;
  undefined2 uVar5;
  int unaff_BP;
  undefined2 unaff_SS;
  
  uVar5 = *(undefined2 *)(unaff_BP + 8);
  uVar3 = *(undefined2 *)(unaff_BP + 6);
  *(undefined2 *)(unaff_BP + -0x26) = uVar5;
  *(undefined2 *)(unaff_BP + -0x28) = uVar3;
  FUN_1000_599f(unaff_BP + -6);
  *(undefined2 *)(unaff_BP + -2) = *(undefined2 *)((int)*(undefined4 *)(unaff_BP + -0x28) + 4);
  puVar4 = (uint *)FUN_1000_5c87();
  puVar1 = puVar4;
  uVar2 = *puVar1;
  *puVar1 = *puVar1 + 1;
  puVar4[1] = puVar4[1] + (uint)(0xfffe < uVar2);
  FUN_1000_6bc3((undefined2 *)&DAT_28d3_57e8,0x1000,unaff_BP + -6);
  return;
}



// Function: FUN_1000_57a5

int __cdecl16far FUN_1000_57a5(undefined4 param_1,undefined4 param_3)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  undefined2 in_DX;
  
  FUN_1000_599f((int)param_1,param_1._2_2_,(int)param_3,param_3._2_2_);
  *(undefined2 *)((int)param_1 + 4) = *(undefined2 *)((int)param_3 + 4);
  puVar3 = (uint *)FUN_1000_5c87();
  puVar1 = puVar3;
  uVar2 = *puVar1;
  *puVar1 = *puVar1 + 1;
  puVar3[1] = puVar3[1] + (uint)(0xfffe < uVar2);
  return (int)param_1;
}



// Function: FUN_1000_58d4

uint * __cdecl16far FUN_1000_58d4(uint *param_1,undefined2 param_3,undefined2 param_4)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  int *piVar6;
  uint in_DX;
  uint uVar7;
  undefined2 local_24;
  
  FUN_1000_5c93();
  if (((uint)(uint *)param_1 | param_1._2_2_) == 0) {
    puVar4 = (uint *)FUN_1000_44b3(4);
    param_1 = (uint *)CONCAT22(in_DX,puVar4);
    if (((uint)puVar4 | in_DX) == 0) goto code_r0x00015956;
  }
  uVar5 = FUN_1000_44b3(4);
  if ((uVar5 | in_DX) != 0) {
    uVar7 = in_DX;
    FUN_280e_0000(uVar5,in_DX,param_3,param_4);
    piVar6 = (int *)FUN_1000_5c87();
    piVar1 = piVar6;
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    piVar6[1] = piVar6[1] - (uint)(iVar3 == 0);
  }
  ((uint *)param_1)[1] = in_DX;
  *param_1 = uVar5;
code_r0x00015956:
  puVar4 = (uint *)FUN_1000_5c87();
  puVar2 = puVar4;
  uVar5 = *puVar2;
  *puVar2 = *puVar2 + 1;
  puVar4[1] = puVar4[1] + (uint)(0xfffe < uVar5);
  FUN_1000_5d02(local_24);
  return (uint *)param_1;
}



// Function: FUN_1000_599f

uint * __cdecl16far FUN_1000_599f(uint *param_1,undefined2 *param_2)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  int *piVar6;
  uint in_DX;
  uint uVar7;
  undefined2 local_24;
  
  FUN_1000_5c93();
  if (((uint)(uint *)param_1 | param_1._2_2_) == 0) {
    puVar4 = (uint *)FUN_1000_44b3(4);
    param_1 = (uint *)CONCAT22(in_DX,puVar4);
    if (((uint)puVar4 | in_DX) == 0) goto code_r0x00015a25;
  }
  uVar5 = FUN_1000_44b3(4);
  if ((uVar5 | in_DX) != 0) {
    uVar7 = in_DX;
    FUN_280e_0000(uVar5,in_DX,*param_2,((undefined2 *)param_2)[1]);
    piVar6 = (int *)FUN_1000_5c87();
    piVar1 = piVar6;
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    piVar6[1] = piVar6[1] - (uint)(iVar3 == 0);
  }
  ((uint *)param_1)[1] = in_DX;
  *param_1 = uVar5;
code_r0x00015a25:
  puVar4 = (uint *)FUN_1000_5c87();
  puVar2 = puVar4;
  uVar5 = *puVar2;
  *puVar2 = *puVar2 + 1;
  puVar4[1] = puVar4[1] + (uint)(0xfffe < uVar5);
  FUN_1000_5d02(local_24);
  return (uint *)param_1;
}



// Function: FUN_1000_5a4a

void __cdecl16far FUN_1000_5a4a(undefined2 *param_1,uint param_2)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  uint *puVar6;
  undefined2 in_DX;
  
  piVar5 = (int *)FUN_1000_5c87();
  piVar1 = piVar5;
  iVar3 = *piVar1;
  *piVar1 = *piVar1 + -1;
  piVar5[1] = piVar5[1] - (uint)(iVar3 == 0);
  if (((uint)(undefined2 *)param_1 | param_1._2_2_) != 0) {
    puVar6 = (uint *)FUN_1000_5c87();
    puVar2 = puVar6;
    uVar4 = *puVar2;
    *puVar2 = *puVar2 + 1;
    puVar6[1] = puVar6[1] + (uint)(0xfffe < uVar4);
    FUN_280e_0305(*param_1,((undefined2 *)param_1)[1],3);
    if ((param_2 & 1) != 0) {
      FUN_1000_441a((undefined2 *)param_1,param_1._2_2_);
    }
  }
  return;
}



// Function: FUN_1000_5c87

undefined2 __cdecl16far FUN_1000_5c87(void)

{
  return 0x10;
}



// Function: FUN_1000_5c8d

undefined2 __cdecl16far FUN_1000_5c8d(void)

{
  return 0x14;
}



// Function: FUN_1000_5c93

void __cdecl16far FUN_1000_5c93(void)

{
  undefined2 uVar1;
  undefined2 in_AX;
  undefined2 *puVar2;
  undefined2 uVar3;
  int in_BX;
  undefined2 *puVar4;
  int unaff_BP;
  undefined2 unaff_SI;
  undefined2 unaff_SS;
  
  puVar4 = (undefined2 *)(*(int *)(in_BX + 4) + unaff_BP);
  puVar4[3] = in_BX;
  puVar4[4] = in_AX;
  puVar4[5] = &stack0x0004;
  puVar4[7] = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  puVar4[8] = unaff_SI;
  puVar4[1] = 0x7abf;
  puVar4[2] = 0x1000;
  puVar4[6] = 0;
  puVar4[9] = 0;
  puVar2 = (undefined2 *)FUN_1000_5c87();
  uVar3 = puVar2[1];
  puVar4[0xd] = *puVar2;
  puVar4[0xe] = uVar3;
  puVar2 = (undefined2 *)FUN_1000_5c8d();
  uVar1 = *puVar2;
  *puVar2 = puVar4;
  *puVar4 = uVar1;
  return;
}



// Function: FUN_1000_5d02

void __stdcall16far FUN_1000_5d02(undefined2 param_1)

{
  undefined2 *puVar1;
  undefined2 in_DX;
  
  puVar1 = (undefined2 *)FUN_1000_5c8d();
  *puVar1 = param_1;
  return;
}



// Function: FUN_1000_5d22

char * __cdecl16far FUN_1000_5d22(undefined4 param_1)

{
  char *pcVar1;
  
  if (((uint)param_1 | param_1._2_2_) == 0) {
    pcVar1 = (char *)s_<notype>_28d3_2890;
  }
  else {
    pcVar1 = (char *)((uint)param_1 + *(int *)((uint)param_1 + 4));
  }
  return pcVar1;
}



// Function: FUN_1000_5d47

undefined2 __cdecl16far FUN_1000_5d47(int *param_1,int *param_3)

{
  char cVar1;
  char cVar2;
  undefined4 local_a;
  undefined4 local_6;
  
  if ((param_1._2_2_ != param_3._2_2_) || ((int *)param_1 != (int *)param_3)) {
    if ((((int *)param_1)[1] != ((int *)param_3)[1]) ||
       ((*param_1 != *param_3 || (((((int *)param_1)[1] | ((int *)param_3)[1]) & 0x80U) != 0)))) {
      return 0;
    }
    local_6 = (char *)CONCAT22(param_1._2_2_,(char *)((int)(int *)param_1 + ((int *)param_1)[2]));
    local_a = (char *)CONCAT22(param_3._2_2_,(char *)((int)(int *)param_3 + ((int *)param_3)[2]));
    do {
      cVar1 = *local_6;
      local_6 = (char *)CONCAT22(local_6._2_2_,(char *)local_6 + 1);
      cVar2 = *local_a;
      local_a = (char *)CONCAT22(local_a._2_2_,(char *)local_a + 1);
      if (cVar1 != cVar2) {
        return 0;
      }
    } while (cVar1 != '\0');
  }
  return 1;
}



// Function: FUN_1000_5de5

undefined2 __cdecl16near
FUN_1000_5de5(undefined4 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5,int param_6)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  uint *local_6;
  
  uVar7 = (undefined2)((ulong)param_1 >> 0x10);
  iVar5 = (int)param_1;
  local_6 = (uint *)CONCAT22(uVar7,(uint *)(iVar5 + *(int *)(iVar5 + 0xc)));
  do {
    uVar8 = (undefined2)((ulong)local_6 >> 0x10);
    puVar6 = (uint *)local_6;
    uVar1 = puVar6[1];
    uVar2 = *local_6;
    if ((uVar2 | uVar1) == 0) {
      local_6 = (uint *)CONCAT22(uVar7,(uint *)(iVar5 + *(int *)(iVar5 + 10)));
      while( true ) {
        uVar7 = (undefined2)((ulong)local_6 >> 0x10);
        puVar6 = (uint *)local_6;
        uVar1 = puVar6[1];
        uVar2 = *local_6;
        if ((uVar2 | uVar1) == 0) {
          return 0;
        }
        if ((param_6 == 0) || ((puVar6[3] & 3) != 3)) {
          iVar5 = 0;
        }
        else {
          iVar5 = 1;
        }
        iVar3 = FUN_1000_5d47(param_2,param_3,uVar2,uVar1);
        if (((iVar3 != 0) && (iVar5 != 0)) ||
           (((*(uint *)(uVar2 + 8) & 4) != 0 &&
            (iVar5 = FUN_1000_5de5(uVar2,uVar1,param_2,param_3,param_4,param_5,iVar5), iVar5 != 0)))
           ) break;
        local_6 = (uint *)CONCAT22(uVar7,puVar6 + 4);
      }
      return 1;
    }
    if ((puVar6[3] & 8) == 0) {
      if ((param_6 == 0) || ((puVar6[3] & 3) != 3)) {
        iVar3 = 0;
      }
      else {
        iVar3 = 1;
      }
      iVar4 = FUN_1000_5d47(param_2,param_3,uVar2,uVar1);
      if ((iVar4 != 0) && (iVar3 != 0)) {
        return 1;
      }
      if (((*(uint *)(uVar2 + 8) & 4) != 0) &&
         (iVar3 = FUN_1000_5de5(uVar2,uVar1,param_2,param_3,param_4,param_5,iVar3), iVar3 != 0)) {
        return 1;
      }
    }
    local_6 = (uint *)CONCAT22(uVar8,puVar6 + 4);
  } while( true );
}



// Function: FUN_1000_5f3b

undefined2 __cdecl16near
FUN_1000_5f3b(undefined4 param_1,undefined4 param_3,int param_5,undefined2 param_6,
             undefined2 param_7)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined2 uVar4;
  uint local_6;
  uint local_4;
  
  do {
    if ((param_1._2_2_ == param_3._2_2_) && ((int)param_1 == (int)param_3)) goto LAB_1000_6070;
    uVar1 = *(uint *)((int)param_1 + 2);
    uVar2 = *(uint *)((int)param_3 + 2);
    if ((uVar1 & uVar2 & 0x10) == 0) {
      if ((uVar1 & uVar2 & 0x400) == 0) {
        iVar3 = FUN_1000_5d47((int)param_1,param_1._2_2_,(int)param_3,param_3._2_2_);
        if (iVar3 != 0) goto LAB_1000_6070;
        if ((((uVar1 & 2) != 0) && ((uVar2 & 1) != 0)) && ((*(uint *)((int)param_1 + 8) & 4) != 0))
        {
          uVar4 = FUN_1000_5de5((int)param_1,param_1._2_2_,(int)param_3,param_3._2_2_,param_6,
                                param_7,1);
          return uVar4;
        }
        goto LAB_1000_60ac;
      }
      if (((*(int *)((int)param_1 + 0xc) != *(int *)((int)param_3 + 0xc)) ||
          (*(int *)((int)param_1 + 10) != *(int *)((int)param_3 + 10))) &&
         ((param_5 != 0 ||
          ((*(uint *)((int)param_1 + 10) | *(uint *)((int)param_3 + 10) |
           *(uint *)((int)param_1 + 0xc) | *(uint *)((int)param_3 + 0xc)) != 0))))
      goto LAB_1000_60ac;
    }
    else {
      local_4 = uVar1 & 0x3300;
      local_6 = uVar2 & 0x3300;
      if (local_4 != local_6) {
        if (param_5 != 0) goto LAB_1000_60ac;
        if ((uVar1 & 0x300) == (uVar2 & 0x300)) {
LAB_1000_5fca:
          if (((local_4 | 0x3000) == (local_6 | 0x3000)) && ((local_4 & 0x1000) != 0)) {
LAB_1000_6070:
            uVar4 = 1;
          }
          else {
LAB_1000_60ac:
            uVar4 = 0;
          }
          return uVar4;
        }
        if ((~(uVar2 & 0x300) & local_4 & 0x300) != 0) goto LAB_1000_60ac;
        local_4 = local_4 | 0x300;
        local_6 = local_6 | 0x300;
        if (local_4 != local_6) goto LAB_1000_5fca;
      }
    }
    param_5 = 1;
    param_1 = CONCAT22(*(undefined2 *)((int)param_1 + 8),*(undefined2 *)((int)param_1 + 6));
    param_3 = CONCAT22(*(undefined2 *)((int)param_3 + 8),*(undefined2 *)((int)param_3 + 6));
  } while( true );
}



// Function: FUN_1000_60b4

uint __cdecl16far FUN_1000_60b4(uint param_1)

{
  uint *puVar1;
  uint uVar2;
  uint in_DX;
  undefined2 unaff_SS;
  
  uVar2 = FUN_1000_4752(param_1);
  if ((uVar2 | in_DX) == 0) {
    if ((0x80 < param_1) || ((*(uint *)((int)*(undefined4 *)0x16 + 4) & 1) != 0)) {
      FUN_1000_4cca();
    }
    puVar1 = (uint *)((int)*(undefined4 *)0x16 + 4);
    *puVar1 = *puVar1 | 1;
    uVar2 = *(uint *)((int)*(undefined4 *)0x16 + 0x20);
  }
  return uVar2;
}



// Function: FUN_1000_6111

void __cdecl16far FUN_1000_6111(int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_SS;
  
  uVar3 = (undefined2)((ulong)*(undefined4 *)0x16 >> 0x10);
  iVar2 = (int)*(undefined4 *)0x16;
  if ((*(int *)(iVar2 + 0x22) == param_2) && (*(int *)(iVar2 + 0x20) == param_1)) {
    puVar1 = (uint *)((int)*(undefined4 *)0x16 + 4);
    *puVar1 = *puVar1 & 0xfffe;
  }
  else {
    FUN_1000_4648(param_1,param_2);
  }
  return;
}



// Function: FUN_1000_614a

bool __cdecl16near
FUN_1000_614a(undefined4 param_1,undefined2 param_3,undefined2 param_4,undefined4 param_5,
             uint param_7)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  uint local_6;
  
  iVar3 = FUN_1000_5f3b((int)param_1,param_1._2_2_,(int)param_5,param_5._2_2_,0,param_3,param_4);
  if (iVar3 == 0) {
    uVar1 = *(uint *)((int)param_1 + 2);
    local_6 = *(uint *)((int)param_5 + 2);
    if ((local_6 & 0x20) == 0) {
LAB_1000_6206:
      if ((local_6 & 0x10) != 0) {
        if ((param_7 & 1) != 0) goto LAB_1000_6214;
        if (((uVar1 & 0x10) != 0) &&
           ((((uVar1 & 0x2000) == 0 || ((local_6 & 0x2000) != 0)) && ((local_6 & 0x40) != 0)))) {
          return (uVar1 & 0x300) == (local_6 & 0x300);
        }
      }
    }
    else {
      iVar3 = FUN_1000_5f3b((int)param_1,param_1._2_2_,*(undefined2 *)((int)param_5 + 6),
                            *(undefined2 *)((int)param_5 + 8),1,param_3,param_4);
      if (iVar3 != 0) goto LAB_1000_6214;
      local_6 = *(uint *)(*(int *)((int)param_5 + 6) + 2);
      if ((local_6 & 0x10) != 0) {
        iVar3 = FUN_1000_5f3b((int)param_1,param_1._2_2_,*(int *)((int)param_5 + 6),
                              *(undefined2 *)((int)param_5 + 8),0,param_3,param_4);
        if (iVar3 != 0) goto LAB_1000_6214;
        if ((uVar1 & 0x3000) == (local_6 & 0x3000)) goto LAB_1000_6206;
      }
    }
    bVar2 = false;
  }
  else {
LAB_1000_6214:
    bVar2 = true;
  }
  return bVar2;
}



// Function: FUN_1000_6257

void __cdecl16near
FUN_1000_6257(undefined4 param_1,undefined2 param_3,undefined2 param_4,code *param_5,
             undefined2 param_5_00,uint param_6)

{
  uint uVar1;
  undefined2 unaff_SS;
  undefined2 uVar2;
  undefined2 uVar3;
  uint local_6;
  
  uVar2 = *(undefined2 *)((int)*(undefined4 *)0x16 + 6);
  local_6 = param_6 & 1;
  if ((param_6 & 4) != 0) {
    local_6 = local_6 | 2;
  }
  uVar1 = local_6;
  if (((param_6 & 2) != 0) && (uVar1 = local_6 | 4, (param_6 & 0x100) == 0)) {
    uVar1 = local_6 | 0x24;
  }
  local_6 = uVar1;
  if ((param_6 & 0x20) != 0) {
    local_6 = local_6 | 8;
  }
  if ((param_6 & 0x80) != 0) {
    local_6 = local_6 | 0x10;
  }
  if ((param_6 & 0x1000) == 0) {
    switch(local_6) {
    case 0:
      (*param_5)((undefined2)param_1,param_3);
      break;
    case 1:
LAB_1000_63c0:
      (*param_5)(0x1000,(undefined2)param_1,param_3);
      break;
    case 2:
      (*param_5)((undefined2)param_1,param_1._2_2_,param_3,param_4);
      break;
    case 3:
      (*param_5)(0x1000,(undefined2)param_1,param_1._2_2_,param_3,param_4);
      break;
    case 4:
      uVar2 = param_3;
LAB_1000_63ff:
      (*param_5)((undefined2)param_1,uVar2);
      break;
    case 5:
      uVar3 = param_3;
LAB_1000_640d:
      (*param_5)(0x1000,(undefined2)param_1,uVar3);
      break;
    case 6:
    case 10:
LAB_1000_6390:
      (*param_5)((undefined2)param_1,param_1._2_2_,param_3,param_4);
      break;
    case 7:
    case 0xb:
LAB_1000_63a3:
      (*param_5)(0x1000,(undefined2)param_1,param_1._2_2_,param_3,param_4);
      break;
    case 8:
      (*param_5)();
      break;
    case 9:
LAB_1000_637a:
      (*param_5)(0x1000);
      break;
    case 0x10:
      (*param_5)(param_3);
      break;
    case 0x11:
      (*param_5)(0x1000,param_3);
      break;
    case 0x12:
      (*param_5)(param_3,param_4,uVar2);
      break;
    case 0x13:
      (*param_5)(0x1000,param_3,param_4,uVar2);
      break;
    case 0x14:
      (*param_5)(param_3);
      break;
    case 0x15:
      (*param_5)(0x1000,param_3);
      break;
    case 0x16:
      (*param_5)(param_3,param_4,uVar2);
      break;
    case 0x17:
      (*param_5)(0x1000,param_3,param_4,uVar2);
    }
  }
  else {
    switch(local_6) {
    case 0:
      (*param_5)((undefined2)param_1,0,param_3);
      break;
    case 1:
      (*param_5)(0x1000,(undefined2)param_1,0,param_3);
      break;
    case 2:
      (*param_5)((undefined2)param_1,param_1._2_2_,0,param_3,param_4);
      break;
    case 3:
      (*param_5)(0x1000,(undefined2)param_1,param_1._2_2_,0,param_3,param_4);
      break;
    case 4:
      (*param_5)((undefined2)param_1,param_3,0);
      break;
    case 5:
      (*param_5)(0x1000,(undefined2)param_1,param_3,0);
      break;
    case 6:
      (*param_5)((undefined2)param_1,param_1._2_2_,param_3,param_4,0);
      break;
    case 7:
      (*param_5)(0x1000,(undefined2)param_1,param_1._2_2_,param_3,param_4,0);
      break;
    case 8:
      (*param_5)();
      break;
    case 9:
      goto LAB_1000_637a;
    case 10:
      goto LAB_1000_6390;
    case 0xb:
      goto LAB_1000_63a3;
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
      break;
    case 0x10:
      (*param_5)(0,param_3);
      break;
    case 0x11:
      param_1._0_2_ = 0;
      goto LAB_1000_63c0;
    case 0x12:
      (*param_5)(0,param_3,param_4,uVar2);
      break;
    case 0x13:
      (*param_5)(0x1000,0,param_3,param_4,uVar2);
      break;
    case 0x14:
      uVar2 = 0;
      param_1._0_2_ = param_3;
      goto LAB_1000_63ff;
    case 0x15:
      uVar3 = 0;
      param_1._0_2_ = param_3;
      goto LAB_1000_640d;
    case 0x16:
      (*param_5)(param_3,param_4,0,uVar2);
      break;
    case 0x17:
      (*param_5)(0x1000,param_3,param_4,0,uVar2,
                 (char *)s_String_reference_out_of_range_28d3_28cc + 7);
    }
  }
  return;
}



// Function: FUN_1000_65ab

void __cdecl16near
FUN_1000_65ab(undefined4 param_1,undefined2 param_2,undefined2 param_3_00,code *param_3,
             undefined2 param_5_00,uint param_4,int param_5)

{
  undefined2 uVar1;
  uint uVar2;
  undefined2 uVar3;
  undefined2 unaff_SS;
  uint local_8;
  
  if (param_5 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = 2;
  }
  uVar1 = *(undefined2 *)((int)*(undefined4 *)0x16 + 6);
  local_8 = param_4 & 1;
  if ((param_4 & 4) != 0) {
    local_8 = local_8 | 2;
  }
  uVar2 = local_8;
  if (((param_4 & 2) != 0) && (uVar2 = local_8 | 4, (param_4 & 0x100) == 0)) {
    uVar2 = local_8 | 0x24;
  }
  local_8 = uVar2;
  if ((param_4 & 0x20) != 0) {
    local_8 = local_8 | 8;
  }
  if ((param_4 & 0x80) != 0) {
    local_8 = local_8 | 0x10;
  }
  switch(local_8) {
  case 0:
    (*param_3)((undefined2)param_1,uVar3);
    break;
  case 1:
    (*param_3)(0x1000,(undefined2)param_1,uVar3);
    break;
  case 2:
    (*param_3)((undefined2)param_1,param_1._2_2_,uVar3);
    break;
  case 3:
    (*param_3)(0x1000,(undefined2)param_1,param_1._2_2_,uVar3);
    break;
  case 4:
    (*param_3)((undefined2)param_1,uVar3);
    break;
  case 5:
    goto LAB_1000_66c8;
  case 6:
    (*param_3)((undefined2)param_1,param_1._2_2_,uVar3);
    break;
  case 7:
    (*param_3)(0x1000,(undefined2)param_1,param_1._2_2_,uVar3);
    break;
  case 8:
    (*param_3)();
    break;
  case 9:
    (*param_3)(0x1000);
    break;
  case 10:
    (*param_3)((undefined2)param_1,param_1._2_2_);
    break;
  case 0xb:
    uVar3 = param_1._2_2_;
LAB_1000_66c8:
    (*param_3)(0x1000,(undefined2)param_1,uVar3);
    break;
  case 0x10:
    (*param_3)(uVar3);
    break;
  case 0x11:
    (*param_3)(0x1000,uVar3);
    break;
  case 0x12:
    (*param_3)(uVar3,uVar1);
    break;
  case 0x13:
    (*param_3)(0x1000,uVar3,uVar1);
    break;
  case 0x14:
    (*param_3)(uVar3);
    break;
  case 0x15:
    (*param_3)(0x1000,uVar3);
    break;
  case 0x16:
    (*param_3)(uVar3,uVar1);
    break;
  case 0x17:
    (*param_3)(0x1000,uVar3,uVar1,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  return;
}



// Function: FUN_1000_6768

void __cdecl16near
FUN_1000_6768(undefined2 param_1,undefined2 param_2,code *param_3,undefined2 param_4_00,uint param_4
             )

{
  undefined2 uVar1;
  undefined2 unaff_SS;
  uint local_6;
  
  uVar1 = *(undefined2 *)((int)*(undefined4 *)0x16 + 6);
  local_6 = param_4 & 1;
  if ((param_4 & 4) != 0) {
    local_6 = local_6 | 2;
  }
  if ((param_4 & 2) != 0) {
    local_6 = local_6 | 4;
  }
  if ((param_4 & 0x20) != 0) {
    local_6 = local_6 | 8;
  }
  switch(local_6) {
  case 0:
    (*param_3)(param_1);
    break;
  case 1:
    (*param_3)(0x1000,param_1);
    break;
  case 2:
    (*param_3)(param_1,param_2);
    break;
  case 3:
    (*param_3)(0x1000,param_1,param_2);
    break;
  case 4:
    (*param_3)(param_1);
    break;
  case 5:
    (*param_3)(0x1000,param_1);
    break;
  case 6:
  case 10:
    (*param_3)(param_1,param_2);
    break;
  case 7:
  case 0xb:
    (*param_3)(0x1000,param_1,param_2);
    break;
  case 8:
    (*param_3)();
    break;
  case 9:
    (*param_3)(0x1000,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  return;
}



// Function: FUN_1000_688a

void __cdecl16far
FUN_1000_688a(int *param_1,int param_2,undefined2 param_3,undefined2 param_4,undefined2 param_5,
             undefined2 param_6,undefined2 param_7,undefined2 param_8,undefined2 param_9,
             undefined2 param_10,undefined2 param_11,undefined2 param_12,undefined2 param_13,
             undefined2 param_14,undefined2 param_15,int param_16)

{
  undefined2 *puVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  undefined2 extraout_DX;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined2 uVar7;
  undefined2 unaff_SS;
  undefined2 local_4a;
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  undefined2 *local_42;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  undefined4 local_3a;
  undefined4 local_36;
  undefined4 local_32;
  uint local_2e;
  uint local_2c;
  int local_2a;
  int *local_28;
  int local_26;
  undefined4 local_24;
  undefined2 local_20;
  undefined2 local_14;
  
  FUN_1000_5c93();
  local_24 = (int *)CONCAT22(param_2,param_1);
  *(char **)((int)*(undefined4 *)0x16 + 6) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  iVar5 = *(int *)0x16;
  uVar7 = (undefined2)((ulong)*(undefined4 *)0x16 >> 0x10);
  iVar4 = (int)*(undefined4 *)0x16;
  *(undefined2 *)(iVar4 + 0x1e) = *(undefined2 *)0x18;
  *(int *)(iVar4 + 0x1c) = iVar5 + 0x28;
  uVar7 = (undefined2)((ulong)*(undefined4 *)0x16 >> 0x10);
  iVar5 = (int)*(undefined4 *)0x16;
  local_3a = (char *)CONCAT22(*(undefined2 *)(iVar5 + 0x1e),*(char **)(iVar5 + 0x1c));
  local_36 = (char *)CONCAT22(param_2,(char *)((int)param_1 + param_1[2]));
  while (*local_36 != '\0') {
    if ((char *)local_3a < (char *)(*(int *)((int)*(undefined4 *)0x16 + 0x1c) + 0x7f)) {
      *local_3a = *local_36;
      local_3a = (char *)CONCAT22(local_3a._2_2_,(char *)local_3a + 1);
    }
    local_36 = (char *)CONCAT22(local_36._2_2_,(char *)local_36 + 1);
  }
  *local_3a = '\0';
  *(undefined2 *)((int)*(undefined4 *)0x16 + 0x1a) = param_11;
  uVar7 = (undefined2)((ulong)*(undefined4 *)0x16 >> 0x10);
  iVar5 = (int)*(undefined4 *)0x16;
  *(undefined2 *)(iVar5 + 0x18) = param_13;
  *(undefined2 *)(iVar5 + 0x16) = param_12;
  local_26 = param_2;
  local_28 = param_1;
  local_2a = *local_24;
  local_2c = param_1[1];
  if ((local_2c & 2) == 0) {
    local_2e = 0;
  }
  else {
    local_2e = param_1[4];
  }
  if ((local_2c & 0x30) != 0) {
    local_26 = param_1[4];
    local_28 = (int *)param_1[3];
  }
  iVar5 = local_26;
  puVar3 = (undefined2 *)FUN_1000_60b4(local_2a + 0x3a);
  local_32 = (undefined2 *)CONCAT22(iVar5,puVar3);
  puVar1 = (undefined2 *)*(undefined4 *)0x16;
  uVar7 = *puVar1;
  puVar3[1] = ((undefined2 *)puVar1)[1];
  *local_32 = uVar7;
  uVar2 = *(undefined4 *)0x16;
  *(int *)((int)uVar2 + 2) = iVar5;
  *(undefined2 **)uVar2 = puVar3;
  puVar3[3] = local_24._2_2_;
  puVar3[2] = (int *)local_24;
  puVar3[6] = param_10;
  puVar3[7] = local_2a;
  puVar3[10] = local_2c;
  puVar3[0xb] = local_2e;
  puVar3[9] = local_26;
  puVar3[8] = local_28;
  puVar3[5] = param_6;
  puVar3[4] = param_5;
  puVar3[0x12] = 0;
  puVar3[0x14] = 0;
  puVar3[0x13] = 0;
  puVar3[0xc] = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  puVar3[0xe] = 0x1000;
  puVar3[0xd] = 0x6111;
  puVar3[0x16] = param_11;
  puVar3[0x18] = param_13;
  puVar3[0x17] = param_12;
  puVar3[0x10] = param_8;
  puVar3[0xf] = param_7;
  puVar3[0x11] = param_9;
  *(undefined *)((int)puVar3 + 0x39) = 0;
  *(undefined *)(puVar3 + 0x1c) = 1;
  uVar7 = param_8;
  FUN_1000_1a99(puVar3 + 0x1d,iVar5,param_3,param_4,local_2a);
  if ((local_2e & 1) != 0) {
    puVar3 = (undefined2 *)FUN_1000_5c87();
    local_3c = puVar3[1];
    local_3e = *puVar3;
    local_14 = 6;
    FUN_1000_6257((undefined2 *)local_32 + 0x1d,local_32._2_2_,param_3,param_4,param_7,param_8,
                  param_9);
    local_14 = 0;
    uVar7 = extraout_DX;
    puVar3 = (undefined2 *)FUN_1000_5c87();
    puVar3[1] = local_3c;
    *puVar3 = local_3e;
  }
  if ((param_16 == 0) && ((local_2e & 2) != 0)) {
    local_14 = 0x12;
    uVar7 = (undefined2)((ulong)local_24 >> 0x10);
    piVar6 = (int *)local_24;
    FUN_1000_65ab(param_3,param_4,piVar6,uVar7,piVar6[0xf],piVar6[0x10],piVar6[0x11],1);
    local_14 = 0;
  }
  uVar7 = (undefined2)((ulong)*(undefined4 *)0x16 >> 0x10);
  iVar5 = (int)*(undefined4 *)0x16;
  local_48 = *(undefined2 *)(iVar5 + 0x1e);
  local_4a = *(undefined2 *)(iVar5 + 0x1c);
  local_44 = param_15;
  local_46 = param_14;
  local_40 = local_32._2_2_;
  local_42 = (undefined2 *)local_32;
  FUN_1000_6da4(0xface,0xeef,1,0,3,0,&local_4a);
  FUN_1000_5d02(local_20);
  return;
}



// Function: FUN_1000_6bc3

void __cdecl16far
FUN_1000_6bc3(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5,undefined2 param_6,undefined2 param_7,undefined2 param_8,
             undefined2 param_9,undefined2 param_10,undefined2 param_11,undefined2 param_12,
             undefined2 param_13)

{
  undefined2 in_stack_00000000;
  undefined2 in_stack_00000002;
  
  FUN_1000_688a(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,in_stack_00000000,in_stack_00000002,0);
  return;
}



// Function: FUN_1000_6c1c

void __cdecl16far FUN_1000_6c1c(undefined2 param_1,undefined2 param_2,undefined2 param_3)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  uint unaff_SS;
  undefined2 in_stack_00000000;
  undefined2 in_stack_00000002;
  
  puVar3 = *(uint **)0x16;
  uVar1 = ((uint *)puVar3)[1];
  uVar2 = *puVar3;
  if ((uVar2 | uVar1) == 0) {
    FUN_1000_548d();
  }
  if (*(char *)(uVar2 + 0x38) == '\0') {
    iVar4 = *(int *)(uVar2 + 0x36);
  }
  else {
    iVar4 = uVar2 + 0x3a;
    unaff_SS = uVar1;
  }
  FUN_1000_688a(*(undefined2 *)(uVar2 + 4),*(undefined2 *)(uVar2 + 6),iVar4,unaff_SS,
                *(undefined2 *)(uVar2 + 8),*(undefined2 *)(uVar2 + 10),*(undefined2 *)(uVar2 + 0x1e)
                ,*(undefined2 *)(uVar2 + 0x20),*(undefined2 *)(uVar2 + 0x22),
                *(undefined2 *)(uVar2 + 0xc),param_1,param_2,param_3,in_stack_00000000,
                in_stack_00000002,1);
  return;
}



// Function: FUN_1000_6cc6

void __cdecl16far FUN_1000_6cc6(void)

{
  return;
}



// Function: FUN_1000_6ccb

undefined2 __cdecl16far
FUN_1000_6ccb(int param_1,undefined2 param_2,undefined2 param_3,undefined2 *param_4)

{
  int iVar1;
  undefined2 unaff_SS;
  bool bVar2;
  undefined2 *local_4;
  
  bVar2 = (*(uint *)(param_1 + 4) & 6) != 0;
  local_4 = (undefined2 *)*(undefined2 *)0x14;
  FUN_1000_6cc6();
  for (; (local_4 != (undefined2 *)0xffff && (local_4 != param_4)); local_4 = (undefined2 *)*local_4
      ) {
    iVar1 = (*(code *)local_4[1])(0x1000,param_1);
    if (iVar1 == 0) {
      return 0;
    }
    if (bVar2) {
      *(undefined2 **)0x14 = local_4;
    }
  }
  if (bVar2) {
    *(undefined2 **)0x14 = local_4;
  }
  return 1;
}



// Function: FUN_1000_6d58

void __cdecl16far FUN_1000_6d58(undefined2 param_1,undefined2 *param_2)

{
  undefined2 unaff_SS;
  undefined2 local_4e;
  undefined2 local_4c;
  undefined2 local_4a;
  undefined2 local_48;
  undefined2 local_40;
  
  if (param_2 == (undefined2 *)0x0) {
    local_4c = 0;
    local_4e = 0x26;
    local_48 = 0;
    local_4a = 2;
    local_40 = 0;
    param_2 = &local_4e;
  }
  param_2[2] = param_2[2] | 2;
  FUN_1000_6ccb(param_2,0,0,param_1);
  return;
}



// Function: FUN_1000_6d9f

void __cdecl16far FUN_1000_6d9f(void)

{
  return;
}



// Function: FUN_1000_6da4

/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

undefined2 __cdecl16far FUN_1000_6da4(void)

{
  uint uVar1;
  undefined2 in_AX;
  int iVar2;
  undefined2 extraout_var;
  undefined4 in_ECX;
  undefined2 uVar3;
  undefined4 in_EDX;
  undefined2 *puVar4;
  undefined4 in_EBX;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined4 *puVar8;
  undefined *puVar9;
  undefined2 *puVar10;
  undefined *in_ESP;
  undefined2 uVar12;
  undefined4 *puVar11;
  int iVar13;
  undefined4 in_EBP;
  undefined4 uVar14;
  undefined2 *puVar15;
  undefined4 in_ESI;
  undefined4 in_EDI;
  undefined2 unaff_ES;
  undefined2 uVar16;
  undefined2 unaff_SS;
  undefined2 in_FS;
  undefined2 in_GS;
  byte bVar17;
  byte bVar18;
  byte in_AF;
  byte bVar19;
  byte bVar20;
  byte in_TF;
  byte in_IF;
  byte bVar21;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  
  puVar5 = (undefined *)in_ESP;
  uVar12 = (undefined2)((ulong)in_ESP >> 0x10);
  *(undefined2 *)(puVar5 + -2) = in_AX;
  *(int *)(puVar5 + -4) = (int)in_ECX;
  *(int *)(puVar5 + -6) = (int)in_EDX;
  *(int *)(puVar5 + -8) = (int)in_EBX;
  *(int *)((int)puVar5 + -10) = (int)puVar5 + -8;
  *(int *)(puVar5 + -0xc) = (int)in_EBP;
  *(int *)(puVar5 + -0xe) = (int)in_ESI;
  *(int *)(puVar5 + -0x10) = (int)in_EDI;
  *(char **)(puVar5 + -0x12) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  *(undefined2 *)(puVar5 + -0x14) = unaff_ES;
  uVar14 = CONCAT22((int)((ulong)in_EBP >> 0x10),(int)puVar5 + -0x14);
  bVar17 = puVar5 + -0x14 < (undefined *)0x186;
  bVar21 = SBORROW2((int)puVar5 + -0x14,0x186);
  bVar20 = (int)puVar5 + -0x19a < 0;
  bVar19 = puVar5 == (undefined *)0x19a;
  bVar18 = (POPCOUNT((int)puVar5 - 0x19aU & 0xff) & 1U) == 0;
  *(int *)(puVar5 + -0x19c) = (int)puVar5 + -0x9a;
  *(undefined2 *)(puVar5 + -0x19e) = 0x1000;
  puVar6 = puVar5 + -0x1a0;
  *(undefined2 *)(puVar5 + -0x1a0) = 0x6dbd;
  FUN_1000_6d9f();
  uVar3 = *(undefined2 *)(puVar6 + 4);
  *(uint *)(puVar6 + 4) =
       (uint)(in_NT & 1) * 0x4000 | (uint)(bVar21 & 1) * 0x800 | (uint)(in_IF & 1) * 0x200 |
       (uint)(in_TF & 1) * 0x100 | (uint)(bVar20 & 1) * 0x80 | (uint)(bVar19 & 1) * 0x40 |
       (uint)(in_AF & 1) * 0x10 | (uint)(bVar18 & 1) * 4 | (uint)(bVar17 & 1);
  uVar16 = *(undefined2 *)(puVar6 + 4);
  puVar11 = (undefined4 *)CONCAT22(uVar12,puVar6 + 6);
  iVar2 = (int)uVar14;
  *(undefined2 *)(iVar2 + -8) = uVar16;
  if (DAT_28d3_270c < 3) {
    *(undefined2 *)(iVar2 + -0x9c) = 0;
    *(undefined2 *)(iVar2 + -0x9e) = 0;
    *(undefined2 *)(iVar2 + -0xa0) = 0;
    *(undefined2 *)(iVar2 + -0xa2) = 0;
    *(undefined2 *)(iVar2 + -0xa4) = 0;
    *(undefined2 *)(iVar2 + -0xa6) = 0;
    *(undefined2 *)(iVar2 + -0xa8) = 0;
    *(undefined2 *)(iVar2 + -0xaa) = 0;
    *(undefined2 *)(iVar2 + -0xac) = 0;
    *(undefined2 *)(iVar2 + -0xae) = 0;
    *(undefined2 *)(iVar2 + -0xb0) = 0;
    *(undefined2 *)(iVar2 + -0xb2) = 0;
    *(undefined2 *)(iVar2 + -0xb4) = 0;
    *(undefined2 *)(iVar2 + -0xb6) = 0;
    uVar3 = *(undefined2 *)(iVar2 + -8);
    *(undefined2 *)(iVar2 + -0x90) = 0;
    *(undefined2 *)(iVar2 + -0x92) = uVar3;
  }
  else {
    *(ulong *)(puVar6 + 2) = CONCAT22(extraout_var,uVar16);
    *(ulong *)(puVar6 + -2) = CONCAT22((int)((ulong)in_ECX >> 0x10),uVar3);
    *(undefined4 *)(puVar6 + -6) = in_EDX;
    *(undefined4 *)(puVar6 + -10) = in_EBX;
    *(undefined4 **)(puVar6 + -0xe) = puVar11;
    *(undefined4 *)(puVar6 + -0x12) = uVar14;
    *(undefined4 *)(puVar6 + -0x16) = in_ESI;
    *(undefined4 *)(puVar6 + -0x1a) = in_EDI;
    *(undefined **)(iVar2 + -10) = puVar6 + -0x1a;
    *(undefined2 *)(puVar6 + -0x1c) = 0x20;
    *(undefined2 *)(puVar6 + -0x1e) = unaff_SS;
    *(undefined2 *)(puVar6 + -0x20) = *(undefined2 *)(iVar2 + -10);
    *(undefined2 *)(puVar6 + -0x22) = unaff_SS;
    *(int *)(puVar6 + -0x24) = iVar2 + -0x186;
    *(undefined2 *)(puVar6 + -0x26) = 0x1000;
    puVar7 = puVar6 + -0x28;
    *(undefined2 *)(puVar6 + -0x28) = 0x6de5;
    FUN_1000_1a99();
    uVar14 = *(undefined4 *)(puVar7 + 0x16);
    iVar2 = (int)uVar14;
    uVar3 = *(undefined2 *)(iVar2 + -0x186);
    *(undefined2 *)(iVar2 + -0xb4) = *(undefined2 *)(iVar2 + -0x184);
    *(undefined2 *)(iVar2 + -0xb6) = uVar3;
    uVar3 = *(undefined2 *)(iVar2 + -0x182);
    *(undefined2 *)(iVar2 + -0xb0) = *(undefined2 *)(iVar2 + -0x180);
    *(undefined2 *)(iVar2 + -0xb2) = uVar3;
    uVar3 = *(undefined2 *)(iVar2 + -0x176);
    *(undefined2 *)(iVar2 + -0xac) = *(undefined2 *)(iVar2 + -0x174);
    *(undefined2 *)(iVar2 + -0xae) = uVar3;
    uVar3 = *(undefined2 *)(iVar2 + -0x172);
    *(undefined2 *)(iVar2 + -0xa8) = *(undefined2 *)(iVar2 + -0x170);
    *(undefined2 *)(iVar2 + -0xaa) = uVar3;
    uVar3 = *(undefined2 *)(iVar2 + -0x16e);
    *(undefined2 *)(iVar2 + -0xa4) = *(undefined2 *)(iVar2 + -0x16c);
    *(undefined2 *)(iVar2 + -0xa6) = uVar3;
    uVar3 = *(undefined2 *)(iVar2 + -0x16a);
    *(undefined2 *)(iVar2 + -0xa0) = *(undefined2 *)(iVar2 + -0x168);
    *(undefined2 *)(iVar2 + -0xa2) = uVar3;
    uVar3 = *(undefined2 *)(iVar2 + -0x17e);
    *(undefined2 *)(iVar2 + -0x9c) = *(undefined2 *)(iVar2 + -0x17c);
    *(undefined2 *)(iVar2 + -0x9e) = uVar3;
    *(ulong *)(puVar7 + 0x2a) =
         (ulong)(in_NT & 1) * 0x4000 | (ulong)SCARRY2((int)(puVar7 + 4),10) * 0x800 |
         (ulong)(in_IF & 1) * 0x200 | (ulong)(in_TF & 1) * 0x100 |
         (ulong)((int)(puVar7 + 0xe) < 0) * 0x80 | (ulong)(puVar7 == (undefined *)0xfff2) * 0x40 |
         (ulong)(in_AF & 1) * 0x10 | (ulong)((POPCOUNT((uint)(puVar7 + 0xe) & 0xff) & 1U) == 0) * 4
         | (ulong)((undefined *)0xfff5 < puVar7 + 4) | (ulong)(in_ID & 1) * 0x200000 |
         (ulong)(in_VIP & 1) * 0x100000 | (ulong)(in_VIF & 1) * 0x80000 |
         (ulong)(in_AC & 1) * 0x40000;
    puVar11 = (undefined4 *)CONCAT22(uVar12,puVar7 + 0x2a) + 1;
    *(undefined2 *)(iVar2 + -0x90) =
         (int)((ulong)*(undefined4 *)CONCAT22(uVar12,puVar7 + 0x2a) >> 0x10);
    *(undefined2 *)(iVar2 + -0x92) = *(undefined2 *)(iVar2 + -8);
    *(undefined2 *)(iVar2 + -0xc0) = 0;
    *(undefined2 *)(iVar2 + -0xc2) = in_FS;
    *(undefined2 *)(iVar2 + -0xc4) = 0;
    *(undefined2 *)(iVar2 + -0xc6) = in_GS;
  }
  iVar2 = (int)uVar14;
  uVar1 = *(uint *)(iVar2 + -0x9e);
  *(int *)(iVar2 + -0x8c) = *(int *)(iVar2 + -0x9c) + (uint)(0xffe7 < uVar1);
  *(int *)(iVar2 + -0x8e) = uVar1 + 0x18;
  if ((*(int *)(iVar2 + 0x1a) == 0xeef) && (*(int *)(iVar2 + 0x18) == -0x532)) {
    uVar16 = (undefined2)((ulong)*(undefined4 *)(iVar2 + 0x24) >> 0x10);
    iVar13 = (int)*(undefined4 *)(iVar2 + 0x24);
    uVar3 = *(undefined2 *)(iVar13 + 6);
    uVar16 = *(undefined2 *)(iVar13 + 4);
  }
  else {
    *(int *)(iVar2 + -10) = iVar2;
    uVar3 = *(undefined2 *)(*(int *)(iVar2 + -10) + 0x16);
    uVar16 = *(undefined2 *)(*(int *)(iVar2 + -10) + 0x14);
  }
  *(undefined2 *)(iVar2 + -4) = uVar3;
  *(undefined2 *)(iVar2 + -6) = uVar16;
  uVar3 = *(undefined2 *)(iVar2 + -6);
  *(undefined2 *)(iVar2 + -0x98) = 0;
  *(undefined2 *)(iVar2 + -0x9a) = uVar3;
  uVar3 = *(undefined2 *)(iVar2 + -4);
  *(undefined2 *)(iVar2 + -0x94) = 0;
  *(undefined2 *)(iVar2 + -0x96) = uVar3;
  puVar8 = (undefined4 *)puVar11;
  *(undefined2 *)((int)puVar8 + -2) = 0x14;
  *(undefined2 *)(puVar8 + -1) = unaff_SS;
  *(int *)((int)puVar8 + -6) = iVar2;
  *(undefined2 *)(puVar8 + -2) = unaff_SS;
  *(int *)((int)puVar8 + -10) = iVar2 + -0x166;
  *(undefined2 *)(puVar8 + -3) = 0x1000;
  puVar9 = (undefined *)((int)puVar8 + -0xe);
  *(undefined2 *)((int)puVar8 + -0xe) = 0x6f3c;
  FUN_1000_1a99();
  iVar2 = (int)uVar14;
  uVar3 = *(undefined2 *)(iVar2 + -0x164);
  *(undefined2 *)(iVar2 + -0xb8) = 0;
  *(undefined2 *)(iVar2 + -0xba) = uVar3;
  uVar3 = *(undefined2 *)(iVar2 + -0x166);
  *(undefined2 *)(iVar2 + -0xbc) = 0;
  *(undefined2 *)(iVar2 + -0xbe) = uVar3;
  *(undefined2 *)(iVar2 + -0x88) = 0;
  *(undefined2 *)(iVar2 + -0x8a) = unaff_SS;
  *(undefined2 *)(iVar2 + -0xa2) = *(undefined2 *)(iVar2 + -0x154);
  *(undefined2 *)(iVar2 + -0xae) = *(undefined2 *)(iVar2 + -0x15a);
  *(undefined2 *)(iVar2 + -0xa6) = *(undefined2 *)(iVar2 + -0x156);
  *(undefined2 *)(iVar2 + -0xaa) = *(undefined2 *)(iVar2 + -0x158);
  *(undefined2 *)(iVar2 + -0xb2) = *(undefined2 *)(iVar2 + -0x160);
  *(undefined2 *)(iVar2 + -0xb6) = *(undefined2 *)(iVar2 + -0x162);
  *(undefined2 *)(iVar2 + -0x9e) = *(undefined2 *)(iVar2 + -0x15e);
  uVar3 = *(undefined2 *)(iVar2 + 0x18);
  *(uint *)(iVar2 + -0x54) = *(uint *)(iVar2 + 0x1a) & 0xefff;
  *(undefined2 *)(iVar2 + -0x56) = uVar3;
  uVar3 = *(undefined2 *)(iVar2 + 0x1c);
  *(undefined2 *)(iVar2 + -0x50) = *(undefined2 *)(iVar2 + 0x1e);
  *(undefined2 *)(iVar2 + -0x52) = uVar3;
  uVar3 = *(undefined2 *)(iVar2 + -6);
  *(undefined2 *)(iVar2 + -0x4a) = *(undefined2 *)(iVar2 + -4);
  *(undefined2 *)(iVar2 + -0x4c) = uVar3;
  *(undefined2 *)(iVar2 + -0x4e) = 0;
  if ((*(uint *)(iVar2 + 0x24) | *(uint *)(iVar2 + 0x26)) == 0) {
    *(undefined2 *)(iVar2 + 0x22) = 0;
    *(undefined2 *)(iVar2 + 0x20) = 0;
  }
  if ((*(int *)(iVar2 + 0x22) != 0) || (0xf < *(uint *)(iVar2 + 0x20))) {
    *(undefined2 *)(iVar2 + 0x22) = 0;
    *(undefined2 *)(iVar2 + 0x20) = 0xf;
  }
  *(undefined2 *)(iVar2 + -0x48) = *(undefined2 *)(iVar2 + 0x20);
  *(undefined2 *)(iVar2 + -2) = 0;
  while( true ) {
    if ((*(int *)(iVar2 + 0x22) == 0) &&
       ((puVar4 = (undefined2 *)(puVar9 + 0xe), *(int *)(iVar2 + 0x22) != 0 ||
        (puVar4 = (undefined2 *)(puVar9 + 0xe), *(uint *)(iVar2 + 0x20) <= *(uint *)(iVar2 + -2)))))
    break;
    puVar4 = (undefined2 *)(*(int *)(iVar2 + -2) * 4 + iVar2 + -0x46);
    uVar16 = (undefined2)((ulong)*(undefined4 *)(iVar2 + 0x24) >> 0x10);
    puVar15 = (undefined2 *)((int)*(undefined4 *)(iVar2 + 0x24) + *(int *)(iVar2 + -2) * 4);
    uVar3 = *puVar15;
    puVar4[1] = puVar15[1];
    *puVar4 = uVar3;
    *(int *)(iVar2 + -2) = *(int *)(iVar2 + -2) + 1;
  }
  while( true ) {
    *(undefined2 *)((int)puVar4 + -2) = 0xffff;
    *(undefined2 *)((int)puVar4 + -4) = unaff_SS;
    *(int *)((int)puVar4 + -6) = (int)uVar14 + -0x152;
    *(int *)((int)puVar4 + -8) = (int)uVar14 + -0x56;
    *(undefined2 *)((int)puVar4 + -10) = 0x1000;
    puVar10 = (undefined2 *)((int)puVar4 + -0xc);
    *(undefined2 *)((int)puVar4 + -0xc) = 0x704d;
    iVar2 = FUN_1000_6ccb();
    puVar4 = puVar10 + 6;
    iVar13 = (int)uVar14;
    if (iVar2 != 0) break;
    if ((*(uint *)(iVar13 + 0x1c) & 1) == 0) goto LAB_1000_70a7;
    *(undefined2 *)(iVar13 + -0x54) = 0xc000;
    *(undefined2 *)(iVar13 + -0x56) = 0x25;
    uVar3 = *(undefined2 *)(iVar13 + 0x1c);
    *(undefined2 *)(iVar13 + -0x50) = *(undefined2 *)(iVar13 + 0x1e);
    *(undefined2 *)(iVar13 + -0x52) = uVar3;
    *(undefined2 *)(iVar13 + -0x4a) = 0;
    *(undefined2 *)(iVar13 + -0x4c) = 0;
    *(undefined2 *)(iVar13 + -0x4e) = 0;
    *(undefined2 *)(iVar13 + -0x48) = 0;
  }
  *(uint *)(iVar13 + -0x52) = *(uint *)(iVar13 + -0x52) | 2;
  puVar10[5] = 0xffff;
  puVar10[4] = unaff_SS;
  puVar10[3] = iVar13 + -0x152;
  puVar10[2] = iVar13 + -0x56;
  puVar10[1] = 0x1000;
  *puVar10 = 0x709d;
  iVar2 = FUN_1000_6ccb();
  if (iVar2 != 0) {
    *(undefined2 *)((int)puVar10 + 10) = 0x1000;
    *(undefined2 *)((int)puVar10 + 8) = 0x7217;
    FUN_1000_548d();
    return *(undefined2 *)(iVar13 + 0x12);
  }
LAB_1000_70a7:
  if (2 < DAT_28d3_270c) {
    iVar2 = *(int *)(iVar13 + -0x8e);
    uVar3 = *(undefined2 *)(iVar13 + -0x8a);
    *(undefined2 *)(iVar2 + -0x30) = *(undefined2 *)(iVar13 + -0xc6);
    *(undefined2 *)(iVar2 + -0x2e) = *(undefined2 *)(iVar13 + -0xc2);
    *(undefined2 *)(iVar2 + -0x2c) = *(undefined2 *)(iVar13 + -0xbe);
    *(undefined2 *)(iVar2 + -0x2a) = *(undefined2 *)(iVar13 + -0xba);
    uVar16 = *(undefined2 *)(iVar13 + -0xb6);
    *(undefined2 *)(iVar2 + -0x26) = *(undefined2 *)(iVar13 + -0xb4);
    *(undefined2 *)(iVar2 + -0x28) = uVar16;
    uVar16 = *(undefined2 *)(iVar13 + -0xb2);
    *(undefined2 *)(iVar2 + -0x22) = *(undefined2 *)(iVar13 + -0xb0);
    *(undefined2 *)(iVar2 + -0x24) = uVar16;
    uVar16 = *(undefined2 *)(iVar13 + -0x9e);
    *(undefined2 *)(iVar2 + -0x1e) = *(undefined2 *)(iVar13 + -0x9c);
    *(undefined2 *)(iVar2 + -0x20) = uVar16;
    uVar16 = *(undefined2 *)(iVar13 + -0x8e);
    *(undefined2 *)(iVar2 + -0x1a) = *(undefined2 *)(iVar13 + -0x8c);
    *(undefined2 *)(iVar2 + -0x1c) = uVar16;
    uVar16 = *(undefined2 *)(iVar13 + -0xae);
    *(undefined2 *)(iVar2 + -0x16) = *(undefined2 *)(iVar13 + -0xac);
    *(undefined2 *)(iVar2 + -0x18) = uVar16;
    uVar16 = *(undefined2 *)(iVar13 + -0xaa);
    *(undefined2 *)(iVar2 + -0x12) = *(undefined2 *)(iVar13 + -0xa8);
    *(undefined2 *)(iVar2 + -0x14) = uVar16;
    uVar16 = *(undefined2 *)(iVar13 + -0xa6);
    *(undefined2 *)(iVar2 + -0xe) = *(undefined2 *)(iVar13 + -0xa4);
    *(undefined2 *)(iVar2 + -0x10) = uVar16;
    uVar16 = *(undefined2 *)(iVar13 + -0xa2);
    *(undefined2 *)(iVar2 + -10) = *(undefined2 *)(iVar13 + -0xa0);
    *(undefined2 *)(iVar2 + -0xc) = uVar16;
    uVar16 = *(undefined2 *)(iVar13 + -0x92);
    *(undefined2 *)(iVar2 + -6) = *(undefined2 *)(iVar13 + -0x90);
    *(undefined2 *)(iVar2 + -8) = uVar16;
    *(undefined2 *)(iVar2 + -4) = *(undefined2 *)(iVar13 + -0x9a);
    *(undefined2 *)(iVar2 + -2) = *(undefined2 *)(iVar13 + -0x96);
    return (int)*(undefined4 *)(iVar2 + -0xc);
  }
  iVar2 = *(int *)(iVar13 + -0x8e);
  uVar3 = *(undefined2 *)(iVar13 + -0x8a);
  *(undefined2 *)(iVar2 + -0x1a) = *(undefined2 *)(iVar13 + -0xbe);
  *(undefined2 *)(iVar2 + -0x18) = *(undefined2 *)(iVar13 + -0xba);
  *(undefined2 *)(iVar2 + -0x16) = *(undefined2 *)(iVar13 + -0xb6);
  *(undefined2 *)(iVar2 + -0x14) = *(undefined2 *)(iVar13 + -0xb2);
  *(undefined2 *)(iVar2 + -0x12) = *(undefined2 *)(iVar13 + -0x9e);
  *(undefined2 *)(iVar2 + -0x10) = *(undefined2 *)(iVar13 + -0x8e);
  *(undefined2 *)(iVar2 + -0xe) = *(undefined2 *)(iVar13 + -0xae);
  *(undefined2 *)(iVar2 + -0xc) = *(undefined2 *)(iVar13 + -0xaa);
  *(undefined2 *)(iVar2 + -10) = *(undefined2 *)(iVar13 + -0xa6);
  *(undefined2 *)(iVar2 + -8) = *(undefined2 *)(iVar13 + -0xa2);
  *(undefined2 *)(iVar2 + -6) = *(undefined2 *)(iVar13 + -0x92);
  *(undefined2 *)(iVar2 + -4) = *(undefined2 *)(iVar13 + -0x9a);
  *(undefined2 *)(iVar2 + -2) = *(undefined2 *)(iVar13 + -0x96);
  return *(undefined2 *)(iVar2 + -8);
}



// Function: FUN_1000_724e

void __cdecl16near
FUN_1000_724e(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5,undefined2 param_6,undefined2 param_7)

{
  undefined2 local_20;
  
  FUN_1000_5c93();
  FUN_1000_65ab(param_1,param_2,param_3,param_4,param_5,param_6,param_7,1);
  FUN_1000_5d02(local_20);
  return;
}



// Function: FUN_1000_72a4

void __cdecl16near FUN_1000_72a4(undefined4 param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  undefined2 in_DX;
  undefined2 extraout_DX;
  int iVar4;
  int iVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  
  uVar6 = (undefined2)((ulong)param_1 >> 0x10);
  iVar4 = (int)param_1;
  if (*(char *)(iVar4 + 0x38) != '\0') {
    if ((*(uint *)(iVar4 + 0x16) & 2) != 0) {
      puVar3 = (undefined2 *)FUN_1000_5c87();
      uVar1 = puVar3[1];
      uVar2 = *puVar3;
      uVar7 = (undefined2)((ulong)*(undefined4 *)(iVar4 + 4) >> 0x10);
      iVar5 = (int)*(undefined4 *)(iVar4 + 4);
      FUN_1000_724e(iVar4 + 0x3a,uVar6,iVar4,uVar6,*(undefined2 *)(iVar5 + 0x1e),
                    *(undefined2 *)(iVar5 + 0x20),*(undefined2 *)(iVar5 + 0x22));
      uVar7 = extraout_DX;
      puVar3 = (undefined2 *)FUN_1000_5c87();
      puVar3[1] = uVar1;
      *puVar3 = uVar2;
    }
    *(undefined *)(iVar4 + 0x38) = 0;
  }
  if (*(char *)(iVar4 + 0x39) != '\0') {
    if (((*(uint *)(*(int *)(iVar4 + 0x32) + 2) & 2) != 0) &&
       ((*(uint *)(*(int *)(iVar4 + 0x32) + 8) & 2) != 0)) {
      FUN_1000_724e(*(undefined2 *)(iVar4 + 0x36));
    }
    *(undefined *)(iVar4 + 0x39) = 0;
  }
  return;
}



// Function: FUN_1000_738b

void __cdecl16far FUN_1000_738b(void)

{
  int iVar1;
  undefined2 *puVar2;
  undefined2 uVar3;
  int iVar4;
  int *piVar5;
  undefined2 *puVar6;
  undefined2 unaff_SS;
  undefined2 *local_6;
  
  piVar5 = *(int **)0x16;
  iVar1 = ((int *)piVar5)[1];
  puVar2 = (undefined2 *)*piVar5;
  local_6 = (undefined2 *)CONCAT22(iVar1,puVar2);
  uVar3 = *local_6;
  puVar6 = (undefined2 *)*(undefined4 *)0x16;
  ((undefined2 *)puVar6)[1] = puVar2[1];
  *puVar6 = uVar3;
  iVar4 = puVar2[0x12];
  *(undefined2 *)(iVar4 + 0xc) =
       *(undefined2 *)((int)*(undefined4 *)(iVar4 + 6) + *(int *)(iVar4 + 0xc));
  FUN_1000_72a4(puVar2,iVar1);
  (*(code *)puVar2[0xd])(0x1000,puVar2,iVar1,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  return;
}



// Function: FUN_1000_7408

undefined2 __cdecl16near
FUN_1000_7408(uint *param_1,int param_2,undefined2 param_3,undefined2 param_4,int *param_5)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  undefined2 uVar4;
  undefined2 unaff_SS;
  undefined4 local_a;
  uint local_6;
  uint local_4;
  
  while( true ) {
    uVar4 = (undefined2)((ulong)param_1 >> 0x10);
    puVar3 = (uint *)param_1;
    local_4 = puVar3[1];
    local_6 = *param_1;
    if ((local_6 | local_4) == 0) {
      return 0;
    }
    local_a = (undefined2 *)CONCAT22(param_5[1],(undefined2 *)(*param_5 + puVar3[2]));
    if (param_2 != 0) {
      local_a = (undefined2 *)CONCAT22(param_5[1],(undefined2 *)*local_a);
    }
    iVar1 = FUN_1000_5d47(local_6,local_4,param_3,param_4);
    if ((iVar1 != 0) ||
       ((((*(uint *)(local_6 + 2) & 2) != 0 &&
         (uVar2 = local_6 + *(int *)(local_6 + 10), (uVar2 | local_4) != 0)) &&
        (iVar1 = FUN_1000_7408(uVar2,local_4,0,param_3,param_4,&local_a), iVar1 != 0)))) break;
    param_1 = (uint *)CONCAT22(uVar4,puVar3 + 4);
  }
  param_5[1] = local_a._2_2_;
  *param_5 = (int)(undefined2 *)local_a;
  return 1;
}



// Function: FUN_1000_74d5

uint __cdecl16far
FUN_1000_74d5(uint param_1,uint param_2,undefined4 param_3,undefined2 param_4,undefined2 param_5)

{
  int iVar1;
  undefined2 uVar2;
  
  if ((((param_1 | param_2) != 0) &&
      (uVar2 = (undefined2)((ulong)param_3 >> 0x10),
      iVar1 = FUN_1000_7408((int)param_3 + *(int *)((int)param_3 + 10),uVar2,0,param_4,param_5,
                            &param_1), iVar1 == 0)) &&
     (uVar2 = (undefined2)((ulong)param_3 >> 0x10),
     iVar1 = FUN_1000_7408((int)param_3 + *(int *)((int)param_3 + 0xc),uVar2,1,param_4,param_5,
                           &param_1), iVar1 == 0)) {
    param_1 = 0;
  }
  return param_1;
}



// Function: FUN_1000_7558

void __cdecl16near
FUN_1000_7558(undefined4 param_1,undefined2 param_2_00,undefined4 param_2,int *param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  bool bVar10;
  undefined4 local_10;
  uint local_a;
  uint local_8;
  
  uVar8 = (undefined2)((ulong)param_1 >> 0x10);
  iVar6 = (int)param_1;
  uVar1 = *(uint *)(iVar6 + 6);
  local_a = *(uint *)(iVar6 + 4);
  uVar9 = (undefined2)((ulong)param_2 >> 0x10);
  iVar7 = (int)param_2;
  *(uint *)(iVar7 + 0x34) = uVar1;
  *(uint *)(iVar7 + 0x32) = local_a;
  if ((local_a | uVar1) == 0) {
    return;
  }
  if ((*(uint *)(iVar6 + 8) & 0x80) != 0) {
    return;
  }
  bVar10 = (*(uint *)(iVar6 + 8) & 1) == 0;
  local_10 = (undefined2 *)CONCAT22(uVar9,(undefined2 *)(iVar7 + 0x3a));
  *(undefined *)(iVar7 + 0x39) = 1;
  *(int *)(iVar7 + 0x36) = *param_3 + param_4;
  uVar2 = *(uint *)(local_a + 2);
  uVar5 = uVar2;
  local_8 = uVar1;
  if ((uVar2 & 0x30) != 0) {
    local_8 = *(uint *)(local_a + 8);
    local_a = *(uint *)(local_a + 6);
    uVar5 = *(uint *)(local_a + 2);
  }
  if (((uVar2 & 0x10) != 0) && ((*(uint *)(iVar7 + 0xc) & 1) != 0)) {
    FUN_1000_1ae3(*(undefined2 *)(iVar7 + 0x36));
    goto LAB_1000_7769;
  }
  if (((uVar5 & 1) == 0) || ((uVar2 & 0x30) == 0)) {
    if ((*(uint *)(iVar7 + 0x14) & 1) == 0) {
      if ((uVar2 & 0x20) != 0) {
        FUN_1000_1a99(*(undefined2 *)(iVar7 + 0x36));
        goto LAB_1000_7769;
      }
    }
    else {
      iVar6 = FUN_1000_5d47(*(undefined2 *)(iVar7 + 0x10),*(undefined2 *)(iVar7 + 0x12),local_a,
                            local_8);
      if (iVar6 == 0) {
        puVar4 = (undefined2 *)
                 FUN_1000_74d5((undefined2 *)(iVar7 + 0x3a),uVar9,*(undefined2 *)(iVar7 + 0x10),
                               *(undefined2 *)(iVar7 + 0x12),local_a,local_8);
        local_10 = (undefined2 *)CONCAT22(uVar5,puVar4);
      }
      bVar10 = iVar6 == 0 || bVar10;
      if ((*(uint *)(local_a + 8) & 1) != 0) {
        FUN_1000_6257(*(undefined2 *)(iVar7 + 0x36));
LAB_1000_7769:
        bVar10 = true;
        goto LAB_1000_77d2;
      }
    }
  }
  else {
    if ((uVar2 & 0x20) == 0) {
      puVar4 = (undefined2 *)*local_10;
      local_10 = (undefined2 *)CONCAT22(*(undefined2 *)(iVar7 + 0x3c),puVar4);
      if ((*(uint *)(iVar7 + 0x14) & 0x1000) != 0) {
        local_10 = (undefined2 *)
                   CONCAT22((char *)s_String_reference_out_of_range_28d3_28cc + 7,puVar4);
        goto LAB_1000_7675;
      }
    }
    else {
LAB_1000_7675:
      bVar10 = true;
    }
    iVar6 = FUN_1000_5d47(*(undefined2 *)(iVar7 + 0x10),*(undefined2 *)(iVar7 + 0x12),local_a,
                          local_8);
    if (iVar6 == 0) {
      iVar6 = local_10._2_2_;
      puVar4 = (undefined2 *)local_10;
      puVar3 = (undefined2 *)
               FUN_1000_74d5((undefined2 *)local_10,local_10._2_2_,*(undefined2 *)(iVar7 + 0x10),
                             *(undefined2 *)(iVar7 + 0x12),local_a,local_8);
      local_10 = (undefined2 *)CONCAT22(local_10._2_2_,puVar3);
      if ((local_10._2_2_ != iVar6) || (puVar3 != puVar4)) {
        bVar10 = true;
      }
    }
  }
  FUN_1000_1a99(*(undefined2 *)(iVar7 + 0x36));
LAB_1000_77d2:
  if (!bVar10) {
    if ((*(uint *)(local_a + 8) & 2) != 0) {
      FUN_1000_724e((undefined2 *)local_10,local_10._2_2_,local_a,local_8,
                    *(undefined2 *)(local_a + 0x1e),*(undefined2 *)(local_a + 0x20),
                    *(undefined2 *)(local_a + 0x22));
    }
    *(undefined *)(iVar7 + 0x38) = 0;
  }
  return;
}



// Function: FUN_1000_7815

void __cdecl16near FUN_1000_7815(int param_1)

{
  uint uVar1;
  uint uVar2;
  code **ppcVar3;
  uint *puVar4;
  undefined2 *puVar5;
  undefined2 *puVar6;
  undefined2 uVar7;
  int iVar8;
  undefined *puVar9;
  undefined2 uVar10;
  undefined2 unaff_SS;
  char *pcVar11;
  
  pcVar11 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  puVar9 = &stack0xfffe;
  *(undefined2 *)((int)*(undefined4 *)0x16 + 6) = *(undefined2 *)(param_1 + 0xe);
  *(undefined2 *)((int)*(undefined4 *)0x16 + 8) = *(undefined2 *)(param_1 + 0x10);
  while ((*(int *)(puVar9 + -6) != 0 && (*(int *)(puVar9 + -6) != *(int *)(puVar9 + 6)))) {
    *(undefined2 *)(puVar9 + -0x12) = *(undefined2 *)(puVar9 + -6);
    *(undefined2 *)(puVar9 + -8) =
         *(undefined2 *)((int)*(undefined4 *)(puVar9 + -4) + *(int *)(puVar9 + -0x12));
    *(int *)(puVar9 + -0x12) = *(int *)(puVar9 + -0x12) + 2;
    *(undefined2 *)(puVar9 + -0x10) =
         *(undefined2 *)((int)*(undefined4 *)(puVar9 + -4) + *(int *)(puVar9 + -0x12));
    *(int *)(puVar9 + -0x12) = *(int *)(puVar9 + -0x12) + 2;
    *(undefined2 *)(*(int *)(puVar9 + 4) + 0xc) = *(undefined2 *)(puVar9 + -8);
    switch(*(undefined2 *)(puVar9 + -0x10)) {
    case 0:
      uVar10 = (undefined2)((ulong)*(undefined4 *)(puVar9 + -4) >> 0x10);
      iVar8 = (int)*(undefined4 *)(puVar9 + -4) + *(int *)(puVar9 + -0x12);
      uVar7 = *(undefined2 *)(iVar8 + 4);
      *(undefined2 *)&DAT_28d3_58c2 = *(undefined2 *)(iVar8 + 6);
      *(undefined2 *)&DAT_28d3_58c0 = uVar7;
      *(undefined2 *)(*(int *)(puVar9 + 4) + 0x12) = 1;
      (**(code **)&DAT_28d3_58c0)(0x1000);
      *(undefined2 *)(*(int *)(puVar9 + 4) + 0x12) = 0;
      break;
    case 4:
      *(int *)(puVar9 + -0x12) = *(int *)(puVar9 + -0x12) + 4;
      uVar7 = *(undefined2 *)0x16;
      *(undefined2 *)(puVar9 + -0x18) = *(undefined2 *)0x18;
      *(undefined2 *)(puVar9 + -0x1a) = uVar7;
      while( true ) {
        puVar4 = *(uint **)(puVar9 + -0x1a);
        uVar1 = ((uint *)puVar4)[1];
        uVar2 = *puVar4;
        *(uint *)(puVar9 + -0x14) = uVar1;
        *(uint *)(puVar9 + -0x16) = uVar2;
        if (((uVar2 | uVar1) == 0) ||
           ((*(int *)((int)*(undefined4 *)(puVar9 + -0x16) + 0x24) == *(int *)(puVar9 + 4) &&
            (*(int *)((int)*(undefined4 *)(puVar9 + -0x16) + 0x2a) == *(int *)(puVar9 + -6)))))
        break;
        uVar7 = *(undefined2 *)(puVar9 + -0x16);
        *(undefined2 *)(puVar9 + -0x18) = *(undefined2 *)(puVar9 + -0x14);
        *(undefined2 *)(puVar9 + -0x1a) = uVar7;
      }
      puVar5 = *(undefined2 **)(puVar9 + -0x16);
      uVar7 = *puVar5;
      puVar6 = *(undefined2 **)(puVar9 + -0x1a);
      ((undefined2 *)puVar6)[1] = ((undefined2 *)puVar5)[1];
      *puVar6 = uVar7;
      FUN_1000_72a4(*(undefined2 *)(puVar9 + -0x16),*(undefined2 *)(puVar9 + -0x14));
      ppcVar3 = (code **)((int)*(undefined4 *)(puVar9 + -0x16) + 0x1a);
      (**ppcVar3)(0x1000,*(undefined2 *)(puVar9 + -0x16),*(undefined2 *)(puVar9 + -0x14));
      break;
    case 5:
      *(undefined2 *)(puVar9 + -0x1c) =
           *(undefined2 *)((int)*(undefined4 *)(puVar9 + -4) + *(int *)(puVar9 + -0x12));
      *(int *)(puVar9 + -0x12) = *(int *)(puVar9 + -0x12) + 2;
      uVar7 = *(undefined2 *)((int)*(undefined4 *)(puVar9 + -4) + *(int *)(puVar9 + -0x12));
      *(char **)(puVar9 + -0x1e) = pcVar11;
      *(undefined2 *)(puVar9 + -0x20) = uVar7;
      uVar7 = *(undefined2 *)(puVar9 + -0x20);
      *(undefined2 *)(puVar9 + -0x1e) = *(undefined2 *)(puVar9 + -2);
      *(undefined2 *)(puVar9 + -0x20) = uVar7;
      uVar7 = FUN_1000_840b(*(undefined2 *)(puVar9 + -0x20),*(undefined2 *)(puVar9 + -0x1e),
                            *(int *)(puVar9 + -0x1c) + *(int *)(puVar9 + -0xe),
                            *(int *)(puVar9 + -0x1c) + *(int *)(puVar9 + -0xe) >> 0xf,
                            *(undefined2 *)(puVar9 + 4),*(undefined2 *)(puVar9 + -10));
      *(undefined2 *)(puVar9 + -0xe) = uVar7;
    }
    *(undefined2 *)(puVar9 + -6) = *(undefined2 *)(puVar9 + -8);
  }
  return;
}



// Function: FUN_1000_7a09

void __cdecl16far FUN_1000_7a09(void)

{
  undefined2 *puVar1;
  undefined2 unaff_SS;
  
  puVar1 = (undefined2 *)*(undefined2 *)0x14;
  FUN_1000_7815(puVar1,0);
  *(undefined2 *)0x14 = *puVar1;
  return;
}



// Function: FUN_1000_7a33

uint * __cdecl16near FUN_1000_7a33(int param_1,undefined2 param_2,undefined4 param_3)

{
  int iVar1;
  uint *puVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  uint *local_6;
  
  local_6 = (uint *)CONCAT22(param_2,(uint *)(param_1 + 4));
  while( true ) {
    uVar4 = (undefined2)((ulong)local_6 >> 0x10);
    puVar2 = (uint *)local_6;
    if ((*local_6 | puVar2[1]) == 0) break;
    if ((puVar2[2] | puVar2[3]) == 0) goto LAB_1000_7ab1;
    uVar3 = (undefined2)((ulong)param_3 >> 0x10);
    iVar1 = (int)param_3;
    iVar1 = FUN_1000_614a(*(undefined2 *)(iVar1 + 4),*(undefined2 *)(iVar1 + 6),
                          *(undefined2 *)(iVar1 + 8),*(undefined2 *)(iVar1 + 10),puVar2[2],puVar2[3]
                          ,*(undefined2 *)(iVar1 + 0xc),0);
    if (iVar1 != 0) goto LAB_1000_7ab1;
    local_6 = (uint *)CONCAT22(uVar4,puVar2 + 8);
  }
  uVar4 = 0;
  puVar2 = (uint *)0x0;
LAB_1000_7ab1:
  return (uint *)CONCAT22(uVar4,puVar2);
}



// Function: FUN_1000_7e95

void __cdecl16far
FUN_1000_7e95(undefined2 param_1,undefined2 param_2,undefined4 param_3,undefined2 param_4)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 local_20;
  
  FUN_1000_5c93();
  uVar2 = (undefined2)((ulong)param_3 >> 0x10);
  iVar1 = (int)param_3;
  FUN_1000_65ab(param_1,param_2,iVar1,uVar2,*(undefined2 *)(iVar1 + 0x1e),
                *(undefined2 *)(iVar1 + 0x20),*(undefined2 *)(iVar1 + 0x22),param_4);
  FUN_1000_5d02(local_20);
  return;
}



// Function: FUN_1000_7f07

void __cdecl16far
FUN_1000_7f07(int param_1,undefined2 param_2,int *param_3,int *param_4,undefined2 param_5_00,
             undefined2 param_5,int param_6,undefined2 param_7)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined4 local_6;
  
  while (piVar3 = (int *)param_3, piVar1 = (int *)param_3 + -4,
        param_3 = (int *)CONCAT22(param_3._2_2_,piVar1), param_4 <= piVar1) {
    local_6 = (undefined2 *)CONCAT22(param_2,(undefined2 *)(param_1 + piVar3[-2]));
    if (param_6 != 0) {
      local_6 = (undefined2 *)CONCAT22(param_2,(undefined2 *)*local_6);
    }
    iVar2 = piVar3[-3];
    if ((*(uint *)(*param_3 + 8) & 2) != 0) {
      FUN_1000_7f89((undefined2 *)local_6,local_6._2_2_,*param_3,iVar2,param_5,0,0,param_7);
      param_5 = 0;
    }
  }
  return;
}



// Function: FUN_1000_7f89

void __cdecl16far
FUN_1000_7f89(int param_1,undefined2 param_2,undefined4 param_3,uint param_4,uint param_5,
             int param_6,undefined2 param_7)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  int *piVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  bool bVar12;
  int local_24;
  int local_22;
  uint local_20;
  uint local_1e;
  uint local_1c;
  int *local_1a;
  undefined4 local_12;
  uint *local_a;
  
  iVar6 = (int)param_3;
  uVar9 = (undefined2)((ulong)param_3 >> 0x10);
  if (param_6 == 0) {
    uVar5 = *(uint *)(iVar6 + 0x1c);
  }
  else {
    uVar5 = *(uint *)(iVar6 + 0x1a);
  }
  if ((((param_4 | param_5) == 0) || (param_5 != 0)) || (uVar5 <= param_4)) {
    FUN_1000_7e95(param_1,param_2,iVar6,uVar9,param_6);
  }
  else {
    local_1c = param_5;
    local_1e = param_4;
    puVar2 = (uint *)(iVar6 + *(int *)(iVar6 + 0xc));
    local_12 = (uint *)CONCAT22(uVar9,puVar2);
    if (param_6 != 0) {
      while( true ) {
        uVar10 = (undefined2)((ulong)local_12 >> 0x10);
        uVar5 = ((uint *)local_12)[1];
        uVar1 = *local_12;
        if ((uVar1 | uVar5) == 0) break;
        if ((*(uint *)(uVar1 + 8) & 2) != 0) {
          uVar5 = *(uint *)(uVar1 + 0x1c);
          if ((local_1c == 0) && ((local_1c != 0 || (local_1e <= uVar5)))) {
            local_12._0_2_ = (uint *)local_12 + 4;
            local_12._2_2_ = uVar10;
            goto LAB_1000_805f;
          }
          bVar12 = local_1e < uVar5;
          local_1e = local_1e - uVar5;
          local_1c = local_1c - bVar12;
        }
        local_12 = (uint *)CONCAT22(uVar10,(uint *)local_12 + 4);
      }
    }
    puVar3 = (uint *)(iVar6 + *(int *)(iVar6 + 10));
    local_a = (uint *)CONCAT22(uVar9,puVar3);
    while( true ) {
      uVar10 = (undefined2)((ulong)local_a >> 0x10);
      puVar7 = (uint *)local_a;
      uVar5 = puVar7[1];
      uVar1 = *local_a;
      if ((uVar1 | uVar5) == 0) break;
      if ((*(uint *)(uVar1 + 8) & 2) != 0) {
        uVar5 = *(uint *)(uVar1 + 0x1c);
        if ((local_1c == 0) && ((local_1c != 0 || (local_1e <= uVar5)))) {
          FUN_1000_7f07(param_1,param_2,puVar7 + 4,uVar10,puVar3,uVar9,local_1e,0,param_7);
          goto joined_r0x0001822f;
        }
        bVar12 = local_1e < uVar5;
        local_1e = local_1e - uVar5;
        local_1c = local_1c - bVar12;
      }
      local_a = (uint *)CONCAT22(uVar10,puVar7 + 4);
    }
    piVar4 = (int *)(iVar6 + *(int *)(iVar6 + 0x24));
    local_1a = (int *)CONCAT22(uVar9,piVar4);
    while( true ) {
      uVar11 = (undefined2)((ulong)local_1a >> 0x10);
      iVar6 = ((int *)local_1a)[1];
      local_24 = *local_1a;
      local_20 = 1;
      local_22 = iVar6;
      if ((*(uint *)(local_24 + 2) & 0x400) != 0) {
        local_20 = *(uint *)(local_24 + 10);
        local_22 = *(int *)(local_24 + 8);
        local_24 = *(int *)(local_24 + 6);
      }
      uVar5 = *(int *)(local_24 + 0x1a) * local_20;
      if ((local_1c == 0) && (local_1e <= uVar5)) break;
      bVar12 = local_1e < uVar5;
      local_1e = local_1e - uVar5;
      local_1c = local_1c - bVar12;
      local_1a = (int *)CONCAT22(uVar11,(int *)local_1a + 3);
    }
    do {
      uVar11 = (undefined2)((ulong)local_1a >> 0x10);
      piVar8 = (int *)local_1a;
      if (local_20 < 2) {
        FUN_1000_7f89(param_1 + piVar8[2],param_2,*local_1a,piVar8[1],local_1e,local_1c,1,param_7);
      }
      else {
        FUN_1000_8257(param_1 + piVar8[2],param_2,*local_1a,piVar8[1],local_1e,local_1c,param_7);
      }
      local_1c = 0;
      local_1e = 0;
      local_1a = (int *)CONCAT22(uVar11,piVar8 + -3);
    } while (piVar4 <= piVar8 + -3);
    FUN_1000_7f07(param_1,param_2,puVar7,uVar10,puVar3,uVar9,0,0,param_7);
joined_r0x0001822f:
    if (param_6 != 0) {
      local_1e = 0;
LAB_1000_805f:
      FUN_1000_7f07(param_1,param_2,(uint *)local_12,local_12._2_2_,puVar2,uVar9,local_1e,1,param_7)
      ;
    }
  }
  return;
}



// Function: FUN_1000_8257

void __cdecl16far
FUN_1000_8257(int param_1,undefined2 param_2,int param_3,undefined2 param_4,uint param_5,
             uint param_6,undefined2 param_7)

{
  undefined2 uVar1;
  int *piVar2;
  uint uVar3;
  ulong uVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  int local_10;
  int local_e;
  int *local_6;
  
  lVar6 = CONCAT22(param_6,param_5);
  uVar1 = *(undefined2 *)(param_3 + 8);
  piVar2 = *(int **)(param_3 + 6);
  local_6 = (int *)CONCAT22(uVar1,piVar2);
  uVar3 = piVar2[0xd];
  if ((param_5 | param_6) == 0) {
    lVar6 = FUN_1000_3f98();
  }
  lVar7 = FUN_1000_3ed0(lVar6,uVar3,0);
  lVar8 = FUN_1000_3f98();
  uVar4 = lVar6 - lVar8;
  iVar5 = FUN_1000_3f98();
  param_1 = iVar5 + param_1;
  if (uVar4 == 0) goto LAB_1000_8341;
  while( true ) {
    FUN_1000_7f89(param_1,param_2,piVar2,uVar1,uVar4,1,param_7);
LAB_1000_8341:
    local_e = (int)((ulong)lVar7 >> 0x10);
    local_10 = (int)lVar7;
    if (lVar7 == 0) break;
    param_1 = param_1 - *local_6;
    uVar4 = (ulong)uVar3;
    lVar7 = CONCAT22(local_e - (uint)(local_10 == 0),local_10 + -1);
  }
  return;
}



// Function: FUN_1000_8359

int __cdecl16far FUN_1000_8359(int param_1,undefined2 param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined2 unaff_SS;
  undefined4 local_a;
  
  iVar3 = param_3[1];
  iVar1 = *param_3;
  if (((*(uint *)(iVar1 + 8) & 0x50) == 0x50) && (*(int *)(iVar1 + 6) != -1)) {
    piVar2 = (int *)(param_1 + *(int *)(iVar1 + 6));
    local_a = (int *)CONCAT22(param_2,piVar2);
    if ((*(uint *)(iVar1 + 8) & 0x1000) == 0) {
      iVar3 = *local_a;
      local_a._2_2_ = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    }
    else {
      iVar3 = *local_a;
      local_a._2_2_ = (char *)piVar2[1];
    }
    param_1 = param_1 - *(int *)(iVar3 + -4);
    iVar3 = iVar3 - *(int *)(iVar3 + -2);
    iVar1 = *(int *)(iVar3 + -8);
    param_3[1] = *(int *)(iVar3 + -6);
    *param_3 = iVar1;
  }
  return param_1;
}



// Function: FUN_1000_840b

undefined2 __cdecl16near
FUN_1000_840b(undefined4 *param_1,uint param_2,int param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  int **ppiVar2;
  int *piVar3;
  uint *puVar4;
  uint uVar5;
  int **ppiVar6;
  int *piVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined2 uVar10;
  int *unaff_SS;
  bool bVar11;
  undefined2 uVar12;
  undefined2 uVar13;
  undefined4 local_22;
  int *piVar14;
  int **local_1a;
  int *local_18;
  uint uStack_16;
  uint local_14;
  uint local_12;
  int local_10;
  undefined4 local_e;
  uint local_a;
  int local_8;
  uint local_6;
  int local_4;
  
  local_10 = 0;
  if ((undefined4 *)param_1 != (undefined4 *)0xffff) {
    iVar8 = *(int *)(param_4 + 0x1c);
    local_6 = *(uint *)(param_4 + 0x1a);
    local_4 = iVar8;
    puVar4 = (uint *)FUN_1000_5c87();
    uVar5 = *puVar4 - local_6;
    local_a = uVar5 - param_2;
    local_8 = (((puVar4[1] - local_4) - (uint)(*puVar4 < local_6)) - param_3) -
              (uint)(uVar5 < param_2);
    uVar10 = (undefined2)((ulong)param_1 >> 0x10);
    if ((*(uint *)((undefined4 *)param_1 + 1) & 0x20) != 0) {
      uVar1 = *(undefined4 *)((int)*param_1 + 6);
      local_a = *(uint *)((int)uVar1 + 0x1a);
      local_8 = 0;
    }
    if ((*(uint *)((undefined4 *)param_1 + 1) & 0x100) != 0) {
      return *(undefined2 *)((int)*param_1 + 0x1c);
    }
    if ((local_8 < 1) && ((local_8 != 0 || (local_a == 0)))) {
      if ((*(uint *)((undefined4 *)param_1 + 1) & 3) != 3) {
        return 0;
      }
      local_e = param_1;
      local_10 = local_10 + 1;
    }
    else {
      local_e = param_1;
      while( true ) {
        uVar10 = (undefined2)((ulong)local_e >> 0x10);
        puVar9 = (undefined4 *)local_e;
        if ((*(uint *)local_e | *(uint *)((int)puVar9 + 2)) == 0) break;
        uStack_16 = *(uint *)((int)puVar9 + 2);
        local_14 = *(uint *)local_e;
        local_1a = (int **)0x1;
        if ((*(uint *)(local_14 + 2) & 0x10) != 0) {
          local_12 = *(uint *)(local_14 + 8);
          local_14 = *(uint *)(local_14 + 6);
          uStack_16 = local_12;
          if ((((*(uint *)(local_14 + 2) & 2) != 0) && ((*(uint *)(local_14 + 8) & 0x20) != 0)) &&
             ((*(uint *)(puVar9 + 1) & 8) != 0)) {
            if ((*(uint *)(puVar9 + 1) & 4) == 0) {
              piVar7 = *(int **)(puVar9 + 2);
              ppiVar6 = (int **)*(int **)((int)puVar9 + 6);
            }
            else {
              ppiVar6 = (int **)(*(uint *)((int)puVar9 + 6) + param_5);
              piVar7 = unaff_SS;
            }
            local_22 = (int **)CONCAT22(piVar7,ppiVar6);
            if ((*(uint *)(puVar9 + 1) & 0x80) == 0) {
              piVar7 = *local_22;
              piVar14 = (int *)((char *)s_String_reference_out_of_range_28d3_28cc + 7);
            }
            else {
              piVar14 = ppiVar6[1];
              piVar7 = *local_22;
            }
            if ((*(uint *)(puVar9 + 1) & 0x40) != 0) {
              piVar7 = piVar7 + 2;
            }
            FUN_1000_8359(piVar7,piVar14,&local_14);
            uStack_16 = local_12;
          }
        }
        piVar7 = (int *)local_14;
        if ((*(uint *)(local_14 + 2) & 0x400) != 0) {
          local_1a = (int **)*(int *)(local_14 + 10);
          piVar7 = (int *)*(uint *)(local_14 + 6);
          uStack_16 = *(uint *)(local_14 + 8);
        }
        uVar5 = *(int *)((int)piVar7 + 0x1a) * (int)local_1a;
        if ((local_8 == 0) && ((local_8 != 0 || (local_a <= uVar5)))) goto LAB_1000_8632;
        bVar11 = local_a < uVar5;
        local_a = local_a - uVar5;
        local_8 = local_8 - (uint)bVar11;
        local_e = (undefined4 *)
                  CONCAT22(local_e._2_2_,(undefined4 *)((int)(undefined4 *)local_e + 10));
      }
      local_e = (undefined4 *)CONCAT22(uVar10,(undefined4 *)((int)puVar9 + -10));
    }
LAB_1000_8632:
    do {
      uVar10 = (undefined2)((ulong)local_e >> 0x10);
      puVar9 = (undefined4 *)local_e;
      local_12 = *(uint *)((int)puVar9 + 2);
      local_14 = *(uint *)local_e;
      uVar5 = *(uint *)(puVar9 + 1);
      if ((uVar5 & 4) == 0) {
        local_1a = (int **)*(uint **)((int)puVar9 + 6);
        local_18 = (int *)CONCAT22(uVar5,*(int **)(puVar9 + 2));
      }
      else {
        local_1a = (int **)(*(uint *)((int)puVar9 + 6) + param_5);
        local_18 = (int *)CONCAT22(uVar5,unaff_SS);
      }
      piVar3 = local_18;
      if (((ulong)local_18 & 0x110000) != 0) {
        uVar5 = *(uint *)(local_14 + 8);
        local_14 = *(uint *)(local_14 + 6);
        ppiVar2 = (int **)CONCAT22((int *)local_18,local_1a);
        if (((ulong)local_18 & 0x800000) == 0) {
          local_1a = (int **)*ppiVar2;
          piVar7 = (int *)((char *)s_String_reference_out_of_range_28d3_28cc + 7);
        }
        else {
          piVar7 = local_1a[1];
          local_1a = (int **)*ppiVar2;
        }
        local_22 = (int **)CONCAT22(piVar7,local_1a);
        if ((uStack_16 & 0x48) == 0x40) {
          if (((ulong)piVar3 & 0x800000) == 0) {
            iVar8 = 2;
          }
          else {
            iVar8 = 4;
          }
          local_1a = (int **)((int)local_1a + iVar8);
        }
        local_12 = uVar5;
        if ((((*(uint *)(local_14 + 2) & 2) != 0) && ((*(uint *)(local_14 + 8) & 0x20) != 0)) &&
           (((ulong)piVar3 & 0x80000) != 0)) {
          local_1a = (int **)FUN_1000_8359(local_1a,piVar7,&local_14);
        }
      }
      if (local_10 == 0) {
        if ((*(uint *)(local_14 + 2) & 0x400) == 0) {
          FUN_1000_7f89(local_1a,piVar7,local_14,local_12,local_a,local_8,1,param_5);
        }
        else {
          FUN_1000_8257(local_1a,piVar7,local_14,local_12,local_a,local_8,param_5);
        }
      }
      if ((uStack_16 & 3) == 3) {
        if ((uStack_16 & 0x48) == 0x48) {
          local_22 = (int **)CONCAT22(local_22._2_2_,(int **)local_22 + -2);
        }
        if ((*(uint *)(local_14 + 2) & 0x400) == 0) {
          if ((*(uint *)(local_14 + 0xe) | *(uint *)(local_14 + 0x10)) != 0) {
            uVar10 = *(undefined2 *)(local_14 + 0x12);
            uVar13 = *(undefined2 *)(local_14 + 0x10);
            uVar12 = *(undefined2 *)(local_14 + 0xe);
            goto LAB_1000_87f5;
          }
          if (((ulong)local_18 & 0x800000) != 0) {
            FUN_1000_441a((int **)local_22,local_22._2_2_);
          }
        }
        else {
          uVar5 = *(uint *)(local_14 + 8);
          local_14 = *(uint *)(local_14 + 6);
          local_12 = uVar5;
          if ((*(uint *)(local_14 + 0x16) | *(uint *)(local_14 + 0x18)) == 0) {
            if (((ulong)local_18 & 0x800000) != 0) {
              FUN_1000_4430((int **)local_22,local_22._2_2_);
            }
          }
          else {
            uVar10 = *(undefined2 *)(local_14 + 0x14);
            uVar13 = *(undefined2 *)(local_14 + 0x18);
            uVar12 = *(undefined2 *)(local_14 + 0x16);
LAB_1000_87f5:
            FUN_1000_6768((int **)local_22,local_22._2_2_,uVar12,uVar13,uVar10);
          }
        }
      }
      local_8 = 0;
      local_a = 0;
      puVar9 = (undefined4 *)local_e;
      local_e = (undefined4 *)
                CONCAT22(local_e._2_2_,(undefined4 *)((int)(undefined4 *)local_e + -10));
    } while ((undefined4 *)param_1 < puVar9);
  }
  return 0;
}



// Function: FUN_1000_8838

undefined2 __cdecl16far FUN_1000_8838(int param_1)

{
  int iVar1;
  undefined2 unaff_SS;
  
  if ((param_1 != -1) &&
     (iVar1 = FUN_1000_1a71(*(int *)(param_1 + 2) + -8,*(undefined2 *)(param_1 + 4),0x2899,
                            (char *)s_String_reference_out_of_range_28d3_28cc + 7,8), iVar1 == 0)) {
    return *(undefined2 *)(param_1 + 0xc);
  }
  return 0xffff;
}



// Function: FUN_1000_88bf

undefined2 * __cdecl16far FUN_1000_88bf(undefined2 *param_1)

{
  undefined2 *puVar1;
  uint in_DX;
  undefined2 local_6;
  undefined2 local_4;
  
  if (((uint)(undefined2 *)param_1 | param_1._2_2_) == 0) {
    puVar1 = (undefined2 *)FUN_1000_44b3(8);
    param_1 = (undefined2 *)CONCAT22(in_DX,puVar1);
    if (((uint)puVar1 | in_DX) == 0) goto LAB_1000_8921;
  }
  ((undefined2 *)param_1)[1] = 0x1000;
  *param_1 = 0x8ece;
  local_4 = 0;
  local_6 = 0;
  FUN_1000_6bc3(0x8eb1,0x1000,&local_6);
LAB_1000_8921:
  return (undefined2 *)param_1;
}



// Function: FUN_1000_892d

undefined2 __cdecl16far FUN_1000_892d(undefined2 param_1)

{
  return param_1;
}



// Function: FUN_1000_893c

void __cdecl16far FUN_1000_893c(undefined2 *param_1,uint param_3)

{
  if (((uint)(undefined2 *)param_1 | param_1._2_2_) != 0) {
    ((undefined2 *)param_1)[1] = 0x1000;
    *param_1 = 0x8ece;
    if ((param_3 & 1) != 0) {
      FUN_1000_441a((undefined2 *)param_1,param_1._2_2_);
    }
  }
  return;
}



// Function: FUN_1000_8971

bool __cdecl16far FUN_1000_8971(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  
  uVar2 = (undefined2)((ulong)param_2 >> 0x10);
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = FUN_1000_5d47(*(undefined2 *)((int)param_1 + 4),*(undefined2 *)((int)param_1 + 6),
                        *(undefined2 *)((int)param_2 + 4),*(undefined2 *)((int)param_2 + 6));
  return iVar1 != 0;
}



// Function: FUN_1000_89a2

bool __cdecl16far
FUN_1000_89a2(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  char cVar1;
  
  cVar1 = FUN_1000_8971(param_1,param_2,param_3,param_4);
  return cVar1 == '\0';
}



// Function: FUN_1000_89c4

undefined2 __cdecl16far FUN_1000_89c4(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = (int)param_1;
  if ((*(uint *)(iVar1 + 4) | *(uint *)(iVar1 + 6)) == 0) {
    uVar3 = 0;
  }
  else {
    uVar4 = (undefined2)((ulong)param_2 >> 0x10);
    iVar2 = (int)param_2;
    if ((*(uint *)(iVar2 + 4) | *(uint *)(iVar2 + 6)) == 0) {
      uVar3 = 1;
    }
    else {
      iVar1 = FUN_1000_1bbc(*(int *)(iVar1 + 4) + *(int *)(*(int *)(iVar1 + 4) + 4),
                            *(undefined2 *)(iVar1 + 6),
                            *(int *)(iVar2 + 4) + *(int *)(*(int *)(iVar2 + 4) + 4),
                            *(undefined2 *)(iVar2 + 6));
      if (iVar1 < 0) {
        uVar3 = 1;
      }
      else {
        uVar3 = 0;
      }
    }
  }
  return uVar3;
}



// Function: FUN_1000_8a3b

void __cdecl16far FUN_1000_8a3b(undefined4 param_1)

{
  undefined2 uVar1;
  
  uVar1 = (undefined2)((ulong)param_1 >> 0x10);
  FUN_1000_5d22(*(undefined2 *)((int)param_1 + 4),*(undefined2 *)((int)param_1 + 6));
  return;
}



// Function: FUN_1000_8a55

int __cdecl16far
FUN_1000_8a55(uint param_1,uint param_2,undefined4 param_3,undefined2 param_4_00,
             undefined2 param_5_00,int param_4,undefined2 param_5)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 uVar3;
  
  if ((param_1 | param_2) == 0) {
    FUN_1000_6bc3(0x8e9b,0x1000,0x58c8,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0,0,0,0
                  ,0,0,0,0,0);
  }
  uVar3 = (undefined2)((ulong)param_3 >> 0x10);
  iVar2 = (int)param_3 - *(int *)((int)param_3 + -2);
  uVar1 = *(undefined2 *)(iVar2 + -8);
  *(undefined2 *)(param_4 + 6) = *(undefined2 *)(iVar2 + -6);
  *(undefined2 *)(param_4 + 4) = uVar1;
  return param_4;
}



// Function: FUN_1000_8ad8

undefined2 * __cdecl16near
FUN_1000_8ad8(int param_1,undefined2 param_2,undefined4 param_3,undefined2 *param_5,uint param_6,
             undefined2 param_7,undefined2 param_8,uint param_9,uint param_10,uint param_11,
             uint param_12,uint *param_13,int param_14,uint param_15,uint param_16)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  uint *puVar5;
  undefined2 uVar6;
  undefined2 unaff_SS;
  long lVar7;
  uint local_1a;
  uint local_18;
  undefined4 local_16;
  uint local_12;
  int local_10;
  undefined2 *local_e;
  uint local_c;
  uint local_a;
  uint *local_6;
  
  local_a = 0;
  local_c = 0;
  local_e = (undefined2 *)0x0;
  local_10 = 0;
  if ((((param_11 | param_12) == 0) ||
      (iVar4 = FUN_1000_5d47(param_11,param_12,(int)param_3,param_3._2_2_), iVar4 == 0)) &&
     ((*(uint *)((int)param_3 + 8) & 4) != 0)) {
    bVar3 = false;
    iVar4 = *(int *)((int)param_3 + 0xc);
    do {
      local_6 = (uint *)CONCAT22(param_3._2_2_,(uint *)((int)param_3 + iVar4));
      while( true ) {
        uVar6 = (undefined2)((ulong)local_6 >> 0x10);
        puVar5 = (uint *)local_6;
        uVar1 = puVar5[1];
        uVar2 = *local_6;
        if ((uVar2 | uVar1) == 0) break;
        if ((puVar5[3] & 8) == 0) {
          if ((param_14 == 0) || ((puVar5[3] & 3) != 3)) {
            local_12 = 0;
          }
          else {
            local_12 = 1;
          }
          local_16 = (undefined2 *)CONCAT22(param_2,(undefined2 *)(param_1 + puVar5[2]));
          local_18 = param_16;
          local_1a = param_15;
          if ((puVar5[3] & 4) != 0) {
            local_16 = (undefined2 *)CONCAT22(param_2,(undefined2 *)*local_16);
            local_1a = uVar2;
            local_18 = uVar1;
          }
          iVar4 = FUN_1000_5d47(param_7,param_8,uVar2,uVar1);
          if (iVar4 == 0) {
            if (((*(uint *)(uVar2 + 8) & 4) != 0) &&
               (local_16 = (undefined2 *)
                           FUN_1000_8ad8((undefined2 *)local_16,local_16._2_2_,uVar2,uVar1,param_5,
                                         param_6,param_7,param_8,param_9,param_10,param_11,param_12,
                                         param_13,local_12,local_1a,local_18),
               local_16 != (undefined2 *)0x0)) {
              local_12 = *param_13;
LAB_1000_8caa:
              if (((local_10 == 0) || (local_16._2_2_ != local_c)) ||
                 ((undefined2 *)local_16 != local_e)) {
                local_10 = local_10 + 1;
                local_c = local_16._2_2_;
                local_e = (undefined2 *)local_16;
                local_a = local_12;
              }
              else {
                local_a = local_a | local_12;
              }
            }
          }
          else if (((uint)param_5 | param_6) == 0) {
            if (((param_9 | param_10) == 0) ||
               (lVar7 = FUN_1000_8ad8((undefined2 *)local_16,local_16._2_2_,uVar2,uVar1,param_9,
                                      param_10,param_11,param_12,0,0,0,0,param_13,0,0,0), lVar7 != 0
               )) goto LAB_1000_8caa;
          }
          else if ((param_6 == local_16._2_2_) && (param_5 == (undefined2 *)local_16))
          goto LAB_1000_8d1c;
        }
        local_6 = (uint *)CONCAT22(uVar6,puVar5 + 4);
      }
      if (bVar3) goto LAB_1000_8cfd;
      bVar3 = true;
      iVar4 = *(int *)((int)param_3 + 10);
    } while( true );
  }
  local_16._2_2_ = 0;
  local_16._0_2_ = (undefined2 *)0x0;
LAB_1000_8d1c:
  return (undefined2 *)CONCAT22(local_16._2_2_,(undefined2 *)local_16);
LAB_1000_8cfd:
  *param_13 = local_a;
  local_16._0_2_ = local_e;
  local_16._2_2_ = local_c;
  if (local_10 != 1) {
    local_c = 0;
    local_e = (undefined2 *)0x0;
    local_16._0_2_ = local_e;
    local_16._2_2_ = local_c;
  }
  goto LAB_1000_8d1c;
}



// Function: FUN_1000_8d22

int __cdecl16far
FUN_1000_8d22(uint param_1,uint param_2,undefined4 param_3,undefined2 param_4,undefined2 param_5,
             uint param_6,uint param_7,int param_8)

{
  int iVar1;
  undefined2 uVar2;
  long lVar3;
  int local_18;
  undefined4 local_16;
  int local_12;
  uint local_10;
  undefined2 local_e;
  undefined2 local_c;
  uint local_a;
  uint local_8;
  undefined2 local_6;
  undefined2 local_4;
  
  lVar3 = CONCAT22(local_16._2_2_,(undefined2)local_16);
  local_4 = param_5;
  local_6 = param_4;
  local_8 = param_7;
  local_a = param_6;
  if ((param_1 | param_2) != 0) {
    uVar2 = (undefined2)((ulong)param_3 >> 0x10);
    iVar1 = (int)param_3;
    local_12 = param_1 - *(int *)(iVar1 + -4);
    local_10 = param_2;
    iVar1 = iVar1 - *(int *)(iVar1 + -2);
    local_c = *(undefined2 *)(iVar1 + -6);
    local_e = *(undefined2 *)(iVar1 + -8);
    if ((param_6 | param_7) == 0) {
      return local_12;
    }
    iVar1 = FUN_1000_5d47(param_6,param_7,local_e,local_c);
    if (iVar1 != 0) {
      return local_12;
    }
    iVar1 = FUN_1000_5d47(local_6,local_4,local_e,local_c);
    if (iVar1 == 0) {
      local_16 = FUN_1000_8ad8(local_12,local_10,local_e,local_c,0,0,local_a,local_8,param_1,param_2
                               ,local_6,local_4,&local_18,1,0,0);
      if (local_16 != 0) {
        return (int)local_16;
      }
    }
    lVar3 = FUN_1000_8ad8(local_12,local_10,local_e,local_c,0,0,local_a,local_8,0,0,0,0,&local_18,1,
                          0,0);
    if ((lVar3 != 0) && (local_18 != 0)) {
      return (int)lVar3;
    }
  }
  if (param_8 != 0) {
    local_16 = lVar3;
    FUN_1000_6bc3(0x8e87,0x1000,0x58c9,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0,0,0,0
                  ,0,0,0,0,0);
  }
  return 0;
}



// Function: FUN_1000_8ff2

undefined2 __cdecl16far FUN_1000_8ff2(uint param_1,uint param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined2 uVar4;
  undefined2 in_DX;
  
  if ((param_1 | param_2) == 0) {
    uVar4 = 0;
  }
  else {
    piVar3 = (int *)FUN_1000_5c87();
    piVar1 = piVar3;
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    piVar3[1] = piVar3[1] - (uint)(iVar2 == 0);
    uVar4 = FUN_1000_5a4a(param_1,param_2,0);
    if ((param_3 & 1) != 0) {
      uVar4 = FUN_1000_441a(param_1,param_2);
    }
  }
  return uVar4;
}



// Function: FUN_1000_91a4

undefined2 __cdecl16far FUN_1000_91a4(uint param_1,uint param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined2 uVar4;
  undefined2 in_DX;
  
  if ((param_1 | param_2) == 0) {
    uVar4 = 0;
  }
  else {
    piVar3 = (int *)FUN_1000_5c87();
    piVar1 = piVar3;
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    piVar3[1] = piVar3[1] - (uint)(iVar2 == 0);
    uVar4 = FUN_1000_5a4a(param_1,param_2,0);
    if ((param_3 & 1) != 0) {
      uVar4 = FUN_1000_441a(param_1,param_2);
    }
  }
  return uVar4;
}



// Function: FUN_1000_91f2

undefined2 __cdecl16far FUN_1000_91f2(uint param_1,uint param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined2 uVar4;
  undefined2 in_DX;
  
  if ((param_1 | param_2) == 0) {
    uVar4 = 0;
  }
  else {
    piVar3 = (int *)FUN_1000_5c87();
    piVar1 = piVar3;
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    piVar3[1] = piVar3[1] - (uint)(iVar2 == 0);
    uVar4 = FUN_1000_5a4a(param_1,param_2,0);
    if ((param_3 & 1) != 0) {
      uVar4 = FUN_1000_441a(param_1,param_2);
    }
  }
  return uVar4;
}



// Function: FUN_1000_9240

undefined2 __cdecl16far FUN_1000_9240(uint param_1,uint param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined2 uVar4;
  undefined2 in_DX;
  
  if ((param_1 | param_2) == 0) {
    uVar4 = 0;
  }
  else {
    piVar3 = (int *)FUN_1000_5c87();
    piVar1 = piVar3;
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    piVar3[1] = piVar3[1] - (uint)(iVar2 == 0);
    uVar4 = FUN_1000_5a4a(param_1,param_2,0);
    if ((param_3 & 1) != 0) {
      uVar4 = FUN_1000_441a(param_1,param_2);
    }
  }
  return uVar4;
}



// Function: FUN_1928_000e

/* WARNING (jumptable): Stack frame is not setup normally: Input value of stackpointer is not used
    */
/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 __cdecl16far FUN_1928_000e(void)

{
  int iVar1;
  undefined2 uVar2;
  uint in_DX;
  int *piVar3;
  int iVar4;
  undefined *puVar5;
  undefined2 *puVar6;
  undefined2 *puVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  int *piVar10;
  int *piVar11;
  int *piVar12;
  undefined2 *puVar13;
  ulong *puVar14;
  ulong *puVar15;
  undefined2 *puVar16;
  undefined *puVar17;
  char **ppcVar18;
  char **ppcVar19;
  undefined *puVar20;
  undefined4 in_ESP;
  undefined2 unaff_BP;
  undefined2 unaff_SI;
  undefined2 unaff_DI;
  undefined2 uVar21;
  undefined2 unaff_SS;
  
  iVar4 = (int)in_ESP;
  uVar21 = (undefined2)((ulong)in_ESP >> 0x10);
  *(undefined2 *)(iVar4 + -2) = unaff_BP;
  *(undefined2 *)(iVar4 + -0x12) = unaff_SI;
  *(undefined2 *)(iVar4 + -0x14) = unaff_DI;
  *(undefined2 *)(iVar4 + -10) = 0;
  DAT_28d3_2960 = 0;
  DAT_28d3_2962 = 0;
  DAT_28d3_2964 = 0;
  DAT_28d3_2966 = 0;
  DAT_28d3_29d2 = 0;
  DAT_28d3_29d4 = 0xf;
  DAT_28d3_29d6 = 10;
  DAT_28d3_297a = 0;
  DAT_28d3_2978 = 0;
  DAT_28d3_297c = 0;
  DAT_28d3_2980 = 0;
  DAT_28d3_2984 = 0;
  DAT_28d3_29dc = 0;
  DAT_28d3_296e = 0;
  DAT_28d3_2970 = 0;
  *(char **)(iVar4 + -0x16) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  *(undefined2 *)(iVar4 + -0x18) = 0xec7;
  *(char **)(iVar4 + -0x1a) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  *(undefined2 *)(iVar4 + -0x1c) = 0x2998;
  *(undefined2 *)(iVar4 + -0x1e) = 0x1928;
  puVar5 = (undefined *)(iVar4 + -0x20);
  *(undefined2 *)(iVar4 + -0x20) = 0x9309;
  FUN_1000_1bec();
  DAT_28d3_29a2 = _DAT_28d3_0eca;
  DAT_28d3_29aa = 500;
  DAT_28d3_29ac = 500;
  DAT_28d3_29ae = 500;
  DAT_28d3_29b0 = 0;
  DAT_28d3_29b2 = 0;
  DAT_28d3_29b4 = 0;
  DAT_28d3_2972 = 0;
  DAT_28d3_2974 = 0;
  DAT_28d3_2976 = 0;
  DAT_28d3_2a44 = 0x14;
  DAT_28d3_2a46 = 0x14;
  DAT_28d3_2a48 = 0x3c;
  DAT_28d3_29d8 = 0xff;
  DAT_28d3_29b6 = 1;
  DAT_28d3_29ce = 1;
  DAT_28d3_29d0 = 0;
  DAT_28d3_2a4a = 1;
  DAT_28d3_2a4c = 100;
  DAT_28d3_2a4e = 1;
  DAT_28d3_2a50 = 100;
  DAT_28d3_2a52 = 100;
  DAT_28d3_2a54 = 100;
  *(undefined2 *)(puVar5 + 10) = 0x1000;
  puVar6 = (undefined2 *)(puVar5 + 8);
  *(undefined2 *)(puVar5 + 8) = 0x93a7;
  FUN_1928_4395();
  puVar6[1] = DAT_28d3_29b6;
  *puVar6 = 0x1000;
  puVar7 = puVar6 + -1;
  puVar6[-1] = 0x93b0;
  FUN_2229_00da();
  *(undefined2 *)((int)puVar7 + 4) = 0x2229;
  puVar8 = (undefined2 *)((int)puVar7 + 2);
  *(undefined2 *)((int)puVar7 + 2) = 0x93b6;
  FUN_2229_04e4();
  puVar8[1] = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  *puVar8 = (undefined1 *)&DAT_28d3_5796;
  puVar8[-1] = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  puVar8[-2] = 0x29de;
  puVar8[-3] = 0x2229;
  puVar9 = puVar8 + -4;
  puVar8[-4] = 0x93c3;
  FUN_1000_1bec();
  *(undefined2 *)((int)puVar9 + 10) = 0x2001;
  *(undefined2 *)((int)puVar9 + 8) = 0;
  *(undefined2 *)((int)puVar9 + 6) = 0x1000;
  piVar10 = (int *)((int)puVar9 + 4);
  *(undefined2 *)((int)puVar9 + 4) = 0x93d1;
  iVar1 = FUN_23f1_03f4();
  if (iVar1 < 0) {
    piVar10[3] = (int)((char *)s_String_reference_out_of_range_28d3_28cc + 7);
    piVar12 = piVar10 + 2;
    piVar10[2] = 0xed2;
  }
  else {
    piVar10[3] = (int)((char *)s_String_reference_out_of_range_28d3_28cc + 7);
    piVar10[2] = 0xee1;
    piVar10[1] = unaff_SS;
    *piVar10 = iVar4 + -6;
    piVar10[-1] = unaff_SS;
    piVar10[-2] = iVar4 + -10;
    piVar10[-3] = 0x23f1;
    piVar11 = piVar10 + -4;
    piVar10[-4] = 0x93f1;
    FUN_23f1_0979();
    *(undefined2 *)((int)piVar11 + 0xe) = 0x23f1;
    piVar12 = (int *)((int)piVar11 + 0xc);
    *(undefined2 *)((int)piVar11 + 0xc) = 0x93f9;
    uVar2 = FUN_23f1_030d();
    *(undefined2 *)(iVar4 + -8) = uVar2;
    if (*(int *)(iVar4 + -8) == 0) {
      piVar12[1] = 0x23f1;
      *piVar12 = 0x9419;
      iVar1 = FUN_215c_0002();
      if (iVar1 == 0) {
        DAT_28d3_2960 = 1;
      }
      piVar12[1] = 0x215c;
      *piVar12 = 0x9428;
      FUN_23c2_003a();
      piVar12[1] = (int)((char *)s_String_reference_out_of_range_28d3_28cc + 7);
      *piVar12 = 0x952;
      piVar12[-1] = 0;
      piVar12[-2] = 0;
      piVar12[-3] = 0x23c2;
      puVar13 = piVar12 + -4;
      piVar12[-4] = 0x9435;
      FUN_23c2_0001();
      *(undefined2 *)((int)puVar13 + 10) = 0x23c2;
      puVar14 = (ulong *)((int)puVar13 + 8);
      *(undefined2 *)((int)puVar13 + 8) = 0x943d;
      uVar2 = FUN_1000_4a9a();
      *(uint *)((int)puVar14 + 2) = in_DX;
      *(undefined2 *)puVar14 = uVar2;
      DAT_28d3_2a3c = *(ulong *)CONCAT22(uVar21,puVar14) - 30000;
      *puVar14 = DAT_28d3_2a3c;
      *(undefined2 *)((int)puVar14 + -2) = 0x1000;
      puVar15 = puVar14 + -1;
      *(undefined2 *)(puVar14 + -1) = 0x9455;
      DAT_28d3_2a40 = FUN_1000_475c();
      DAT_28d3_2a42 = in_DX;
      if ((DAT_28d3_2a40 | DAT_28d3_2a42) == 0) {
        *(char **)((int)puVar15 + 6) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
        *(undefined2 *)((int)puVar15 + 4) = 0xef1;
        *(undefined2 *)((int)puVar15 + 2) = 0x1000;
        *(undefined2 *)puVar15 = 0x946c;
        FUN_1000_302b();
        *(undefined2 *)((int)puVar15 + 6) = 0x1000;
        *(undefined2 *)((int)puVar15 + 4) = 0x963a;
        FUN_23f1_0e3e();
        out(0x31c,0);
        return 0;
      }
      DAT_28d3_2a3c = DAT_28d3_2a3c / 6;
      *(undefined2 *)((int)puVar15 + 6) = 0x1000;
      uVar21 = 0x2229;
      puVar16 = (undefined2 *)((int)puVar15 + 4);
      *(undefined2 *)((int)puVar15 + 4) = 0x9488;
      FUN_2229_0326();
      puVar20 = (undefined *)((int)puVar16 + 4);
      do {
        *(undefined2 *)(puVar20 + -2) = 1;
        *(undefined2 *)(puVar20 + -4) = 1;
        *(undefined2 *)(puVar20 + -6) = 0;
        *(undefined2 *)(puVar20 + -8) = uVar21;
        puVar17 = puVar20 + -10;
        *(undefined2 *)(puVar20 + -10) = 0x9493;
        FUN_23f1_115d();
        *(undefined2 *)(puVar17 + 8) = 1;
        *(undefined2 *)(puVar17 + 6) = 0x23f1;
        ppcVar18 = (char **)(puVar17 + 4);
        *(undefined2 *)(puVar17 + 4) = 0x94a0;
        FUN_1928_43ac();
        ppcVar18[2] = (char *)0x0;
        ppcVar18[1] = (char *)0x7;
        *ppcVar18 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
        ppcVar18[-1] = (char *)0x96;
        ppcVar18[-2] = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
        ppcVar18[-3] = (char *)0xb2;
        ppcVar18[-4] = "ry arena trashed";
        ppcVar19 = ppcVar18 + -5;
        ppcVar18[-5] = (char *)0x94b8;
        uVar21 = FUN_1928_5dc0();
        puVar20 = (undefined *)((int)ppcVar19 + 0x10);
        *(undefined2 *)(iVar4 + -4) = uVar21;
        *(undefined2 *)(iVar4 + -0x10) = *(undefined2 *)(iVar4 + -4);
        iVar1 = 8;
        piVar3 = (int *)0x416;
        do {
          uVar21 = 0x1000;
          if (*piVar3 == *(int *)(iVar4 + -0x10)) {
                    /* WARNING: Could not recover jumptable at 0x000194d9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
            uVar21 = (*(code *)piVar3[8])();
            return uVar21;
          }
          piVar3 = piVar3 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      } while( true );
    }
    piVar12[1] = (int)((char *)s_String_reference_out_of_range_28d3_28cc + 7);
    *piVar12 = 0xee2;
  }
  *(undefined2 *)((int)piVar12 + -2) = 0x23f1;
  *(undefined2 *)((int)piVar12 + -4) = 0x940b;
  FUN_1000_302b();
  return 0xff;
}



// Function: FUN_1928_0436

void __cdecl16far
FUN_1928_0436(undefined4 param_1,int param_2,undefined2 param_3,undefined2 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 uVar5;
  
  FUN_23f1_1211(1,0x3f);
  iVar3 = param_2 * 6;
  uVar5 = (undefined2)((ulong)param_1 >> 0x10);
  iVar4 = (int)param_1;
  iVar1 = *(int *)(iVar4 + (iVar3 + 3) * 2);
  iVar2 = *(int *)(iVar4 + (iVar3 + 2) * 2);
  FUN_23f1_1c32(iVar2,iVar1,iVar2 + *(int *)(iVar4 + (iVar3 + 4) * 2),
                iVar1 + *(int *)(iVar4 + (iVar3 + 5) * 2));
  FUN_23f1_1211(1,0);
  iVar3 = param_2 * 6;
  iVar1 = *(int *)(iVar4 + (iVar3 + 3) * 2);
  iVar2 = *(int *)(iVar4 + (iVar3 + 2) * 2);
  FUN_23f1_1c32(iVar2 + 1,iVar1 + 1,iVar2 + *(int *)(iVar4 + (iVar3 + 4) * 2) + 1,
                iVar1 + *(int *)(iVar4 + (iVar3 + 5) * 2) + 1);
  FUN_23f1_1211(1,7);
  iVar3 = param_2 * 6;
  iVar1 = *(int *)(iVar4 + (iVar3 + 3) * 2);
  iVar2 = *(int *)(iVar4 + (iVar3 + 2) * 2);
  FUN_23f1_1c32(iVar2 + 1,iVar1 + 1,iVar2 + *(int *)(iVar4 + (iVar3 + 4) * 2),
                iVar1 + *(int *)(iVar4 + (iVar3 + 5) * 2));
  FUN_23f1_1d5c(0);
  FUN_23f1_1f2a(*(int *)(iVar4 + (param_2 * 6 + 2) * 2) + 4,
                *(int *)(iVar4 + (param_2 * 6 + 3) * 2) + 4,param_3,param_4);
  return;
}



// Function: FUN_1928_05bb

void __cdecl16far
FUN_1928_05bb(undefined4 param_1,int param_2,undefined2 param_3,undefined2 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 uVar5;
  
  FUN_23f1_1211(1,0);
  iVar3 = param_2 * 6;
  uVar5 = (undefined2)((ulong)param_1 >> 0x10);
  iVar4 = (int)param_1;
  iVar1 = *(int *)(iVar4 + (iVar3 + 3) * 2);
  iVar2 = *(int *)(iVar4 + (iVar3 + 2) * 2);
  FUN_23f1_1c32(iVar2,iVar1,iVar2 + *(int *)(iVar4 + (iVar3 + 4) * 2),
                iVar1 + *(int *)(iVar4 + (iVar3 + 5) * 2));
  FUN_23f1_1211(1,7);
  iVar3 = param_2 * 6;
  iVar1 = *(int *)(iVar4 + (iVar3 + 3) * 2);
  iVar2 = *(int *)(iVar4 + (iVar3 + 2) * 2);
  FUN_23f1_1c32(iVar2 + 1,iVar1 + 1,iVar2 + *(int *)(iVar4 + (iVar3 + 4) * 2) + 1,
                iVar1 + *(int *)(iVar4 + (iVar3 + 5) * 2) + 1);
  FUN_23f1_1d5c(0);
  FUN_23f1_1f2a(*(int *)(iVar4 + (param_2 * 6 + 2) * 2) + 5,
                *(int *)(iVar4 + (param_2 * 6 + 3) * 2) + 5,param_3,param_4);
  return;
}



// Function: FUN_1928_06d5

void __cdecl16far
FUN_1928_06d5(int param_1,int param_2,undefined2 param_3,undefined2 param_4,undefined2 param_5)

{
  FUN_23f1_1d5c(param_3);
  FUN_23f1_119e(param_1,param_2,param_1 + 10,param_2 + 10);
  FUN_23f1_1f2a(param_1 + 0xf,param_2 + 2,param_4,param_5);
  return;
}



// Function: FUN_1928_0715

undefined2 __cdecl16far FUN_1928_0715(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined2 uVar2;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  iVar1 = (int)param_1;
  if ((((*(int *)(iVar1 + (param_2 * 6 + 2) * 2) < DAT_28d3_5806) &&
       (DAT_28d3_5806 <
        *(int *)(iVar1 + (param_2 * 6 + 2) * 2) + *(int *)(iVar1 + (param_2 * 6 + 4) * 2))) &&
      (*(int *)(iVar1 + (param_2 * 6 + 3) * 2) < DAT_28d3_5808)) &&
     (DAT_28d3_5808 <
      *(int *)(iVar1 + (param_2 * 6 + 3) * 2) + *(int *)(iVar1 + (param_2 * 6 + 5) * 2))) {
    return 1;
  }
  return 0;
}



// Function: FUN_1928_07ab

undefined2 __cdecl16far
FUN_1928_07ab(undefined2 param_1,undefined2 param_2,int param_3,undefined2 param_4)

{
  int iVar1;
  undefined2 uVar2;
  
  FUN_23f1_2066(0xb4,0x122,0x181,0x159,0x2a56,(char *)s_String_reference_out_of_range_28d3_28cc + 7)
  ;
  FUN_23f1_1211(1,0);
  FUN_23f1_1c32(0xb8,0x126,0x180,0x158);
  FUN_23f1_1211(1,0x3c);
  FUN_23f1_1c32(0xb4,0x122,0x17c,0x154);
  FUN_23f1_1d5c(0);
  FUN_23f1_1f2a(0xbe,0x129,param_1,param_2);
  if (param_3 != 0) {
    FUN_23f1_1f2a(0xbe,0x145,0xf51,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  FUN_1928_4fc9(0x7be,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0x7b2,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7,param_3 + 2);
  iVar1 = FUN_1928_5dc0(0x7be,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0x7b2,
                        (char *)s_String_reference_out_of_range_28d3_28cc + 7,param_3 + 2,param_4);
  FUN_23f1_1526(0xb4,0x122,0x2a56,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0);
  if (iVar1 == 0) {
LAB_1928_0898:
    uVar2 = 1;
  }
  else {
    if (iVar1 != 1) {
      if (iVar1 == 2) {
        return 2;
      }
      if (DAT_28d3_29da == 0xd) goto LAB_1928_0898;
    }
    uVar2 = 0;
  }
  return uVar2;
}



// Function: FUN_1928_08a3

bool __cdecl16far
FUN_1928_08a3(int param_1,int param_2,int param_3,undefined2 param_4,undefined2 param_5)

{
  if (param_3 == 0) {
    FUN_23f1_1526(param_1,param_2,0x2a56,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0);
  }
  else {
    FUN_23f1_2066(param_1,param_2,param_1 + 0xcd,param_2 + 0x2d,0x2a56,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7);
    FUN_23f1_1211(1,0);
    FUN_23f1_1c32(param_1 + 4,param_2 + 4,param_1 + 0xcc,param_2 + 0x2c);
    FUN_23f1_1211(1,0x3c);
    FUN_23f1_1c32(param_1,param_2,param_1 + 200,param_2 + 0x28);
    FUN_23f1_1d5c(0);
    FUN_23f1_1f2a(param_1 + 10,param_2 + 7,param_4,param_5);
  }
  return param_3 != 0;
}



// Function: FUN_1928_0948

void __cdecl16far
FUN_1928_0948(int param_1,int param_2,int param_3,int param_4,undefined2 param_5,undefined2 param_6,
             undefined2 param_7)

{
  FUN_23f1_1211(1,0);
  FUN_23f1_1c32(param_1 + 5,param_2 + 5,param_3 + 5,param_4 + 5);
  FUN_23f1_1211(1,param_5);
  FUN_23f1_1c32(param_1,param_2,param_3,param_4);
  FUN_23f1_1d5c(0);
  FUN_23f1_119e(param_1,param_2,param_3,param_4);
  FUN_23f1_1f2a(param_1 + 10,param_2 + 5,param_6,param_7);
  FUN_23f1_1bcf(param_1 + 3,param_2 + 0x12,param_3 + -3,param_2 + 0x12);
  FUN_23f1_1bcf(param_1 + 3,param_4 + -0x1e,param_3 + -3,param_4 + -0x1e);
  return;
}



// Function: FUN_1928_1906

void __cdecl16far FUN_1928_1906(int param_1,int param_2,int param_3,int param_4,undefined2 param_5)

{
  if (param_1 == param_2) {
    param_5 = 0x3c;
  }
  FUN_23f1_1211(1,param_5);
  FUN_23f1_1c32(param_3 + 1,param_4 + 1,param_3 + 9,param_4 + 9);
  return;
}



// Function: FUN_1928_2578

/* WARNING: Instruction at (ram,0x000156ec) overlaps instruction at (ram,0x000156ea)
    */
/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl16far FUN_1928_2578(undefined2 param_1,uint param_2)

{
  byte *pbVar1;
  char *pcVar2;
  uint *puVar3;
  uint uVar4;
  undefined *puVar5;
  int *piVar6;
  char cVar7;
  byte bVar8;
  uint *puVar9;
  uint *puVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  long lVar15;
  undefined uVar16;
  byte bVar17;
  uint in_CX;
  int iVar18;
  ulong uVar19;
  ulong in_EDX;
  undefined uVar20;
  ulong uVar21;
  int unaff_BP;
  uint *unaff_SI;
  uint uVar22;
  char *pcVar23;
  int *piVar24;
  undefined *puVar25;
  int *piVar26;
  int *unaff_DI;
  char *pcVar27;
  int unaff_ES;
  char *unaff_SS;
  bool bVar28;
  undefined2 uVar29;
  undefined2 uVar30;
  undefined2 uVar31;
  undefined2 uVar32;
  
  FUN_23f1_119e(500);
  FUN_23f1_1f2a(500);
  FUN_23f1_119e(500);
  FUN_23f1_119e(0x20f);
  FUN_23f1_1f2a(0x1f6);
  FUN_23f1_119e(0x20f);
  FUN_23f1_1f2a(0x1f6);
  FUN_23f1_119e(0x20f);
  FUN_23f1_1f2a(0x1f6);
  FUN_23f1_119e(0x20f);
  FUN_23f1_1f2a(0x1f6);
  while( true ) {
    uVar14 = (uint)in_EDX;
    if (*(int *)(unaff_BP + -0x26) == 0) {
      FUN_1928_1906(*(undefined2 *)(unaff_BP + -0x14),1);
      uVar29 = 0xb8ee;
      FUN_1928_1906(*(undefined2 *)(unaff_BP + -0x12),1);
      FUN_23f1_1211();
      FUN_23f1_1c32(0x6e);
      FUN_23f1_1d5c();
      uVar22 = 0x3b;
      uVar11 = FUN_1928_5a33();
      uVar13 = *(uint *)(unaff_BP + -0x10);
      if (uVar13 < 4) {
        switch(uVar13) {
        case 0:
          unaff_SI[6] = param_2;
          puVar3 = unaff_SI + 6;
          *puVar3 = *puVar3 & 1;
          uVar4 = *puVar3;
          unaff_SI[5] = (uint)unaff_DI;
          unaff_SI[3] = uVar14;
          unaff_SI[2] = uVar22;
          unaff_SI[1] = uVar13 * 2;
          *unaff_SI = uVar11;
          if (uVar4 != 0) {
            FUN_1000_1f84();
          }
          return uVar11;
        case 1:
          pbVar1 = (byte *)((int)unaff_DI + unaff_BP + 0x646);
          *pbVar1 = *pbVar1 | (byte)uVar22;
          return uVar11;
        case 2:
          if ((uVar11 | uVar14) != 0) {
            FUN_1000_58d4(*(undefined2 *)(unaff_BP + 6),*(undefined2 *)(unaff_BP + 8));
            *(undefined2 *)((int)*(undefined4 *)(unaff_BP + 6) + 4) =
                 *(undefined2 *)(unaff_BP + 0xe);
          }
          puVar10 = (uint *)FUN_1000_5c87();
          break;
        case 3:
          bVar8 = in(0x30a);
          out(0x30a,bVar8 | 1);
          uVar14 = FUN_1928_08a3(0x104);
          DAT_28d3_29d8 = 0xff;
          return uVar14;
        }
        goto code_r0x000156ef;
      }
      iVar12 = DAT_28d3_29ac;
      if (DAT_28d3_29ac < DAT_28d3_29aa) {
        iVar12 = DAT_28d3_29aa;
      }
      *(int *)(unaff_BP + -0xe) = iVar12;
      if (DAT_28d3_29ae < *(int *)(unaff_BP + -0xe)) {
        uVar30 = (undefined2)(0xdac / (long)*(int *)(unaff_BP + -0xe));
      }
      else {
        uVar30 = (undefined2)(0xdac / (long)DAT_28d3_29ae);
      }
      *(undefined2 *)(unaff_BP + -0xe) = uVar30;
      *(int *)(unaff_BP + -10) = (*(int *)(unaff_BP + -0xe) * *(int *)(unaff_BP + -0x1a)) / 10;
      iVar12 = *(int *)(unaff_BP + -0xe) * *(int *)(unaff_BP + -0x1c);
      in_EDX = (long)iVar12 % 10 & 0xffff;
      *(int *)(unaff_BP + -0xc) = iVar12 / 10;
      if (*(int *)(unaff_BP + -0x14) != 0) {
        FUN_23f1_119e(0x78);
      }
      uVar31 = 0x23f1;
      uVar30 = 0xbaf1;
      FUN_23f1_1f2a(0x6e);
      FUN_23f1_1d5c();
      in_CX = 0;
      uVar32 = 0xbb05;
      FUN_23f1_1211();
      *(undefined8 *)(unaff_BP + -0x62) = DAT_28d3_29a2;
      FUN_1000_04ab(uVar29,uVar30,uVar31,uVar32);
      FUN_23f1_1c32(0x1f5);
      FUN_23f1_1f2a(0x1fe);
      FUN_23f1_1c32(0x1f5);
      uVar31 = 0x23f1;
      uVar30 = 0xbb69;
      FUN_23f1_1f2a(0x1f9);
      *(int *)(unaff_BP + -0x2c) = DAT_28d3_29aa;
      *(double *)(unaff_BP + -0x62) = (double)((float)*(int *)(unaff_BP + -0x2c) / _DAT_28d3_0ff6);
      FUN_1000_04ab(uVar29,uVar30,uVar31);
      FUN_23f1_1c32(0x1f5);
      uVar31 = 0x23f1;
      uVar30 = 0xbbb5;
      FUN_23f1_1f2a(0x1fe);
      *(int *)(unaff_BP + -0x2c) = DAT_28d3_29ac;
      *(double *)(unaff_BP + -0x62) = (double)((float)*(int *)(unaff_BP + -0x2c) / _DAT_28d3_0ff6);
      FUN_1000_04ab(uVar29,uVar30,uVar31);
      FUN_23f1_1c32(0x1f5);
      uVar31 = 0x23f1;
      uVar30 = 0xbc03;
      FUN_23f1_1f2a(0x1fe);
      *(int *)(unaff_BP + -0x2c) = DAT_28d3_29ae;
      *(double *)(unaff_BP + -0x62) = (double)((float)*(int *)(unaff_BP + -0x2c) / _DAT_28d3_0ff6);
      FUN_1000_04ab(uVar29,uVar30,uVar31);
      FUN_23f1_1c32(0x1f5);
      FUN_23f1_1f2a(0x1fe);
    }
    uVar14 = (uint)in_EDX;
    uVar13 = *(uint *)(unaff_BP + -0x10);
    if (uVar13 < 4) break;
    if (DAT_28d3_2978 != 0) {
      FUN_23f1_1211();
      *(int *)(unaff_BP + -0x2c) =
           (*(int *)(unaff_BP + -0x1c) * 10 - *(int *)(unaff_BP + -0x24)) -
           *(int *)(unaff_BP + -0x18);
      *(double *)(unaff_BP + -0x62) = (double)((float)*(int *)(unaff_BP + -0x2c) / DAT_28d3_1073);
      FUN_1000_04ab();
      FUN_23f1_1c32(0x210);
      FUN_23f1_1f2a(0x219);
      *(int *)(unaff_BP + -0x2c) = *(int *)(unaff_BP + -0x1e) + *(int *)(unaff_BP + -0x16);
      *(double *)(unaff_BP + -0x62) = (double)((float)*(int *)(unaff_BP + -0x2c) / DAT_28d3_1073);
      FUN_1000_04ab();
      FUN_23f1_1c32(0x210);
      FUN_23f1_1f2a(0x219);
      *(int *)(unaff_BP + -0x2c) =
           (*(int *)(unaff_BP + -0x1a) * 10 - *(int *)(unaff_BP + -0x22)) -
           *(int *)(unaff_BP + -0x16);
      *(double *)(unaff_BP + -0x62) = (double)((float)*(int *)(unaff_BP + -0x2c) / DAT_28d3_1073);
      FUN_1000_04ab();
      FUN_23f1_1c32(0x210);
      FUN_23f1_1f2a(0x219);
      *(int *)(unaff_BP + -0x2c) = *(int *)(unaff_BP + -0x20) + *(int *)(unaff_BP + -0x18);
      *(double *)(unaff_BP + -0x62) = (double)((float)*(int *)(unaff_BP + -0x2c) / DAT_28d3_1073);
      FUN_1000_04ab();
      FUN_23f1_1c32(0x210);
      FUN_23f1_1f2a(0x219);
    }
    if (*(int *)(unaff_BP + -0x14) == 0) {
      uVar29 = 0xf;
    }
    else {
      uVar29 = 0;
    }
    *(undefined2 *)(unaff_BP + -2) = uVar29;
    if (*(int *)(unaff_BP + -0x14) == 0) {
      unaff_DI = (int *)0x0;
    }
    else {
      unaff_DI = (int *)((int)(undefined2 *)&DAT_28d3_0002 + 1);
    }
    FUN_23f1_1211();
    FUN_23f1_1c32(0x79);
    *(undefined4 *)(unaff_BP + -0x2a) = 0;
    while (*(long *)(unaff_BP + -0x2a) < DAT_28d3_2984) {
      if ((*(int *)(unaff_BP + -0x12) == 0) || (*(int *)(unaff_BP + -6) != 0)) {
        iVar12 = 0;
        uVar13 = FUN_1000_3eb2();
        uVar14 = *(uint *)(unaff_BP + -6);
        uVar22 = uVar13 + uVar14;
        iVar12 = *(int *)(uVar22 * 2 + DAT_28d3_2a40) + *(int *)(unaff_BP + -0x16);
      }
      else {
        iVar12 = 0;
        uVar13 = FUN_1000_3eb2();
        uVar14 = *(uint *)(unaff_BP + -6);
        uVar22 = uVar13 + uVar14;
        iVar12 = (*(int *)(unaff_BP + -0x1a) * 10 - *(int *)(uVar22 * 2 + DAT_28d3_2a40)) -
                 *(int *)(unaff_BP + -0x16);
      }
      unaff_DI = (int *)(int *)(((long)iVar12 * (long)*(int *)(unaff_BP + -0xe)) / 100);
      if ((*(int *)(unaff_BP + -0x12) == 0) || (*(int *)(unaff_BP + -0x10) != 1)) {
        iVar12 = 0;
        uVar13 = FUN_1000_3eb2();
        uVar14 = *(uint *)(unaff_BP + -8);
        uVar22 = uVar13 + uVar14;
        unaff_SI = (uint *)(uVar22 * 2 + DAT_28d3_2a40);
        unaff_ES = (((iVar12 + ((int)uVar14 >> 0xf) + (uint)CARRY2(uVar13,uVar14)) * 2 |
                    (uint)CARRY2(uVar22,uVar22)) + (uint)CARRY2(uVar22 * 2,DAT_28d3_2a40)) * 0x1000
                   + DAT_28d3_2a42;
        iVar12 = *unaff_SI + *(int *)(unaff_BP + -0x18);
      }
      else {
        iVar12 = 0;
        uVar13 = FUN_1000_3eb2();
        uVar14 = *(uint *)(unaff_BP + -8);
        uVar22 = uVar13 + uVar14;
        unaff_SI = (uint *)(uVar22 * 2 + DAT_28d3_2a40);
        unaff_ES = (((iVar12 + ((int)uVar14 >> 0xf) + (uint)CARRY2(uVar13,uVar14)) * 2 |
                    (uint)CARRY2(uVar22,uVar22)) + (uint)CARRY2(uVar22 * 2,DAT_28d3_2a40)) * 0x1000
                   + DAT_28d3_2a42;
        iVar12 = (*(int *)(unaff_BP + -0x1c) * 10 - *unaff_SI) - *(int *)(unaff_BP + -0x18);
      }
      lVar15 = (long)iVar12 * (long)*(int *)(unaff_BP + -0xe);
      in_EDX = lVar15 % 100;
      *(undefined2 *)(unaff_BP + -4) = (int)(lVar15 / 100);
      if ((((0 < (int)unaff_DI) && ((int)unaff_DI < *(int *)(unaff_BP + -10))) &&
          (0 < *(int *)(unaff_BP + -4))) && (*(int *)(unaff_BP + -4) < *(int *)(unaff_BP + -0xc))) {
        FUN_23f1_2046();
      }
      *(long *)(unaff_BP + -0x2a) = *(long *)(unaff_BP + -0x2a) + 1;
    }
    *(undefined2 *)(unaff_BP + -0x26) = 0;
    uVar29 = FUN_1928_5dc0(0x4e2,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0x466);
    *(undefined2 *)(unaff_BP + -2) = uVar29;
    *(undefined2 *)(unaff_BP + -0x2e) = *(undefined2 *)(unaff_BP + -2);
    iVar12 = 0x20;
    piVar26 = (int *)0x383f;
    do {
      if (*piVar26 == *(int *)(unaff_BP + -0x2e)) {
                    /* WARNING: Could not recover jumptable at 0x0001bff7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar14 = (*(code *)piVar26[0x20])();
        return uVar14;
      }
      piVar26 = piVar26 + 1;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
    in_CX = 0;
  }
  bVar28 = CARRY2(uVar13,uVar13);
  puVar10 = (uint *)(uVar13 * 2);
  switch(uVar13) {
  case 0:
    break;
  case 1:
    uVar14 = FUN_1000_3492(0x1da0,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
    return uVar14;
  case 2:
    uVar14 = puVar10[0x1156];
    *(uint *)(unaff_BP + -2) = puVar10[0x1157];
    *(uint *)(unaff_BP + -4) = uVar14;
    if (((*(uint *)(unaff_BP + 6) | *(uint *)(unaff_BP + 8)) != 0) &&
       (**(char **)(unaff_BP + 6) != '\0')) {
      FUN_1000_2afc((char *)*(char **)(unaff_BP + 6));
      FUN_1000_2afc(0x2577);
    }
    FUN_1000_2afc(*(undefined2 *)(unaff_BP + -4));
    uVar14 = FUN_1000_2afc(0x257a);
    return uVar14;
  case 3:
switchD_1000_bc5e_caseD_3:
    cVar7 = *(char *)(unaff_BP + (int)unaff_DI);
    pcVar2 = (char *)((int)puVar10 + (int)unaff_DI + 6);
    *pcVar2 = *pcVar2 >> 0x17;
    in_CX = CONCAT11(3,(char)in_CX + cVar7 + bVar28 +
                       *(char *)((int)puVar10 + (int)unaff_DI + -0x7ba));
LAB_1000_214e:
    puVar3 = unaff_SI;
    unaff_SI = (uint *)((int)unaff_SI + 1);
    cVar7 = *(char *)puVar3;
LAB_1000_2150:
    if (0x5f < (byte)(cVar7 - 0x20U)) goto switchD_1000_216c_caseD_13;
    bVar8 = *(byte *)((byte)(cVar7 - 0x20U) + 0x224b);
    puVar10 = (uint *)((uint)bVar8 * 2);
    uVar16 = (undefined)in_CX;
    bVar17 = (byte)(in_CX >> 8);
    uVar20 = SUB21(puVar10,0);
    pcVar27 = unaff_SS;
    switch(bVar8) {
    case 0:
      goto switchD_1000_216c_caseD_0;
    case 1:
      if (bVar17 != 0) goto switchD_1000_216c_caseD_13;
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 1;
      goto LAB_1000_214e;
    case 2:
      unaff_DI = *(int **)(unaff_BP + 4);
      iVar12 = *unaff_DI;
      *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 2;
      if (1 < bVar17) {
        if (bVar17 != 4) goto switchD_1000_216c_caseD_13;
        *(int *)(unaff_BP + -10) = iVar12;
        in_CX = CONCAT11(5,uVar16);
        goto LAB_1000_214e;
      }
      if (iVar12 < 0) {
        iVar12 = -iVar12;
        *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 2;
      }
      bVar28 = false;
      *(int *)(unaff_BP + -8) = iVar12;
      goto switchD_1000_bc5e_caseD_3;
    case 3:
      if (bVar17 != 0) goto switchD_1000_216c_caseD_13;
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 2;
      goto LAB_1000_214e;
    case 4:
      if (3 < bVar17) goto switchD_1000_216c_caseD_13;
      in_CX = CONCAT11(4,uVar16);
      *(int *)(unaff_BP + -10) = *(int *)(unaff_BP + -10) + 1;
      goto LAB_1000_214e;
    case 5:
      goto switchD_1000_216c_caseD_5;
    case 6:
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 0x10;
      break;
    case 7:
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 0x100;
    case 8:
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) & 0xffef;
      break;
    case 9:
      if (bVar17 == 0) {
        if ((*(uint *)(unaff_BP + -2) & 2) == 0) {
          *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 8;
          in_CX = CONCAT11(1,uVar16);
        }
        goto LAB_1000_214e;
      }
switchD_1000_216c_caseD_5:
      if (bVar17 < 3) {
        in_CX = CONCAT11(2,uVar16);
        LOCK();
        iVar12 = *(int *)(unaff_BP + -8);
        *(int *)(unaff_BP + -8) = (int)(char)(cVar7 + -0x30);
        UNLOCK();
        if (-1 < iVar12) {
          *(int *)(unaff_BP + -8) = *(int *)(unaff_BP + -8) + iVar12 * 10;
        }
      }
      else {
        if (bVar17 != 4) goto switchD_1000_216c_caseD_13;
        LOCK();
        iVar12 = *(int *)(unaff_BP + -10);
        *(int *)(unaff_BP + -10) = (int)(char)(cVar7 + -0x30);
        UNLOCK();
        if (iVar12 != 0) {
          *(int *)(unaff_BP + -10) = *(int *)(unaff_BP + -10) + iVar12 * 10;
        }
      }
      goto LAB_1000_214e;
    case 10:
      uVar29 = CONCAT11(10,uVar20);
      *(undefined *)(unaff_BP + -6) = 1;
      *(char *)(unaff_BP + -5) = cVar7;
      piVar26 = *(int **)(unaff_BP + 4);
      iVar12 = *piVar26;
      iVar18 = iVar12 >> 0xf;
      goto LAB_1000_227d;
    case 0xb:
      uVar29 = CONCAT11(8,uVar20);
      goto LAB_1000_2259;
    case 0xc:
      uVar29 = CONCAT11(10,uVar20);
      goto LAB_1000_2259;
    case 0xd:
      uVar29 = CONCAT11(0x10,cVar7 + -0x17);
LAB_1000_2259:
      *(undefined *)(unaff_BP + -0xb) = 0;
      *(char *)(unaff_BP + -5) = cVar7;
      iVar18 = 0;
      *(undefined *)(unaff_BP + -6) = 0;
      piVar26 = *(int **)(unaff_BP + 4);
      iVar12 = *piVar26;
LAB_1000_227d:
      piVar24 = piVar26 + 1;
      *(uint **)(unaff_BP + 6) = unaff_SI;
      if ((*(uint *)(unaff_BP + -2) & 0x10) != 0) {
        iVar18 = *piVar24;
        piVar24 = piVar26 + 2;
      }
      *(int **)(unaff_BP + 4) = piVar24;
      puVar10 = (uint *)(unaff_BP + -0x45);
      if ((iVar12 == 0) && (iVar18 == 0)) {
        if (*(int *)(unaff_BP + -10) != 0) goto LAB_1000_22ae;
        *(char *)puVar10 = '\0';
      }
      else {
        *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 4;
LAB_1000_22ae:
        FUN_1000_3faf(uVar29,*(undefined *)(unaff_BP + -6),(char)((uint)uVar29 >> 8),puVar10);
      }
      iVar12 = *(int *)(unaff_BP + -10);
      if (iVar12 < 0) {
LAB_1000_23be:
        if (((*(uint *)(unaff_BP + -2) & 8) != 0) && (iVar12 = *(int *)(unaff_BP + -8), 0 < iVar12))
        goto LAB_1000_23cc;
      }
      else {
LAB_1000_23cc:
        FUN_1000_20b5();
        if (*(char *)puVar10 == '-') {
          in_CX = in_CX - 1;
        }
        if (iVar12 - in_CX != 0 && (int)in_CX <= iVar12) {
          *(int *)(unaff_BP + -0xe) = iVar12 - in_CX;
        }
      }
      if (*(char *)puVar10 == '-') {
LAB_1000_23ee:
        if ((0 < *(int *)(unaff_BP + -0xe)) && (in_CX = *(uint *)(unaff_BP + -10), (int)in_CX < 0))
        {
          *(int *)(unaff_BP + -0xe) = *(int *)(unaff_BP + -0xe) + -1;
        }
      }
      else if (*(char *)(unaff_BP + -0xb) != '\0') {
        puVar10 = (uint *)((int)puVar10 + -1);
        *(char *)puVar10 = *(char *)(unaff_BP + -0xb);
        goto LAB_1000_23ee;
      }
      FUN_1000_20b5();
LAB_1000_2401:
      pcVar23 = *(char **)(unaff_BP + -4);
      uVar14 = *(uint *)(unaff_BP + -8);
      if ((*(uint *)(unaff_BP + -2) & 5) == 5) {
        cVar7 = *(char *)(unaff_BP + -5);
        if (cVar7 == 'o') {
          if (*(int *)(unaff_BP + -0xe) < 1) {
            *(undefined2 *)(unaff_BP + -0xe) = 1;
          }
        }
        else if ((cVar7 == 'x') || (cVar7 == 'X')) {
          *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 0x40;
          uVar14 = uVar14 - 2;
          piVar6 = (int *)(unaff_BP + -0xe);
          iVar12 = *piVar6;
          *piVar6 = *piVar6 + -2;
          if (SBORROW2(iVar12,2) != *piVar6 < 0) {
            *(undefined2 *)(unaff_BP + -0xe) = 0;
          }
        }
      }
      in_CX = in_CX + *(int *)(unaff_BP + -0xe);
      if ((*(uint *)(unaff_BP + -2) & 2) == 0) {
        for (; (int)in_CX < (int)uVar14; uVar14 = uVar14 - 1) {
          FUN_1000_20c2();
        }
      }
      if ((*(uint *)(unaff_BP + -2) & 0x40) != 0) {
        FUN_1000_20c2();
        FUN_1000_20c2();
      }
      iVar12 = *(int *)(unaff_BP + -0xe);
      if (0 < iVar12) {
        in_CX = in_CX - iVar12;
        uVar14 = uVar14 - iVar12;
        cVar7 = *(char *)puVar10;
        if (((cVar7 == '-') || (cVar7 == ' ')) || (cVar7 == '+')) {
          puVar10 = (uint *)((int)puVar10 + 1);
          FUN_1000_20c2();
          in_CX = in_CX - 1;
          uVar14 = uVar14 - 1;
        }
        uVar21 = (ulong)uVar14;
        uVar19 = (ulong)in_CX;
        for (; iVar12 != 0; iVar12 = iVar12 + -1) {
          FUN_1000_20c2();
          uVar14 = (uint)uVar21;
          in_CX = (uint)uVar19;
        }
      }
      if (in_CX != 0) {
        uVar19 = (ulong)(uVar14 - in_CX);
        do {
          puVar3 = puVar10;
          puVar10 = (uint *)((int)puVar10 + 1);
          *pcVar23 = *(char *)puVar3;
          pcVar23 = pcVar23 + 1;
          pcVar2 = (char *)(unaff_BP + -0x14);
          cVar7 = *pcVar2;
          *pcVar2 = *pcVar2 + -1;
          if (*pcVar2 == '\0' || SBORROW1(cVar7,'\x01') != *pcVar2 < '\0') {
            FUN_1000_20cb();
          }
          uVar14 = (uint)uVar19;
          in_CX = in_CX - 1;
        } while (in_CX != 0);
      }
      if (0 < (int)uVar14) {
        do {
          FUN_1000_20c2();
          uVar14 = uVar14 - 1;
        } while (uVar14 != 0);
      }
LAB_1000_210b:
      unaff_ES = (int)((ulong)*(uint **)(unaff_BP + 6) >> 0x10);
      puVar10 = (uint *)*(uint **)(unaff_BP + 6);
LAB_1000_210e:
      unaff_SI = (uint *)((int)puVar10 + 1);
      cVar7 = *(char *)puVar10;
      if (cVar7 == '\0') goto LAB_1000_250e;
      if (cVar7 == '%') {
        *(uint **)(unaff_BP + -0x10) = unaff_SI;
        puVar3 = unaff_SI;
        unaff_SI = puVar10 + 1;
        cVar7 = *(char *)puVar3;
        if (cVar7 != '%') goto code_r0x00012132;
      }
      *pcVar23 = cVar7;
      pcVar23 = pcVar23 + 1;
      pcVar2 = (char *)(unaff_BP + -0x14);
      cVar7 = *pcVar2;
      *pcVar2 = *pcVar2 + -1;
      puVar10 = unaff_SI;
      if (*pcVar2 == '\0' || SBORROW1(cVar7,'\x01') != *pcVar2 < '\0') {
        FUN_1000_20cb();
      }
      goto LAB_1000_210e;
    case 0xe:
      *(char *)(unaff_BP + -5) = cVar7;
      *(uint **)(unaff_BP + 6) = unaff_SI;
      puVar25 = (undefined *)(unaff_BP + -0x46);
      iVar12 = *(int *)(unaff_BP + 4);
      *(int *)(unaff_BP + 4) = iVar12 + 2;
      if ((*(uint *)(unaff_BP + -2) & 0x20) != 0) {
        *(int *)(unaff_BP + 4) = iVar12 + 4;
        FUN_1000_2083();
        puVar5 = puVar25;
        puVar25 = (undefined *)(unaff_BP + -0x45);
        *puVar5 = 0x3a;
      }
      FUN_1000_2083();
      *puVar25 = 0;
      *(undefined *)(unaff_BP + -6) = 0;
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) & 0xfffb;
      puVar10 = (uint *)(unaff_BP + -0x46);
      in_CX = (int)puVar25 - (int)puVar10;
      goto LAB_1000_23be;
    case 0xf:
      *(uint **)(unaff_BP + 6) = unaff_SI;
      *(char *)(unaff_BP + -5) = cVar7;
      in_CX = *(uint *)(unaff_BP + -10);
      if ((int)in_CX < 0) {
        in_CX = 6;
      }
      uVar14 = *(uint *)(unaff_BP + -2);
      if ((*(uint *)(unaff_BP + -2) & 0x100) == 0) {
        *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 8;
        uVar29 = 6;
      }
      else {
        uVar29 = 8;
        *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 10;
      }
      thunk_FUN_1000_068f(uVar29,uVar14 & 1,cVar7,unaff_BP + -0x45,unaff_SS);
      puVar10 = (uint *)(unaff_BP + -0x45);
      goto LAB_1000_23be;
    case 0x10:
      *(uint **)(unaff_BP + 6) = unaff_SI;
      *(char *)(unaff_BP + -5) = cVar7;
      uVar14 = **(uint **)(unaff_BP + 4);
      *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 2;
      puVar10 = (uint *)(unaff_BP + -0x45);
      *puVar10 = uVar14 & 0xff;
      in_CX = 1;
      goto LAB_1000_2401;
    case 0x11:
      *(uint **)(unaff_BP + 6) = unaff_SI;
      *(char *)(unaff_BP + -5) = cVar7;
      if ((*(uint *)(unaff_BP + -2) & 0x20) == 0) {
                    /* WARNING: Load size is inaccurate */
        puVar10 = *(uint **)*(undefined2 *)(unaff_BP + 4);
        *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 2;
        pcVar27 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
        puVar9 = puVar10;
      }
      else {
        puVar3 = *(uint **)*(undefined2 *)(unaff_BP + 4);
        pcVar27 = (char *)((ulong)puVar3 >> 0x10);
        puVar10 = (uint *)puVar3;
        *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 4;
        puVar9 = (uint *)((uint)pcVar27 | (uint)puVar10);
      }
      if (puVar9 == (uint *)0x0) {
        pcVar27 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
        puVar10 = (uint *)0x2244;
      }
      FUN_1000_20b5();
      if (*(uint *)(unaff_BP + -10) < in_CX) {
        in_CX = *(uint *)(unaff_BP + -10);
      }
      goto LAB_1000_2401;
    case 0x12:
      *(uint **)(unaff_BP + 6) = unaff_SI;
      if ((*(uint *)(unaff_BP + -2) & 0x20) == 0) {
                    /* WARNING: Load size is inaccurate */
        piVar26 = *(int **)*(undefined2 *)(unaff_BP + 4);
        *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 2;
        pcVar27 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
      }
      else {
        piVar6 = *(int **)*(undefined2 *)(unaff_BP + 4);
        pcVar27 = (char *)((ulong)piVar6 >> 0x10);
        piVar26 = (int *)piVar6;
        *(int *)(unaff_BP + 4) = *(int *)(unaff_BP + 4) + 4;
      }
      *piVar26 = (uint)(byte)(0x50 - *(char *)(unaff_BP + -0x14)) + *(int *)(unaff_BP + -0x12);
      if ((*(uint *)(unaff_BP + -2) & 0x10) != 0) {
        piVar26[1] = 0;
      }
      pcVar23 = *(char **)(unaff_BP + -4);
      goto LAB_1000_210b;
    default:
      goto switchD_1000_216c_caseD_13;
    case 0x16:
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) & 0xffdf;
      break;
    case 0x17:
      *(uint *)(unaff_BP + -2) = *(uint *)(unaff_BP + -2) | 0x20;
    }
    in_CX = CONCAT11(5,uVar16);
    goto LAB_1000_214e;
  }
code_r0x000156ef:
  puVar3 = puVar10;
  uVar13 = *puVar3;
  *puVar3 = *puVar3 + 1;
  puVar10[1] = puVar10[1] + (uint)(0xfffe < uVar13);
  return *(uint *)(unaff_BP + 6);
code_r0x00012132:
  *(char **)(unaff_BP + -4) = pcVar23;
  in_CX = 0;
  *(undefined2 *)(unaff_BP + -0xe) = 0;
  *(undefined2 *)(unaff_BP + -2) = 0x20;
  *(undefined *)(unaff_BP + -0xb) = 0;
  *(undefined2 *)(unaff_BP + -8) = 0xffff;
  *(undefined2 *)(unaff_BP + -10) = 0xffff;
  goto LAB_1000_2150;
switchD_1000_216c_caseD_0:
  if (bVar17 != 0) {
switchD_1000_216c_caseD_13:
    pcVar27 = *(char **)(unaff_BP + -0x10);
    uVar29 = *(undefined2 *)(unaff_BP + 8);
    do {
      FUN_1000_20c2();
      pcVar2 = pcVar27;
      pcVar27 = pcVar27 + 1;
    } while (*pcVar2 != '\0');
LAB_1000_250e:
    if (*(char *)(unaff_BP + -0x14) < 'P') {
      FUN_1000_20cb();
    }
    if (*(int *)(unaff_BP + -0x16) == 0) {
      uVar14 = *(uint *)(unaff_BP + -0x12);
    }
    else {
      uVar14 = 0xffff;
    }
    return uVar14;
  }
  if (*(char *)(unaff_BP + -0xb) != '+') {
    *(char *)(unaff_BP + -0xb) = cVar7;
  }
  goto LAB_1000_214e;
}



// Function: FUN_1928_38fa

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 __cdecl16far
FUN_1928_38fa(int param_1,int param_2,double param_3,double param_4,int param_5)

{
  undefined2 *puVar1;
  double dVar2;
  int iVar3;
  undefined2 uVar4;
  int iVar5;
  undefined2 *puVar6;
  undefined2 unaff_SS;
  longdouble in_ST0;
  longdouble lVar7;
  longdouble in_ST1;
  longdouble in_ST2;
  longdouble in_ST3;
  longdouble in_ST4;
  longdouble in_ST5;
  longdouble in_ST6;
  longdouble in_ST7;
  char local_12;
  undefined2 auStack_11 [3];
  char local_b;
  double local_a;
  
  local_12 = '_';
  puVar6 = (undefined2 *)(&local_12 + 1);
  for (iVar5 = 3; iVar5 != 0; iVar5 = iVar5 + -1) {
    puVar1 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar1 = 0;
  }
  iVar5 = 0;
  FUN_23f1_1d5c(0);
  while( true ) {
    FUN_23f1_1211(1,0xf);
    FUN_23f1_1c32(param_1,param_2,param_1 + 0x3a,param_2 + 0xe);
    FUN_23f1_1f2a(param_1 + 9,param_2 + 4,&local_12);
    lVar7 = in_ST0;
    do {
      iVar3 = FUN_1000_1953();
    } while (iVar3 == 0);
    local_b = FUN_1000_18df();
    iVar3 = iVar5;
    if (((('/' < local_b) && (local_b < ':')) || (local_b == '.')) && (iVar5 < 5)) {
      (&local_12)[iVar5] = local_b;
      iVar3 = iVar5 + 1;
      (&local_12)[iVar5 + 1] = '_';
    }
    iVar5 = iVar3;
    if ((local_b == '\b') && (0 < iVar3)) {
      (&local_12)[iVar3] = '\0';
      iVar5 = iVar3 + -1;
      (&stack0xffed)[iVar3] = 0x5f;
    }
    if (local_b == '\x1b') break;
    in_ST0 = lVar7;
    if (local_b == '\r') {
      in_ST0 = in_ST1;
      in_ST1 = in_ST2;
      in_ST2 = in_ST3;
      in_ST3 = in_ST4;
      in_ST4 = in_ST5;
      in_ST5 = in_ST6;
      in_ST6 = in_ST7;
      FUN_1000_0492(&local_12);
      local_a = (double)lVar7;
      if ((param_3 <= local_a) && (local_a <= param_4)) {
        dVar2 = local_a;
        if (param_5 != 0) {
          dVar2 = DAT_28d3_29a2;
          if (param_5 == 1) {
            local_a = (double)(_DAT_28d3_0ff6 * (float)lVar7);
          }
          else if (param_5 == 2) {
            local_a = (double)(DAT_28d3_1073 * (float)lVar7);
          }
        }
        DAT_28d3_29a2 = dVar2;
        uVar4 = FUN_1000_0f76();
        return uVar4;
      }
      in_ST7 = in_ST6;
      FUN_1928_07ab((char *)s_HCOut_of_range_28d3_1205 + 2,
                    (char *)s_String_reference_out_of_range_28d3_28cc + 7,0,0);
    }
  }
  return 0xffff;
}



// Function: FUN_1928_3a59

void FUN_1928_3a59(undefined2 param_1_00,undefined2 param_1)

{
  byte bVar1;
  
  FUN_1928_08a3(0x104,0x10e,1,(char *)s_Please_wait_28d3_1214,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  bVar1 = in(0x30a);
  out(0x30a,bVar1 & 0xfe);
  FUN_1000_537f(0x1e);
  FUN_215c_05ad(param_1);
  bVar1 = in(0x30a);
  out(0x30a,bVar1 | 1);
  FUN_1928_08a3(0x104,0x10e,0,0x1220,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  DAT_28d3_29d8 = 0xff;
  return;
}



// Function: FUN_1928_3aaf

void FUN_1928_3aaf(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  FUN_1928_0948(0xb4,0xb4,0x1c2,400,3,(char *)s_Glass_Load_28d3_1221,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_1928_4fc9(0x662,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0x656,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7,3);
  FUN_23f1_119e(300,0xe6,0x186,0x14f);
  FUN_23f1_119e(0x136,0x126,0x15e,0x138);
  FUN_23f1_1f2a(0x136,0xf0,0x122c,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_23f1_1f2a(0x152,0x104,0x1236,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_23f1_1f2a(0x136,0x118,0x1239,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_23f1_1f2a(0x136,0x140,0x1243,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  do {
    iVar1 = FUN_1928_5dc0(0x662,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0x656,
                          (char *)s_String_reference_out_of_range_28d3_28cc + 7,3,0);
    iVar2 = 4;
    piVar3 = (int *)0x3bb7;
    do {
      if (*piVar3 == iVar1) {
                    /* WARNING: Could not recover jumptable at 0x0001ce00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*(code *)piVar3[4])();
        return;
      }
      piVar3 = piVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  } while( true );
}



// Function: FUN_1928_4395

void __cdecl16far FUN_1928_4395(void)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    ((undefined2 *)&DAT_28d3_29ba)[iVar1] = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 10);
  return;
}



// Function: FUN_1928_43ac

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl16far FUN_1928_43ac(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined local_28 [26];
  int local_e;
  int local_c;
  int local_a;
  int local_8;
  undefined2 local_6;
  undefined2 local_4;
  
  if (param_1 == 0) {
    local_4 = 0x90;
    local_6 = 0x1d0;
  }
  else {
    local_4 = 0;
    local_6 = 0x27f;
  }
  for (uVar1 = (uint)(param_1 == 0); (int)uVar1 < 0x14; uVar1 = uVar1 + 1) {
    FUN_23f1_125e(uVar1 * 8 + 0x992,(char *)s_String_reference_out_of_range_28d3_28cc + 7,1);
    FUN_23f1_1c32();
  }
  iVar2 = 0;
  do {
    FUN_23f1_125e((0x13 - iVar2) * 8 + 0x992,(char *)s_String_reference_out_of_range_28d3_28cc + 7,1
                 );
    FUN_23f1_1c32();
    iVar2 = iVar2 + 1;
  } while (iVar2 < 10);
  FUN_23f1_1d5c(1);
  FUN_23f1_1f2a();
  FUN_23f1_1f2a();
  if (param_1 != 0) {
    FUN_23f1_1211(1,1);
    iVar2 = 0;
    do {
      local_a = iVar2 * 0xc;
      local_c = local_a + 0xb8;
      local_e = local_a + 0xb6;
      FUN_23f1_1c32();
      iVar2 = iVar2 + 1;
    } while (iVar2 < 7);
    FUN_1928_4a4a();
    FUN_1928_4fc9();
    FUN_1928_60ae(local_28);
    FUN_23f1_1d5c(9);
    FUN_23f1_1f2a();
    FUN_23f1_1d5c(0x3b);
    if (DAT_28d3_29dc != 0) {
      FUN_23f1_1f2a();
    }
    FUN_1928_06d5();
    FUN_1928_06d5();
    FUN_1928_06d5();
    FUN_23f1_1211(1,0x3c);
    if (DAT_28d3_29b6 == 0) {
      FUN_23f1_1c32();
    }
    else {
      FUN_23f1_1c32();
      FUN_1928_4979(0x1e,0x55,DAT_28d3_29b8);
    }
    if (DAT_28d3_29ce != 0) {
      FUN_23f1_1c32();
    }
    FUN_23f1_1f2a();
    FUN_23f1_1f2a();
    FUN_23f1_1f2a();
    FUN_1000_40a5();
    FUN_23f1_1f2a();
    FUN_23f1_1f2a();
    FUN_23f1_1f2a();
    FUN_23f1_1f2a();
    FUN_1000_04ab(DAT_28d3_29a2,4,local_28);
    FUN_23f1_1f2a();
    FUN_23f1_1f2a();
    local_8 = DAT_28d3_29aa;
    FUN_1000_04ab((double)((float)DAT_28d3_29aa / _DAT_28d3_0ff6),4,local_28);
    FUN_23f1_1f2a();
    FUN_23f1_1f2a();
    local_8 = DAT_28d3_29ac;
    FUN_1000_04ab((double)((float)DAT_28d3_29ac / _DAT_28d3_0ff6),4,local_28);
    FUN_23f1_1f2a();
    FUN_23f1_1f2a();
    local_8 = DAT_28d3_29ae;
    FUN_1000_04ab((double)((float)DAT_28d3_29ae / _DAT_28d3_0ff6),4,local_28);
    FUN_23f1_1f2a();
    FUN_23f1_119e();
    if (DAT_28d3_2960 != 0) {
      FUN_23f1_1d5c(0x3c);
      FUN_23f1_1f2a();
    }
    FUN_23f1_1d5c(0);
    FUN_23f1_1211(1,0x3b);
    FUN_23f1_1c32();
    FUN_1000_40a5();
    FUN_23f1_1f2a();
  }
  FUN_23f1_1d5c(0x3b);
  FUN_23f1_1f2a();
  FUN_23f1_1f2a();
  FUN_1928_4827(0);
  if (DAT_28d3_2978 != 0) {
    FUN_1928_4acf(0x23f1,DAT_28d3_297a,1);
  }
  return;
}



// Function: FUN_1928_4827

void __cdecl16far FUN_1928_4827(int param_1)

{
  int iVar1;
  int iVar2;
  undefined local_c [6];
  uint local_6;
  undefined2 local_4;
  
  FUN_23f1_1d5c(0x3b);
  FUN_23f1_1211(1,0);
  if (DAT_28d3_29b6 == 0) {
    FUN_23f1_119e(0x14,0x194,0x3c,0x1a2);
    FUN_23f1_1c32(0x15,0x195,0x3b,0x1a1);
    FUN_1000_4055(DAT_28d3_29cc,local_c);
    FUN_23f1_1f2a(0x18,0x198,local_c);
  }
  else {
    local_6 = 1;
    iVar1 = 0;
    do {
      iVar2 = 0;
      do {
        FUN_23f1_119e(iVar2 * 0x2a + 10,iVar1 * 0x10 + 0x194,iVar2 * 0x2a + 0x32,
                      iVar1 * 0x10 + 0x1a2);
        if (param_1 != 0) {
          if ((DAT_28d3_4fe2 & local_6) == 0) {
            local_4 = 0;
          }
          else {
            local_4 = 0x3c;
          }
          FUN_23f1_1211(1,local_4);
        }
        FUN_23f1_1c32(iVar2 * 0x2a + 0xb,iVar1 * 0x10 + 0x195,iVar2 * 0x2a + 0x31,
                      iVar1 * 0x10 + 0x1a1);
        if ((DAT_28d3_29b8 & local_6) != 0) {
          FUN_1000_4055(((undefined2 *)&DAT_28d3_29ba)[iVar1 * 3 + iVar2],local_c);
          FUN_23f1_1f2a(iVar2 * 0x2a + 0xe,iVar1 * 0x10 + 0x198,local_c);
        }
        local_6 = local_6 << 1;
        iVar2 = iVar2 + 1;
      } while (iVar2 < 3);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 3);
  }
  return;
}



// Function: FUN_1928_4979

void __cdecl16far FUN_1928_4979(int param_1,int param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  uint local_6;
  undefined local_4 [2];
  
  local_6 = 1;
  iVar1 = 0;
  do {
    iVar2 = 0;
    do {
      FUN_23f1_119e(iVar2 * 0x10 + param_1,iVar1 * 0x10 + param_2,iVar2 * 0x10 + param_1 + 0xe,
                    iVar1 * 0x10 + param_2 + 0xe);
      if ((param_3 & local_6) != 0) {
        FUN_23f1_1c32(iVar2 * 0x10 + param_1 + 1,iVar1 * 0x10 + param_2 + 1,
                      iVar2 * 0x10 + param_1 + 0xd,iVar1 * 0x10 + param_2 + 0xd);
      }
      local_6 = local_6 << 1;
      FUN_1000_4055(iVar1 * 3 + iVar2 + 1,local_4);
      FUN_23f1_1f2a(iVar2 * 0x10 + param_1 + 4,iVar1 * 0x10 + param_2 + 4,local_4);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 3);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 3);
  return;
}



// Function: FUN_1928_4a4a

void __cdecl16far FUN_1928_4a4a(void)

{
  int iVar1;
  int iVar2;
  uint local_a;
  int local_8;
  int local_6;
  undefined2 local_4;
  
  local_4 = 0;
  local_8 = 2;
  while (0 < local_8) {
    local_8 = local_8 + -1;
    iVar1 = 0;
    do {
      iVar2 = 0;
      do {
        local_a = 0x80;
        local_6 = 0;
        do {
          if ((local_a & *(byte *)(iVar1 * 0xf + iVar2 + 0xa32)) == 0) {
            FUN_23f1_2046(iVar2 * 8 + local_6 + local_8 * 3 + 500,local_8 * 3 + (0x32 - iVar1),
                          local_4);
          }
          local_a = (int)local_a >> 1;
          local_6 = local_6 + 1;
        } while (local_6 < 8);
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0xf);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x22);
    local_4 = 9;
  }
  return;
}



// Function: FUN_1928_4acf

/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Instruction at (ram,0x000156ec) overlaps instruction at (ram,0x000156ea)
    */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint * __cdecl16near
FUN_1928_4acf(uint **param_1_00,uint **param_1,undefined2 param_3,undefined2 param_4,uint *param_5)

{
  uint **ppuVar1;
  uint **ppuVar2;
  uint *puVar3;
  uint *puVar4;
  byte bVar5;
  code *pcVar6;
  char cVar7;
  byte bVar8;
  char cVar9;
  uint *puVar10;
  uint **ppuVar11;
  uint *puVar12;
  uint uVar13;
  uint uVar14;
  undefined uVar15;
  byte bVar18;
  uint *puVar16;
  int iVar17;
  char *pcVar19;
  int iVar20;
  char *pcVar21;
  uint *in_EDX;
  undefined uVar22;
  int *piVar23;
  char *pcVar24;
  uint **ppuVar25;
  uint **unaff_SI;
  char *pcVar26;
  byte *pbVar27;
  char *pcVar28;
  int unaff_ES;
  undefined2 uVar29;
  char *unaff_SS;
  bool bVar30;
  undefined uStack_48;
  uint auStack_47 [11];
  int iStack_30;
  undefined2 uStack_2e;
  undefined4 uStack_2c;
  char *pcVar31;
  uint *local_1e;
  undefined8 local_1c;
  uint *local_14;
  uint **local_12;
  int local_10;
  undefined2 local_e;
  char *local_c;
  char *local_a;
  undefined2 local_8;
  undefined4 local_6;
  
  FUN_23f1_1d5c();
  uStack_2c._2_2_ = (undefined2 *)0x96;
  uStack_2c._0_2_ = 0x23f1;
  uStack_2e = 0xdd6c;
  cVar9 = FUN_23f1_1f2a();
  uVar13 = DAT_28d3_297a;
  if (3 < DAT_28d3_297a) {
    iVar17 = DAT_28d3_29ac;
    if (DAT_28d3_29ac < DAT_28d3_29aa) {
      iVar17 = DAT_28d3_29aa;
    }
    if (DAT_28d3_29ae < iVar17) {
      iVar17 = (int)(3000 / (long)iVar17);
    }
    else {
      iVar17 = (int)(3000 / (long)DAT_28d3_29ae);
    }
    local_8 = (iVar17 * local_10) / 10;
    uStack_2c._2_2_ = (undefined2 *)0xa0;
    uStack_2c._0_2_ = 0x23f1;
    uStack_2e = 0xde8f;
    FUN_23f1_119e();
    if (param_1._2_2_ == 0) {
      if ((uint **)param_1 == (uint **)0x0) {
        iVar20 = 0;
        uVar13 = FUN_1000_3eb2();
        iVar20 = *(int *)(uVar13 + DAT_28d3_2a40);
        FUN_1000_3eb2();
      }
      else if ((uint **)param_1 == (uint **)((int)(undefined2 *)&DAT_28d3_0000 + 1)) {
        iVar20 = 0;
        uVar13 = FUN_1000_3eb2();
        uVar14 = uVar13 + 1;
        iVar20 = *(int *)(uVar14 * 2 + DAT_28d3_2a40);
        FUN_1000_3eb2();
      }
      else {
        FUN_1000_3eb2();
        iVar20 = 0;
        uVar13 = FUN_1000_3eb2();
        pcVar26 = (char *)(uVar13 + (int)(uint **)param_1) + -2;
        iVar20 = *(int *)((int)pcVar26 * 2 + DAT_28d3_2a40);
        FUN_1000_0f76();
      }
      local_c = (char *)((iVar20 * iVar17) / 100);
      uStack_2c._2_2_ = (undefined2 *)local_8;
      uStack_2c._0_2_ = (uint)local_c;
      uStack_2e = 0x1000;
      iStack_30 = 0xe203;
      uVar13 = FUN_1928_4f92();
      local_6 = (uint *)(ulong)uVar13;
    }
    else {
      uStack_2c._2_2_ = (undefined2 *)0xdea3;
      FUN_23f1_1211();
      uStack_2c._2_2_ = (undefined2 *)0xa1;
      uStack_2c._0_2_ = 0x23f1;
      uStack_2e = 0xdec0;
      FUN_23f1_1c32();
      for (local_6 = (uint *)0x0; (long)local_6 < DAT_28d3_2984;
          local_6 = (uint *)((long)local_6 + 1)) {
        if ((uint **)param_1 == (uint **)0x0) {
          iVar20 = 0;
          uVar13 = FUN_1000_3eb2();
          iVar20 = *(int *)(uVar13 + DAT_28d3_2a40);
          FUN_1000_3eb2();
        }
        else if ((uint **)param_1 == (uint **)((int)(undefined2 *)&DAT_28d3_0000 + 1)) {
          iVar20 = 0;
          uVar13 = FUN_1000_3eb2();
          uVar14 = uVar13 + 1;
          iVar20 = *(int *)(uVar14 * 2 + DAT_28d3_2a40);
          FUN_1000_3eb2();
        }
        else {
          FUN_1000_3eb2();
          FUN_1000_0f76();
          iVar20 = 0;
          uVar13 = FUN_1000_3eb2();
          pcVar26 = (char *)(uVar13 + (int)(uint **)param_1) + -2;
          iVar20 = *(int *)((int)pcVar26 * 2 + DAT_28d3_2a40);
        }
        local_c = (char *)((iVar20 * iVar17) / 100);
        uStack_2c._2_2_ = (undefined2 *)local_8;
        uStack_2c._0_2_ = (uint)local_c;
        uStack_2e = 0x1000;
        iStack_30 = 0xe064;
        FUN_1928_4f92();
      }
    }
    return (uint *)local_6;
  }
  iVar17 = DAT_28d3_297a * 2;
  uVar29 = 0x1000;
  switch(DAT_28d3_297a) {
  case 0:
    uStack_2c._2_2_ = &local_8;
    uStack_2c._0_2_ = 0x1000;
    uStack_2e = 0x576e;
    uVar29 = param_1._2_2_;
    FUN_1000_599f();
    local_6 = (uint *)CONCAT22(uStack_2c._2_2_[2],(byte *)local_6);
    puVar12 = (uint *)FUN_1000_5c87();
    puVar3 = puVar12;
    uVar13 = *puVar3;
    *puVar3 = *puVar3 + 1;
    puVar12[1] = puVar12[1] + (uint)(0xfffe < uVar13);
    uStack_2c._2_2_ = (undefined2 *)&DAT_28d3_57e8;
    uStack_2c._0_2_ = 0x1000;
    uStack_2e = 0x579c;
    puVar12 = (uint *)FUN_1000_6bc3();
    return puVar12;
  case 1:
switchD_1000_dd7c_caseD_1:
    iStack_30 = 0xbd7d;
    uStack_2e = uVar29;
    FUN_1000_04ab();
    uStack_2c._2_2_ = (undefined2 *)0xbd91;
    FUN_23f1_1c32();
    uStack_2c._2_2_ = (undefined2 *)0xbda4;
    FUN_23f1_1f2a();
    uStack_2e = 0x23f1;
    iStack_30 = -0x4232;
    FUN_1000_04ab();
    uStack_2c._2_2_ = (undefined2 *)0xbde2;
    FUN_23f1_1c32();
    uStack_2c._2_2_ = (undefined2 *)0xbdf5;
    FUN_23f1_1f2a();
    while( true ) {
      if (local_1c._6_2_ == 0) {
        uVar29 = 0xf;
      }
      else {
        uVar29 = 0;
      }
      local_6 = (uint *)CONCAT22(uVar29,(byte *)local_6);
      if (local_1c._6_2_ == 0) {
        ppuVar11 = (uint **)0x0;
      }
      else {
        ppuVar11 = (uint **)((int)(undefined2 *)&DAT_28d3_0002 + 1);
      }
      FUN_23f1_1211();
      uVar13 = 0x23f1;
      uStack_2c._2_2_ = (undefined2 *)0xbe3a;
      FUN_23f1_1c32();
      for (uStack_2c = 0; uStack_2c < DAT_28d3_2984; uStack_2c = uStack_2c + 1) {
        if ((local_14 == (uint *)0x0) || (local_8 != 0)) {
          iVar17 = 0;
          uVar13 = FUN_1000_3eb2();
          uVar14 = uVar13 + local_8;
          iVar17 = *(int *)(uVar14 * 2 + DAT_28d3_2a40) + local_1c._4_2_;
        }
        else {
          iVar17 = 0;
          uVar13 = FUN_1000_3eb2();
          uVar14 = uVar13 + local_8;
          iVar17 = ((int)local_1c * 10 - *(int *)(uVar14 * 2 + DAT_28d3_2a40)) - local_1c._4_2_;
        }
        ppuVar11 = (uint **)(uint **)(((long)iVar17 * (long)local_10) / 100);
        if ((local_14 == (uint *)0x0) ||
           (local_12 != (uint **)((int)(undefined2 *)&DAT_28d3_0000 + 1))) {
          iVar17 = 0;
          uVar13 = FUN_1000_3eb2();
          pcVar26 = local_a + uVar13;
          unaff_SI = (uint **)((int)pcVar26 * 2 + DAT_28d3_2a40);
          unaff_ES = (((iVar17 + ((int)local_a >> 0xf) + (uint)CARRY2(uVar13,(uint)local_a)) * 2 |
                      (uint)CARRY2((uint)pcVar26,(uint)pcVar26)) +
                     (uint)CARRY2((int)pcVar26 * 2,DAT_28d3_2a40)) * 0x1000 + DAT_28d3_2a42;
          iVar17 = (int)*unaff_SI + local_1c._2_2_;
        }
        else {
          iVar17 = 0;
          uVar13 = FUN_1000_3eb2();
          pcVar26 = local_a + uVar13;
          unaff_SI = (uint **)((int)pcVar26 * 2 + DAT_28d3_2a40);
          unaff_ES = (((iVar17 + ((int)local_a >> 0xf) + (uint)CARRY2(uVar13,(uint)local_a)) * 2 |
                      (uint)CARRY2((uint)pcVar26,(uint)pcVar26)) +
                     (uint)CARRY2((int)pcVar26 * 2,DAT_28d3_2a40)) * 0x1000 + DAT_28d3_2a42;
          iVar17 = ((int)local_1e * 10 - (int)*unaff_SI) - local_1c._2_2_;
        }
        uVar13 = 0x1000;
        in_EDX = (uint *)(((long)iVar17 * (long)local_10) % 100);
        pbVar27 = (byte *)(byte *)(((long)iVar17 * (long)local_10) / 100);
        local_6 = (uint *)CONCAT22(local_6._2_2_,pbVar27);
        if ((((0 < (int)ppuVar11) && ((int)ppuVar11 < (int)local_c)) && (0 < (int)pbVar27)) &&
           ((int)pbVar27 < local_e)) {
          uVar13 = 0x23f1;
          FUN_23f1_2046();
        }
      }
      pcVar26 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
      uStack_2c._2_2_ = (undefined2 *)0x4e2;
      uStack_2e = 0xbfd5;
      uStack_2c._0_2_ = uVar13;
      iStack_30 = FUN_1928_5dc0();
      puVar12 = (uint *)in_EDX;
      local_6 = (uint *)CONCAT22(iStack_30,(byte *)local_6);
      iVar17 = 0x20;
      piVar23 = (int *)0x383f;
      do {
        if (*piVar23 == iStack_30) {
                    /* WARNING: Could not recover jumptable at 0x0001bff7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
          puVar12 = (uint *)(*(code *)piVar23[0x20])();
          return puVar12;
        }
        piVar23 = piVar23 + 1;
        iVar17 = iVar17 + -1;
      } while (iVar17 != 0);
      pcVar31 = (char *)0x0;
      if (pcVar26 == (char *)0x0) {
        uStack_2c._2_2_ = (undefined2 *)0x1000;
        uStack_2c._0_2_ = 0xb8da;
        FUN_1928_1906();
        uStack_2c._2_2_ = (undefined2 *)0x1000;
        uStack_2c._0_2_ = 0xb8ee;
        FUN_1928_1906();
        FUN_23f1_1211();
        uStack_2c._2_2_ = (undefined2 *)0xb90c;
        FUN_23f1_1c32();
        puVar16 = (uint *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 0x1b);
        FUN_23f1_1d5c();
        puVar10 = (uint *)FUN_1928_5a33();
        if (local_12 < (uint **)s_NULL_CHECK_28d3_0004) {
          switch(local_12) {
          case (uint **)0x0:
            unaff_SI[6] = local_1e;
            ppuVar2 = unaff_SI + 6;
            *ppuVar2 = (uint *)((uint)*ppuVar2 & 1);
            puVar4 = *ppuVar2;
            unaff_SI[5] = (uint *)ppuVar11;
            unaff_SI[3] = puVar12;
            unaff_SI[2] = puVar16;
            unaff_SI[1] = (uint *)((int)local_12 * 2);
            *unaff_SI = puVar10;
            if (puVar4 != (uint *)0x0) {
              FUN_1000_1f84();
            }
            return puVar10;
          case (uint **)0x1:
            (&stack0x0644)[(int)ppuVar11] = (&stack0x0644)[(int)ppuVar11] | (byte)puVar16;
            return puVar10;
          case (uint **)0x2:
            if (((uint)puVar10 | (uint)puVar12) != 0) {
              uStack_2c._2_2_ = (undefined2 *)0x1000;
              uStack_2c._0_2_ = 0x56db;
              FUN_1000_58d4();
              ((uint **)param_1)[2] = param_5;
            }
            break;
          case (uint **)0x3:
            bVar8 = in(0x30a);
            out(0x30a,bVar8 | 1);
            uStack_2c._2_2_ = (undefined2 *)0xcd24;
            puVar12 = (uint *)FUN_1928_08a3();
            DAT_28d3_29d8 = 0xff;
            return puVar12;
          }
          puVar10 = (uint *)FUN_1000_5c87();
          goto code_r0x000156ef;
        }
        iVar17 = DAT_28d3_29ac;
        if (DAT_28d3_29ac < DAT_28d3_29aa) {
          iVar17 = DAT_28d3_29aa;
        }
        if (DAT_28d3_29ae < iVar17) {
          local_10 = (int)(0xdac / (long)iVar17);
        }
        else {
          local_10 = (int)(0xdac / (long)DAT_28d3_29ae);
        }
        local_c = (char *)((local_10 * (int)local_1c) / 10);
        local_e = (local_10 * (int)local_1e) / 10;
        in_EDX = (uint *)((long)(local_10 * (int)local_1e) % 10 & 0xffff);
        if (local_1c._6_2_ != 0) {
          uStack_2c._2_2_ = (undefined2 *)0xbae0;
          FUN_23f1_119e();
        }
        uStack_2c._2_2_ = (undefined2 *)0xbaf1;
        FUN_23f1_1f2a();
        pcVar31 = (char *)0x0;
        FUN_23f1_1d5c();
        FUN_23f1_1211();
        uStack_2e = 0x23f1;
        iStack_30 = 0xbb22;
        FUN_1000_04ab();
        uStack_2c._2_2_ = (undefined2 *)0xbb34;
        FUN_23f1_1c32();
        uStack_2c._2_2_ = (undefined2 *)0xbb46;
        FUN_23f1_1f2a();
        uStack_2c._2_2_ = (undefined2 *)0xbb58;
        FUN_23f1_1c32();
        uStack_2c._2_2_ = (undefined2 *)0xbb69;
        FUN_23f1_1f2a();
        uStack_2e = 0x23f1;
        iStack_30 = 0xbb90;
        FUN_1000_04ab();
        uStack_2c._2_2_ = (undefined2 *)0xbba3;
        FUN_23f1_1c32();
        uStack_2c._2_2_ = (undefined2 *)0xbbb5;
        FUN_23f1_1f2a();
        uStack_2e = 0x23f1;
        iStack_30 = 0xbbdc;
        FUN_1000_04ab();
        uStack_2c._2_2_ = (undefined2 *)0xbbf0;
        FUN_23f1_1c32();
        uStack_2c._2_2_ = (undefined2 *)0xbc03;
        FUN_23f1_1f2a();
        uStack_2e = 0x23f1;
        iStack_30 = -0x43d6;
        FUN_1000_04ab();
        uStack_2c._2_2_ = (undefined2 *)0xbc3e;
        FUN_23f1_1c32();
        uStack_2c._2_2_ = (undefined2 *)0xbc51;
        FUN_23f1_1f2a();
      }
      puVar12 = (uint *)in_EDX;
      if (local_12 < (uint **)s_NULL_CHECK_28d3_0004) break;
      if (DAT_28d3_2978 != 0) goto code_r0x0001bc9c;
    }
    bVar30 = CARRY2((uint)local_12,(uint)local_12);
    puVar10 = (uint *)((int)local_12 * 2);
    switch(local_12) {
    case (uint **)0x0:
code_r0x000156ef:
      puVar3 = puVar10;
      uVar13 = *puVar3;
      *puVar3 = *puVar3 + 1;
      puVar10[1] = puVar10[1] + (uint)(0xfffe < uVar13);
      return (uint *)(uint **)param_1;
    case (uint **)0x1:
      uStack_2c._2_2_ = (undefined2 *)0x1000;
      uStack_2c._0_2_ = 0x1e68;
      puVar12 = (uint *)FUN_1000_3492();
      return puVar12;
    case (uint **)0x2:
      local_6._2_2_ = puVar10[0x1157];
      local_6._0_2_ = (byte *)puVar10[0x1156];
      if ((((uint)(uint **)param_1 | param_1._2_2_) != 0) && (*(char *)param_1 != '\0')) {
        uStack_2c._2_2_ = (undefined2 *)0x2feb;
        FUN_1000_2afc();
        uStack_2c._2_2_ = (undefined2 *)0x2ffd;
        FUN_1000_2afc();
      }
      uStack_2c._2_2_ = (undefined2 *)0x3010;
      FUN_1000_2afc();
      uStack_2c._2_2_ = (undefined2 *)0x3022;
      puVar12 = (uint *)FUN_1000_2afc();
      return puVar12;
    case (uint **)0x3:
switchD_1000_bc5e_caseD_3:
      cVar9 = (&stack0xfffe)[(int)ppuVar11];
      pcVar21 = (char *)((int)puVar10 + (int)ppuVar11 + 6);
      *pcVar21 = *pcVar21 >> 0x17;
      pcVar31 = (char *)CONCAT11(3,(char)pcVar31 + cVar9 + bVar30 +
                                   *(char *)((int)puVar10 + (int)ppuVar11 + -0x7ba));
      pcVar26 = local_c;
      pcVar19 = local_a;
    }
LAB_1000_214e:
    local_a = pcVar19;
    local_c = pcVar26;
    ppuVar2 = unaff_SI;
    unaff_SI = (uint **)((int)unaff_SI + 1);
    bVar8 = *(byte *)ppuVar2;
LAB_1000_2150:
    ppuVar11 = param_1_00;
    uVar29 = param_1._2_2_;
    if (0x5f < (byte)(bVar8 - 0x20)) goto LAB_1000_2505;
    bVar5 = *(byte *)((byte)(bVar8 - 0x20) + 0x224b);
    puVar10 = (uint *)((uint)bVar5 * 2);
    uVar15 = SUB21(pcVar31,0);
    bVar18 = (byte)((uint)pcVar31 >> 8);
    uVar22 = SUB21(puVar10,0);
    pcVar28 = unaff_SS;
    pcVar26 = local_c;
    pcVar19 = local_a;
    switch(bVar5) {
    case 0:
      goto switchD_1000_216c_caseD_0;
    case 1:
      if (bVar18 != 0) goto LAB_1000_2505;
      local_6 = (uint *)((ulong)local_6 | 0x10000);
      goto LAB_1000_214e;
    case 2:
      pcVar26 = *(char **)param_1_00;
      param_1_00 = (uint **)((int)param_1_00 + 2);
      if (1 < bVar18) {
        if (bVar18 != 4) goto LAB_1000_2505;
        pcVar31 = (char *)CONCAT11(5,uVar15);
        goto LAB_1000_214e;
      }
      local_a = pcVar26;
      if ((int)pcVar26 < 0) {
        local_a = (char *)-(int)pcVar26;
        local_6 = (uint *)((ulong)local_6 | 0x20000);
      }
      bVar30 = false;
      goto switchD_1000_bc5e_caseD_3;
    case 3:
      if (bVar18 != 0) goto LAB_1000_2505;
      local_6 = (uint *)((ulong)local_6 | 0x20000);
      goto LAB_1000_214e;
    case 4:
      if (3 < bVar18) goto LAB_1000_2505;
      pcVar31 = (char *)CONCAT11(4,uVar15);
      pcVar26 = local_c + 1;
      goto LAB_1000_214e;
    case 5:
      goto switchD_1000_216c_caseD_5;
    case 6:
      local_6 = (uint *)((ulong)local_6 | 0x100000);
      break;
    case 7:
      local_6 = (uint *)((ulong)local_6 | 0x1000000);
    case 8:
      local_6 = (uint *)((ulong)local_6 & 0xffefffff);
      break;
    case 9:
      if (bVar18 == 0) {
        if (((ulong)local_6 & 0x20000) == 0) {
          local_6 = (uint *)((ulong)local_6 | 0x80000);
          pcVar31 = (char *)CONCAT11(1,uVar15);
        }
        goto LAB_1000_214e;
      }
switchD_1000_216c_caseD_5:
      pcVar28 = (char *)(int)(char)(bVar8 - 0x30);
      if (bVar18 < 3) {
        pcVar31 = (char *)CONCAT11(2,uVar15);
        LOCK();
        UNLOCK();
        pcVar19 = pcVar28;
        if (-1 < (int)local_a) {
          pcVar19 = pcVar28 + (int)local_a * 10;
        }
      }
      else {
        if (bVar18 != 4) goto LAB_1000_2505;
        LOCK();
        UNLOCK();
        pcVar26 = pcVar28;
        if (local_c != (char *)0x0) {
          pcVar26 = pcVar28 + (int)local_c * 10;
        }
      }
      goto LAB_1000_214e;
    case 10:
      uVar13 = CONCAT11(10,uVar22);
      local_8 = CONCAT11(bVar8,1);
      pcVar26 = *(char **)param_1_00;
      pcVar19 = (char *)((int)pcVar26 >> 0xf);
      goto LAB_1000_227d;
    case 0xb:
      uVar13 = CONCAT11(8,uVar22);
      goto LAB_1000_2259;
    case 0xc:
      uVar13 = CONCAT11(10,uVar22);
      goto LAB_1000_2259;
    case 0xd:
      uVar13 = CONCAT11(0x10,bVar8 - 0x17);
LAB_1000_2259:
      local_e._1_1_ = 0;
      pcVar19 = (char *)0x0;
      local_8 = (uint)bVar8 << 8;
      pcVar26 = *(char **)param_1_00;
LAB_1000_227d:
      ppuVar11 = (uint **)((int)param_1_00 + 2);
      param_1 = (uint **)CONCAT22(param_1._2_2_,unaff_SI);
      if (((ulong)local_6 & 0x100000) != 0) {
        pcVar19 = *(char **)ppuVar11;
        ppuVar11 = param_1_00 + 1;
      }
      param_1_00 = ppuVar11;
      puVar12 = auStack_47;
      if ((pcVar26 == (char *)0x0) && (pcVar19 == (char *)0x0)) {
        if (local_c != (char *)0x0) goto LAB_1000_22ae;
        auStack_47[0] = auStack_47[0] & 0xff00;
      }
      else {
        local_6 = (uint *)((ulong)local_6 | 0x40000);
LAB_1000_22ae:
        uStack_2c._2_2_ = (undefined2 *)(local_8 & 0xff);
        uStack_2e = 0x22be;
        uStack_2c._0_2_ = uVar13;
        FUN_1000_3faf();
      }
      pcVar26 = local_c;
      if ((int)local_c < 0) {
LAB_1000_23be:
        if ((((ulong)local_6 & 0x80000) != 0) && (pcVar26 = local_a, 0 < (int)local_a))
        goto LAB_1000_23cc;
      }
      else {
LAB_1000_23cc:
        FUN_1000_20b5();
        if (*(byte *)puVar12 == 0x2d) {
          pcVar31 = pcVar31 + -1;
        }
        if ((int)pcVar26 - (int)pcVar31 != 0 && (int)pcVar31 <= (int)pcVar26) {
          local_10 = (int)pcVar26 - (int)pcVar31;
        }
      }
      if (*(byte *)puVar12 == 0x2d) {
LAB_1000_23ee:
        if ((0 < local_10) && (pcVar31 = local_c, (int)local_c < 0)) {
          local_10 = local_10 + -1;
        }
      }
      else if (local_e._1_1_ != 0) {
        puVar12 = (uint *)((int)puVar12 + -1);
        *(byte *)puVar12 = local_e._1_1_;
        goto LAB_1000_23ee;
      }
      FUN_1000_20b5();
LAB_1000_2401:
      pbVar27 = (byte *)local_6;
      if ((local_6._2_2_ & 5) == 5) {
        if (local_8._1_1_ == 'o') {
          if (local_10 < 1) {
            local_10 = 1;
          }
        }
        else if ((local_8._1_1_ == 'x') || (local_8._1_1_ == 'X')) {
          local_6 = (uint *)((ulong)local_6 | 0x400000);
          local_a = local_a + -2;
          bVar30 = local_10 < 2;
          local_10 = local_10 + -2;
          if (bVar30) {
            local_10 = 0;
          }
        }
      }
      pcVar31 = pcVar31 + local_10;
      if (((ulong)local_6 & 0x20000) == 0) {
        for (; (int)pcVar31 < (int)local_a; local_a = local_a + -1) {
          FUN_1000_20c2();
        }
      }
      if (((ulong)local_6 & 0x400000) != 0) {
        FUN_1000_20c2();
        FUN_1000_20c2();
      }
      if (0 < local_10) {
        pcVar31 = pcVar31 + -local_10;
        local_a = local_a + -local_10;
        bVar8 = *(byte *)puVar12;
        if (((bVar8 == 0x2d) || (bVar8 == 0x20)) || (bVar8 == 0x2b)) {
          puVar12 = (uint *)((int)puVar12 + 1);
          FUN_1000_20c2();
          pcVar31 = pcVar31 + -1;
          local_a = local_a + -1;
        }
        pcVar24 = (char *)ZEXT24(local_a);
        pcVar21 = (char *)ZEXT24(pcVar31);
        for (; local_10 != 0; local_10 = local_10 + -1) {
          FUN_1000_20c2();
          local_a = (char *)pcVar24;
          pcVar31 = (char *)pcVar21;
        }
      }
      if (pcVar31 != (char *)0x0) {
        pcVar21 = (char *)(ulong)(uint)((int)local_a - (int)pcVar31);
        do {
          puVar3 = puVar12;
          puVar12 = (uint *)((int)puVar12 + 1);
          *pbVar27 = *(byte *)puVar3;
          pbVar27 = pbVar27 + 1;
          cVar7 = local_1c._6_1_;
          cVar9 = local_1c._6_1_ + -1;
          local_1c._0_7_ = CONCAT16(cVar9,(undefined6)local_1c);
          local_1c = (qword)(uint7)local_1c;
          if (cVar9 == '\0' || cVar7 < '\x01') {
            FUN_1000_20cb();
          }
          local_a = (char *)pcVar21;
          pcVar31 = pcVar31 + -1;
        } while (pcVar31 != (char *)0x0);
      }
      if (0 < (int)local_a) {
        do {
          FUN_1000_20c2();
          local_a = local_a + -1;
        } while (local_a != (char *)0x0);
      }
LAB_1000_210b:
      unaff_ES = (int)((ulong)param_1 >> 0x10);
      ppuVar25 = (uint **)param_1;
LAB_1000_210e:
      local_12 = (uint **)((int)ppuVar25 + 1);
      bVar8 = *(byte *)ppuVar25;
      if (bVar8 == 0) goto LAB_1000_250e;
      unaff_SI = local_12;
      if (bVar8 == 0x25) {
        unaff_SI = ppuVar25 + 1;
        bVar8 = *(byte *)local_12;
        if (bVar8 != 0x25) goto code_r0x00012132;
      }
      *pbVar27 = bVar8;
      pbVar27 = pbVar27 + 1;
      cVar7 = local_1c._6_1_;
      cVar9 = local_1c._6_1_ + -1;
      local_1c._0_7_ = CONCAT16(cVar9,(undefined6)local_1c);
      local_1c = (qword)(uint7)local_1c;
      ppuVar25 = unaff_SI;
      if (cVar9 == '\0' || cVar7 < '\x01') {
        FUN_1000_20cb();
      }
      goto LAB_1000_210e;
    case 0xe:
      param_1 = (uint **)CONCAT22(param_1._2_2_,unaff_SI);
      puVar10 = (uint *)&uStack_48;
      ppuVar11 = (uint **)((int)param_1_00 + 2);
      local_8._1_1_ = bVar8;
      if (((ulong)local_6 & 0x200000) != 0) {
        param_1_00 = param_1_00 + 1;
        FUN_1000_2083();
        puVar10 = auStack_47;
        uStack_48 = 0x3a;
        ppuVar11 = param_1_00;
      }
      param_1_00 = ppuVar11;
      FUN_1000_2083();
      *(undefined *)puVar10 = 0;
      local_8 = (uint)local_8._1_1_ << 8;
      local_6 = (uint *)((ulong)local_6 & 0xfffbffff);
      puVar12 = (uint *)&uStack_48;
      pcVar31 = (char *)((int)puVar10 - (int)puVar12);
      goto LAB_1000_23be;
    case 0xf:
      param_1 = (uint **)CONCAT22(param_1._2_2_,unaff_SI);
      local_8 = CONCAT11(bVar8,(undefined)local_8);
      pcVar31 = local_c;
      if ((int)local_c < 0) {
        pcVar31 = (char *)s_NULL_CHECK_28d3_0004 + 2;
      }
      uStack_2c._0_2_ = local_6._2_2_ & 1;
      if (((ulong)local_6 & 0x1000000) == 0) {
        param_1_00 = param_1_00 + 2;
        uStack_2e = 6;
      }
      else {
        uStack_2e = 8;
        param_1_00 = (uint **)((int)param_1_00 + 10);
      }
      iStack_30 = 0x23b9;
      uStack_2c._2_2_ = (undefined2 *)(uint)bVar8;
      thunk_FUN_1000_068f();
      puVar12 = auStack_47;
      goto LAB_1000_23be;
    case 0x10:
      param_1 = (uint **)CONCAT22(param_1._2_2_,unaff_SI);
      local_8 = CONCAT11(bVar8,(undefined)local_8);
      ppuVar1 = param_1_00;
      param_1_00 = (uint **)((int)param_1_00 + 2);
      puVar12 = auStack_47;
      auStack_47[0] = (uint)*(char **)ppuVar1 & 0xff;
      pcVar31 = (char *)((int)(undefined2 *)&DAT_28d3_0000 + 1);
      goto LAB_1000_2401;
    case 0x11:
      param_1 = (uint **)CONCAT22(param_1._2_2_,unaff_SI);
      local_8 = CONCAT11(bVar8,(undefined)local_8);
      if (((ulong)local_6 & 0x200000) == 0) {
                    /* WARNING: Load size is inaccurate */
        puVar12 = *param_1_00;
        param_1_00 = (uint **)((int)param_1_00 + 2);
        pcVar28 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
        puVar10 = puVar12;
      }
      else {
        pcVar28 = (char *)((ulong)*param_1_00 >> 0x10);
        puVar12 = (uint *)*param_1_00;
        param_1_00 = param_1_00 + 1;
        puVar10 = (uint *)((uint)pcVar28 | (uint)puVar12);
      }
      if (puVar10 == (uint *)0x0) {
        pcVar28 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
        puVar12 = (uint *)0x2244;
      }
      FUN_1000_20b5();
      if (local_c < pcVar31) {
        pcVar31 = local_c;
      }
      goto LAB_1000_2401;
    case 0x12:
      param_1 = (uint **)CONCAT22(param_1._2_2_,unaff_SI);
      if (((ulong)local_6 & 0x200000) == 0) {
                    /* WARNING: Load size is inaccurate */
        puVar12 = *param_1_00;
        param_1_00 = (uint **)((int)param_1_00 + 2);
        pcVar26 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
      }
      else {
        pcVar26 = (char *)((ulong)*param_1_00 >> 0x10);
        puVar12 = (uint *)*param_1_00;
        param_1_00 = param_1_00 + 1;
      }
      *puVar12 = (uint)(byte)(0x50 - local_1c._6_1_) + (int)local_14;
      pbVar27 = (byte *)local_6;
      if (((ulong)local_6 & 0x100000) != 0) {
        puVar12[1] = 0;
      }
      goto LAB_1000_210b;
    default:
      goto LAB_1000_2505;
    case 0x16:
      local_6 = (uint *)((ulong)local_6 & 0xffdfffff);
      break;
    case 0x17:
      local_6 = (uint *)((ulong)local_6 | 0x200000);
    }
    pcVar31 = (char *)CONCAT11(5,uVar15);
    goto LAB_1000_214e;
  case 3:
    pcVar6 = (code *)swi(1);
    puVar12 = (uint *)(*pcVar6)();
    return puVar12;
  }
  ppuVar2 = unaff_SI + DAT_28d3_297a + 0x30fd;
  *(byte *)ppuVar2 = *(byte *)ppuVar2 | cVar9 + 0xb9U;
  if (*(byte *)ppuVar2 == 0) {
    uVar14 = 0x902;
    *(undefined2 *)((int)&local_6 + iVar17 + 2) = 0x80;
    *(undefined2 *)((int)&local_6 + iVar17) = 2;
    cVar9 = **(char **)(&param_4 + uVar13);
    (&param_4)[uVar13] = (&param_4)[uVar13] + 1;
    if ((cVar9 == '+') ||
       ((**(char **)(&param_4 + uVar13) == '+' && ((cVar9 == 't' || (cVar9 == 'b')))))) {
      if (cVar9 == '+') {
        cVar9 = **(char **)(&param_4 + uVar13);
      }
      uVar14 = 0x904;
      *(undefined2 *)((int)&local_6 + iVar17 + 2) = 0x180;
      *(undefined2 *)((int)&local_6 + iVar17) = 3;
    }
    if (cVar9 == 't') {
      uVar14 = uVar14 | 0x4000;
    }
    else {
      if (cVar9 == 'b') {
        uVar14 = uVar14 | 0x8000;
      }
      else {
        if ((cVar9 != '+') && (cVar9 != '\0')) goto LAB_1000_2946;
        uVar14 = uVar14 | DAT_28d3_21da & 0xc000;
        if ((DAT_28d3_21da & 0x8000) == 0) goto LAB_1000_295d;
      }
      *(uint *)((int)&local_6 + iVar17) = *(uint *)((int)&local_6 + iVar17) | 0x40;
    }
LAB_1000_295d:
    DAT_28d3_2716 = 0x1000;
    DAT_28d3_2714 = 0x3721;
    **(uint **)((int)&param_1 + iVar17 + 2) = uVar14;
    **(undefined2 **)(&param_1_00 + uVar13) = *(undefined2 *)((int)&local_6 + iVar17 + 2);
    puVar12 = *(uint **)((int)&local_6 + iVar17);
  }
  else {
LAB_1000_2946:
    puVar12 = (uint *)0x0;
  }
  return puVar12;
code_r0x00012132:
  pcVar31 = (char *)0x0;
  local_10 = 0;
  local_6 = (uint *)CONCAT22(0x20,pbVar27);
  local_e = 0;
  local_a = (char *)0xffff;
  local_c = (char *)0xffff;
  goto LAB_1000_2150;
switchD_1000_216c_caseD_0:
  if (bVar18 != 0) {
LAB_1000_2505:
    do {
      FUN_1000_20c2();
      ppuVar2 = local_12;
      local_12 = (uint **)((int)local_12 + 1);
    } while (*(char *)ppuVar2 != '\0');
LAB_1000_250e:
    if (local_1c._6_1_ < 'P') {
      FUN_1000_20cb();
    }
    if (local_1c._4_2_ != 0) {
      local_14 = (uint *)0xffff;
    }
    return local_14;
  }
  if (local_e._1_1_ != 0x2b) {
    local_e = (uint)bVar8 << 8;
  }
  goto LAB_1000_214e;
code_r0x0001bc9c:
  FUN_23f1_1211();
  uStack_2e = 0x23f1;
  iStack_30 = 0xbcd5;
  FUN_1000_04ab();
  uStack_2c._2_2_ = (undefined2 *)0xbce9;
  FUN_23f1_1c32();
  uStack_2c._2_2_ = (undefined2 *)0xbcfc;
  FUN_23f1_1f2a();
  uStack_2e = 0x23f1;
  iStack_30 = 0xbd26;
  FUN_1000_04ab();
  uStack_2c._2_2_ = (undefined2 *)0xbd3a;
  FUN_23f1_1c32();
  uVar29 = 0x23f1;
  uStack_2c._2_2_ = (undefined2 *)0xbd4d;
  FUN_23f1_1f2a();
  goto switchD_1000_dd7c_caseD_1;
}



// Function: FUN_1928_4f92

void __cdecl16far FUN_1928_4f92(int param_1,int param_2,int param_3,int param_4,undefined2 param_5)

{
  if ((((0 < param_1) && (param_1 < param_2)) && (0 < param_3)) && (param_3 < param_4)) {
    FUN_23f1_2046(param_1 + 0xa0,0x1c2 - param_3,param_5);
  }
  return;
}



// Function: FUN_1928_4fc9

undefined2 __cdecl16far FUN_1928_4fc9(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  
  for (iVar3 = 0; iVar3 < param_3; iVar3 = iVar3 + 1) {
    uVar4 = (undefined2)((ulong)param_1 >> 0x10);
    iVar1 = (int)param_1;
    uVar5 = (undefined2)((ulong)param_2 >> 0x10);
    if (*(int *)(iVar1 + iVar3 * 0xc) == 1) {
      puVar2 = (undefined2 *)((int)param_2 + iVar3 * 4);
      FUN_1928_0436(iVar1,uVar4,iVar3,*puVar2,puVar2[1]);
    }
    else if (*(int *)(iVar1 + iVar3 * 0xc) == 3) {
      puVar2 = (undefined2 *)((int)param_2 + iVar3 * 4);
      FUN_1928_06d5(*(undefined2 *)(iVar1 + (iVar3 * 6 + 2) * 2),
                    *(undefined2 *)(iVar1 + (iVar3 * 6 + 3) * 2),0,*puVar2,puVar2[1]);
    }
  }
  return 1;
}



// Function: FUN_1928_505d

void FUN_1928_505d(void)

{
  int iVar1;
  int *piVar2;
  undefined local_16 [16];
  int local_6;
  int local_4;
  
  FUN_1928_0948(0x6e,0xb4,0x19a,400,2,(char *)s_Sorting_28d3_134b,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_1928_4fc9(0x806,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0x7e2,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7,9);
  FUN_23f1_119e();
  FUN_23f1_119e();
  FUN_23f1_1f2a();
  FUN_23f1_1f2a();
  FUN_23f1_1f2a();
  FUN_1928_60ae(local_16);
  FUN_23f1_1d5c(0);
  FUN_23f1_1f2a();
  do {
    FUN_1928_1906(DAT_28d3_29d2,0,0x82,0xd2,2);
    FUN_1928_1906(DAT_28d3_29d2,1,0x82,0xe6,2);
    FUN_1928_1906(DAT_28d3_29d2,2,0x82,0xfa,2);
    FUN_23f1_1d5c(0);
    FUN_23f1_1211(1,0x3b);
    FUN_23f1_1c32();
    FUN_1000_4055();
    FUN_23f1_1f2a();
    FUN_23f1_1c32();
    FUN_1000_4055();
    FUN_23f1_1f2a();
    FUN_1000_40a5(DAT_28d3_2984,local_16);
    FUN_23f1_1f2a();
    local_6 = FUN_1928_5dc0(0x806,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0x7e2,
                            (char *)s_String_reference_out_of_range_28d3_28cc + 7,9,0);
    iVar1 = 10;
    piVar2 = (int *)0x5323;
    do {
      local_4 = local_6;
      if (*piVar2 == local_6) {
                    /* WARNING: Could not recover jumptable at 0x0001e4a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*(code *)piVar2[10])();
        return;
      }
      piVar2 = piVar2 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  } while( true );
}



// Function: FUN_1928_5802

/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

undefined2 __cdecl16far FUN_1928_5802(void)

{
  uint uVar1;
  uint uVar2;
  undefined2 uVar3;
  int iVar4;
  int in_DX;
  int iVar5;
  undefined *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  char **ppcVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined *puVar14;
  char **ppcVar15;
  undefined *puVar16;
  undefined4 *puVar17;
  undefined4 *puVar18;
  char **ppcVar19;
  undefined *puVar20;
  undefined *puVar21;
  undefined *puVar22;
  undefined *puVar23;
  undefined *puVar24;
  char **ppcVar25;
  undefined4 in_ESP;
  undefined4 *puVar26;
  undefined2 unaff_BP;
  undefined2 uVar27;
  undefined2 unaff_SS;
  
  iVar5 = (int)in_ESP;
  uVar3 = (undefined2)((ulong)in_ESP >> 0x10);
  *(undefined2 *)(iVar5 + -2) = unaff_BP;
  if (DAT_28d3_2984 == 0) {
    return 0;
  }
  *(char **)(iVar5 + -0x1a) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  *(undefined2 *)(iVar5 + -0x1c) = 0x2a56;
  *(undefined2 *)(iVar5 + -0x1e) = 0x1da;
  *(undefined2 *)(iVar5 + -0x20) = 0x1cc;
  *(undefined2 *)(iVar5 + -0x22) = 0x1d0;
  *(undefined2 *)(iVar5 + -0x24) = 0xa0;
  *(undefined2 *)(iVar5 + -0x26) = 0x1928;
  uVar27 = 0x23f1;
  puVar6 = (undefined *)(iVar5 + -0x28);
  *(undefined2 *)(iVar5 + -0x28) = 0xeaa5;
  FUN_23f1_2066();
  *(undefined2 *)(puVar6 + 0xe) = 0x1d0;
  *(undefined2 *)(puVar6 + 0xc) = 0xa0;
  *(undefined2 *)(puVar6 + 10) = 1;
  puVar26 = (undefined4 *)(CONCAT22(uVar3,(int)puVar6 + 10) + -4);
  *puVar26 = 0;
  puVar7 = (undefined4 *)puVar26;
  uVar3 = (undefined2)((ulong)puVar26 >> 0x10);
  puVar7[-1] = DAT_28d3_2984;
  *(undefined2 *)((int)puVar7 + -6) = 0x23f1;
  puVar8 = puVar7 + -2;
  *(undefined2 *)(puVar7 + -2) = 0xeabd;
  FUN_1928_5f6b();
  ppcVar9 = (char **)((int)puVar8 + 0x12);
  *(undefined4 *)(iVar5 + -6) = 1;
  while (*(long *)(iVar5 + -6) < DAT_28d3_2984) {
    *(undefined2 *)(iVar5 + -0x18) = *(undefined2 *)(DAT_28d3_2a40 + 4);
    iVar4 = 0;
    *(undefined2 *)((int)ppcVar9 + -2) = uVar27;
    puVar10 = (undefined4 *)((int)ppcVar9 + -4);
    *(undefined2 *)((int)ppcVar9 + -4) = 0xeaf8;
    uVar1 = FUN_1000_3eb2();
    puVar13 = puVar10 + 1;
    uVar2 = uVar1 + 2;
    in_DX = (((iVar4 + (uint)(0xfffd < uVar1)) * 2 | (uint)CARRY2(uVar2,uVar2)) +
            (uint)CARRY2(uVar2 * 2,DAT_28d3_2a40)) * 0x1000 + DAT_28d3_2a42;
    if (*(int *)(uVar2 * 2 + DAT_28d3_2a40) < *(int *)(iVar5 + -0x18)) {
      *puVar10 = *(undefined4 *)(iVar5 + -6);
      puVar26 = (undefined4 *)CONCAT22(uVar3,puVar10) + -1;
      *puVar26 = 0;
      puVar11 = (undefined4 *)puVar26;
      uVar3 = (undefined2)((ulong)puVar26 >> 0x10);
      *(undefined2 *)((int)puVar11 + -2) = 0x1000;
      puVar12 = puVar11 + -1;
      *(undefined2 *)(puVar11 + -1) = 0xeb2a;
      FUN_1928_6bc5();
      puVar13 = (undefined4 *)((int)puVar12 + 0xc);
    }
    *(undefined2 *)((int)puVar13 + -2) = 0x1d0;
    *(undefined2 *)((int)puVar13 + -4) = 0xa0;
    *(undefined2 *)((int)puVar13 + -6) = 0;
    *(undefined4 *)((int)puVar13 + -10) = *(undefined4 *)(iVar5 + -6);
    *(long *)((int)puVar13 + -0xe) = DAT_28d3_2984;
    *(undefined2 *)((int)puVar13 + -0x10) = 0x1000;
    puVar14 = (undefined *)((int)puVar13 + -0x12);
    *(undefined2 *)((int)puVar13 + -0x12) = 0xeb43;
    FUN_1928_5f6b();
    *(undefined2 *)(puVar14 + 0x10) = 0x1000;
    ppcVar15 = (char **)(puVar14 + 0xe);
    *(undefined2 *)(puVar14 + 0xe) = 0xeb4b;
    iVar4 = FUN_1000_1953();
    ppcVar9 = ppcVar15 + 2;
    if (iVar4 != 0) {
      ppcVar15[1] = (char *)0x1000;
      *ppcVar15 = (char *)0xeb54;
      iVar4 = FUN_1000_18df();
      ppcVar9 = ppcVar15 + 2;
      if (iVar4 == 0x1b) {
        ppcVar15[1] = (char *)0x0;
        *ppcVar15 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
        ppcVar15[-1] = (char *)0x2a56;
        ppcVar15[-2] = (char *)0x1d0;
        ppcVar15[-3] = (char *)0xa0;
        ppcVar15[-4] = (char *)0x1000;
        ppcVar15[-5] = (char *)0xeb6a;
        FUN_23f1_1526();
        return 0;
      }
    }
    uVar27 = 0x1000;
    *(long *)(iVar5 + -6) = *(long *)(iVar5 + -6) + 1;
  }
  *(undefined2 *)((int)ppcVar9 + -2) = 0;
  *(char **)((int)ppcVar9 + -4) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  *(undefined2 *)((int)ppcVar9 + -6) = 0x2a56;
  *(undefined2 *)((int)ppcVar9 + -8) = 0x1d0;
  *(undefined2 *)((int)ppcVar9 + -10) = 0xa0;
  *(undefined2 *)((int)ppcVar9 + -0xc) = uVar27;
  uVar27 = 0x23f1;
  puVar16 = (undefined *)((int)ppcVar9 + -0xe);
  *(undefined2 *)((int)ppcVar9 + -0xe) = 0xeb92;
  FUN_23f1_1526();
  *(undefined2 *)(puVar16 + 0xc) = 0x1d0;
  *(undefined2 *)(puVar16 + 10) = 0xa0;
  *(undefined2 *)(puVar16 + 8) = 1;
  *(undefined4 *)((undefined *)CONCAT22(uVar3,puVar16 + 8) + -4) = 0;
  puVar17 = (undefined4 *)((undefined *)CONCAT22(uVar3,puVar16 + 8) + -4);
  puVar17[-1] = DAT_28d3_2984;
  *(undefined2 *)((int)puVar17 + -6) = 0x23f1;
  puVar18 = puVar17 + -2;
  *(undefined2 *)(puVar17 + -2) = 0xebaa;
  FUN_1928_5f6b();
  ppcVar19 = (char **)((int)puVar18 + 0x12);
  *(undefined4 *)(iVar5 + -6) = 0;
  do {
    if (DAT_28d3_2984 + -2 <= *(long *)(iVar5 + -6)) {
      *(undefined2 *)((int)ppcVar19 + -2) = 0;
      *(char **)((int)ppcVar19 + -4) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
      *(undefined2 *)((int)ppcVar19 + -6) = 0x2a56;
      *(undefined2 *)((int)ppcVar19 + -8) = 0x1d0;
      *(undefined2 *)((int)ppcVar19 + -10) = 0xa0;
      *(undefined2 *)((int)ppcVar19 + -0xc) = uVar27;
      *(undefined2 *)((int)ppcVar19 + -0xe) = 0xecab;
      FUN_23f1_1526();
      return 1;
    }
    *(long *)((int)ppcVar19 + -4) = *(long *)(iVar5 + -6) + 1;
    *(undefined4 *)((int)ppcVar19 + -8) = *(undefined4 *)(iVar5 + -6);
    *(undefined2 *)((int)ppcVar19 + -10) = uVar27;
    puVar20 = (undefined *)((int)ppcVar19 + -0xc);
    *(undefined2 *)((int)ppcVar19 + -0xc) = 0xebc9;
    uVar3 = FUN_1928_6a64();
    puVar21 = puVar20 + 0xc;
    *(int *)(iVar5 + -0x14) = in_DX;
    *(undefined2 *)(iVar5 + -0x16) = uVar3;
    *(long *)(iVar5 + -0xe) = *(long *)(iVar5 + -6) + 1;
    *(long *)(iVar5 + -10) = *(long *)(iVar5 + -6) + 2;
    while (*(long *)(iVar5 + -10) < DAT_28d3_2984) {
      *(undefined4 *)(puVar21 + -4) = *(undefined4 *)(iVar5 + -10);
      *(undefined4 *)(puVar21 + -8) = *(undefined4 *)(iVar5 + -6);
      *(undefined2 *)(puVar21 + -10) = uVar27;
      puVar22 = puVar21 + -0xc;
      *(undefined2 *)(puVar21 + -0xc) = 0xebf7;
      uVar3 = FUN_1928_6a64();
      puVar21 = puVar22 + 0xc;
      *(int *)(iVar5 + -0x10) = in_DX;
      *(undefined2 *)(iVar5 + -0x12) = uVar3;
      if (*(long *)(iVar5 + -0x12) < *(long *)(iVar5 + -0x16)) {
        *(undefined4 *)(iVar5 + -0x16) = *(undefined4 *)(iVar5 + -0x12);
        *(undefined4 *)(iVar5 + -0xe) = *(undefined4 *)(iVar5 + -10);
      }
      *(long *)(iVar5 + -10) = *(long *)(iVar5 + -10) + 1;
    }
    *(long *)(puVar21 + -4) = *(long *)(iVar5 + -6) + 1;
    *(undefined4 *)(puVar21 + -8) = *(undefined4 *)(iVar5 + -0xe);
    *(undefined2 *)(puVar21 + -10) = uVar27;
    puVar23 = puVar21 + -0xc;
    *(undefined2 *)(puVar21 + -0xc) = 0xec3a;
    FUN_1928_6bc5();
    *(undefined2 *)(puVar23 + 10) = 0x1d0;
    *(undefined2 *)(puVar23 + 8) = 0xa0;
    *(undefined2 *)(puVar23 + 6) = 0;
    *(undefined4 *)(puVar23 + 2) = *(undefined4 *)(iVar5 + -6);
    *(long *)(puVar23 + -2) = DAT_28d3_2984 + -2;
    *(undefined2 *)(puVar23 + -4) = uVar27;
    puVar24 = puVar23 + -6;
    *(undefined2 *)(puVar23 + -6) = 0xec58;
    FUN_1928_5f6b();
    *(undefined2 *)(puVar24 + 0x10) = uVar27;
    ppcVar25 = (char **)(puVar24 + 0xe);
    *(undefined2 *)(puVar24 + 0xe) = 0xec60;
    iVar4 = FUN_1000_1953();
    ppcVar19 = ppcVar25 + 2;
    if (iVar4 != 0) {
      ppcVar25[1] = (char *)0x1000;
      *ppcVar25 = (char *)0xec69;
      iVar4 = FUN_1000_18df();
      ppcVar19 = ppcVar25 + 2;
      if (iVar4 == 0x1b) {
        ppcVar25[1] = (char *)0x0;
        *ppcVar25 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
        ppcVar25[-1] = (char *)0x2a56;
        ppcVar25[-2] = (char *)0x1d0;
        ppcVar25[-3] = (char *)0xa0;
        ppcVar25[-4] = (char *)0x1000;
        ppcVar25[-5] = (char *)0xec7f;
        FUN_23f1_1526();
        return 0;
      }
    }
    uVar27 = 0x1000;
    *(long *)(iVar5 + -6) = *(long *)(iVar5 + -6) + 1;
  } while( true );
}



// Function: FUN_1928_5a33

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 __cdecl16far FUN_1928_5a33(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  long lVar4;
  
  DAT_28d3_4fd6 = *_DAT_28d3_2a40;
  DAT_28d3_4fda = DAT_28d3_2a40[1];
  DAT_28d3_4fde = DAT_28d3_2a40[2];
  DAT_28d3_4fd8 = DAT_28d3_4fd6;
  DAT_28d3_4fdc = DAT_28d3_4fda;
  DAT_28d3_4fe0 = DAT_28d3_4fde;
  for (lVar4 = 1; lVar4 < DAT_28d3_2984; lVar4 = lVar4 + 1) {
    iVar3 = 0;
    uVar1 = FUN_1000_3eb2();
    if (*(int *)(uVar1 + (int)DAT_28d3_2a40) < DAT_28d3_4fd6) {
      iVar3 = 0;
      uVar1 = FUN_1000_3eb2();
      DAT_28d3_4fd6 = *(int *)(uVar1 + (int)DAT_28d3_2a40);
    }
    iVar3 = 0;
    uVar1 = FUN_1000_3eb2();
    if (DAT_28d3_4fd8 < *(int *)(uVar1 + (int)DAT_28d3_2a40)) {
      iVar3 = 0;
      uVar1 = FUN_1000_3eb2();
      DAT_28d3_4fd8 = *(int *)(uVar1 + (int)DAT_28d3_2a40);
    }
    iVar3 = 0;
    uVar1 = FUN_1000_3eb2();
    uVar2 = uVar1 + 1;
    if (DAT_28d3_2a40[uVar2] < DAT_28d3_4fda) {
      iVar3 = 0;
      uVar1 = FUN_1000_3eb2();
      uVar2 = uVar1 + 1;
      DAT_28d3_4fda = DAT_28d3_2a40[uVar2];
    }
    iVar3 = 0;
    uVar1 = FUN_1000_3eb2();
    uVar2 = uVar1 + 1;
    if (DAT_28d3_4fdc < DAT_28d3_2a40[uVar2]) {
      iVar3 = 0;
      uVar1 = FUN_1000_3eb2();
      uVar2 = uVar1 + 1;
      DAT_28d3_4fdc = DAT_28d3_2a40[uVar2];
    }
    iVar3 = 0;
    uVar1 = FUN_1000_3eb2();
    uVar2 = uVar1 + 2;
    if (DAT_28d3_2a40[uVar2] < DAT_28d3_4fde) {
      iVar3 = 0;
      uVar1 = FUN_1000_3eb2();
      uVar2 = uVar1 + 2;
      DAT_28d3_4fde = DAT_28d3_2a40[uVar2];
    }
    iVar3 = 0;
    uVar1 = FUN_1000_3eb2();
    uVar2 = uVar1 + 2;
    if (DAT_28d3_4fe0 < DAT_28d3_2a40[uVar2]) {
      iVar3 = 0;
      uVar1 = FUN_1000_3eb2();
      uVar2 = uVar1 + 2;
      DAT_28d3_4fe0 = DAT_28d3_2a40[uVar2];
    }
  }
  DAT_28d3_4fde = FUN_1000_0f76(lVar4,DAT_28d3_4fde);
  DAT_28d3_4fe0 = FUN_1000_0f76(lVar4,DAT_28d3_4fe0);
  if ((((9 < DAT_28d3_2968 + DAT_28d3_4fd6) && (DAT_28d3_2968 + DAT_28d3_4fd8 < 0x5bcd)) &&
      (9 < DAT_28d3_296a + DAT_28d3_4fda)) &&
     (((DAT_28d3_296a + DAT_28d3_4fdc < 0x5bcd && (9 < DAT_28d3_296c + DAT_28d3_4fde)) &&
      (DAT_28d3_296c + DAT_28d3_4fe0 < 0x2ee1)))) {
    if (((-1 < DAT_28d3_4fd6) && (DAT_28d3_4fd8 <= DAT_28d3_29aa * 10)) &&
       ((-1 < DAT_28d3_4fda &&
        (((DAT_28d3_4fdc <= DAT_28d3_29ac * 10 && (-1 < DAT_28d3_4fde)) &&
         (DAT_28d3_4fe0 <= DAT_28d3_29ae * 10)))))) {
      return 1;
    }
    return 0xffff;
  }
  return 0;
}



// Function: FUN_1928_5dc0

int __cdecl16far FUN_1928_5dc0(undefined4 param_1,undefined4 param_3,int param_4,undefined2 param_5)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar6;
  undefined2 uVar7;
  int iVar5;
  undefined2 uVar8;
  
  DAT_28d3_29da = 0;
  do {
    while( true ) {
      iVar2 = FUN_23c2_012f(param_5);
      iVar4 = (int)param_1;
      uVar7 = (undefined2)((ulong)param_1 >> 0x10);
      iVar5 = (int)param_3;
      uVar8 = (undefined2)((ulong)param_3 >> 0x10);
      if (iVar2 == 0) break;
      if (iVar2 != 1) {
        DAT_28d3_29da = iVar2;
        return 0xff;
      }
      for (iVar2 = 0; iVar2 < param_4; iVar2 = iVar2 + 1) {
        iVar3 = FUN_1928_0715(iVar4,uVar7,iVar2);
        if (iVar3 != 0) {
          if (*(int *)(iVar4 + iVar2 * 0xc) == 1) {
            puVar6 = (undefined2 *)(iVar5 + DAT_28d3_29d8 * 4);
            FUN_1928_0436(iVar4,uVar7,DAT_28d3_29d8,*puVar6,puVar6[1]);
          }
          DAT_28d3_29d8 = 0xff;
          if (*(int *)(iVar4 + (iVar2 * 6 + 1) * 2) == 1) {
            DAT_28d3_29d8 = 0xff;
            return iVar2;
          }
        }
      }
    }
    bVar1 = false;
    if ((DAT_28d3_29d8 == 0xff) || (iVar2 = FUN_1928_0715(iVar4,uVar7,DAT_28d3_29d8), iVar2 == 0)) {
      for (iVar2 = 0; iVar2 < param_4; iVar2 = iVar2 + 1) {
        iVar3 = FUN_1928_0715(iVar4,uVar7,iVar2);
        if (iVar3 != 0) {
          if (*(int *)(iVar4 + iVar2 * 0xc) == 1) {
            puVar6 = (undefined2 *)(iVar5 + iVar2 * 4);
            FUN_1928_05bb(iVar4,uVar7,iVar2,*puVar6,puVar6[1]);
          }
          if (*(int *)(iVar4 + (iVar2 * 6 + 1) * 2) == 0) {
            DAT_28d3_29d8 = iVar2;
            return iVar2;
          }
          bVar1 = true;
          DAT_28d3_29d8 = iVar2;
        }
      }
    }
    else {
      if (*(int *)(iVar4 + (DAT_28d3_29d8 * 6 + 1) * 2) == 0) {
        return DAT_28d3_29d8;
      }
      if (*(int *)(iVar4 + (DAT_28d3_29d8 * 6 + 1) * 2) == 1) {
        bVar1 = true;
      }
    }
    if ((!bVar1) && (DAT_28d3_29d8 != 0xff)) {
      if (*(int *)(iVar4 + DAT_28d3_29d8 * 0xc) == 1) {
        puVar6 = (undefined2 *)(iVar5 + DAT_28d3_29d8 * 4);
        FUN_1928_0436(iVar4,uVar7,DAT_28d3_29d8,*puVar6,puVar6[1]);
      }
      DAT_28d3_29d8 = 0xff;
    }
  } while( true );
}



// Function: FUN_1928_5f6b

void __cdecl16far FUN_1928_5f6b(long param_1,long param_2,int param_3,int param_4,int param_5)

{
  undefined2 uVar1;
  long lVar2;
  uint uVar3;
  undefined2 uVar4;
  ulong uVar5;
  undefined local_a [4];
  uint local_6;
  uint local_4;
  
  lVar2 = (param_2 + 1) * 100;
  uVar5 = lVar2 % param_1;
  local_6 = (uint)(lVar2 / param_1);
  local_4 = local_6 >> 1;
  if (param_3 != 0) {
    DAT_28d3_4fe4 = 0;
    DAT_28d3_4fe6 = 0xffff;
    FUN_23f1_1211(1,7);
    FUN_23f1_1c32(param_4,param_5,param_4 + 0xfe,param_5 + 10);
    FUN_23f1_2066(param_4 + 0x109,param_5 + 2,param_4 + 0x121,param_5 + 10,0x4996,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7);
    FUN_23f1_1d5c(0xc);
    FUN_23f1_1f2a(param_4 + 0x122,param_5 + 2,0x1369,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  uVar4 = (undefined2)uVar5;
  if ((DAT_28d3_4fe4 != local_4) && (DAT_28d3_4fe4 = local_4, local_4 != 0)) {
    FUN_23f1_1211(1,1);
    local_4 = 0;
    while( true ) {
      uVar4 = (undefined2)uVar5;
      if (DAT_28d3_4fe4 <= local_4) break;
      uVar3 = local_4 * 5;
      uVar5 = (ulong)uVar3;
      FUN_23f1_1c32(param_4 + 3 + uVar3,param_5 + 2,param_4 + 6 + uVar3,param_5 + 8);
      local_4 = local_4 + 1;
    }
  }
  if (DAT_28d3_4fe6 != local_6) {
    DAT_28d3_4fe6 = local_6;
    FUN_23f1_1d5c(0xc);
    FUN_23f1_1526(param_4 + 0x109,param_5 + 2,0x4996,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7,0);
    uVar1 = FUN_1000_4055(local_6,local_a);
    FUN_23f1_1f2a(param_4 + 0x109,param_5 + 2,uVar1,uVar4);
  }
  return;
}



// Function: FUN_1928_60ae

/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

void __cdecl16far FUN_1928_60ae(void)

{
  ulong uVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined *puVar6;
  undefined *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined *puVar14;
  undefined2 *puVar15;
  undefined4 in_ESP;
  undefined4 *puVar16;
  undefined2 unaff_BP;
  undefined2 uVar17;
  undefined2 unaff_SS;
  int iVar7;
  
  uVar17 = 0x1928;
  iVar7 = (int)in_ESP;
  uVar2 = (undefined2)((ulong)in_ESP >> 0x10);
  *(undefined2 *)(iVar7 + -2) = unaff_BP;
  puVar6 = (undefined *)(iVar7 + -0x1e);
  *(undefined4 *)(iVar7 + -0xe) = 0;
  if (DAT_28d3_2984 != 0) {
    *(char **)(iVar7 + -0x20) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    *(undefined2 *)(iVar7 + -0x22) = 0x2a56;
    *(undefined2 *)(iVar7 + -0x24) = 0x1da;
    *(undefined2 *)(iVar7 + -0x26) = 0x1cc;
    *(undefined2 *)(iVar7 + -0x28) = 0x1d0;
    *(undefined2 *)(iVar7 + -0x2a) = 0xa0;
    *(undefined2 *)(iVar7 + -0x2c) = 0x1928;
    uVar17 = 0x23f1;
    puVar8 = (undefined *)(iVar7 + -0x2e);
    *(undefined2 *)(iVar7 + -0x2e) = 0xf359;
    FUN_23f1_2066();
    *(undefined2 *)(puVar8 + 0xe) = 0x1d0;
    *(undefined2 *)(puVar8 + 0xc) = 0xa0;
    *(undefined2 *)(puVar8 + 10) = 1;
    puVar16 = (undefined4 *)(CONCAT22(uVar2,(int)puVar8 + 10) + -4);
    *puVar16 = 0;
    puVar9 = (undefined4 *)puVar16;
    puVar9[-1] = DAT_28d3_2984;
    *(undefined2 *)((int)puVar9 + -6) = 0x23f1;
    puVar10 = puVar9 + -2;
    *(undefined2 *)(puVar9 + -2) = 0xf370;
    FUN_1928_5f6b();
    puVar11 = (undefined *)((int)puVar10 + 0x12);
    *(undefined4 *)(iVar7 + -6) = 0;
    while (*(long *)(iVar7 + -6) < DAT_28d3_2984 + -1) {
      uVar5 = *(uint *)(iVar7 + -6) + 3;
      uVar3 = *(uint *)(iVar7 + -6);
      *(int *)(iVar7 + -0x1a) =
           *(int *)(uVar5 * 2 + DAT_28d3_2a40) - *(int *)(uVar3 * 2 + DAT_28d3_2a40);
      uVar3 = (int)*(uint *)(iVar7 + -0x1a) >> 0xf;
      *(int *)(iVar7 + -0x10) = (*(uint *)(iVar7 + -0x1a) ^ uVar3) - uVar3;
      uVar3 = *(uint *)(iVar7 + -6) + 4;
      uVar5 = *(uint *)(iVar7 + -6) + 1;
      *(int *)(iVar7 + -0x1c) =
           *(int *)(uVar3 * 2 + DAT_28d3_2a40) - *(int *)(uVar5 * 2 + DAT_28d3_2a40);
      uVar3 = (int)*(uint *)(iVar7 + -0x1c) >> 0xf;
      *(int *)(iVar7 + -0x12) = (*(uint *)(iVar7 + -0x1c) ^ uVar3) - uVar3;
      uVar3 = *(uint *)(iVar7 + -6) + 5;
      uVar5 = *(uint *)(iVar7 + -6) + 2;
      *(int *)(iVar7 + -0x1e) =
           *(int *)(uVar3 * 2 + DAT_28d3_2a40) - *(int *)(uVar5 * 2 + DAT_28d3_2a40);
      uVar3 = (int)*(uint *)(iVar7 + -0x1e) >> 0xf;
      *(int *)(iVar7 + -0x14) = (*(uint *)(iVar7 + -0x1e) ^ uVar3) - uVar3;
      *(undefined2 *)(puVar11 + -2) = *(undefined2 *)(iVar7 + -0x14);
      *(undefined2 *)(puVar11 + -4) = *(undefined2 *)(iVar7 + -0x12);
      *(undefined2 *)(puVar11 + -6) = *(undefined2 *)(iVar7 + -0x10);
      *(undefined2 *)(puVar11 + -8) = uVar17;
      uVar17 = 0x215c;
      puVar12 = (undefined4 *)(puVar11 + -10);
      *(undefined2 *)(puVar11 + -10) = 0xf48e;
      iVar4 = FUN_215c_0b84();
      *(long *)(iVar7 + -10) = (long)iVar4;
      *(long *)(iVar7 + -0xe) =
           (long)DAT_28d3_2988 * *(long *)(iVar7 + -10) + *(long *)(iVar7 + -0xe);
      *(undefined2 *)(puVar12 + 2) = 0x1d0;
      *(undefined2 *)((int)puVar12 + 6) = 0xa0;
      *(undefined2 *)(puVar12 + 1) = 0;
      *puVar12 = *(undefined4 *)(iVar7 + -6);
      puVar12[-1] = DAT_28d3_2984;
      *(undefined2 *)((int)puVar12 + -6) = 0x215c;
      puVar13 = puVar12 + -2;
      *(undefined2 *)(puVar12 + -2) = 0xf4bf;
      FUN_1928_5f6b();
      puVar11 = (undefined *)((int)puVar13 + 0x12);
      *(long *)(iVar7 + -6) = *(long *)(iVar7 + -6) + 1;
    }
    *(undefined2 *)(puVar11 + -2) = 0;
    *(char **)(puVar11 + -4) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    *(undefined2 *)(puVar11 + -6) = 0x2a56;
    *(undefined2 *)(puVar11 + -8) = 0x1d0;
    *(undefined2 *)(puVar11 + -10) = 0xa0;
    *(undefined2 *)(puVar11 + -0xc) = uVar17;
    uVar17 = 0x23f1;
    puVar14 = puVar11 + -0xe;
    *(undefined2 *)(puVar11 + -0xe) = 0xf4e5;
    FUN_23f1_1526();
    puVar6 = puVar14 + 0xe;
    *(long *)(iVar7 + -0xe) = *(long *)(iVar7 + -0xe) / 1000;
  }
  *(char **)(puVar6 + -2) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  *(char **)(puVar6 + -4) = (char *)s_Time__28d3_136b;
  *(undefined2 *)(puVar6 + -6) = *(undefined2 *)(iVar7 + 6);
  *(undefined2 *)(puVar6 + -8) = *(undefined2 *)(iVar7 + 4);
  *(undefined2 *)(puVar6 + -10) = uVar17;
  puVar15 = (undefined2 *)(puVar6 + -0xc);
  *(undefined2 *)(puVar6 + -0xc) = 0xf50a;
  FUN_1000_1bec();
  puVar15[5] = 10;
  puVar15[4] = unaff_SS;
  puVar15[3] = iVar7 + -0x18;
  iVar4 = *(int *)(iVar7 + -0xe) % 0xe10;
  puVar15[2] = *(int *)(iVar7 + -0xe) / 0xe10;
  puVar15[1] = 0x1000;
  *puVar15 = 0xf523;
  uVar2 = FUN_1000_4055();
  puVar15[5] = iVar4;
  puVar15[4] = uVar2;
  puVar15[3] = *(undefined2 *)(iVar7 + 6);
  puVar15[2] = *(undefined2 *)(iVar7 + 4);
  puVar15[1] = 0x1000;
  *puVar15 = 0xf533;
  FUN_1000_1b7d();
  puVar15[5] = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  puVar15[4] = 0x1372;
  puVar15[3] = *(undefined2 *)(iVar7 + 6);
  puVar15[2] = *(undefined2 *)(iVar7 + 4);
  puVar15[1] = 0x1000;
  *puVar15 = 0xf545;
  FUN_1000_1b7d();
  puVar15[5] = 10;
  puVar15[4] = unaff_SS;
  puVar15[3] = iVar7 + -0x18;
  uVar1 = (ulong)(uint)((int)(*(long *)(iVar7 + -0xe) % 0xe10) >> 0xf) << 0x10 |
          *(long *)(iVar7 + -0xe) % 0xe10 & 0xffffU;
  uVar17 = (undefined2)((long)uVar1 % 0x3c);
  puVar15[2] = (int)((long)uVar1 / 0x3c);
  puVar15[1] = 0x1000;
  *puVar15 = 0xf56d;
  uVar2 = FUN_1000_4055();
  puVar15[5] = uVar17;
  puVar15[4] = uVar2;
  puVar15[3] = *(undefined2 *)(iVar7 + 6);
  puVar15[2] = *(undefined2 *)(iVar7 + 4);
  puVar15[1] = 0x1000;
  *puVar15 = 0xf57d;
  FUN_1000_1b7d();
  puVar15[5] = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  puVar15[4] = 0x1374;
  puVar15[3] = *(undefined2 *)(iVar7 + 6);
  puVar15[2] = *(undefined2 *)(iVar7 + 4);
  puVar15[1] = 0x1000;
  *puVar15 = 0xf58f;
  FUN_1000_1b7d();
  puVar15[5] = 10;
  puVar15[4] = unaff_SS;
  puVar15[3] = iVar7 + -0x18;
  uVar17 = (undefined2)
           ((long)((ulong)(uint)((int)(*(long *)(iVar7 + -0xe) % 0xe10) >> 0xf) << 0x10 |
                  *(long *)(iVar7 + -0xe) % 0xe10 & 0xffffU) % 0x3c);
  puVar15[2] = uVar17;
  puVar15[1] = 0x1000;
  *puVar15 = 0xf5b7;
  uVar2 = FUN_1000_4055();
  puVar15[5] = uVar17;
  puVar15[4] = uVar2;
  puVar15[3] = *(undefined2 *)(iVar7 + 6);
  puVar15[2] = *(undefined2 *)(iVar7 + 4);
  puVar15[1] = 0x1000;
  *puVar15 = 0xf5c7;
  FUN_1000_1b7d();
  return;
}



// Function: FUN_1928_634c

void FUN_1928_634c(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined local_a [8];
  
  FUN_1928_0948(0x6e,0xb4,0x19a,400,2,(char *)s_Dimensions_Modification_28d3_1376,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_1928_4fc9(0x8aa,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0x872,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7,0xe);
  FUN_23f1_119e();
  FUN_23f1_119e();
  FUN_23f1_119e();
  FUN_23f1_119e();
  FUN_23f1_1f2a();
  FUN_23f1_1f2a();
  FUN_23f1_1f2a();
  FUN_23f1_1f2a();
  FUN_23f1_1f2a();
  FUN_23f1_1bcf();
  FUN_23f1_1bcf();
  FUN_23f1_1bcf();
  do {
    FUN_1928_1906(DAT_28d3_2a4a,0,0x82,0x131,2);
    FUN_1928_1906(DAT_28d3_2a4a,1,0x82,0x145,2);
    FUN_1928_1906(DAT_28d3_2a4e,1,0x82,0xe1,2);
    FUN_1928_1906(DAT_28d3_2a4e,0,0x82,0x109,2);
    FUN_23f1_1211(1,0x3b);
    FUN_23f1_1c32();
    FUN_1000_4055();
    FUN_23f1_1f2a();
    FUN_23f1_1c32();
    FUN_1000_4055();
    FUN_23f1_1f2a();
    FUN_23f1_1c32();
    FUN_1000_4055();
    FUN_23f1_1f2a();
    FUN_23f1_1c32();
    FUN_1000_4055();
    FUN_23f1_1f2a();
    FUN_1000_40a5(DAT_28d3_2984,local_a);
    FUN_23f1_1f2a();
    iVar1 = FUN_1928_5dc0(0x8aa,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0x872,
                          (char *)s_String_reference_out_of_range_28d3_28cc + 7,0xe,0);
    iVar2 = 0xf;
    piVar3 = (int *)0x6a28;
    do {
      if (*piVar3 == iVar1) {
                    /* WARNING: Could not recover jumptable at 0x0001f876. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*(code *)piVar3[0xf])();
        return;
      }
      piVar3 = piVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  } while( true );
}



// Function: FUN_1928_6a64

int __cdecl16far FUN_1928_6a64(long param_1,long param_2)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int local_e;
  
  lVar3 = param_1 * 3;
  lVar4 = param_2 * 3;
  param_2._2_2_ = (int)((ulong)lVar4 >> 0x10);
  param_2._0_2_ = (uint)lVar4;
  param_1._2_2_ = (int)((ulong)lVar3 >> 0x10);
  param_1._0_2_ = (uint)lVar3;
  uVar1 = *(int *)((uint)param_2 * 2 + DAT_28d3_2a40) - *(int *)((uint)param_1 * 2 + DAT_28d3_2a40);
  uVar5 = (int)uVar1 >> 0xf;
  uVar5 = (uVar1 ^ uVar5) - uVar5;
  uVar1 = (uint)(lVar4 + 1);
  uVar6 = (uint)(lVar3 + 1);
  uVar6 = *(int *)(uVar1 * 2 + DAT_28d3_2a40) - *(int *)(uVar6 * 2 + DAT_28d3_2a40);
  uVar1 = (int)uVar6 >> 0xf;
  uVar1 = (uVar6 ^ uVar1) - uVar1;
  uVar6 = (uint)(lVar4 + 2);
  uVar7 = (uint)(lVar3 + 2);
  lVar3 = (long)(*(int *)(uVar6 * 2 + DAT_28d3_2a40) - *(int *)(uVar7 * 2 + DAT_28d3_2a40));
  if (uVar1 < uVar5) {
    uVar1 = uVar5;
  }
  iVar2 = DAT_28d3_29d6;
  if (0 < lVar3) {
    iVar2 = DAT_28d3_29d4;
  }
  local_e = uVar1 + (int)((iVar2 * lVar3) / 10);
  return local_e;
}



// Function: FUN_1928_6bc5

void __cdecl16far FUN_1928_6bc5(long param_1,long param_2)

{
  undefined2 uVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  uint uVar5;
  
  lVar2 = param_1 * 3;
  lVar3 = param_2 * 3;
  param_1._2_2_ = (int)((ulong)lVar2 >> 0x10);
  param_1._0_2_ = (uint)lVar2;
  uVar1 = *(undefined2 *)((uint)param_1 * 2 + DAT_28d3_2a40);
  param_2._2_2_ = (int)((ulong)lVar3 >> 0x10);
  param_2._0_2_ = (uint)lVar3;
  *(undefined2 *)((uint)param_1 * 2 + DAT_28d3_2a40) =
       *(undefined2 *)((uint)param_2 * 2 + DAT_28d3_2a40);
  *(undefined2 *)((uint)param_2 * 2 + DAT_28d3_2a40) = uVar1;
  uVar4 = (uint)(lVar2 + 1);
  uVar1 = *(undefined2 *)(uVar4 * 2 + DAT_28d3_2a40);
  uVar4 = (uint)(lVar3 + 1);
  uVar5 = (uint)(lVar2 + 1);
  *(undefined2 *)(uVar5 * 2 + DAT_28d3_2a40) = *(undefined2 *)(uVar4 * 2 + DAT_28d3_2a40);
  uVar4 = (uint)(lVar3 + 1);
  *(undefined2 *)(uVar4 * 2 + DAT_28d3_2a40) = uVar1;
  uVar4 = (uint)(lVar2 + 2);
  uVar1 = *(undefined2 *)(uVar4 * 2 + DAT_28d3_2a40);
  uVar4 = (uint)(lVar3 + 2);
  uVar5 = (uint)(lVar2 + 2);
  *(undefined2 *)(uVar5 * 2 + DAT_28d3_2a40) = *(undefined2 *)(uVar4 * 2 + DAT_28d3_2a40);
  uVar4 = (uint)(lVar3 + 2);
  *(undefined2 *)(uVar4 * 2 + DAT_28d3_2a40) = uVar1;
  return;
}



// Function: caseD_0

void __cdecl16near switchD_2000:40cc::caseD_0(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}



// Function: FUN_2001_04a0

void __cdecl16near FUN_2001_04a0(void)

{
  undefined2 *puVar1;
  undefined1 *puVar2;
  undefined2 *puVar3;
  byte bVar4;
  undefined uVar5;
  undefined2 in_AX;
  int iVar6;
  undefined2 *puVar7;
  undefined2 *puVar8;
  undefined1 *puVar9;
  
  bVar4 = (byte)in_AX;
  DAT_28d3_03fe = in_AX;
  if (1 < bVar4) {
    puVar7 = (undefined2 *)((uint)(byte)(bVar4 - 2) * 8 + 0x890);
    puVar8 = (undefined2 *)&DAT_28d3_0437;
    for (iVar6 = 4; iVar6 != 0; iVar6 = iVar6 + -1) {
      puVar3 = puVar8;
      puVar8 = puVar8 + 1;
      puVar1 = puVar7;
      puVar7 = puVar7 + 1;
      *puVar3 = *puVar1;
    }
    return;
  }
  uVar5 = 0xff;
  if (bVar4 != 1) {
    uVar5 = 0;
  }
  puVar9 = (undefined1 *)&DAT_28d3_0437;
  for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar2 = puVar9;
    puVar9 = puVar9 + 1;
    *puVar2 = uVar5;
  }
  return;
}



// Function: FUN_2001_067b

undefined4 __cdecl16near FUN_2001_067b(void)

{
  char *pcVar1;
  undefined2 in_DX;
  
  pcVar1 = (char *)0x5;
  if (cRam000204e2 != '\0') {
    pcVar1 = (char *)s_Are_you_sure__28d3_1005;
  }
  out(0x3ce,pcVar1);
  out(0x3ce,3);
  out(0x3ce,0xff08);
  out(0x3c4,0xf02);
  return CONCAT22(in_DX,0xf02);
}



// Function: FUN_2001_06a0

void __cdecl16near FUN_2001_06a0(void)

{
  if (DAT_2001_0248 != '\0') {
    out(0x3ce,0x1803);
  }
  return;
}



// Function: FUN_2001_06ca

long __cdecl16near
FUN_2001_06ca(uint param_1,int param_2,uint param_3,int param_4,undefined param_5)

{
  int iVar1;
  undefined2 uVar2;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  undefined extraout_AH;
  int iVar6;
  int extraout_DX;
  int iVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  bool bVar11;
  byte bVar12;
  
  uVar3 = param_3;
  uVar2 = DAT_28d3_04e3;
  FUN_2001_06a0((char *)s_String_reference_out_of_range_28d3_28cc + 7);
  out(0x3ce,0);
  out(0x3cf,param_5);
  out(0x3ce,1);
  out(0x3cf,0xff);
  uVar8 = param_4 - param_2;
  if ((int)uVar8 < 0) {
    LOCK();
    UNLOCK();
    param_2 = param_4;
    LOCK();
    param_3 = param_1;
    UNLOCK();
    param_1 = uVar3;
    uVar8 = -uVar8;
  }
  pbVar10 = (byte *)(param_2 * 0x50 + (param_1 >> 3));
  bVar5 = (byte)((uint)(param_2 * 0x40) >> 8);
  out(0x3ce,8);
  bVar4 = 0x80 >> ((byte)param_1 & 7);
  param_3 = param_3 - param_1;
  if ((int)param_3 < 0) {
    if (-param_3 < uVar8) {
      iVar6 = uVar8 + 1;
      iVar9 = param_3 * -2 - uVar8;
      iVar7 = param_3 * -2 + uVar8 * -2;
      out(0x3cf,bVar4);
      do {
        bVar11 = (uRam000204e0 & 1) != 0;
        uRam000204e0 = uRam000204e0 >> 1 | (uint)bVar11 << 0xf;
        if (bVar11) {
          LOCK();
          bVar12 = *pbVar10;
          *pbVar10 = bVar5;
          UNLOCK();
          bVar5 = bVar12;
        }
        iVar1 = uVar8 * 2 + iVar7;
        if (-1 < iVar9) {
          bVar11 = (char)bVar4 < '\0';
          bVar4 = bVar4 << 1 | bVar11;
          pbVar10 = pbVar10 + -(uint)bVar11;
          out(0x3cf,bVar4);
          iVar1 = iVar7;
        }
        iVar9 = iVar9 + iVar1;
        pbVar10 = pbVar10 + 0x50;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    else {
      iVar6 = -param_3 + 1;
      iVar7 = uVar8 * 2 + param_3;
      iVar9 = uVar8 * 2 + param_3 * 2;
      bVar5 = 0;
      do {
        bVar11 = (uRam000204e0 & 1) != 0;
        uRam000204e0 = uRam000204e0 >> 1 | (uint)bVar11 << 0xf;
        if (bVar11) {
          bVar5 = bVar5 | bVar4;
        }
        if (iVar7 < 0) {
          iVar7 = iVar7 + param_3 * -2 + iVar9;
          bVar11 = (char)bVar4 < '\0';
          bVar4 = bVar4 << 1 | bVar11;
          if (bVar11) {
            out(0x3cf,bVar5);
            LOCK();
            *pbVar10 = bVar5;
            UNLOCK();
            pbVar10 = pbVar10 + -1;
            bVar5 = 0;
          }
        }
        else {
          out(0x3cf,bVar5);
          LOCK();
          *pbVar10 = bVar5;
          UNLOCK();
          iVar7 = iVar7 + iVar9;
          bVar11 = (char)bVar4 < '\0';
          bVar4 = bVar4 << 1 | bVar11;
          bVar5 = 0;
          pbVar10 = pbVar10 + (0x50 - (uint)bVar11);
        }
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      out(0x3cf,bVar5);
      LOCK();
      *pbVar10 = bVar5;
      UNLOCK();
    }
  }
  else if (param_3 < uVar8) {
    iVar6 = uVar8 + 1;
    iVar9 = param_3 * 2 - uVar8;
    iVar7 = param_3 * 2 + uVar8 * -2;
    out(0x3cf,bVar4);
    do {
      bVar11 = (uRam000204e0 & 1) != 0;
      uRam000204e0 = uRam000204e0 >> 1 | (uint)bVar11 << 0xf;
      if (bVar11) {
        LOCK();
        bVar12 = *pbVar10;
        *pbVar10 = bVar5;
        UNLOCK();
        bVar5 = bVar12;
      }
      iVar1 = uVar8 * 2 + iVar7;
      if (-1 < iVar9) {
        bVar12 = bVar4 & 1;
        bVar4 = bVar4 >> 1 | bVar12 << 7;
        pbVar10 = pbVar10 + bVar12;
        out(0x3cf,bVar4);
        iVar1 = iVar7;
      }
      iVar9 = iVar9 + iVar1;
      pbVar10 = pbVar10 + 0x50;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  else {
    iVar6 = param_3 + 1;
    iVar7 = uVar8 * 2 - param_3;
    iVar9 = uVar8 * 2 + param_3 * -2;
    bVar5 = 0;
    do {
      bVar11 = (uRam000204e0 & 1) != 0;
      uRam000204e0 = uRam000204e0 >> 1 | (uint)bVar11 << 0xf;
      if (bVar11) {
        bVar5 = bVar5 | bVar4;
      }
      if (iVar7 < 0) {
        iVar7 = iVar7 + param_3 * 2 + iVar9;
        bVar11 = (bool)(bVar4 & 1);
        bVar4 = bVar4 >> 1 | bVar11 << 7;
        if (bVar11) {
          out(0x3cf,bVar5);
          LOCK();
          *pbVar10 = bVar5;
          UNLOCK();
          pbVar10 = pbVar10 + 1;
          bVar5 = 0;
        }
      }
      else {
        out(0x3cf,bVar5);
        LOCK();
        *pbVar10 = bVar5;
        UNLOCK();
        iVar7 = iVar7 + iVar9;
        bVar12 = bVar4 & 1;
        bVar4 = bVar4 >> 1 | bVar12 << 7;
        bVar5 = 0;
        pbVar10 = pbVar10 + bVar12 + 0x50;
      }
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    out(0x3cf,bVar5);
    LOCK();
    *pbVar10 = bVar5;
    UNLOCK();
  }
  FUN_2001_067b();
  out(extraout_DX,0xff);
  out(extraout_DX + -1,1);
  out(extraout_DX,0);
  return (ulong)CONCAT21(extraout_DX,extraout_AH) << 8;
}



// Function: FUN_2001_0fe8

undefined __cdecl16near FUN_2001_0fe8(void)

{
  char in_CL;
  byte bVar1;
  int in_BX;
  
  bVar1 = in_CL - 1;
  if (((char)bVar1 < '\0') && (bVar1 = 7, DAT_28d3_04e2 != '\0')) {
    FUN_2001_1573();
  }
  out(0x3cf,*(undefined *)(ulong)(in_BX + (uint)bVar1));
  return *(undefined *)(ulong)(in_BX + (uint)bVar1);
}



// Function: FUN_2001_1573

undefined __cdecl16near FUN_2001_1573(void)

{
  undefined uVar1;
  uint unaff_DI;
  
  out(0x3ce,7);
  uVar1 = 10;
  if ((unaff_DI & 1) == 0) {
    uVar1 = 5;
  }
  out(0x3cf,uVar1);
  out(0x3ce,8);
  return 8;
}



// Function: FUN_215c_0002

undefined2 __cdecl16far FUN_215c_0002(void)

{
  char cVar1;
  
  DAT_28d3_4ff6 = 7;
  out(0x30c,7);
  out(0x31c,0);
  out(0x30b,0x82);
  out(0x308,0x96);
  out(0x30a,0xfd);
  out(0x30a,0xff);
  out(0x30a,0xfc);
  out(0x313,0x91);
  out(0x311,0xff);
  out(0x313,9);
  out(0x313,0xb);
  out(0x313,0xd);
  out(0x303,0x34);
  out(0x303,0x78);
  out(0x303,0xb4);
  out(0x307,0x34);
  out(0x307,0x78);
  out(0x307,0xb8);
  out(0x317,0x34);
  out(0x317,0x7a);
  out(0x317,0xb8);
  FUN_215c_01eb(DAT_28d3_2988,1);
  cVar1 = in(0x308);
  if (cVar1 != -0x6a) {
    return 0;
  }
  return 1;
}



// Function: FUN_215c_00a8

undefined2 __cdecl16far FUN_215c_00a8(int param_1)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  undefined2 uVar6;
  uint uVar7;
  uint uVar8;
  uint local_c;
  uint local_a;
  uint local_4;
  
  if (DAT_28d3_2960 == 0) {
    local_c = DAT_28d3_4fe2;
    uVar4 = DAT_28d3_29b8;
    if (DAT_28d3_29b6 == 0) {
      uVar4 = 0x200;
    }
    uVar7 = uVar4;
    if ((DAT_28d3_29ce != 0) && (DAT_28d3_4fe2 != 0)) {
      uVar7 = DAT_28d3_4fe2 & uVar4;
    }
    if (param_1 != 0) {
      FUN_215c_0241(uVar7);
    }
    uVar8 = 0;
    do {
      iVar5 = FUN_1000_1953();
      if ((iVar5 != 0) && (iVar5 = FUN_1000_18df(), uVar1 = DAT_28d3_4fe2, iVar5 == 0x1b)) break;
      do {
        iVar5 = FUN_215c_0221();
      } while ((iVar5 - 2U & 0xffe0) != 0);
      FUN_215c_01eb(DAT_28d3_2988,(undefined)DAT_28d3_298a);
      DAT_28d3_4fe8 = DAT_28d3_4fe8 + 1;
      FUN_1000_537f(1);
      FUN_215c_01eb(DAT_28d3_2988,1);
      if (DAT_28d3_29ce == 0) goto LAB_215c_0194;
      bVar2 = in(0x310);
      bVar3 = in(0x312);
      uVar7 = uVar7 - ((uint)bVar2 + (uint)bVar3 * 0x100 & 0x3ff & uVar7);
      if (uVar7 == 0) {
        if ((uVar8 != 0) || (DAT_28d3_4fe2 != 0)) {
          FUN_215c_0241(uVar4);
        }
        DAT_28d3_4fe2 = 0;
        goto LAB_215c_0194;
      }
      if (uVar8 != 10) {
        local_a = 1;
        local_4 = 0;
        do {
          if ((local_a & uVar7) != 0) {
            ((undefined2 *)&DAT_28d3_29ba)[local_4] = ((undefined2 *)&DAT_28d3_29ba)[local_4] + 1;
          }
          local_a = local_a << 1;
          local_4 = local_4 + 1;
        } while (local_4 < 10);
        FUN_1928_4827(0);
        if (uVar7 != local_c) {
          FUN_215c_0241(uVar7);
          local_c = uVar7;
        }
      }
      uVar8 = uVar8 + 1;
      uVar1 = uVar7;
    } while (uVar8 < 0xb);
    DAT_28d3_4fe2 = uVar1;
    uVar6 = 0;
  }
  else {
    DAT_28d3_4fe8 = DAT_28d3_4fe8 + 1;
LAB_215c_0194:
    uVar6 = 1;
  }
  return uVar6;
}



// Function: FUN_215c_01eb

uint __cdecl16far FUN_215c_01eb(int param_1,undefined param_2)

{
  uint uVar1;
  
  out(0x314,(char)((param_1 * 100) % 0x100));
  uVar1 = (param_1 * 100) / 0x100;
  out(0x314,(char)uVar1);
  out(0x315,param_2);
  out(0x315,0);
  return uVar1 & 0xff00;
}



// Function: FUN_215c_0221

int __cdecl16far FUN_215c_0221(void)

{
  byte bVar1;
  byte bVar2;
  
  out(0x317,0);
  bVar1 = in(0x314);
  bVar2 = in(0x314);
  return (uint)bVar1 + (uint)bVar2 * 0x100;
}



// Function: FUN_215c_0241

undefined __cdecl16far FUN_215c_0241(uint param_1)

{
  undefined uVar1;
  
  out(0x311,(byte)param_1 ^ 0xff);
  if ((param_1 & 0x100) == 0) {
    uVar1 = 9;
  }
  else {
    uVar1 = 8;
  }
  out(0x313,uVar1);
  if ((param_1 & 0x200) == 0) {
    uVar1 = 0xb;
  }
  else {
    uVar1 = 10;
  }
  out(0x313,uVar1);
  out(0x313,0xc);
  FUN_1000_537f(DAT_28d3_57ea);
  out(0x313,0xd);
  return 0xd;
}



// Function: FUN_215c_028f

undefined __cdecl16far FUN_215c_028f(void)

{
  out(0x311,0xff);
  out(0x313,9);
  out(0x313,0xb);
  out(0x313,0xd);
  return 0xd;
}



// Function: FUN_215c_05ad

undefined2 __cdecl16far FUN_215c_05ad(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  out(0x300,100);
  out(0x300,0);
  out(0x301,0);
  out(0x301,0x70);
  out(0x304,100);
  out(0x304,0);
  out(0x305,0);
  out(0x305,0x70);
  out(0x302,100);
  out(0x302,0);
  out(0x306,0);
  out(0x306,0x40);
  if (param_1 == 0) {
    DAT_28d3_4ff6 = 0x39;
    bVar1 = 1;
  }
  else {
    DAT_28d3_4ff6 = 0x3b;
    bVar1 = 3;
  }
  out(0x30c,DAT_28d3_4ff6);
  if (DAT_28d3_2960 == 0) {
    while (DAT_28d3_4ff6 != bVar1) {
      bVar2 = in(0x309);
      if ((bVar2 & 3) != 3) {
        DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xf7;
      }
      if ((bVar2 & 0xc) != 0xc) {
        DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xef;
      }
      if ((bVar2 & 0x30) != 0x30) {
        DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xdf;
      }
      out(0x30c,DAT_28d3_4ff6);
    }
  }
  out(0x300,200);
  out(0x300,0);
  out(0x301,200);
  out(0x301,0);
  out(0x304,200);
  out(0x304,0);
  out(0x305,200);
  out(0x305,0);
  out(0x302,200);
  out(0x302,0);
  out(0x306,200);
  out(0x306,0);
  if (param_1 == 0) {
    DAT_28d3_4ff6 = 0x3e;
  }
  else {
    DAT_28d3_4ff6 = 0x3c;
  }
  out(0x30c,DAT_28d3_4ff6);
  bVar2 = 1;
  bVar1 = 1;
  if (DAT_28d3_2960 == 0) {
    while ((bool)(bVar2 | bVar1)) {
      bVar3 = in(0x309);
      if ((bVar3 & 0x80) != 0) {
        DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xe7;
        bVar2 = 0;
      }
      if ((bVar3 & 0x40) != 0) {
        DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xdf;
        bVar1 = 0;
      }
      out(0x30c,DAT_28d3_4ff6);
    }
  }
  out(0x30c,0x80);
  if (param_1 == 0) {
    DAT_28d3_2972 = 0x5b04;
    DAT_28d3_2974 = 200;
    DAT_28d3_2976 = 200;
  }
  DAT_28d3_296e = (uint)(param_1 == 0);
  return 1;
}



// Function: FUN_215c_0750

/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

undefined2 __cdecl16far FUN_215c_0750(void)

{
  bool bVar1;
  bool bVar2;
  undefined uVar3;
  byte bVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  uint uVar7;
  undefined4 in_EDX;
  int iVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  undefined4 *puVar15;
  undefined2 *puVar16;
  undefined *puVar17;
  undefined4 in_ESP;
  undefined2 uVar19;
  undefined4 *puVar18;
  undefined2 unaff_BP;
  undefined2 unaff_SI;
  undefined2 unaff_DI;
  undefined2 uVar20;
  undefined2 unaff_SS;
  
  uVar20 = 0x215c;
  iVar8 = (int)in_ESP;
  uVar19 = (undefined2)((ulong)in_ESP >> 0x10);
  *(undefined2 *)(iVar8 + -2) = unaff_BP;
  *(undefined2 *)(iVar8 + -0x1e) = unaff_SI;
  puVar17 = (undefined *)(iVar8 + -0x20);
  *(undefined2 *)(iVar8 + -0x20) = unaff_DI;
  bVar1 = false;
  bVar2 = false;
  while( true ) {
    uVar6 = (undefined2)in_EDX;
    *(int *)(iVar8 + -4) = *(int *)(iVar8 + 4) - DAT_28d3_2972;
    *(int *)(iVar8 + -6) = *(int *)(iVar8 + 6) - DAT_28d3_2974;
    *(int *)(iVar8 + -8) = *(int *)(iVar8 + 8) - DAT_28d3_2976;
    *(undefined2 *)(puVar17 + -2) = *(undefined2 *)(iVar8 + -8);
    *(undefined2 *)(puVar17 + -4) = *(undefined2 *)(iVar8 + -6);
    *(undefined2 *)(puVar17 + -6) = *(undefined2 *)(iVar8 + -4);
    *(undefined2 *)(puVar17 + -8) = uVar20;
    puVar9 = puVar17 + -10;
    *(char **)(puVar17 + -10) = (char *)s_Partial_loss_of_precision_28d3_1d2d + 0x19;
    uVar5 = FUN_215c_0b84();
    puVar18 = (undefined4 *)CONCAT22(uVar19,puVar9 + 10);
    *(undefined2 *)(iVar8 + -10) = uVar5;
    if (*(int *)(iVar8 + -4) == 0) {
      DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xf7;
    }
    else {
      *(undefined2 *)(puVar9 + 8) = *(undefined2 *)(iVar8 + -10);
      *(undefined2 *)(puVar9 + 6) = *(undefined2 *)(iVar8 + -4);
      *(undefined2 *)(puVar9 + 4) = uVar20;
      puVar10 = puVar9 + 2;
      *(char **)(puVar9 + 2) = (char *)s_Floating_point_error___s__28d3_1d53 + 0xc;
      uVar5 = FUN_215c_0c45();
      *(undefined2 *)(iVar8 + -0xe) = uVar6;
      *(undefined2 *)(iVar8 + -0x10) = uVar5;
      *(long *)(puVar10 + 4) = *(long *)(iVar8 + -0x10) % 0x100;
      puVar18 = (undefined4 *)CONCAT22(uVar19,puVar10 + 4) + 1;
      out(0x300,(char)*(undefined4 *)CONCAT22(uVar19,puVar10 + 4));
      out(0x300,(char)(*(long *)(iVar8 + -0x10) / 0x100));
      *(undefined2 *)(iVar8 + -0x12) = *(undefined2 *)(iVar8 + -4);
      uVar7 = (int)*(uint *)(iVar8 + -0x12) >> 0xf;
      *(int *)((int)(undefined4 *)puVar18 + -2) =
           (int)((*(uint *)(iVar8 + -0x12) ^ uVar7) - uVar7) % 0x100;
      out(0x301,(char)*(undefined2 *)((int)(undefined4 *)puVar18 + -2));
      *(undefined2 *)(iVar8 + -0x14) = *(undefined2 *)(iVar8 + -4);
      uVar7 = (int)*(uint *)(iVar8 + -0x14) >> 0xf;
      uVar6 = 0x301;
      out(0x301,(char)((int)((*(uint *)(iVar8 + -0x14) ^ uVar7) - uVar7) / 0x100));
      if (*(int *)(iVar8 + -4) < 1) {
        DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xfe | 8;
      }
      else {
        DAT_28d3_4ff6 = DAT_28d3_4ff6 | 9;
      }
      bVar1 = true;
    }
    uVar19 = (undefined2)((ulong)puVar18 >> 0x10);
    puVar11 = (undefined4 *)puVar18;
    if (*(int *)(iVar8 + -6) == 0) {
      DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xef;
    }
    else {
      *(undefined2 *)((int)puVar11 + -2) = *(undefined2 *)(iVar8 + -10);
      *(undefined2 *)(puVar11 + -1) = *(undefined2 *)(iVar8 + -6);
      *(undefined2 *)((int)puVar11 + -6) = uVar20;
      puVar12 = puVar11 + -2;
      *(undefined2 *)(puVar11 + -2) = 0x1dfb;
      uVar5 = FUN_215c_0c45();
      *(undefined2 *)(iVar8 + -0xe) = uVar6;
      *(undefined2 *)(iVar8 + -0x10) = uVar5;
      *(long *)((int)puVar12 + 4) = *(long *)(iVar8 + -0x10) % 0x100;
      puVar18 = (undefined4 *)CONCAT22(uVar19,(undefined4 *)((int)puVar12 + 4)) + 1;
      out(0x304,(char)*(undefined4 *)CONCAT22(uVar19,(undefined4 *)((int)puVar12 + 4)));
      out(0x304,(char)(*(long *)(iVar8 + -0x10) / 0x100));
      *(undefined2 *)(iVar8 + -0x16) = *(undefined2 *)(iVar8 + -6);
      uVar7 = (int)*(uint *)(iVar8 + -0x16) >> 0xf;
      *(int *)((int)(undefined4 *)puVar18 + -2) =
           (int)((*(uint *)(iVar8 + -0x16) ^ uVar7) - uVar7) % 0x100;
      out(0x305,(char)*(undefined2 *)((int)(undefined4 *)puVar18 + -2));
      *(undefined2 *)(iVar8 + -0x18) = *(undefined2 *)(iVar8 + -6);
      uVar7 = (int)*(uint *)(iVar8 + -0x18) >> 0xf;
      uVar6 = 0x305;
      out(0x305,(char)((int)((*(uint *)(iVar8 + -0x18) ^ uVar7) - uVar7) / 0x100));
      if (*(int *)(iVar8 + -6) < 1) {
        DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xfd | 0x10;
      }
      else {
        DAT_28d3_4ff6 = DAT_28d3_4ff6 | 0x12;
      }
      bVar1 = true;
    }
    uVar19 = (undefined2)((ulong)puVar18 >> 0x10);
    puVar13 = (undefined4 *)puVar18;
    if (*(int *)(iVar8 + -8) == 0) {
      DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xdf;
    }
    else {
      *(undefined2 *)((int)puVar13 + -2) = *(undefined2 *)(iVar8 + -10);
      *(undefined2 *)(puVar13 + -1) = *(undefined2 *)(iVar8 + -8);
      *(undefined2 *)((int)puVar13 + -6) = uVar20;
      puVar14 = puVar13 + -2;
      *(undefined2 *)(puVar13 + -2) = 0x1e97;
      uVar5 = FUN_215c_0c45();
      *(undefined2 *)(iVar8 + -0xe) = uVar6;
      *(undefined2 *)(iVar8 + -0x10) = uVar5;
      *(long *)((int)puVar14 + 4) = *(long *)(iVar8 + -0x10) % 0x100;
      puVar18 = (undefined4 *)CONCAT22(uVar19,(undefined4 *)((int)puVar14 + 4)) + 1;
      out(0x302,(char)*(undefined4 *)CONCAT22(uVar19,(undefined4 *)((int)puVar14 + 4)));
      out(0x302,(char)(*(long *)(iVar8 + -0x10) / 0x100));
      *(undefined2 *)(iVar8 + -0x1a) = *(undefined2 *)(iVar8 + -8);
      uVar7 = (int)*(uint *)(iVar8 + -0x1a) >> 0xf;
      *(int *)((int)(undefined4 *)puVar18 + -2) =
           (int)((*(uint *)(iVar8 + -0x1a) ^ uVar7) - uVar7) % 0x100;
      out(0x306,(char)*(undefined2 *)((int)(undefined4 *)puVar18 + -2));
      *(undefined2 *)(iVar8 + -0x1c) = *(undefined2 *)(iVar8 + -8);
      uVar7 = (int)*(uint *)(iVar8 + -0x1c) >> 0xf;
      out(0x306,(char)((int)((*(uint *)(iVar8 + -0x1c) ^ uVar7) - uVar7) / 0x100));
      if (*(int *)(iVar8 + -8) < 1) {
        DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xfb | 0x20;
      }
      else {
        DAT_28d3_4ff6 = DAT_28d3_4ff6 | 0x24;
      }
      bVar2 = true;
    }
    puVar15 = (undefined4 *)puVar18;
    DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0x7f;
    out(0x30c,DAT_28d3_4ff6);
    if ((((*(int *)(iVar8 + -4) == 0) && (*(int *)(iVar8 + -6) == 0)) && (*(int *)(iVar8 + -8) == 0)
        ) || (DAT_28d3_2960 != 0)) break;
    do {
      do {
        uVar19 = (undefined2)((ulong)puVar18 >> 0x10);
        puVar15 = (undefined4 *)puVar18;
        if (!(bool)(bVar1 | bVar2)) goto LAB_215c_0a1c;
        uVar3 = in(0x309);
        *(undefined *)(iVar8 + -0xb) = uVar3;
        if ((bVar1) && ((*(byte *)(iVar8 + -0xb) & 0x80) == 0x80)) {
          DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xe7;
          bVar1 = false;
        }
        if ((bVar2) && ((*(byte *)(iVar8 + -0xb) & 0x40) == 0x40)) {
          DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xdf;
          bVar2 = false;
        }
        out(0x30c,DAT_28d3_4ff6);
      } while ((*(byte *)(iVar8 + -0xb) & 0x3f) == 0x3f);
      *(undefined2 *)((int)puVar15 + -2) = 1;
      *(undefined2 *)(puVar15 + -1) = uVar20;
      uVar20 = 0x1000;
      puVar16 = (undefined2 *)((int)puVar15 + -6);
      *(undefined2 *)((int)puVar15 + -6) = 0x1fa7;
      FUN_1000_537f();
      puVar18 = (undefined4 *)CONCAT22(uVar19,puVar16 + 3);
      in_EDX = 0x309;
      uVar3 = in(0x309);
      *(undefined *)(iVar8 + -0xb) = uVar3;
      if (((*(byte *)(iVar8 + -0xb) & 0x3f) != 0x3f) || (DAT_28d3_29d0 == 2)) {
        bVar4 = DAT_28d3_4ff6 & 199;
        out(0x30c,bVar4);
        bVar1 = false;
        bVar2 = false;
        if ((*(byte *)(iVar8 + -0xb) & 3) != 3) {
          out(0x300,200);
          out(0x300,0);
          out(0x301,200);
          out(0x301,0);
          if (*(int *)(iVar8 + -4) < 0) {
            bVar4 = bVar4 | 9;
          }
          else {
            bVar4 = DAT_28d3_4ff6 & 0xc6 | 8;
          }
          bVar1 = true;
        }
        DAT_28d3_4ff6 = bVar4;
        if ((*(byte *)(iVar8 + -0xb) & 0xc) != 0xc) {
          out(0x304,200);
          out(0x304,0);
          out(0x305,200);
          out(0x305,0);
          if (*(int *)(iVar8 + -6) < 0) {
            DAT_28d3_4ff6 = DAT_28d3_4ff6 | 0x12;
          }
          else {
            DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xfd | 0x10;
          }
          bVar1 = true;
        }
        if ((*(byte *)(iVar8 + -0xb) & 0x30) != 0x30) {
          out(0x302,200);
          out(0x302,0);
          out(0x306,200);
          out(0x306,0);
          if (*(int *)(iVar8 + -8) < 0) {
            DAT_28d3_4ff6 = DAT_28d3_4ff6 | 0x24;
          }
          else {
            DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xfb | 0x20;
          }
          bVar2 = true;
        }
        DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0x7f;
        while (out(0x30c,DAT_28d3_4ff6), (bool)(bVar1 | bVar2)) {
          uVar3 = in(0x309);
          *(undefined *)(iVar8 + -0xb) = uVar3;
          if ((bVar1) && ((*(byte *)(iVar8 + -0xb) & 0x80) == 0x80)) {
            DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xe7;
            bVar1 = false;
          }
          if ((bVar2) && ((*(byte *)(iVar8 + -0xb) & 0x40) == 0x40)) {
            DAT_28d3_4ff6 = DAT_28d3_4ff6 & 0xdf;
            bVar2 = false;
          }
        }
        out(0x30c,DAT_28d3_4ff6 & 199);
        DAT_28d3_296e = 0;
        DAT_28d3_4ff6 = DAT_28d3_4ff6 & 199;
        return 0;
      }
    } while (DAT_28d3_29d0 != 1);
    puVar16[2] = 0;
    puVar16[1] = 0x1000;
    *puVar16 = 0x1fd0;
    FUN_215c_05ad();
    puVar17 = (undefined *)((int)puVar16 + 6);
  }
LAB_215c_0a1c:
  if (DAT_28d3_2960 != 0) {
    *(undefined2 *)((int)puVar15 + -2) = DAT_28d3_2988;
    *(undefined2 *)((int)puVar15 + -4) = uVar20;
    *(undefined2 *)((int)puVar15 + -6) = 0x1fec;
    FUN_1000_537f();
  }
  DAT_28d3_2976 = *(undefined2 *)(iVar8 + 8);
  DAT_28d3_2974 = *(undefined2 *)(iVar8 + 6);
  DAT_28d3_2972 = *(undefined2 *)(iVar8 + 4);
  return 1;
}



// Function: FUN_215c_0b84

int __cdecl16far FUN_215c_0b84(uint param_1,uint param_2,uint param_3)

{
  int iVar1;
  long lVar3;
  uint uVar4;
  int iVar2;
  
  if ((int)((param_2 ^ (int)param_2 >> 0xf) - ((int)param_2 >> 0xf)) <
      (int)((param_1 ^ (int)param_1 >> 0xf) - ((int)param_1 >> 0xf))) {
    param_2 = param_1;
  }
  lVar3 = (long)(int)((param_2 ^ (int)param_2 >> 0xf) - ((int)param_2 >> 0xf));
  uVar4 = (int)param_3 >> 0xf;
  if (lVar3 <= (int)((param_3 ^ uVar4) - uVar4)) {
    lVar3 = (long)(int)((param_3 ^ uVar4) - uVar4);
  }
  lVar3 = (lVar3 * 1000) / (long)DAT_28d3_298c;
  iVar2 = (int)(lVar3 / (long)DAT_28d3_2988);
  iVar1 = iVar2 + 1;
  if ((long)(DAT_28d3_2988 - DAT_28d3_2994) < lVar3 % (long)DAT_28d3_2988) {
    iVar1 = iVar2 + 2;
  }
  return iVar1;
}



// Function: FUN_215c_0c45

/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

undefined2 __cdecl16far FUN_215c_0c45(void)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  int iVar5;
  undefined4 in_ESP;
  undefined2 unaff_BP;
  undefined2 unaff_SS;
  
  iVar5 = (int)in_ESP;
  *(undefined2 *)(iVar5 + -2) = unaff_BP;
  *(undefined4 *)(iVar5 + -0xe) = 0xffdc;
  *(undefined4 *)(iVar5 + -6) = (long)(100000 / (sqword)(long)DAT_28d3_298c);
  *(undefined4 *)(iVar5 + -10) = *(undefined4 *)(iVar5 + -6);
  if (DAT_28d3_298e == 0) {
    iVar1 = *(int *)(iVar5 + 6);
    lVar3 = (long)DAT_28d3_2988;
    lVar4 = (long)DAT_28d3_2994;
    *(undefined2 *)(iVar5 + -0x10) = *(undefined2 *)(iVar5 + 4);
    *(long *)(iVar5 + -0x14) = (iVar1 * lVar3 - lVar4) * 100;
    uVar2 = (int)*(uint *)(iVar5 + -0x10) >> 0xf;
    *(long *)(iVar5 + -6) =
         *(long *)CONCAT22((int)((ulong)in_ESP >> 0x10),(long *)(iVar5 + -0x14)) /
         (long)(int)((*(uint *)(iVar5 + -0x10) ^ uVar2) - uVar2);
    if (*(long *)(iVar5 + -6) < *(long *)(iVar5 + -10)) {
      *(undefined4 *)(iVar5 + -6) = *(undefined4 *)(iVar5 + -10);
    }
    if (*(long *)(iVar5 + -0xe) < *(long *)(iVar5 + -6)) {
      *(undefined4 *)(iVar5 + -6) = *(undefined4 *)(iVar5 + -0xe);
    }
  }
  return *(undefined2 *)(iVar5 + -6);
}



// Function: FUN_2229_000c

undefined2 __cdecl16far
FUN_2229_000c(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5)

{
  uint uVar1;
  uint in_DX;
  
  uVar1 = FUN_1000_2aa3(param_1,param_2,0x1428,(char *)s_String_reference_out_of_range_28d3_28cc + 7
                       );
  if ((uVar1 | in_DX) == 0) {
    FUN_1928_07ab((char *)s_File_open_error_28d3_1418,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7,0,0);
    return 1;
  }
  FUN_1000_2c70(param_3,param_4,1,param_5,uVar1,in_DX);
  FUN_1000_258a(uVar1,in_DX);
  return 0;
}



// Function: FUN_2229_006c

undefined2 __cdecl16far
FUN_2229_006c(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5)

{
  uint uVar1;
  uint in_DX;
  
  uVar1 = FUN_1000_2aa3(param_1,param_2,0x142b,(char *)s_String_reference_out_of_range_28d3_28cc + 7
                       );
  if ((uVar1 | in_DX) == 0) {
    FUN_1928_07ab((char *)s_File_open_error_28d3_1418,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7,0,0);
    return 1;
  }
  FUN_1000_1ce3(uVar1,in_DX);
  FUN_1000_2efb(param_3,param_4,1,param_5,uVar1,in_DX);
  FUN_1000_258a(uVar1,in_DX);
  return 0;
}



// Function: FUN_2229_00da

/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

void __cdecl16far FUN_2229_00da(void)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 in_DX;
  int iVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined4 *puVar8;
  undefined *puVar10;
  undefined4 *puVar11;
  undefined *puVar13;
  undefined4 *puVar14;
  undefined *puVar16;
  undefined4 *puVar17;
  undefined *puVar19;
  undefined4 *puVar20;
  undefined *puVar22;
  undefined4 *puVar23;
  undefined *puVar25;
  undefined4 *puVar26;
  undefined *puVar28;
  undefined4 *puVar29;
  undefined *puVar31;
  undefined4 *puVar32;
  undefined *puVar34;
  undefined4 *puVar35;
  undefined4 in_ESP;
  undefined4 *puVar37;
  undefined2 unaff_BP;
  undefined2 unaff_SI;
  undefined2 unaff_SS;
  undefined4 *puVar9;
  undefined4 *puVar12;
  undefined4 *puVar15;
  undefined4 *puVar18;
  undefined4 *puVar21;
  undefined4 *puVar24;
  undefined4 *puVar27;
  undefined4 *puVar30;
  undefined4 *puVar33;
  undefined4 *puVar36;
  
  iVar4 = (int)in_ESP;
  uVar3 = (undefined2)((ulong)in_ESP >> 0x10);
  *(undefined2 *)(iVar4 + -2) = unaff_BP;
  *(undefined2 *)(iVar4 + -0x6a) = unaff_SI;
  iVar1 = *(int *)(iVar4 + 4);
  *(char **)(iVar4 + -4) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  *(undefined2 *)(iVar4 + -6) = 0x142e;
  if (iVar1 == 0) {
    *(undefined2 *)(iVar4 + -0x6c) = 0x32;
    *(undefined2 *)(iVar4 + -0x6e) = unaff_SS;
    *(int *)(iVar4 + -0x70) = iVar4 + -0x68;
    *(char **)(iVar4 + -0x72) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    *(char **)(iVar4 + -0x74) = (char *)s_flint1_cfg_28d3_143b;
  }
  else {
    *(undefined2 *)(iVar4 + -0x6c) = 0x32;
    *(undefined2 *)(iVar4 + -0x6e) = unaff_SS;
    *(int *)(iVar4 + -0x70) = iVar4 + -0x68;
    *(char **)(iVar4 + -0x72) = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    *(undefined2 *)(iVar4 + -0x74) = 0x1430;
  }
  *(undefined2 *)(iVar4 + -0x76) = 0x2229;
  puVar5 = (undefined *)(iVar4 + -0x78);
  *(undefined2 *)(iVar4 + -0x78) = 0x239a;
  FUN_2229_000c();
  *(undefined2 *)(puVar5 + 0xc) = *(undefined2 *)(iVar4 + -4);
  *(undefined2 *)(puVar5 + 10) = *(undefined2 *)(iVar4 + -6);
  *(undefined2 *)(puVar5 + 8) = unaff_SS;
  *(int *)(puVar5 + 6) = iVar4 + -0x68;
  *(undefined2 *)(puVar5 + 4) = 0x2229;
  puVar6 = puVar5 + 2;
  *(undefined2 *)(puVar5 + 2) = 0x23ad;
  uVar2 = FUN_1000_19a6();
  *(undefined2 *)(iVar4 + -8) = in_DX;
  *(undefined2 *)(iVar4 + -10) = uVar2;
  *(undefined4 *)(iVar4 + -0xe) = *(undefined4 *)(iVar4 + -10);
  *(undefined2 *)(puVar6 + 10) = *(undefined2 *)(iVar4 + -0xc);
  *(undefined2 *)(puVar6 + 8) = *(undefined2 *)(iVar4 + -0xe);
  *(undefined2 *)(puVar6 + 6) = 0x1000;
  puVar7 = puVar6 + 4;
  *(undefined2 *)(puVar6 + 4) = 0x23c9;
  DAT_28d3_2968 = FUN_1000_40d1();
  *(undefined2 *)(puVar7 + 6) = *(undefined2 *)(iVar4 + -4);
  *(undefined2 *)(puVar7 + 4) = *(undefined2 *)(iVar4 + -6);
  puVar37 = (undefined4 *)(CONCAT22(uVar3,(int)puVar7 + 4) + -4);
  *puVar37 = 0;
  puVar8 = (undefined4 *)puVar37;
  uVar2 = (undefined2)((ulong)puVar37 >> 0x10);
  *(undefined2 *)((int)puVar8 + -2) = 0x1000;
  puVar9 = puVar8 + -1;
  *(undefined2 *)(puVar8 + -1) = 0x23dd;
  uVar3 = FUN_1000_19a6();
  *(undefined2 *)(iVar4 + -8) = in_DX;
  *(undefined2 *)(iVar4 + -10) = uVar3;
  *(undefined4 *)(iVar4 + -0x12) = *(undefined4 *)(iVar4 + -10);
  *(undefined2 *)((int)puVar9 + 10) = *(undefined2 *)(iVar4 + -0x10);
  *(undefined2 *)((int)puVar9 + 8) = *(undefined2 *)(iVar4 + -0x12);
  *(undefined2 *)((int)puVar9 + 6) = 0x1000;
  puVar10 = (undefined *)((int)puVar9 + 4);
  *(undefined2 *)((int)puVar9 + 4) = 0x23f9;
  DAT_28d3_296a = FUN_1000_40d1();
  *(undefined2 *)(puVar10 + 6) = *(undefined2 *)(iVar4 + -4);
  *(undefined2 *)(puVar10 + 4) = *(undefined2 *)(iVar4 + -6);
  puVar37 = (undefined4 *)((undefined *)CONCAT22(uVar2,puVar10 + 4) + -4);
  *puVar37 = 0;
  puVar11 = (undefined4 *)puVar37;
  uVar2 = (undefined2)((ulong)puVar37 >> 0x10);
  *(undefined2 *)((int)puVar11 + -2) = 0x1000;
  puVar12 = puVar11 + -1;
  *(undefined2 *)(puVar11 + -1) = 0x240d;
  uVar3 = FUN_1000_19a6();
  *(undefined2 *)(iVar4 + -8) = in_DX;
  *(undefined2 *)(iVar4 + -10) = uVar3;
  *(undefined4 *)(iVar4 + -0x16) = *(undefined4 *)(iVar4 + -10);
  *(undefined2 *)((int)puVar12 + 10) = *(undefined2 *)(iVar4 + -0x14);
  *(undefined2 *)((int)puVar12 + 8) = *(undefined2 *)(iVar4 + -0x16);
  *(undefined2 *)((int)puVar12 + 6) = 0x1000;
  puVar13 = (undefined *)((int)puVar12 + 4);
  *(undefined2 *)((int)puVar12 + 4) = 0x2429;
  DAT_28d3_296c = FUN_1000_40d1();
  *(undefined2 *)(puVar13 + 6) = *(undefined2 *)(iVar4 + -4);
  *(undefined2 *)(puVar13 + 4) = *(undefined2 *)(iVar4 + -6);
  puVar37 = (undefined4 *)((undefined *)CONCAT22(uVar2,puVar13 + 4) + -4);
  *puVar37 = 0;
  puVar14 = (undefined4 *)puVar37;
  uVar2 = (undefined2)((ulong)puVar37 >> 0x10);
  *(undefined2 *)((int)puVar14 + -2) = 0x1000;
  puVar15 = puVar14 + -1;
  *(undefined2 *)(puVar14 + -1) = 0x243d;
  uVar3 = FUN_1000_19a6();
  *(undefined2 *)(iVar4 + -8) = in_DX;
  *(undefined2 *)(iVar4 + -10) = uVar3;
  *(undefined4 *)(iVar4 + -0x1a) = *(undefined4 *)(iVar4 + -10);
  *(undefined2 *)((int)puVar15 + 10) = *(undefined2 *)(iVar4 + -0x18);
  *(undefined2 *)((int)puVar15 + 8) = *(undefined2 *)(iVar4 + -0x1a);
  *(undefined2 *)((int)puVar15 + 6) = 0x1000;
  puVar16 = (undefined *)((int)puVar15 + 4);
  *(undefined2 *)((int)puVar15 + 4) = 0x2459;
  DAT_28d3_2996 = FUN_1000_40d1();
  *(undefined2 *)(puVar16 + 6) = *(undefined2 *)(iVar4 + -4);
  *(undefined2 *)(puVar16 + 4) = *(undefined2 *)(iVar4 + -6);
  puVar37 = (undefined4 *)((undefined *)CONCAT22(uVar2,puVar16 + 4) + -4);
  *puVar37 = 0;
  puVar17 = (undefined4 *)puVar37;
  uVar2 = (undefined2)((ulong)puVar37 >> 0x10);
  *(undefined2 *)((int)puVar17 + -2) = 0x1000;
  puVar18 = puVar17 + -1;
  *(undefined2 *)(puVar17 + -1) = 0x246d;
  uVar3 = FUN_1000_19a6();
  *(undefined2 *)(iVar4 + -8) = in_DX;
  *(undefined2 *)(iVar4 + -10) = uVar3;
  *(undefined4 *)(iVar4 + -0x1e) = *(undefined4 *)(iVar4 + -10);
  *(undefined2 *)((int)puVar18 + 10) = *(undefined2 *)(iVar4 + -0x1c);
  *(undefined2 *)((int)puVar18 + 8) = *(undefined2 *)(iVar4 + -0x1e);
  *(undefined2 *)((int)puVar18 + 6) = 0x1000;
  puVar19 = (undefined *)((int)puVar18 + 4);
  *(undefined2 *)((int)puVar18 + 4) = 0x2489;
  DAT_28d3_2988 = FUN_1000_40d1();
  *(undefined2 *)(puVar19 + 6) = *(undefined2 *)(iVar4 + -4);
  *(undefined2 *)(puVar19 + 4) = *(undefined2 *)(iVar4 + -6);
  puVar37 = (undefined4 *)((undefined *)CONCAT22(uVar2,puVar19 + 4) + -4);
  *puVar37 = 0;
  puVar20 = (undefined4 *)puVar37;
  uVar2 = (undefined2)((ulong)puVar37 >> 0x10);
  *(undefined2 *)((int)puVar20 + -2) = 0x1000;
  puVar21 = puVar20 + -1;
  *(undefined2 *)(puVar20 + -1) = 0x249d;
  uVar3 = FUN_1000_19a6();
  *(undefined2 *)(iVar4 + -8) = in_DX;
  *(undefined2 *)(iVar4 + -10) = uVar3;
  *(undefined4 *)(iVar4 + -0x22) = *(undefined4 *)(iVar4 + -10);
  *(undefined2 *)((int)puVar21 + 10) = *(undefined2 *)(iVar4 + -0x20);
  *(undefined2 *)((int)puVar21 + 8) = *(undefined2 *)(iVar4 + -0x22);
  *(undefined2 *)((int)puVar21 + 6) = 0x1000;
  puVar22 = (undefined *)((int)puVar21 + 4);
  *(undefined2 *)((int)puVar21 + 4) = 0x24b9;
  DAT_28d3_298a = FUN_1000_40d1();
  *(undefined2 *)(puVar22 + 6) = *(undefined2 *)(iVar4 + -4);
  *(undefined2 *)(puVar22 + 4) = *(undefined2 *)(iVar4 + -6);
  puVar37 = (undefined4 *)((undefined *)CONCAT22(uVar2,puVar22 + 4) + -4);
  *puVar37 = 0;
  puVar23 = (undefined4 *)puVar37;
  uVar2 = (undefined2)((ulong)puVar37 >> 0x10);
  *(undefined2 *)((int)puVar23 + -2) = 0x1000;
  puVar24 = puVar23 + -1;
  *(undefined2 *)(puVar23 + -1) = 0x24cd;
  uVar3 = FUN_1000_19a6();
  *(undefined2 *)(iVar4 + -8) = in_DX;
  *(undefined2 *)(iVar4 + -10) = uVar3;
  *(undefined4 *)(iVar4 + -0x26) = *(undefined4 *)(iVar4 + -10);
  *(undefined2 *)((int)puVar24 + 10) = *(undefined2 *)(iVar4 + -0x24);
  *(undefined2 *)((int)puVar24 + 8) = *(undefined2 *)(iVar4 + -0x26);
  *(undefined2 *)((int)puVar24 + 6) = 0x1000;
  puVar25 = (undefined *)((int)puVar24 + 4);
  *(undefined2 *)((int)puVar24 + 4) = 0x24e9;
  DAT_28d3_298c = FUN_1000_40d1();
  *(undefined2 *)(puVar25 + 6) = *(undefined2 *)(iVar4 + -4);
  *(undefined2 *)(puVar25 + 4) = *(undefined2 *)(iVar4 + -6);
  puVar37 = (undefined4 *)((undefined *)CONCAT22(uVar2,puVar25 + 4) + -4);
  *puVar37 = 0;
  puVar26 = (undefined4 *)puVar37;
  uVar2 = (undefined2)((ulong)puVar37 >> 0x10);
  *(undefined2 *)((int)puVar26 + -2) = 0x1000;
  puVar27 = puVar26 + -1;
  *(undefined2 *)(puVar26 + -1) = 0x24fd;
  uVar3 = FUN_1000_19a6();
  *(undefined2 *)(iVar4 + -8) = in_DX;
  *(undefined2 *)(iVar4 + -10) = uVar3;
  *(undefined4 *)(iVar4 + -0x2a) = *(undefined4 *)(iVar4 + -10);
  *(undefined2 *)((int)puVar27 + 10) = *(undefined2 *)(iVar4 + -0x28);
  *(undefined2 *)((int)puVar27 + 8) = *(undefined2 *)(iVar4 + -0x2a);
  *(undefined2 *)((int)puVar27 + 6) = 0x1000;
  puVar28 = (undefined *)((int)puVar27 + 4);
  *(undefined2 *)((int)puVar27 + 4) = 0x2519;
  DAT_28d3_298e = FUN_1000_40d1();
  *(undefined2 *)(puVar28 + 6) = *(undefined2 *)(iVar4 + -4);
  *(undefined2 *)(puVar28 + 4) = *(undefined2 *)(iVar4 + -6);
  puVar37 = (undefined4 *)((undefined *)CONCAT22(uVar2,puVar28 + 4) + -4);
  *puVar37 = 0;
  puVar29 = (undefined4 *)puVar37;
  uVar2 = (undefined2)((ulong)puVar37 >> 0x10);
  *(undefined2 *)((int)puVar29 + -2) = 0x1000;
  puVar30 = puVar29 + -1;
  *(undefined2 *)(puVar29 + -1) = 0x252d;
  uVar3 = FUN_1000_19a6();
  *(undefined2 *)(iVar4 + -8) = in_DX;
  *(undefined2 *)(iVar4 + -10) = uVar3;
  *(undefined4 *)(iVar4 + -0x2e) = *(undefined4 *)(iVar4 + -10);
  *(undefined2 *)((int)puVar30 + 10) = *(undefined2 *)(iVar4 + -0x2c);
  *(undefined2 *)((int)puVar30 + 8) = *(undefined2 *)(iVar4 + -0x2e);
  *(undefined2 *)((int)puVar30 + 6) = 0x1000;
  puVar31 = (undefined *)((int)puVar30 + 4);
  *(undefined2 *)((int)puVar30 + 4) = 0x2549;
  DAT_28d3_2994 = FUN_1000_40d1();
  *(undefined2 *)(puVar31 + 6) = *(undefined2 *)(iVar4 + -4);
  *(undefined2 *)(puVar31 + 4) = *(undefined2 *)(iVar4 + -6);
  puVar37 = (undefined4 *)((undefined *)CONCAT22(uVar2,puVar31 + 4) + -4);
  *puVar37 = 0;
  puVar32 = (undefined4 *)puVar37;
  uVar2 = (undefined2)((ulong)puVar37 >> 0x10);
  *(undefined2 *)((int)puVar32 + -2) = 0x1000;
  puVar33 = puVar32 + -1;
  *(undefined2 *)(puVar32 + -1) = 0x255d;
  uVar3 = FUN_1000_19a6();
  *(undefined2 *)(iVar4 + -8) = in_DX;
  *(undefined2 *)(iVar4 + -10) = uVar3;
  *(undefined4 *)(iVar4 + -0x32) = *(undefined4 *)(iVar4 + -10);
  *(undefined2 *)((int)puVar33 + 10) = *(undefined2 *)(iVar4 + -0x30);
  *(undefined2 *)((int)puVar33 + 8) = *(undefined2 *)(iVar4 + -0x32);
  *(undefined2 *)((int)puVar33 + 6) = 0x1000;
  puVar34 = (undefined *)((int)puVar33 + 4);
  *(undefined2 *)((int)puVar33 + 4) = 0x2579;
  DAT_28d3_57ea = FUN_1000_40d1();
  if (iVar1 != 0) {
    *(undefined2 *)(puVar34 + 6) = *(undefined2 *)(iVar4 + -4);
    *(undefined2 *)(puVar34 + 4) = *(undefined2 *)(iVar4 + -6);
    *(undefined4 *)((undefined *)CONCAT22(uVar2,puVar34 + 4) + -4) = 0;
    puVar35 = (undefined4 *)((undefined *)CONCAT22(uVar2,puVar34 + 4) + -4);
    *(undefined2 *)((int)puVar35 + -2) = 0x1000;
    puVar36 = puVar35 + -1;
    *(undefined2 *)(puVar35 + -1) = 0x2591;
    uVar3 = FUN_1000_19a6();
    *(undefined2 *)(iVar4 + -8) = in_DX;
    *(undefined2 *)(iVar4 + -10) = uVar3;
    *(undefined4 *)(iVar4 + -0x36) = *(undefined4 *)(iVar4 + -10);
    *(undefined2 *)((int)puVar36 + 10) = *(undefined2 *)(iVar4 + -0x34);
    *(undefined2 *)((int)puVar36 + 8) = *(undefined2 *)(iVar4 + -0x36);
    *(undefined2 *)((int)puVar36 + 6) = 0x1000;
    *(undefined2 *)((int)puVar36 + 4) = 0x25ad;
    DAT_28d3_29b8 = FUN_1000_40d1();
  }
  return;
}



// Function: FUN_2229_0326

void __cdecl16far FUN_2229_0326(void)

{
  uint in_DX;
  undefined local_50 [66];
  byte local_e;
  byte local_d;
  byte local_c;
  byte local_b;
  byte local_a;
  byte local_9;
  byte local_8;
  byte local_7;
  uint local_6;
  uint local_4;
  
  FUN_2229_04e4();
  FUN_1000_1bec(local_50);
  FUN_1000_1f49(0x29de,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  local_6 = FUN_1000_2aa3((char *)s_flash_dat_28d3_1446,
                          (char *)s_String_reference_out_of_range_28d3_28cc + 7,0x1450,
                          (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  local_4 = in_DX;
  if ((local_6 | in_DX) == 0) {
    FUN_1928_07ab((char *)s_File_open_error_28d3_1418,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7,0,0);
  }
  FUN_1000_2c70(&local_e);
  FUN_1000_258a(local_6,local_4);
  DAT_28d3_4fe8 =
       (ulong)local_e * 0x1000000 + (ulong)local_d * 0x10000 + (ulong)local_c * 0x100 +
       (ulong)local_b;
  DAT_28d3_4fec =
       (ulong)local_a * 0x1000000 + (ulong)local_9 * 0x10000 + (ulong)local_8 * 0x100 +
       (ulong)local_7;
  FUN_1000_1f49(local_50);
  return;
}



// Function: FUN_2229_04e4

void __cdecl16far FUN_2229_04e4(void)

{
  char cVar1;
  
  FUN_1000_1bec((undefined1 *)&DAT_28d3_5796,(char *)s_String_reference_out_of_range_28d3_28cc + 7,
                0x1460,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  cVar1 = FUN_1000_1d24();
  DAT_28d3_5796 = cVar1 + 'A';
  FUN_1000_1f65(0,0x5799,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  return;
}



// Function: FUN_2229_062c

void __cdecl16far FUN_2229_062c(void)

{
  undefined uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  for (iVar2 = 0; iVar5 = iVar2, iVar2 < DAT_28d3_57e8; iVar2 = iVar2 + 1) {
    while (iVar5 = iVar5 + 1, iVar5 <= DAT_28d3_57e8) {
      iVar3 = 0;
      do {
        if ((char)((undefined1 *)&DAT_28d3_4ff8)[iVar5 * 0xd + iVar3] <
            (char)((undefined1 *)&DAT_28d3_4ff8)[iVar2 * 0xd + iVar3]) {
          iVar3 = 0;
          do {
            uVar1 = ((undefined1 *)&DAT_28d3_4ff8)[iVar5 * 0xd + iVar3];
            iVar4 = iVar2 * 0xd + iVar3;
            ((undefined1 *)&DAT_28d3_4ff8)[iVar5 * 0xd + iVar3] =
                 ((undefined1 *)&DAT_28d3_4ff8)[iVar4];
            ((undefined1 *)&DAT_28d3_4ff8)[iVar4] = uVar1;
            iVar3 = iVar3 + 1;
          } while (iVar3 < 0xd);
          iVar3 = 8;
        }
        if ((char)((undefined1 *)&DAT_28d3_4ff8)[iVar2 * 0xd + iVar3] <
            (char)((undefined1 *)&DAT_28d3_4ff8)[iVar5 * 0xd + iVar3]) {
          iVar3 = 8;
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < 8);
    }
  }
  return;
}



// Function: FUN_2229_06c8

void __cdecl16far FUN_2229_06c8(void)

{
  undefined uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if ((DAT_28d3_550c == '.') && (DAT_28d3_550d == '.')) {
    iVar3 = 1;
  }
  else {
    iVar3 = 0;
  }
  for (; iVar4 = iVar3, iVar3 < DAT_28d3_57e6; iVar3 = iVar3 + 1) {
    while (iVar4 = iVar4 + 1, iVar4 <= DAT_28d3_57e6) {
      iVar2 = 0;
      do {
        if ((char)((undefined1 *)&DAT_28d3_550c)[iVar4 * 0xd + iVar2] <
            (char)((undefined1 *)&DAT_28d3_550c)[iVar3 * 0xd + iVar2]) {
          iVar2 = 0;
          do {
            uVar1 = ((undefined1 *)&DAT_28d3_550c)[iVar4 * 0xd + iVar2];
            iVar5 = iVar3 * 0xd + iVar2;
            ((undefined1 *)&DAT_28d3_550c)[iVar4 * 0xd + iVar2] =
                 ((undefined1 *)&DAT_28d3_550c)[iVar5];
            ((undefined1 *)&DAT_28d3_550c)[iVar5] = uVar1;
            iVar2 = iVar2 + 1;
          } while (iVar2 < 0xd);
          iVar2 = 8;
        }
        if ((char)((undefined1 *)&DAT_28d3_550c)[iVar3 * 0xd + iVar2] <
            (char)((undefined1 *)&DAT_28d3_550c)[iVar4 * 0xd + iVar2]) {
          iVar2 = 8;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 8);
    }
  }
  return;
}



// Function: FUN_2229_0a8b

int __cdecl16far FUN_2229_0a8b(void)

{
  uint uVar1;
  uint in_DX;
  int iVar2;
  int iVar3;
  undefined local_16 [16];
  uint local_6;
  uint local_4;
  
  iVar2 = 0;
  do {
    iVar3 = 0;
    do {
      ((undefined1 *)&DAT_28d3_4cb6)[iVar2 * 0x10 + iVar3] = 0;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x10);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x32);
  local_6 = FUN_1000_2aa3((char *)s__Aflint_gls_28d3_1476 + 2,
                          (char *)s_String_reference_out_of_range_28d3_28cc + 7,0x1482,
                          (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  if ((local_6 | in_DX) == 0) {
    FUN_1928_07ab((char *)s_File_open_error_28d3_1418,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7,0,0);
    iVar2 = 0;
  }
  else {
    iVar2 = 0;
    local_4 = in_DX;
    while( true ) {
      uVar1 = FUN_1000_2726(local_16);
      if ((uVar1 | in_DX) == 0) break;
      FUN_1000_1bec((undefined1 *)&DAT_28d3_4cb6 + iVar2 * 0x10,
                    (char *)s_String_reference_out_of_range_28d3_28cc + 7,local_16);
      iVar2 = iVar2 + 1;
    }
    FUN_1000_258a(local_6,local_4);
  }
  return iVar2;
}



// Function: FUN_2229_1502

/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */

undefined2 __cdecl16far FUN_2229_1502(void)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined2 *puVar6;
  undefined2 *puVar7;
  undefined2 *puVar8;
  undefined4 in_ESP;
  undefined2 uVar9;
  undefined2 unaff_BP;
  undefined2 unaff_SS;
  
  iVar4 = (int)in_ESP;
  uVar9 = (undefined2)((ulong)in_ESP >> 0x10);
  *(undefined2 *)(iVar4 + -2) = unaff_BP;
  *(undefined2 *)(iVar4 + -0x14) = 0x6662;
  *(undefined2 *)(iVar4 + -0x16) = 0x2229;
  puVar5 = (undefined2 *)(iVar4 + -0x18);
  *(undefined2 *)(iVar4 + -0x18) = 0x37aa;
  uVar1 = FUN_1000_0f76();
  *(undefined2 *)(iVar4 + -0x12) = uVar1;
  *(undefined2 *)(iVar4 + -0x10) = DAT_28d3_29aa;
  *(undefined2 *)(iVar4 + -0xe) = DAT_28d3_29ac;
  *(undefined2 *)(iVar4 + -0xc) = DAT_28d3_29ae;
  *(undefined2 *)(iVar4 + -10) = (int)(DAT_28d3_2984 / 0x10000);
  uVar3 = (uint)(DAT_28d3_2984 % 0x10000);
  *(uint *)(iVar4 + -8) = uVar3;
  puVar5[1] = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  *puVar5 = 0x1577;
  puVar5[-1] = *(undefined2 *)(iVar4 + 6);
  puVar5[-2] = *(undefined2 *)(iVar4 + 4);
  puVar5[-3] = 0x1000;
  puVar6 = puVar5 + -4;
  puVar5[-4] = 0x37f2;
  uVar2 = FUN_1000_2aa3();
  *(uint *)(iVar4 + -4) = uVar3;
  *(uint *)(iVar4 + -6) = uVar2;
  if ((uVar2 | uVar3) == 0) {
    puVar6[5] = 0;
    puVar6[4] = 0;
    puVar6[3] = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    puVar6[2] = (char *)s_File_open_error_28d3_1418;
    puVar6[1] = 0x1000;
    *puVar6 = 0x380c;
    FUN_1928_07ab();
    return 1;
  }
  puVar6[5] = *(undefined2 *)(iVar4 + -4);
  puVar6[4] = *(undefined2 *)(iVar4 + -6);
  puVar6[3] = 0x1000;
  puVar7 = puVar6 + 2;
  puVar6[2] = 0x381f;
  FUN_1000_1ce3();
  puVar7[3] = *(undefined2 *)(iVar4 + -4);
  puVar7[2] = *(undefined2 *)(iVar4 + -6);
  puVar7[1] = 7;
  *puVar7 = 2;
  puVar7[-1] = unaff_SS;
  puVar7[-2] = iVar4 + -0x14;
  puVar7[-3] = 0x1000;
  puVar8 = puVar7 + -4;
  puVar7[-4] = 0x3836;
  FUN_1000_2efb();
  puVar8[7] = *(undefined2 *)(iVar4 + -4);
  puVar8[6] = *(undefined2 *)(iVar4 + -6);
  *(long *)(puVar8 + 4) = DAT_28d3_2984 / 2;
  puVar8[5] = (int)*(undefined4 *)CONCAT22(uVar9,puVar8 + 4) + (int)(DAT_28d3_2984 % 2);
  puVar8[4] = 0xc;
  puVar8[3] = DAT_28d3_2a42;
  puVar8[2] = DAT_28d3_2a40;
  puVar8[1] = 0x1000;
  *puVar8 = 0x3873;
  FUN_1000_2efb();
  *(undefined2 *)((int)puVar8 + 0xe) = *(undefined2 *)(iVar4 + -4);
  *(undefined2 *)((int)puVar8 + 0xc) = *(undefined2 *)(iVar4 + -6);
  *(undefined2 *)((int)puVar8 + 10) = 0x1000;
  *(undefined2 *)((int)puVar8 + 8) = 0x3881;
  FUN_1000_258a();
  return 0;
}



// Function: FUN_2229_15f8

undefined2 __cdecl16far FUN_2229_15f8(undefined2 param_1,undefined2 param_2)

{
  uint in_DX;
  int local_1c;
  uint local_1a;
  undefined2 local_18;
  undefined2 local_16;
  undefined2 local_14;
  undefined2 local_12;
  uint local_10;
  ulong local_e;
  ulong local_a;
  uint local_6;
  uint local_4;
  
  local_6 = FUN_1000_2aa3(param_1,param_2,0x157a,
                          (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  if ((local_6 | in_DX) == 0) {
    FUN_1928_07ab((char *)s_File_open_error_28d3_1418,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7,0,0);
    return 1;
  }
  local_4 = in_DX;
  FUN_1000_2c70(&local_1c);
  if (local_1c != 0x6662) {
    FUN_1000_258a(local_6,local_4);
    return 0;
  }
  local_e = (ulong)local_1a;
  DAT_28d3_29a2 = (double)((float)local_e / DAT_28d3_1573);
  DAT_28d3_29aa = local_18;
  DAT_28d3_29ac = local_16;
  DAT_28d3_29ae = local_14;
  local_a = CONCAT22(local_12,local_10);
  if (DAT_28d3_2a3c < local_a) {
    FUN_1000_258a(local_6,local_4);
    return 0xffff;
  }
  FUN_1000_2c70(DAT_28d3_2a40,DAT_28d3_2a42,0xc,(int)(local_a >> 1) + (local_10 & 1),local_6,local_4
               );
  FUN_1000_258a(local_6,local_4);
  return (undefined2)local_a;
}



// Function: FUN_23c2_0001

void __cdecl16far
FUN_23c2_0001(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  DAT_28d3_57ec = 9;
  DAT_28d3_57ee = param_2;
  DAT_28d3_57f0 = param_1;
  DAT_28d3_57fc = param_4;
  DAT_28d3_57f2 = param_3;
  FUN_1000_5290(0x33,(undefined2 *)&DAT_28d3_57ec,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7,(undefined2 *)&DAT_28d3_57ec,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7,(undefined2 *)&DAT_28d3_57fc,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  return;
}



// Function: FUN_23c2_003a

void __cdecl16far FUN_23c2_003a(void)

{
  DAT_28d3_57ec = 0;
  FUN_1000_525b(0x33,(undefined2 *)&DAT_28d3_57ec,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7,(undefined2 *)&DAT_28d3_57ec,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  if (DAT_28d3_57ec == 0) {
    FUN_1000_3431((char *)s_no_mouse___28d3_1580,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7);
    FUN_1000_4d6e(0xffff);
  }
  return;
}



// Function: FUN_23c2_0072

void __cdecl16far FUN_23c2_0072(undefined *param_1)

{
  undefined2 uVar1;
  
  DAT_28d3_57ec = 3;
  FUN_1000_525b(0x33,(undefined2 *)&DAT_28d3_57ec,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7,(undefined2 *)&DAT_28d3_57ec,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  *param_1 = (undefined)DAT_28d3_57ee;
  uVar1 = (undefined2)((ulong)param_1 >> 0x10);
  *(undefined2 *)((undefined *)param_1 + 1) = DAT_28d3_57f0;
  *(undefined2 *)((undefined *)param_1 + 3) = DAT_28d3_57f2;
  return;
}



// Function: FUN_23c2_00ac

void __cdecl16far FUN_23c2_00ac(undefined2 param_1,undefined2 param_2)

{
  DAT_28d3_57ec = 4;
  DAT_28d3_57f0 = param_1;
  DAT_28d3_57f2 = param_2;
  FUN_1000_525b(0x33,(undefined2 *)&DAT_28d3_57ec,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7,(undefined2 *)&DAT_28d3_57ec,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  return;
}



// Function: FUN_23c2_00d5

int __cdecl16far FUN_23c2_00d5(char *param_1)

{
  undefined2 uVar1;
  
  DAT_28d3_57ec = 6;
  DAT_28d3_57ee = (int)*param_1;
  FUN_1000_525b(0x33,(undefined2 *)&DAT_28d3_57ec,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7,(undefined2 *)&DAT_28d3_57ec,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  uVar1 = (undefined2)((ulong)param_1 >> 0x10);
  *(undefined2 *)((char *)param_1 + 1) = DAT_28d3_57f0;
  *(undefined2 *)((char *)param_1 + 3) = DAT_28d3_57f2;
  return DAT_28d3_57ee;
}



// Function: FUN_23c2_0113

void __cdecl16far FUN_23c2_0113(undefined2 param_1,undefined2 param_2)

{
  FUN_1000_4c8f(param_1);
  FUN_1000_537f(param_2);
  FUN_1000_4cbf();
  return;
}



// Function: FUN_23c2_012f

int __cdecl16far FUN_23c2_012f(int param_1)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  undefined2 uVar4;
  char cVar5;
  char local_8;
  int local_7;
  int local_5;
  
  pcVar1 = (code *)swi(0x33);
  (*pcVar1)();
  do {
    if (param_1 != 0) {
      FUN_23c2_0113(0x834,0x46);
      FUN_23c2_0113(3000,0x46);
    }
    local_8 = '\0';
    iVar2 = FUN_23c2_00d5(&local_8);
    if (iVar2 != 0) {
LAB_23c2_01bc:
      DAT_28d3_580a = 0;
      DAT_28d3_580c = 0;
      pcVar1 = (code *)swi(0x33);
      (*pcVar1)();
      return 1;
    }
    FUN_23c2_0072(&local_8);
    if (local_8 == '\x01') {
      if (DAT_28d3_580a == 0) {
        DAT_28d3_580a = 1;
LAB_23c2_01f6:
        DAT_28d3_5806 = local_7;
        DAT_28d3_5808 = local_5;
        pcVar1 = (code *)swi(0x33);
        (*pcVar1)();
        return 0;
      }
      if (DAT_28d3_580c == 0) {
        DAT_28d3_580c = 1;
        iVar2 = 0;
        do {
          FUN_1000_537f(10);
          local_8 = '\0';
          iVar3 = FUN_23c2_00d5(&local_8);
          if (iVar3 != 0) goto LAB_23c2_01bc;
          iVar2 = iVar2 + 1;
        } while (iVar2 < 0x32);
      }
      FUN_1000_537f(10);
      FUN_23c2_0072(&local_8);
      if (local_8 == '\x01') goto LAB_23c2_01f6;
    }
    iVar2 = FUN_1000_0fe0(1);
    if (iVar2 != 0) {
      uVar4 = FUN_1000_0fe0(0);
      cVar5 = (char)uVar4;
      if (cVar5 == '\0') {
        cVar5 = (char)((uint)uVar4 >> 8);
        if (cVar5 == 'K') {
          local_7 = local_7 + -8;
        }
        else if (cVar5 == 'H') {
          local_5 = local_5 + -8;
        }
        else if (cVar5 == 'M') {
          local_7 = local_7 + 8;
        }
        else if (cVar5 == 'P') {
          local_5 = local_5 + 8;
        }
        else {
          if ((':' < cVar5) && (cVar5 < 'R')) {
            pcVar1 = (code *)swi(0x33);
            (*pcVar1)();
            return (int)(char)((uint)uVar4 >> 8);
          }
          FUN_23c2_0113(1000,100);
        }
        FUN_23c2_00ac(local_7,local_5);
      }
      else {
        if (cVar5 == '\x1b') {
          pcVar1 = (code *)swi(0x33);
          (*pcVar1)();
          return 0x1b;
        }
        if (cVar5 == '\r') {
          DAT_28d3_5806 = local_7;
          DAT_28d3_5808 = local_5;
          pcVar1 = (code *)swi(0x33);
          (*pcVar1)();
          return 0xd;
        }
        FUN_23c2_0113(1000,100);
      }
    }
    DAT_28d3_580a = 0;
    DAT_28d3_580c = 0;
  } while( true );
}



// Function: FUN_23f1_0000

char * FUN_23f1_0000(uint param_1)

{
  char *pcVar1;
  
  pcVar1 = (char *)&DAT_28d3_1902;
  DAT_28d3_1902 = 0;
  do {
    pcVar1 = pcVar1 + -1;
    *pcVar1 = (char)((ulong)param_1 % 10) + '0';
    param_1 = param_1 / 10;
  } while (param_1 != 0);
  return pcVar1;
}



// Function: FUN_23f1_0031

char * FUN_23f1_0031(char *param_1,char *param_2)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar3 = (char *)param_1;
  pcVar4 = (char *)param_2;
  do {
    pcVar1 = pcVar3;
    pcVar3 = pcVar3 + 1;
    cVar2 = *pcVar1;
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
    *pcVar1 = cVar2;
  } while (cVar2 != '\0');
  return param_2;
}



// Function: FUN_23f1_0050

int FUN_23f1_0050(int param_1,char *param_2,char *param_3)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  
  uVar6 = (undefined2)((ulong)param_3 >> 0x10);
  pcVar3 = (char *)param_3;
  uVar5 = (undefined2)((ulong)param_2 >> 0x10);
  pcVar4 = (char *)param_2;
  do {
    if (param_1 == 0) break;
    param_1 = param_1 + -1;
    pcVar2 = pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar1 = pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (*pcVar1 == *pcVar2);
  return (int)(char)(pcVar3[-1] - pcVar4[-1]);
}



// Function: FUN_23f1_0071

void FUN_23f1_0071(byte *param_1)

{
  byte bVar1;
  byte *pbVar2;
  undefined2 uVar3;
  
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  for (pbVar2 = (byte *)param_1; bVar1 = *pbVar2, bVar1 != 0; pbVar2 = pbVar2 + 1) {
    if ((0x60 < bVar1) && ((char)bVar1 < '{')) {
      *pbVar2 = bVar1 & 0x5f;
    }
  }
  return;
}



// Function: FUN_23f1_0094

char * FUN_23f1_0094(char *param_1)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  undefined2 uVar4;
  
  uVar4 = (undefined2)((ulong)param_1 >> 0x10);
  pcVar3 = (char *)param_1;
  iVar2 = -1;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar1 = pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (*pcVar1 != '\0');
  return (char *)CONCAT22(uVar4,pcVar3 + -1);
}



// Function: FUN_23f1_00ad

char * FUN_23f1_00ad(char *param_1,char *param_2,char *param_3)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  undefined2 uVar6;
  uint uVar7;
  
  uVar6 = (undefined2)((ulong)param_3 >> 0x10);
  pcVar4 = (char *)param_3;
  uVar7 = (uint)((ulong)param_2 >> 0x10);
  pcVar3 = (char *)param_2;
  pcVar5 = pcVar4;
  if ((uVar7 | (uint)pcVar3) != 0) {
    do {
      pcVar4 = pcVar5;
      pcVar1 = pcVar3;
      pcVar3 = pcVar3 + 1;
      cVar2 = *pcVar1;
      *pcVar4 = cVar2;
      pcVar5 = pcVar4 + 1;
    } while (cVar2 != '\0');
  }
  pcVar3 = (char *)param_1;
  do {
    pcVar5 = pcVar4;
    pcVar1 = pcVar3;
    pcVar3 = pcVar3 + 1;
    cVar2 = *pcVar1;
    *pcVar5 = cVar2;
    pcVar4 = pcVar5 + 1;
  } while (cVar2 != '\0');
  return (char *)CONCAT22(uVar6,pcVar5);
}



// Function: FUN_23f1_00db

void FUN_23f1_00db(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



// Function: FUN_23f1_00eb

void __cdecl16near FUN_23f1_00eb(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}



// Function: FUN_23f1_00f8

undefined2 FUN_23f1_00f8(undefined2 param_1,uint *param_2)

{
  code *pcVar1;
  undefined2 uVar2;
  uint uVar3;
  undefined2 unaff_BP;
  undefined in_CF;
  bool bVar4;
  undefined4 uVar5;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if ((bool)in_CF) {
    uVar2 = 0xfffd;
  }
  else {
    *(undefined2 *)&DAT_28d3_1903 = uVar2;
    bVar4 = false;
    pcVar1 = (code *)swi(0x21);
    uVar5 = (*pcVar1)();
    uVar3 = (uint)uVar5;
    if ((((bVar4) || (uVar3 == 0)) || ((int)((ulong)uVar5 >> 0x10) != 0)) || (0x7fff < uVar3)) {
      FUN_23f1_00eb();
      uVar2 = 0x403d;
    }
    else {
      *param_2 = uVar3;
      uVar2 = 0;
    }
  }
  return uVar2;
}



// Function: FUN_23f1_013d

undefined2 FUN_23f1_013d(void)

{
  code *pcVar1;
  char *pcVar2;
  bool bVar3;
  
  pcVar2 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  bVar3 = false;
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if (!bVar3) {
    pcVar2 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    if (!bVar3) {
      return 0;
    }
  }
  FUN_23f1_00eb();
  *(undefined2 *)&DAT_28d3_17a6 = 0xfff4;
  return 1;
}



// Function: FUN_23f1_0178

void __cdecl16near FUN_23f1_0178(undefined *param_1,undefined *param_2,int param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  
  puVar3 = (undefined *)param_2;
  puVar4 = (undefined *)param_1;
  for (; param_3 != 0; param_3 = param_3 + -1) {
    puVar2 = puVar4;
    puVar4 = puVar4 + 1;
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar2 = *puVar1;
  }
  return;
}



// Function: FUN_23f1_0193

/* WARNING: Instruction at (ram,0x00020001) overlaps instruction at (ram,0x00020000)
    */
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0x0002800c) */
/* WARNING: Type propagation algorithm not settling */

char * __cdecl16near FUN_23f1_0193(undefined2 param_1_00,undefined *param_1,undefined2 param_3)

{
  byte *pbVar1;
  char *pcVar2;
  undefined1 *puVar3;
  undefined uVar4;
  undefined *puVar5;
  undefined2 uVar6;
  code *pcVar7;
  undefined uVar8;
  byte bVar9;
  byte bVar11;
  char **ppcVar12;
  byte bVar15;
  uint uVar13;
  char *pcVar14;
  undefined uVar16;
  byte bVar17;
  int iVar18;
  int in_CX;
  char cVar19;
  uint in_DX;
  char *extraout_DX;
  undefined2 *puVar20;
  int *piVar21;
  undefined *puVar22;
  undefined1 *puVar23;
  uint uVar24;
  undefined *puVar25;
  int unaff_SI;
  uint *puVar26;
  uint *unaff_DI;
  undefined2 unaff_ES;
  undefined2 unaff_SS;
  bool bVar27;
  char in_AF;
  char *in_FPUStatusWord;
  char *pcStack_10;
  char *pcStack_e;
  char cVar10;
  
  pcStack_e = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  pcVar14 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  puVar22 = param_1 + 0x12;
  if ((undefined *)0x12 < puVar22) {
    uVar13 = FUN_23f1_0000();
    if ((uVar13 | 0x28d3) == 0) {
      pcVar14 = (char *)FUN_23f1_0031();
    }
    else {
      FUN_23f1_00ad();
      FUN_23f1_0031();
      pcVar14 = (char *)s_No_Error_28d3_1905;
    }
    return pcVar14;
  }
  puVar20 = (undefined2 *)((int)puVar22 * 2);
  cVar19 = (char)in_DX;
  bVar11 = (byte)((uint)puVar20 >> 8);
  switch(puVar22) {
  case (undefined *)0x0:
    pcVar7 = (code *)swi(0x10);
    pcVar14 = (char *)(*pcVar7)();
    return pcVar14;
  case (undefined *)0x1:
    DAT_28d3_17ec = 0;
    DAT_28d3_17ee = param_3;
    DAT_28d3_17f0 = 1;
    pcVar14 = (char *)FUN_23f1_1f60();
    return pcVar14;
  case (undefined *)0x2:
    return pcVar14;
  case (undefined *)0x3:
    if (((in_CX <= (int)unaff_DI) &&
        ((DAT_28d3_008a <= (int)puVar20 || (DAT_28d3_008a <= (int)in_DX)))) &&
       (((int)puVar20 <= DAT_28d3_008e || ((int)in_DX <= DAT_28d3_008e)))) {
      FUN_23f1_35f2();
      FUN_23f1_35f2();
      FUN_23f1_35f2();
      FUN_23f1_35f2();
      return extraout_DX;
    }
    return pcVar14;
  case (undefined *)0x4:
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  case (undefined *)0x5:
    while( true ) {
      bVar11 = (byte)((uint)pcVar14 >> 8);
      DAT_28d3_078a = DAT_28d3_078a | bVar11;
      *(char *)unaff_DI = (char)pcVar14;
      unaff_DI = (uint *)((int)unaff_DI + 1);
      puVar20 = (undefined2 *)((int)puVar20 + 1);
      in_CX = in_CX + -1;
      if (in_CX == 0) break;
      pcVar14 = (char *)CONCAT11(bVar11,*(undefined *)puVar20);
    }
    FUN_2001_04a0();
    uVar16 = DAT_28d3_0257;
    puVar23 = (undefined1 *)&DAT_28d3_0437;
    puVar22 = (undefined *)0x132;
    iVar18 = 8;
    do {
      puVar3 = puVar23;
      puVar23 = puVar23 + 1;
      uVar4 = *puVar3;
      pcVar14 = (char *)CONCAT11(uVar16,uVar4);
      cVar19 = '\x04';
      do {
        bVar11 = (byte)((uint)pcVar14 >> 8);
        bVar27 = (bool)(bVar11 & 1);
        uVar8 = 0;
        if (bVar27) {
          uVar8 = uVar4;
        }
        pcVar14 = (char *)CONCAT11(bVar11 >> 1 | bVar27 << 7,uVar8);
        puVar5 = puVar22;
        puVar22 = puVar22 + 1;
        *puVar5 = uVar8;
        cVar19 = cVar19 + -1;
      } while (cVar19 != '\0');
      iVar18 = iVar18 + -1;
    } while (iVar18 != 0);
    return pcVar14;
  case (undefined *)0x6:
    *(byte *)((int)puVar20 + (int)param_1) = *(byte *)((int)puVar20 + (int)param_1) ^ 0x28;
    *(char *)((int)unaff_DI + 1) = *(char *)((int)unaff_DI + 1) + (char)in_CX + '\x01';
    ((undefined *)((int)puVar20 + (int)param_1))[0x20] =
         ((undefined *)((int)puVar20 + (int)param_1))[0x20] & bVar11;
    *(byte *)((int)puVar20 + (int)param_1) = *(byte *)((int)puVar20 + (int)param_1) ^ 0x28;
    (&stack0xffff)[(int)param_1] = (&stack0xffff)[(int)param_1] + cVar19;
    ((undefined *)((int)puVar20 + (int)param_1))[0x20] =
         ((undefined *)((int)puVar20 + (int)param_1))[0x20] & (byte)puVar20;
    uVar24 = (uint)param_1 ^ unaff_DI[1];
    *(byte *)((int)puVar20 + uVar24) = *(byte *)((int)puVar20 + uVar24) ^ 0x28;
    in_CX = in_CX + 3;
    *(byte *)(unaff_DI + 0x29) = *(byte *)(unaff_DI + 0x29) & (byte)in_CX;
    puVar22 = (undefined *)(uVar24 - 1);
    puVar26 = unaff_DI + 1;
    *(byte *)(unaff_DI + -0x177e) = *(char *)(unaff_DI + -0x177e) + bVar11;
    bVar11 = bVar11 + (byte)in_CX;
    uVar13 = CONCAT11(bVar11,(byte)puVar20);
    pbVar1 = (byte *)(uVar13 + 2);
    bVar9 = *pbVar1;
    *pbVar1 = *pbVar1 + bVar11;
    *(undefined2 *)(puVar22 + uVar13) = 0x27f;
    *(undefined2 *)(puVar22 + uVar13) = 9000;
    in_DX = (in_DX - *(int *)(uVar24 + 0x810)) - (uint)CARRY1(bVar9,bVar11);
    ppcVar12 = (char **)param_1;
    break;
  case (undefined *)0x7:
    return pcVar14;
  case (undefined *)0x8:
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  case (undefined *)0x9:
    pcStack_10 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    uVar6 = *(undefined2 *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 7);
    uVar13 = *(uint *)(unaff_SI + -1);
    uVar16 = (undefined)(uVar13 >> 8);
    bVar11 = (char)uVar13 - 0x34;
    pcVar14 = pcStack_10;
    if (bVar11 < 8) {
      if (CONCAT11(uVar16,bVar11) == -0x1cfd) {
        *(undefined2 *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 = 0x4100;
        *(undefined2 *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 2) = 0x3f;
        *(undefined2 *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 0x25) = 0;
        *(undefined2 *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 0xd) =
             *(undefined2 *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 0x11);
        *(undefined2 *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 4) = 0;
      }
      else if ((CONCAT11(uVar16,bVar11) != -0x1ff9) ||
              (pcVar14 = in_FPUStatusWord,
              '\x01' < ((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020)[6])) {
        *(undefined *)(unaff_SI + -2) = 0x9b;
        *(char *)(unaff_SI + -1) = *(char *)(unaff_SI + -1) + -0x5c;
        pcVar14 = pcStack_10;
      }
    }
    else if (bVar11 < 9) {
      if ((uVar13 & 0x2000) != 0) goto LAB_27b2_058c;
      *(undefined *)(unaff_SI + -2) = 0x9b;
      uVar13 = CONCAT11(uVar16,uVar16) & 0x7c0;
      *(int *)(unaff_SI + -1) = (CONCAT11((char)(uVar13 >> 8),(byte)uVar13 >> 3) ^ 0x18) + 0xd826;
    }
    else {
      if (9 < bVar11) {
LAB_27b2_058c:
        pcVar7 = (code *)swi(3);
        pcVar14 = (char *)(*pcVar7)();
        return pcVar14;
      }
      *(undefined2 *)(unaff_SI + -2) = 0x9b90;
    }
    pcStack_10 = pcVar14;
    return pcStack_10;
  case (undefined *)0xa:
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  case (undefined *)0xb:
    pcVar14 = (char *)(CONCAT11(in_AF + '(',in_AF * '\x06' + -0x2d) & 0xff0f);
  default:
    *puVar20 = param_1;
    return pcVar14;
  case (undefined *)0xc:
    *(char *)((int)puVar20 + (int)param_1) =
         *(char *)((int)puVar20 + (int)param_1) + (char)((uint)in_CX >> 8);
    uVar13 = (uint)puVar20 & *(uint *)((undefined *)((int)puVar20 + (int)param_1) + 0x1b);
    *(int *)(param_1 + uVar13) = *(int *)(param_1 + uVar13) + in_CX;
    ppcVar12 = &pcStack_e;
    puVar22 = param_1;
    puVar26 = unaff_DI;
    break;
  case (undefined *)0xd:
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  case (undefined *)0xe:
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  case (undefined *)0xf:
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    *(char *)unaff_DI = *(char *)unaff_DI + cVar19;
    (&stack0x04ce)[(int)unaff_DI] =
         (&stack0x04ce)[(int)unaff_DI] +
         (char)((uint)((char *)s_Tri_mesh__Vertices__28d3_14f0 + 0x10 +
                      (uint)(0xd1 < CARRY2((uint)puVar22,(uint)puVar22)) +
                      CONCAT11(0x28,-0x2f - CARRY2((uint)puVar22,(uint)puVar22))) >> 8);
    DAT_28d3_04d2 = puVar20;
    DAT_28d3_04d4 = in_CX;
    DAT_28d3_04d6 = in_DX;
    return (char *)s_Tri_mesh__Vertices__28d3_14f0 + 0x10 +
           (uint)(0xd1 < CARRY2((uint)puVar22,(uint)puVar22)) +
           CONCAT11(0x28,-0x2f - CARRY2((uint)puVar22,(uint)puVar22));
  case (undefined *)0x10:
    uRam0002c4b9 = 0;
    return pcVar14;
  }
  puVar22[uVar13 + 0x90] = puVar22[uVar13 + 0x90] | (byte)in_DX;
  *(char *)(uVar13 + 2) = *(char *)(uVar13 + 2) + (char)(uVar13 >> 8);
  *(char **)(uVar13 + 2) = *(char **)(uVar13 + 2) + (int)puVar26;
  *(int *)(puVar22 + uVar13) = *(int *)(puVar22 + uVar13) + unaff_SI;
  piVar21 = (int *)(uVar13 & *(uint *)(puVar22 + uVar13 + 0x1b));
  puVar25 = puVar22 + 1;
  bVar17 = (byte)in_CX;
  *(byte *)((int)piVar21 + (int)puVar25) = *(byte *)((int)piVar21 + (int)puVar25) | bVar17;
  *(char *)((int)piVar21 + (int)puVar25) = *(char *)((int)piVar21 + (int)puVar25) + (char)ppcVar12;
  pbVar1 = (byte *)(unaff_SI + (int)puVar26);
  bVar11 = *pbVar1;
  bVar15 = (byte)((uint)ppcVar12 >> 8);
  *pbVar1 = *pbVar1 - bVar15;
  bVar9 = in_AF * '\x06' - 0x2d;
  cVar10 = bVar9 + (0x90 < (bVar9 & 0xf0) |
                   (in_DX < *(uint *)((int)piVar21 + (int)puVar25) ||
                   in_DX - *(uint *)((int)piVar21 + (int)puVar25) < (uint)(bVar11 < bVar15)) |
                   in_AF * (0xf9 < bVar9)) * '`';
  uVar13 = CONCAT11(0x28,cVar10);
  *(byte *)((int)piVar21 + (int)puVar25) = *(byte *)((int)piVar21 + (int)puVar25) | bVar17;
  pcVar2 = (char *)((int)piVar21 + (int)puVar25);
  cVar19 = *pcVar2;
  *pcVar2 = *pcVar2 + cVar10;
  if (*pcVar2 != '\0' && SCARRY1(cVar19,cVar10) == *pcVar2 < '\0') {
    if (*pcVar2 != '\0' && SCARRY1(cVar19,cVar10) == *pcVar2 < '\0') {
      pbVar1 = (byte *)(unaff_SI + (int)puVar26);
      bVar11 = *pbVar1;
      *pbVar1 = *pbVar1 - 0x28;
      uVar13 = -(uint)(bVar11 < 0x28) - *(int *)(unaff_SI + 0x1e);
      goto code_r0x000203b9;
    }
  }
  else {
    piVar21[1] = (int)((char *)piVar21[1] + (int)puVar26);
  }
  *(undefined2 *)((int)piVar21 + (int)puVar25) = *(undefined2 *)((int)piVar21 + (int)puVar25);
  piVar21 = (int *)((uint)piVar21 & *(uint *)((undefined *)((int)piVar21 + (int)puVar25) + 0x1b));
  puVar25 = puVar22 + 2;
code_r0x000203b9:
  *(byte *)((int)piVar21 + (int)puVar25) = *(byte *)((int)piVar21 + (int)puVar25) | bVar17;
  *piVar21 = *piVar21 + uVar13;
  *piVar21 = *piVar21 + uVar13;
  pcVar14 = (char *)(CONCAT11((char)((uVar13 & *puVar26) + 0xca2f >> 8),*(undefined *)piVar21) &
                    0xff0f);
  DAT_28d3_0259 = SUB21(pcVar14,0);
  if (DAT_28d3_0255 < 4) {
    (**(code **)((byte)(DAT_28d3_0255 << 1) + 0x30f))();
    pcVar7 = (code *)swi(0x10);
    pcVar14 = (char *)(*pcVar7)();
  }
  return pcVar14;
}



// Function: FUN_23f1_030d

void __cdecl16far FUN_23f1_030d(void)

{
  DAT_28d3_17a6 = 0;
  return;
}



// Function: FUN_23f1_032a

void __cdecl16far FUN_23f1_032a(void)

{
  char *pcVar1;
  
  if (DAT_28d3_17b9 == 0) {
    pcVar1 = (char *)s__BGI_Error__Graphics_not_initial_28d3_1ba6;
  }
  else {
    pcVar1 = (char *)s__BGI_Error__Not_in_graphics_mode_28d3_1b7f;
  }
  FUN_23f1_00db(pcVar1,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_1000_4c55(0xffff);
  return;
}



// Function: FUN_23f1_034e

bool __cdecl16near FUN_23f1_034e(uint *param_1,undefined2 param_2)

{
  uint uVar1;
  uint uVar2;
  char *in_DX;
  
  uVar1 = FUN_1000_4c7d(param_2);
  uVar2 = uVar1 | (uint)in_DX;
  if (((uVar2 != 0) && (uVar1 == 0)) &&
     (in_DX == (char *)s_String_reference_out_of_range_28d3_28cc + 7)) {
    uVar2 = 0;
    in_DX = (char *)0x0;
  }
  *param_1 = uVar1;
  ((uint *)param_1)[1] = (uint)in_DX;
  return uVar2 == 0;
}



// Function: FUN_23f1_0380

void __cdecl16near FUN_23f1_0380(uint *param_1,int param_2)

{
  uint *puVar1;
  undefined2 uVar2;
  
  uVar2 = (undefined2)((ulong)param_1 >> 0x10);
  puVar1 = (uint *)param_1;
  if (((*param_1 | puVar1[1]) != 0) && (param_2 != 0)) {
    FUN_1000_4c67(*param_1,puVar1[1],param_2);
  }
  puVar1[1] = 0;
  *param_1 = 0;
  return;
}



// Function: FUN_23f1_03b8

undefined2 FUN_23f1_03b8(int param_1,int *param_2,int param_3,int param_4)

{
  undefined *puVar1;
  undefined *puVar2;
  uint uVar3;
  undefined *puVar4;
  undefined *puVar5;
  
  uVar3 = param_3 + *param_2;
  *param_2 = *param_2 - (uVar3 & 0xf);
  param_4 = param_4 + (uVar3 >> 4);
  puVar4 = (undefined *)(uVar3 & 0xf);
  if (puVar4 != (undefined *)0x0) {
    puVar5 = (undefined *)0x0;
    for (; param_1 != 0; param_1 = param_1 + -1) {
      puVar2 = puVar5;
      puVar5 = puVar5 + 1;
      puVar1 = puVar4;
      puVar4 = puVar4 + 1;
      *puVar2 = *puVar1;
    }
  }
  return 0;
}



// Function: FUN_23f1_03f4

int __cdecl16far FUN_23f1_03f4(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (DAT_28d3_17b9 != 3) {
    if (*param_1 != 0x6b70) {
      DAT_28d3_17a6 = 0xfffc;
      return -4;
    }
    if ((*(byte *)((int *)param_1 + 0x43) < 2) || (1 < *(byte *)((int *)param_1 + 0x44))) {
      DAT_28d3_17a6 = 0xffee;
      return -0x12;
    }
    for (iVar2 = 0; iVar2 < DAT_28d3_17f6; iVar2 = iVar2 + 1) {
      iVar1 = FUN_23f1_0050(8,iVar2 * 0x1a + 0x1801,
                            (char *)s_String_reference_out_of_range_28d3_28cc + 7,
                            (int)(int *)param_1 + 0x8b,param_1._2_2_);
      if (iVar1 == 0) {
        uVar3 = FUN_23f1_03b8(((int *)param_1)[0x42],(int *)param_1 + 0x40,param_1._2_2_,
                              (int *)param_1,param_1._2_2_);
        ((undefined2 *)&DAT_28d3_1810)[iVar2 * 0xd] = (int)((ulong)uVar3 >> 0x10);
        ((undefined2 *)&DAT_28d3_180e)[iVar2 * 0xd] = (int)uVar3;
        DAT_28d3_17a6 = 0;
        return iVar2;
      }
    }
  }
  DAT_28d3_17a6 = 0xfff5;
  return -0xb;
}



// Function: FUN_23f1_04a8

int __cdecl16far FUN_23f1_04a8(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined2 *puVar4;
  int *piVar5;
  undefined2 uVar6;
  undefined4 uVar7;
  uint local_c;
  
  if (*param_1 == 0x4b50) {
    uVar6 = (undefined2)((ulong)param_1 >> 0x10);
    iVar3 = -1;
    piVar5 = (int *)param_1;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      piVar1 = piVar5;
      piVar5 = (int *)((int)piVar5 + 1);
    } while (*(char *)piVar1 != '\x1a');
    if ((*(char *)(piVar5 + 4) != '\0') && (*(byte *)(piVar5 + 5) < 2)) {
      iVar3 = piVar5[1];
      local_c = 0;
      for (puVar4 = (undefined2 *)&DAT_28d3_15fd;
          (local_c < 0x14 && ((puVar4[6] != piVar5[2] || (puVar4[5] != iVar3))));
          puVar4 = (undefined2 *)((int)puVar4 + 0xf)) {
        local_c = local_c + 1;
      }
      if (local_c == 0x14) {
        local_c = DAT_28d3_15fb;
        if (0x13 < DAT_28d3_15fb) {
          DAT_28d3_17a6 = 0xfff5;
          return -0xb;
        }
        iVar2 = DAT_28d3_15fb * 0xf;
        puVar4 = (undefined2 *)((int)(undefined2 *)&DAT_28d3_15fd + iVar2);
        DAT_28d3_15fb = DAT_28d3_15fb + 1;
        *(int *)((int)(undefined2 *)&DAT_28d3_1609 + iVar2) = piVar5[2];
        *(int *)((int)(undefined2 *)&DAT_28d3_1607 + iVar2) = iVar3;
      }
      FUN_23f1_0380(puVar4,(char *)s_String_reference_out_of_range_28d3_28cc + 7,puVar4[4],
                    (char *)s_String_reference_out_of_range_28d3_28cc + 7);
      puVar4[1] = 0;
      *puVar4 = 0;
      uVar7 = FUN_23f1_03b8(piVar5[3],piVar5,uVar6,(int *)param_1,uVar6);
      puVar4[3] = (int)((ulong)uVar7 >> 0x10);
      puVar4[2] = (int)uVar7;
      puVar4[4] = 0;
      return local_c + 1;
    }
  }
  DAT_28d3_17a6 = 0xfff3;
  return -0xd;
}



// Function: FUN_23f1_0593

uint __cdecl16far FUN_23f1_0593(uint param_1)

{
  uint uVar1;
  
  uVar1 = DAT_28d3_15f9;
  if ((DAT_28d3_17b9 == 0) && (0xff < param_1)) {
    DAT_28d3_15f9 = param_1;
  }
  else {
    DAT_28d3_17a6 = 0xfff5;
  }
  return uVar1;
}



// Function: FUN_23f1_05c9

/* WARNING: Instruction at (ram,0x000232d9) overlaps instruction at (ram,0x000232d8)
    */
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Removing unreachable block (ram,0x0002b103) */
/* WARNING: Removing unreachable block (ram,0x0002b12f) */
/* WARNING: Removing unreachable block (ram,0x0002b136) */
/* WARNING: Removing unreachable block (ram,0x0002b13b) */
/* WARNING: Removing unreachable block (ram,0x0002b212) */
/* WARNING: Removing unreachable block (ram,0x0002b2d6) */
/* WARNING: Removing unreachable block (ram,0x0002b160) */
/* WARNING: Removing unreachable block (ram,0x0002b165) */
/* WARNING: Removing unreachable block (ram,0x0002b1d6) */
/* WARNING: Removing unreachable block (ram,0x0002b16d) */
/* WARNING: Removing unreachable block (ram,0x0002b16f) */
/* WARNING: Removing unreachable block (ram,0x0002b1de) */
/* WARNING: Removing unreachable block (ram,0x0002b1c3) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint * __cdecl16near
FUN_23f1_05c9(undefined2 param_1_00,int param_1,undefined2 *param_2,undefined2 *param_3)

{
  byte *pbVar1;
  char **ppcVar2;
  uint *puVar3;
  char *pcVar4;
  char *pcVar5;
  undefined4 *puVar6;
  undefined2 *puVar7;
  undefined uVar8;
  uint **ppuVar9;
  undefined *puVar10;
  long lVar11;
  undefined2 *puVar12;
  uint **ppuVar13;
  code *pcVar14;
  undefined2 uVar15;
  byte bVar16;
  char cVar17;
  byte bVar18;
  char *pcVar19;
  uint uVar20;
  uint *puVar21;
  uint uVar22;
  uint uVar23;
  undefined *puVar24;
  uint in_CX;
  uint uVar25;
  byte bVar26;
  byte bVar27;
  int iVar28;
  undefined2 in_DX;
  byte bVar29;
  char cVar30;
  uint uVar31;
  char cVar34;
  char *pcVar32;
  undefined *puVar33;
  uint **ppuVar35;
  uint **ppuVar36;
  uint **ppuVar37;
  uint **ppuVar38;
  uint **ppuVar39;
  undefined2 *puVar40;
  undefined2 *puVar41;
  int iVar42;
  ulong uVar43;
  uint *unaff_SI;
  undefined2 *puVar44;
  undefined2 *puVar45;
  undefined *puVar46;
  undefined4 *puVar47;
  char **unaff_DI;
  uint *puVar48;
  undefined *puVar49;
  undefined2 uVar50;
  undefined2 uVar51;
  undefined2 unaff_SS;
  undefined2 in_FS;
  undefined2 in_GS;
  bool bVar52;
  bool bVar53;
  bool bVar54;
  bool bVar55;
  byte in_AF;
  int in_stack_00000000;
  undefined local_14 [2];
  undefined auStack_12 [2];
  undefined local_10 [2];
  undefined4 uStack_e;
  undefined2 local_4;
  
  puVar46 = &stack0xfffe;
  uVar43 = ZEXT24(&stack0xfffe);
  local_4 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  pcVar19 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  uVar50 = (undefined2)((ulong)param_2 >> 0x10);
  *param_2 = 0;
  uVar31 = param_1 + 1;
  if (0xb < uVar31) {
    *param_2 = 0xffff;
    *param_3 = 0xffff;
    return (uint *)((char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  bVar52 = CARRY2(uVar31,uVar31);
  pcVar32 = (char *)(uVar31 * 2);
  uVar51 = 0x2000;
  bVar18 = (byte)in_CX;
  bVar16 = (byte)(in_CX >> 8);
  cVar17 = (char)in_DX;
  cVar30 = (char)pcVar32;
  switch(uVar31) {
  case 0:
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  case 1:
    return (uint *)((char *)s_String_reference_out_of_range_28d3_28cc + 7);
  case 2:
    bVar26 = 0xd3;
    out(0x3cf,cVar30);
    if (DAT_2001_0d95 == '\x04') {
      bVar26 = 0x2c;
    }
    *(byte *)unaff_DI = bVar26;
    bVar18 = (byte)(((uint)bVar16 << 8) >> (bVar18 & 0x1f));
    out(0x3cf,0xd3);
    if (DAT_2001_0d95 == '\x04') {
      bVar18 = ~bVar18;
    }
    bVar16 = *(byte *)((int)unaff_DI + 1);
    *(byte *)((int)unaff_DI + 1) = bVar18;
    return (uint *)CONCAT11(bVar16,bVar18);
  case 3:
    pcVar4 = &stack0xfffe + (int)unaff_SI;
    cVar17 = *pcVar4;
    *pcVar4 = *pcVar4 + -0x2d;
    if (SCARRY1(cVar17,-0x2d) == *pcVar4 < '\0') {
      puVar21 = unaff_SI + -1;
      *(undefined *)puVar21 = 0x9b;
      *(char *)((int)unaff_SI + -1) = *(char *)((int)unaff_SI + -1) + -0x5c;
    }
    else {
      puVar21 = (uint *)(in_stack_00000000 + 1);
    }
    return puVar21;
  case 4:
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  case 5:
    return (uint *)(CONCAT11(in_AF + 0x28,in_AF * '\x06' + -0x2d) & 0xff0f);
  case 6:
    while( true ) {
      cVar17 = (char)in_CX;
      *(byte *)unaff_DI = *(byte *)ZEXT24(pcVar32 + (byte)((char)pcVar19 + bVar52 + 0x92));
      if (unaff_SI == DAT_28d3_04d0) break;
      FUN_2001_0fe8();
      cVar17 = (char)in_CX;
      bVar52 = false;
      if ((*(byte *)ZEXT24(pcVar32 + (in_CX & 0xff)) & *(byte *)unaff_DI) != 0) break;
      pcVar19 = (char *)(in_CX & 0xff);
    }
    bVar18 = cVar17 + 1;
    if (bVar18 == 8) {
      bVar18 = 0;
      unaff_DI = (char **)((int)unaff_DI + 1);
      if (DAT_28d3_04e2 != '\0') {
        bVar18 = 0;
        FUN_2001_1573();
      }
    }
    out(0x3cf,*(undefined *)ZEXT24(pcVar32 + bVar18));
    s_variable_28d3_0cef._7_2_ = (int)unaff_SI + 1;
    DAT_28d3_0d13 = (int)unaff_SI + 1;
    DAT_28d3_0d15 = _DAT_28d3_0d07;
    DAT_28d3_0d17 = unaff_DI;
    DAT_28d3_0d19 = bVar18;
    return _DAT_28d3_0d07;
  case 7:
    pcVar32[(int)unaff_SI] = pcVar32[(int)unaff_SI] + cVar17;
    return (uint *)((char *)s_String_reference_out_of_range_28d3_28cc + 7);
  case 8:
    *(byte *)(unaff_DI + -0x19) = *(byte *)(unaff_DI + -0x19) | bVar18;
    uStack_e = (char **)CONCAT22(&stack0xffff,unaff_DI + 1);
    puVar21 = (uint *)FUN_1928_2578();
    return puVar21;
  case 10:
    if (bVar52 || pcVar32 == (char *)0x0) {
      puVar46 = &stack0xfffe;
      FUN_1000_5728();
      if (*(int *)(puVar46 + 10) == 0) goto LAB_280e_0930;
      local_4 = *(char **)(puVar46 + -0x20);
    }
    FUN_1000_1a99();
LAB_280e_0930:
    *(undefined2 *)((int)*(undefined4 *)(puVar46 + 6) + 8) = *(undefined2 *)(puVar46 + -0x26);
    uVar50 = (undefined2)((ulong)*(undefined4 *)(puVar46 + 6) >> 0x10);
    iVar28 = (int)*(undefined4 *)(puVar46 + 6);
    if (((*(int *)(iVar28 + 4) != *(int *)(puVar46 + -0x20)) ||
        (*(int *)(iVar28 + 2) != *(int *)(puVar46 + -0x22))) ||
       (*(int *)(puVar46 + 0x12) != *(int *)(puVar46 + 0xc))) {
      local_4 = *(char **)(puVar46 + -0x20);
      FUN_1000_1b58();
    }
    if (*(int *)(puVar46 + 0x12) != 0) {
      if ((*(uint *)(puVar46 + 0xe) | *(uint *)(puVar46 + 0x10)) == 0) {
        local_4 = (char *)(*(int *)(puVar46 + -0x22) + *(int *)(puVar46 + 10));
        FUN_1000_1ae3();
      }
      else {
        local_4 = *(char **)(puVar46 + -0x20);
        FUN_1000_1b58();
      }
    }
    uVar50 = (undefined2)((ulong)*(undefined4 *)(puVar46 + 6) >> 0x10);
    iVar28 = (int)*(undefined4 *)(puVar46 + 6);
    *(undefined2 *)(iVar28 + 6) = *(undefined2 *)(puVar46 + -0x24);
    *(undefined *)((int)*(undefined4 *)(puVar46 + -0x22) + *(int *)(iVar28 + 6)) = 0;
    uVar50 = (undefined2)((ulong)*(undefined4 *)(puVar46 + 6) >> 0x10);
    iVar28 = (int)*(undefined4 *)(puVar46 + 6);
    if ((*(int *)(iVar28 + 4) != *(int *)(puVar46 + -0x20)) ||
       (*(int *)(iVar28 + 2) != *(int *)(puVar46 + -0x22))) {
      local_4 = (char *)0x8b02;
      FUN_1000_4648();
      uVar51 = (undefined2)((ulong)*(undefined4 *)(puVar46 + 6) >> 0x10);
      iVar28 = (int)*(undefined4 *)(puVar46 + 6);
      uVar50 = *(undefined2 *)(puVar46 + -0x22);
      *(undefined2 *)(iVar28 + 4) = *(undefined2 *)(puVar46 + -0x20);
      *(undefined2 *)(iVar28 + 2) = uVar50;
    }
    puVar21 = (uint *)FUN_1000_5d02();
    return puVar21;
  case 0xb:
    while( true ) {
      in(0x9b);
      iVar28 = (int)uVar43;
      *(double *)(iVar28 + -0x1a) = (double)((float)*(int *)(iVar28 + -0x1c) / _DAT_28d3_1474);
      *(undefined8 *)(iVar28 + -0x6e) = *(undefined8 *)(iVar28 + -0x1a);
      local_14 = (undefined  [2])uVar51;
      FUN_1000_04ab();
      uStack_e = (char **)CONCAT22((int)uVar43 + -0x5e,0x1000);
      local_10 = (undefined  [2])0x3313;
      FUN_1000_1b7d();
      uStack_e = (char **)CONCAT22((int)uVar43 + -0x5e,0x1000);
      local_10 = (undefined  [2])0x3324;
      FUN_1000_1b7d();
      uStack_e = (char **)CONCAT22((int)uVar43 + -0x5e,0x1000);
      local_10 = (undefined  [2])0x3337;
      FUN_1000_2afc();
      iVar28 = (int)uVar43;
      *(long *)(iVar28 + -0x12) = *(long *)(iVar28 + -0x12) + 1;
      if (DAT_28d3_2984 <= *(long *)(iVar28 + -0x12)) break;
      uStack_e = (char **)*(undefined4 *)(iVar28 + -0x12);
      local_10 = (undefined  [2])0x1000;
      auStack_12 = (undefined  [2])0x3172;
      FUN_1000_40a5();
      uStack_e = (char **)CONCAT22((int)uVar43 + -0x5e,0x1000);
      local_10 = (undefined  [2])0x3183;
      FUN_1000_1bec();
      uStack_e = (char **)CONCAT22((int)uVar43 + -0x5e,0x1000);
      local_10 = (undefined  [2])0x3195;
      FUN_1000_1b7d();
      uStack_e = (char **)CONCAT22((int)uVar43 + -0x5e,0x1000);
      local_10 = (undefined  [2])0x31a6;
      FUN_1000_1b7d();
      iVar28 = 0;
      uVar31 = FUN_1000_3eb2();
      iVar42 = (int)uVar43;
      *(undefined2 *)(iVar42 + -0x1c) = *(undefined2 *)(uVar31 + DAT_28d3_2a40);
      *(double *)(iVar42 + -0x1a) = (double)((float)*(int *)(iVar42 + -0x1c) / _DAT_28d3_1474);
      *(undefined8 *)(iVar42 + -0x6e) = *(undefined8 *)(iVar42 + -0x1a);
      local_14 = (undefined  [2])0x1000;
      FUN_1000_04ab();
      uStack_e = (char **)CONCAT22((int)uVar43 + -0x5e,0x1000);
      local_10 = (undefined  [2])0x320d;
      FUN_1000_1b7d();
      uStack_e = (char **)CONCAT22((int)uVar43 + -0x5e,0x1000);
      local_10 = (undefined  [2])0x321e;
      FUN_1000_1b7d();
      iVar28 = 0;
      uVar31 = FUN_1000_3eb2();
      uVar20 = uVar31 + 1;
      iVar42 = (int)uVar43;
      *(int *)(iVar42 + -0x1c) = -*(int *)(uVar20 * 2 + DAT_28d3_2a40);
      *(double *)(iVar42 + -0x1a) = (double)((float)*(int *)(iVar42 + -0x1c) / _DAT_28d3_1474);
      *(undefined8 *)(iVar42 + -0x6e) = *(undefined8 *)(iVar42 + -0x1a);
      local_14 = (undefined  [2])0x1000;
      FUN_1000_04ab();
      uStack_e = (char **)CONCAT22((int)uVar43 + -0x5e,0x1000);
      local_10 = (undefined  [2])0x3291;
      FUN_1000_1b7d();
      uStack_e = (char **)CONCAT22((int)uVar43 + -0x5e,0x1000);
      local_10 = (undefined  [2])0x32a2;
      FUN_1000_1b7d();
      iVar28 = 0;
      uVar51 = 0x1000;
      uVar31 = FUN_1000_3eb2();
      uVar20 = uVar31 + 2;
      *(undefined2 *)((int)uVar43 + -0x1c) = *(undefined2 *)(uVar20 * 2 + DAT_28d3_2a40);
    }
    uStack_e = (char **)CONCAT22(0x3356,(undefined2)uStack_e);
    FUN_1000_258a();
    return (uint *)0x0;
  }
  *(uint *)(pcVar32 + (int)unaff_SI) = *(uint *)(pcVar32 + (int)unaff_SI) >> (bVar18 & 0x1f);
  *unaff_SI = *unaff_SI ^ (uint)&local_4;
  *(uint *)(pcVar32 + (int)unaff_SI) = *(uint *)(pcVar32 + (int)unaff_SI) >> (bVar18 & 0x1f);
  *(char *)(unaff_SI + 0x12) = *(char *)(unaff_SI + 0x12) - cVar17;
  *(uint *)(pcVar32 + (int)unaff_SI) = *(uint *)(pcVar32 + (int)unaff_SI) >> (bVar18 & 0x1f);
  ppcVar2 = unaff_DI + 0x12;
  bVar26 = *(byte *)ppcVar2;
  bVar29 = (byte)((uint)in_DX >> 8);
  *(byte *)ppcVar2 = *(byte *)ppcVar2 - bVar29;
  bVar27 = *(byte *)ppcVar2;
  puVar3 = (uint *)(pcVar32 + (int)unaff_SI);
  uVar31 = *puVar3;
  *puVar3 = *puVar3 >> (bVar18 & 0x1f);
  bVar54 = (in_CX & 0x1f) != 0;
  bVar55 = (uVar31 >> (bVar18 & 0x1f) - 1 & 1) != 0;
  bVar53 = !bVar54 && bVar26 < bVar29 || bVar54 && bVar55;
  bVar52 = (in_CX & 0x1f) != 0;
  if (((bVar54 || bVar26 >= bVar29) && (!bVar54 || !bVar55)) &&
      ((bVar52 || bVar27 != 0) && (!bVar52 || *puVar3 != 0))) {
    *(uint *)(pcVar32 + (int)unaff_SI) = *(uint *)(pcVar32 + (int)unaff_SI) >> (bVar18 & 0x1f);
    *(uint *)(pcVar32 + (int)unaff_SI) = *(uint *)(pcVar32 + (int)unaff_SI) >> (bVar18 & 0x1f);
    ppcVar2 = unaff_DI;
    unaff_DI = unaff_DI + 1;
    *ppcVar2 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
    cVar34 = (char)((uint)pcVar32 >> 8);
    (&stack0xd323)[(int)unaff_DI] = (&stack0xd323)[(int)unaff_DI] - cVar34;
    in_DX = CONCAT11(bVar29,cVar17 - cVar30);
    pcVar32 = (char *)CONCAT11(cVar34,cVar30 - bVar16);
    in_CX = (uint)(byte)(bVar16 - cVar34) << 8;
    *pcVar32 = *pcVar32;
    ppcVar2 = unaff_DI;
    bVar53 = 0xd7 < *(byte *)ppcVar2;
    *(byte *)ppcVar2 = *(byte *)ppcVar2 + 0x28;
  }
  puVar3 = (uint *)(pcVar32 + (int)unaff_SI);
  bVar27 = (byte)in_CX;
  uVar31 = *puVar3;
  *puVar3 = *puVar3 >> (bVar27 & 0x1f);
  bVar52 = (in_CX & 0x1f) != 0;
  ppcVar2 = unaff_DI;
  uVar20 = (uint)(byte)(!bVar52 & bVar53 | (bVar52 && (uVar31 >> (bVar27 & 0x1f) - 1 & 1) != 0));
  pcVar19 = *ppcVar2;
  pcVar5 = *ppcVar2;
  *ppcVar2 = &stack0xfffa + (int)pcVar5 + uVar20;
  puVar3 = (uint *)(pcVar32 + (int)unaff_SI);
  uVar31 = *puVar3;
  *puVar3 = *puVar3 >> (bVar27 & 0x1f);
  bVar52 = (in_CX & 0x1f) != 0;
  bVar54 = !bVar52 &&
           (CARRY2((uint)pcVar19,(uint)&stack0xfffa) ||
           CARRY2((uint)(&stack0xfffa + (int)pcVar5),uVar20)) ||
           bVar52 && (uVar31 >> (bVar27 & 0x1f) - 1 & 1) != 0;
  bVar18 = *(byte *)unaff_DI;
  bVar16 = *(byte *)unaff_DI + 0x28;
  puVar3 = (uint *)(pcVar32 + (int)unaff_SI);
  uVar31 = *puVar3;
  *puVar3 = *puVar3 >> (bVar27 & 0x1f);
  bVar52 = (in_CX & 0x1f) != 0;
  uVar20 = (uint)(!bVar52 && (0xd7 < bVar18 || CARRY1(bVar16,bVar54)) ||
                 bVar52 && (uVar31 >> (bVar27 & 0x1f) - 1 & 1) != 0);
  pcVar19 = *unaff_DI;
  puVar46 = &stack0xfffa + (int)*unaff_DI;
  puVar3 = (uint *)(pcVar32 + (int)unaff_SI);
  uVar31 = *puVar3;
  *puVar3 = *puVar3 >> (bVar27 & 0x1f);
  bVar52 = (in_CX & 0x1f) != 0;
  bVar55 = !bVar52 && (CARRY2((uint)&stack0xfffa,(uint)pcVar19) || CARRY2((uint)puVar46,uVar20)) ||
           bVar52 && (uVar31 >> (bVar27 & 0x1f) - 1 & 1) != 0;
  puVar3 = (uint *)(pcVar32 + (int)unaff_SI);
  uVar31 = *puVar3;
  *puVar3 = *puVar3 >> (bVar27 & 0x1f);
  bVar52 = (in_CX & 0x1f) != 0;
  DAT_3000_6055 = DAT_3000_6055 - (char)in_DX;
  *pcVar32 = *pcVar32 - (char)in_DX;
  uVar22 = (uint)((undefined *)&DAT_3000_6055 +
                 (uint)(!bVar52 && 7 < bVar55 || bVar52 && (uVar31 >> (bVar27 & 0x1f) - 1 & 1) != 0)
                 + CONCAT11(bVar16 + bVar54,bVar55 + -8)) & 0x28d3;
  ppcVar2 = unaff_DI;
  bVar18 = *(byte *)ppcVar2;
  bVar26 = (byte)(uVar22 >> 8);
  *(byte *)ppcVar2 = *(byte *)ppcVar2 - bVar26;
  puVar3 = (uint *)(pcVar32 + (int)unaff_SI);
  uVar31 = *puVar3;
  *puVar3 = *puVar3 >> (bVar27 & 0x1f);
  bVar52 = (in_CX & 0x1f) != 0;
  ppcVar2 = unaff_DI;
  uVar25 = (uint)(!bVar52 && bVar18 < bVar26 || bVar52 && (uVar31 >> (bVar27 & 0x1f) - 1 & 1) != 0);
  pcVar19 = *ppcVar2;
  pcVar5 = *ppcVar2;
  *ppcVar2 = (char *)(((int)pcVar5 - (int)(puVar46 + uVar20)) - uVar25);
  puVar3 = (uint *)(pcVar32 + (int)unaff_SI);
  uVar31 = *puVar3;
  *puVar3 = *puVar3 >> (bVar27 & 0x1f);
  bVar52 = (in_CX & 0x1f) != 0;
  bVar16 = (byte)uVar22;
  bVar18 = 9 < (bVar16 & 0xf) | in_AF;
  bVar16 = bVar16 + bVar18 * '\x06';
  *(uint *)(pcVar32 + (int)unaff_SI) = *(uint *)(pcVar32 + (int)unaff_SI) >> (bVar27 & 0x1f);
  uVar51 = *(undefined2 *)(puVar46 + (uVar20 - 1));
  uVar15 = *(undefined2 *)(puVar46 + uVar20 + 1);
  *(uint *)(puVar46 + uVar20 + 1) =
       CONCAT11(bVar26,bVar16 + (0x90 < (bVar16 & 0xf0) |
                                (!bVar52 &&
                                 (pcVar19 < puVar46 + uVar20 ||
                                 (uint)((int)pcVar5 - (int)(puVar46 + uVar20)) < uVar25) ||
                                bVar52 && (uVar31 >> (bVar27 & 0x1f) - 1 & 1) != 0) |
                                bVar18 * (0xf9 < bVar16)) * '`') & 0x28d3;
  *(uint *)(puVar46 + (uVar20 - 1)) = in_CX;
  *(undefined2 *)(puVar46 + (uVar20 - 3)) = in_DX;
  *(char **)(puVar46 + (uVar20 - 5)) = pcVar32;
  *(undefined **)(puVar46 + (uVar20 - 7)) = puVar46 + uVar20 + 3;
  *(undefined **)(puVar46 + (uVar20 - 9)) = &stack0xffff;
  *(undefined2 *)(puVar46 + (uVar20 - 0xb)) = uVar51;
  *(undefined2 *)(puVar46 + (uVar20 - 0xd)) = uVar15;
  puVar21 = *(uint **)(puVar46 + (uVar20 - 0xd));
  puVar44 = *(undefined2 **)(puVar46 + (uVar20 - 0xb));
  uVar22 = *(uint *)(puVar46 + (uVar20 - 9));
  puVar33 = *(undefined **)(puVar46 + (uVar20 - 5));
  uVar51 = *(undefined2 *)(puVar46 + (uVar20 - 3));
  uVar25 = *(uint *)(puVar46 + (uVar20 - 1));
  uVar23 = *(uint *)(puVar46 + uVar20 + 1) & 0x28d3;
  puVar3 = (uint *)(puVar33 + (int)puVar44);
  bVar18 = (byte)uVar25;
  uVar31 = *puVar3;
  *puVar3 = *puVar3 >> (bVar18 & 0x1f);
  puVar3 = puVar21;
  *puVar3 = *puVar3 + (uint)((uVar25 & 0x1f) != 0 && (uVar31 >> (bVar18 & 0x1f) - 1 & 1) != 0) *
                      (((uint)(puVar46 + uVar20 + 3) & 3) - (*puVar3 & 3));
  *(uint *)(puVar33 + (int)puVar44) = *(uint *)(puVar33 + (int)puVar44) >> (bVar18 & 0x1f);
  puVar24 = (undefined *)(ulong)uVar23;
  *(uint *)(puVar33 + (int)puVar44) = *(uint *)(puVar33 + (int)puVar44) >> (bVar18 & 0x1f);
  puVar49 = puVar46 + uVar20 + 1;
  ppuVar39 = (uint **)(puVar46 + uVar20 + 1);
  *(undefined **)(puVar46 + uVar20 + 1) = (undefined *)&DAT_3000_6055;
  bVar27 = (byte)((uint)uVar51 >> 8);
  puVar33[(int)puVar44] = puVar33[(int)puVar44] - bVar27;
  puVar3 = puVar21 + 0x39;
  bVar18 = *(byte *)puVar3;
  bVar26 = (byte)uVar23;
  *(byte *)puVar3 = *(byte *)puVar3 + bVar26;
  bVar16 = *(byte *)puVar3;
  bVar52 = *(byte *)puVar3 == 0;
  if (CARRY1(bVar18,bVar26)) {
    uVar22 = (int)*(undefined4 *)((int)puVar44 + 0x65) * 0x6e20;
code_r0x0002b119:
    pbVar1 = (byte *)((int)puVar21 + 0x65);
    bVar18 = *pbVar1;
    *pbVar1 = *pbVar1 + (byte)uVar25;
    bVar52 = *pbVar1 == 0;
    puVar48 = puVar21 + 1;
    uVar31 = in(uVar51);
    *puVar21 = uVar31;
    puVar47 = (undefined4 *)(puVar44 + 1);
    out(*puVar44,uVar51);
    if (CARRY1(bVar18,(byte)uVar25)) {
LAB_28d3_246c:
      puVar46 = (undefined *)puVar24;
      puVar21 = (uint *)((int)puVar48 + 1);
      cVar17 = in(uVar51);
      *(char *)puVar48 = cVar17;
      ppuVar35 = (uint **)(undefined *)((long)*(int *)(puVar47 + 8) * 0x6164);
      bVar54 = (undefined *)(long)(int)ppuVar35 !=
               (undefined *)((long)*(int *)(puVar47 + 8) * 0x6164);
      if (bVar52) {
        puVar48 = (uint *)((int)puVar48 + 3);
        uVar31 = in(uVar51);
        *puVar21 = uVar31;
        goto code_r0x0002b206;
      }
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + (char)puVar24;
      puVar44 = (undefined2 *)((int)puVar47 + -1);
      puVar47 = (undefined4 *)((int)puVar47 + 1);
      out(*puVar44,uVar51);
      pbVar1 = (byte *)((int)puVar21 + uVar22 + 0x75);
      bVar54 = false;
      *pbVar1 = *pbVar1 & (byte)((uint)uVar51 >> 8);
code_r0x0002b1ab:
      puVar46 = (undefined *)puVar24;
      puVar3 = (uint *)((int)puVar47 + (int)(puVar33 + 0x20));
      iVar28 = (uVar22 & 3) - (*puVar3 & 3);
      *puVar3 = *puVar3 + (uint)bVar54 * iVar28;
      if (bVar54 || 0 < iVar28) {
        uVar22 = uVar22 + 1;
        if (-1 < (int)uVar22) {
code_r0x0002b21e:
          puVar3 = (uint *)(puVar33 + (int)puVar47);
          iVar28 = ((uint)ppuVar35 & 3) - (*puVar3 & 3);
          bVar52 = 0 < iVar28;
          *puVar3 = *puVar3 + (uint)bVar54 * iVar28;
code_r0x0002b220:
          cVar17 = (char)puVar24;
          puVar6 = puVar47;
          puVar47 = puVar47 + 1;
          out(*puVar6,uVar51);
          if (!bVar54) {
            puVar48 = *ppuVar35;
            puVar47 = (undefined4 *)ppuVar35[1];
            uVar22 = (uint)ppuVar35[2];
            puVar33 = (undefined *)ppuVar35[4];
            uVar51 = ppuVar35[5];
            uVar25 = (uint)ppuVar35[6];
            puVar46 = (undefined *)ppuVar35[7];
            puVar24 = (undefined *)ZEXT24(puVar46);
            ppuVar39 = ppuVar35 + 8;
            ppuVar37 = ppuVar35 + 8;
            ppuVar35 = ppuVar35 + 8;
            if (bVar52) goto LAB_28d3_2516_1;
            if (!bVar54) {
              puVar6 = puVar47;
              puVar47 = (undefined4 *)((int)puVar47 + 2);
              out(*(undefined2 *)puVar6,uVar51);
              goto LAB_28d3_24fd;
            }
            puVar44 = (undefined2 *)((int)puVar47 + 1);
            out(*(undefined *)puVar47,uVar51);
            puVar47 = (undefined4 *)((int)puVar47 + 3);
            out(*puVar44,uVar51);
            if (bVar54 || bVar52) goto LAB_28d3_2570;
            goto code_r0x0002b30e;
          }
          puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
          puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
          goto LAB_28d3_2564_1;
        }
        *(byte *)((int)puVar47 + 0x65) =
             *(byte *)((int)puVar47 + 0x65) & (byte)((ulong)puVar24 >> 8);
        puVar47 = (undefined4 *)*(undefined2 *)((int)ppuVar35 + 2);
        uVar22 = *(uint *)((int)ppuVar35 + 4);
        goto code_r0x0002b280;
      }
      puVar3 = puVar21;
      *puVar3 = *puVar3 + (uint)bVar54 * (((uint)ppuVar35 & 3) - (*puVar3 & 3));
      bVar52 = SCARRY2(uVar25,1);
      uVar25 = uVar25 + 1;
      if (uVar25 != 0) {
code_r0x0002b1b8:
        puVar46 = (undefined *)puVar24;
        uVar31 = in(uVar51);
        *puVar21 = uVar31;
        ppuVar37 = ppuVar35;
        puVar48 = puVar21 + 1;
        if (bVar52) goto LAB_28d3_2500;
        bVar18 = (byte)((uint)uVar51 >> 8);
        *(byte *)((int)puVar47 + 0x6f) = *(byte *)((int)puVar47 + 0x6f) & bVar18;
        pbVar1 = (byte *)((int)puVar47 + uVar22 + 0x65);
        *pbVar1 = *pbVar1 & bVar18;
        bVar18 = *pbVar1;
        uVar31 = in(uVar51);
        puVar21[1] = uVar31;
        puVar48 = puVar21 + 2;
        puVar6 = puVar47;
        puVar47 = (undefined4 *)((int)puVar47 + 2);
        out(*(undefined2 *)puVar6,uVar51);
        bVar54 = false;
        if (bVar18 != 0) {
          pbVar1 = (byte *)((int)puVar48 + uVar22 + 0x75);
          bVar54 = false;
          *pbVar1 = *pbVar1 & (byte)((ulong)puVar24 >> 8);
          bVar52 = *pbVar1 == 0;
          ppuVar39 = ppuVar35;
          puVar21 = puVar48;
          goto LAB_28d3_249b;
        }
LAB_28d3_24fd:
        puVar33 = puVar33 + 1;
        ppuVar37 = ppuVar35;
        if (!bVar54) goto LAB_28d3_2500;
        goto LAB_28d3_256f;
      }
      pbVar1 = (byte *)((int)puVar21 + uVar22 + 0x72);
      bVar54 = CARRY1(*pbVar1,(byte)puVar24);
      *pbVar1 = *pbVar1 + (byte)puVar24;
      puVar6 = puVar47;
      puVar47 = (undefined4 *)((int)puVar47 + 2);
      out(*(undefined2 *)puVar6,uVar51);
      ppuVar37 = ppuVar35;
      puVar48 = puVar21;
LAB_28d3_2500:
      if (bVar54) {
        bVar52 = puVar46 < (undefined *)0x6564;
        puVar46 = puVar46 + -0x6564;
        if (!bVar52 && puVar46 != (undefined *)0x0) {
          puVar3 = puVar48 + 0x10;
          *puVar3 = *puVar3 + (uint)bVar52 * (((uint)ppuVar37 & 3) - (*puVar3 & 3));
          puVar3 = puVar48;
          puVar48 = (uint *)((int)puVar48 + 1);
          cVar17 = in(uVar51);
          *(char *)puVar3 = cVar17;
          uVar22 = 0;
          puVar33[(int)puVar47] = puVar33[(int)puVar47] + (char)puVar46;
          goto LAB_28d3_2512;
        }
        goto LAB_28d3_2570;
      }
LAB_28d3_2575:
      *(char *)(uVar22 + (int)puVar47) = *(char *)(uVar22 + (int)puVar47) + (char)uVar25;
      *(char *)puVar48 = *(char *)puVar48 + (char)uVar25;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + (char)puVar46;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + (char)puVar46;
      pcVar4 = (char *)((int)puVar47 + uVar22 + 0xd325);
      *pcVar4 = *pcVar4 + (char)((uint)uVar51 >> 8);
LAB_28d3_2585:
      bVar18 = (byte)uVar25;
      cVar17 = (char)((uint)uVar51 >> 8);
      *(char *)((int)puVar47 + -0x2cdb) = *(char *)((int)puVar47 + -0x2cdb) - cVar17;
      *(char *)((int)puVar48 + -0x2cdb) = *(char *)((int)puVar48 + -0x2cdb) - cVar17;
      ((undefined *)&DAT_3000_6055)[uVar22] = ((undefined *)&DAT_3000_6055)[uVar22] - cVar17;
      ((undefined *)&DAT_3000_6055)[(int)puVar33] =
           ((undefined *)&DAT_3000_6055)[(int)puVar33] - cVar17;
      cVar17 = (char)((uint)puVar33 >> 8);
      *(char *)((int)puVar47 + (int)(puVar33 + -0x2cdb)) =
           *(char *)((int)puVar47 + (int)(puVar33 + -0x2cdb)) - cVar17;
      *(char *)((int)puVar48 + (int)(puVar33 + -0x2cdb)) =
           *(char *)((int)puVar48 + (int)(puVar33 + -0x2cdb)) - cVar17;
      goto LAB_28d3_259d;
    }
    *(byte *)((int)puVar48 + (int)(puVar33 + 0x72)) =
         *(byte *)((int)puVar48 + (int)(puVar33 + 0x72)) & (byte)((ulong)puVar24 >> 8);
    out(*(undefined *)puVar47,uVar51);
    *(byte *)(*(int *)(puVar49 + 2) + 0x72) =
         *(byte *)(*(int *)(puVar49 + 2) + 0x72) & (byte)((uint)*(undefined2 *)(puVar49 + 10) >> 8);
    puVar48 = *(uint **)(puVar49 + 0x10);
    puVar47 = *(undefined4 **)(puVar49 + 0x12);
    uVar22 = *(uint *)(puVar49 + 0x14);
    puVar33 = *(undefined **)(puVar49 + 0x18);
    uVar51 = *(undefined2 *)(puVar49 + 0x1a);
    uVar25 = *(uint *)(puVar49 + 0x1c);
    puVar24 = (undefined *)(ulong)*(uint *)(puVar49 + 0x1e);
    pbVar1 = (byte *)((int)puVar48 + (int)(puVar33 + 0x6e));
    bVar52 = CARRY1(*pbVar1,(byte)uVar25);
    *pbVar1 = *pbVar1 + (byte)uVar25;
code_r0x0002b193:
    puVar3 = (uint *)(puVar33 + 100);
    *puVar3 = *puVar3 + (uint)bVar52 * ((uVar22 & 3) - (*puVar3 & 3));
    pbVar1 = (byte *)((int)puVar48 + (int)(puVar33 + 0x6e));
    bVar18 = *pbVar1;
    *pbVar1 = *pbVar1 + (byte)uVar25;
    bVar55 = (char)*pbVar1 < '\0';
    bVar52 = *pbVar1 == 0;
    puVar21 = puVar48;
    if (!CARRY1(bVar18,(byte)uVar25) && !bVar52) goto LAB_28d3_246c;
LAB_28d3_24cd:
    puVar46 = (undefined *)puVar24;
    puVar48 = (uint *)((int)puVar21 + 1);
    cVar17 = in(uVar51);
    *(char *)puVar21 = cVar17;
    ppuVar35 = (uint **)(undefined *)((long)*(int *)(puVar47 + 8) * 0x7261);
    bVar54 = (undefined *)(long)(int)ppuVar35 != (undefined *)((long)*(int *)(puVar47 + 8) * 0x7261)
    ;
    if (bVar52) {
code_r0x0002b206:
      out(*(undefined *)puVar47,uVar51);
      uVar25 = uVar25 + 1;
      if (!bVar54) {
        *(byte *)(undefined2 *)((int)puVar47 + 0x6a) =
             *(byte *)(undefined2 *)((int)puVar47 + 0x6a) & (byte)(uVar25 >> 8);
        puVar47 = (undefined4 *)*(undefined2 *)((int)ppuVar35 + 2);
        uVar22 = *(uint *)((int)ppuVar35 + 4);
code_r0x0002b280:
        puVar12 = (undefined2 *)((long)*(int *)((int)puVar47 + uVar22 + 0x6c) * 0x2065);
        puVar41 = (undefined2 *)puVar12;
        puVar49 = (undefined *)*puVar41;
        puVar44 = (undefined2 *)puVar41[1];
        uVar31 = puVar41[2];
        puVar33 = (undefined *)puVar41[4];
        uVar51 = puVar41[5];
        uVar25 = puVar41[6];
        puVar46 = (undefined *)puVar41[7];
        ppuVar37 = (uint **)(puVar41 + 8);
        puVar48 = (uint *)(puVar49 + 1);
        uVar8 = in(uVar51);
        *puVar49 = uVar8;
        puVar47 = (undefined4 *)(puVar44 + 1);
        out(*puVar44,uVar51);
        puVar3 = (uint *)(uVar31 + (int)puVar48);
        *puVar3 = *puVar3 + (uint)((undefined2 *)(long)(int)puVar41 != puVar12) *
                            ((uVar31 & 3) - (*puVar3 & 3));
        cVar17 = (char)puVar46;
        puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
        puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
        puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
        puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
        puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
        puVar49[0x6f] = puVar49[0x6f] + (char)uVar51;
        uVar22 = *(int *)(uVar31 + 0x6f) * 0x77;
LAB_28d3_256f:
        puVar6 = puVar47;
        puVar47 = (undefined4 *)((int)puVar47 + 1);
        out(*(undefined *)puVar6,uVar51);
LAB_28d3_2570:
        *(byte *)(puVar48 + 0x39) = *(byte *)(puVar48 + 0x39) & (byte)((uint)puVar46 >> 8);
        goto LAB_28d3_2575;
      }
      *(byte *)(puVar48 + 0x3c) = *(byte *)(puVar48 + 0x3c) & (byte)((uint)puVar46 >> 8);
      puVar6 = (undefined4 *)((long)*(int *)((int)puVar48 + uVar22 + 0x74) * 0x73);
      puVar47 = (undefined4 *)puVar6;
      bVar54 = (undefined4 *)(long)(int)puVar47 != puVar6;
LAB_28d3_254c:
      puVar40 = (undefined2 *)((int)ppuVar35 + -2);
      ppuVar35 = (uint **)((int)ppuVar35 + -2);
      *puVar40 = puVar46;
      puVar6 = puVar47;
      puVar47 = (undefined4 *)((int)puVar47 + 2);
      out(*(undefined2 *)puVar6,uVar51);
LAB_28d3_254e:
      bVar16 = (byte)uVar51;
      bVar18 = (byte)uVar25;
      if (bVar54) goto code_r0x0002b280;
LAB_28d3_25c3:
      bVar26 = (byte)((uint)puVar46 >> 8);
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      puVar33[(int)puVar48] = puVar33[(int)puVar48] & bVar26;
      *(uint *)(puVar33 + (int)puVar48) = *(uint *)(puVar33 + (int)puVar48) & (uint)ppuVar35;
      *(uint *)(puVar33 + (int)puVar48) = *(uint *)(puVar33 + (int)puVar48) & (uint)ppuVar35;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      puVar3 = (uint *)((int)puVar47 + (int)(puVar33 + 0x40));
      bVar52 = 0xbfbf < *puVar3;
      *puVar3 = *puVar3 + 0x4040;
    }
    else {
joined_r0x0002b273:
      cVar17 = (char)puVar24;
      if (!bVar55) {
LAB_28d3_2564_1:
        puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
        puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
        *(uint *)((int)ppuVar35 + -2) = uVar22;
        puVar6 = puVar47;
        puVar47 = (undefined4 *)((int)puVar47 + 1);
        out(*(undefined *)puVar6,uVar51);
        goto code_r0x0002b280;
      }
      bVar18 = (byte)uVar25;
      if (bVar55) {
        if (!bVar52 && bVar54 == bVar55) {
          puVar46 = puVar46 + 1;
          goto code_r0x0002b30e;
        }
        puVar33[(int)puVar47] = puVar33[(int)puVar47] + (char)puVar46;
        goto LAB_28d3_25b2;
      }
      if (bVar54) goto LAB_28d3_254c;
      bVar18 = (byte)((uint)puVar46 >> 8);
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
      *(uint *)(puVar33 + (int)puVar48) = *(uint *)(puVar33 + (int)puVar48) & (uint)ppuVar35;
      *(uint *)(puVar33 + (int)puVar48) = *(uint *)(puVar33 + (int)puVar48) & (uint)ppuVar35;
      *(uint *)(puVar33 + (int)puVar47) = *(uint *)(puVar33 + (int)puVar47) & (uint)ppuVar35;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
code_r0x0002b30e:
      bVar16 = (byte)uVar51;
      bVar18 = (byte)uVar25;
      bVar52 = false;
      *(byte *)((int)puVar48 + (int)(puVar33 + 0x4040)) =
           *(byte *)((int)puVar48 + (int)(puVar33 + 0x4040)) & (byte)puVar46;
      puVar46 = puVar46 + 2;
    }
    bVar26 = bVar16 + *(byte *)(uVar22 + (int)puVar47);
    bVar54 = CARRY1(bVar16,*(byte *)(uVar22 + (int)puVar47)) || CARRY1(bVar26,bVar52);
    bVar26 = bVar26 + bVar52;
    bVar16 = bVar26 + *(byte *)(uVar22 + (int)puVar47);
    bVar52 = CARRY1(bVar26,*(byte *)(uVar22 + (int)puVar47)) || CARRY1(bVar16,bVar54);
    bVar16 = bVar16 + bVar54;
    bVar26 = bVar16 + *(byte *)(uVar22 + (int)puVar47);
    bVar54 = CARRY1(bVar16,*(byte *)(uVar22 + (int)puVar47)) || CARRY1(bVar26,bVar52);
    bVar26 = bVar26 + bVar52;
    bVar16 = bVar26 + *(byte *)(uVar22 + (int)puVar47);
    bVar27 = bVar16 + bVar54;
    bVar52 = CARRY1(bVar27,*(byte *)(uVar22 + (int)puVar47)) ||
             CARRY1(bVar27 + *(byte *)(uVar22 + (int)puVar47),
                    CARRY1(bVar26,*(byte *)(uVar22 + (int)puVar47)) || CARRY1(bVar16,bVar54));
    bVar16 = (char)puVar46 + 0x26;
    bVar54 = 0xeb < (byte)((char)puVar46 + 0x12U) || CARRY1(bVar16,bVar52);
    bVar16 = bVar16 + bVar52;
    bVar26 = bVar16 + 0x14;
    cVar17 = bVar26 + bVar54 + (0xeb < bVar16 || CARRY1(bVar26,bVar54));
    bVar52 = 0xfb < (byte)(cVar17 + 0x38U);
    pbVar1 = puVar33 + (int)puVar47;
    bVar27 = (byte)puVar33;
    bVar54 = *pbVar1 < bVar27 || (byte)(*pbVar1 - bVar27) < bVar52;
    *pbVar1 = (*pbVar1 - bVar27) - bVar52;
    pbVar1 = puVar33 + (int)puVar47;
    bVar16 = *pbVar1;
    bVar26 = *pbVar1;
    *pbVar1 = (bVar26 - bVar27) - bVar54;
    puVar33[(int)puVar47] =
         (puVar33[(int)puVar47] - bVar27) - (bVar16 < bVar27 || (byte)(bVar26 - bVar27) < bVar54);
    puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
    puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
    puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
    puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
    puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
    puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
    puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
    puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
    puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
    puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
    puVar46 = (undefined *)((byte)(cVar17 + 0x3c) + 8);
    goto code_r0x0002b36c;
  }
  bVar29 = (byte)(uVar23 >> 8);
  if (!CARRY1(bVar18,bVar26)) {
    puVar33[(int)puVar44] = puVar33[(int)puVar44] ^ bVar26;
    uVar25 = uVar25 - 1;
    puVar45 = (undefined2 *)((int)puVar44 + 1);
    out(*(undefined *)puVar44,uVar51);
    if (uVar25 != 0) {
      puVar7 = (undefined2 *)((int)puVar21 + 1);
      cVar17 = in(uVar51);
      *(char *)puVar21 = cVar17;
      puVar10 = (undefined *)((long)*(int *)((int)puVar44 + 0x21) * 0x7566);
      ppuVar35 = (uint **)puVar10;
      out(*(undefined *)puVar45,uVar51);
      puVar3 = (uint *)((int)puVar44 + 0x6b);
      *puVar3 = *puVar3 + (uint)((undefined *)(long)(int)ppuVar35 != puVar10) *
                          (((uint)(puVar44 + 1) & 3) - (*puVar3 & 3));
      out(puVar44[1],uVar51);
      out(*(undefined *)(puVar44 + 2),uVar51);
      *(byte *)(uVar22 + 0x75) = *(byte *)(uVar22 + 0x75) & (byte)(uVar25 >> 8);
      puVar21 = (uint *)((int)puVar21 + 3);
      uVar15 = in(uVar51);
      *puVar7 = uVar15;
      *(char *)(uVar22 + 0x6f) = *(char *)(uVar22 + 0x6f) + (char)uVar25;
      pbVar1 = (byte *)((int)puVar21 + uVar22 + 0x75);
      *pbVar1 = *pbVar1 & bVar27;
      puVar3 = (uint *)((int)(undefined2 *)((int)puVar44 + 5) + (int)(puVar33 + 0x20));
      bVar52 = 0 < (int)((uVar22 & 3) - (*puVar3 & 3));
      *puVar3 = *puVar3;
      uVar22 = (int)*(undefined4 *)(puVar44 + 0x35) * 0x6f20;
      puVar44 = (undefined2 *)((int)puVar44 + 5);
      goto code_r0x0002b0ce;
    }
    pcVar4 = (char *)((int)puVar45 + uVar22 + 0x61);
    *pcVar4 = *pcVar4 + bVar26;
    goto code_r0x0002b10f;
  }
  ppuVar35 = (uint **)(puVar46 + (uVar20 - 1));
  ppuVar39 = (uint **)(puVar46 + (uVar20 - 1));
  *(undefined2 *)(puVar46 + (uVar20 - 1)) = 0x6620;
  lVar11 = (long)*(int *)((int)puVar44 + 0x65) * 0x6f20;
  uVar22 = (uint)lVar11;
  bVar54 = (int)uVar22 != lVar11;
  if (bVar54) {
code_r0x0002b0ee:
    if (-1 < (char)bVar16) {
      *(byte *)(uVar22 + 0x69) = *(byte *)(uVar22 + 0x69) & bVar29;
      puVar45 = puVar44;
code_r0x0002b10f:
      *(byte *)(uVar22 + 0x69) = *(byte *)(uVar22 + 0x69) & (byte)((ulong)puVar24 >> 8);
      puVar44 = (undefined2 *)((int)puVar21 + 1);
      cVar17 = in(uVar51);
      *(char *)puVar21 = cVar17;
      *(byte *)(uVar22 + 0x75) = *(byte *)(uVar22 + 0x75) & (byte)(uVar25 >> 8);
      puVar21 = (uint *)((int)puVar21 + 3);
      uVar15 = in(uVar51);
      *puVar44 = uVar15;
      puVar49 = (undefined *)ppuVar39;
      puVar44 = puVar45;
      goto code_r0x0002b119;
    }
    puVar47 = (undefined4 *)(puVar44 + 1);
    out(*puVar44,uVar51);
    if (!bVar54) {
      out(*(undefined *)puVar47,uVar51);
      *(byte *)(uVar22 + 0x69) = *(byte *)(uVar22 + 0x69) & bVar29;
      cVar17 = in(uVar51);
      *(char *)puVar21 = cVar17;
      *(uint *)((int)ppuVar39 + -2) = uVar23;
      puVar46 = (undefined *)(*(int *)((int)puVar21 + uVar22 + 0x74) * 0x6f69);
      out(*puVar46,uVar51);
      puVar46[0x66] = puVar46[0x66] & bVar29;
      out(puVar46[1],uVar51);
      ppuVar36 = (uint **)(*(int *)((int)puVar21 + 0x65) * 0x4200);
      puVar21 = *ppuVar36;
      uVar22 = (uint)ppuVar36[2];
      puVar33 = (undefined *)ppuVar36[4];
      uVar51 = ppuVar36[5];
      uVar25 = (uint)ppuVar36[6];
      puVar24 = (undefined *)ZEXT24(ppuVar36[7]);
      ppuVar39 = ppuVar36 + 8;
      puVar45 = ppuVar36[1];
      goto code_r0x0002b10f;
    }
    *(byte *)((int)puVar21 + (int)(puVar33 + 100)) =
         *(byte *)((int)puVar21 + (int)(puVar33 + 100)) & bVar29;
code_r0x0002b15e:
    bVar54 = false;
    puVar3 = (uint *)((int)puVar47 + 0x6f);
    bVar52 = 0 < (int)(((uint)puVar47 & 3) - (*puVar3 & 3));
    *puVar3 = *puVar3;
code_r0x0002b1d8:
    puVar46 = (undefined *)puVar24;
    ppuVar37 = ppuVar39;
    puVar48 = puVar21;
    if (bVar54) {
LAB_28d3_2523:
      puVar6 = puVar47;
      puVar47 = (undefined4 *)((int)puVar47 + 1);
      out(*(undefined *)puVar6,uVar51);
      ppuVar39 = (uint **)((int)ppuVar37 + -2);
      ppuVar35 = (uint **)((int)ppuVar37 + -2);
      *(undefined2 *)((int)ppuVar37 + -2) = uVar51;
      if (!bVar54) {
        *(uint *)(puVar33 + (int)puVar47) =
             *(uint *)(puVar33 + (int)puVar47) >> ((byte)uVar25 & 0x1f);
        ppuVar37 = (uint **)((int)ppuVar37 + -2);
        goto code_r0x0002b2d2;
      }
      puVar3 = puVar48;
      puVar48 = (uint *)((int)puVar48 + 1);
      cVar17 = in(uVar51);
      *(char *)puVar3 = cVar17;
      if (!bVar52) goto LAB_28d3_252e;
      goto LAB_28d3_254e;
    }
LAB_28d3_24aa:
    puVar46 = (undefined *)puVar24;
    pbVar1 = (byte *)(uVar22 + 0x6f);
    bVar18 = *pbVar1;
    *pbVar1 = *pbVar1 + (byte)uVar25;
    bVar16 = (byte)((ulong)puVar24 >> 8);
    if (*pbVar1 == 0) {
      pbVar1 = (byte *)((int)puVar21 + (int)(puVar33 + 0x72));
      *pbVar1 = *pbVar1 & bVar16;
      bVar55 = (char)*pbVar1 < '\0';
      bVar52 = *pbVar1 == 0;
      goto LAB_28d3_24cd;
    }
    puVar48 = puVar21;
    if (!CARRY1(bVar18,(byte)uVar25)) goto LAB_28d3_2512;
    puVar3 = puVar21;
    puVar21 = puVar21 + 1;
    uVar31 = in(uVar51);
    *puVar3 = uVar31;
    pbVar1 = (byte *)((int)puVar47 + 0x65);
    bVar54 = false;
    *pbVar1 = *pbVar1 & bVar16;
    bVar52 = *pbVar1 == 0;
    if (!bVar52) {
      *puVar21 = *puVar21;
      puVar44 = (undefined2 *)((int)puVar47 + -1);
      puVar47 = (undefined4 *)((int)puVar47 + 1);
      out(*puVar44,uVar51);
      goto code_r0x0002b1ed;
    }
    puVar48 = puVar21;
    if (bVar52) goto LAB_28d3_2523;
LAB_28d3_258d_3:
    *(uint *)(puVar33 + (int)puVar47) = *(uint *)(puVar33 + (int)puVar47) >> ((byte)uVar25 & 0x1f);
    puVar33 = (undefined *)CONCAT11(0x25,(char)puVar33);
    *(uint *)(puVar33 + (int)puVar47) = *(uint *)(puVar33 + (int)puVar47) >> ((byte)uVar25 & 0x1f);
    puVar46 = (undefined *)&DAT_3000_6055;
    goto LAB_28d3_2585;
  }
code_r0x0002b0ce:
  puVar12 = (undefined2 *)((long)*(int *)((int)puVar44 + uVar22 + 0x65) * 0x7463);
  puVar45 = (undefined2 *)puVar12;
  bVar54 = (undefined2 *)(long)(int)puVar45 != puVar12;
  puVar47 = (undefined4 *)(puVar45 + 1);
  out(*puVar45,uVar51);
  if (bVar54) {
LAB_28d3_2420:
    ppuVar39 = ppuVar35;
    if (!bVar54) {
      pbVar1 = (byte *)((int)puVar47 + uVar22 + 0x6c);
      *pbVar1 = *pbVar1 & bVar29;
      out(*(undefined2 *)puVar47,uVar51);
LAB_28d3_2426:
      puVar12 = (undefined2 *)((int)puVar21 + uVar22 + 0x20);
      *puVar12 = *puVar12;
      puVar21 = *ppuVar35;
      puVar47 = (undefined4 *)ppuVar35[1];
      uVar22 = (uint)ppuVar35[2];
      puVar33 = (undefined *)ppuVar35[4];
      uVar51 = ppuVar35[5];
      uVar25 = (uint)ppuVar35[6];
      puVar24 = (undefined *)ZEXT24(ppuVar35[7]);
      ppuVar39 = ppuVar35 + 8;
      goto code_r0x0002b15e;
    }
LAB_28d3_249b:
    if (bVar54) {
      cVar17 = (char)puVar24;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
LAB_28d3_2516_1:
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + (char)puVar24;
      puVar48 = *ppuVar39;
      puVar47 = (undefined4 *)ppuVar39[1];
      uVar22 = (uint)ppuVar39[2];
      puVar33 = (undefined *)ppuVar39[4];
      uVar51 = ppuVar39[5];
      uVar25 = (uint)ppuVar39[6];
      puVar46 = (undefined *)ppuVar39[7];
      ppuVar37 = ppuVar39 + 8;
LAB_28d3_2512:
      cVar17 = (char)puVar46;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
      pcVar4 = (char *)((int)puVar48 + 0x61);
      *pcVar4 = *pcVar4 + (char)uVar25;
      if (*pcVar4 != '\0') {
        pbVar1 = (byte *)((int)puVar48 + (int)(puVar33 + 0x72));
        bVar54 = false;
        *pbVar1 = *pbVar1 & (byte)((uint)puVar46 >> 8);
        bVar52 = *pbVar1 == 0;
        if (!bVar52) goto LAB_28d3_258d_3;
        goto LAB_28d3_2523;
      }
      goto LAB_28d3_2585;
    }
    puVar6 = puVar47;
    puVar47 = (undefined4 *)((int)puVar47 + 1);
    out(*(undefined *)puVar6,uVar51);
    if (!bVar52) {
      puVar12 = (undefined2 *)((long)*(int *)((int)puVar47 + uVar22 + 0x65) * 0x7463);
      puVar44 = (undefined2 *)puVar12;
      bVar54 = (undefined2 *)(long)(int)puVar44 != puVar12;
      puVar47 = (undefined4 *)(puVar44 + 1);
      out(*puVar44,uVar51);
      goto code_r0x0002b1d8;
    }
    *(byte *)(uVar22 + 0x69) = *(byte *)(uVar22 + 0x69) & (byte)((ulong)puVar24 >> 8);
  }
  else {
    pcVar4 = (char *)((int)puVar47 + (int)(puVar33 + 0x61));
    *pcVar4 = *pcVar4 + (char)uVar51;
    if (*pcVar4 == '\0') {
      uVar25 = uVar25 - 1;
      puVar6 = puVar47;
      puVar47 = (undefined4 *)((int)puVar45 + 3);
      out(*(undefined *)puVar6,uVar51);
      pbVar1 = (byte *)((int)puVar21 + (int)(puVar33 + 0x6e));
      bVar54 = CARRY1(*pbVar1,(byte)uVar25);
      *pbVar1 = *pbVar1 + (byte)uVar25;
      bVar52 = *pbVar1 == 0;
      if (!bVar54 && !bVar52) {
        puVar44 = (undefined2 *)((int)puVar21 + 1);
        cVar17 = in(uVar51);
        *(char *)puVar21 = cVar17;
        puVar10 = (undefined *)((long)*(int *)((int)puVar45 + 0x23) * 0x656d);
        ppuVar35 = (uint **)puVar10;
        bVar54 = (undefined *)(long)(int)ppuVar35 != puVar10;
        puVar21 = (uint *)((int)puVar21 + 3);
        uVar15 = in(uVar51);
        *puVar44 = uVar15;
        puVar6 = puVar47;
        puVar47 = (undefined4 *)((int)puVar45 + 5);
        out(*(undefined2 *)puVar6,uVar51);
        goto LAB_28d3_2420;
      }
      if (bVar54) goto code_r0x0002b1ab;
      goto code_r0x0002b220;
    }
    pbVar1 = (byte *)(uVar22 + 0x6f);
    bVar18 = (byte)(uVar25 >> 8);
    *pbVar1 = *pbVar1 & bVar18;
    if (*pbVar1 != 0) {
      out(*puVar47,uVar51);
      if (*pbVar1 == 0) {
        *(char *)((int)puVar45 + 0x75) = *(char *)((int)puVar45 + 0x75) + (char)uVar51;
        out(puVar45[3],uVar51);
        pbVar1 = (byte *)((int)puVar21 + 0x61);
        bVar54 = false;
        *pbVar1 = *pbVar1 & bVar18;
        bVar16 = *pbVar1;
        puVar44 = (undefined2 *)((int)puVar45 + 9);
        out(*(undefined *)(puVar45 + 4),uVar51);
        ppuVar39 = ppuVar35;
        goto code_r0x0002b0ee;
      }
      goto LAB_28d3_2426;
    }
    puVar10 = (undefined *)((long)*(int *)((int)puVar47 + uVar22 + 0x6f) * 0x6d6e);
    puVar46 = (undefined *)puVar10;
    out(*puVar46,uVar51);
    uVar25 = uVar25 - 1;
    puVar47 = (undefined4 *)(puVar46 + 2);
    out(puVar46[1],uVar51);
    ppuVar37 = ppuVar35;
    if ((undefined *)(long)(int)puVar46 != puVar10 || uVar25 == 0) goto LAB_28d3_24aa;
    puVar44 = (undefined2 *)((int)puVar21 + 1);
    cVar17 = in(uVar51);
    *(char *)puVar21 = cVar17;
    ppuVar13 = (uint **)((long)*(int *)(puVar46 + 0x22) * 0x6f66);
    ppuVar37 = (uint **)ppuVar13;
    ppuVar9 = (uint **)(long)(int)ppuVar37;
    if (ppuVar9 == ppuVar13) {
      puVar21 = *ppuVar37;
      puVar46 = (undefined *)ppuVar37[1];
      uVar22 = (uint)ppuVar37[2];
      puVar33 = (undefined *)ppuVar37[4];
      uVar51 = ppuVar37[5];
      ppuVar38 = ppuVar37 + 6;
      uVar31 = (uint)ppuVar37[7];
      puVar24 = (undefined *)(ulong)uVar31;
      ppuVar37 = ppuVar37 + 8;
      uVar25 = (int)*ppuVar38 - 1;
      puVar47 = (undefined4 *)(puVar46 + 1);
      out(*puVar46,uVar51);
      if (ppuVar9 != ppuVar13 || uVar25 == 0) {
        *(char *)(uVar22 + 0x6f) = *(char *)(uVar22 + 0x6f) + (char)uVar25;
        goto code_r0x0002b1ed;
      }
      puVar48 = (uint *)((int)puVar21 + 1);
      cVar17 = in(uVar51);
      *(char *)puVar21 = cVar17;
      ppuVar35 = (uint **)(undefined *)((long)*(int *)(puVar46 + 0x21) * 0x6361);
      bVar52 = (undefined *)(long)(int)ppuVar35 !=
               (undefined *)((long)*(int *)(puVar46 + 0x21) * 0x6361);
      puVar3 = puVar21 + 0x3a;
      *puVar3 = *puVar3 + (uint)bVar52 * (((uint)ppuVar35 & 3) - (*puVar3 & 3));
      if (bVar52) goto code_r0x0002b193;
      pbVar1 = (byte *)((int)puVar48 + (int)(puVar33 + 0x74));
      bVar18 = (byte)uVar31;
      bVar54 = CARRY1(*pbVar1,bVar18);
      bVar52 = SCARRY1(*pbVar1,bVar18);
      *pbVar1 = *pbVar1 + bVar18;
      if (*pbVar1 == 0) goto code_r0x0002b21e;
      puVar21 = (uint *)((int)puVar21 + 3);
      uVar31 = in(uVar51);
      *puVar48 = uVar31;
      goto code_r0x0002b1b8;
    }
    puVar21 = (uint *)((int)puVar21 + 3);
    uVar15 = in(uVar51);
    *puVar44 = uVar15;
    puVar6 = puVar47;
    puVar47 = (undefined4 *)(puVar46 + 4);
    out(*(undefined2 *)puVar6,uVar51);
code_r0x0002b1ed:
    *(byte *)((int)puVar21 + 0x6f) = *(byte *)((int)puVar21 + 0x6f) & (byte)(uVar25 >> 8);
    *(byte *)(uVar22 + 0x69) = *(byte *)(uVar22 + 0x69) & (byte)((ulong)puVar24 >> 8);
    ppuVar39 = ppuVar37;
  }
  puVar46 = (undefined *)puVar24;
  puVar48 = (uint *)((int)puVar21 + 1);
  cVar17 = in(uVar51);
  *(char *)puVar21 = cVar17;
  uVar25 = uVar25 - 1;
  bVar55 = (int)uVar25 < 0;
  bVar52 = uVar25 == 0;
  puVar6 = puVar47;
  puVar47 = (undefined4 *)((int)puVar47 + 1);
  out(*(undefined *)puVar6,uVar51);
  puVar21 = puVar48;
  if (!bVar52) goto LAB_28d3_24cd;
LAB_28d3_252e:
  if (!bVar52) {
    out(*(undefined2 *)puVar47,uVar51);
    *(byte *)((int)puVar47 + 99) = *(byte *)((int)puVar47 + 99) & (byte)(uVar25 >> 8);
    *(char *)(uVar22 + 0x69) = *(char *)(uVar22 + 0x69) + (char)puVar46;
    cVar17 = in(uVar51);
    *(char *)puVar48 = cVar17;
    pbVar1 = (byte *)((int)puVar48 + (int)(puVar33 + 0x6d));
    bVar54 = false;
    *pbVar1 = *pbVar1 & (byte)((uint)puVar46 >> 8);
    bVar55 = (char)*pbVar1 < '\0';
    bVar52 = *pbVar1 == 0;
    puVar48 = *ppuVar39;
    puVar47 = (undefined4 *)ppuVar39[1];
    uVar22 = (uint)ppuVar39[2];
    puVar33 = (undefined *)ppuVar39[4];
    uVar51 = ppuVar39[5];
    uVar25 = (uint)ppuVar39[6];
    puVar46 = (undefined *)ppuVar39[7];
    puVar24 = (undefined *)ZEXT24(puVar46);
    ppuVar35 = ppuVar39 + 8;
    goto joined_r0x0002b273;
  }
  puVar46 = (undefined *)((uint)puVar46 & 0x28d3);
  ppuVar37 = ppuVar39;
code_r0x0002b2d2:
  bVar18 = (byte)uVar25;
  puVar33 = (undefined *)&DAT_3000_6055;
LAB_28d3_259d:
  pcVar4 = (char *)((int)puVar47 + uVar22 + 0xd325);
  cVar17 = (char)((uint)puVar33 >> 8);
  *pcVar4 = *pcVar4 - cVar17;
  pcVar4 = (char *)((int)puVar48 + uVar22 + 0xd325);
  *pcVar4 = *pcVar4 - cVar17;
  *(char *)((int)puVar47 + -0x2cdb) = *(char *)((int)puVar47 + -0x2cdb) - cVar17;
  pcVar4 = puVar33 + 0x7f;
  bVar55 = SBORROW1(*pcVar4,cVar17);
  *pcVar4 = *pcVar4 - cVar17;
  bVar54 = *pcVar4 < '\0';
  bVar52 = *pcVar4 != '\0';
  if (bVar52 && bVar55 == bVar54) {
    puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
LAB_28d3_262e_1:
    puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
  }
  else {
    if (bVar52 && bVar55 == bVar54) goto LAB_28d3_262e_1;
    ppuVar35 = ppuVar37;
    if (!bVar52 || bVar55 != bVar54) {
LAB_28d3_25b2:
      bVar16 = (byte)uVar51;
      cVar17 = (char)puVar46;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] + cVar17;
      bVar26 = (byte)((uint)puVar46 >> 8);
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar26;
      goto LAB_28d3_25c3;
    }
  }
  puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] | bVar18;
  *(byte *)((int)puVar47 + (int)(puVar33 + 0x40)) =
       *(byte *)((int)puVar47 + (int)(puVar33 + 0x40)) | (byte)puVar46;
code_r0x0002b36c:
  bVar18 = (char)puVar46 + 2;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] & bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  puVar33[(int)puVar47] = puVar33[(int)puVar47] + bVar18;
  pcVar14 = (code *)swi(3);
  puVar21 = (uint *)(*pcVar14)();
  return puVar21;
}



// Function: FUN_23f1_069f

void __cdecl16near FUN_23f1_069f(void)

{
  DAT_28d3_172f = 0x23f1;
  DAT_28d3_172d = 0x32a;
  DAT_28d3_172b = 0x23f1;
  DAT_28d3_1729 = 0x32a;
  DAT_28d3_178c = 0x1744;
  DAT_28d3_1794 = 0;
  DAT_28d3_1792 = 0;
  DAT_28d3_17aa = 0;
  DAT_28d3_17a8 = 0;
  DAT_28d3_1798 = 0;
  DAT_28d3_1796 = 0;
  DAT_28d3_179e = 0;
  DAT_28d3_179c = 0;
  DAT_28d3_1752 = 0;
  DAT_28d3_1750 = 0;
  DAT_28d3_1754 = 0;
  DAT_28d3_176c = 0;
  DAT_28d3_176a = 0;
  DAT_28d3_176e = 0;
  DAT_28d3_175a = 0;
  DAT_28d3_17a2 = 1;
  DAT_28d3_17a0 = 1;
  DAT_28d3_17bd = 0;
  DAT_28d3_17b9 = 0;
  return;
}



// Function: FUN_23f1_072d

undefined2
FUN_23f1_072d(undefined2 param_1,undefined2 *param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5,undefined2 param_6)

{
  undefined2 unaff_SS;
  undefined local_66 [100];
  
  *param_2 = 0;
  FUN_23f1_00ad(param_3,param_4,param_5,param_6,local_66,unaff_SS);
  DAT_28d3_17a6 = FUN_23f1_00f8(param_1,(undefined2 *)param_2,param_2._2_2_,local_66,unaff_SS);
  if (DAT_28d3_17a6 != 0) {
    FUN_23f1_00ad(param_3,param_4,0,0,local_66,unaff_SS);
    DAT_28d3_17a6 = FUN_23f1_00f8(param_1,(undefined2 *)param_2,param_2._2_2_,local_66,unaff_SS);
    if (DAT_28d3_17a6 != 0) {
      return 1;
    }
  }
  return 0;
}



// Function: FUN_23f1_07a5

undefined2 FUN_23f1_07a5(undefined2 param_1,undefined2 param_2,int param_3)

{
  int iVar1;
  undefined2 uVar2;
  
  FUN_23f1_00ad(0x1be3,(char *)s_String_reference_out_of_range_28d3_28cc + 7,param_3 * 0x1a + 0x17f8
                ,(char *)s_String_reference_out_of_range_28d3_28cc + 7,0x159b,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  DAT_28d3_172f = ((undefined2 *)&DAT_28d3_1810)[param_3 * 0xd];
  DAT_28d3_172d = ((undefined2 *)&DAT_28d3_180e)[param_3 * 0xd];
  if ((DAT_28d3_172d | DAT_28d3_172f) == 0) {
    iVar1 = FUN_23f1_072d(0xfffc,(undefined2 *)&DAT_28d3_179a,
                          (char *)s_String_reference_out_of_range_28d3_28cc + 7,0x159b,
                          (char *)s_String_reference_out_of_range_28d3_28cc + 7,param_1,param_2);
    if (iVar1 == 0) {
      iVar1 = FUN_23f1_034e((undefined2 *)&DAT_28d3_1796,
                            (char *)s_String_reference_out_of_range_28d3_28cc + 7,DAT_28d3_179a);
      if (iVar1 == 0) {
        iVar1 = FUN_23f1_013d(DAT_28d3_1796,DAT_28d3_1798,DAT_28d3_179a,0);
        if (iVar1 == 0) {
          iVar1 = FUN_23f1_03f4(DAT_28d3_1796,DAT_28d3_1798);
          if (iVar1 == param_3) {
            DAT_28d3_172f = ((undefined2 *)&DAT_28d3_1810)[param_3 * 0xd];
            DAT_28d3_172d = ((undefined2 *)&DAT_28d3_180e)[param_3 * 0xd];
            FUN_23f1_00eb();
            goto LAB_23f1_0899;
          }
          FUN_23f1_00eb();
          DAT_28d3_17a6 = 0xfffc;
          FUN_23f1_0380((undefined2 *)&DAT_28d3_1796,
                        (char *)s_String_reference_out_of_range_28d3_28cc + 7,DAT_28d3_179a);
        }
        else {
          FUN_23f1_0380((undefined2 *)&DAT_28d3_1796,
                        (char *)s_String_reference_out_of_range_28d3_28cc + 7,DAT_28d3_179a);
        }
      }
      else {
        FUN_23f1_00eb();
        DAT_28d3_17a6 = 0xfffb;
      }
    }
    uVar2 = 0;
  }
  else {
    DAT_28d3_1798 = 0;
    DAT_28d3_1796 = 0;
    DAT_28d3_179a = 0;
LAB_23f1_0899:
    uVar2 = 1;
  }
  return uVar2;
}



// Function: FUN_23f1_08a1

void __cdecl16far FUN_23f1_08a1(void)

{
  undefined *puVar1;
  undefined1 *puVar2;
  undefined *puVar3;
  undefined2 uVar4;
  int iVar5;
  undefined2 in_DX;
  undefined1 *puVar6;
  
  if (DAT_28d3_17b9 == 0) {
    FUN_23f1_032a((char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  FUN_23f1_0f00(0,0,*(undefined2 *)(DAT_28d3_178a + 2),*(undefined2 *)(DAT_28d3_178a + 4),1);
  puVar3 = (undefined *)FUN_23f1_1db3();
  puVar6 = (undefined1 *)&DAT_28d3_17db;
  for (iVar5 = 0x11; iVar5 != 0; iVar5 = iVar5 + -1) {
    puVar2 = puVar6;
    puVar6 = puVar6 + 1;
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar2 = *puVar1;
  }
  FUN_23f1_13e9((undefined1 *)&DAT_28d3_17db,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  iVar5 = FUN_23f1_1d98();
  if (iVar5 != 1) {
    FUN_23f1_138d(0);
  }
  DAT_28d3_17b2 = 0;
  uVar4 = FUN_23f1_1d7d();
  FUN_23f1_1d5c(uVar4);
  uVar4 = FUN_23f1_1d7d();
  FUN_23f1_125e(0x1969,(char *)s_String_reference_out_of_range_28d3_28cc + 7,uVar4);
  uVar4 = FUN_23f1_1d7d();
  FUN_23f1_1211(1,uVar4);
  FUN_23f1_115d(0,0,1);
  FUN_23f1_165b(0,0,1);
  FUN_23f1_161a(0,2);
  FUN_23f1_19e7(0x23f1,0);
  FUN_23f1_1007(0,0);
  return;
}



// Function: FUN_23f1_0979

void __cdecl16far FUN_23f1_0979(uint *param_1,int *param_2,uint param_3,uint param_4)

{
  int iVar1;
  undefined2 uVar2;
  undefined *puVar3;
  undefined *puVar4;
  char *pcVar5;
  uint local_a;
  undefined *local_6;
  
  pcVar5 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  local_a = 0;
  DAT_28d3_172b = DAT_28d3_158e + (DAT_28d3_158c + 0x20U >> 4);
  DAT_28d3_1729 = 0;
  if (*param_1 == 0) {
    while( true ) {
      if ((DAT_28d3_17f6 <= (int)local_a) || (*param_1 != 0)) goto LAB_23f1_0a10;
      if (((((undefined2 *)&DAT_28d3_180a)[local_a * 0xd] |
           ((undefined2 *)&DAT_28d3_180c)[local_a * 0xd]) != 0) &&
         (iVar1 = (*(code *)((undefined2 *)&DAT_28d3_180a)[local_a * 0xd])(0x23f1,pcVar5),
         -1 < iVar1)) break;
      local_a = local_a + 1;
    }
    DAT_28d3_178e = local_a;
    *param_1 = local_a + 0x80;
    *param_2 = iVar1;
  }
LAB_23f1_0a10:
  FUN_23f1_1aab((undefined2 *)&DAT_28d3_178e,(char *)s_String_reference_out_of_range_28d3_28cc + 7,
                (uint *)param_1,param_1._2_2_,(int *)param_2,param_2._2_2_);
  if ((int)*param_1 < 0) {
    DAT_28d3_17a6 = 0xfffe;
    *param_1 = 0xfffe;
  }
  else {
    DAT_28d3_1790 = *param_2;
    if ((param_3 | param_4) == 0) {
      DAT_28d3_15a8 = '\0';
    }
    else {
      FUN_23f1_0031(param_3,param_4,(undefined1 *)&DAT_28d3_15a8,
                    (char *)s_String_reference_out_of_range_28d3_28cc + 7);
      if (DAT_28d3_15a8 != '\0') {
        puVar4 = (undefined *)
                 FUN_23f1_0094((undefined1 *)&DAT_28d3_15a8,
                               (char *)s_String_reference_out_of_range_28d3_28cc + 7);
        uVar2 = (undefined2)((ulong)puVar4 >> 0x10);
        puVar3 = (undefined *)puVar4;
        if ((puVar3[-1] != ':') && (puVar3[-1] != '\\')) {
          *puVar4 = 0x5c;
          local_6 = (undefined *)CONCAT22(uVar2,puVar3 + 1);
          *local_6 = 0;
        }
      }
    }
    if (0x80 < (int)*param_1) {
      DAT_28d3_178e = *param_1 & 0x7f;
    }
    iVar1 = FUN_23f1_07a5((undefined1 *)&DAT_28d3_15a8,
                          (char *)s_String_reference_out_of_range_28d3_28cc + 7,DAT_28d3_178e);
    if (iVar1 == 0) {
      *param_1 = DAT_28d3_17a6;
    }
    else {
      puVar3 = (undefined *)0x1744;
      for (iVar1 = 0x45; iVar1 != 0; iVar1 = iVar1 + -1) {
        puVar4 = puVar3;
        puVar3 = puVar3 + 1;
        *puVar4 = 0;
      }
      iVar1 = FUN_23f1_034e((undefined2 *)&DAT_28d3_1750,
                            (char *)s_String_reference_out_of_range_28d3_28cc + 7,DAT_28d3_15f9);
      if (iVar1 == 0) {
        uRam0002a475 = 0;
        DAT_28d3_175a = 0;
        DAT_28d3_179e = DAT_28d3_1752;
        DAT_28d3_179c = DAT_28d3_1750;
        DAT_28d3_176c = DAT_28d3_1752;
        DAT_28d3_176a = DAT_28d3_1750;
        DAT_28d3_1754 = DAT_28d3_15f9;
        DAT_28d3_176e = DAT_28d3_15f9;
        pcRam0002a490 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
        puRam0002a48e = (undefined2 *)&DAT_28d3_17a6;
        if (DAT_28d3_1789 == '\0') {
          FUN_23f1_18b4(0x23f1,0x1744,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
        }
        else {
          FUN_23f1_18b9(0x1744,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
        }
        FUN_23f1_0178(0x1731,(char *)s_String_reference_out_of_range_28d3_28cc + 7,DAT_28d3_17ac,
                      DAT_28d3_17ae,0x13);
        FUN_23f1_1b59(0x1744,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
        if (bRam0002a461 == 0) {
          DAT_28d3_178c = 0x1744;
          DAT_28d3_178a = 0x1731;
          DAT_28d3_17a4 = FUN_23f1_1df1();
          DAT_28d3_17a0 = DAT_28d3_173f;
          DAT_28d3_17a2 = (undefined2 *)&DAT_28d3_2710;
          DAT_28d3_1789 = 3;
          DAT_28d3_17b9 = 3;
          FUN_23f1_08a1();
          DAT_28d3_17a6 = 0;
          return;
        }
        DAT_28d3_17a6 = (uint)bRam0002a461;
      }
      else {
        DAT_28d3_17a6 = 0xfffb;
        *param_1 = 0xfffb;
        FUN_23f1_0380((undefined2 *)&DAT_28d3_1796,
                      (char *)s_String_reference_out_of_range_28d3_28cc + 7,DAT_28d3_179a);
      }
    }
  }
  FUN_23f1_069f();
  return;
}



// Function: FUN_23f1_0bd6

int __cdecl16far
FUN_23f1_0bd6(char *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_6;
  
  uVar3 = FUN_23f1_0094(param_1,param_2);
  local_6 = (char *)CONCAT22((int)((ulong)uVar3 >> 0x10),(char *)((int)uVar3 + -1));
  while ((*local_6 == ' ' && (param_1 <= (char *)local_6))) {
    *local_6 = '\0';
    local_6 = (char *)CONCAT22(local_6._2_2_,(char *)local_6 + -1);
  }
  FUN_23f1_0071(param_1,param_2);
  iVar2 = 0;
  while( true ) {
    if (DAT_28d3_17f6 <= iVar2) {
      if (DAT_28d3_17f6 < 10) {
        FUN_23f1_0031(param_1,param_2,DAT_28d3_17f6 * 0x1a + 0x17f8,
                      (char *)s_String_reference_out_of_range_28d3_28cc + 7);
        FUN_23f1_0031(param_1,param_2,DAT_28d3_17f6 * 0x1a + 0x1801,
                      (char *)s_String_reference_out_of_range_28d3_28cc + 7);
        iVar2 = DAT_28d3_17f6;
        ((undefined2 *)&DAT_28d3_180c)[DAT_28d3_17f6 * 0xd] = param_4;
        ((undefined2 *)&DAT_28d3_180a)[iVar2 * 0xd] = param_3;
        iVar2 = DAT_28d3_17f6 + 10;
        DAT_28d3_17f6 = DAT_28d3_17f6 + 1;
      }
      else {
        iVar2 = -0xb;
        DAT_28d3_17a6 = 0xfff5;
      }
      return iVar2;
    }
    iVar1 = FUN_23f1_0050(8,iVar2 * 0x1a + 0x17f8,
                          (char *)s_String_reference_out_of_range_28d3_28cc + 7,param_1,param_2);
    if (iVar1 == 0) break;
    iVar2 = iVar2 + 1;
  }
  ((undefined2 *)&DAT_28d3_180c)[iVar2 * 0xd] = param_4;
  ((undefined2 *)&DAT_28d3_180a)[iVar2 * 0xd] = param_3;
  return iVar2 + 10;
}



// Function: FUN_23f1_0cbb

int __cdecl16far FUN_23f1_0cbb(undefined2 *param_1,undefined2 param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_6;
  
  uVar4 = FUN_23f1_0094(param_1,param_2);
  local_6 = (undefined2 *)CONCAT22((int)((ulong)uVar4 >> 0x10),(undefined2 *)((int)uVar4 + -1));
  while ((*(char *)local_6 == ' ' && (param_1 <= (undefined2 *)local_6))) {
    *(char *)local_6 = '\0';
    local_6 = (undefined2 *)CONCAT22(local_6._2_2_,(undefined2 *)((int)(undefined2 *)local_6 + -1));
  }
  FUN_23f1_0071(param_1,param_2);
  iVar3 = 0;
  while( true ) {
    if (DAT_28d3_15fb <= iVar3) {
      if (DAT_28d3_15fb < 0x14) {
        uVar1 = *param_1;
        iVar3 = DAT_28d3_15fb * 0xf;
        *(undefined2 *)((int)(undefined2 *)&DAT_28d3_1609 + iVar3) = param_1[1];
        *(undefined2 *)((int)(undefined2 *)&DAT_28d3_1607 + iVar3) = uVar1;
        iVar3 = DAT_28d3_15fb + 1;
        DAT_28d3_15fb = iVar3;
      }
      else {
        iVar3 = -0xb;
        DAT_28d3_17a6 = 0xfff5;
      }
      return iVar3;
    }
    iVar2 = FUN_23f1_0050(4,(int)(undefined2 *)&DAT_28d3_1607 + iVar3 * 0xf,
                          (char *)s_String_reference_out_of_range_28d3_28cc + 7,param_1,param_2);
    if (iVar2 == 0) break;
    iVar3 = iVar3 + 1;
  }
  return iVar3 + 1;
}



// Function: FUN_23f1_0d62

void __cdecl16far FUN_23f1_0d62(int param_1)

{
  if (DAT_28d3_17b9 != 2) {
    if (DAT_28d3_17a4 < param_1) {
      DAT_28d3_17a6 = 0xfff6;
    }
    else {
      if ((DAT_28d3_1792 | DAT_28d3_1794) != 0) {
        DAT_28d3_172b = DAT_28d3_1794;
        DAT_28d3_1729 = DAT_28d3_1792;
        DAT_28d3_1794 = 0;
        DAT_28d3_1792 = 0;
      }
      DAT_28d3_1790 = param_1;
      FUN_23f1_1929(param_1,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
      FUN_23f1_0178(0x1731,(char *)s_String_reference_out_of_range_28d3_28cc + 7,DAT_28d3_17ac,
                    DAT_28d3_17ae,0x13);
      DAT_28d3_178a = 0x1731;
      DAT_28d3_178c = 0x1744;
      DAT_28d3_17a0 = DAT_28d3_173f;
      DAT_28d3_17a2 = (undefined2 *)&DAT_28d3_2710;
      FUN_23f1_08a1();
    }
  }
  return;
}



// Function: FUN_23f1_0de8

undefined2 __cdecl16far FUN_23f1_0de8(void)

{
  if (DAT_28d3_1789 == '\0') {
    DAT_28d3_17a6 = 0xffff;
    return 0xffff;
  }
  return DAT_28d3_1790;
}



// Function: FUN_23f1_0e0a

void __cdecl16far FUN_23f1_0e0a(void)

{
  FUN_23f1_195f((char *)s_String_reference_out_of_range_28d3_28cc + 7);
  if ((DAT_28d3_1792 | DAT_28d3_1794) == 0) {
    DAT_28d3_1794 = DAT_28d3_172b;
    DAT_28d3_1792 = DAT_28d3_1729;
    DAT_28d3_172b = 0x23f1;
    DAT_28d3_1729 = 0x32a;
  }
  return;
}



// Function: FUN_23f1_0e3e

void __cdecl16far FUN_23f1_0e3e(void)

{
  int iVar1;
  undefined2 *puVar2;
  uint uVar3;
  
  if (DAT_28d3_1789 == '\0') {
    DAT_28d3_17a6 = 0xffff;
  }
  else {
    DAT_28d3_1789 = '\0';
    FUN_23f1_0e0a((char *)s_String_reference_out_of_range_28d3_28cc + 7);
    FUN_23f1_0380((undefined2 *)&DAT_28d3_179c,(char *)s_String_reference_out_of_range_28d3_28cc + 7
                  ,DAT_28d3_15f9);
    if ((DAT_28d3_1796 | DAT_28d3_1798) != 0) {
      FUN_23f1_0380((undefined2 *)&DAT_28d3_1796,
                    (char *)s_String_reference_out_of_range_28d3_28cc + 7,DAT_28d3_179a);
      iVar1 = DAT_28d3_178e;
      ((undefined2 *)&DAT_28d3_1810)[DAT_28d3_178e * 0xd] = 0;
      ((undefined2 *)&DAT_28d3_180e)[iVar1 * 0xd] = 0;
    }
    FUN_23f1_069f();
    puVar2 = (undefined2 *)&DAT_28d3_15fd;
    for (uVar3 = 0; uVar3 < 0x14; uVar3 = uVar3 + 1) {
      if ((*(char *)(puVar2 + 5) != '\0') && (puVar2[4] != 0)) {
        FUN_23f1_0380(puVar2,(char *)s_String_reference_out_of_range_28d3_28cc + 7,puVar2[4]);
        puVar2[1] = 0;
        *puVar2 = 0;
        puVar2[3] = 0;
        puVar2[2] = 0;
        puVar2[4] = 0;
      }
      puVar2 = (undefined2 *)((int)puVar2 + 0xf);
    }
  }
  return;
}



// Function: FUN_23f1_0ee5

void __cdecl16far FUN_23f1_0ee5(void)

{
  FUN_23f1_1b7e((char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_23f1_1007(0,0);
  return;
}



// Function: FUN_23f1_0f00

void __cdecl16far
FUN_23f1_0f00(int param_1,int param_2,uint param_3,uint param_4,undefined2 param_5)

{
  if ((((param_1 < 0) || (param_2 < 0)) || (*(uint *)(DAT_28d3_178a + 2) < param_3)) ||
     (((*(uint *)(DAT_28d3_178a + 4) < param_4 || ((int)param_3 < param_1)) ||
      ((int)param_4 < param_2)))) {
    DAT_28d3_17a6 = 0xfff5;
  }
  else {
    DAT_28d3_17bf = param_1;
    DAT_28d3_17c1 = param_2;
    DAT_28d3_17c3 = param_3;
    DAT_28d3_17c5 = param_4;
    DAT_28d3_17c7 = param_5;
    FUN_23f1_18fd(param_1,param_2,param_3,param_4,param_5,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7);
    FUN_23f1_1007(0,0);
  }
  return;
}



// Function: FUN_23f1_0f77

void __cdecl16far FUN_23f1_0f77(undefined2 param_1,undefined2 param_2)

{
  FUN_1000_4b0a((undefined2 *)&DAT_28d3_17bf,(char *)s_String_reference_out_of_range_28d3_28cc + 7,
                param_1,param_2);
  return;
}



// Function: FUN_23f1_0f96

void __cdecl16far FUN_23f1_0f96(void)

{
  char *pcVar1;
  int iVar2;
  undefined2 uVar3;
  
  pcVar1 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  iVar2 = DAT_28d3_17cf;
  uVar3 = DAT_28d3_17d1;
  FUN_23f1_1211(0,0,(char *)s_String_reference_out_of_range_28d3_28cc + 7,DAT_28d3_17cf,
                DAT_28d3_17d1);
  FUN_23f1_1c32(0,0,DAT_28d3_17c3 - DAT_28d3_17bf,DAT_28d3_17c5 - DAT_28d3_17c1);
  if (iVar2 == 0xc) {
    FUN_23f1_125e((undefined1 *)&DAT_28d3_17d3,(char *)s_String_reference_out_of_range_28d3_28cc + 7
                  ,uVar3);
  }
  else {
    FUN_23f1_1211(iVar2,uVar3,pcVar1);
  }
  FUN_23f1_1007(0,0);
  return;
}



// Function: FUN_23f1_1007

void __cdecl16far FUN_23f1_1007(undefined2 param_1,undefined2 param_2)

{
  FUN_23f1_1b95(param_1,param_2,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  DAT_28d3_17b5 = param_1;
  DAT_28d3_17b7 = param_2;
  return;
}



// Function: FUN_23f1_102e

void __cdecl16far FUN_23f1_102e(int param_1,int param_2)

{
  FUN_23f1_1007(DAT_28d3_17b5 + param_1,DAT_28d3_17b7 + param_2,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  return;
}



// Function: FUN_23f1_104e

undefined2 __cdecl16far FUN_23f1_104e(void)

{
  return DAT_28d3_17b5;
}



// Function: FUN_23f1_105d

undefined2 __cdecl16far FUN_23f1_105d(void)

{
  return DAT_28d3_17b7;
}



// Function: FUN_23f1_106c

undefined2 __cdecl16far FUN_23f1_106c(void)

{
  return *(undefined2 *)(DAT_28d3_178a + 2);
}



// Function: FUN_23f1_107f

undefined2 __cdecl16far FUN_23f1_107f(void)

{
  return *(undefined2 *)(DAT_28d3_178a + 4);
}



// Function: FUN_23f1_1092

int __cdecl16far FUN_23f1_1092(void)

{
  if (DAT_28d3_17b9 != 3) {
    return 0;
  }
  return DAT_28d3_178e * 0x1a + 0x1801;
}



// Function: FUN_23f1_10b8

char * __cdecl16far FUN_23f1_10b8(undefined2 param_1)

{
  undefined2 uVar1;
  undefined2 in_DX;
  char *pcVar2;
  char *pcVar3;
  
  pcVar3 = (char *)s_String_reference_out_of_range_28d3_28cc + 7;
  pcVar2 = (char *)s_Bad_Mode_28d3_1971;
  uVar1 = FUN_23f1_1dd0(param_1,(char *)s_Bad_Mode_28d3_1971,
                        (char *)s_String_reference_out_of_range_28d3_28cc + 7,
                        (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_23f1_0031(uVar1,in_DX,pcVar2,pcVar3);
  return (char *)s_Bad_Mode_28d3_1971;
}



// Function: FUN_23f1_10dc

void __cdecl16far FUN_23f1_10dc(undefined2 param_1,undefined2 param_2)

{
  FUN_23f1_1bb2(param_1,param_2,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_23f1_1007(param_1,param_2);
  return;
}



// Function: FUN_23f1_1103

void __cdecl16far FUN_23f1_1103(int param_1,int param_2)

{
  FUN_23f1_1bb2(DAT_28d3_17b5 + param_1,DAT_28d3_17b7 + param_2,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_23f1_1007(DAT_28d3_17b5 + param_1,DAT_28d3_17b7 + param_2);
  return;
}



// Function: FUN_23f1_113e

void __cdecl16far FUN_23f1_113e(undefined2 param_1,undefined2 param_2)

{
  FUN_1000_4b0a((undefined2 *)&DAT_28d3_17c9,(char *)s_String_reference_out_of_range_28d3_28cc + 7,
                param_1,param_2);
  return;
}



// Function: FUN_23f1_115d

void __cdecl16far FUN_23f1_115d(uint param_1,undefined2 param_2,uint param_3)

{
  if ((param_1 < 5) && (param_3 < 4)) {
    DAT_28d3_17c9 = param_1;
    DAT_28d3_17cb = param_2;
    DAT_28d3_17cd = param_3;
    FUN_23f1_1e8c(param_1,param_2,param_3,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  else {
    DAT_28d3_17a6 = 0xfff5;
  }
  return;
}



// Function: FUN_23f1_119e

void __cdecl16far
FUN_23f1_119e(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  FUN_23f1_1bcf(param_1,param_2,param_3,param_2,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_23f1_1bcf(param_3,param_2,param_3,param_4);
  FUN_23f1_1bcf(param_3,param_4,param_1,param_4);
  FUN_23f1_1bcf(param_1,param_4,param_1,param_2);
  return;
}



// Function: FUN_23f1_11f4

void __cdecl16far FUN_23f1_11f4(undefined2 *param_1)

{
  undefined2 uVar1;
  
  uVar1 = DAT_28d3_17cf;
  ((undefined2 *)param_1)[1] = DAT_28d3_17d1;
  *param_1 = uVar1;
  return;
}



// Function: FUN_23f1_1211

void __cdecl16far FUN_23f1_1211(uint param_1,undefined2 param_2)

{
  if (param_1 < 0xc) {
    DAT_28d3_17cf = param_1;
    DAT_28d3_17d1 = param_2;
    FUN_23f1_1efa(param_1,param_2,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  else {
    DAT_28d3_17a6 = 0xfff5;
  }
  return;
}



// Function: FUN_23f1_1245

void __cdecl16far FUN_23f1_1245(undefined *param_1)

{
  undefined1 *puVar1;
  undefined *puVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined *puVar5;
  
  puVar4 = (undefined1 *)&DAT_28d3_17d3;
  puVar5 = (undefined *)param_1;
  for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar2 = puVar5;
    puVar5 = puVar5 + 1;
    puVar1 = puVar4;
    puVar4 = puVar4 + 1;
    *puVar2 = *puVar1;
  }
  return;
}



// Function: FUN_23f1_125e

void __cdecl16far FUN_23f1_125e(undefined *param_1,uint param_2)

{
  undefined *puVar1;
  undefined1 *puVar2;
  uint uVar3;
  int iVar4;
  undefined *puVar5;
  undefined1 *puVar6;
  undefined2 uVar7;
  
  uVar3 = FUN_23f1_1d7d((char *)s_String_reference_out_of_range_28d3_28cc + 7);
  if (uVar3 < param_2) {
    DAT_28d3_17a6 = 0xfff5;
  }
  else {
    DAT_28d3_17cf = 0xc;
    DAT_28d3_17d1 = param_2;
    uVar7 = (undefined2)((ulong)param_1 >> 0x10);
    puVar6 = (undefined1 *)&DAT_28d3_17d3;
    puVar5 = (undefined *)param_1;
    for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
      puVar2 = puVar6;
      puVar6 = puVar6 + 1;
      puVar1 = puVar5;
      puVar5 = puVar5 + 1;
      *puVar2 = *puVar1;
    }
    FUN_23f1_1a0a((undefined *)param_1,uVar7,param_2);
  }
  return;
}



// Function: FUN_23f1_12b3

void FUN_23f1_12b3(void)

{
  undefined2 uVar1;
  int iVar2;
  
  iVar2 = DAT_28d3_17a0 >> 0xf;
  uVar1 = FUN_1000_3eb2(DAT_28d3_17a2,DAT_28d3_17a2 >> 0xf);
  FUN_1000_3ecc(0x1000,uVar1,iVar2);
  return;
}



// Function: FUN_23f1_12d5

void __cdecl16far
FUN_23f1_12d5(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5)

{
  undefined2 uVar1;
  
  uVar1 = FUN_23f1_12b3(param_5,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_23f1_1c96(param_1,param_2,param_3,param_4,param_5,uVar1);
  return;
}



// Function: FUN_23f1_1300

void __cdecl16far FUN_23f1_1300(undefined2 param_1,undefined2 param_2,undefined2 param_3)

{
  undefined2 uVar1;
  
  uVar1 = FUN_23f1_12b3(param_3,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_23f1_1c96(param_1,param_2,0,0x168,param_3,uVar1);
  return;
}



// Function: FUN_23f1_132c

void __cdecl16far FUN_23f1_132c(undefined2 *param_1,undefined2 *param_2)

{
  *param_1 = DAT_28d3_17a0;
  *param_2 = DAT_28d3_17a2;
  return;
}



// Function: FUN_23f1_134a

void __cdecl16far FUN_23f1_134a(undefined2 param_1,undefined2 param_2)

{
  DAT_28d3_17a0 = param_1;
  DAT_28d3_17a2 = param_2;
  return;
}



// Function: FUN_23f1_1362

void __cdecl16far
FUN_23f1_1362(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5)

{
  undefined2 uVar1;
  
  uVar1 = FUN_23f1_12b3(param_5,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  FUN_23f1_1d03(param_1,param_2,param_3,param_4,param_5,uVar1);
  return;
}



// Function: FUN_23f1_138d

void __cdecl16far FUN_23f1_138d(uint param_1)

{
  if (param_1 < 0x10) {
    DAT_28d3_17b2 = (undefined)param_1;
    if (param_1 == 0) {
      DAT_28d3_17dc = '\0';
    }
    else {
      DAT_28d3_17dc = ((undefined1 *)&DAT_28d3_17dc)[param_1];
    }
    FUN_23f1_1e0d((int)DAT_28d3_17dc,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  return;
}



// Function: FUN_23f1_13c7

undefined __cdecl16far FUN_23f1_13c7(void)

{
  return DAT_28d3_17b0;
}



// Function: FUN_23f1_13d8

undefined __cdecl16far FUN_23f1_13d8(void)

{
  return DAT_28d3_17b2;
}



// Function: FUN_23f1_13e9

void __cdecl16far FUN_23f1_13e9(byte *param_1,undefined2 param_2)

{
  undefined1 *puVar1;
  undefined *puVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined *puVar5;
  undefined2 unaff_SS;
  undefined local_1c [17];
  undefined local_b;
  byte *local_a;
  uint local_6;
  uint local_4;
  
  local_a = (byte *)CONCAT22(param_2,param_1);
  if (DAT_28d3_17b9 != 0) {
    if (*local_a < 0x11) {
      local_6 = (uint)*local_a;
    }
    else {
      local_6 = 0x10;
    }
    for (local_4 = 0; local_4 < local_6; local_4 = local_4 + 1) {
      if (-1 < (char)param_1[local_4 + 1]) {
        ((undefined1 *)&DAT_28d3_17dc)[local_4] = param_1[local_4 + 1];
      }
    }
    if (param_1[1] != 0xff) {
      DAT_28d3_17b2 = 0;
    }
    puVar4 = (undefined1 *)&DAT_28d3_17db;
    puVar5 = local_1c;
    for (iVar3 = 0x11; iVar3 != 0; iVar3 = iVar3 + -1) {
      puVar2 = puVar5;
      puVar5 = puVar5 + 1;
      puVar1 = puVar4;
      puVar4 = puVar4 + 1;
      *puVar2 = *puVar1;
    }
    local_b = DAT_28d3_17bb;
    FUN_23f1_1e71(local_1c);
  }
  return;
}



// Function: FUN_23f1_148f

void __cdecl16far FUN_23f1_148f(uint param_1,int param_2)

{
  if (((DAT_28d3_17b9 != 0) && (param_1 <= DAT_28d3_17db - 1)) && (-1 < param_2)) {
    ((undefined1 *)&DAT_28d3_17dc)[param_1] = (undefined)param_2;
    if (param_1 == 0) {
      DAT_28d3_17b2 = 0;
    }
    FUN_23f1_1e52(param_1,param_2,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  return;
}



// Function: FUN_23f1_14d2

void __cdecl16far FUN_23f1_14d2(undefined2 param_1,undefined2 param_2)

{
  FUN_1000_4b0a((undefined1 *)&DAT_28d3_17db,(char *)s_String_reference_out_of_range_28d3_28cc + 7,
                param_1,param_2);
  return;
}



// Function: FUN_23f1_14f1

int __cdecl16far
FUN_23f1_14f1(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  int iVar1;
  
  iVar1 = FUN_23f1_1a5a(param_1,param_2,param_3,param_4,
                        (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  if (iVar1 == 0) {
    DAT_28d3_17a6 = 0xfff5;
    iVar1 = -1;
  }
  return iVar1;
}



// Function: FUN_23f1_1526

void __cdecl16far FUN_23f1_1526(int param_1,int param_2,int *param_3,undefined2 param_4)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  undefined2 uVar4;
  
  uVar4 = (undefined2)((ulong)param_3 >> 0x10);
  piVar3 = (int *)param_3;
  uVar1 = piVar3[1];
  uVar2 = *(int *)(DAT_28d3_178a + 4) - (param_2 + DAT_28d3_17c1);
  if (uVar1 < uVar2) {
    uVar2 = uVar1;
  }
  if ((((uint)(param_1 + DAT_28d3_17bf + *param_3) <= *(uint *)(DAT_28d3_178a + 2)) &&
      (SCARRY2(param_1,DAT_28d3_17bf) == param_1 + DAT_28d3_17bf < 0)) &&
     (SCARRY2(param_2,DAT_28d3_17c1) == param_2 + DAT_28d3_17c1 < 0)) {
    piVar3[1] = uVar2;
    FUN_23f1_20a3(param_1,param_2,piVar3,uVar4,param_4,
                  (char *)s_String_reference_out_of_range_28d3_28cc + 7);
    piVar3[1] = uVar1;
  }
  return;
}



// Function: FUN_23f1_15af

void __cdecl16far FUN_23f1_15af(undefined2 param_1,undefined2 param_2)

{
  FUN_1000_4b0a((undefined2 *)&DAT_28d3_17ec,(char *)s_String_reference_out_of_range_28d3_28cc + 7,
                param_1,param_2);
  return;
}



// Function: FUN_23f1_15ce

void __cdecl16far FUN_23f1_15ce(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  
  FUN_23f1_1f2a(DAT_28d3_17b5,DAT_28d3_17b7,param_1,param_2,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  if ((DAT_28d3_17f2 == 0) && (DAT_28d3_17ee == 0)) {
    iVar1 = FUN_23f1_1fd7(param_1,param_2,DAT_28d3_17b7);
    FUN_23f1_1007(iVar1 + DAT_28d3_17b5);
  }
  return;
}



// Function: FUN_23f1_161a

void __cdecl16far FUN_23f1_161a(int param_1,int param_2)

{
  if ((((param_1 < 0) || (2 < param_1)) || (param_2 < 0)) || (2 < param_2)) {
    DAT_28d3_17a6 = 0xfff5;
  }
  else {
    DAT_28d3_17f2 = param_1;
    DAT_28d3_17f4 = param_2;
    FUN_23f1_1a3d(param_1,param_2,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  return;
}



// Function: FUN_23f1_165b

void __cdecl16far FUN_23f1_165b(int param_1,undefined2 param_2,undefined2 param_3)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  int iVar4;
  undefined2 unaff_SS;
  int local_8;
  int local_6;
  int local_4;
  
  if ((*(char *)(DAT_28d3_178a + 1) == '\x03') || (param_1 == 0)) goto LAB_23f1_17fe;
  if ((param_1 < 0) || (DAT_28d3_15fb < param_1)) {
    DAT_28d3_17a6 = -0xe;
LAB_23f1_17f7:
    param_1 = 0;
    param_3 = 1;
  }
  else {
    if (param_1 == DAT_28d3_17ec) goto LAB_23f1_17fe;
    iVar1 = param_1 * 0xf;
    if (param_1 != DAT_28d3_17bd) {
      if (*(int *)((int)(undefined2 *)&DAT_28d3_1605 + (DAT_28d3_17bd + -1) * 0xf) != 0) {
        iVar2 = (DAT_28d3_17bd + -1) * 0xf;
        puVar3 = (undefined2 *)((int)(undefined2 *)&DAT_28d3_15fd + iVar2);
        FUN_23f1_0380(puVar3,(char *)s_String_reference_out_of_range_28d3_28cc + 7,
                      *(undefined2 *)((int)(undefined2 *)&DAT_28d3_1605 + iVar2),
                      (char *)s_String_reference_out_of_range_28d3_28cc + 7);
        *(undefined2 *)((int)(undefined2 *)&DAT_28d3_15ff + iVar2) = 0;
        *puVar3 = 0;
        *(undefined2 *)((int)(undefined2 *)&DAT_28d3_1603 + iVar2) = 0;
        *(undefined2 *)((int)(undefined2 *)&DAT_28d3_1601 + iVar2) = 0;
        *(undefined2 *)((int)(undefined2 *)&DAT_28d3_1605 + iVar2) = 0;
      }
      if ((*(uint *)(iVar1 + 0x15f2) | *(uint *)(iVar1 + 0x15f4)) == 0) {
        FUN_23f1_00ad(0x1be8,(char *)s_String_reference_out_of_range_28d3_28cc + 7,iVar1 + 0x15f8,
                      (char *)s_String_reference_out_of_range_28d3_28cc + 7,0x1592,
                      (char *)s_String_reference_out_of_range_28d3_28cc + 7);
        iVar2 = FUN_23f1_072d(0xfff3,&local_4,unaff_SS,0x1592,
                              (char *)s_String_reference_out_of_range_28d3_28cc + 7,
                              (undefined1 *)&DAT_28d3_15a8,
                              (char *)s_String_reference_out_of_range_28d3_28cc + 7);
        if (iVar2 == 0) {
          iVar2 = FUN_23f1_034e(&local_8);
          if (iVar2 == 0) {
            iVar4 = local_6 + (local_8 + 0xfU >> 4);
            iVar2 = FUN_23f1_013d(0,iVar4,local_4,0);
            if (iVar2 == 0) {
              FUN_23f1_00eb();
              iVar2 = FUN_23f1_04a8(0,iVar4);
              if (iVar2 == param_1) {
                *(int *)(iVar1 + 0x15f0) = local_6;
                *(int *)(iVar1 + 0x15ee) = local_8;
                *(int *)(iVar1 + 0x15f6) = local_4 + 0x10;
                goto LAB_23f1_17de;
              }
              FUN_23f1_0380(&local_8);
              DAT_28d3_17a6 = -0xd;
            }
            else {
              FUN_23f1_0380(&local_8);
            }
          }
          else {
            FUN_23f1_00eb();
            DAT_28d3_17a6 = -9;
          }
        }
        else if (DAT_28d3_17a6 == -3) {
          DAT_28d3_17a6 = -8;
        }
        goto LAB_23f1_17f7;
      }
LAB_23f1_17de:
      DAT_28d3_17bd = param_1;
    }
    DAT_28d3_17aa = *(undefined2 *)(iVar1 + 0x15f4);
    DAT_28d3_17a8 = *(undefined2 *)(iVar1 + 0x15f2);
  }
LAB_23f1_17fe:
  DAT_28d3_17ee = param_2;
  DAT_28d3_17f0 = param_3;
  DAT_28d3_17ec = param_1;
  FUN_23f1_1f60(param_1,param_2,param_3);
  return;
}



// Function: FUN_23f1_1822

void __cdecl16far
FUN_23f1_1822(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  FUN_23f1_1fb1(param_1,param_2,param_3,param_4,
                (char *)s_String_reference_out_of_range_28d3_28cc + 7);
  DAT_28d3_17f0 = 0;
  return;
}



// Function: FUN_23f1_1848

void __cdecl16far FUN_23f1_1848(void)

{
  FUN_23f1_2004((char *)s_String_reference_out_of_range_28d3_28cc + 7);
  return;
}



// Function: FUN_23f1_185b

void __cdecl16far FUN_23f1_185b(void)

{
  return;
}



// Function: FUN_23f1_185e

void __cdecl16near FUN_23f1_185e(void)

{
  code *pcVar1;
  
  if (DAT_28d3_1bf7 == -1) {
    if (DAT_28d3_1590 == -0x5b) {
      DAT_28d3_1bf7 = 0;
      return;
    }
    pcVar1 = (code *)swi(0x10);
    DAT_28d3_1bf7 = (*pcVar1)();
    DAT_28d3_1bf8 = DAT_0000_0410;
    if ((DAT_28d3_1bf0 != '\x05') && (DAT_28d3_1bf0 != '\a')) {
      DAT_0000_0410 = DAT_0000_0410 & 0xcf | 0x20;
    }
  }
  return;
}



// Function: FUN_23f1_189d

void __cdecl16far FUN_23f1_189d(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_18b4

void FUN_23f1_18b4(undefined2 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 uVar3;
  
  uVar1 = uRam00021859;
  DAT_28d3_1bf7 = 0xff;
  uVar3 = (undefined2)((ulong)param_2 >> 0x10);
  iVar2 = (int)param_2;
  if (*(char *)(iVar2 + 0x16) == '\0') {
    uVar3 = (undefined2)((ulong)*(undefined4 *)&DAT_28d3_172d >> 0x10);
    iVar2 = (int)*(undefined4 *)&DAT_28d3_172d;
  }
  (**(code **)&DAT_28d3_1729)(0x2000);
  *(int *)&DAT_28d3_17ac = iVar2;
  *(undefined2 *)&DAT_28d3_17ae = uVar3;
  return;
}



// Function: FUN_23f1_18b9

void __cdecl16far FUN_23f1_18b9(undefined4 param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 uVar3;
  
  uVar1 = uRam00021859;
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  iVar2 = (int)param_1;
  if (*(char *)(iVar2 + 0x16) == '\0') {
    uVar3 = (undefined2)((ulong)*(undefined4 *)&DAT_28d3_172d >> 0x10);
    iVar2 = (int)*(undefined4 *)&DAT_28d3_172d;
  }
  (**(code **)&DAT_28d3_1729)(0x2000);
  *(int *)&DAT_28d3_17ac = iVar2;
  *(undefined2 *)&DAT_28d3_17ae = uVar3;
  return;
}



// Function: FUN_23f1_18fd

void __cdecl16far FUN_23f1_18fd(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1929

void __cdecl16far FUN_23f1_1929(byte param_1)

{
  undefined2 uVar1;
  
  uVar1 = uRam00021859;
  FUN_23f1_185e();
  if (param_1 < 10) {
    *(byte *)&DAT_28d3_1bef = param_1;
    FUN_23f1_18b9(*(undefined2 *)0x1bf3,*(undefined2 *)0x1bf5);
  }
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_195f

void __cdecl16far FUN_23f1_195f(void)

{
  code *pcVar1;
  undefined2 uVar2;
  
  uVar2 = uRam00021859;
  if (*(char *)&DAT_28d3_1bf7 != -1) {
    (**(code **)&DAT_28d3_1729)(0x2000);
    if (*(char *)&DAT_28d3_1590 != -0x5b) {
      DAT_0000_0410 = *(undefined1 *)&DAT_28d3_1bf8;
      pcVar1 = (code *)swi(0x10);
      (*pcVar1)();
    }
  }
  *(undefined1 *)&DAT_28d3_1bf7 = 0xff;
  return;
}



// Function: FUN_23f1_199e

void FUN_23f1_199e(undefined2 param_1_00,undefined param_1)

{
  (**(code **)&DAT_28d3_1729)(0x2000,param_1);
  FUN_23f1_19dd();
  return;
}



// Function: FUN_23f1_19c1

void FUN_23f1_19c1(undefined2 param_1_00,undefined param_1)

{
  (**(code **)&DAT_28d3_1729)(0x2000,param_1);
  FUN_23f1_185b();
  return;
}



// Function: FUN_23f1_19dd

void __cdecl16far FUN_23f1_19dd(void)

{
  FUN_23f1_185b();
  return;
}



// Function: FUN_23f1_19e7

void FUN_23f1_19e7(undefined2 param_1_00,undefined param_1)

{
  (**(code **)&DAT_28d3_1729)(0x2000,param_1);
  FUN_23f1_19dd();
  return;
}



// Function: FUN_23f1_1a0a

void __cdecl16far FUN_23f1_1a0a(undefined2 param_1,undefined2 param_2_00,undefined param_2)

{
  undefined2 uVar1;
  
  uVar1 = uRam00021859;
  *(undefined *)0x17b1 = param_2;
  (**(code **)&DAT_28d3_1729)(0x2000);
  *(undefined *)0x17b4 = 0xc;
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1a3d

void __cdecl16far FUN_23f1_1a3d(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1a5a

int __cdecl16far FUN_23f1_1a5a(int param_1,int param_2,int param_3,int param_4)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  
  param_3 = param_3 - param_1;
  if (param_3 < 0) {
    param_3 = -param_3;
  }
  (**(code **)&DAT_28d3_1729)(0x2000);
  iVar2 = FUN_23f1_185b();
  param_4 = param_4 - param_2;
  if (param_4 < 0) {
    param_4 = -param_4;
  }
  lVar1 = (ulong)(iVar2 * (param_3 + 8U >> 3)) * (ulong)(param_4 + 1);
  uVar3 = (uint)lVar1;
  iVar2 = uVar3 + 6;
  if ((0xfff9 < uVar3) || ((int)((ulong)lVar1 >> 0x10) != 0)) {
    iVar2 = 0;
  }
  return iVar2;
}



// Function: FUN_23f1_1aab

void __cdecl16far FUN_23f1_1aab(uint *param_1,byte *param_2,undefined *param_3)

{
  byte bVar1;
  undefined2 uVar2;
  uint uVar3;
  
  uVar2 = uRam00021859;
  *(undefined1 *)&DAT_28d3_1bee = 0xff;
  *(undefined *)&DAT_28d3_1bef = 0;
  *(undefined1 *)&DAT_28d3_1bf1 = 10;
  bVar1 = *param_2;
  *(byte *)&DAT_28d3_1bf0 = bVar1;
  if (bVar1 == 0) {
    FUN_23f1_1b37();
    uVar3 = (uint)*(byte *)&DAT_28d3_1bee;
  }
  else {
    *(undefined1 *)&DAT_28d3_1bef = *param_3;
    bVar1 = *param_2;
    if ((char)bVar1 < '\0') {
      return;
    }
    if (bVar1 < 0xb) {
      *(undefined1 *)&DAT_28d3_1bf1 = *(undefined *)(bVar1 + 0x20e2);
      bVar1 = *(byte *)(bVar1 + 0x20c6);
      uVar3 = (uint)bVar1;
      *(byte *)&DAT_28d3_1bee = bVar1;
    }
    else {
      uVar3 = (uint)(byte)-('\n' - bVar1);
    }
  }
  *param_1 = uVar3;
  return;
}



// Function: FUN_23f1_1b1c

void __cdecl16far FUN_23f1_1b1c(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  
  uVar2 = uRam00021859;
  uVar1 = *(undefined2 *)&DAT_28d3_1bee;
  FUN_23f1_1b37();
  *(undefined2 *)&DAT_28d3_1bee = uVar1;
  return;
}



// Function: FUN_23f1_1b37

void __cdecl16near FUN_23f1_1b37(void)

{
  uint uVar1;
  int unaff_BP;
  undefined2 unaff_SS;
  
  FUN_23f1_20f0();
  uVar1 = (uint)DAT_28d3_1bf0;
  if (DAT_28d3_1bf0 == 0xff) {
    uVar1 = 0xffff;
  }
  **(uint **)(unaff_BP + 6) = uVar1;
  **(uint **)(unaff_BP + 10) = (uint)DAT_28d3_1bef;
  return;
}



// Function: FUN_23f1_1b59

void __cdecl16far FUN_23f1_1b59(undefined4 param_1)

{
  undefined2 uVar1;
  
  uVar1 = uRam00021859;
  FUN_23f1_185e();
  *(undefined2 *)0x1bf3 = (int)param_1;
  *(undefined2 *)0x1bf5 = (int)((ulong)param_1 >> 0x10);
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1b7e

void __cdecl16far FUN_23f1_1b7e(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1b95

void __cdecl16far FUN_23f1_1b95(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1bb2

void __cdecl16far FUN_23f1_1bb2(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1bcf

void __cdecl16far FUN_23f1_1bcf(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1bf2

void __cdecl16far FUN_23f1_1bf2(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1c12

void __cdecl16far FUN_23f1_1c12(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1c32

void __cdecl16far FUN_23f1_1c32(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1c55

void __cdecl16far FUN_23f1_1c55(uint param_1,uint param_2,uint param_3,uint param_4)

{
  undefined2 uVar1;
  
  uVar1 = uRam00021859;
  if (param_3 <= param_1) {
    param_3 = param_1;
  }
  if (param_2 < param_4) {
    param_4 = param_2;
  }
  (**(code **)&DAT_28d3_1729)(0x2000,param_4,param_3);
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1c96

void __cdecl16far FUN_23f1_1c96(void)

{
  undefined2 uVar1;
  
  uVar1 = uRam00021859;
  (**(code **)&DAT_28d3_1729)(0x2000);
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1cc6

void __cdecl16far FUN_23f1_1cc6(void)

{
  undefined2 uVar1;
  
  uVar1 = uRam00021859;
  (**(code **)&DAT_28d3_1729)(0x2000);
  (**(code **)&DAT_28d3_1729)(0x2000);
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1d03

void __cdecl16far FUN_23f1_1d03(void)

{
  undefined2 uVar1;
  
  uVar1 = uRam00021859;
  (**(code **)&DAT_28d3_1729)(0x2000);
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1d33

void __cdecl16far FUN_23f1_1d33(undefined2 *param_1)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined2 *in_BX;
  undefined2 *puVar4;
  undefined2 unaff_ES;
  
  (**(code **)&DAT_28d3_1729)(0x2000,uRam00021859);
  puVar4 = (undefined2 *)param_1;
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar2 = puVar4;
    puVar4 = puVar4 + 1;
    puVar1 = in_BX;
    in_BX = in_BX + 1;
    *puVar2 = *puVar1;
  }
  return;
}



// Function: FUN_23f1_1d5c

void __cdecl16far FUN_23f1_1d5c(undefined param_1)

{
  undefined2 uVar1;
  
  uVar1 = uRam00021859;
  *(undefined1 *)&DAT_28d3_17b0 = param_1;
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1d7d

undefined2 __cdecl16far FUN_23f1_1d7d(void)

{
  undefined2 in_CX;
  
  (**(code **)&DAT_28d3_1729)(0x2000);
  return in_CX;
}



// Function: FUN_23f1_1d98

undefined2 __cdecl16far FUN_23f1_1d98(void)

{
  undefined2 in_BX;
  
  (**(code **)&DAT_28d3_1729)(0x2000);
  return in_BX;
}



// Function: FUN_23f1_1db3

undefined2 __cdecl16far FUN_23f1_1db3(void)

{
  undefined2 in_BX;
  
  (**(code **)&DAT_28d3_1729)(0x2000);
  return in_BX;
}



// Function: FUN_23f1_1dd0

int __cdecl16far FUN_23f1_1dd0(void)

{
  int in_BX;
  
  (**(code **)&DAT_28d3_1729)(0x2000);
  return in_BX + 1;
}



// Function: FUN_23f1_1df1

int __cdecl16far FUN_23f1_1df1(void)

{
  int in_CX;
  
  (**(code **)&DAT_28d3_1729)(0x2000);
  return in_CX + -1;
}



// Function: FUN_23f1_1e0d

void __cdecl16far FUN_23f1_1e0d(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1e2c

void __cdecl16far FUN_23f1_1e2c(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1e52

void __cdecl16far FUN_23f1_1e52(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1e71

void __cdecl16far FUN_23f1_1e71(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1e8c

void __cdecl16far FUN_23f1_1e8c(undefined param_1,undefined2 param_2,undefined param_3)

{
  undefined2 uVar1;
  
  uVar1 = uRam00021859;
  *(undefined *)0x17b3 = param_1;
  *(undefined *)0x1bf2 = param_3;
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1eb5

/* WARNING: Unable to track spacebase fully for stack */

void __cdecl16far FUN_23f1_1eb5(void)

{
  undefined2 uVar1;
  code *pcVar2;
  code *pcVar3;
  undefined2 uVar4;
  int iVar5;
  undefined2 uVar6;
  undefined2 unaff_SS;
  
  uVar4 = uRam00021859;
  uVar6 = (undefined2)((ulong)*(undefined4 *)0x1bf3 >> 0x10);
  iVar5 = (int)*(undefined4 *)0x1bf3;
  uVar1 = *(undefined2 *)(iVar5 + 0xe);
  iVar5 = *(int *)(iVar5 + 0xc) + *(int *)(iVar5 + 0x10);
  *(undefined **)(iVar5 + -4) = &stack0xfff8;
  *(undefined2 *)(iVar5 + -6) = unaff_SS;
  pcVar2 = ((code **)&DAT_28d3_1729)[1];
  pcVar3 = *(code **)&DAT_28d3_1729;
  *(undefined2 *)(iVar5 + -8) = 0x2000;
  *(undefined2 *)(iVar5 + -10) = 0x5dfd;
  (*pcVar3)();
  return;
}



// Function: FUN_23f1_1efa

void __cdecl16far FUN_23f1_1efa(undefined param_1,undefined param_2)

{
  undefined2 uVar1;
  
  uVar1 = uRam00021859;
  *(undefined *)0x17b1 = param_2;
  (**(code **)&DAT_28d3_1729)(0x2000);
  *(undefined *)0x17b4 = param_1;
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1f2a

void __cdecl16far FUN_23f1_1f2a(undefined2 param_1,undefined2 param_2,char *param_3)

{
  char *pcVar1;
  undefined2 uVar2;
  int iVar3;
  char *pcVar4;
  
  uVar2 = uRam00021859;
  (**(code **)&DAT_28d3_1729)(0x2000);
  pcVar4 = (char *)param_3;
  iVar3 = -1;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (*pcVar1 != '\0');
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1f60

void __cdecl16far FUN_23f1_1f60(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1fb1

void __cdecl16far FUN_23f1_1fb1(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_1fd7

char * __cdecl16far FUN_23f1_1fd7(char *param_1)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar3 = (char *)param_1;
  iVar2 = -1;
  pcVar4 = pcVar3;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (*pcVar1 != '\0');
  (**(code **)&DAT_28d3_1729)(0x2000);
  return pcVar3;
}



// Function: FUN_23f1_2004

undefined2 __cdecl16far FUN_23f1_2004(void)

{
  undefined2 uVar1;
  
  uVar1 = 1;
  (**(code **)&DAT_28d3_1729)(0x2000);
  return uVar1;
}



// Function: FUN_23f1_2025

undefined __cdecl16far FUN_23f1_2025(void)

{
  undefined extraout_DL;
  
  (**(code **)&DAT_28d3_1729)(0x2000);
  return extraout_DL;
}



// Function: FUN_23f1_2046

void __cdecl16far FUN_23f1_2046(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_2066

void __cdecl16far FUN_23f1_2066(uint param_1,uint param_2,uint param_3,uint param_4,int *param_5)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = uRam00021859;
  uVar2 = param_1;
  if (param_3 <= param_1) {
    uVar2 = param_3;
    param_3 = param_1;
  }
  uVar3 = param_2;
  if (param_4 <= param_2) {
    uVar3 = param_4;
    param_4 = param_2;
  }
  *param_5 = param_3 - uVar2;
  ((int *)param_5)[1] = param_4 - uVar3;
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_20a3

void __cdecl16far FUN_23f1_20a3(void)

{
  (**(code **)&DAT_28d3_1729)(0x2000);
  return;
}



// Function: FUN_23f1_20f0

void __cdecl16near FUN_23f1_20f0(void)

{
  uint uVar1;
  
  DAT_28d3_1bee = 0xff;
  DAT_28d3_1bf0 = 0xff;
  DAT_28d3_1bef = 0;
  FUN_23f1_2126();
  if (DAT_28d3_1bf0 != 0xff) {
    uVar1 = (uint)DAT_28d3_1bf0;
    DAT_28d3_1bee = *(undefined *)(uVar1 + 0x20c6);
    DAT_28d3_1bef = *(undefined *)(uVar1 + 0x20d4);
    DAT_28d3_1bf1 = *(undefined *)(uVar1 + 0x20e2);
  }
  return;
}



// Function: FUN_23f1_2126

void __cdecl16near FUN_23f1_2126(void)

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  bool bVar5;
  
  pcVar1 = (code *)swi(0x10);
  bVar2 = (*pcVar1)();
  bVar5 = bVar2 < 7;
  if (bVar2 == 7) {
    FUN_23f1_218d();
    if (!bVar5) {
      cVar3 = FUN_23f1_221e();
      if (cVar3 == '\0') {
        uRam000b8000 = ~uRam000b8000;
        DAT_28d3_1bf0 = 1;
        return;
      }
      DAT_28d3_1bf0 = 7;
      return;
    }
  }
  else {
    FUN_23f1_221b();
    if (bVar5) {
      DAT_28d3_1bf0 = 6;
      return;
    }
    FUN_23f1_218d();
    if (!bVar5) {
      iVar4 = FUN_23f1_2250();
      bVar5 = false;
      if (iVar4 == 0) {
        DAT_28d3_1bf0 = 1;
        FUN_23f1_21fa();
        if (bVar5) {
          DAT_28d3_1bf0 = 2;
        }
        return;
      }
      DAT_28d3_1bf0 = 10;
      return;
    }
  }
  FUN_23f1_21ab();
  return;
}



// Function: FUN_23f1_218d

void __cdecl16near FUN_23f1_218d(void)

{
  code *pcVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  
  cVar3 = '\x10';
  cVar4 = -1;
  cVar2 = '\x0f';
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  if (((cVar2 < '\f') && (cVar4 < '\x02')) && (cVar3 < '\x04')) {
    return;
  }
  return;
}



// Function: FUN_23f1_21ab

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl16near FUN_23f1_21ab(void)

{
  undefined2 in_BX;
  char cVar1;
  bool bVar2;
  
  DAT_28d3_1bf0 = 4;
  cVar1 = (char)((uint)in_BX >> 8);
  bVar2 = cVar1 == '\0';
  if (cVar1 != '\x01') {
    FUN_23f1_21eb();
    if ((!bVar2) && (bVar2 = false, (char)in_BX != '\0')) {
      DAT_28d3_1bf0 = 3;
      FUN_23f1_21fa();
      if ((bVar2) || ((_DAT_c000_0039 == 0x345a && (_DAT_c000_003b == 0x3934)))) {
        DAT_28d3_1bf0 = 9;
      }
    }
    return;
  }
  DAT_28d3_1bf0 = 5;
  return;
}



// Function: FUN_23f1_21eb

void __cdecl16near FUN_23f1_21eb(void)

{
  return;
}



// Function: FUN_23f1_21fa

void __cdecl16near FUN_23f1_21fa(void)

{
  code *pcVar1;
  char cVar2;
  byte in_BL;
  
  pcVar1 = (code *)swi(0x10);
  cVar2 = (*pcVar1)();
  if ((cVar2 == '\x1a') && (((in_BL == 7 || (in_BL == 8)) || ((10 < in_BL && (in_BL < 0xd)))))) {
    return;
  }
  return;
}



// Function: FUN_23f1_221b

undefined __cdecl16near FUN_23f1_221b(void)

{
  return 0;
}



// Function: FUN_23f1_221e

undefined __cdecl16near FUN_23f1_221e(void)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  byte bVar4;
  
  bVar4 = 0;
  bVar1 = in(0x3ba);
  iVar3 = -0x8000;
  while ((bVar2 = in(0x3ba), (bVar2 & 0x80) == (bVar1 & 0x80) || (bVar4 = bVar4 + 1, bVar4 < 10))) {
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      return 0;
    }
  }
  iVar3 = -0x8000;
  do {
    bVar1 = in(0x3ba);
    if ((bVar1 & 0x30) != 0x10) {
      return 1;
    }
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return 2;
}



// Function: FUN_23f1_2250

undefined2 __cdecl16near FUN_23f1_2250(void)

{
  code *pcVar1;
  byte bVar2;
  uint uVar3;
  uint extraout_DX;
  
  uVar3 = 0;
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  if ((uVar3 | extraout_DX) != 0) {
    if (((*(char *)(extraout_DX + 2) == '\0') || (*(char *)(extraout_DX + 2) == '\x02')) &&
       (bVar2 = in(0x188), (bVar2 & 4) != 0)) {
      return 1;
    }
  }
  return 0;
}



// Function: FUN_23f1_35f2

void __cdecl16near FUN_23f1_35f2(void)

{
  int in_AX;
  int unaff_DI;
  
  if (in_AX < unaff_DI) {
    return;
  }
  return;
}



// Function: FUN_27b2_04e0

undefined2 FUN_27b2_04e0(void)

{
  code *pcVar1;
  byte bVar2;
  undefined2 in_AX;
  uint uVar3;
  undefined uVar6;
  uint uVar4;
  undefined2 uVar5;
  int iVar7;
  undefined2 unaff_SS;
  undefined2 in_FPUStatusWord;
  undefined4 in_stack_00000000;
  undefined2 local_4;
  
  iVar7 = (int)in_stack_00000000;
  uVar3 = (uint)((ulong)in_stack_00000000 >> 0x10) ^
          *(uint *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 7);
  uVar4 = *(uint *)(iVar7 + -1);
  uVar6 = (undefined)(uVar4 >> 8);
  bVar2 = (char)uVar4 - 0x34;
  local_4 = in_AX;
  if (bVar2 < 8) {
    if (CONCAT11(uVar6,bVar2) == -0x1cfd) {
      *(undefined2 *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 = 0x4100;
      *(undefined2 *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 2) = 0x3f;
      *(undefined2 *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 0x25) = 0;
      *(undefined2 *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 0xd) =
           *(undefined2 *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 0x11);
      *(undefined2 *)((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020 + 4) = 0;
    }
    else if ((CONCAT11(uVar6,bVar2) != -0x1ff9) ||
            (local_4 = in_FPUStatusWord,
            '\x01' < ((char *)s_Borland_C_____Copyright_1994_Bor_28d3_0020)[6])) {
      *(undefined *)(iVar7 + -2) = 0x9b;
      *(char *)(iVar7 + -1) = *(char *)(iVar7 + -1) + -0x5c;
      local_4 = in_AX;
    }
  }
  else if (bVar2 < 9) {
    if ((uVar4 & 0x2000) != 0) goto LAB_27b2_058c;
    *(undefined *)(iVar7 + -2) = 0x9b;
    uVar4 = CONCAT11(uVar6,uVar6) & 0x7c0;
    *(int *)(iVar7 + -1) = (CONCAT11((char)(uVar4 >> 8),(byte)uVar4 >> 3) ^ 0x18) + 0xd826;
  }
  else {
    if (9 < bVar2) {
LAB_27b2_058c:
      pcVar1 = (code *)swi(3);
      uVar5 = (*pcVar1)();
      return uVar5;
    }
    *(undefined2 *)(iVar7 + -2) = 0x9b90;
  }
  return local_4;
}



// Function: FUN_280e_0000

int ** __cdecl16far FUN_280e_0000(int **param_1,undefined2 *param_2)

{
  uint *puVar1;
  uint uVar2;
  undefined2 uVar3;
  int **ppiVar4;
  uint *puVar5;
  uint in_DX;
  undefined2 local_20;
  
  FUN_1000_5c93();
  if (((uint)(int **)param_1 | param_1._2_2_) == 0) {
    ppiVar4 = (int **)FUN_1000_44b3(4);
    param_1 = (int **)CONCAT22(in_DX,ppiVar4);
    if (((uint)ppiVar4 | in_DX) == 0) goto LAB_280e_0049;
  }
  in_DX = ((undefined2 *)param_2)[1];
  uVar3 = *param_2;
  *(uint *)((int)(int **)param_1 + 2) = in_DX;
  *(undefined2 *)param_1 = uVar3;
  **param_1 = **param_1 + 1;
LAB_280e_0049:
  puVar5 = (uint *)FUN_1000_5c87();
  puVar1 = puVar5;
  uVar2 = *puVar1;
  *puVar1 = *puVar1 + 1;
  puVar5[1] = puVar5[1] + (uint)(0xfffe < uVar2);
  FUN_1000_5d02(local_20);
  return (int **)param_1;
}



// Function: FUN_280e_00e9

uint * __cdecl16far FUN_280e_00e9(uint *param_1,uint param_2,uint param_3)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  undefined2 uVar6;
  int *piVar7;
  uint in_DX;
  uint uVar8;
  undefined2 local_24;
  
  FUN_1000_5c93();
  if (((uint)(uint *)param_1 | param_1._2_2_) == 0) {
    puVar4 = (uint *)FUN_1000_44b3(4);
    param_1 = (uint *)CONCAT22(in_DX,puVar4);
    if (((uint)puVar4 | in_DX) == 0) goto LAB_280e_018c;
  }
  uVar5 = FUN_1000_44b3(0xc);
  if ((uVar5 | in_DX) != 0) {
    uVar8 = in_DX;
    if ((param_2 | param_3) == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = FUN_1000_1c56(param_2,param_3,0,0,0,0);
    }
    FUN_280e_05c3(uVar5,in_DX,param_2,param_3,uVar6);
    piVar7 = (int *)FUN_1000_5c87();
    piVar1 = piVar7;
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    piVar7[1] = piVar7[1] - (uint)(iVar3 == 0);
  }
  ((uint *)param_1)[1] = in_DX;
  *param_1 = uVar5;
LAB_280e_018c:
  puVar4 = (uint *)FUN_1000_5c87();
  puVar2 = puVar4;
  uVar5 = *puVar2;
  *puVar2 = *puVar2 + 1;
  puVar4[1] = puVar4[1] + (uint)(0xfffe < uVar5);
  FUN_1000_5d02(local_24);
  return (uint *)param_1;
}



// Function: FUN_280e_0305

void __cdecl16far FUN_280e_0305(int **param_1,uint param_2)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  uint *puVar6;
  undefined2 in_DX;
  undefined2 local_20;
  
  FUN_1000_5c93();
  piVar5 = (int *)FUN_1000_5c87();
  piVar1 = piVar5;
  iVar3 = *piVar1;
  *piVar1 = *piVar1 + -1;
  piVar5[1] = piVar5[1] - (uint)(iVar3 == 0);
  if (((uint)(int **)param_1 | param_1._2_2_) != 0) {
    piVar1 = *param_1;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      puVar6 = (uint *)FUN_1000_5c87();
      puVar2 = puVar6;
      uVar4 = *puVar2;
      *puVar2 = *puVar2 + 1;
      puVar6[1] = puVar6[1] + (uint)(0xfffe < uVar4);
      FUN_280e_06ac(*(undefined2 *)param_1,*(undefined2 *)((int)(int **)param_1 + 2),3);
    }
    if ((param_2 & 1) != 0) {
      FUN_1000_441a((int **)param_1,param_1._2_2_);
    }
  }
  FUN_1000_5d02(local_20);
  return;
}



// Function: FUN_280e_038c

void __cdecl16far FUN_280e_038c(undefined4 *param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  undefined2 in_DX;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  undefined2 local_28;
  undefined local_a [4];
  undefined local_6 [4];
  
  FUN_1000_5c93();
  if (*(uint *)((int)*param_1 + 6) <= param_2) {
    uVar12 = 0;
    uVar11 = 0;
    uVar10 = 0;
    uVar9 = 0;
    uVar8 = 5;
    uVar7 = 0x1000;
    uVar6 = 0x916f;
    uVar5 = 0;
    uVar4 = 0;
    FUN_280e_00e9(local_6);
    FUN_1000_58d4(local_a);
    FUN_280e_0305(local_6);
    puVar3 = (uint *)FUN_1000_5c87(uVar4,uVar5,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12);
    puVar1 = puVar3;
    uVar2 = *puVar1;
    *puVar1 = *puVar1 + 1;
    puVar3[1] = puVar3[1] + (uint)(0xfffe < uVar2);
    FUN_1000_6bc3(0xc00,0x1000,local_a);
  }
  FUN_1000_5d02(local_28);
  return;
}



// Function: FUN_280e_044a

void __cdecl16far FUN_280e_044a(undefined4 *param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  undefined2 in_DX;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  undefined2 local_28;
  undefined local_a [4];
  undefined local_6 [4];
  
  FUN_1000_5c93();
  if (*(uint *)((int)*param_1 + 6) < param_2) {
    uVar12 = 0;
    uVar11 = 0;
    uVar10 = 0;
    uVar9 = 0;
    uVar8 = 5;
    uVar7 = 0x1000;
    uVar6 = 0x916f;
    uVar5 = 0;
    uVar4 = 0;
    FUN_280e_00e9(local_6);
    FUN_1000_58d4(local_a);
    FUN_280e_0305(local_6);
    puVar3 = (uint *)FUN_1000_5c87(uVar4,uVar5,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12);
    puVar1 = puVar3;
    uVar2 = *puVar1;
    *puVar1 = *puVar1 + 1;
    puVar3[1] = puVar3[1] + (uint)(0xfffe < uVar2);
    FUN_1000_6bc3(0xc00,0x1000,local_a);
  }
  FUN_1000_5d02(local_28);
  return;
}



// Function: FUN_280e_0508

void __cdecl16far FUN_280e_0508(undefined4 param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  undefined2 in_DX;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  undefined2 local_28;
  undefined local_a [4];
  undefined local_6 [4];
  
  FUN_1000_5c93();
  if (*(uint *)((int)param_1 + 6) <= param_2) {
    uVar12 = 0;
    uVar11 = 0;
    uVar10 = 0;
    uVar9 = 0;
    uVar8 = 5;
    uVar7 = 0x1000;
    uVar6 = 0x916f;
    uVar5 = 0;
    uVar4 = 0;
    FUN_280e_00e9(local_6);
    FUN_1000_58d4(local_a);
    FUN_280e_0305(local_6);
    puVar3 = (uint *)FUN_1000_5c87(uVar4,uVar5,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12);
    puVar1 = puVar3;
    uVar2 = *puVar1;
    *puVar1 = *puVar1 + 1;
    puVar3[1] = puVar3[1] + (uint)(0xfffe < uVar2);
    FUN_1000_6bc3(0xc00,0x1000,local_a);
  }
  FUN_1000_5d02(local_28);
  return;
}



// Function: FUN_280e_05c3

undefined2 * __cdecl16far
FUN_280e_05c3(undefined2 *param_1,undefined2 param_2,undefined2 param_3,int param_4,
             undefined2 param_5,undefined2 param_6,int param_7,int param_8)

{
  uint *puVar1;
  uint uVar2;
  undefined2 *puVar3;
  undefined2 uVar4;
  uint *puVar5;
  uint in_DX;
  uint extraout_DX;
  undefined2 uVar6;
  
  if (((uint)(undefined2 *)param_1 | param_1._2_2_) == 0) {
    puVar3 = (undefined2 *)FUN_1000_44b3(0xc);
    param_1 = (undefined2 *)CONCAT22(in_DX,puVar3);
    if (((uint)puVar3 | in_DX) == 0) goto LAB_280e_0690;
  }
  uVar6 = (undefined2)((ulong)param_1 >> 0x10);
  puVar3 = (undefined2 *)param_1;
  *param_1 = 1;
  puVar3[5] = 0;
  puVar3[3] = param_4 + param_7;
  uVar4 = FUN_280e_0845(puVar3[3] + param_8);
  puVar3[4] = uVar4;
  uVar4 = FUN_1000_4752(puVar3[4] + 1);
  puVar3[2] = in_DX;
  puVar3[1] = uVar4;
  if ((puVar3[1] | puVar3[2]) == 0) {
    FUN_1000_5728(0x1000,0x26f6,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
    in_DX = extraout_DX;
  }
  FUN_1000_1a99(puVar3[1],puVar3[2],param_2,param_3,param_4);
  FUN_1000_1a99(puVar3[1] + param_4,puVar3[2],param_5,param_6,param_7);
  *(undefined *)((int)*(undefined4 *)(puVar3 + 1) + param_4 + param_7) = 0;
LAB_280e_0690:
  puVar5 = (uint *)FUN_1000_5c87();
  puVar1 = puVar5;
  uVar2 = *puVar1;
  *puVar1 = *puVar1 + 1;
  puVar5[1] = puVar5[1] + (uint)(0xfffe < uVar2);
  return (undefined2 *)param_1;
}



// Function: FUN_280e_06ac

void __cdecl16far FUN_280e_06ac(undefined4 param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined2 in_DX;
  undefined2 local_20;
  
  FUN_1000_5c93();
  piVar3 = (int *)FUN_1000_5c87();
  piVar1 = piVar3;
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + -1;
  piVar3[1] = piVar3[1] - (uint)(iVar2 == 0);
  if (((uint)param_1 | param_1._2_2_) != 0) {
    FUN_1000_4648(*(undefined2 *)((uint)param_1 + 2),*(undefined2 *)((uint)param_1 + 4));
    if ((param_2 & 1) != 0) {
      FUN_1000_441a((uint)param_1,param_1._2_2_);
    }
  }
  FUN_1000_5d02(local_20);
  return;
}



// Function: FUN_280e_070d

void __cdecl16far FUN_280e_070d(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 in_DX;
  int iVar3;
  undefined2 uVar4;
  undefined2 local_20;
  
  FUN_1000_5c93();
  uVar4 = (undefined2)((ulong)param_1 >> 0x10);
  iVar3 = (int)param_1;
  *(uint *)(iVar3 + 10) = *(uint *)(iVar3 + 10) | 1;
  iVar1 = FUN_280e_0845(param_2 + 1);
  if (DAT_28d3_28ac < (uint)(*(int *)(iVar3 + 8) - iVar1)) {
    uVar2 = FUN_1000_48b9(*(undefined2 *)(iVar3 + 2),*(undefined2 *)(iVar3 + 4),iVar1 + 1);
    *(undefined2 *)(iVar3 + 4) = in_DX;
    *(undefined2 *)(iVar3 + 2) = uVar2;
    *(int *)(iVar3 + 8) = iVar1;
  }
  FUN_1000_5d02(local_20);
  return;
}



// Function: FUN_280e_077b

void __cdecl16far FUN_280e_077b(undefined4 param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 in_DX;
  int iVar3;
  undefined2 uVar4;
  undefined2 local_20;
  
  FUN_1000_5c93();
  uVar4 = (undefined2)((ulong)param_1 >> 0x10);
  iVar3 = (int)param_1;
  iVar1 = FUN_280e_0845(*(undefined2 *)(iVar3 + 6));
  if (DAT_28d3_28ac < (uint)(*(int *)(iVar3 + 8) - iVar1)) {
    uVar2 = FUN_1000_48b9(*(undefined2 *)(iVar3 + 2),*(undefined2 *)(iVar3 + 4),iVar1 + 1);
    *(undefined2 *)(iVar3 + 4) = in_DX;
    *(undefined2 *)(iVar3 + 2) = uVar2;
    *(int *)(iVar3 + 8) = iVar1;
  }
  FUN_1000_5d02(local_20);
  return;
}



// Function: FUN_280e_07e3

void __cdecl16far FUN_280e_07e3(undefined4 param_1,undefined2 param_2)

{
  undefined2 uVar1;
  undefined2 in_DX;
  int iVar2;
  undefined2 uVar3;
  undefined2 local_20;
  
  FUN_1000_5c93();
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  iVar2 = (int)param_1;
  *(undefined2 *)(iVar2 + 8) = param_2;
  uVar1 = FUN_1000_48b9(*(undefined2 *)(iVar2 + 2),*(undefined2 *)(iVar2 + 4),
                        *(int *)(iVar2 + 8) + 1);
  *(undefined2 *)(iVar2 + 4) = in_DX;
  *(undefined2 *)(iVar2 + 2) = uVar1;
  if ((*(uint *)(iVar2 + 2) | *(uint *)(iVar2 + 4)) == 0) {
    FUN_1000_5728(0x1000,0x26f6,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
  }
  FUN_1000_5d02(local_20);
  return;
}



// Function: FUN_280e_0845

int __cdecl16far FUN_280e_0845(int param_1)

{
  int iVar1;
  undefined2 local_20;
  
  FUN_1000_5c93();
  iVar1 = ((((param_1 - DAT_28d3_28a8) + DAT_28d3_28aa) - 1) / DAT_28d3_28aa) * DAT_28d3_28aa +
          DAT_28d3_28a8;
  FUN_1000_5d02(local_20);
  return iVar1;
}



// Function: FUN_280e_0884

void __cdecl16far
FUN_280e_0884(undefined4 param_1,int param_2,int param_3,uint param_4,uint param_5,int param_6)

{
  int iVar1;
  uint uVar2;
  int in_DX;
  int iVar3;
  undefined2 uVar4;
  int local_24;
  int local_22;
  undefined2 local_20;
  
  FUN_1000_5c93();
  uVar4 = (undefined2)((ulong)param_1 >> 0x10);
  iVar3 = (int)param_1;
  iVar1 = (*(int *)(iVar3 + 6) + param_6) - param_3;
  uVar2 = FUN_280e_0845(iVar1);
  if (*(uint *)(iVar3 + 8) < uVar2) {
    FUN_280e_07e3(iVar3,uVar4,uVar2);
  }
  else if ((DAT_28d3_28ac < *(int *)(iVar3 + 8) - uVar2) && ((*(uint *)(iVar3 + 10) & 1) == 0)) {
    local_24 = FUN_1000_4752(uVar2 + 1);
    if ((*(uint *)(iVar3 + 2) | *(uint *)(iVar3 + 4)) == 0) {
      FUN_1000_5728(0x1000,0x26f6,(char *)s_String_reference_out_of_range_28d3_28cc + 7);
    }
    if (param_2 != 0) {
      FUN_1000_1a99(local_24,in_DX,*(undefined2 *)(iVar3 + 2),*(undefined2 *)(iVar3 + 4),param_2);
    }
    *(uint *)(iVar3 + 8) = uVar2;
    local_22 = in_DX;
    goto LAB_280e_094d;
  }
  local_22 = *(int *)(iVar3 + 4);
  local_24 = *(int *)(iVar3 + 2);
LAB_280e_094d:
  if (((*(int *)(iVar3 + 4) != local_22) || (*(int *)(iVar3 + 2) != local_24)) ||
     (param_6 != param_3)) {
    FUN_1000_1b58(local_24 + param_2 + param_6,local_22,*(int *)(iVar3 + 2) + param_2 + param_3,
                  *(undefined2 *)(iVar3 + 4),(*(int *)(iVar3 + 6) - param_2) - param_3);
  }
  if (param_6 != 0) {
    if ((param_4 | param_5) == 0) {
      FUN_1000_1ae3(local_24 + param_2,local_22,0x20,param_6);
    }
    else {
      FUN_1000_1b58(local_24 + param_2,local_22,param_4,param_5,param_6);
    }
  }
  *(int *)(iVar3 + 6) = iVar1;
  *(undefined *)(local_24 + *(int *)(iVar3 + 6)) = 0;
  if ((*(int *)(iVar3 + 4) != local_22) || (*(int *)(iVar3 + 2) != local_24)) {
    FUN_1000_4648(*(undefined2 *)(iVar3 + 2),*(undefined2 *)(iVar3 + 4));
    *(int *)(iVar3 + 4) = local_22;
    *(int *)(iVar3 + 2) = local_24;
  }
  FUN_1000_5d02(local_20);
  return;
}



// Function: FUN_280e_0a43

undefined2 __cdecl16far FUN_280e_0a43(undefined2 param_1)

{
  undefined2 uVar1;
  
  uVar1 = DAT_28d3_28a2;
  DAT_28d3_28a2 = param_1;
  return uVar1;
}



// Function: FUN_280e_0a60

undefined2 __cdecl16far FUN_280e_0a60(undefined2 param_1)

{
  undefined2 uVar1;
  
  uVar1 = DAT_28d3_28a4;
  DAT_28d3_28a4 = param_1;
  return uVar1;
}



// Function: FUN_280e_0a7d

undefined2 __cdecl16far FUN_280e_0a7d(undefined2 param_1)

{
  undefined2 uVar1;
  
  uVar1 = DAT_28d3_28a6;
  DAT_28d3_28a6 = param_1;
  return uVar1;
}



// Function: FUN_280e_0a9a

undefined2 __cdecl16far FUN_280e_0a9a(undefined2 param_1)

{
  undefined2 uVar1;
  
  uVar1 = DAT_28d3_28a8;
  DAT_28d3_28a8 = param_1;
  return uVar1;
}



// Function: FUN_280e_0ab7

undefined2 __cdecl16far FUN_280e_0ab7(int param_1)

{
  undefined2 uVar1;
  
  uVar1 = DAT_28d3_28aa;
  DAT_28d3_28aa = param_1;
  if (param_1 == 0) {
    DAT_28d3_28aa = 1;
  }
  return uVar1;
}



// Function: FUN_280e_0ae1

undefined2 __cdecl16far FUN_280e_0ae1(undefined2 param_1)

{
  undefined2 uVar1;
  
  uVar1 = DAT_28d3_28ac;
  DAT_28d3_28ac = param_1;
  return uVar1;
}



