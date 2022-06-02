#include "rpi.h" 
#include "WS2812B.h"

#define PADS_BANK0_BASE             0x4001C000
#define PADS_BANK0_GPIO25_RW        (PADS_BANK0_BASE+0x68+0x0000)

#define ACTUAL_SECOND 1000000
#define LED 15

static const uint16_t pio_instructions[] = {
    0xe081, //  0: set    pindirs, 1                 
    0xe001, //  1: set    pins, 1                    
    0x80a0, //  2: pull   block                      
    0x6021, //  3: out    x, 1                       
    0x0028, //  4: jmp    !x, 8                      
    0xe601, //  5: set    pins, 1                [6] 
    0xe200, //  6: set    pins, 0                [2] 
    0x0001, //  7: jmp    1                          
    0xe900, //  8: set    pins, 0                [9] 
    0x0001, //  9: jmp    1                                         
};


int mymain() {
    enable_clock(true);
    // 0. Reset pads
    reset_pads();
    // 1. Reset PIO0
    reset_pio();

    printf("periph reset\n");

    int size = sizeof pio_instructions / sizeof pio_instructions[0];
    for (int i = 0; i < size; i++) {
        PUT32(PIO0_INSTR_MEM_BASE + (i * 4), pio_instructions[i]);
        printf("Wrote to mem addr %x\n", PIO0_INSTR_MEM_BASE + (i *4));
    }
    // 1. enable PIO on gpio pin 
    gpio_set_function(LED, PIO0);

    // 2. Drive PIO 
    drive_pad(LED);
    // 3. Setup PIO registers, what pins we control and enable
    // Have to set out count and set count and base pg.401
    //PUT32(PIO0_SM0_CLKDIV + SET_OFFSET, (10000 << 16));
    //PUT32(PIO0_SM0_CLKDIV + SET_OFFSET, (128 << 8));
    PUT32(PIO0_SM0_PINCTRL, LED | (1 << 20) | (LED << 5) | (1 << 26));
    PUT32(PIO0_CTRL, 1);
    printf("Finished setting val\n");

    //pix_sendpixel(LED, 0xff,0,0);
    //pix_flush();
    while (1) {
        //while (1) {
            //if((GET32(PIO0_FSTAT) & ( 1<< 16) )== 0) break;
        //}
        //PUT32(PIO0_TXF0, 0x1);
        //while (1) {
            //if((GET32(PIO0_FSTAT) & ( 1<< 16) )== 0) break;
        //}
        //PUT32(PIO0_TXF0, 0x0);
        pix_sendpixel(0xff,0,0);
        pix_sendpixel(0xff,0,0);
        // same as writing low

        pix_flush();
        DELAY(10000000);

        printf("Cycle complete\n");
    }
    return 0;
}