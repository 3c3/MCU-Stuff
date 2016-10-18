/*
 * TwiUtils.h
 *
 * Created: 29.7.2016 г. 0:13:02
 *  Author: Kosyo
 */ 


#ifndef TWIUTILS_H_
#define TWIUTILS_H_

#include "twi.h"
#include "uart.h"

bool TwiWriteTo(ubyte addr, ubyte* buff, ubyte len);
bool TwiWriteToReg(ubyte addr, ubyte regAddr, ubyte* buff, ubyte len);
bool TwiWriteToReg(ubyte addr, ubyte regAddr, ubyte val);
bool TwiSelectReg(ubyte addr, ubyte regAddr);
bool TwiReadFrom(ubyte addr, ubyte* recvBuff, ubyte len);
bool TwiReadFromReg(ubyte addr, ubyte regAddr, ubyte* recvBuff, ubyte len);
void TwiReportState();

#endif /* TWIUTILS_H_ */