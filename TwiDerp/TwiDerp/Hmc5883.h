/*
 * Hmc5883.h
 *
 * Created: 29.7.2016 г. 13:06:34
 *  Author: Kosyo
 */ 


#ifndef HMC5883_H_
#define HMC5883_H_

#include "TwiUtils.h"

#define HMC_ADDR 0x1E

#define HMC_CTRL_REG_A 0
#define HMC_MS_NORMAL 0 // default
#define HMC_MS_POS_XY_NEG_Z 1
#define HMC_MS_NEG_XY_POS_Z 2
#define HMC_DATA_RATE_0_75 0
#define HMC_DATA_RATE_1_5 1
#define HMC_DATA_RATE_3 2
#define HMC_DATA_RATE_7_5 3
#define HMC_DATA_RATE_15 4 // default
#define HMC_DATA_RATE_30 5
#define HMC_DATA_RATE_75 6

// Gain = counts/gauss
#define HMC_CTRL_REG_B 1
#define HMC_GAIN_1280 0
#define HMC_GAIN_1024 1 // default
#define HMC_GAIN_768 2
#define HMC_GAIN_614 3
#define HMC_GAIN_415 4
#define HMC_GAIN_361 5
#define HMC_GAIN_307 6
#define HMC_GAIN_219 7

#define HMC_MODE_REG 2
#define HMC_CNT_MODE 0
#define HMC_SINGLE_MODE 1 // default
#define HMC_IDLE_MODE 2
#define HMC_SLEEP_MODE 3

#define HMC_XH_REG 3
#define HMC_XL_REG 4
#define HMC_YH_REG 5
#define HMC_YL_REG 6
#define HMC_ZH_REG 7
#define HMC_ZL_REG 8

// Read-only, not used
#define HMC_SREG 9
#define HMC_ID_REG_A 10
#define HMC_ID_REG_B 11
#define HMC_ID_REG_C 12

bool HmcInit();
bool HmcRead(int* mx, int* my, int* mz);

#endif /* HMC5883_H_ */