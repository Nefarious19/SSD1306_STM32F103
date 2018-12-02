/*
 * @file:   spi.c
 * @author  Nefarious19
 * @brief:  This file contains simple API for
 *          SPI1 peripheral. SPI is configured as master and in
 *          transmit only mode.
 *
 */
#include "stm32f1xx_hal.h"
#include "spi.h"

void SPI_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //Enable GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; //Enable SPI1

	GPIO_init(SPI1_PORT, GPIO_MODE_DIGITAL_AF_PP_OUT_50MHZ, SCK1_PIN, GPIO_LOW);
	GPIO_init(SPI1_PORT, GPIO_MODE_DIGITAL_AF_PP_OUT_50MHZ, MOSI1_PIN, GPIO_LOW);
	GPIO_init(SPI1_PORT, GPIO_MODE_DIGITAL_INPUT_FLOATING, MISO1_PIN, GPIO_LOW);
	GPIO_init(SPI1_PORT, GPIO_MODE_DIGITAL_OUT_PP_50MHZ, NSS1_PIN, GPIO_LOW);

	SPI1->CR1 = SPI_CR1_BIDIMODE |	//Only one line of data
				SPI_CR1_BIDIOE   |  //Enable Transmission only
				SPI_CR1_SSM      |  //NSS software management
				SPI_CR1_SSI      |  //Set internal SSI
				SPI_CR1_MSTR     |  //SPI in MASTER mode
				SPI_CR1_BR_0     |  //Prescaler == 2, SCK = 36MHZ / 2 = 18MHz
				SPI_CR1_SPE;        //Enable SPI
}

void SPI_Deinit(void)
{
	//Reset all registers
	GPIO_init(SPI1_PORT, GPIO_MODE_DIGITAL_INPUT_FLOATING, SCK1_PIN, GPIO_LOW);
	GPIO_init(SPI1_PORT, GPIO_MODE_DIGITAL_INPUT_FLOATING, MOSI1_PIN, GPIO_LOW);
	GPIO_init(SPI1_PORT, GPIO_MODE_DIGITAL_INPUT_FLOATING, MISO1_PIN, GPIO_LOW);
	GPIO_init(SPI1_PORT, GPIO_MODE_DIGITAL_INPUT_FLOATING, NSS1_PIN, GPIO_LOW);
	SPI1->CR1 = 0;
	SPI1->CR2 = 0;
	SPI1->SR = 0;
	RCC->APB2ENR &= ~RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
}


void SPI_writeData(uint8_t data)
{
	while(!(SPI1->SR & SPI_SR_TXE)); //wait until tx is empty again
	SPI1->DR = data;                 //put data into TX data register
}



