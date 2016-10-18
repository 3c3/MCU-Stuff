/*
 * uart.cpp
 *
 * Created: 15.8.2016 г. 16:39:28
 *  Author: Kosyo
 */ 

#include "uart.h"

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

void UsartSend(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void UsartSend(char* data, int len)
{
	while(len--)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *data++;
	}
}

void UsartSend(char* szData)
{
	while(*szData)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *szData++;
	}
}

void UsartSend(int num)
{
	char buff[5];
	if(num < 0)
	{
		num=-num;
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = '-';
	}

	char* ptr = buff;

	do 
	{
		*ptr++ = num%10 + '0';
		num/=10;
	} while (num);

	ptr--;

	while(ptr >= buff)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *ptr--;
	}
}

void UsartSend(long num)
{
	char buff[10];
	if(num < 0)
	{
		num=-num;
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = '-';
	}

	char* ptr = buff;

	do
	{
		*ptr++ = num%10 + '0';
		num/=10;
	} while (num);

	ptr--;

	while(ptr >= buff)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *ptr--;
	}
}

void UsartSend(unsigned int unum)
{
	char buff[5];
	char* ptr = buff;

	do
	{
		*ptr++ = unum%10 + '0';
		unum/=10;
	} while (unum);

	ptr--;

	while(ptr >= buff)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *ptr--;
	}
}

void UsartSend(unsigned long unum)
{
	char buff[10];
	char* ptr = buff;

	do
	{
		*ptr++ = unum%10 + '0';
		unum/=10;
	} while (unum);

	ptr--;

	while(ptr >= buff)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *ptr--;
	}
}

volatile char rxBuff[RX_BUFFER_SIZE];
volatile char rxStart, rxEnd, rxLen;

#define UsartAvailable rxLen

ISR(USART_RX_vect)
{
	rxBuff[rxEnd++] = UDR0;
	rxEnd &= RX_BUFFER_SIZE - 1;
	if(rxEnd == rxStart) rxStart++;
	if(!(rxLen & RX_BUFFER_SIZE)) rxLen++;
}

bool UsartRead(char* c)
{
	if(rxLen > 0)
	{
		rxLen--;

		*c = rxBuff[rxStart++];
		rxStart &= RX_BUFFER_SIZE - 1;

		return true;
	} else return false;
}

bool UsartRead(char* buff, int len)
{
	if(len > rxLen) return false;
	
	cli();
	
	rxLen -= len;

	while(len--)
	{
		*buff++ = rxBuff[rxStart++];
		rxStart &= RX_BUFFER_SIZE - 1;
	}

	sei();

	return true;
}

void UsartNewLine()
{
	UsartSend('\r');
	UsartSend('\n');
}