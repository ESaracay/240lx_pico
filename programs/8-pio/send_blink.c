#include "rpi.h" 
#include "pio.h"

#define PADS_BANK0_BASE             0x4001C000
#define PADS_BANK0_GPIO25_RW        (PADS_BANK0_BASE+0x68+0x0000)

#define ACTUAL_SECOND 1000000
#define LED 25

static const uint16_t pio_instructions[] = {
    0xe081, //  0: set    pindirs, 1                 
    0x80a0, //  1: pull   block                      
    0x6001, //  2: out    pins, 1                    
    0x0001, //  3: jmp    1                                  
};

int mymain() {
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
    PUT32(PIO0_SM0_PINCTRL, LED | (1 << 20) | (LED << 5) | (1 << 26));
    PUT32(PIO0_CTRL, 1);
    printf("Finished setting val\n");
    while(1) {
        PUT32(PIO0_TXF0, 0xffffffff);
        delay_us(ACTUAL_SECOND);
        printf("Waiting here\n");
        PUT32(PIO0_TXF0, 0);
        delay_us(ACTUAL_SECOND);
    }
    return 0;
}