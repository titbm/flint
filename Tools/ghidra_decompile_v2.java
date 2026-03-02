// Ghidra headless script v2: targeted decompilation of ALL app functions
// Imports IDA MAP, creates missing functions, sets signatures, decompiles by segment.
// @category Export
// @author Flint project

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import ghidra.program.model.data.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.lang.*;
import ghidra.util.task.ConsoleTaskMonitor;

import java.io.*;
import java.util.*;

public class ghidra_decompile_v2 extends GhidraScript {

    // All known app function addresses (Ghidra segment:offset)
    // Format: ghidraSeg:offset, name, module
    static final String[][] APP_FUNCTIONS = {
        // ── PROJ5.CPP (segment 1928) ──
        {"1928:000e", "main",        "PROJ5.CPP"},
        {"1928:0436", "button",      "PROJ5.CPP"},
        {"1928:05bb", "buttonp",     "PROJ5.CPP"},
        {"1928:06d5", "ctlbt",       "PROJ5.CPP"},
        {"1928:0715", "pressbt",     "PROJ5.CPP"},
        {"1928:07ab", "msgbox",      "PROJ5.CPP"},
        {"1928:08a3", "msg",         "PROJ5.CPP"},
        {"1928:0948", "WndBkgr",     "PROJ5.CPP"},
        {"1928:0a0a", "msgbox1",     "PROJ5.CPP"},
        {"1928:1906", "sw_ctl",      "PROJ5.CPP"},
        {"1928:2578", "dlgcfg",      "PROJ5.CPP"},
        {"1928:3a59", "glload",      "PROJ5.CPP"},
        {"1928:3aaf", "dlgload",     "PROJ5.CPP"},
        {"1928:4395", "ClearRpt",    "PROJ5.CPP"},
        {"1928:43ac", "mainscr",     "PROJ5.CPP"},
        {"1928:4827", "show_reit",   "PROJ5.CPP"},
        {"1928:4979", "glaspos",     "PROJ5.CPP"},
        {"1928:4a4a", "drawfl",      "PROJ5.CPP"},
        {"1928:4acf", "draw",        "PROJ5.CPP"},
        {"1928:4f92", "DrawPix",     "PROJ5.CPP"},
        {"1928:4fc9", "draw_bt",     "PROJ5.CPP"},
        {"1928:505d", "dlgsort",     "PROJ5.CPP"},
        {"1928:5802", "sort2",       "PROJ5.CPP"},
        {"1928:5a33", "minmax",      "PROJ5.CPP"},
        {"1928:5dc0", "scan_ms",     "PROJ5.CPP"},
        {"1928:5f6b", "progbar",     "PROJ5.CPP"},
        {"1928:60ae", "htime",       "PROJ5.CPP"},
        {"1928:634c", "dlgdim",      "PROJ5.CPP"},
        {"1928:6a64", "cros",        "PROJ5.CPP"},
        {"1928:6bc5", "swap",        "PROJ5.CPP"},

        // IDA-resolved addresses for functions Ghidra may not see
        // These are computed: IDA_addr = (idaSeg*16 + offset), Ghidra_seg = idaSeg + 0x1000
        // ida_sub_9C8A  => IDA 0928:1402 => Ghidra 1928:1402 (wait, 0x9C8A = 0928*16+offset?)
        // Actually ida_sub_XXXXX means linear IDA address XXXXX (hex).
        // Linear = seg*16 + offset. IDA seg 0928, so offset = XXXXX - 0x09280 
        // For Ghidra: segment 1928, same offset

        // ida_sub_9C8A: linear 0x9C8A, IDA base seg=0928, offset=0x9C8A-0x9280=0x140A 
        // Wait, that doesn't match. Let me recalculate:
        // IDA segment 0928 means physical base = 0x0928 * 16 = 0x09280
        // ida_sub_9C8A: linear address 0x9C8A
        // 0x9C8A - 0x9280 = 0x140A → Ghidra addr = 1928:140A
        // But the annotation script has ida_sub_9C8A mapped to msgbox1/dlgcfg...
        // Actually dlgcfg is at FUN_1928_2578, and ida_sub_9C8A maps differently.
        // The ida_sub names need proper conversion. Let me just use the FUN_ addresses.

        // Additional IDA-named functions (converted to Ghidra seg:ofs)
        // ida_sub_AB45: 0xAB45 - 0x9280 = 0x18C5 => 1928:18C5  (draw_bt duplicate?)
        // ida_sub_ABCE: 0xABCE - 0x9280 = 0x194E => 1928:194E  (InrDcr)
        // ida_sub_B5BE: 0xB5BE - 0x9280 = 0x233E => 1928:233E  (chdiska)
        // ida_sub_B6DC: 0xB6DC - 0x9280 = 0x245C => 1928:245C  (inp_dig)
        // ida_sub_CB4F: 0xCB4F - 0x9280 = 0x38CF => 1928:38CF  (chkdisk)
        // ida_sub_CE47: 0xCE47 - 0x9280 = 0x3BC7 => 1928:3BC7  (gselect)
        // ida_sub_D18E: 0xD18E - 0x9280 = 0x3F0E => 1928:3F0E  (dlgstart)
        // ida_sub_E5CB: 0xE5CB - 0x9280 = 0x534B => 1928:534B  (sort)

        {"1928:18c5", "draw_bt_2",   "PROJ5.CPP"},  // ida_sub_AB45
        {"1928:194e", "InrDcr",      "PROJ5.CPP"},  // ida_sub_ABCE
        {"1928:233e", "chdiska",     "PROJ5.CPP"},  // ida_sub_B5BE
        {"1928:245c", "inp_dig",     "PROJ5.CPP"},  // ida_sub_B6DC
        {"1928:38cf", "chkdisk",     "PROJ5.CPP"},  // ida_sub_CB4F
        {"1928:3bc7", "gselect",     "PROJ5.CPP"},  // ida_sub_CE47
        {"1928:3f0e", "dlgstart",    "PROJ5.CPP"},  // ida_sub_D18E
        {"1928:534b", "sort",        "PROJ5.CPP"},  // ida_sub_E5CB

        // Functions that exist in source but may be at IDA-resolved addresses:
        // dlgopen: should be between sw_ctl and dlgcfg 
        // disksel: should be near dlgopen
        // dlged: should be near dlgopen

        // ── PIC.CPP (segment 215c) ──
        {"215c:0002", "pi_ini",       "PIC.CPP"},
        {"215c:00a8", "lpuls",        "PIC.CPP"},
        {"215c:01eb", "program_pt2",  "PIC.CPP"},
        {"215c:0221", "read_pt2",     "PIC.CPP"},
        {"215c:0241", "sh_open",      "PIC.CPP"},
        {"215c:028f", "sh_close",     "PIC.CPP"},
        {"215c:02ac", "process",      "PIC.CPP"},
        {"215c:05ad", "move_sen",     "PIC.CPP"},
        {"215c:0750", "move",         "PIC.CPP"},
        {"215c:0b84", "seg_time",     "PIC.CPP"},
        {"215c:0c45", "calc_k2",      "PIC.CPP"},

        // ── RDWRF.CPP (segment 2229) ──
        {"2229:000c", "rdfile",       "RDWRF.CPP"},
        {"2229:006c", "wrfile",       "RDWRF.CPP"},
        {"2229:00da", "RdCfg",        "RDWRF.CPP"},
        {"2229:0326", "FlashRd",      "RDWRF.CPP"},
        {"2229:0404", "FlashWr",      "RDWRF.CPP"},
        {"2229:04e4", "CurDir",       "RDWRF.CPP"},
        {"2229:0511", "rddir",        "RDWRF.CPP"},
        {"2229:062c", "sort_fnm",     "RDWRF.CPP"},
        {"2229:06c8", "sort_dnm",     "RDWRF.CPP"},
        {"2229:077d", "rdcft_t",      "RDWRF.CPP"},
        {"2229:0a8b", "rdgls",        "RDWRF.CPP"},
        {"2229:0b22", "rdasc_t",      "RDWRF.CPP"},
        {"2229:0d88", "wrasc",        "RDWRF.CPP"},
        {"2229:10ce", "wrt_cft",      "RDWRF.CPP"},
        {"2229:1502", "wrt_bft",      "RDWRF.CPP"},
        {"2229:15f8", "rdbft_t",      "RDWRF.CPP"},
        {"2229:1702", "rdbmp",        "RDWRF.CPP"},

        // ── MSKEYC.CPP (segment 23c2) ──
        {"23c2:0001", "set_gr_cursor", "MSKEYC.CPP"},
        {"23c2:003a", "ms_init",       "MSKEYC.CPP"},
        {"23c2:0072", "ms_state",      "MSKEYC.CPP"},
        {"23c2:00ac", "ms_move",       "MSKEYC.CPP"},
        {"23c2:00d5", "ms_release",    "MSKEYC.CPP"},
        {"23c2:0113", "beep",          "MSKEYC.CPP"},
        {"23c2:012f", "ms_key_cmd",    "MSKEYC.CPP"},
    };

    // App code segment prefixes  
    static final Set<String> APP_SEGS = new HashSet<>(Arrays.asList(
        "1928", "215c", "2229", "23c2"
    ));

    @Override
    public void run() throws Exception {
        String outputPath = getScriptArgs()[0];
        PrintWriter out = new PrintWriter(new FileWriter(outputPath));

        FunctionManager funcMgr = currentProgram.getFunctionManager();
        AddressFactory addrFactory = currentProgram.getAddressFactory();
        Listing listing = currentProgram.getListing();

        out.println("/*************************************************************");
        out.println(" * PROJ5.EXE  —  Flint 2.77 (DOS 16-bit)");
        out.println(" * Application Functions Decompilation v2");
        out.println(" * All source-file functions targeted for complete recovery");
        out.println(" * Generated by Ghidra " + ghidra.framework.Application.getApplicationVersion());
        out.println(" *************************************************************/");
        out.println();

        // ===== STEP 1: Import MAP file to create functions Ghidra missed =====
        String mapPath = null;
        if (getScriptArgs().length > 1) {
            mapPath = getScriptArgs()[1];
        } else {
            File outFile = new File(outputPath);
            File workspace = outFile.getParentFile().getParentFile();
            File mapFile = new File(workspace, "Help/PROJ5.map");
            if (mapFile.exists()) mapPath = mapFile.getAbsolutePath();
        }
        
        int mapCreated = 0, mapExisted = 0;
        if (mapPath != null && new File(mapPath).exists()) {
            out.println("// MAP file: " + mapPath);
            BufferedReader mapReader = new BufferedReader(new FileReader(mapPath));
            String mapLine;
            while ((mapLine = mapReader.readLine()) != null) {
                mapLine = mapLine.trim();
                if (mapLine.matches("[0-9A-Fa-f]{4}:[0-9A-Fa-f]{4}\\s+\\S+")) {
                    String[] parts = mapLine.split("\\s+", 2);
                    String addrStr = parts[0];
                    String name = parts[1];
                    if (name.startsWith("loc_") || name.startsWith("locret_") ||
                        name.startsWith("byte_") || name.startsWith("word_") ||
                        name.startsWith("dword_") || name.startsWith("unk_") ||
                        name.startsWith("asc_") || name.startsWith("off_") ||
                        name.startsWith("seg0") || name.startsWith("dseg")) {
                        continue;
                    }
                    String[] addrParts = addrStr.split(":");
                    int idaSegVal = Integer.parseInt(addrParts[0], 16);
                    int ghidraSegVal = idaSegVal + 0x1000;
                    String ghidraSeg = String.format("%04x", ghidraSegVal);
                    String offset = addrParts[1];
                    
                    try {
                        Address addr = addrFactory.getAddress(ghidraSeg + ":" + offset);
                        if (addr == null) continue;
                        Function existing = funcMgr.getFunctionAt(addr);
                        if (existing != null) { mapExisted++; continue; }
                        
                        MemoryBlock block = currentProgram.getMemory().getBlock(addr);
                        if (block == null || !block.isExecute()) continue;
                        
                        ghidra.app.cmd.function.CreateFunctionCmd cmd = 
                            new ghidra.app.cmd.function.CreateFunctionCmd(addr);
                        if (cmd.applyTo(currentProgram, monitor)) {
                            mapCreated++;
                        }
                    } catch (Exception e) { /* skip */ }
                }
            }
            mapReader.close();
        }
        out.println("// MAP import: created=" + mapCreated + " existed=" + mapExisted);
        out.println();

        // ===== STEP 2: Ensure ALL app functions exist =====
        out.println("/* ========== CREATING APP FUNCTIONS ========== */");
        int appCreated = 0, appExisted = 0, appFailed = 0;
        
        for (String[] funcDef : APP_FUNCTIONS) {
            String addrStr = funcDef[0];
            String funcName = funcDef[1];
            String module = funcDef[2];
            
            try {
                Address addr = addrFactory.getAddress(addrStr);
                if (addr == null) {
                    out.println("// ADDR_NULL: " + funcName + " @ " + addrStr);
                    appFailed++;
                    continue;
                }
                
                Function func = funcMgr.getFunctionAt(addr);
                if (func != null) {
                    // Rename if it has a generic name
                    String curName = func.getName();
                    if (curName.startsWith("FUN_") || curName.startsWith("ida_")) {
                        try {
                            func.setName(funcName, SourceType.USER_DEFINED);
                        } catch (Exception e) { /* name collision */ }
                    }
                    appExisted++;
                } else {
                    // Create function
                    MemoryBlock block = currentProgram.getMemory().getBlock(addr);
                    if (block != null && block.isExecute()) {
                        ghidra.app.cmd.function.CreateFunctionCmd cmd = 
                            new ghidra.app.cmd.function.CreateFunctionCmd(addr);
                        if (cmd.applyTo(currentProgram, monitor)) {
                            func = funcMgr.getFunctionAt(addr);
                            if (func != null) {
                                try {
                                    func.setName(funcName, SourceType.USER_DEFINED);
                                } catch (Exception e) { /* name collision */ }
                            }
                            appCreated++;
                            out.println("// CREATED: " + funcName + " @ " + addrStr);
                        } else {
                            appFailed++;
                            out.println("// FAILED: " + funcName + " @ " + addrStr);
                        }
                    } else {
                        appFailed++;
                        out.println("// NO_EXEC_MEM: " + funcName + " @ " + addrStr);
                    }
                }
            } catch (Exception e) {
                out.println("// ERROR: " + funcName + " @ " + addrStr + ": " + e.getMessage());
                appFailed++;
            }
        }
        out.println("// App functions: created=" + appCreated + 
            " existed=" + appExisted + " failed=" + appFailed);
        out.println();

        // ===== STEP 3: Also find dlgopen/disksel/dlged via MAP =====
        // These may have been imported via MAP but at addresses we need to discover
        out.println("/* ========== SEARCHING FOR dlgopen/disksel/dlged ========== */");
        String[] searchNames = {"dlgopen", "disksel", "dlged"};
        if (mapPath != null && new File(mapPath).exists()) {
            BufferedReader mapReader2 = new BufferedReader(new FileReader(mapPath));
            String mapLine2;
            while ((mapLine2 = mapReader2.readLine()) != null) {
                mapLine2 = mapLine2.trim();
                for (String sn : searchNames) {
                    if (mapLine2.contains(sn) || mapLine2.contains("_" + sn)) {
                        out.println("// MAP_MATCH: " + mapLine2);
                    }
                }
            }
            mapReader2.close();
        }
        // Also search by function name in the program
        SymbolTable symTable = currentProgram.getSymbolTable();
        for (String sn : searchNames) {
            SymbolIterator si = symTable.getSymbols(sn);
            while (si.hasNext()) {
                Symbol sym = si.next();
                out.println("// SYM_FOUND: " + sn + " @ " + sym.getAddress());
            }
            // Also search with underscore prefix (C name mangling)
            SymbolIterator si2 = symTable.getSymbols("_" + sn);
            while (si2.hasNext()) {
                Symbol sym = si2.next();
                out.println("// SYM_FOUND: _" + sn + " @ " + sym.getAddress());
            }
        }
        out.println();

        // ===== STEP 4: Set up decompiler with better options =====
        DecompInterface decomp = new DecompInterface();
        DecompileOptions options = new DecompileOptions();
        // Increase analysis timeout for complex functions
        decomp.setOptions(options);
        decomp.openProgram(currentProgram);
        // Longer timeout for complex functions (5 min)
        int decompTimeout = 300;

        // ===== STEP 5: Decompile ALL app-segment functions =====
        out.println("/* ========== FULL DECOMPILATION ========== */");
        out.println();

        // Collect all functions, organize by segment
        Map<String, List<Function>> segFunctions = new LinkedHashMap<>();
        segFunctions.put("1928", new ArrayList<>());  // PROJ5.CPP
        segFunctions.put("215c", new ArrayList<>());  // PIC.CPP
        segFunctions.put("2229", new ArrayList<>());  // RDWRF.CPP
        segFunctions.put("23c2", new ArrayList<>());  // MSKEYC.CPP

        FunctionIterator funcIter = funcMgr.getFunctions(true);
        while (funcIter.hasNext()) {
            Function func = funcIter.next();
            String addrStr = func.getEntryPoint().toString();
            // Extract segment from address (format: XXXX:YYYY)
            if (addrStr.contains(":")) {
                String seg = addrStr.split(":")[0];
                if (segFunctions.containsKey(seg)) {
                    segFunctions.get(seg).add(func);
                }
            }
        }

        // Sort each segment's functions by address
        for (List<Function> funcs : segFunctions.values()) {
            funcs.sort((a, b) -> a.getEntryPoint().compareTo(b.getEntryPoint()));
        }

        String[] segNames = {"PROJ5.CPP", "PIC.CPP", "RDWRF.CPP", "MSKEYC.CPP"};
        String[] segKeys  = {"1928", "215c", "2229", "23c2"};
        
        int decompCount = 0;
        int failCount = 0;

        for (int s = 0; s < segKeys.length; s++) {
            String seg = segKeys[s];
            String modName = segNames[s];
            List<Function> funcs = segFunctions.get(seg);
            
            out.println("/***********************************************************");
            out.println(" * SEGMENT " + seg + " — " + modName);
            out.println(" * " + funcs.size() + " functions");
            out.println(" ***********************************************************/");
            out.println();

            for (Function func : funcs) {
                out.println("/* ────────────────────────────────────────────────────────");
                out.println(" * Function: " + func.getName());
                out.println(" * Module:   " + modName);
                out.println(" * Address:  " + func.getEntryPoint());
                out.println(" * Size:     " + func.getBody().getNumAddresses() + " bytes");
                out.println(" * Return:   " + func.getReturnType().getDisplayName());
                out.println(" * Params:   " + func.getParameterCount());
                
                Parameter[] params = func.getParameters();
                for (Parameter p : params) {
                    out.println(" *   " + p.getDataType().getDisplayName() + " " + p.getName());
                }
                
                Variable[] locals = func.getLocalVariables();
                if (locals.length > 0) {
                    out.println(" * Locals:   " + locals.length);
                    for (Variable v : locals) {
                        out.println(" *   " + v.getDataType().getDisplayName() + " " + v.getName() +
                            " @ " + v.getVariableStorage());
                    }
                }
                
                out.println(" * CallingConv: " + func.getCallingConventionName());
                
                Set<Function> called = func.getCalledFunctions(monitor);
                if (!called.isEmpty()) {
                    out.println(" * Calls: " + called.size() + " functions");
                    for (Function cf : called) {
                        out.println(" *   -> " + cf.getName() + " @ " + cf.getEntryPoint());
                    }
                }
                
                out.println(" * ──────────────────────────────────────────────────────── */");

                // Decompile with extended timeout
                DecompileResults results = decomp.decompileFunction(func, decompTimeout, monitor);
                if (results != null && results.decompileCompleted()) {
                    String code = results.getDecompiledFunction().getC();
                    out.println(code);
                    decompCount++;
                } else {
                    out.println("/* DECOMPILATION FAILED */");
                    // Fallback: assembly listing
                    out.println("/* --- Assembly listing --- */");
                    InstructionIterator instrIter = listing.getInstructions(func.getBody(), true);
                    while (instrIter.hasNext()) {
                        ghidra.program.model.listing.Instruction instr = instrIter.next();
                        out.println("// " + instr.getAddress() + "  " + instr.toString());
                    }
                    out.println("/* --- End assembly --- */");
                    out.println();
                    failCount++;
                }
                out.println();
            }
        }

        // ===== STEP 6: Global variables in data segment =====
        out.println("/* ========== DATA SEGMENT (28d3) GLOBALS ========== */");
        Memory memory = currentProgram.getMemory();
        for (MemoryBlock block : memory.getBlocks()) {
            String blockAddr = block.getStart().toString();
            if (blockAddr.startsWith("28d3")) {
                DataIterator dataIter = listing.getDefinedData(block.getStart(), true);
                int count = 0;
                while (dataIter.hasNext() && count < 5000) {
                    Data d = dataIter.next();
                    if (d.getAddress().compareTo(block.getEnd()) > 0) break;
                    Symbol[] syms = symTable.getSymbols(d.getAddress());
                    String symName = (syms.length > 0) ? syms[0].getName() : "";
                    Object val = d.getValue();
                    out.println("// " + d.getAddress() + " " +
                        d.getDataType().getDisplayName() + " " +
                        symName + (val != null ? " = " + val : ""));
                    count++;
                }
            }
        }
        out.println();

        // ===== STEP 7: String table =====
        out.println("/* ========== STRING TABLE ========== */");
        int strCount = 0;
        DataIterator strIter = listing.getDefinedData(true);
        while (strIter.hasNext()) {
            Data data = strIter.next();
            if (data.getDataType() instanceof StringDataType || 
                data.getDataType().getName().contains("string") ||
                data.getDataType().getName().contains("String")) {
                Object val = data.getValue();
                if (val != null) {
                    String sv = val.toString();
                    if (sv.length() > 0 && sv.length() < 200) {
                        out.println("// STR " + data.getAddress() + ": \"" +
                            sv.replace("\\", "\\\\").replace("\"", "\\\"")
                              .replace("\n","\\n").replace("\r","\\r") + "\"");
                        strCount++;
                    }
                }
            }
        }
        out.println("// Total strings: " + strCount);
        out.println();

        // ===== SUMMARY =====
        out.println("/* ========== SUMMARY ========== */");
        out.println("// App functions decompiled: " + decompCount);
        out.println("// App functions failed:     " + failCount);
        for (int s = 0; s < segKeys.length; s++) {
            out.println("// Segment " + segKeys[s] + " (" + segNames[s] + "): " + 
                segFunctions.get(segKeys[s]).size() + " functions");
        }

        out.flush();
        out.close();
        decomp.dispose();

        println("Export complete: " + outputPath);
        println("Functions decompiled: " + decompCount + ", failed: " + failCount);
    }
}
