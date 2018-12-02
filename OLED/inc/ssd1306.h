/*
 * @file    ssd1306.h
 * @brief   This file contains API for BASIC funcionalities.
 * @author  Nefarious19
 */

#ifndef SSD1306_H_
#define SSD1306_H_

#include <stdint.h>
#include "../../GPIO/gpio.h"
/*
 * define which driver you use
 */

//#define OLED_DRIVER_SYMBOL SSD1306
#define OLED_DRIVER_SYMBOL SH1106

/*
 * some ports definitions
 */
#define SSDPORT GPIOA
//#define SSD_RST GPIO_PIN_2
//#define SSD_DC  GPIO_PIN_1

#define SSD_RST PA2
#define SSD_DC  PA1
/*
 * display size
 */
#define SSD_WIDTH    0x80   //128 px
#define SSD_HEIGHT	 0x40   //64 px

/*
 * BASIC API for using the display.
 */
void SSD_init(void);
void SSD_clrScreen(uint8_t pattern);
void SSD_updateBuffer(uint8_t * buffer);
void SSD_setContrast(uint8_t contrastLVL);
void SSD_setActiveLine( uint8_t activeLineNo );

/*
 * THIS API can only be used when DMA is properly set.
 *
 */
void SSD_DMA_trigger(void);
void SSD_DMA_Callback(void);

#endif /* SSD1306_H_ */
