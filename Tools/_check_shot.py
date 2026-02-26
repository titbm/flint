data = open(r'..\!GENESIS\Flint 2.77\PROJ5.EXE','rb').read()
# Search for 'Shot' string
for i in range(len(data)-3):
    if data[i:i+4] == b'Shot':
        ctx = data[max(0,i-8):i+12]
        print(f'  Found "Shot" at offset 0x{i:X}: {ctx}')
# Search for 'metal' or 'Metal'
for i in range(len(data)-4):
    if data[i:i+5].lower() == b'metal':
        ctx = data[max(0,i-8):i+12]
        print(f'  Found "metal" at offset 0x{i:X}: {ctx}')

# Check how many buttons in btc_cfg by searching for the bnam_cfg table
# Look for button name strings near config dialog
for s in [b'Ok\x00', b'Cancel\x00', b'protect', b'constant', b'variable', b'Reset']:
    pos = data.find(s)
    if pos != -1:
        print(f'  String "{s}" at 0x{pos:X}')

# Also look for PULS_ON pattern (AND al, 0xBF) in dlgcfg area
# dlgcfg is in PROJ5.CPP, should be a large function
# PC6 pulse: in al, dx; and al, 0xBF; out dx, al
pattern = b'\xec\x24\xbf'  # in al,dx; and al,0xBF
offset = 0
while True:
    pos = data.find(pattern, offset)
    if pos == -1:
        break
    print(f'  PULS_ON pattern (in; and al,0xBF) at 0x{pos:X}')
    offset = pos + 1
