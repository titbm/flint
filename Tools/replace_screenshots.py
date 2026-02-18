#!/usr/bin/env python3
"""
Replace base64-encoded screenshots in FLINT_Help.html with new generated ones.
Maps screenshot filenames to their line positions in the HTML.
"""
import os, re, base64

HELP_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "Help")
HTML_PATH = os.path.join(HELP_DIR, "FLINT_Help.html")
SCREENSHOTS_DIR = os.path.join(HELP_DIR, "screenshots")

# Order of images as they appear in the HTML file (top to bottom)
SCREENSHOT_ORDER = [
    "mainscr.png",
    "config.png",
    "convert.png",
    "fileopen.png",
    "glassload.png",
    "glassselect.png",
    "start.png",
    "sorting.png",
    "dimensions.png",
    "msgbox.png",
]

def main():
    with open(HTML_PATH, "r", encoding="utf-8") as f:
        html = f.read()

    # Find all data:image/png;base64 occurrences
    pattern = r'data:image/png;base64,[A-Za-z0-9+/=\s]+'
    matches = list(re.finditer(pattern, html))
    
    print(f"Found {len(matches)} base64 images in HTML")
    print(f"Have {len(SCREENSHOT_ORDER)} replacement images")
    
    if len(matches) != len(SCREENSHOT_ORDER):
        print(f"WARNING: count mismatch! Expected {len(SCREENSHOT_ORDER)}, found {len(matches)}")
    
    # Replace from last to first (to preserve positions)
    replacements = list(zip(matches, SCREENSHOT_ORDER))
    replacements.reverse()
    
    for match, filename in replacements:
        img_path = os.path.join(SCREENSHOTS_DIR, filename)
        if not os.path.exists(img_path):
            print(f"  SKIP {filename} - file not found")
            continue
        
        with open(img_path, "rb") as f:
            img_data = f.read()
        
        b64 = base64.b64encode(img_data).decode("ascii")
        new_src = f"data:image/png;base64,{b64}"
        
        html = html[:match.start()] + new_src + html[match.end():]
        print(f"  Replaced image #{SCREENSHOT_ORDER.index(filename)+1}: {filename} ({len(b64)} chars)")
    
    with open(HTML_PATH, "w", encoding="utf-8") as f:
        f.write(html)
    
    print(f"\nDone! Updated {HTML_PATH}")

if __name__ == "__main__":
    main()
