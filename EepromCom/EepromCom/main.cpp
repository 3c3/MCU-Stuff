/*
 * EepromCom.cpp
 *
 * Created: 22.8.2016 г. 14:32:47
 * Author : Kosyo
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "twi.h"

#include "24c16.h"

int main(void)
{
	UsartInit();
	TwiInit();
    /* Replace with your application code */

	char dummy;

    while (!UsartRead(&dummy)) 
    {
		UsartSend("Press any key...\r\n\0");
    }
	bool result;

	/*
	UsartSend("Writing...\r\n\0");
	result = WriteByte(0x19, 0);
	UsartSend("Done writing! \0");
	if(result) UsartSend("OK\r\n\0");
	else UsartSend("failed\r\n\0");

	_delay_ms(100);
	*/

	ubyte recv;
	UsartSend("Reading...\r\n\0");
	result = ReadByte(0x19, &recv);
	UsartSend("Done\r\n\0");
	if(result)
	{
		UsartSend("Recv: \0");
		UsartSend(recv);
	}
	else
	{
		UsartSend("Failed.\0");
	}

	while(1);
}

