/*
 * spi1_dma.h
 *
 *  Created on: 25.11.2018
 *      Author: rafal
 */

#ifndef SPI1_DMA_H_
#define SPI1_DMA_H_

void SPI1_DMA_init(void);
void SPI1_DMA_trigger(uint32_t noOfBytesToSend, uint32_t sourceBufferAddress);
void SPI1_DMA_triggerOff(void);
void SPI1_registerDMA_TCIF3_callback (void(*callback)(void));
#endif /* SPI1_DMA_H_ */
