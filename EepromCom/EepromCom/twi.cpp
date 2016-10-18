#include "twi.h"

ubyte lastTwiAction;
ubyte lastTwiStatus;

void TwiInit()
{
	TWSR = 0;
	TWBR = 72; // 100 kHz при 8 МHz F_CPU

	DDRC &= ~((1<<5) | (1<<4));
	//PORTC |= (1<<5) | (1<<4);	// без pull-up

	TWCR = 1 << TWEN;
}

bool TwiStart()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	TwiWaitInt();
	lastTwiAction = TWI_ACTION_START;
	lastTwiStatus = TwiStatus();
	return (lastTwiStatus == TW_START) || (lastTwiStatus == TW_REP_START);
}

void TwiStop()
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void TwiWrite(ubyte data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	TwiWaitInt();
	lastTwiAction = TWI_ACTION_WRITE;
	lastTwiStatus = TwiStatus();
}

ubyte TwiReadAck()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	TwiWaitInt();
	lastTwiAction = TWI_ACTION_READ_ACK;
	lastTwiStatus = TwiStatus();
	return TWDR;
}

ubyte TwiReadNack()
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	TwiWaitInt();
	lastTwiAction = TWI_ACTION_READ_NACK;
	lastTwiStatus = TwiStatus();
	return TWDR;
}