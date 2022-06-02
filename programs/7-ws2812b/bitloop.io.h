// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ------ //
// ws2812 //
// ------ //

#define ws2812_wrap_target 0
#define ws2812_wrap 8

static const uint16_t ws2812_program_instructions[] = {
            //     .wrap_target
    0xe081, //  0: set    pindirs, 1                 
    0x80a0, //  1: pull   block                      
    0x6021, //  2: out    x, 1                       
    0x0027, //  3: jmp    !x, 7                      
    0xe601, //  4: set    pins, 1                [6] 
    0xe200, //  5: set    pins, 0                [2] 
    0x0001, //  6: jmp    1                          
    0xe900, //  7: set    pins, 0                [9] 
    0x0001, //  8: jmp    1                          
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program ws2812_program = {
    .instructions = ws2812_program_instructions,
    .length = 9,
    .origin = -1,
};

static inline pio_sm_config ws2812_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + ws2812_wrap_target, offset + ws2812_wrap);
    return c;
}
#endif

