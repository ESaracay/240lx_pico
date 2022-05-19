#include "gpio.h"
#include <stdint.h>

int mymain() {
    gpio_reset();
    //release reset on IO_BANK0
    
    gpio_set_output(25); 
        //output disable
  

    while (1) {
        gpio_set_on(25);
        DELAY(0x100000);
        gpio_set_off(25);
        DELAY(0x100000);
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