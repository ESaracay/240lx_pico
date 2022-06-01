# Disable automatic rules 
HEADERS := ./include/
C_FILES := ./src/
MAKEFLAGS += --no-builtin-rules
BUILD_DIR = ./build/
ASM_SRCS := start.S
C_SRCS := cstart.c gpio.c clock.c sw-uart.c printf.c uart.c
DEPS := $(HEADERS)cstart.h $(HEADERS)gpio.h $(HEADERS)clock.h $(HEADERS)sw-uart.h $(HEADERS)printf.h $(HEADERS)uart.h $(HEADERS)integer-math.h
OBJS := $(patsubst %.S,$(BUILD_DIR)%.o,$(ASM_SRCS))
OBJS += $(patsubst %.c,$(BUILD_DIR)%.o,$(C_SRCS))

XCPU = -mcpu=cortex-m0
CFLAGS := -g -mthumb -Wall -nostdlib -nostartfiles -ffreestanding $(XCPU) -Iinclude
ASMFLAGS := -g -mthumb -Wall -nostdlib -nostartfiles -ffreestanding $(XCPU) 
# https://manpages.debian.org/testing/binutils-arm-none-eabi/arm-none-eabi-ld.1.en.html#nostdlib
# Ensures we only use files we explicitly want
LFLAGS := -nostdlib -nostartfiles
ARMGNU := arm-none-eabi

.PHONY: all
all: mymain

# Make sure to keep track of .h files
include $(wildcard $(BUILD_DIR)*.d)

$(BUILD_DIR)%.o: $(C_FILES)%.c 
	mkdir -p $(BUILD_DIR)
	$(ARMGNU)-gcc $(CFLAGS)  -c $^ -o $@ 
	$(ARMGNU)-gcc $(CFLAGS) -MM $^ > $@.d

$(BUILD_DIR)%.o: %.S
	mkdir -p $(BUILD_DIR)
	$(ARMGNU)-gcc $(ASMFLAGS) -c $^ -o $@
	$(ARMGNU)-gcc $(ASMFLAGS) -MM  $^ > $@.d

# -T means we will entirely replace linker script
mymain: $(OBJS)
	$(ARMGNU)-ar -c -D -r rasplib.a $^ 
	echo 'libpi done building'

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f rasplib.a