/*
 * uart.h
 *
 * Created: 10.7.2016 г. 16:37:52
 *  Author: Kosyo
 */ 


#ifndef UART_H_
#define UART_H_

#include "Typedefs.h"
#include "TinyGps.h"

#define BAUD 9600 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

void UsartInit()
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	#if USE_2X
	UCSR0A |= (1 << U2X0);
	#else
	UCSR0A &= ~(1 << U2X0);
	#endif
	UCSR0B|= (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);

	sei();
}

void UsartSendBlocking(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void UsartSendBlocking(char* data, int len)
{
	while(len--)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *data++;
	}
}

TinyGPS gps;
volatile bool gpsUpdated = false;

ISR(USART_RX_vect)
{	
	if(gps.encode(UDR0)) gpsUpdated = true;
}

void UsartNewLine()
{
	UsartSendBlocking('\r');
	UsartSendBlocking('\n');
}

#endif