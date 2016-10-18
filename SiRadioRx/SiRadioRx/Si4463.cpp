/*
 * Si4463.cpp
 *
 * Created: 17.8.2016 г. 19:04:28
 *  Author: Kosyo
 */ 

#include "Si4463.h"

ubyte cfgTable[] = RADIO_CONFIGURATION_DATA_ARRAY;

Si4463::Si4463(volatile ubyte *csn_port, ubyte csn_pin, volatile ubyte *sdn_port, ubyte sdn_pin)
{
	csnPort = csn_port;
	csnPin = csn_pin;
	sdnPort = sdn_port;
	sdnPin = sdn_pin;
}

void Si4463::Reset()
{
	SdnHigh();
	_delay_us(50);
	SdnLow();
	CsnHigh();
}

bool Si4463::WaitForCts()
{
	int time = CTS_TIMEOUT;
	ubyte retVal = 0;
	while(retVal != 0xFF && time > 0)
	{
		//UsartSend(time); UsartSend(" \0");
		CsnLow();
		SpiExchange(READ_CMD_BUFF);
		retVal = SpiExchange(0xFF);
		CsnHigh();
		time--;
	}
	//UsartNewLine();
	return retVal == 0xFF;
}

bool Si4463::SendCmd(ubyte* cmdBuff, ubyte len)
{
	if(!WaitForCts()) return false;
	CsnLow();
	while(len--) SpiExchange(*cmdBuff++);
	CsnHigh();
	return true;
}

bool Si4463::Init()
{
	SpiMasterInit();
	Reset();
	_delay_ms(10);

	ubyte len;
	int idx = 0;

	int cmdId = 0;

	while((len = cfgTable[idx]) != 0)
	{
		idx++;
		//UsartSend("cmd...\0");
		if(!SendCmd(cfgTable + idx, len))
		{
			//UsartSend("failed init \r\n\0");
			failedCmd = cmdId;
			return false;
		}
		if(cmdId == 0) _delay_ms(10);
		//UsartSend(cmdId); UsartNewLine();
		cmdId++;
		idx += len;
	}

	return true;
}

bool Si4463::SetProperty(int propId, ubyte nProps, ubyte* data)
{
	ubyte cmdBuff[16] = { SET_PROPERTY, (ubyte)(propId >> 8), nProps, (ubyte)(propId & 0xFF) };
	int idx = 4;
	while(nProps--) cmdBuff[idx++] = *data++;
	return SendCmd(cmdBuff, idx);
}

bool Si4463::GetProperty(int propId, ubyte nProps, ubyte* recv)
{
	ubyte cmdBuff[4] = { GET_PROPERTY, (ubyte)(propId >> 8), nProps, (ubyte)(propId & 0xFF) };
	if(!SendCmd(cmdBuff, 4)) return false;
	return ReadResponse(recv, nProps);
}

bool Si4463::ReadResponse(ubyte* buff, ubyte len)
{
	int time = CTS_TIMEOUT;
	ubyte val;
	bool ok = false;
	while(time)
	{
		CsnLow();
		SpiExchange(READ_CMD_BUFF);
		val = SpiExchange(0xFF); // read CTS
		if(val != 0xFF)
		{
			CsnHigh();
			time--;
		}
		else
		{
			while(len--) *buff++ = SpiExchange(0xFF);
			CsnHigh();
			ok = true;
			break;
		}
	}

	return ok;
}

bool Si4463::GetIntStatus(ubyte clearPh, ubyte clearModem, ubyte clearChip, IntStatus* recv)
{
	ubyte cmdBuff[] = { GET_INT_STATUS, clearPh, clearModem, clearChip };
	if(!SendCmd(cmdBuff, 4)) return false;
	return ReadResponse((ubyte*)recv, 8);
}

void Si4463::PrintIntStatus(IntStatus* status)
{
	#ifdef DETAILED_INT_PRINT
		UsartSend("Pending:\r\n\0");
		
		UsartSend("INT: \0");
		if(status->intPend & 4) UsartSend("CHIP_INT_STATUS \0");
		if(status->intPend & 2) UsartSend("MODEM_INT_STATUS \0");
		if(status->intPend & 1) UsartSend("PH_INT_STATUS \0");
		UsartNewLine();

		UsartSend("PH: \0");
		if(status->phPend & 128) UsartSend("FILTER_MATCH \0");
		if(status->phPend & 64) UsartSend("FILTER_MISS \0");
		if(status->phPend & 32) UsartSend("PACKET_SENT \0");
		if(status->phPend & 16) UsartSend("PACKET_RX \0");
		if(status->phPend & 8) UsartSend("CRC_ERROR \0");
		if(status->phPend & 2) UsartSend("TX_ALMOST_EMPTY \0");
		if(status->phPend & 1) UsartSend("RX_ALMOST_FULL \0");
		UsartNewLine();

		UsartSend("MODEM: \0");
		if(status->modemPend & 32) UsartSend("INVALID_SYNC \0");
		if(status->modemPend & 16) UsartSend("RSSI_JUMP \0");
		if(status->modemPend & 8) UsartSend("RSSI \0");
		if(status->modemPend & 4) UsartSend("INVALID_PREAMBLE \0");
		if(status->modemPend & 2) UsartSend("PREAMBLE_DETECT \0");
		if(status->modemPend & 1) UsartSend("SYNC_DETECT \0");
		UsartNewLine();

		UsartSend("CHIP: \0");
		if(status->chipPend & 0xC0) UsartSend("CAL \0");
		if(status->chipPend & 32) UsartSend("FIFO_FLOW_ERROR \0");
		if(status->chipPend & 16) UsartSend("STATE_CHANGE \0");
		if(status->chipPend & 8) UsartSend("CMD_ERROR \0");
		if(status->chipPend & 4) UsartSend("CHIP_RDY \0");
		if(status->chipPend & 2) UsartSend("LOW_BATT \0");
		if(status->chipPend & 1) UsartSend("WUT \0");
		UsartNewLine();

		UsartSend("Status: \r\n\0");

		UsartSend("INT: \0");
		if(status->intStatus & 4) UsartSend("CHIP_INT_STATUS \0");
		if(status->intStatus & 2) UsartSend("MODEM_INT_STATUS \0");
		if(status->intStatus & 1) UsartSend("PH_INT_STATUS \0");
		UsartNewLine();

		UsartSend("PH: \0");
		if(status->phStatus & 128) UsartSend("FILTER_MATCH \0");
		if(status->phStatus & 64) UsartSend("FILTER_MISS \0");
		if(status->phStatus & 32) UsartSend("PACKET_SENT \0");
		if(status->phStatus & 16) UsartSend("PACKET_RX \0");
		if(status->phStatus & 8) UsartSend("CRC_ERROR \0");
		if(status->phStatus & 2) UsartSend("TX_ALMOST_EMPTY \0");
		if(status->phStatus & 1) UsartSend("RX_ALMOST_FULL \0");
		UsartNewLine();

		UsartSend("MODEM: \0");
		if(status->modemStatus & 32) UsartSend("INVALID_SYNC \0");
		if(status->modemStatus & 16) UsartSend("RSSI_JUMP \0");
		if(status->modemStatus & 8) UsartSend("RSSI \0");
		if(status->modemStatus & 4) UsartSend("INVALID_PREAMBLE \0");
		if(status->modemStatus & 2) UsartSend("PREAMBLE_DETECT \0");
		if(status->modemStatus & 1) UsartSend("SYNC_DETECT \0");
		UsartNewLine();

		UsartSend("CHIP: \0");
		if(status->chipStatus & 0xC0) UsartSend("CAL \0");
		if(status->chipStatus & 32) UsartSend("FIFO_FLOW_ERROR \0");
		if(status->chipStatus & 16) UsartSend("STATE_CHANGE \0");
		if(status->chipStatus & 8) UsartSend("CMD_ERROR \0");
		if(status->chipStatus & 4) UsartSend("CHIP_RDY \0");
		if(status->chipStatus & 2) UsartSend("LOW_BATT \0");
		if(status->chipStatus & 1) UsartSend("WUT \0");
		UsartNewLine();
	#else
		
		ubyte* val = (ubyte*)status;

		for(int i = 0; i < 8; i++)
		{ 
			UsartSend((int)*val++);
			if(i&1) UsartNewLine();
			else UsartSend('\t');
		}

	#endif
}

bool Si4463::ChangeState(ubyte newState)
{
	ubyte cmdBuff[] = { CHANGE_STATE, newState };
	return SendCmd(cmdBuff, 2);
}

bool Si4463::GetPowerLevel(ubyte* lvl)
{
	return GetProperty(PA_PWR_LVL, lvl);
}

bool Si4463::SetPowerLevel(ubyte newLevel)
{
	return SetProperty(PA_PWR_LVL, newLevel);
}

bool Si4463::GetFifoInfo(FifoInfo* fi)
{
	ubyte cmdBuff[] = { FIFO_INFO, 0 };
	if(!SendCmd(cmdBuff, 2)) return false;
	return ReadResponse((ubyte*)fi, 2);
}

bool Si4463::StartTx(ubyte channel, ubyte condition, int txLen)
{
	ubyte cmdBuff[] = { START_TX, channel, condition, (ubyte)(txLen >> 8), (ubyte)(txLen & 0xFF) };
	return SendCmd(cmdBuff, 5);
}

void Si4463::WriteTx(ubyte* buffer, ubyte len)
{
	CsnLow();
	SpiExchange(WRITE_TX_FIFO);
	while(len--) SpiExchange(*buffer++);
	CsnHigh();
}

bool Si4463::StartRx(ubyte channel, ubyte condition, int rxLen, ubyte timeoutState, ubyte validState, ubyte invalidState)
{
	ubyte cmdBuff[] = { START_RX, channel, condition, (ubyte)(rxLen >> 8), (ubyte)(rxLen & 0xFF), timeoutState, validState, invalidState };
	return SendCmd(cmdBuff, 8);
}

void Si4463::ReadRx(ubyte* buffer, ubyte len)
{
	CsnLow();
	SpiExchange(READ_RX_FIFO);
	while(len--) *buffer++ = SpiExchange(0xFF);
	CsnHigh();
}

void Si4463::ReadFrr(ubyte firstReg, ubyte count, ubyte* recv)
{
	if(count < 0 || count > 3) return;
	ubyte cmd = -1;
	switch(firstReg)
	{
		case 0: // A
			cmd = 0x50;
			break;
		case 1: // B
			cmd = 0x51;
			break;
		case 2: // C
			cmd = 0x53;
			break;
		case 3: // D
			cmd = 0x57;
			break;
	}

	if(cmd != -1)
	{
		CsnLow();
		SpiExchange(cmd);
		while(count--) *recv++ = SpiExchange(0xFF);
		CsnHigh();
	}
}

ubyte Si4463::ReadFrrA()
{
	CsnLow();
	SpiExchange(FRR_A_READ);
	ubyte retVal = SpiExchange(0xFF);
	CsnHigh();
	return retVal;
}

ubyte Si4463::ReadFrrB()
{
	CsnLow();
	SpiExchange(FRR_B_READ);
	ubyte retVal = SpiExchange(0xFF);
	CsnHigh();
	return retVal;
}

ubyte Si4463::ReadFrrC()
{
	CsnLow();
	SpiExchange(FRR_C_READ);
	ubyte retVal = SpiExchange(0xFF);
	CsnHigh();
	return retVal;
}

ubyte Si4463::ReadFrrD()
{
	CsnLow();
	SpiExchange(FRR_D_READ);
	ubyte retVal = SpiExchange(0xFF);
	CsnHigh();
	return retVal;
}

bool Si4463::GetProperty(int propId, ubyte* value)
{
	ubyte cmdBuff[4] = { GET_PROPERTY, (ubyte)(propId >> 8), 1, (ubyte)(propId & 0xFF) };
	if(!SendCmd(cmdBuff, 4)) return false;
	return ReadResponse(value, 1);
}

bool Si4463::SetProperty(int propId, ubyte value)
{
	ubyte cmdBuff[5] = { SET_PROPERTY, (ubyte)(propId >> 8), 1, (ubyte)(propId & 0xFF), value };
	return SendCmd(cmdBuff, 5);
}

bool Si4463::ConfigurePacketField(ubyte packetNum, PacketField* packet)
{
	switch(packetNum)
	{
		case 1:
			return SetProperty(PKT_FIELD_1_LENGTH_12_8, 4, packet->data);
			break;
		case 2:
			return SetProperty(PKT_FIELD_2_LENGTH_12_8, 4, packet->data);
			break;
		case 3:
			return SetProperty(PKT_FIELD_3_LENGTH_12_8, 4, packet->data);
			break;
		case 4:
			return SetProperty(PKT_FIELD_4_LENGTH_12_8, 4, packet->data);
			break;
		case 5:
			return SetProperty(PKT_FIELD_5_LENGTH_12_8, 4, packet->data);
			break;
		default:
			return false;
			break;
	}
}

bool Si4463::ConfigureRxPacketField(ubyte packetNum, PacketField* packet)
{
		switch(packetNum)
		{
			case 1:
				return SetProperty(PKT_RX_FIELD_1_LENGTH_12_8, 4, packet->data);
				break;
			case 2:
				return SetProperty(PKT_RX_FIELD_2_LENGTH_12_8, 4, packet->data);
				break;
			case 3:
				return SetProperty(PKT_RX_FIELD_3_LENGTH_12_8, 4, packet->data);
				break;
			case 4:
				return SetProperty(PKT_RX_FIELD_4_LENGTH_12_8, 4, packet->data);
				break;
			case 5:
				return SetProperty(PKT_RX_FIELD_5_LENGTH_12_8, 4, packet->data);
				break;
			default:
				return false;
				break;
		}
}