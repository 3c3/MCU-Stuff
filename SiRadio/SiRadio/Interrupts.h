/*
 * Interrupts.h
 *
 * Created: 8.10.2016 г. 9:01:52
 *  Author: Kosyo
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#define PH_INT_RX_ALMOST_FULL 1
#define PH_INT_TX_ALMOST_EMPTY (1<<1)
#define PH_INT_CRC_ERROR (1<<3)
#define PH_INT_PACKET_RX (1<<4)
#define PH_INT_PACKET_TX (1<<5)
#define PH_INT_FILTER_MISS (1<<6)
#define PH_INT_FILTER_MATCH (1<<7)

#define PH_INT_RX_ACTION_MASK (PH_INT_PACKET_RX | PH_INT_CRC_ERROR)

#define MODEM_INT_SYNC_DETECT 1
#define MODEM_INT_PREAMBLE_DETECT (1<<1)
#define MODEM_INT_INVALID_PREAMBLE (1<<2)
#define MODEM_INT_RSSI (1<<3)
#define MODEM_INT_RSSI_JUMP (1<<4)
#define MODEM_INT_INVALID_SYNC (1<<5)

#define CHIP_INT_WUT 1
#define CHIP_INT_LOW_BATT (1<<1)
#define CHIP_INT_READY (1<<2)
#define CHIP_INT_CMD_ERROR (1<<3)
#define CHIP_INT_STATE_CHANGE (1<<4)
#define CHIP_INT_FIFO_UNDERFLOW_OVERFLOW_ERROR (1<<5)
#define CHIP_INT_CAL (1<<6)


#endif /* INTERRUPTS_H_ */