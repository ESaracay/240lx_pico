#include "clock.h"
#include "sw-uart.h"
#include "gpio.h"

static inline void timed_write(int pin, int v, unsigned usec) {
    if (v) gpio_set_on(pin);
    else gpio_set_off(pin);
    delay_us(usec);
}

void sw_uart_putc(sw_uart_t *uart, unsigned char c) {
    timed_write(uart->tx, 0, uart->usec_per_bit);
    for (int i = 0; i < 8; i++) {
        timed_write(uart->tx, (c >> i) & 1, uart->usec_per_bit);
    }
    // Stop bit
    timed_write(uart->tx, 1, uart->usec_per_bit);
}

void sw_uart_putk(sw_uart_t *uart, const char *msg) {
    for(int i = 0; msg[i] != '\0'; i++) {
        sw_uart_putc(uart, msg[i]);
    }
}

int init_uart_printing() {
    gpio_set_output(0);
    gpio_set_on(0);
    gpio_set_input(1);
    global_uart = sw_uart_init(0, 1, 9600);
    return 1;
}
