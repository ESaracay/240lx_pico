#include "rpi.h" 
#include "pio.h"

#define PADS_BANK0_BASE             0x4001C000
#define PADS_BANK0_GPIO25_RW        (PADS_BANK0_BASE+0x68+0x0000)

#define ACTUAL_SECOND 1000000
#define LED 15

static const uint16_t pio_instructions[] = {
    0xe081, //  0: set    pindirs, 1                 
    0xfe01, //  1: set    pins, 1                [30]
    0xbf42, //  2: nop                           [31]
    0xfd00, // 12: set    pins, 0                [29]
    0x0001, // 13: jmp    1                          
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
    PUT32(PIO0_SM0_CLKDIV, 0xFFFF0000);
    PUT32(PIO0_SM0_PINCTRL, (LED << 5) | (1 << 26));
    PUT32(PIO0_CTRL, 1);
    printf("exiting\n");
    return 0;
}