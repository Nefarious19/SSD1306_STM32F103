/*
 * @file:   spi.h
 * @author  Nefarious19
 * @brief:  This file contains simple API for
 *          SPI1 peripheral. SPI is configured as master and in
 *          transmit only mode.
 *
 */

#ifndef SPI_H_
#define SPI_H_

#include "../GPIO/gpio.h"

#define SPI1_PORT  GPIOA

#define NSS1_PIN   PA4
#define SCK1_PIN   PA5
#define MISO1_PIN  PA6
#define MOSI1_PIN  PA7


#define SPI1_NSSLow() {                            		   \
						GPIO_setLow(SPI1_PORT, NSS1_PIN);  \
					  }

#define SPI1_NSSHig() {  								    \
						 while((SPI1->SR & SPI_SR_BSY));    \
						 GPIO_setHigh(SPI1_PORT, NSS1_PIN); \
					  }
void SPI_Init(void);
void SPI_Deinit(void);
void SPI_writeData(uint8_t data);

#endif /* SPI_H_ */
