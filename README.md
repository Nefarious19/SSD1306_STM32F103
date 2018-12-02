# SSD1306_STM32F103
 


### 1.Library for 1.3" SSD1306 OLED display. Developed on STM32F103C8T6 microcontroller. It can be easily ported on any other type of microcontroller. 

### 2. FIle structure description

|FOLDER: 	|FILES	|Description
----------------|-------|--------------------------------------------------------------------
|GPIO  		| pins.h | contains #defines with pin numbers (PA0 - 0, PA1 - 1 etc).
|               | gpio.h | header file with listed API for controling GPIOs
|               | gpio.c | source file that contains functions that can be used to control GPIOS
|SPI            | spi.h  |header file with listed very simple API for controling SPI1(only transmission in master mode)                             	


SPI		spi.h  - header file with listed very simple API for controling 
			SPI1(only transmission in master mode)
		spi.c  - source file that contains functions for SPI1 interface 						 				(transmission only (one data pin) in master mode.
----------------------------------------------------------------------------
SPI1_DMA	spi1_dma.c - file contains code for using DMA1 channel 3 for SPI 										     transimsion
		spi1_dma.h - listed API for DMA1 Ch3 SPI transmision mode.
----------------------------------------------------------------------------			
src		main.c - example of how to use OLED api
----------------------------------------------------------------------------
OLED		
|--icons icons.h - this file contains few 8x8pixels icons for OLED display	
|
|--inc  	ssd1306_font.h  - file contains 5x7px font
|			ssd1306_gfx.h	 - file contains API for drawing grpahics
|			ssd1306_print.h - file contains API for printing 
|			ssd1306_registers.h - file contains register names and offset
|			ssd1306.h	 - basic API for OLED menagment
|
|--src		ssd1306.c	 		- basic API for OLED menagment
		ssd1306_gfx.c	- file contains API for drawing grpahics		
		ssd1306_print.c - file contains API for printing 
		
### 3. How to use this library

As It was written, this library was developed on STM32F103C8T6 uC. Hardware configuration was as below:
	- 1.3" OLED display with SH1106 (similar to SSD1306) controller. Oled is configured in SPI mode.
	- STM32F103C8T6 configured as SPI master with only one data line (3 wire SPI)
	- DMA1 channel 3 is used for updating internal OLED GRAM data for every 100ms. That means that all
	graphics and printing stuff is done on internal uC RAM and then transferred to OLED display.

>NOTICE!
>
>Source code do not contains any of HAL functions. It's not fully functional project so it must be 
>tailored for your own purposes!

#### 3.1 Using library without DMA

If you want to use this library without DMA you must follow steps as below:

* Provide correct API for SPI transmission, you can replace API form spi.c with your own code

* Provide correct API for GPIO configuration, you can replace API form gpio.c with your own code

* Select what OLED driver you use in ssd1306.h file:


```c
//#define OLED_DRIVER_SYMBOL SSD1306
#define OLED_DRIVER_SYMBOL SH1106
```
	
* Include all needed files in your main.c file:

```c
#include "../SPI/spi.h"
#include "../OLED/inc/ssd1306.h"
#include "../OLED/inc/ssd1306_gfx.h"
#include "../OLED/inc/ssd1306_print.h"
#include "../OLED/icons/icons.h"
```
	
* Initialize SPI and OLED Display:


```c
int main(void)
{	
	SPI_Init();
	SSD_init();
	
	while(1);
}
```
	
* If everything is ok you should see your display filled with all pixels after compilation and 	uploading your code. 


* Now you can freely use all api from ssd1306_gfx.h and ssd1306_prt.h. To refresh your display 
  you can invoke function as below:
	
```c
int main(void)
{	
    SPI_Init();
    SSD_init();
    
    //example use of gfx API
    SSD_GFX_loadSmallBitmap(ant_8x8,8,8,0,0);
    SSD_GFX_loadSmallBitmap(sig_strenght_lvl4_8x8,8,8,8,0);

    while(1)
    {
        //some stuff
        if(timer100ms_flag == 1)
        {	
            //update OLED GRAM
	    SSD_updateBuffer(SSD_GFX_returnBufferPointer());
        }
    }
}
```

	
