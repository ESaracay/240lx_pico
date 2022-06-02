# Disable automatic rules 
BUILD := ./build
MAKEFLAGS += --no-builtin-rules
BUILD_DIR = ./build/
ASM_SRCS := start.S
C_SRCS := cstart.c gpio.c
DEPS := cstart.h gpio.h
OBJS := $(patsubst %.S,$(BUILD_DIR)%.o,$(ASM_SRCS))
OBJS += $(patsubst %.c,$(BUILD_DIR)%.o,$(C_SRCS))

XCPU = -mcpu=cortex-m0
CFLAGS := -g -mthumb -Wall -nostdlib -nostartfiles -ffreestanding $(XCPU)
ASMFLAGS := -g -mthumb -Wall -nostdlib -nostartfiles -ffreestanding $(XCPU) 
# https://manpages.debian.org/testing/binutils-arm-none-eabi/arm-none-eabi-ld.1.en.html#nostdlib
# Ensures we only use files we explicitly want
LFLAGS := -nostdlib -nostartfiles 
ARMGNU := arm-none-eabi

.PHONY: all
all: mymain

# Make sure to keep track of .h files
include $(wildcard $(BUILD_DIR)*.d)

$(BUILD_DIR)%.o: %.c 
	mkdir -p $(BUILD_DIR)
	$(ARMGNU)-gcc $(CFLAGS) -c $^ -o $@ 
	$(ARMGNU)-gcc $(CFLAGS) -MM $^ > $@.d

$(BUILD_DIR)%.o: %.S
	mkdir -p $(BUILD_DIR)
	$(ARMGNU)-gcc $(ASMFLAGS) -c $^ -o $@
	$(ARMGNU)-gcc $(ASMFLAGS) -MM  $^ > $@.d

# -T means we will entirely replace linker script
$(BUILD_DIR)mymain.bin: $(OBJS)
	$(ARMGNU)-ld $(LFLAGS) -T memmap $^ -o $(BUILD_DIR)mymain.elf
	$(ARMGNU)-objdump -D $(BUILD_DIR)mymain.elf > $(BUILD_DIR)mymain.list
	$(ARMGNU)-objcopy -O binary $(BUILD_DIR)mymain.elf $@

$(BUILD_DIR)uf2conv: uf2conv.c
	gcc -O2 $^ -o $@

mymain: $(BUILD_DIR)mymain.bin $(BUILD_DIR)uf2conv
	cd $(BUILD_DIR);./uf2conv mymain.bin ../firmware.uf2

$(BUILD_DIR)makeuf2: makeuf2.c
	gcc -O2 $^ -o $@

#mymain: $(BUILD_DIR)mymain.bin $(BUILD_DIR)makeuf2
#cd $(BUILD_DIR); ./makeuf2 mymain.bin ../actual.uf2

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f firmware.uf2