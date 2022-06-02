#include "gpio.h"
#include "clock.h"
#include <stdint.h>

void cstart() {
    extern uint32_t __bss_start__,__bss_end__;

    // Clear out all values in bss section
    uint32_t *bss_end = &__bss_end__;
    uint32_t *bss = &__bss_start__;
    while (bss < bss_end) {
        *bss++ = 0;
    }

    mymain();
}