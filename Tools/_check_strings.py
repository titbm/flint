data = open(r'..\!GENESIS\Flint 2.77\PROJ5.EXE','rb').read()

# Count button strings in bnam_cfg area near 0x1B7A4 ("Ok")
# Button names are null-terminated strings, referenced as pointers in bnam_cfg table
# Let's dump strings in that area
print("=== Strings near bnam_cfg (0x1B7A0 - 0x1B900) ===")
i = 0x1B7A0
while i < 0x1B900:
    if data[i] >= 0x20 and data[i] < 0x7f:
        end = i
        while end < len(data) and data[end] != 0:
            end += 1
        s = data[i:end]
        try:
            txt = s.decode('ascii')
            if len(txt) > 0:
                print(f"  0x{i:X}: \"{txt}\"")
        except:
            pass
        i = end + 1
    else:
        i += 1

# Also check bnam_cfg string pointer table
# In large model Borland C, static char *bnam_cfg[] is an array of far pointers (seg:off)
# Each entry = 4 bytes. Let's find the pointer table that points to 0x1B7A4 ("Ok")

# Let's check BNM_CFG value by looking at how many button names are defined
# Search strings from 0x1B820 to 0x1B900
print("\n=== Strings near 0x1B820 - 0x1BB00 ===")
i = 0x1B820
while i < 0x1BB00:
    if data[i] >= 0x20 and data[i] < 0x7f:
        end = i
        while end < len(data) and data[end] != 0:
            end += 1
        s = data[i:end]
        try:
            txt = s.decode('ascii')
            if len(txt) > 0:
                print(f"  0x{i:X}: \"{txt}\"")
        except:
            pass
        i = end + 1
    else:
        i += 1
