/*
 * SiRadio.cpp
 *
 * 15.8.2016 21:12 - INIT WORKS!
 * 1.10.2016 - Init работи (наистина) и праща пакет
 *
 * Created: 15.8.2016 г. 20:18:41
 * Author : Kosyo
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "Si4463.h"
#include "PacketField.h"
#include "CrcConfig.h"
#include "SerialManager.h"

Si4463 radio(&PORTB, 1, &PORTB, 2);
SerialManager serMan;

IntStatus its;
ubyte rxFifoBuff[64];

ISR(INT0_vect)
{
	bool rxDone = false;
	if(radio.GetIntStatus(0,0,0,&its))
	{
		ubyte rssi = 0;
		if(its.phPend & PH_INT_RX_ACTION_MASK)
		{
			rssi = radio.ReadFrrA(); // RSSI
			rxDone = true;
		}

		if(its.phPend & PH_INT_PACKET_RX)
		{
			FifoInfo fi;
			radio.GetFifoInfo(&fi);
			if(fi.rxFifoCount > 0)
			{
				radio.ReadRx(rxFifoBuff, fi.rxFifoCount);
				serMan.RxMsg(rssi, rxFifoBuff, fi.rxFifoCount);
			}
		}
		
		if(its.phPend & PH_INT_CRC_ERROR)
		{
			serMan.CrcMsg();
		}

		if(rxDone) radio.StartRx(0, 0, 0, 0, 3, 8);
	} else serMan.Msg(MSG_GET_INT_ERROR);
}

void EnableExtInterrupt()
{
	// INT0, falling edge
	DDRD &= ~(1<<2);
	EICRA = 2;
	EIMSK = 1;
}

int main(void)
{
	DDRB |= (1<<1) | (1<<2);
	PORTB |= 1<<1;

	UsartInit();

	char c;
	while(!UsartRead(&c));
    bool result = radio.Init();
	
	serMan.InitMsg(result);
	if(!result) while(1);

	EnableExtInterrupt();

	radio.SetProperty(PKT_CRC_CONFIG, CRC_32_IEEE); // CRC polynomial config

	PacketField packet1;
	packet1.SetConfig(false, false, false, false);
	packet1.SetCrcConfig(true, true, true, true);
	packet1.SetLength(11);

	radio.SetProperty(PKT_FIELD_1_LENGTH_12_8, 4, packet1.data);

	radio.SetProperty(MODEM_RSSI_CONTROL, 1); // RSSI
	radio.SetProperty(FRR_CTL_A_MODE, 10); // FRR A = latched RSSI

	radio.StartRx(0, 0, 0, 0, 3, 8);

	while (1);
}

