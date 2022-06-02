#include "gpio.h"
#include "clock.h"
#include "integer-math.h"
#include <stdint.h>
#include <stdbool.h>

// Clock is 5.8 times slower than expected
#define US_CYCLES 1
#define SCALING_FACTOR 196

// TODO: Cannot have cycles_start nested and cannot be more than 16 seconds
void seconds_start() {
    PUT32(STK_CSR, 4);
    PUT32(STK_RVR, 12000000 - 1);
    // Clear Current Value register
    PUT32(STK_CVR, 0);
    PUT32(STK_CSR, 5);
    while(!((GET32(STK_CSR) >> 16) & 1)) {;}
}


// Clock will run at 12 MHZ
void enable_clock(bool enable_sys) {
    // frequency_mhz * (1000 / 256);
    uint32_t delay = 47;
    PUT32(XOSC_CTRL, 0xaa0);
    PUT32(XOSC_STARTUP, delay);
    PUT32(XOSC_CTRL + SET_OFFSET, 0xfab);

    // Wait till ready
    while (!(GET32(XOSC_STATUS) >> 31));
    // Setup clk_ref so you can setup clock_sys
    if (enable_sys) {
        PUT32(CLK_REF_CTRL, 0x2);
        PUT32(CLK_SYS_CTRL, 0x0);
    }
}

static inline uint32_t micro_second_end() {
    //uint32_t cur_val = GET32(STK_CVR) & (0x7fffff);
    return (GET32(STK_CSR) & (1 << 16));
    //return GET32(STK_CSR) | 1;
    //return 1;
}

/*
void delay_us(uint32_t us) {
    //uint32_t scaled_us = udiv(us * 10, SCALING_FACTOR);
    micro_seconds_start(us - 1);
    while(!micro_second_end()) {;}
}
*/

// XOSC runs at 12MHZ by default
void delay_us(uint32_t us) {
    uint32_t num_loops = (us * 12) >> 8;
    for (int i = 0; i < num_loops; i++) {
        PUT32(XOSC_COUNT + SET_OFFSET, 169);
        while ((GET32(XOSC_COUNT) & 0xff)) {;}
    }
}

/*
// Must be less than 20,000 nanoseconds
// Too slow
void delay_ns(uint32_t ns) {
    // Subtract by one to make up for slow div
    uint32_t num_ticks = udiv(ns, 83) - 1;
    PUT32(XOSC_COUNT + SET_OFFSET, num_ticks);
    while ((GET32(XOSC_COUNT) & 0xff)) {;}
}
*/


void micro_seconds_start(uint32_t count) {
    PUT32(STK_CSR, 0);
    PUT32(STK_RVR, count);
    // Clear Current Value register
    PUT32(STK_CVR, 0);
    PUT32(STK_CSR, 1);
}

//Default speed should be 48MHZ, maybe 125MHZ
void enable_clk_peri(uint32_t source) {
    if (source > 6) {
        return;
    }
    PUT32(CLK_PERI_CTRL + SET_OFFSET, 1 << 11);
    PUT32(CLK_PERI_CTRL + SET_OFFSET, source << 5);
}