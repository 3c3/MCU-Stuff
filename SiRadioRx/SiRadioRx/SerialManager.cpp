/*
 * SerialManager.cpp
 *
 * Created: 8.10.2016 г. 20:39:57
 *  Author: Kosyo
 */ 

 #include "SerialManager.h"

 void SerialManager::Msg(ubyte msg)
 {
	basicBuff[2] = 1;
	basicBuff[3] = msg;
 }

 void SerialManager::InitMsg(bool ok)
 {
	basicBuff[2] = 1;
	basicBuff[3] = ok;
	UsartSend((char*)basicBuff, 4);
 }

 void SerialManager::CrcMsg()
 {
	basicBuff[2] = 1;
	basicBuff[3] = 2;
	UsartSend((char*)basicBuff, 4);
 }

 void SerialManager::RxMsg(ubyte rssi, ubyte* payload, ubyte len)
 {
	basicBuff[2] = len + 2;
	basicBuff[3] = 3;
	UsartSend((char*)basicBuff, 4);
	UsartSend((char)rssi);
	UsartSend((char*)payload, len);
 }