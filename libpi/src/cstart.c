#include "gpio.h"
#include "clock.h"
#include "sw-uart.h"
#include <stdint.h>
#include "cstart.h"
#include "printf.h"
#include "uart.h"
#include <stdbool.h>

void cstart() {
    // Clear out all values in bss section
    extern uint32_t __bss_start__,__bss_end__;
    uint32_t *bss_end = &__bss_end__;
    uint32_t *bss = &__bss_start__;
    while (bss < bss_end) {
        *bss++ = 0;
    }   // Extrememly important that gpio is deasserted before trying anything
    enable_clock(false);
    PUT32(CLK_PERI_CTRL, (1 << 11) | (0x4 << 5));

    gpio_reset();
    init_uart_printing();
    global_hw_uart.tx = 12;
    global_hw_uart.rx = 13;
    global_hw_uart.baud_rate = 115200;
    global_hw_uart.index = UART0;
    uart_init(&global_hw_uart);

    mymain();
}