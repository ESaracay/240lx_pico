#include "cstart.h"
@ exit into normal arm mode .arm
@ Enter thumb mode from a arm function .thumb_func
@ Assembler directives
@ https://sourceware.org/binutils/docs/as/ARM-Directives.html

.cpu cortex-m0

@ Used for linker to load this section
.section ".text.boot"

@ _start is automatically run first
.thumb
.globl _start
.thumb_func
@ Tell machine this is where code will start in RAM
_start:
   @ include constant in linker script
   ldr r0, =STACK_START
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