/*
 * @file:   ssd1306_print.h
 * @author  Nefarious19
 * @brief:  This file contains API for printing data to the screen
 *
 */


#ifndef INC_SSD1306_PRINT_H_
#define INC_SSD1306_PRINT_H_

/* Defines listed below are only used to calculate proper line height and position
 *
 */
#define FONT_WIDTH 	5
#define FONT_HEIGHT	7

#define CHAR_WIDTH   (FONT_WIDTH + 2)
#define CHAR_HEIGHT  (FONT_HEIGHT + 3)

/* enum SSD_PRT_LineNo can be used as y parameter of printing
 * API.
 */

enum SSD_PRT_LineNo
{
	SSD_LINE1 = 0,
	SSD_LINE2 = CHAR_HEIGHT*1,
	SSD_LINE3 = CHAR_HEIGHT*2,
	SSD_LINE4 = CHAR_HEIGHT*3,
	SSD_LINE5 = CHAR_HEIGHT*4,
	SSD_LINE6 = CHAR_HEIGHT*5,
};


/*	Declaration of API that can be used for printing different
 *  types of data
 */
void SSD_PRT_putChr(char   data, uint8_t x, uint8_t y, uint8_t size );
void SSD_PRT_putStr(char * data, uint8_t x, uint8_t y, uint8_t size );
void SSD_PRT_putInt(int32_t num , uint8_t x, uint8_t y, uint8_t size );
void SSD_PRT_putHex(int32_t num , uint8_t x, uint8_t y, uint8_t size );
void SSD_PRT_putFloat( float num , uint8_t precision, uint8_t x, uint8_t y, uint8_t size );

#endif /* INC_SSD1306_PRINT_H_ */
