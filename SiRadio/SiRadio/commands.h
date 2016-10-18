/*
 * commands.h
 *
 * Created: 2.10.2016 г. 18:46:20
 *  Author: Kosyo
 */ 


#ifndef COMMANDS_H_
#define COMMANDS_H_

#define POWER_UP 0x02 // Power-up device and mode selection. Modes include operationa function.
#define NOP 0x00 // No operation command
#define PART_INFO 0x01 // Reports basic information about the device.
#define FUNC_INFO 0x10 // Returns the Function revision information of the device.
#define SET_PROPERTY 0x11 // Sets the value of a property.
#define GET_PROPERTY 0x12 // Retrieve a property's value.
#define GPIO_PIN_CFG 0x13 // Configures the GPIO pins.
#define GET_ADC_READING 0x14 // Retrieve the results of possible ADC conversions.
#define FIFO_INFO 0x15 // Provides access to transmit and receive fifo counts and reset.
#define PACKET_INFO 0x16 // Returns information about the last packet received and optionally overrides field length.
#define IRCAL 0x17 // Calibrate Image Rejection.
#define PROTOCOL_CFG 0x18 // Sets the chip up for specified protocol.
#define GET_INT_STATUS 0x20 // Returns the interrupt status byte.
#define GET_PH_STATUS 0x21 // Returns the packet handler status.
#define GET_MODEM_STATUS 0x22 // Returns the modem status byte.
#define GET_CHIP_STATUS 0x23 // Returns the chip status.
#define START_TX 0x31 // Switches to TX state and starts packet transmission.
#define START_RX 0x32 // Switches to RX state.
#define REQUEST_DEVICE_STATE 0x33 // Request current device state.
#define CHANGE_STATE 0x34 // Update state machine entries.
#define READ_CMD_BUFF 0x44 // Used to read CTS and the command response.
#define FRR_A_READ 0x50 // Reads the fast response registers starting with A.
#define FRR_B_READ 0x51 // Reads the fast response registers starting with B.
#define FRR_C_READ 0x53 // Reads the fast response registers starting with C.
#define FRR_D_READ 0x57 // Reads the fast response registers starting with D.
#define WRITE_TX_FIFO 0x66 // Writes the TX FIFO.
#define READ_RX_FIFO 0x77 // Reads the RX FIFO.
#define RX_HOP 0x36 // Fast RX to RX transitions for use in frequency hopping systems

#endif /* COMMANDS_H_ */