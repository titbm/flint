/*
 * HELLO32.C — Simple 32-bit DOS DPMI32 demo
 * Compile with: bcc32 -WX hello32.c
 *
 * Demonstrates:
 *   1. Running as 32-bit DPMI protected-mode app under DOSBox-X
 *   2. Allocating more than 1MB of memory (proves 32-bit flat model)
 *   3. Using standard C runtime (CW32.LIB)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_ALLOC (4 * 1024 * 1024)   /* 4 MB — impossible in real mode */

int main(void)
{
    char  *p;
    int    i;

    printf("\n");
    printf("  *** Hello from 32-bit Borland C++ (DPMI32) ***\n");
    printf("\n");
    printf("  sizeof(int)    = %d bytes\n", (int)sizeof(int));
    printf("  sizeof(long)   = %d bytes\n", (int)sizeof(long));
    printf("  sizeof(void *) = %d bytes  (must be 4 for 32-bit)\n",
           (int)sizeof(void *));
    printf("\n");

    /* Allocate 4 MB — only possible in protected mode */
    printf("  Allocating %d MB... ", BIG_ALLOC / (1024 * 1024));
    p = (char *)malloc(BIG_ALLOC);
    if (!p) {
        printf("FAILED (malloc returned NULL)\n");
    } else {
        /* Touch every page to prove it's real memory */
        memset(p, 0xAB, BIG_ALLOC);
        /* Verify one byte mid-buffer */
        if ((unsigned char)p[BIG_ALLOC / 2] == 0xAB)
            printf("OK  (flat 32-bit address space works!)\n");
        else
            printf("ERROR: memory verify mismatch\n");
        free(p);
    }

    printf("\n");
    printf("  Press Enter to exit.\n");
    getchar();
    return 0;
}
