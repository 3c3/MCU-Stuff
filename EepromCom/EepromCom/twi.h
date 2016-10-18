/*
 * twi.h
 * Basics, basically
 * Created: 28.7.2016 г. 12:20:58
 *  Author: Kosyo
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>
#include <util/twi.h>
#include "Typedefs.h"

#define TwiWaitInt() while (!(TWCR & (1<<TWINT)))
#define TwiStatus() TWSR & 0xF8

#define TWI_ACTION_START 0
#define TWI_ACTION_WRITE 1
#define TWI_ACTION_READ_ACK 2
#define TWI_ACTION_READ_NACK 3

#define W 0
#define R 1

extern ubyte lastTwiAction;
extern ubyte lastTwiStatus;

void TwiInit();
bool TwiStart();
void TwiStop();
void TwiWrite(ubyte data);
ubyte TwiReadAck();
ubyte TwiReadNack();

#endif /* TWI_H_ */