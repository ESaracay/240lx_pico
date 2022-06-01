#include "gpio.h"
#include "clock.h"
#include "sw-uart.h"
#include <stdint.h>
#include "cstart.h"
#include "printf.h"

#define ACTUAL_SECOND 1000000

int mymain() {
    enable_clock();
    //gpio_reset();

    gpio_set_output(15); 
    uint32_t counter = 0;
    while(1) {
        gpio_set_on(15);
        delay_us(ACTUAL_SECOND);
        counter++;
        printf("Hello World: %x\n", counter);
        gpio_set_off(15);
        delay_us(ACTUAL_SECOND);
    }
    return 0;
}

void cstart() {
    extern uint32_t __bss_start__,__bss_end__;
    gpio_reset();

    // Clear out all values in bss section
    uint32_t *bss_end = &__bss_end__;
    uint32_t *bss = &__bss_start__;
    while (bss < bss_end) {
        *bss++ = 0;
    }

    if(!init_uart_printing()){
        return;
    }

    mymain();
}