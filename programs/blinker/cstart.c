#include "gpio.h"
#include <stdint.h>
#define RESETS_BASE                 0x4000C000

#define RESETS_RESET_RW             (RESETS_BASE+0x0+0x0000)
#define RESETS_RESET_XOR            (RESETS_BASE+0x0+0x1000)
#define RESETS_RESET_SET            (RESETS_BASE+0x0+0x2000)
#define RESETS_RESET_CLR            (RESETS_BASE+0x0+0x3000)

#define RESETS_WDSEL_RW             (RESETS_BASE+0x4+0x0000)
#define RESETS_WDSEL_XOR            (RESETS_BASE+0x4+0x1000)
#define RESETS_WDSEL_SET            (RESETS_BASE+0x4+0x2000)
#define RESETS_WDSEL_CLR            (RESETS_BASE+0x4+0x3000)

#define RESETS_RESET_DONE_RW        (RESETS_BASE+0x8+0x0000)
#define RESETS_RESET_DONE_XOR       (RESETS_BASE+0x8+0x1000)
#define RESETS_RESET_DONE_SET       (RESETS_BASE+0x8+0x2000)
#define RESETS_RESET_DONE_CLR       (RESETS_BASE+0x8+0x3000)

#define SIO_GPIO_OUT_RW             (SIO_BASE+0x10)
#define SIO_GPIO_OUT_SET            (SIO_BASE+0x14)
#define SIO_GPIO_OUT_CLR            (SIO_BASE+0x18)
#define SIO_GPIO_OUT_XOR            (SIO_BASE+0x1C)

#define SIO_GPIO_OE_RW              (SIO_BASE+0x20)
#define SIO_GPIO_OE_SET             (SIO_BASE+0x24)
#define SIO_GPIO_OE_CLR             (SIO_BASE+0x28)
#define SIO_GPIO_OE_XOR             (SIO_BASE+0x2C)

#define IO_BANK0_BASE               0x40014000

#define IO_BANK0_GPIO25_STATUS_RW   (IO_BANK0_BASE+0x0C8+0x0000)
#define IO_BANK0_GPIO25_STATUS_XOR  (IO_BANK0_BASE+0x0C8+0x1000)
#define IO_BANK0_GPIO25_STATUS_SET  (IO_BANK0_BASE+0x0C8+0x2000)
#define IO_BANK0_GPIO25_STATUS_CLR  (IO_BANK0_BASE+0x0C8+0x3000)

#define IO_BANK0_GPIO25_CTRL_RW     (IO_BANK0_BASE+0x0CC+0x0000)
#define IO_BANK0_GPIO25_CTRL_XOR    (IO_BANK0_BASE+0x0CC+0x1000)
#define IO_BANK0_GPIO25_CTRL_SET    (IO_BANK0_BASE+0x0CC+0x2000)
#define IO_BANK0_GPIO25_CTRL_CLR    (IO_BANK0_BASE+0x0CC+0x3000) 

int mymain() {
       PUT32(RESETS_RESET_CLR,1<<5); //IO_BANK0
    //wait for reset to be done
    while(1)
    {
        if((GET32(RESETS_RESET_DONE_RW)&(1<<5))!=0) break;
    }

    /*
    gpio_reset();
    while(gpio_is_reset()) {};
    */
        //output disable
    PUT32(SIO_GPIO_OE_CLR,1<<25);
    //turn off pin 25
    PUT32(SIO_GPIO_OUT_CLR,1<<25);
    PUT32(IO_BANK0_GPIO25_CTRL_RW,5);
    //gpio_set_output();
    PUT32(SIO_GPIO_OE_SET,1<<25);
    while (1) {
        /*
        gpio_set_on(25);
        DELAY(0x1000000);
        gpio_set_off(25);
        DELAY(0x1000000);
        */
        //turn on the led
        PUT32(SIO_GPIO_OUT_SET,1<<25);
        DELAY(0x100000);
        //turn off the led
        PUT32(SIO_GPIO_OUT_CLR,1<<25);
        DELAY(0x100000);
    }
    return 0;

/*
        //release reset on IO_BANK0
    PUT32(RESETS_RESET_CLR,1<<5); //IO_BANK0
    //wait for reset to be done
    while(1)
    {
        if((GET32(RESETS_RESET_DONE_RW)&(1<<5))!=0) break;
    }

    //output disable
    PUT32(SIO_GPIO_OE_CLR,1<<25);
    //turn off pin 25
    PUT32(SIO_GPIO_OUT_CLR,1<<25);

    //set the function select to SIO (software controlled I/O)
    PUT32(IO_BANK0_GPIO25_CTRL_RW,5);

    //output enable
    PUT32(SIO_GPIO_OE_SET,1<<25);
    while(1)
    {
        //turn on the led
        PUT32(SIO_GPIO_OUT_SET,1<<25);
        DELAY(0x100000);
        //turn off the led
        PUT32(SIO_GPIO_OUT_CLR,1<<25);
        DELAY(0x100000);
    }
    return(0);
    */
}

void cstart() {
    extern uint32_t __bss_start__,__bss_end__;

    // Clear out all values in bss section
    uint32_t *bss_end = &__bss_end__;
    uint32_t *bss = &__bss_start__;
    while (bss < bss_end) {
        *bss++ = 0;
    }
    

    mymain();
}