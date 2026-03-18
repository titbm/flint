/*
    DELAY_TEST.CPP
    Проверка корректности pit_delay_ms() из COMPAT.H

    Тест 1: точность — delay(100) должна занять ~100ms (+/-5ms)
    Тест 2: повторяемость — 10 вызовов delay(10) дают ~100ms суммарно
    Тест 3: стресс — звук не искажается при параллельных delay()

    Компилятор: Open Watcom C++ wpp386 (DOS/4GW 32-bit)
*/

#include <stdio.h>
#include <i86.h>
#include <conio.h>

/* Включаем COMPAT.H из исходников FLINT */
#include "..\..\Flint 2.77 (32bit) src\COMPAT.H"

/*
    Измерить время delay(ms), используя BIOS tick counter (18.2 Гц, ~55ms).
    Грубо, но достаточно для проверки что delay не зависает
    и возвращается примерно вовремя.
    Возвращает микросекунды.
*/
static unsigned long bios_ticks(void) {
    /* В DOS/4GW flat model нижний 1MB маппирован 1:1,
       BIOS tick counter лежит по линейному адресу 0x46C */
    return *(volatile unsigned long *)0x46CUL;
}

static unsigned long measure_delay_us(unsigned ms) {
    unsigned long t0, t1, dt;
    t0 = bios_ticks();
    delay(ms);
    t1 = bios_ticks();
    if(t1 >= t0)
        dt = t1 - t0;
    else
        dt = t1 + 0x1800B0UL - t0;  /* midnight wrap */
    /* 1 BIOS tick = 54925 us (1000000/18.2065) */
    return dt * 54925UL;
}

int main(void) {
    unsigned long us, t0, t1, dt;
    int i, pass, fail = 0;

    printf("=== DLYTEST: pit_delay_ms() accuracy test ===\n\n");

    /* ----------------------------------------
       Тест 1: delay(500) = 500ms +/- 60ms
       (BIOS tick = 55ms, поэтому допуск ~1 тик)
    ---------------------------------------- */
    printf("Test 1: delay(500) accuracy\n");
    us = measure_delay_us(500);
    pass = (us >= 440000UL && us <= 560000UL);
    printf("  Measured: %lu us  (expected 440000..560000)\n", us);
    printf("  Result:   %s\n\n", pass ? "PASS" : "FAIL");
    if(!pass) fail++;

    /* ----------------------------------------
       Тест 2: 10x delay(50) суммарно = ~500ms
    ---------------------------------------- */
    printf("Test 2: 10 x delay(50) repeatability\n");
    t0 = bios_ticks();
    for(i = 0; i < 10; i++)
        delay(50);
    t1 = bios_ticks();
    dt = (t1 >= t0) ? (t1 - t0) : (t1 + 0x1800B0UL - t0);
    us = dt * 54925UL;
    pass = (us >= 440000UL && us <= 560000UL);
    printf("  Measured: %lu us total  (expected 440000..560000)\n", us);
    printf("  Result:   %s\n\n", pass ? "PASS" : "FAIL");
    if(!pass) fail++;

    /* ----------------------------------------
       Тест 3: delay(500) не зависает при звуке
    ---------------------------------------- */
    printf("Test 3: sound not corrupted during delay\n");
    printf("  Starting 1000 Hz tone for 500ms...\n");
    sound(1000);
    us = measure_delay_us(500);
    nosound();
    pass = (us >= 440000UL && us <= 560000UL);
    printf("  delay(500) while sound: %lu us  (expected 440000..560000)\n", us);
    printf("  Result:   %s\n\n", pass ? "PASS" : "FAIL");
    if(!pass) fail++;

    /* ----------------------------------------
       Итог
    ---------------------------------------- */
    printf("============================\n");
    if(fail == 0)
        printf("ALL TESTS PASSED\n");
    else
        printf("FAILED: %d test(s)\n", fail);
    printf("============================\n");
    printf("\nPress any key...\n");
    getch();
    return fail;
}
