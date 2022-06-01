#include "gpio.h"
#include "clock.h"
#include "sw-uart.h"
#include <stdint.h>
#include "cstart.h"
#include "printf.h"
#include "uart.h"

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

void cstart() {
    // Extrememly important that gpio is deasserted before trying anything
    extern uint32_t __bss_start__,__bss_end__;
    uint8_t *bss_end = &__bss_end__;
    uint8_t *bss = &__bss_start__;
    while (bss < bss_end) {
        *bss++ = 0;
    }
    enable_clock();
    PUT32(CLK_PERI_CTRL, (1 << 11) | (0x4 << 5));

    gpio_reset();
    init_uart_printing();
    global_hw_uart.tx = 12;
    global_hw_uart.rx = 13;
    global_hw_uart.baud_rate = 115200;
    global_hw_uart.index = UART0;
    uart_init(&global_hw_uart);

    // Clear out all values in bss section
    printf("Going to jump to mymain\n");
    mymain();
}