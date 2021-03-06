// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ----- //
// hello //
// ----- //

#define hello_wrap_target 0
#define hello_wrap 3

static const uint16_t hello_program_instructions[] = {
            //     .wrap_target
    0xe081, //  0: set    pindirs, 1                 
    0x80a0, //  1: pull   block                      
    0x6001, //  2: out    pins, 1                    
    0x0001, //  3: jmp    1                          
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program hello_program = {
    .instructions = hello_program_instructions,
    .length = 4,
    .origin = -1,
};

static inline pio_sm_config hello_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + hello_wrap_target, offset + hello_wrap);
    return c;
}
#endif

