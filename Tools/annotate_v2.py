#!/usr/bin/env python3
"""
annotate_v2.py — Annotate PROJ5_decompiled_v2.c with correct names
====================================================================
The v2 Ghidra output already has most function names set, but some are WRONG
due to incorrect address mappings. This script:
1. Corrects wrong function names (using temp placeholders to avoid chain conflicts)
2. Replaces remaining FUN_xxxx_yyyy with library function names
3. Replaces DAT_xxxx_yyyy with global variable names
4. Cleans up string literals and float constants

Output: Flint 2.77 raw/PROJ5_app_annotated.c
"""

import re
import os

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INPUT_FILE  = os.path.join(BASE, "Flint 2.77 raw", "PROJ5_decompiled_v2.c")
OUTPUT_FILE = os.path.join(BASE, "Flint 2.77 raw", "PROJ5_app_annotated.c")

# ═══════════════════════════════════════════════════════════════════════════════
# FUNCTION NAME CORRECTIONS
# The v2 Ghidra script assigned some names incorrectly.
# Based on VERIFICATION_REPORT.md analysis:
#
# Address   | v2 label    | Correct name | Evidence
# ----------|-------------|--------------|------------------------------------------
# 1928:0a0a | msgbox1     | dlgcfg       | sub_9C8A in MAP, verification says dlgcfg
# 1928:18c5 | draw_bt_2   | InrDcr       | ida_sub_AB45, verification says InrDcr
# 1928:194e | InrDcr      | dlgopen      | ida_sub_ABCE, verification says dlgopen
# 1928:245c | inp_dig     | dlged        | ida_sub_B6DC, verification says dlged
# 1928:2578 | dlgcfg      | inp_dig      | auto-detected within dlged, inp_dig body
# 1928:233e | chdiska     | disksel      | MAP label, bodies swapped with chkdisk
# 1928:38cf | chkdisk     | chdiska      | ida_sub_CB4F, verification confirmed swap
# ═══════════════════════════════════════════════════════════════════════════════

# Two-phase replacement to avoid conflicts (e.g., InrDcr→dlgopen then draw_bt_2→InrDcr)
# Phase 1: wrong name → unique placeholder
# Phase 2: placeholder → correct name
NAME_CORRECTIONS_PHASE1 = [
    # (wrong_name, placeholder) — order matters for chains!
    # 1928:18c5 was draw_bt_2, actually InrDcr (ida_sub_AB45)
    ("draw_bt_2",  "__P_INCRDCR__"),
    # 1928:194e was InrDcr, actually dlgopen (ida_sub_ABCE)
    ("InrDcr",     "__P_DLGOPEN__"),
    # 1928:0a0a was msgbox1 (sub_9C8A), actually dlgcfg (WndBkgr "Config")
    ("msgbox1",    "__P_DLGCFG__"),
    # 1928:245c was inp_dig (ida_sub_B6DC), actually dlged
    ("inp_dig",    "__P_DLGED__"),
    # 1928:233e was chdiska (MAP label), actually disksel — bodies swapped
    ("chdiska",    "__P_DISKSEL__"),
    # 1928:38cf was chkdisk (ida_sub_CB4F), actually chdiska
    ("chkdisk",    "__P_CHDISKA__"),
    # 1928:38fa (sub_CB7A) is inp_dig — rename from FUN_ name
    ("FUN_1928_38fa", "__P_INPDIG__"),
]

NAME_CORRECTIONS_PHASE2 = [
    ("__P_INCRDCR__", "InrDcr"),
    ("__P_DLGOPEN__", "dlgopen"),
    ("__P_DLGCFG__",  "dlgcfg"),
    ("__P_DLGED__",   "dlged"),
    ("__P_DISKSEL__", "disksel"),
    ("__P_CHDISKA__", "chdiska"),
    ("__P_INPDIG__",  "inp_dig"),
]

# ═══════════════════════════════════════════════════════════════════════════════
# GLOBAL VARIABLE NAME MAPPING (DAT_xxxx_yyyy → real name)
# ═══════════════════════════════════════════════════════════════════════════════

DATA_NAMES = {
    # ── PROJ5.CPP core processing variables (verified 2960-298e) ──
    "DAT_28d3_2960": "f_demo",
    "DAT_28d3_2962": "f_bcab",
    "DAT_28d3_2964": "f_bca",
    "DAT_28d3_2966": "f_bc",
    "DAT_28d3_2968": "xptr",
    "DAT_28d3_296a": "yptr",
    "DAT_28d3_296c": "zptr",
    "DAT_28d3_296e": "do_ptr",
    "DAT_28d3_2970": "f_ptr",
    "DAT_28d3_2972": "xcur",
    "DAT_28d3_2974": "ycur",
    "DAT_28d3_2976": "zcur",
    "DAT_28d3_2978": "f_data",
    "DAT_28d3_297a": "f_xyz",
    "DAT_28d3_297c": "start_nmb",
    "DAT_28d3_2980": "lastn",
    "DAT_28d3_2984": "nmax",
    "DAT_28d3_2988": "l_period",
    "DAT_28d3_298a": "gate_delay",
    "DAT_28d3_298c": "step_freq",
    "DAT_28d3_298e": "f_const",
    "DAT_28d3_2994": "dT",
    "DAT_28d3_2996": "step",
    "DAT_28d3_29a2": "nglas",
    "DAT_28d3_29aa": "xsize",
    "DAT_28d3_29ac": "ysize",
    "DAT_28d3_29ae": "zsize",
    "DAT_28d3_29b0": "xofs",
    "DAT_28d3_29b2": "yofs",
    "DAT_28d3_29b4": "zofs",
    "DAT_28d3_29b6": "gl_nmb",
    "DAT_28d3_29b8": "glpos9",
    "DAT_28d3_29ba": "nmrpt",
    "DAT_28d3_29cc": "nmrpt_9",
    "DAT_28d3_29ce": "d_check",
    "DAT_28d3_29d0": "f_noise",
    "DAT_28d3_29d2": "f_sort",
    "DAT_28d3_29d4": "sK1",
    "DAT_28d3_29d6": "sK2",
    "DAT_28d3_29d8": "nmb_pbt",
    "DAT_28d3_29da": "pkey",
    "DAT_28d3_29dc": "tout",

    # ── File I/O variables ──
    "DAT_28d3_2a3c": "ulMax",
    "DAT_28d3_2a40": "iTabl",
    "DAT_28d3_2a42": "iTabl_seg",
    "DAT_28d3_2a44": "dx",
    "DAT_28d3_2a46": "dy",
    "DAT_28d3_2a48": "dz",
    "DAT_28d3_2a4a": "fcdim",
    "DAT_28d3_2a4c": "kdim",
    "DAT_28d3_2a4e": "feqk",
    "DAT_28d3_2a50": "kxdim",
    "DAT_28d3_2a52": "kydim",
    "DAT_28d3_2a54": "kzdim",

    # ── Glass type array ──
    "DAT_28d3_4cb6": "gtype",

    # ── Display/range variables ──
    "DAT_28d3_4fd6": "xmin",
    "DAT_28d3_4fd8": "xmax",
    "DAT_28d3_4fda": "ymin",
    "DAT_28d3_4fdc": "ymax",
    "DAT_28d3_4fde": "zmin",
    "DAT_28d3_4fe0": "zmax",
    "DAT_28d3_4fe2": "errnmb",
    "DAT_28d3_4fe4": "k_old",
    "DAT_28d3_4fe6": "p_old",
    "DAT_28d3_4fe8": "ulFlash",
    "DAT_28d3_4fec": "ulService",

    # ── PIC.CPP variables ──
    "DAT_28d3_4ff6": "ctlw",

    # ── RDWRF.CPP file/dir lists ──
    "DAT_28d3_4ff8": "flist",
    "DAT_28d3_550c": "dlist",
    "DAT_28d3_57e6": "lastd",
    "DAT_28d3_57e8": "lastf",

    # ── PIC.CPP shutter delay ──
    "DAT_28d3_57ea": "sh_delay",

    # ── RDWRF.CPP path ──
    "DAT_28d3_5796": "path",

    # ── MSKEYC.CPP mouse registers ──
    "DAT_28d3_57ec": "r_ax",
    "DAT_28d3_57ee": "r_bx",
    "DAT_28d3_57f0": "r_cx",
    "DAT_28d3_57f2": "r_dx",

    # ── MSKEYC.CPP variables ──
    "DAT_28d3_5806": "coord_h",
    "DAT_28d3_5808": "coord_v",
    "DAT_28d3_580a": "sts_old",
    "DAT_28d3_580c": "nmb_rpt",
}

# ═══════════════════════════════════════════════════════════════════════════════
# CRT / LIBRARY FUNCTION NAMES (segments 1000, 23f1)
# ═══════════════════════════════════════════════════════════════════════════════

LIB_FUNC_NAMES = {
    # ── CRT standard library (segment 1000) ──
    "FUN_1000_1bec": "memset",
    "FUN_1000_19a6": "strtok",
    "FUN_1000_1b7d": "strcat",
    "FUN_1000_1bbc": "strcmp",
    "FUN_1000_1c15": "stricmp",
    "FUN_1000_1c77": "strstr",
    "FUN_1000_3e8c": "strlwr",
    "FUN_1000_0492": "atof",
    "FUN_1000_04ab": "gcvt",
    "FUN_1000_40d1": "atoi",
    "FUN_1000_4055": "itoa",
    "FUN_1000_40a5": "ltoa",
    "FUN_1000_4084": "ultoa",
    "FUN_1000_3faf": "__LONGTOA",
    "FUN_1000_0fe0": "bioskey",
    "FUN_1000_1953": "kbhit",
    "FUN_1000_18df": "getch",
    "FUN_1000_302b": "printf",
    "FUN_1000_3431": "puts",
    "FUN_1000_258a": "fclose",
    "FUN_1000_2726": "fgets",
    "FUN_1000_2aa3": "fopen",
    "FUN_1000_2afc": "fputs",
    "FUN_1000_2c70": "fread",
    "FUN_1000_2efb": "fwrite",
    "FUN_1000_3492": "setvbuf",
    "FUN_1000_1ce3": "clearerr",
    "FUN_1000_1d24": "getdisk",
    "FUN_1000_1d42": "setdisk",
    "FUN_1000_1f49": "chdir",
    "FUN_1000_1f65": "getcurdir",
    "FUN_1000_3886": "findfirst",
    "FUN_1000_38bd": "findnext",
    "FUN_1000_475c": "farmalloc",
    "FUN_1000_4a9a": "farcoreleft",
    "FUN_1000_525b": "int86",
    "FUN_1000_537f": "delay",
    "FUN_1000_4d6e": "exit",
    "FUN_1000_4c8f": "sound",
    "FUN_1000_4cbf": "nosound",
    "FUN_1000_0f76": "F_FTOL",
    "FUN_1000_3eb2": "LXMUL",
    "FUN_1000_1f84": "__IOERROR",
    "FUN_1000_068f": "__realcvt",
    "FUN_1000_20c2": "__OUTC",
    "FUN_1000_20cb": "__OUTS",

    # ── BGI graphics (segment 23f1) ──
    "FUN_23f1_030d": "graphresult",
    "FUN_23f1_03f4": "registerfarbgidriver",
    "FUN_23f1_0979": "initgraph",
    "FUN_23f1_0e3e": "closegraph",
    "FUN_23f1_115d": "setlinestyle",
    "FUN_23f1_119e": "rectangle",
    "FUN_23f1_1211": "setfillstyle",
    "FUN_23f1_125e": "setfillpattern",
    "FUN_23f1_1526": "putimage",
    "FUN_23f1_1bcf": "line",
    "FUN_23f1_1c32": "bar",
    "FUN_23f1_1d5c": "setcolor",
    "FUN_23f1_1f2a": "outtextxy",
    "FUN_23f1_2046": "putpixel",
    "FUN_23f1_2066": "getimage",
    "FUN_23f1_0193": "detectgraph",
    "FUN_23f1_05c9": "getmaxx",
}

# ═══════════════════════════════════════════════════════════════════════════════
# FLOAT/DOUBLE CONSTANT REPLACEMENTS
# ═══════════════════════════════════════════════════════════════════════════════

FLOAT_CONSTANTS = {
    "_ida_dbl_19BFA":  "1.506",
    "_ida_flt_19D26":  "10.0f",
    "_ida_flt_1A1A4":  "10.0f",
    "_ida_dbl_1A1C1":  "(-1.0)",
    "DAT_28d3_1073":   "100.0f",
    "DAT_28d3_1573":   "1000.0f",
}

# ═══════════════════════════════════════════════════════════════════════════════
# STRING CONSTANT REPLACEMENTS
# ═══════════════════════════════════════════════════════════════════════════════

# IDA auto-named strings (sorted longest-first)
STRING_CONSTANTS = [
    ("ida_aFlint9_cfg_0", '"Flint9.cfg"'),
    ("ida_aRb_1",         '"rb"'),
    ("ida_aRb_0",         '"rb"'),
    ("ida_aWb_1",         '"wb"'),
    ("ida_aWb_0",         '"wb"'),
    ("ida_a123",          '"123"'),
    ("ida_a456",          '"456"'),
    ("ida_a789",          '"789"'),
    ("ida_aY_10",         '"Y"'),
    ("ida_aR_1",          '"r"'),
    ("ida_aR_0",          '"r"'),
    ("ida_aZ_6",          '"Z"'),
    ("ida_a10",           '"10"'),
    ("ida_aRb",           '"rb"'),
    ("ida_aR",            '"r"'),
]

# Ghidra s_xxx_28d3_yyyy → "text"
STRING_CLEANUPS = [
    ('(char *)s_String_reference_out_of_range_28d3_28cc + 7', '""  /* empty */'),
    ('s_String_reference_out_of_range_28d3_28cc + 7',         '""  /* empty */'),
    ('s_String_reference_out_of_range_28d3_28cc',             '"String reference out of range"'),
    ('s__Graphics_error_28d3_0ed1',       '"Graphics error"'),
    ('s_graphics_error_28d3_0ee2',        '"graphics error"'),
    ('s_Please_wait_28d3_1214',           '"Please wait"'),
    ('s_Glass_Load_28d3_1221',            '"Glass Load"'),
    ('s_Glass_select_28d3_1250',          '"Glass select"'),
    ('s_Glass__n__28d3_125d',             '"Glass  n "'),
    ('s_Start_28d3_1268',                 '"Start"'),
    ('s_Sorting_28d3_134b',               '"Sorting"'),
    ('s_Dimensions_Modification_28d3_1376','"Dimensions Modification"'),
    ('s_For_STOP__press_ESC_28d3_13b2',   '"For STOP, press ESC"'),
    ('s_For_STOP__press_ESC_28d3_13f2',   '"For STOP, press ESC"'),
    ('s_KPU_End_sens_error_28d3_13c7',    '"KPU End sens error"'),
    ('s_Check_laser__Retry__Ok_28d3_13db', '"Check laser! Retry? Ok"'),
    ('s_Ok__TABLE_END_28d3_1408',         '"Ok! TABLE END"'),
    ('s_File_open_error_28d3_1418',       '"File open error"'),
    ('s_flint1_cfg_28d3_143b',            '"flint1.cfg"'),
    ('s_flash_dat_28d3_1446',             '"flash.dat"'),
    ('s_flash_dat_28d3_1453',             '"flash.dat"'),
    ('s_flinttab_28d3_146b',              '"flinttab"'),
    ('s_Aflint_gls_28d3_1476',            r'"A:\\flint.gls"'),
    ('s_no_mouse___28d3_1580',            '"no mouse !"'),
    ('s_Config_28d3_122e',                '"Config"'),
    ('s_Open_28d3_1235',                  '"Open"'),
]

# ═══════════════════════════════════════════════════════════════════════════════
# PROCESSING
# ═══════════════════════════════════════════════════════════════════════════════

def main():
    print(f"Reading {INPUT_FILE}...")
    with open(INPUT_FILE, 'r', encoding='utf-8', errors='replace') as f:
        text = f.read()
    
    line_count = text.count('\n')
    print(f"  {line_count} lines, {len(text):,} bytes")

    # ── PHASE 1: Fix wrong function names using placeholders ──
    print("Phase 1: Correcting wrong function names...")
    for wrong_name, placeholder in NAME_CORRECTIONS_PHASE1:
        count = text.count(wrong_name)
        if count > 0:
            text = text.replace(wrong_name, placeholder)
            print(f"  {wrong_name} → {placeholder} ({count} occurrences)")

    print("Phase 2: Replacing placeholders with correct names...")
    for placeholder, correct_name in NAME_CORRECTIONS_PHASE2:
        count = text.count(placeholder)
        if count > 0:
            text = text.replace(placeholder, correct_name)
            print(f"  {placeholder} → {correct_name} ({count} occurrences)")

    # ── PHASE 3: Replace library function names ──
    print("Phase 3: Replacing library function names...")
    lib_count = 0
    for ghidra_name, real_name in LIB_FUNC_NAMES.items():
        count = text.count(ghidra_name)
        if count > 0:
            text = text.replace(ghidra_name, real_name)
            lib_count += count
    print(f"  {lib_count} library function replacements")

    # ── PHASE 4: Replace global variable names ──
    print("Phase 4: Replacing global variable names...")
    dat_count = 0
    for ghidra_name, real_name in DATA_NAMES.items():
        count = text.count(ghidra_name)
        if count > 0:
            text = text.replace(ghidra_name, real_name)
            dat_count += count
    print(f"  {dat_count} data/variable replacements")

    # ── PHASE 5: Replace float/double constants ──
    print("Phase 5: Replacing float constants...")
    for ghidra_name, value in FLOAT_CONSTANTS.items():
        count = text.count(ghidra_name)
        if count > 0:
            text = text.replace(ghidra_name, value)

    # ── PHASE 6: Replace string constants ──
    print("Phase 6: Replacing string constants...")
    for ghidra_name, string_val in STRING_CONSTANTS:
        if ghidra_name in text:
            text = text.replace(ghidra_name, string_val)

    for ghidra_str, clean_str in STRING_CLEANUPS:
        if ghidra_str in text:
            text = text.replace(ghidra_str, clean_str)

    # ── PHASE 7: Clean up Ghidra artifacts ──
    print("Phase 7: Cleaning up artifacts...")
    # Remove "undefined" / "undefined1" / "undefined2" type prefixes where possible
    # (leave them in variable declarations but clean up casts)
    text = re.sub(r'\(undefined2\)', '(uint)', text)
    text = re.sub(r'\(undefined1\)', '(uchar)', text)
    text = re.sub(r'\(undefined4\)', '(ulong)', text)

    # Clean up CONCAT patterns
    # CONCAT22(a,b) → MAKELONG(a,b) for readability
    text = re.sub(r'CONCAT22\(', 'MAKELONG(', text)
    text = re.sub(r'CONCAT11\(', 'MAKEWORD_8(', text)

    # Clean up unaff_ prefix (unaffected register variables)
    # Just add a comment marker but keep the name
    # text = re.sub(r'unaff_(\w+)', r'/*reg*/\1', text)

    # ── PHASE 8: Add section separators for readability ──
    print("Phase 8: Adding section markers...")
    # The v2 output already has nice section separators from the Ghidra script
    # Add source-code function signature comments where we know them
    
    FUNC_SIGNATURES = {
        "main":          "int main()",
        "button":        "void button(int btc[], int nmb, char buttxt[])",
        "buttonp":       "void buttonp(int btc[], int nmb, char buttxt[])",
        "ctlbt":         "void ctlbt(int btxl, int btyl, int colctl, char ctltxt[])",
        "pressbt":       "int pressbt(int bt[], int nm)",
        "msgbox":        "int msgbox(char msgtxt[], int more, int f_beep)",
        "msg":           "int msg(int msgx, int msgy, int onoff, char msgtxt[])",
        "WndBkgr":       "void WndBkgr(int xl, int yt, int xr, int yb, int col, char txt[])",
        "dlgcfg":        "int dlgcfg(void)",
        "InrDcr":        "int InrDcr(int param, int pmin, int pmax, int pstep, int updn)",
        "sw_ctl":        "void sw_ctl(int flag, int param, int xpos, int ypos, int col)",
        "dlgopen":       "int dlgopen(char destnm[], char dlgnm[], int flag)",
        "chdiska":       "void chdiska(void)",
        "dlged":         "int dlged(void)",
        "inp_dig":       "long inp_dig(int xl, int yt, double min, double max, int ax)",
        "disksel":       "int disksel(int nmb)",
        "glload":        "void glload(int direct)",
        "dlgload":       "int dlgload(void)",
        "gselect":       "int gselect(void)",
        "dlgstart":      "int dlgstart(void)",
        "ClearRpt":      "void ClearRpt(void)",
        "mainscr":       "void mainscr(int all)",
        "show_reit":     "void show_reit(int mode)",
        "glaspos":       "void glaspos(int xl, int yt, int cw)",
        "drawfl":        "void drawfl(void)",
        "draw":          "void draw(int flag, int all)",
        "DrawPix":       "void DrawPix(int hp, int hs, int vp, int vs, int color)",
        "draw_bt":       "int draw_bt(int btc[], char *bnam[], int nmb)",
        "dlgsort":       "int dlgsort(void)",
        "sort":          "int sort(void)",
        "sort2":         "int sort2(void)",
        "minmax":        "int minmax(void)",
        "scan_ms":       "unsigned int scan_ms(int btc[], char *bnam[], int nbt, int f_beep)",
        "progbar":       "void progbar(long nmb_max, long nmb, int set, int xl, int yt)",
        "htime":         "void htime(char tmpstr[])",
        "dlgdim":        "int dlgdim(void)",
        "cros":          "long cros(unsigned long k1, unsigned long k2)",
        "swap":          "void swap(unsigned long k1, unsigned long k2)",
        "pi_ini":        "int pi_ini(void)",
        "lpuls":         "int lpuls(int flag)",
        "program_pt2":   "void program_pt2(int period, unsigned char gate)",
        "read_pt2":      "unsigned int read_pt2(void)",
        "sh_open":       "void sh_open(unsigned int pos)",
        "sh_close":      "void sh_close(void)",
        "process":       "int process(void)",
        "move_sen":      "int move_sen(int dir)",
        "move":          "int move(int x, int y, int z)",
        "seg_time":      "int seg_time(int dx, int dy, int dz)",
        "calc_k2":       "int calc_k2(int dstep, int k)",
        "rdfile":        "int rdfile(char filename[], char masname[], unsigned int nmb)",
        "wrfile":        "int wrfile(char filename[], char masname[], unsigned int nmb)",
        "RdCfg":         "void RdCfg(int gl_nmber)",
        "FlashRd":       "void FlashRd(void)",
        "FlashWr":       "void FlashWr(void)",
        "CurDir":        "void CurDir(void)",
        "rddir":         "int rddir(char f_namext[])",
        "sort_fnm":      "void sort_fnm(void)",
        "sort_dnm":      "void sort_dnm(void)",
        "rdcft_t":       "long rdcft_t(char filename[])",
        "rdgls":         "int rdgls(void)",
        "rdasc_t":       "int rdasc_t(char filename[])",
        "wrasc":         "int wrasc(char filename[])",
        "wrt_cft":       "int wrt_cft(char filename[])",
        "wrt_bft":       "int wrt_bft(char filename[])",
        "rdbft_t":       "long rdbft_t(char filename[])",
        "rdbmp":         "long rdbmp(char filename[])",
        "set_gr_cursor": "void set_gr_cursor(int hx, int hy, unsigned int far *masks)",
        "ms_init":       "void ms_init(void)",
        "ms_state":      "void ms_state(MOUSE_STATE *m)",
        "ms_move":       "void ms_move(int x, int y)",
        "ms_release":    "int ms_release(MOUSE_STATE *m)",
        "beep":          "void beep(int tone, int duration)",
        "ms_key_cmd":    "int ms_key_cmd(int f_beep)",
    }

    # Add source signature as comment before each function header
    for func_name, sig in FUNC_SIGNATURES.items():
        # Match the function header pattern in the v2 output
        pattern = f" * Function: {func_name}\n"
        if pattern in text:
            replacement = f" * Function: {func_name}\n * Source:   {sig}\n"
            text = text.replace(pattern, replacement, 1)  # Only first occurrence

    # ── Write output ──
    print(f"Writing {OUTPUT_FILE}...")
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
        f.write(text)

    out_size = os.path.getsize(OUTPUT_FILE)
    final_lines = text.count('\n')
    print(f"Done! {final_lines} lines, {out_size:,} bytes ({out_size//1024} KB)")

    # ── Statistics ──
    remaining_fun = len(re.findall(r'FUN_[0-9a-f]{4}_[0-9a-f]{4}', text))
    remaining_dat = len(re.findall(r'DAT_[0-9a-f]{4}_[0-9a-f]{4}', text))
    remaining_ida = len(re.findall(r'ida_sub_[0-9A-Fa-f]+', text))
    remaining_s = len(re.findall(r's_\w+_28d3_[0-9a-f]{4}', text))
    print(f"\nRemaining Ghidra artifacts:")
    print(f"  FUN_xxxx_yyyy: {remaining_fun}")
    print(f"  DAT_xxxx_yyyy: {remaining_dat}")
    print(f"  ida_sub_XXXXX: {remaining_ida}")
    print(f"  s_xxx_28d3_yy: {remaining_s}")


if __name__ == '__main__':
    main()
