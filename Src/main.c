#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "../GPIO/gpio.h"


#include "../SPI/spi.h"
#include "../OLED/inc/ssd1306.h"
#include "../OLED/inc/ssd1306_gfx.h"
#include "../OLED/inc/ssd1306_print.h"
#include "../OLED/icons/icons.h"
#include "../SPI1_DMA/spi1_dma.h"

volatile uint32_t timer = 0;

void HAL_SYSTICK_Callback(void)
{
	if(timer) timer--;
}

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  //enable GPIOS clocks
  MX_GPIO_Init();

  GPIO_init(GPIOB, GPIO_MODE_DIGITAL_OUT_PP_50MHZ, PB12, GPIO_HIGH);

  SPI_Init();
  SSD_init();

  SSD_GFX_loadSmallBitmap(ant_8x8,8,8,0,0);
  SSD_GFX_loadSmallBitmap(sig_strenght_lvl4_8x8,8,8,8,0);
  SSD_GFX_loadSmallBitmap(bat_lvl3_8x8,8,8,20,0);
  SSD_GFX_loadSmallBitmap(wifi_lvl_3_8x8,8,8,32,0);
  SSD_GFX_loadSmallBitmap(message_8x8,8,8,44,0);
  SSD_GFX_loadSmallBitmap(arrow_right_8x8,8,8,56,0);
  SSD_GFX_loadSmallBitmap(bluetooth_8x8,8,8,68,0);
  SSD_GFX_loadSmallBitmap(settings_8x8,8,8,80,0);

  SSD_PRT_putStr("OLED STM32F1xxx",0,SSD_LINE2,1);
  SSD_PRT_putStr("Liczba int: ",0,SSD_LINE3,1);
  SSD_PRT_putInt(1000,11*CHAR_WIDTH,SSD_LINE3,1);
  SSD_PRT_putStr("Licz. float: ",0,SSD_LINE4,1);
  SSD_PRT_putFloat(11.230,3,12*CHAR_WIDTH,SSD_LINE4,1);
  SSD_PRT_putStr("Liczba HEX: ",0,SSD_LINE5,1);
  SSD_PRT_putHex(0xAAFF,12*CHAR_WIDTH,SSD_LINE5,1);

  SPI1_DMA_init();

  while (1)
  {
	  if(!timer)
	  {
		  static uint8_t state = 0;
		  state ^= 1;
		  timer = 100;
		  if(state)
		  {
			  GPIO_setHigh(GPIOB,PB12);
		  }
		  else
		  {
			  GPIO_setLow(GPIOB,PB12);
		  }
		  SSD_DMA_trigger();
	  }
  }
}


