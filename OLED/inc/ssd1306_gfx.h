/*
 * @file:   ssd1306_gfx.h
 * @author  Nefarious19
 * @brief:  This file contains API for drawing graphics
 *
 */


#ifndef SSD1306_GFX_H_
#define SSD1306_GFX_H_

typedef enum 
{
	BLACK,
	WHITE
}SSD_GFX_color_t;

/*
 * 	 This function returns pointer to the internal graphics buffer
 */
uint8_t * SSD_GFX_returnBufferPointer (void);


void SSD_GFX_putPixel(uint8_t x, uint8_t y);
void SSD_GFX_drawLine(uint8_t x_0, uint8_t y_0, uint8_t x_1, uint8_t y_1, SSD_GFX_color_t color );
void SSD_GFX_drawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, SSD_GFX_color_t color);
void SSD_GFX_drawFilledRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, SSD_GFX_color_t color);
void SSD_GFX_drawFilledSquare(uint8_t x, uint8_t y, uint8_t a, SSD_GFX_color_t color);
void SSD_GFX_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius, SSD_GFX_color_t color);
void SSD_GFX_drawFilledCircle(uint8_t x0, uint8_t y0, uint8_t radius, SSD_GFX_color_t color);
void SSD_GFX_drawArc(uint8_t x0, uint8_t y0, uint8_t r, uint8_t one_eight, SSD_GFX_color_t color );
void SSD_GFX_drawRoundedRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t corner_radius, SSD_GFX_color_t color);
void SSD_GFX_loadBitmapFromFlash(const uint8_t * otr);
void SSD_GFX_loadSmallBitmap(const uint8_t *picture, uint8_t height, uint8_t width, uint8_t pos_x, uint8_t pos_y);


#endif /* SSD1306_GFX_H_ */
