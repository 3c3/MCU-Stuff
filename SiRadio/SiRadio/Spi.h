/*
 * Spi.h
 *
 * Created: 30.7.2016 г. 16:23:24
 *  Author: Kosyo
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "Typedefs.h"

#define MOSI_PIN 3
#define SCK_PIN 5

#define SPI_DIV_4 0
#define SPI_DIV_16 1
#define SPI_DIV_64 2
#define SPI_DIV_128 3

void SpiMasterInit();
ubyte SpiExchange(ubyte value);

#endif /* SPI_H_ */