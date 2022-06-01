#include "gpio.h"
#include "uart.h"
#include "integer-math.h"
#include "printf.h"
#include "clock.h"

// !!!! Expects gpio_reset() to have been called before hand
void uart_init(hw_uart_t *uart) {
    gpio_set_function(uart->tx, F2);
    gpio_set_function(uart->rx, F2);
    if (uart->index != UART0 && uart->index != UART1) {
        return;
    }
    reset_periph(RESET_UART0);

    uint32_t baud_rate_divisor = udiv(CLK_PERI_DEFAULT_SPEED, 16 * uart->baud_rate);
    // Careful with overflow
    uint32_t baud_rate_frac = udiv(CLK_PERI_DEFAULT_SPEED * 100, 16 * uart->baud_rate) - (baud_rate_divisor * 100);
    uint32_t fbrd = udiv((baud_rate_frac * 64), 100);
    //printf("baud_rate_divisor val: %d\n", baud_rate_divisor);
    //printf("baud_rate_frac val: %d\n", fbrd);
    PUT32(uart->index + UART_IBRD_OFFSET , baud_rate_divisor);
    PUT32(uart->index + UART_FBRD_OFFSET, fbrd);
    // Setup uart->index with 8n1 (pg 456)
    PUT32(uart->index + UART_LCR_OFFSET + SET_OFFSET, 0b11 << 5);
    // Enable fifos
    PUT32(uart->index + UART_LCR_OFFSET + SET_OFFSET, 1 << 4);
    // Enable uart->index and tx and rx pg 457
    PUT32(uart->index + UART_CTRL_OFFSET + SET_OFFSET, 1 << 8);
    PUT32(uart->index + UART_CTRL_OFFSET + SET_OFFSET, 1 << 9);
    PUT32(uart->index + UART_CTRL_OFFSET + SET_OFFSET, 1);
}

// 1 = at least one byte on rx queue, 0 otherwise
static int uart_can_getc(void) {
    return 0;
}

// returns one byte from the rx queue, if needed
// blocks until there is one.
int uart_getc(void) {
	return 0;
}

// 1 = space to put at least one byte, 0 otherwise.
int uart_can_putc(void) {
    return !((GET32(global_hw_uart.index + UART_FR_OFFSET) >> 5) & 1);
}

// put one byte on the tx qqueue, if needed, blocks
// until TX has space.
void uart_putc(unsigned char c) {
    while(!uart_can_putc()){;}
    PUT32(global_hw_uart.index + UART_DATA_OFFSET, c);
}


// simple wrapper routines useful later.
// a maybe-more intuitive name for clients.
int uart_has_data(void) {
    return uart_can_getc();
}

int uart_getc_async(void) { 
    if(!uart_has_data())
        return -1;
    return uart_getc();
}