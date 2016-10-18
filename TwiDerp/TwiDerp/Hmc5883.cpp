/*
 * Hmc5883.cpp
 *
 * Created: 23.9.2016 г. 21:56:53
 *  Author: Kosyo
 */ 

 #include "Hmc5883.h"

 bool HmcInit()
 {
	 if(!TwiWriteToReg(HMC_ADDR, HMC_CTRL_REG_A, HMC_DATA_RATE_75<<2)) return false;
	 if(!TwiWriteToReg(HMC_ADDR, HMC_MODE_REG, HMC_CNT_MODE)) return false;

	 return true;
 }

 bool HmcRead(int* mx, int* my, int* mz)
 {
	 ubyte data[6];
	 if(!TwiReadFromReg(HMC_ADDR, HMC_XH_REG, data, 6)) return false;

	 *mx = (data[0] << 8) | data[1];
	 *my = (data[2] << 8) | data[3];
	 *mz = (data[4] << 8) | data[5];

	 return true;
 }