#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f1xx_hal.h"

#include "pins.h"


typedef enum
{
	GPIO_MODE_ANALOG_INPUT 					= 0b0000,
	GPIO_MODE_DIGITAL_INPUT_FLOATING 		= 0b0100,
	GPIO_MODE_DIGITAL_INPUT_PULL_UP_DOWN 	= 0b1000,
	GPIO_MODE_DIGITAL_OUT_PP_10MHZ 			= 0b0001,
	GPIO_MODE_DIGITAL_OUT_PP_2MHZ 			= 0b0010,
	GPIO_MODE_DIGITAL_OUT_PP_50MHZ 			= 0b0011,
	GPIO_MODE_DIGITAL_OUT_OD_10MHZ 			= 0b0101,
	GPIO_MODE_DIGITAL_OUT_OD_2MHZ 			= 0b0110,
	GPIO_MODE_DIGITAL_OUT_OD_50MHZ 			= 0b0111,
	GPIO_MODE_DIGITAL_AF_PP_OUT_10MHZ       = 0b1001,
	GPIO_MODE_DIGITAL_AF_PP_OUT_2MHZ 		= 0b1010,
	GPIO_MODE_DIGITAL_AF_PP_OUT_50MHZ		= 0b1011,
	GPIO_MODE_DIGITAL_AF_OD_OUT_10MHZ       = 0b1101,
	GPIO_MODE_DIGITAL_AF_OD_OUT_2MHZ 		= 0b1110,
	GPIO_MODE_DIGITAL_AF_OD_OUT_50MHZ		= 0b1111,
}GPIO_Mode_t;

typedef enum
{
	GPIO_LOW,
	GPIO_HIGH,
}GPIO_State_t;


void GPIO_init(GPIO_TypeDef * gpio, GPIO_Mode_t gpioMode, uint8_t gpioNo, GPIO_State_t gpioState);
void GPIO_setState(GPIO_TypeDef * gpio, uint8_t gpioNo, GPIO_State_t gpioState);
GPIO_State_t GPIO_getState(GPIO_TypeDef * gpio, uint8_t gpioNo);
extern void GPIO_setHigh(GPIO_TypeDef * gpio, uint8_t gpioNo);
extern void GPIO_setLow(GPIO_TypeDef * gpio, uint8_t gpioNo);
extern void GPIO_setToggle(GPIO_TypeDef * gpio, uint8_t gpioNo);


#endif /* GPIO_H_ */
