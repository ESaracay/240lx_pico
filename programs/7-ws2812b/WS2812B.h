#ifndef __WS2812B__
#define __WS2812B__
#include "pio.h"
/*
 * The data sheet for WS2812B says the following timings: 
 *      T0H    0: .35us +- .15us
 *      T1H    1: .9us +- .15us
 *      T0L    0: .9us +- .15us
 *      T1L    1: .35us +- .15us
 *      Trst = 80us 
 */

#define ns_to_bitloops(x) (unsigned) (x/40)


    enum { 
        // to send a 1: set pin high for T1H ns, then low for T0H ns.
        T1H = ns_to_bitloops(900),        // Width of a 1 bit in ns
        T0H = ns_to_bitloops(350),        // Width of a 0 bit in ns
        // to send a 0: set pin high for T1L ns, then low for T0L ns.
        T1L = ns_to_bitloops(350),        // Width of a 1 bit in ns
        T0L = ns_to_bitloops(900),        // Width of a 0 bit in ns

        // to make the LED switch to the new values, old the pin low for FLUSH ns
        FLUSH = ns_to_bitloops(50 *1000)    // how long to hold low to flush
    };



static inline void sendbit(uint32_t bit) {
    /*
    while (1) {
            if((GET32(PIO0_FSTAT) & ( 1<< 16) )== 0) break;
        }
        */
        // Should be just a 1 or 0
        PUT32(PIO0_TXF0, bit);
}

// Write out a zero for 39 ints
static inline void pix_flush(uint32_t LED) { 
    gpio_set_output(LED);
    DELAY(1000);
    gpio_set_function(LED, PIO0);
}

static void pix_sendbyte(uint8_t b) {
    for(int i = 7; i >= 0; i--) {
        //printf("print val %d\n", (b>>i) & 0x1);
        sendbit((b >> i) & 0x1);
    }
}

static inline void pix_sendpixel(uint8_t r, uint8_t g, uint8_t b) {
    pix_sendbyte(g);
    pix_sendbyte(r);
    pix_sendbyte(b);
}

#endif
