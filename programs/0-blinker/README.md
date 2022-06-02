### Blinker: Setting up the Pico for hacking

Take a look at the [rp2040 datasheet](https://github.com/ESaracay/240lx_pico/blob/main/docs/rp2040-datasheet.pdf) to get a general lay of the land. Section 2.6 starting on pg 147 explains how memory is organized on the pico. Theres a lot moving piecies in this lab and getting from zero to blinking is the hardest step. Theres little room for error given that you don't have any tools for debugging. The uart section will help address this problem in the future.

***

### Plugging things in 

***

### 1. Understanding the Bootup Process
The general layout of memory straight from the 2040 datasheet
/insert image/
As explained in section 2.6.3 and 2.8 the pico's Bootrom (default bootloader) takes uf2 files and places them in either flash or ram. To have our programs persist after power downs we will placing our programs in flash via uf2. The steps for our boot sequence are outlined in the diagram below. There are a lot of important details here but the main one is that our second stage bootloader will copy over our program from flash to ram.   
![Untitled drawing](https://user-images.githubusercontent.com/33457643/171758366-2f94be35-190a-4621-b1f5-dff992fb90ba.jpg)
