/*
 * SerialManager.cpp
 *
 * Created: 9.10.2016 г. 9:54:30
 *  Author: Kosyo
 */ 

 #include "SerialManager.h"

 SerialManager::SerialManager(Si4463* _radio, ubyte* pwr, bool* _shouldTx, int32* _lat, int32* _lon)
 {
	radio = _radio;
	pwrLevel = pwr;
	shouldTx = _shouldTx;
	lat = _lat;
	lon = _lon;
 }

 void SerialManager::Msg(char msg)
 {
	outBuffer[1] = 1;
	UsartSend(outBuffer, 2);
	UsartSend(msg);
 }

 void SerialManager::Msg(char msg, int extraData)
 {
	outBuffer[1] = 3;
	UsartSend(outBuffer, 2);
	UsartSend(msg);
	UsartSend((char*)&extraData, 2);
 }

 void SerialManager::PwrChangedMsg()
 {
	radio->GetPowerLevel(pwrLevel);

	outBuffer[1] = 2;
	UsartSend(outBuffer, 2);
	UsartSend((char)MSG_PWR);
	UsartSend((char)*pwrLevel);
 }

 void SerialManager::CheckForCmd()
 {
	char c;
	while(UsartRead(&c)) // докато има
	{
		if(c != SERIAL_IN_HEADER) continue; // ignore

		while(!UsartRead(cmdBuff)); // дължина		

		if(cmdBuff[0] == 0) continue; // празна команда
		if(cmdBuff[0] > 9) continue; // overflow

		while(!UsartRead(cmdBuff + 1, cmdBuff[0])); // командата
		ProcessCmd();
	}
 }

 void SerialManager::ProcessCmd()
 {
	switch(cmdBuff[1])
	{
		case CMD_PAUSE:
			*shouldTx = false;
			break;
		case CMD_RESUME:
			*shouldTx = true;
			break;
		case CMD_PWR_CHANGE:
			if(cmdBuff[0] != 2) return; // грешен брой аргументи
			if(cmdBuff[2] & (1<<7)) return; // неправилна стойност
			radio->SetPowerLevel(cmdBuff[2]);
			PwrChangedMsg();
		case CMD_GPS:
			if(cmdBuff[0] != 9) return; // неправилен брой аргументи
			*lat = *((int32*)(cmdBuff+2));
			*lon = *((int32*)(cmdBuff+6));
			break;
	}
 }