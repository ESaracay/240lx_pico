#include "cstart.h"
@ exit into normal arm mode .arm
@ Enter thumb mode from a arm function .thumb_func
@ Assembler directives
@ https://sourceware.org/binutils/docs/as/ARM-Directives.html

.cpu cortex-m0

@ Used for linker to load this section
.section ".text.boot"
.thumb

    ldr r0,=0x18000008
    ldr r1,=0x00000000
    str r1,[r0]

    ldr r0,=0x18000014
    ldr r1,=0x00000008
    str r1,[r0]

    ldr r0,=0x18000000
    ldr r1,=0x001F0300
    str r1,[r0]

    ldr r0,=0x180000F4
    ldr r1,=0x03000218
    str r1,[r0]

    ldr r0,=0x18000004
    ldr r0,=0x00000000
    str r1, [r0]

    ldr r0,=0x18000008
    ldr r1,=0x00000001
    str r1,[r0]

    ldr r0,=0x10000000
    ldr r1,=0x20000000
    ldr r2,=0x400

copy_loop:
    ldr r3,[r0]
    str r3,[r1]
    add r0,#0x4
    add r1,#0x4
    sub r2,#1
    bne copy_loop

    ldr r0,=0x20000101
    bx r0

@.thumb_func
@_bootstart:
    @ldr r0, =0x10000000
    @@ldr r1, =0x10001000
    @ldr r1, =0x1000
    @ldr r2, =0x20000000
    @_boot_start_loop:
    @ldr r3, [r0]
    @str r3, [r2]
    @add r0, #0x4
    @add r2, #0x4
    @sub r2, #1
    @@cmp r0, r1
    @@bne _boot_start_loop
    @bne _boot_start_loop
    @@ Start at postion in ram after second stage boot which is 256 bytes
    @ldr r0, =0x20001100
    @bx r0

.section ".text.start"
@ _start is automatically run first
.globl _start
@ Tell machine this is where code will start in RAM
.thumb_func
_start:
   @ include constant in linker script
   ldr r0, = 0x20005000
   mov sp, r0
   bl cstart
   b .

.thumb_func
.globl PUT32
PUT32:
    str r1, [r0]
    bx lr

.thumb_func 
.globl GET32
GET32:
    ldr r0, [r0]
    bx lr

.globl DELAY
.thumb_func
DELAY:
    sub r0,#1
    bne DELAY
    bx lr