#include "gpio.h"
#include <stdint.h>

void gpio_set_output(uint32_t pin) {
    if (pin > NUM_GPIOS) {
        return;
    } 
    uint32_t offset = (pin * 4);
    uint32_t val = 0x3 << 12; 
    PUT32(GPIO_IO_BANK_CTRL + offset, val);
}

void gpio_set_on(uint32_t pin) {
    if (pin > NUM_GPIOS) {
        return;
    } 
    uint32_t offset = (pin * 4);
    uint32_t val =  0x3 << 8;
    PUT32(GPIO_IO_BANK_CTRL + offset, val);
}

void gpio_set_off(uint32_t pin) {
    if (pin > NUM_GPIOS) {
        return;
    } 
    uint32_t offset = (pin * 4);
    uint32_t val =  0x2 << 8;
    PUT32(GPIO_IO_BANK_CTRL + offset, val);
}