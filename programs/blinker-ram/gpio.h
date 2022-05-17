#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>
#define GPIO_BASE 0x40014000 
// Checkout page 260 of rp2040 datasheet
typedef enum {
    GPIO_FUNC_ALT0    = 4,
    GPIO_FUNC_ALT1    = 5,
    GPIO_FUNC_ALT2    = 6,
    GPIO_FUNC_ALT3    = 7,
    GPIO_FUNC_ALT4    = 3,
    GPIO_FUNC_ALT5    = 2,
} gpio_func_t;

#define NUM_GPIOS 30
#define GPIO_IO_BANK_STATUS GPIO_BASE + 0x000
#define GPIO_IO_BANK_CTRL GPIO_BASE + 0x004

void PUT32(uint32_t pin, uint32_t val);
uint32_t GET32(uint32_t pin);
void DELAY(uint32_t val);

void gpio_set_function(uint32_t pin, gpio_func_t func);

void gpio_set_input(uint32_t pin);

void gpio_set_output(uint32_t pin);

void gpio_set_on(uint32_t pin);

void gpio_set_off(uint32_t pin);

void gpio_read(uint32_t pin);

// write either 1 or 0
void gpio_write(uint32_t pin, uint32_t val);

// set <pin> as a pullup
void gpio_set_pullup(unsigned pin);
// set <pin> as a pulldown.
void gpio_set_pulldown(unsigned pin);


#endif