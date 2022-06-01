NAME = bootloader
OBJS = $(NAME).o
LPI = ../

%.elf: $(OBJS) $(MEMMAP) $(DEPS)  $(LPI)
	$(CC) $(CFLAGS) $(START) $(OBJS) -T $(MEMMAP) -o $@   $(LPI)

%.list: %.elf
	$(OD) -D  $< > $@

%.bin: %.list
	$(OCP) $*.elf -O binary $*.bin

# to reduce the chance of error.
kernel.img: $(NAME).bin
	mv $(NAME).bin kernel.img

clean:
	rm -rf *.o *.bin *~ tags *.bin *.elf *.list *.img Makefile.bak 
	@make -s -C ./libpi.small clean

.PHONY: all clean  lib

# stop make from deleting these suffix'd files.
.PRECIOUS: %.list %.elf
