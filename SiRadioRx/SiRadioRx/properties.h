/*
 * properties.h
 *
 * Created: 2.10.2016 г. 18:39:18
 *  Author: Kosyo
 */ 


#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#define GLOBAL_XO_TUNE 0x0000 // Default: 0x40; Configure crystal oscillator frequency tuning bank
#define GLOBAL_CLK_CFG 0x0001 // Default: 0; Clock configuration options
#define GLOBAL_LOW_BATT_THRESH 0x0002 // Default: 0x18; Low battery threshold
#define GLOBAL_CONFIG 0x0003 // Default: 0; Global configuration settings
#define GLOBAL_WUT_CONFIG 0x0004 // Default: 0x00; GLOBAL WUT configuation
#define GLOBAL_WUT_M_15_8 0x0005 // Default: 0x00; Configure WUT_M_15_8
#define GLOBAL_WUT_M_7_0 0x0006 // Default: 0x01; Configure WUT_M_7_0
#define GLOBAL_WUT_R 0x0007 // Default: 0x00; Configure WUT_R
#define GLOBAL_WUT_LDC 0x0008 // Default: 0x00; Configure WUT_LDC
#define INT_CTL_ENABLE 0x0100 // Default: 0x04; Interrupt enable property
#define INT_CTL_PH_ENABLE 0x0101 // Default: 0x00; Packet handler interrupt enable property
#define INT_CTL_MODEM_ENABLE 0x0102 // Default: 0x00; Modem interrupt enable property
#define INT_CTL_CHIP_ENABLE 0x0103 // Default: 0x04; Chip interrupt enable property
#define FRR_CTL_A_MODE 0x0200 // Default: 0x01; Fast Response Register A Configuration
#define FRR_CTL_B_MODE 0x0201 // Default: 0x02; Fast Response Register B Configuration
#define FRR_CTL_C_MODE 0x0202 // Default: 0x09; Fast Response Register C Configuration
#define FRR_CTL_D_MODE 0x0203 // Default: 0x00; Fast Response Register D Configuration
#define PREAMBLE_TX_LENGTH 0x1000 // Default: 0x08; Preamble length
#define PREAMBLE_CONFIG_STD_1 0x1001 // Default: 0x14; Standard preamble configuration
#define PREAMBLE_CONFIG_NSTD 0x1002 // Default: 0x00; Non-standard preamble configuation
#define PREAMBLE_CONFIG_STD_2 0x1003 // Default: 0x0F; Standard preamble configuration
#define PREAMBLE_CONFIG 0x1004 // Default: 0x21; Preamble configuration bits
#define PREAMBLE_PATTERN_31_24 0x1005 // Default: 0; Preamble pattern
#define PREAMBLE_PATTERN_23_16 0x1006 // Default: 0; Preamble pattern
#define PREAMBLE_PATTERN_15_8 0x1007 // Default: 0; Preamble pattern
#define PREAMBLE_PATTERN_7_0 0x1008 // Default: 0; Preamble pattern
#define SYNC_CONFIG 0x1100 // Default: 0x01; Sync configuration bits
#define SYNC_BITS_31_24 0x1101 // Default: 0x2D; Byte 3 of sync word
#define SYNC_BITS_23_16 0x1102 // Default: 0xD4; Byte 2 of sync word
#define SYNC_BITS_15_8 0x1103 // Default: 0x2D; Byte 1 of sync word
#define SYNC_BITS_7_0 0x1104 // Default: 0xD4; Byte 0 of sync word
#define PKT_LEN_ADJUST 0x120A // Default: 0; Adjust length field by this amount to derive the byte count of the variable length field.
#define PKT_TX_THRESHOLD 0x120B // Default: 0x30; TX almost empty threshold.
#define PKT_RX_THRESHOLD 0x120C // Default: 0x30; RX almost full threshold.
#define PKT_FIELD_1_LENGTH_12_8 0x120D // Default: 0x00; Byte 1 of field length
#define PKT_FIELD_1_LENGTH_7_0 0x120E // Default: 0x00; Byte 0 of field length
#define PKT_FIELD_1_CONFIG 0x120F // Default: 0x00; Field 1 configuration bits.
#define PKT_CRC_CONFIG 0x1200 // Default: 0; Select a CRC polynomial and seed
#define PKT_CONFIG1 0x1206 // Default: 0; General packet configuration bits
#define PKT_LEN 0x1208 // Default: 0x00; Provides information regarding how to use the length from the received packet.
#define PKT_LEN_FIELD_SOURCE 0x1209 // Default: 0; Field number containing the embedded length field.
#define PKT_FIELD_4_LENGTH_7_0 0x121A // Default: 0x00; Byte 0 of field length
#define PKT_FIELD_4_CONFIG 0x121B // Default: 0x00; Field 4 configuration bits.
#define PKT_FIELD_4_CRC_CONFIG 0x121C // Default: 0x00; Field 4 CRC configuration bits.
#define PKT_FIELD_5_LENGTH_12_8 0x121D // Default: 0x00; Byte 1 of field length
#define PKT_FIELD_5_LENGTH_7_0 0x121E // Default: 0x00; Byte 0 of field length
#define PKT_FIELD_5_CONFIG 0x121F // Default: 0x00; Field 5 configuration bits.
#define PKT_FIELD_1_CRC_CONFIG 0x1210 // Default: 0x00; Field 1 CRC configuration bits.
#define PKT_FIELD_2_LENGTH_12_8 0x1211 // Default: 0x00; Byte 1 of field length
#define PKT_FIELD_2_LENGTH_7_0 0x1212 // Default: 0x00; Byte 0 of field length
#define PKT_FIELD_2_CONFIG 0x1213 // Default: 0x00; Field 2 configuration bits.
#define PKT_FIELD_2_CRC_CONFIG 0x1214 // Default: 0x00; Field 2 CRC configuration bits.
#define PKT_FIELD_3_LENGTH_12_8 0x1215 // Default: 0x00; Byte 1 of field length
#define PKT_FIELD_3_LENGTH_7_0 0x1216 // Default: 0x00; Byte 0 of field length
#define PKT_FIELD_3_CONFIG 0x1217 // Default: 0x00; Field 3 configuration bits.
#define PKT_FIELD_3_CRC_CONFIG 0x1218 // Default: 0x00; Field 3 CRC configuration bits.
#define PKT_FIELD_4_LENGTH_12_8 0x1219 // Default: 0x00; Byte 1 of field length
#define PKT_RX_FIELD_3_LENGTH_7_0 0x122A // Default: 0x00; Byte 0 of field length for RX
#define PKT_RX_FIELD_3_CONFIG 0x122B // Default: 0x00; Field 3 configuration bits for RX.
#define PKT_RX_FIELD_3_CRC_CONFIG 0x122C // Default: 0x00; Field 3 CRC configuration bits for RX.
#define PKT_RX_FIELD_4_LENGTH_12_8 0x122D // Default: 0x00; Byte 1 of field length for RX
#define PKT_RX_FIELD_4_LENGTH_7_0 0x122E // Default: 0x00; Byte 0 of field length for RX
#define PKT_RX_FIELD_4_CONFIG 0x122F // Default: 0x00; Field 4 configuration bits for RX.
#define PKT_FIELD_5_CRC_CONFIG 0x1220 // Default: 0x00; Field 5 CRC configuration bits.
#define PKT_RX_FIELD_1_LENGTH_12_8 0x1221 // Default: 0x00; Byte 1 of field length for RX
#define PKT_RX_FIELD_1_LENGTH_7_0 0x1222 // Default: 0x00; Byte 0 of field length for RX
#define PKT_RX_FIELD_1_CONFIG 0x1223 // Default: 0x00; Field 1 configuration bits for RX.
#define PKT_RX_FIELD_1_CRC_CONFIG 0x1224 // Default: 0x00; Field 1 CRC configuration bits for RX.
#define PKT_RX_FIELD_2_LENGTH_12_8 0x1225 // Default: 0x00; Byte 1 of field length for RX
#define PKT_RX_FIELD_2_LENGTH_7_0 0x1226 // Default: 0x00; Byte 0 of field length for RX
#define PKT_RX_FIELD_2_CONFIG 0x1227 // Default: 0x00; Field 2 configuration bits for RX.
#define PKT_RX_FIELD_2_CRC_CONFIG 0x1228 // Default: 0x00; Field 2 CRC configuration bits for RX.
#define PKT_RX_FIELD_3_LENGTH_12_8 0x1229 // Default: 0x00; Byte 1 of field length for RX
#define PKT_RX_FIELD_4_CRC_CONFIG 0x1230 // Default: 0x00; Field 4 CRC configuration bits for RX.
#define PKT_RX_FIELD_5_LENGTH_12_8 0x1231 // Default: 0x00; Byte 1 of field length for RX
#define PKT_RX_FIELD_5_LENGTH_7_0 0x1232 // Default: 0x00; Byte 0 of field length for RX
#define PKT_RX_FIELD_5_CONFIG 0x1233 // Default: 0x00; Field 5 configuration bits for RX.
#define PKT_RX_FIELD_5_CRC_CONFIG 0x1234 // Default: 0x00; Field 5 CRC configuration bits for RX.
#define MODEM_FREQ_DEV_2 0x200A // Default: 0x00; Byte 2 of TX frequency deviation (a 17-bit unsigned number). This only programs the MSB of TX frequency deviation.
#define MODEM_FREQ_DEV_1 0x200B // Default: 0x06; Byte 1 of frequency deviation.
#define MODEM_FREQ_DEV_0 0x200C // Default: 0xD3; Byte 0 of frequency deviation.
#define MODEM_MOD_TYPE 0x2000 // Default: 0x02; Modulation Type
#define MODEM_MAP_CONTROL 0x2001 // Default: 0x80; Controls bit mapping.
#define MODEM_DATA_RATE_2 0x2003 // Default: 0x0F; Byte 2 of TX data rate in bps (bits per second).
#define MODEM_DATA_RATE_1 0x2004 // Default: 0x42; Byte 1 of TX data rate in bps (bits per second).
#define MODEM_DATA_RATE_0 0x2005 // Default: 0x40; Byte 0 of TX data rate in bps (bits per second).
#define MODEM_RSSI_THRESH 0x204A // Default: 0xFF; RSSI threshold control
#define MODEM_RSSI_JUMP_THRESH 0x204B // Default: 0x0C; RSSI jumping detection threshold.
#define MODEM_RSSI_CONTROL 0x204C // Default: 0x01; RSSI control
#define MODEM_RSSI_CONTROL2 0x204D // Default: 0x00; RSSI control
#define MODEM_RSSI_COMP 0x204E // Default: 0x32; RSSI reading offset.
#define MODEM_ANT_DIV_CONTROL 0x2049 // Default: 0x80; Specifies antenna diversity controls. Antenna diversity mode is valid for standard packet only.
#define PA_MODE 0x2200 // Default: 0x08; PA operating mode and groups.
#define PA_PWR_LVL 0x2201 // Default: 0x7F; PA Level Configuration
#define PA_BIAS_CLKDUTY 0x2202 // Default: 0x00; PA Bias and TX clock duty cycle configuration
#define PA_TC 0x2203 // Default: 0x5D; PA cascode ramping Configuration
#define MATCH_MASK_4 0x300A // Default: 0x00; Match 4 mask.
#define MATCH_CTRL_4 0x300B // Default: 0x00; Match 4 configuration.
#define MATCH_VALUE_1 0x3000 // Default: 0x00; Match 1 value.
#define MATCH_MASK_1 0x3001 // Default: 0x00; Match 1 mask.
#define MATCH_CTRL_1 0x3002 // Default: 0x00; Packet match enable and match 1 configuration.
#define MATCH_VALUE_2 0x3003 // Default: 0x00; Match 2 value.
#define MATCH_MASK_2 0x3004 // Default: 0x00; Match 2 mask.
#define MATCH_CTRL_2 0x3005 // Default: 0x00; Match 2 configuration.
#define MATCH_VALUE_3 0x3006 // Default: 0x00; Match 3 value.
#define MATCH_MASK_3 0x3007 // Default: 0x00; Match 3 mask.
#define MATCH_CTRL_3 0x3008 // Default: 0x00; Match 3 configuration.
#define MATCH_VALUE_4 0x3009 // Default: 0x00; Match 4 value.
#define FREQ_CONTROL_INTE 0x4000 // Default: 0x3C; Frac-N PLL integer number.
#define FREQ_CONTROL_FRAC_2 0x4001 // Default: 0x08; Byte 2 of Frac-N PLL fraction number.
#define FREQ_CONTROL_FRAC_1 0x4002 // Default: 0x00; Byte 1 of Frac-N PLL fraction number.
#define FREQ_CONTROL_FRAC_0 0x4003 // Default: 0x00; Byte 0 of Frac-N PLL fraction number.
#define FREQ_CONTROL_CHANNEL_STEP_SIZE_1 0x4004 // Default: 0x00; Byte 1 of channel step size.
#define FREQ_CONTROL_CHANNEL_STEP_SIZE_0 0x4005 // Default: 0x00; Byte 0 of channel step size.
#define FREQ_CONTROL_VCOCNT_RX_ADJ 0x4007 // Default: 0xFF; VCO target count adjustment for RX
#define RX_HOP_CONTROL 0x5000 // Default: 0x04; RX hop control.
#define RX_HOP_TABLE_SIZE 0x5001 // Default: 0x01; Number of entries in the RX hop table.
#define RX_HOP_TABLE_ENTRY_0 0x5002 // Default: 0; No.1 entry in RX hopping table.
#define RX_HOP_TABLE_ENTRY_63 0x5041 // Default: 2; No.64 entry in RX hopping table.

#endif /* PROPERTIES_H_ */