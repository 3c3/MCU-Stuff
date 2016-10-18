/*
 * SerialManager.h
 *
 * Created: 9.10.2016 г. 9:42:01
 *  Author: Kosyo
 */ 


#ifndef SERIALMANAGER_H_
#define SERIALMANAGER_H_

#include "uart.h"
#include "Si4463.h"

#define SERIAL_OUT_HEADER 0xFF
#define SERIAL_IN_HEADER 0xFF

#define MSG_INIT_FAILED 0x0
#define MSG_INIT_OK 0x1
#define MSG_PWR 0x2
#define MSG_PSENT 0x3
#define MSG_TX_FAIL 0x4
#define MSG_RESET 0x5
#define MSG_INT_ERROR 0x6

#define CMD_PAUSE 0x0
#define CMD_RESUME 0x1
#define CMD_PWR_CHANGE 0x2
#define CMD_GPS 0x3

class SerialManager
{
private:
	char outBuffer[2] = { SERIAL_OUT_HEADER, 0 };
	char cmdBuff[10];

	Si4463* radio;
	bool* shouldTx;
	int32 *lat, *lon;
	ubyte* pwrLevel;

	void ProcessCmd();

public:
	SerialManager(Si4463* _radio, ubyte* pwr, bool* _shouldTx, int32* _lat, int32* _lon);

	void Msg(char msg);
	void Msg(char msg, int extraData);
	void PwrChangedMsg();

	void CheckForCmd();
};

#endif /* SERIALMANAGER_H_ */