/*
 * Si4463.h
 *
 * Created: 17.8.2016 г. 16:58:43
 *  Author: Kosyo
 */ 


#ifndef SI4463_H_
#define SI4463_H_

#include "RadioConfig.h"
#include "properties.h"
#include "commands.h"
#include "Interrupts.h"
#include "PacketField.h"
#include "CrcConfig.h"
#include "Typedefs.h"
#include "Spi.h"
#include "uart.h"
#include <util/delay.h>

//#define DETAILED_INT_PRINT

#define CTS_TIMEOUT 1600

#define CsnLow() *csnPort &= ~(1<<csnPin)
#define CsnHigh() *csnPort |= (1<<csnPin)
#define SdnLow() *sdnPort &= ~(1<<sdnPin)
#define SdnHigh() *sdnPort |= (1<<sdnPin)

enum RadioState { NoChange = 0, Sleep, SpiActive, Ready, Ready2, TxTune, RxTune, Tx, Rx };

struct IntStatus
{
	ubyte intPend, intStatus;
	ubyte phPend, phStatus;
	ubyte modemPend, modemStatus;
	ubyte chipPend, chipStatus;
};

struct FifoInfo
{
	ubyte rxFifoCount;
	ubyte txFifoSpace;
};

class Si4463
{
public:
	int failedCmd;

	Si4463(volatile ubyte *csn_port, ubyte csn_pin, volatile ubyte *sdn_port, ubyte sdn_pin);
	bool Init();

	bool SetProperty(int propId, ubyte nProps, ubyte* data);
	bool GetProperty(int propId, ubyte nProps, ubyte* recv);
	bool SetProperty(int propId, ubyte value);
	bool GetProperty(int propId, ubyte* value);

	bool GetPowerLevel(ubyte* lvl);
	bool SetPowerLevel(ubyte newLevel);

	bool ConfigurePacketField(ubyte packetNum, PacketField* packet);
	bool ConfigureRxPacketField(ubyte packetNum, PacketField* packet);

	bool GetIntStatus(ubyte clearPh, ubyte clearModem, ubyte clearChip, IntStatus* recv);
	bool GetFifoInfo(FifoInfo* fi);
	void ReadFrr(ubyte firstReg, ubyte count, ubyte* recv);
	ubyte ReadFrrA();
	ubyte ReadFrrB();
	ubyte ReadFrrC();
	ubyte ReadFrrD();
	
	bool ChangeState(ubyte newState);	

	bool StartTx(ubyte channel, ubyte condition, int txLen);
	void WriteTx(ubyte* buffer, ubyte len);

	bool StartRx(ubyte channel, ubyte condition, int rxLen, ubyte timeoutState, ubyte validState, ubyte invalidState);
	void ReadRx(ubyte* buffer, ubyte len);

	bool SendCmd(ubyte* cmdBuff, ubyte len);
	bool ReadResponse(ubyte* buff, ubyte len);

	void PrintIntStatus(IntStatus* status);

private:
	volatile ubyte *csnPort, *sdnPort;
	ubyte csnPin, sdnPin;

	void Reset();
	bool WaitForCts();	
};

#endif /* SI4463_H_ */