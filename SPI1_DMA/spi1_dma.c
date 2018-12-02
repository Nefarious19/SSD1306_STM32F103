/*
 * spi1_dma.c
 *
 *  Created on: 25.11.2018
 *      Author: rafal
 */

#include "stm32f1xx_hal.h"
#include "spi1_dma.h"

#include "../SPI/spi.h"

void (*dma_tcif3_callback)(void);

void SPI1_DMA_init(void)
{
	SPI_Deinit();

	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	NVIC_DisableIRQ(DMA1_Channel3_IRQn);
	NVIC_ClearPendingIRQ(DMA1_Channel3_IRQn);
	NVIC_SetPriority(DMA1_Channel3_IRQn, 0x00);
	NVIC_EnableIRQ(DMA1_Channel3_IRQn);

	SPI_Init();
}

void SPI1_DMA_trigger(uint32_t noOfBytesToSend, uint32_t sourceBufferAddress)
{
	DMA1_Channel3->CCR = DMA_CCR_PL_1 |
						 DMA_CCR_PL_0 |
						 DMA_CCR_MINC |
						 DMA_CCR_DIR  |
						 DMA_CCR_TCIE;

	DMA1_Channel3->CMAR = sourceBufferAddress;
	DMA1_Channel3->CPAR = (uint32_t)&SPI1->DR;
	DMA1_Channel3->CNDTR = noOfBytesToSend;
	DMA1_Channel3->CCR |= DMA_CCR_EN;
	SPI1->CR1 |= SPI_CR1_SPE;
	SPI1->CR2 |= SPI_CR2_TXDMAEN;
	SPI1_NSSLow();
}

void SPI1_DMA_triggerOff(void)
{
	while((SPI1->SR & SPI_SR_BSY));
	SPI1->CR2 &= ~SPI_CR2_TXDMAEN;
	DMA1_Channel3->CCR = 0;
}

void SPI1_registerDMA_TCIF3_callback (void(*callback)(void))
{
	if(callback != 0)
	{
		dma_tcif3_callback = callback;
	}
}

 __attribute__((interrupt)) void DMA1_Channel3_IRQHandler(void)
{
	 if((DMA1->ISR & DMA_ISR_TCIF3))
	 {
		 DMA1->IFCR |= DMA_IFCR_CTCIF3;
		 dma_tcif3_callback();
	 }
	 else
	 {
		 asm volatile("nop");
	 }
}

