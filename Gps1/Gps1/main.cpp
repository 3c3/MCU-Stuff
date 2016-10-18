/*
 * Gps1.cpp
 *
 * Created: 26.7.2016 г. 17:34:08
 * Author : Kosyo
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"
#include "ToString.h"

char msgBuff[64];
int MakeMessage(long lat, long lon)
{
	char* ptr = msgBuff;
	ptr += ToString(msgBuff, lat);
	*ptr++ = ' ';
	ptr += ToString(ptr, lon);
	return (ptr-msgBuff);
}

int main(void)
{
	UsartInit();
    while (1) 
    {
		while(!gpsUpdated);

		gpsUpdated = false;

		long lon, lat;
		gps.get_position(&lat, &lon);
		int len = MakeMessage(lat, lon);
		UsartSendBlocking(msgBuff, len);
		UsartNewLine();
    }
}

