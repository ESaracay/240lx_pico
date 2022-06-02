#include "rpi.h" 

#define ACTUAL_SECOND 1000000

static inline void inline_gpio_set_on(uint32_t pin) {
    PUT32(GPIO_OUT_SET, 1 << pin);
}

static inline void inline_gpio_set_off(uint32_t pin) {
    PUT32(GPIO_OUT_CLR, 1 << pin);
}

int mymain() {

    gpio_set_output(15); 
    uint32_t counter = 0;
    while(1) {
        inline_gpio_set_on(15);
        DELAY(100);
        //printf("hello world\n");
        inline_gpio_set_off(15);
        DELAY(100);
    }
    return 0;
}