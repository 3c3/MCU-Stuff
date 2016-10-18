/*
 * Packet.h
 *
 * Created: 7.10.2016 г. 22:49:20
 *  Author: Kosyo
 */ 


#ifndef PACKET_H_
#define PACKET_H_

#include "Typedefs.h"

class PacketField
{
public:
	ubyte data[4];

	void SetLength(int len);
	void SetConfig(bool manch, bool whiten, bool pnStart, bool qfsk);
	void SetCrcConfig(bool crcEnable, bool checkCrc, bool sendCrc, bool crcStart);
};

#endif /* PACKET_H_ */