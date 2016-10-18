/*
 * Adx345.h
 *
 * Created: 29.7.2016 г. 1:02:41
 *  Author: Kosyo
 */ 


#ifndef ADX345_H_
#define ADX345_H_

#include "TwiUtils.h"

#define ADX_ADDR 0x53

#define ADX_OFSX_REG 0x1E
#define ADX_OFSY_REG 0x1F
#define ADX_OFSZ_REG 0x20

#define ADX_BW_RATE_REG 0x2C
#define ADX_LOW_PWR 4
#define ADX_RATE_3200 15
#define ADX_RATE_1600 14
#define ADX_RATE_800 13
#define ADX_RATE_400 12
#define ADX_RATE_200 11
#define ADX_RATE_100 10 // default
#define ADX_RATE_50 9
#define ADX_RATE_25 8
#define ADX_RATE_12_5 7
#define ADX_RATE_6_25 6
#define ADX_RATE_3_13 5
#define ADX_RATE_1_56 4
#define ADX_RATE_0_78 3
#define ADX_RATE_0_39 2
#define ADX_RATE_0_20 1
#define ADX_RATE_0_10 0

#define ADX_POWER_CTL_REG 0x2D
#define ADX_POWER_CTL_AUTO_SLEEP 4
#define ADX_POWER_CTL_MEASURE 3

#define ADX_DATA_FORMAT_REG 0x31
#define ADX_SELF_TEST 7
#define ADX_SPI 6
#define ADX_INT_INVERT 5
#define ADX_FULL_RES 3
#define ADX_JUSTIFY 2
#define ADX_RANGE_2G 0
#define ADX_RANGE_4G 1
#define ADX_RANGE_8G 2
#define ADX_RANGE_16G 3

#define ADX_XH_REG 0x32

bool AdxInit();
bool AdxRead(int* ax, int* ay, int* az);
bool AdxRead(ubyte* buffer);

#endif /* ADX345_H_ */