# SSD1306_STM32F103
 


### 1.Library for 1.3" SSD1306 OLED display. Developed on STM32F103C8T6 microcontroller. It can be easily ported on any other type of microcontroller. 

### 2. FIle structure description
```
	FOLDER: 	FILES
	----------------------------------------------------------------------------
	GPIO  		pins.h - contains #defines with pin numbers (PA0 - 0, PA1 - 1 etc).
	       		gpio.h - header file with listed API for controling GPIOs
	        	gpio.c - source file that contains functions that can be used to 							control GPIOS
	----------------------------------------------------------------------------        	
	SPI			spi.h  - header file with listed very simple API for controling 							SPI1(only transmission in master mode)
				spi.c  - source file that contains functions for SPI1 interface 						 							(transmission only (one data pin) in master mode.
	----------------------------------------------------------------------------
	SPI1_DMA	spi1_dma.c - file contains code for using DMA1 channel 3 for SPI 								transimsion
				spi1_dma.h - listed API for DMA1 Ch3 SPI transmision mode.
	----------------------------------------------------------------------------			
	src			main.c - example of how to use OLED api
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
```
	