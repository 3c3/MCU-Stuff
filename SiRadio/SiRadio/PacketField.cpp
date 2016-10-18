/*
 * Packet.cpp
 *
 * Created: 7.10.2016 г. 22:57:29
 *  Author: Kosyo
 */ 

 #include "PacketField.h"

 void PacketField::SetLength(int len)
 {
	data[0] = len >> 8;
	data[1] = len & 0xFF;
 }

 void PacketField::SetConfig(bool manch, bool whiten, bool pnStart, bool qfsk)
 {
	data[2] = (manch) | (whiten<<1) | (pnStart<<2) | (qfsk<<4);
 }

 void PacketField::SetCrcConfig(bool crcEnable, bool checkCrc, bool sendCrc, bool crcStart)
 {
	data[3] = (crcEnable<<1) | (checkCrc<<3) | (sendCrc<<5) | (crcStart<<7);
 }