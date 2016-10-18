/*
 * Itg3200.cpp
 *
 * Created: 23.9.2016 г. 21:57:46
 *  Author: Kosyo
 */ 

 #include "Itg3200.h"

 bool ItgInit()
 {
	 if(!TwiWriteToReg(ITG_ADDR, DLPF_FS_REG, (FS_2000<<3) | DLPF_256_8000)) return false;
	 if(!TwiWriteToReg(ITG_ADDR, PWR_MGM_REG, CLK_X)) return false;
	 return true;
 }


 // Въртене по хоризонтална ос оказва влияние на перпендикулярната на акселерометъра
 bool ItgReadGyro(int* gx, int* gy, int* gz)
 {
	 ubyte data[6];
	 if(!TwiReadFromReg(ITG_ADDR, ITG_XH_REG, data, 6)) return false;

	 *gx = (data[0] << 8) | data[1];
	 *gy = (data[2] << 8) | data[3];
	 *gz = (data[4] << 8) | data[5];

	 return true;
 }

 bool ItgReadGyro(ubyte* buffer)
 {
	 return TwiReadFromReg(ITG_ADDR, ITG_XH_REG, buffer, 6);
 }

 bool ItgReadTemp(int* temp)
 {
	 ubyte data[2];
	 if(!TwiReadFromReg(ITG_ADDR, ITG_TEMPH_REG, data, 2)) return false;
	 *temp = (data[0] << 8) | data[1];
	 return true;
 }

 bool ItgReadTemp(ubyte* buffer)
 {
	 return TwiReadFromReg(ITG_ADDR, ITG_TEMPH_REG, buffer, 2);
 }
