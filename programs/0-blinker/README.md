### Blinker: Setting up the Pico for hacking

Take a look at the [rp2040 datasheet](https://github.com/ESaracay/240lx_pico/blob/main/docs/rp2040-datasheet.pdf) to get a general lay of the land. Section 2.6 starting on pg 147 explains how memory is organized on the pico. Theres a lot moving piecies in this lab and getting from zero to blinking is the hardest step. Theres little room for error given that you don't have any tools for debugging. The uart section will help address this problem in the future.

***

### Plugging things in 

***

### 1. Understanding the Bootup Process
The general layout of memory straight from the 2040 datasheet
/insert image/
As explained in section 2.6.3 and 2.8 the pico's Bootrom (default bootloader) takes uf2 files and places them in either flash or ram. To have our programs persist after power downs we will placing our programs in flash via uf2. The steps for our boot sequence are outlined in the diagram below. There are a lot of important details here but the main one is that our second stage bootloader will copy over our program from flash to ram.   
![Untitled drawing](https://user-images.githubusercontent.com/33457643/171758450-6498283a-f550-4c82-b60c-4d5ca872fcdc.jpg)

After copying over out .uf2 file over the Bootrom will have placed our file contents in flash. Our Second Stage Bootloader is capped at a max size of 252 bytes. Our Second Stage Bootloader will do the following
1. Setup permissions for reading from flash as described on page 152. The code for this is described in start.S
2. We will copy over the contents of our main program to SRAM
3. We will have our stack point at position far away from our program
4. Finally jump to our main function which we have renamed to mymain so that our compiler does not complain about redefining main.

Note: All assembly is written in ARM Thumb v2. The Pico's CPU only runs thumb instructions which is why the Makefile contains the XCPU flag to make sure you don't write regular ARM instructions.
***
### Writing .uf2 Files
This isn't necessary given that the Raspberry Pi foundation provides a .elf to .uf2 converter [here](https://github.com/raspberrypi/pico-sdk/tree/master/tools/elf2uf2). Also feel free to use mine. However, if you want to get your hands dirty this can be a good experience. This file format was created by Mircosoft specifically for bootloaders. You can checkout their official [uf2 repo](https://github.com/microsoft/uf2). If you decide to write your own make sure to read section 2.8.4.2. I've included the image below because it will save you a lot of headaches. Note that you must only include one CRC for the first 252 bytes. This is specific to the pico's bootloader as other uf2 files will continue providing crc's for all blocks.
<insert image>
***
### GPIO Fun!
