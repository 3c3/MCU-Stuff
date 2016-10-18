/*
 * uart.h
 *
 * Created: 10.7.2016 г. 16:37:52
 *  Author: Kosyo
 */ 


#ifndef UART_H_
#define UART_H_

#ifndef BAUD
#warning "Baud rate not set, default 9600"
#define BAUD 9600 
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>
#include "Typedefs.h"

void UsartInit();
void UsartSend(char data);
void UsartSend(char* data, int len);
void UsartSend(char* szData);
void UsartSend(int num);
void UsartSend(long num);
void UsartSend(unsigned int unum);
void UsartSend(unsigned long unum);

// да е кратно на 2
#define RX_BUFFER_SIZE 64

ISR(USART_RX_vect);

bool UsartRead(char* c);
bool UsartRead(char* buff, int len);
void UsartNewLine();
#endif /* UART_H_ */