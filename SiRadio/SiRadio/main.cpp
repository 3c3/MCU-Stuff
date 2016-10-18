/*
 * SiRadio.cpp
 *
 * 15.8.2016 21:12 - INIT WORKS!
 * 1.10.2016 - Init работи (наистина) и праща пакет
 * 1.10.2016 - успешен обмен на съобщения
 * 
 * Created: 15.8.2016 г. 20:18:41
 * Author : Kosyo
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "Si4463.h"
#include "SerialManager.h"

ubyte msg[11];
bool shouldTx = true;
Si4463 radio(&PORTB, 1, &PORTB, 2);
SerialManager serMan(&radio, msg, &shouldTx, (int32*)(msg+3), (int32*)(msg+7));


IntStatus its;
volatile bool pSent = true;

void CheckInterrupts()
{
	if(radio.GetIntStatus(0,0,0,&its))
	{
		if(its.phPend & 32)
		{
			serMan.Msg(MSG_PSENT);
		}
	} else serMan.Msg(MSG_INT_ERROR);
}

ISR(INT0_vect)
{
	//UsartSend("got int!\r\n\0");
	CheckInterrupts();
}

void EnableExtInterrupt()
{
	// INT0, falling edge
	DDRD &= ~(1<<2);
	EICRA = 2;
	EIMSK = 1;
}

void IncrementMsg(char* msg)
{
	char* current = msg+6;

	while(true)
	{
		(*current)++;
		if(*current < 255) break;

		*current = 0;
		current--;
	}
}

int main(void)
{
	DDRB |= (1<<1) | (1<<2);
	PORTB |= 1<<1;

	UsartInit();

	char c;
	while(!UsartRead(&c));
    bool result = radio.Init();
	
	if(result) serMan.Msg(MSG_INIT_OK);
	else
	{
	   serMan.Msg(MSG_INIT_FAILED);
	   while(1);
	}

	EnableExtInterrupt();

	radio.SetPowerLevel(1);
	
	radio.SetProperty(PKT_CRC_CONFIG, CRC_32_IEEE);

	PacketField packet1;
	packet1.SetConfig(false, false, false, false);
	packet1.SetCrcConfig(true, true, true, true);
	packet1.SetLength(11);

	radio.SetProperty(PKT_FIELD_1_LENGTH_12_8, 4, packet1.data);

	
	msg[0] = 1; // power level

	int* pkgCount = (int*)(msg+1);
	*pkgCount = 0;

	while (1) 
    {
		serMan.CheckForCmd();
		
		if(!(PORTD & (1<<2))) CheckInterrupts(); // изпуснат interrupt?

		if(shouldTx)
		{
			radio.WriteTx(msg, 11);
			(*pkgCount)++;

			if(!radio.StartTx(0, Ready<<4, 0))
			{
				serMan.Msg(MSG_TX_FAIL);
				break;
			}
			_delay_ms(50);
		}
		
    }

	while(1) serMan.Msg(MSG_RESET);
}

