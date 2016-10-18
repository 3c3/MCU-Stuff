/*
 * _24c16.cpp
 *
 * Created: 22.8.2016 г. 15:06:36
 *  Author: Kosyo
 */ 

#include "Typedefs.h"
#include "24c16.h"
#include "uart.h"

bool ReadCurrentByte(ubyte* outByte)
{
	if(!TwiStart())
	{
		UsartSend("Failed start\r\n\0");
		return false;
	}

	TwiWrite(0xA1);
}

bool ReadByte(int addr, ubyte* outByte)
{
	if(!TwiStart())
	{
		UsartSend("Failed start\r\n\0");
		return false;
	}

	TwiWrite(EEPROM_ADDR << 1);
	if(lastTwiStatus != TW_MT_SLA_ACK) // write
	{
		UsartSend("Failed device addr\r\n\0");
		return false;
	}

	TwiWrite(addr & 0xFF);
	if(lastTwiStatus != TW_MT_DATA_ACK) // write
	{
		UsartSend("Failed device addr\r\n\0");
		return false;
	}

	TwiStop();	
	if(!TwiStart())
	{
		UsartSend("Failed second start\r\n\0");
		return false;
	}

	TwiWrite((EEPROM_ADDR << 1) | R);
	if(lastTwiStatus != TW_MR_SLA_ACK)
	{
		UsartSend("Failed slave addr\r\n\0");
		GetTwiState();
		return false;
	}

	//UsartSend("So far so good... \r\n\0");

	*outByte = TwiReadNack();
	return true;
}

bool WriteByte(int addr, ubyte val)
{
	if(!TwiStart())
	{
		UsartSend("Failed start\r\n\0");
		return false;
	}

	TwiWrite(EEPROM_ADDR << 1);
	if(lastTwiStatus != TW_MT_SLA_ACK) // write
	{
		UsartSend("Failed device addr\r\n\0");
		return false;
	}

	TwiWrite(addr & 0xFF);
	if(lastTwiStatus != TW_MT_DATA_ACK) // write
	{
		UsartSend("Failed data addr\r\n\0");
		return false;
	}

	TwiWrite(val);
	if(lastTwiStatus != TW_MT_DATA_ACK) // write
	{
		UsartSend("Failed data\r\n\0");
		return false;
	}

	TwiStop();

	return true;
}

void GetTwiState()
{
	UsartSend(lastTwiAction);
	UsartSend(" \0");
	UsartSend(lastTwiStatus);
	UsartNewLine();
}