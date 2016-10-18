/*
 * Adx345.cpp
 *
 * Created: 23.9.2016 г. 21:55:44
 *  Author: Kosyo
 */ 

 #include "Adx345.h"

 bool AdxInit()
 {
	 if(!TwiWriteToReg(ADX_ADDR, ADX_POWER_CTL_REG, (1<<ADX_POWER_CTL_AUTO_SLEEP) | (1<<ADX_POWER_CTL_MEASURE)))	return false;
	 if(!TwiWriteToReg(ADX_ADDR, ADX_BW_RATE_REG, ADX_RATE_400)) return false;
	 if(!TwiWriteToReg(ADX_ADDR, ADX_DATA_FORMAT_REG, (1<<ADX_FULL_RES) | ADX_RANGE_16G)) return false;
	 return true;
 }

 bool AdxRead(int* ax, int* ay, int* az)
 {
	 ubyte data[6];
	 if(!TwiReadFromReg(ADX_ADDR, ADX_XH_REG, data, 6)) return false;

	 *ax = data[0] | (data[1] << 8);
	 *ay = data[2] | (data[3] << 8);
	 *az = data[4] | (data[5] << 8);

	 return true;
 }

 bool AdxRead(ubyte* buffer)
 {
	 return TwiReadFromReg(ADX_ADDR, ADX_XH_REG, buffer, 6);
 }