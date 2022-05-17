#include "gpio.h"
#include <stdint.h>
#define SIO 0x5
#define CTRL 0x40014000
#define IO_BANK0_BASE               0x40014000
#define IO_BANK0_GPIO25_CTRL_    (IO_BANK0_BASE+0x0CC+0x0000)
void gpio_reset() {
    PUT32(RESET, RESET_IO_BANK0);
}

uint32_t gpio_is_reset() {
    return (GET32(RESET_DONE) >> 5 & 0x1);
}

/*
void gpio_set_output(uint32_t pin) {
    PUT32(IO_BANK0_GPIO25_CTRL_, 5);
    /*
    if (pin > NUM_GPIOS) {
        return;
    } 
    //uint32_t offset = (pin * 8) + 4;
    uint32_t offset = 0x0CC;
    // Setting to SIO
    uint32_t val = 0x5; 
    PUT32(0x40014000 + offset, val);
}
*/

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