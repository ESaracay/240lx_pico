#include <stdint.h>

// pg. 391
#define PIO0_BASE 0x50200000
#define PIO1_BASE 0x50300000

// There are 4 state machines total that can store code
enum {
    PIO0_CTRL = 0x000 + PIO0_BASE,
    PIO0_FSTAT = 0x004 + PIO0_BASE,
    PIO0_FDEBUG = 0x008 + PIO0_BASE,
    PIO0_FLEVEL = 0x00c + PIO0_BASE,
    PIO0_TXF0 = 0x010 + PIO0_BASE,
    PIO0_RXF0 = 0x020 + PIO0_BASE,
    PIO0_INSTR_MEM_BASE = 0x048 + PIO0_BASE,
    PIO0_SM0_CLKDIV = 0x0c8 + PIO0_BASE,
    PIO0_SM0_EXECCTRL = 0x0cc + PIO0_BASE,
    PIO0_SM0_SHIFTCTRL = 0x0d0 + PIO0_BASE,
    PIO0_SM0_PINCTRL = 0x0dc + PIO0_BASE,
};
