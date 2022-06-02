#include "gpio.h"
#include <stdint.h>

uint32_t gpio_is_reset() {
    return (GET32(RESET_DONE) >> 5 & 0x1);
}

void gpio_reset() {
    PUT32(RESETS_RESET_CLR, 1 << RESET_IO_BANK0);
    while(!gpio_is_reset()) {};
}



void gpio_set_output(uint32_t pin) {
    // Enable as output
    if (pin > NUM_GPIOS) {
        return;
    } 
    uint32_t offset = (pin * 8);
    PUT32(GPIO_OE_CLR, 1 << pin);
    PUT32(GPIO_OUT_CLR, 1 << pin);
    PUT32(IO_BANK_BASE_CTRL + offset, SIO);
    PUT32(GPIO_OE_SET, 1 << pin);
}

// Pg: 45 in rp2040 datasheet
void gpio_set_on(uint32_t pin) {
    if (pin > NUM_GPIOS) {
        return;
    } 
    PUT32(GPIO_OUT_SET, 1 << pin);
}

void gpio_set_off(uint32_t pin) {
    if (pin > NUM_GPIOS) {
        return;
    } 
    PUT32(GPIO_OUT_CLR, 1 << pin);
}