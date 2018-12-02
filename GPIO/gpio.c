#include "gpio.h"

void GPIO_init(GPIO_TypeDef * gpio, GPIO_Mode_t gpioMode, uint8_t gpioNo, GPIO_State_t gpioState )
{
	uint8_t gpioModePosition = 0;
	volatile uint32_t * CRx_RegPtr = 0;

	if( gpioNo > 7 )
	{
		CRx_RegPtr = &(gpio->CRH);
		gpioNo -= 8;
	}
	else
	{
		CRx_RegPtr = &(gpio->CRL);
	}

	gpioModePosition = 4*gpioNo;

	*CRx_RegPtr &= ~(0x0F<<gpioModePosition);
	*CRx_RegPtr |=  (gpioMode<<gpioModePosition);

	if(gpioState)
	{
		gpio->ODR |=  (1<<gpioNo);
	}
	else
	{
		gpio->ODR &= ~(1<<gpioNo);
	}
}


void GPIO_setState(GPIO_TypeDef * gpio, uint8_t gpioNo, GPIO_State_t gpioState )
{
	if(gpioState)
	{
		gpio->ODR |=  (1<<gpioNo);
	}
	else
	{
		gpio->ODR &= ~(1<<gpioNo);
	}
}

GPIO_State_t GPIO_getState(GPIO_TypeDef * gpio, uint8_t gpioNo )
{
	GPIO_State_t return_val;
	return_val = (GPIO_State_t)(gpio->IDR & (1<<gpioNo));
	return return_val;
}

inline void GPIO_setHigh(GPIO_TypeDef * gpio, uint8_t gpioNo)
{
	gpio->BSRR = (1<<gpioNo);
}

inline void GPIO_setLow(GPIO_TypeDef * gpio, uint8_t gpioNo)
{
	gpio->BRR = (1<<gpioNo);
}

inline void GPIO_setToggle(GPIO_TypeDef * gpio, uint8_t gpioNo)
{
	gpio->ODR ^= (1<<gpioNo);
}
