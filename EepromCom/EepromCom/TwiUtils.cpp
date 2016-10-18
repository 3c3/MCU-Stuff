#include "TwiUtils.h"

bool TwiWriteTo(ubyte addr, ubyte* buff, ubyte len)
{
	if(!TwiStart()) return false;

	TwiWrite(addr << 1); // ADDR + W
	if(lastTwiStatus != TW_MT_SLA_ACK) return false;

	for(int i = 0; i < len; i++)
	{
		TwiWrite(buff[i]);
		if(lastTwiStatus != TW_MT_DATA_ACK) return false;
	}

	TwiStop();
	return true;
}

bool TwiWriteToReg(ubyte addr, ubyte regAddr, ubyte* buff, ubyte len)
{
	if(!TwiStart()) return false;

	TwiWrite(addr << 1); // ADDR + W
	if(lastTwiStatus != TW_MT_SLA_ACK) return false;

	TwiWrite(regAddr);
	if(lastTwiStatus != TW_MT_DATA_ACK) return false;

	for(int i = 0; i < len; i++)
	{
		TwiWrite(buff[i]);
		if(lastTwiStatus != TW_MT_DATA_ACK) return false;
	}

	TwiStop();
	return true;
}

bool TwiWriteToReg(ubyte addr, ubyte regAddr, ubyte val)
{
	if(!TwiStart()) return false;

	TwiWrite(addr << 1); // ADDR + W
	if(lastTwiStatus != TW_MT_SLA_ACK) return false;

	TwiWrite(regAddr);
	if(lastTwiStatus != TW_MT_DATA_ACK) return false;

	TwiWrite(val);
	if(lastTwiStatus != TW_MT_DATA_ACK) return false;

	TwiStop();
	return true;
}

bool TwiSelectReg(ubyte addr, ubyte regAddr)
{
	if(!TwiStart()) return false;

	TwiWrite(addr << 1); // ADDR + W
	if(lastTwiStatus != TW_MT_SLA_ACK) return false;

	TwiWrite(regAddr);
	if(lastTwiStatus != TW_MT_DATA_ACK) return false;

	TwiStop();
	return true;
}

bool TwiReadFrom(ubyte addr, ubyte* recvBuff, ubyte len)
{
	if(!TwiStart()) return false;

	TwiWrite((addr << 1) | R);
	if(lastTwiStatus != TW_MR_SLA_ACK) return false;

	int lim = len-1;
	for(int i = 0; i < lim; i++)
	{
		recvBuff[i] = TwiReadAck();
		// TODO: проверка за провал
	}
	recvBuff[len-1] = TwiReadNack();

	TwiStop();
	return true;
}

bool TwiReadFromReg(ubyte addr, ubyte regAddr, ubyte* recvBuff, ubyte len)
{
	if(!TwiSelectReg(addr, regAddr)) return false;

	return TwiReadFrom(addr, recvBuff, len);
}

#ifdef UART_H_

void TwiReportState()
{
	UsartSend(lastTwiAction);
	UsartSend(" \0");
	UsartSend(lastTwiStatus);
}

#endif