#!/usr/bin/env python3
"""
BFT File Analyzer — diagnostic tool for Flint BFT files.
Reads a .bft file and reports z-coordinate distribution, nglas value,
dimensions, and statistics useful for diagnosing z-density issues.

Usage:
    python analyze_bft.py <file.bft>
    python analyze_bft.py <file1.bft> <file2.bft>   # compare two files
"""
import sys
import struct
import os
from collections import Counter


def read_bft(filename):
    """Read a BFT file and return header info + point data."""
    with open(filename, 'rb') as f:
        # Header: 7 x uint16 = 14 bytes
        header_raw = f.read(14)
        if len(header_raw) < 14:
            print(f"ERROR: File too short ({len(header_raw)} bytes)")
            return None

        tmp = struct.unpack('<7H', header_raw)
        magic = tmp[0]
        if magic != 0x6662:
            print(f"ERROR: Not a BFT file (magic=0x{magic:04X}, expected 0x6662)")
            return None

        nglas_raw = tmp[1]
        nglas = float(nglas_raw) / 1000.0  # (float) cast as in original
        xsize = tmp[2]
        ysize = tmp[3]
        zsize = tmp[4]
        nmax = tmp[5] * 65536 + tmp[6]

        # Point data: 3 x int16 per point, read in blocks of 2 points (12 bytes)
        nblocks = nmax // 2 + nmax % 2
        point_data = f.read(nblocks * 12)

        points = []
        for i in range(nmax):
            offset = i * 6
            if offset + 6 > len(point_data):
                print(f"WARNING: Truncated at point {i}/{nmax}")
                break
            x, y, z = struct.unpack_from('<3h', point_data, offset)
            points.append((x, y, z))

    return {
        'filename': filename,
        'nglas_raw': nglas_raw,
        'nglas': nglas,
        'xsize': xsize,
        'ysize': ysize,
        'zsize': zsize,
        'nmax': nmax,
        'points': points,
    }


def analyze(bft):
    """Print detailed analysis of a BFT file."""
    print(f"=" * 60)
    print(f"File: {bft['filename']}")
    print(f"=" * 60)
    print(f"nglas (raw): {bft['nglas_raw']}  =>  nglas = {bft['nglas']:.6f}")
    print(f"xsize: {bft['xsize']}  ({bft['xsize']/10:.1f} mm)")
    print(f"ysize: {bft['ysize']}  ({bft['ysize']/10:.1f} mm)")
    print(f"zsize: {bft['zsize']}  ({bft['zsize']/10:.1f} mm)")
    print(f"nmax:  {bft['nmax']} points")
    print()

    if not bft['points']:
        print("No points to analyze.")
        return

    xs = [p[0] for p in bft['points']]
    ys = [p[1] for p in bft['points']]
    zs = [p[2] for p in bft['points']]

    print("--- Raw coordinates (BFT stored, motor steps, 1 unit = 0.01 mm) ---")
    print(f"  X: min={min(xs):6d}  max={max(xs):6d}  range={max(xs)-min(xs):6d}  ({(max(xs)-min(xs))/100:.2f} mm motor)")
    print(f"  Y: min={min(ys):6d}  max={max(ys):6d}  range={max(ys)-min(ys):6d}  ({(max(ys)-min(ys))/100:.2f} mm motor)")
    print(f"  Z: min={min(zs):6d}  max={max(zs):6d}  range={max(zs)-min(zs):6d}  ({(max(zs)-min(zs))/100:.2f} mm motor)")
    print()

    # Z after nglas multiplication = physical distance inside glass
    # Motor moves delta_z steps -> focus shifts delta_z * nglas * 0.01mm inside glass
    z_glass = [int(z * bft['nglas']) for z in zs]
    z_glass_range = max(z_glass) - min(z_glass)
    print("--- Z physical in glass (raw * nglas, as displayed in editor) ---")
    print(f"  Z_glass: min={min(z_glass):6d}  max={max(z_glass):6d}  range={z_glass_range:6d}  ({z_glass_range/100:.2f} mm in glass)")
    print()

    # Z unique layers
    z_layers_raw = sorted(set(zs))
    z_layers_glass = sorted(set(z_glass))
    print(f"--- Z layers (unique Z values) ---")
    print(f"  Motor steps (raw):  {len(z_layers_raw)} unique values")
    print(f"  Glass (raw*nglas):   {len(z_layers_glass)} unique values")
    print()

    # Z gaps distribution (consecutive unique z values)
    if len(z_layers_raw) > 1:
        gaps_raw = [z_layers_raw[i+1] - z_layers_raw[i] for i in range(len(z_layers_raw)-1)]
        print(f"--- Z gap: motor steps (raw) ---")
        print(f"  Min gap: {min(gaps_raw)} steps = {min(gaps_raw)/100:.3f} mm motor")
        print(f"  Max gap: {max(gaps_raw)} steps = {max(gaps_raw)/100:.3f} mm motor")
        print(f"  Avg gap: {sum(gaps_raw)/len(gaps_raw):.1f} steps = {sum(gaps_raw)/len(gaps_raw)/100:.3f} mm motor")
        gap_counts = Counter(gaps_raw)
        print(f"  Gap histogram (top 10):")
        for gap, cnt in gap_counts.most_common(10):
            print(f"    gap={gap:5d} ({gap/100:6.3f} mm motor, {gap*bft['nglas']/100:6.3f} mm glass): {cnt:4d} layers")
        print()

    if len(z_layers_glass) > 1:
        gaps_glass = [z_layers_glass[i+1] - z_layers_glass[i] for i in range(len(z_layers_glass)-1)]
        print(f"--- Z gap: physical in glass (raw * nglas) ---")
        print(f"  Min gap: {min(gaps_glass)} = {min(gaps_glass)/100:.3f} mm in glass")
        print(f"  Max gap: {max(gaps_glass)} = {max(gaps_glass)/100:.3f} mm in glass")
        print(f"  Avg gap: {sum(gaps_glass)/len(gaps_glass):.1f} = {sum(gaps_glass)/len(gaps_glass)/100:.3f} mm in glass")
        print()

    # Points per Z layer
    z_counts_raw = Counter(zs)
    print(f"--- Points per Z layer (first 20 layers) ---")
    for z_val in z_layers_raw[:20]:
        n = z_counts_raw[z_val]
        z_motor_mm = z_val / 100
        z_glass_mm = z_val * bft['nglas'] / 100
        print(f"  z_raw={z_val:6d} ({z_motor_mm:7.2f} mm motor, {z_glass_mm:6.2f} mm glass)  points={n:5d}")
    if len(z_layers_raw) > 20:
        print(f"  ... ({len(z_layers_raw) - 20} more layers)")
    print()

    # znew calculation preview (for process())
    # znew = 11000 - zptr - zsize*10*(1-1/nglas) - iTabl_z_raw
    # iTabl_z_raw = raw BFT Z value (motor steps) — when loaded via F3 main screen
    nglas = bft['nglas']
    zsize = bft['zsize']
    refraction_offset = int(zsize * 10 * (1.0 - 1.0 / nglas))
    print(f"--- process() znew preview (zptr=0, F3 main screen load = raw) ---")
    print(f"  Refraction offset = zsize*10*(1-1/nglas) = {zsize}*10*(1-1/{nglas:.3f}) = {refraction_offset}")
    print(f"  znew = 11000 - zptr - {refraction_offset} - z_raw")
    z_raw_sorted = sorted(zs)
    znew_min = 11000 - refraction_offset - z_raw_sorted[-1]
    znew_max = 11000 - refraction_offset - z_raw_sorted[0]
    print(f"  znew range: {znew_min} .. {znew_max}  ({znew_min/100:.1f} .. {znew_max/100:.1f} mm motor pos)")
    if len(z_raw_sorted) > 1:
        print(f"  znew step = raw Z gap = {gaps_raw[0]} motor steps = {gaps_raw[0]/100:.3f} mm motor")
        print(f"  -> physical Z step in glass = {gaps_raw[0]*nglas/100:.3f} mm")
    print()

    # Round-trip test: what happens after save+load cycle
    print(f"--- Round-trip test (load BFT -> *nglas -> /nglas -> compare) ---")
    diffs = []
    for z_raw in zs:
        z_air_v = int(float(z_raw) * nglas)
        z_back = int(float(z_air_v) / nglas)
        diffs.append(z_raw - z_back)

    diff_counts = Counter(diffs)
    print(f"  Differences (z_original - z_after_roundtrip):")
    for d, cnt in sorted(diff_counts.items()):
        pct = 100.0 * cnt / len(diffs)
        print(f"    diff={d:+2d}: {cnt:6d} points ({pct:5.1f}%)")
    print()


def compare(bft1, bft2):
    """Compare two BFT files."""
    print()
    print(f"{'='*60}")
    print(f"COMPARISON")
    print(f"{'='*60}")
    print(f"File 1: {bft1['filename']}")
    print(f"File 2: {bft2['filename']}")
    print()

    for field in ['nglas_raw', 'nglas', 'xsize', 'ysize', 'zsize', 'nmax']:
        v1 = bft1[field]
        v2 = bft2[field]
        status = "OK" if v1 == v2 else "DIFFER"
        if isinstance(v1, float):
            print(f"  {field:12s}: {v1:12.6f}  vs  {v2:12.6f}  [{status}]")
        else:
            print(f"  {field:12s}: {v1:12d}  vs  {v2:12d}  [{status}]")
    print()

    n = min(len(bft1['points']), len(bft2['points']))
    x_diffs = y_diffs = z_diffs = 0
    max_zdiff = 0
    for i in range(n):
        p1 = bft1['points'][i]
        p2 = bft2['points'][i]
        if p1[0] != p2[0]: x_diffs += 1
        if p1[1] != p2[1]: y_diffs += 1
        if p1[2] != p2[2]:
            z_diffs += 1
            d = abs(p1[2] - p2[2])
            if d > max_zdiff:
                max_zdiff = d

    print(f"  Point differences (of {n} compared):")
    print(f"    X: {x_diffs} differ")
    print(f"    Y: {y_diffs} differ")
    print(f"    Z: {z_diffs} differ (max |diff| = {max_zdiff})")

    if z_diffs > 0:
        print(f"\n  First 10 Z differences:")
        shown = 0
        for i in range(n):
            if bft1['points'][i][2] != bft2['points'][i][2]:
                z1 = bft1['points'][i][2]
                z2 = bft2['points'][i][2]
                print(f"    point[{i}]: z1={z1} z2={z2} diff={z1-z2}")
                shown += 1
                if shown >= 10:
                    break


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)

    files = []
    for path in sys.argv[1:]:
        if not os.path.isfile(path):
            print(f"ERROR: File not found: {path}")
            sys.exit(1)
        bft = read_bft(path)
        if bft:
            files.append(bft)

    for bft in files:
        analyze(bft)

    if len(files) == 2:
        compare(files[0], files[1])


if __name__ == '__main__':
    main()
