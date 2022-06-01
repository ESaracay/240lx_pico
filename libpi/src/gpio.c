#include "gpio.h"
#include "printf.h"
#include <stdint.h>

#define RESETS_BASE                 0x4000C000
#define RESETS_RESET_CLR       (RESETS_BASE+0x0+0x3000)
#define RESETS_RESET_DONE_RW   (RESETS_BASE+0x8+0x0000)

void reset_periph(uint32_t loc) {
    PUT32(RESET + CLR_OFFSET, 1 << loc);
    while(!((GET32(RESET_DONE) >> loc) & 0x1)) {;}
}

void gpio_reset() {
    reset_periph(RESET_IO_BANK0);
}

void gpio_set_function(uint32_t pin, uint32_t function) {
    if (pin > NUM_GPIOS) {
        return;
    }
    if (function > NUM_PIN_FUNCS) {
        return;
    }
    uint32_t offset = (pin * 8);
    PUT32(IO_BANK_BASE_CTRL + offset, function);
}
/*
uint32_t gpio_is_reset() {
    return (GET32(RESET_DONE) >> 5 & 0x1);
}
void gpio_reset() {
    PUT32(RESETS_RESET_CLR,(1<<5)); //IO_BANK0
    while(1)
    {
        if((GET32(RESETS_RESET_DONE_RW)&(1<<5))!=0) break;
    }
    PUT32(RESETS_RESET_CLR, 1 << RESET_IO_BANK0);
    while(!gpio_is_reset()) {};
}
*/

void gpio_set_input(uint32_t pin) {
    if (pin > NUM_GPIOS) {
        return;
    } 
    uint32_t offset = (pin * 8);
    PUT32(IO_BANK_BASE_CTRL + offset, SIO);
    PUT32(GPIO_OE + SET_OFFSET, 0 << pin);
}

uint32_t gpio_read(uint32_t pin) {
    if (pin > NUM_GPIOS) {
        return 0;
    } 
    return (GET32(GPIO_IN) >> pin) & 1;
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