.program ws2812
; Assume we have a clock speed of 125mhz so a nano second is .125 of a tick
; a single cycle is about 8 nanoseconds
; currently each bit will write for 5 cycles = 40 nanoseconds
set pindirs, 1
loop:
    ;set pins, 1  We always end before a pull with line pulled high
	pull
	out x, 1
	jmp !x do_zero
do_one:
    set pins, 1 [6]
    set pins, 0 [2]
    jmp loop
do_zero:
    set pins, 0 [9]
    jmp loop
