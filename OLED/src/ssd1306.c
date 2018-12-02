#include "stm32f1xx_hal.h"
#include "../SPI/spi.h"
#include "../../SPI1_DMA/spi1_dma.h"


#include "../inc/ssd1306.h"
#include "../inc/ssd1306_registers.h"
#include "../inc/ssd1306_gfx.h"

#define CMD_MODE GPIO_setLow(SSDPORT,SSD_DC)
#define DAT_MODE GPIO_setHigh(SSDPORT,SSD_DC)

#define delay(x) { for(uint32_t i = 0; i < x; i++) asm volatile("nop"); }

#if OLED_DRIVER_SYMBOL == SH1106
	#define SSD_setColumnStartAddres() {					\
											SSD_wrCMD(0x02);\
											SSD_wrCMD(0x10);\
										}
#else
	#define SSD_setColumnStartAddres() {					\
											SSD_wrCMD(0x00);\
											SSD_wrCMD(0x10);\
										}
#endif

void SSD_Reset(void);
void SSD_wrCMD(uint8_t CMD);
void SSD_wrDAT(uint8_t DATA);

void SSD_init(void)
{

	GPIO_init(SSDPORT, GPIO_MODE_DIGITAL_OUT_PP_50MHZ, SSD_DC, GPIO_HIGH);
	GPIO_init(SSDPORT, GPIO_MODE_DIGITAL_OUT_PP_50MHZ, SSD_RST, GPIO_HIGH);

	SSD_Reset();

	SSD_wrCMD(SSD1306_DISPLAYOFF);
	SSD_wrCMD(SSD1306_SETDISPLAYCLOCKDIV);
	SSD_wrCMD(0x80);
	SSD_wrCMD(SSD1306_SETMULTIPLEX);
	SSD_wrCMD(0x3F);
	SSD_wrCMD(SSD1306_SETDISPLAYOFFSET);
	SSD_wrCMD(0x00);
	SSD_wrCMD(SSD1306_SETSTARTLINE | 0x00);
	SSD_wrCMD(SSD1306_CHARGEPUMP);
	SSD_wrCMD(0x14);
	SSD_wrCMD(SSD1306_MEMORYMODE);
	SSD_wrCMD(0x02);
	SSD_wrCMD(SSD1306_SEGREMAP | 0x1);

	SSD_wrCMD(SSD1306_COMSCANDEC);

	SSD_wrCMD(SSD1306_SETCOMPINS);
	SSD_wrCMD(0x12);

	// Max contrast
	SSD_wrCMD(SSD1306_SETCONTRAST);
	SSD_wrCMD(0xFF);

	SSD_wrCMD(SSD1306_SETPRECHARGE);
	SSD_wrCMD(0xF1);

	SSD_wrCMD(SSD1306_SETVCOMDETECT);
	SSD_wrCMD(0x40);

	SSD_wrCMD(SSD1306_DISPLAYALLON_RESUME);

	// Non-inverted display
	SSD_wrCMD(SSD1306_NORMALDISPLAY);

	// Turn display back on
	SSD_wrCMD(SSD1306_DISPLAYON);

	SSD_clrScreen(0xFF);

	SPI1_registerDMA_TCIF3_callback(SSD_DMA_Callback);
}

void SSD_Reset(void)
{
	GPIO_setLow(SSDPORT,SSD_RST);
	delay(100);
	GPIO_setHigh(SSDPORT,SSD_RST);
	delay(100);
}


void SSD_wrCMD(uint8_t CMD)
{
	SPI1_NSSLow();
	CMD_MODE;
	SPI_writeData(CMD);
	SPI1_NSSHig();
}

void SSD_wrDAT(uint8_t DATA)
{
	SPI1_NSSLow();
	DAT_MODE;
	SPI_writeData(DATA);
	SPI1_NSSHig();
}

void SSD_clrScreen(uint8_t pattern)
{
	for(uint8_t j = 0; j < 8; j++)
	{
		SSD_wrCMD( 0xB0 | j );
		SSD_setColumnStartAddres();

		DAT_MODE;
		SPI1_NSSLow();
		for(uint8_t i = 0; i < 128; i++)
		{
			SPI_writeData(pattern);
		}
		SPI1_NSSHig();
	}
}

void SSD_updateBuffer(uint8_t * buffer)
{
	for(uint8_t j = 0; j < 8; j++)
	{
		SSD_wrCMD( 0xB0 | j );
		SSD_setColumnStartAddres();

		DAT_MODE;
		SPI1_NSSLow();
		for(uint8_t i = 0; i < 128; i++)
		{
			SPI_writeData(*buffer++);
		}
		SPI1_NSSHig();
	}
}

void SSD_setContrast(uint8_t contrastLVL)
{
	// set contrast
	SSD_wrCMD(SSD1306_SETCONTRAST);
	SSD_wrCMD(contrastLVL);
}

void SSD_setActiveLine( uint8_t activeLineNo )
{
	SSD_wrCMD( 0xB0 | activeLineNo );
	SSD_setColumnStartAddres();
	DAT_MODE;
}

void SSD_DMA_trigger(void)
{
	SSD_setActiveLine(0);
	SPI1_DMA_trigger(0x80,(uint32_t)(SSD_GFX_returnBufferPointer()));
}

void SSD_DMA_Callback(void)
{
	static uint32_t ssd_line_number = 0;
	ssd_line_number++;
	if(ssd_line_number < 8)
	{
		SPI1_DMA_triggerOff();
		SPI1_NSSHig();
		SSD_setActiveLine(ssd_line_number);
		SPI1_DMA_trigger(128, (uint32_t)(SSD_GFX_returnBufferPointer() + ssd_line_number*128));
		SPI1_NSSLow();
	}
	else
	{
		SPI1_DMA_triggerOff();
		SPI1_NSSHig();
		ssd_line_number = 0;
	}
}

