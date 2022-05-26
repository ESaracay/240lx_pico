#include "gpio.h"
#include "clock.h"
#include "sw-uart.h"

#define ACTUAL_SECOND 1000000

int mymain() {
    enable_clock();
    gpio_reset();
    //release reset on IO_BANK0
    gpio_set_output(0);
    gpio_set_on(0);
    gpio_set_input(1);
    sw_uart_t uart = sw_uart_init(0, 1, 9600);

    gpio_set_output(15); 
        //output disable

    while(1) {
        gpio_set_on(15);
        // Second
        delay_us(ACTUAL_SECOND);
        gpio_set_off(15);
        sw_uart_putk(&uart, "Hello World");
        //seconds_start();
        delay_us(ACTUAL_SECOND);
    }
    return 0;

}