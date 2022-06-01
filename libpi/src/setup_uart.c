#include "gpio.h"
#include "clock.h"
#include "sw-uart.h"
#include "cstart.h"
#include "printf.h"

#define ACTUAL_SECOND 1000000

int mymain() {
    enable_clock();
    gpio_reset();

    gpio_set_output(15); 

    while(1) {
        gpio_set_on(15);
        delay_us(ACTUAL_SECOND);
        printf("Hello World\n");
        gpio_set_off(15);
        delay_us(ACTUAL_SECOND);
    }
    return 0;

}