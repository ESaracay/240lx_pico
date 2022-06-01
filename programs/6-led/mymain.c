#include "rpi.h" 

#define ACTUAL_SECOND 1000000

int mymain() {

    gpio_set_output(15); 
    uint32_t counter = 0;
    while(1) {
        gpio_set_on(15);
        delay_us(ACTUAL_SECOND);
        printf("hello world\n");
        gpio_set_off(15);
        delay_us(ACTUAL_SECOND);
    }
    return 0;
}