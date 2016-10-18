/*
 * SerialManager.h
 *
 * Created: 8.10.2016 г. 20:35:38
 *  Author: Kosyo
 */ 


#ifndef SERIALMANAGER_H_
#define SERIALMANAGER_H_

#include "uart.h"
#include "Typedefs.h"

#define SERIAL_HEADER_BYTE_1 0xDE
#define SERIAL_HEADER_BYTE_0 0xAD

#define MSG_INIT_FAILED 0
#define MSG_OK 1
#define MSG_CRC_ERROR 2
#define MSG_PACKET_RX 3
#define MSG_GET_FIFO_ERR 4
#define MSG_GET_INT_ERROR 5

class SerialManager
{
private:
	ubyte basicBuff[4] = { SERIAL_HEADER_BYTE_1, SERIAL_HEADER_BYTE_0, 0, 0 };

public:
	void Msg(ubyte msg);
	void InitMsg(bool ok);
	void CrcMsg();
	void RxMsg(ubyte rssi, ubyte* payload, ubyte len);
};

#endif /* SERIALMANAGER_H_ */