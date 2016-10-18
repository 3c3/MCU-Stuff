/*
 * Spi.cpp
 *
 * Created: 12.8.2016 г. 11:30:34
 *  Author: Kosyo
 */ 

 #include "Spi.h"

 void SpiMasterInit()
 {
	 DDRB |= (1<<MOSI_PIN) | (1<<SCK_PIN);
	 SPCR |= (1<<SPE) | (1<<MSTR) | SPI_DIV_4;
 }

 ubyte SpiExchange(ubyte value)
 {
	 SPDR = value;
	 while(!(SPSR & (1<<SPIF)));
	 return SPDR;
 }