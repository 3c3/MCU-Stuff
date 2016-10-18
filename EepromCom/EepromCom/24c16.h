/*
 * _24c16.h
 *
 * Created: 22.8.2016 г. 15:02:06
 *  Author: Kosyo
 */ 


#ifndef H24C16_H_
#define H24C16_H_

#include "Typedefs.h"
#include "twi.h"
#include "TwiUtils.h"

#define EEPROM_ADDR 0x50

bool ReadCurrentByte(ubyte* outByte);
bool ReadByte(int addr, ubyte* outByte);
bool WriteByte(int addr, ubyte val);

void GetTwiState();

#endif /* 24C16_H_ */