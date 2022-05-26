#include "gpio.h"
#include "clock.h"
#include <stdint.h>
// Clock is 5.8 times slower than expected
#define SECOND_US 170000
#define ACTUAL_SECOND 100
#define ONE_MS 172

int mymain() {
    enable_clock();
    gpio_reset();
    //release reset on IO_BANK0
    
    gpio_set_output(0); 
        //output disable

    while(1) {
        //seconds_start();
        gpio_set_off(0);
        //seconds_start();
        delay_us(ACTUAL_SECOND);

        gpio_set_on(0);
        // Second
        delay_us(ACTUAL_SECOND);
    }
    return 0;

}

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