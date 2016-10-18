/*
 * Itg3200.h
 *
 * Created: 29.7.2016 г. 1:10:52
 *  Author: Kosyo
 */ 


#ifndef ITG3200_H_
#define ITG3200_H_

#include "TwiUtils.h"

#define ITG_ADDR 0x68

#define DLPF_FS_REG 0x16
#define FS_2000 3
#define DLPF_256_8000 0
#define DLPF_188_1000 1
#define DLPF_98_1000 2
#define DLPF_42_1000 3
#define DLPF_20_1000 4
#define DLPF_10_1000 5
#define DLPF_5_1000 6

#define PWR_MGM_REG 0x3E
#define PWR_H_RESET 7
#define PWR_SLEEP 6
#define PWR_STBY_X 5
#define PWR_STBY_Y 4
#define PWR_STBY_Z 3
#define CLK_INTERNAL 0
#define CLK_X 1
#define CLK_Y 2
#define CLK_Z 3
#define CLK_EXT_32_KHZ 4
#define CLK_EXT_19_MHZ 5

#define ITG_TEMPH_REG 0x1B
#define ITG_TEMPL_REG 0x1C
#define ITG_XH_REG 0x1D
#define ITG_XL_REG 0x1E
#define ITG_YH_REG 0x1F
#define ITG_YL_REG 0x20
#define ITG_ZH_REG 0x21
#define ITG_ZL_REG 0x22

bool ItgInit();
bool ItgReadGyro(int* gx, int* gy, int* gz);
bool ItgReadGyro(ubyte* buffer);
bool ItgReadTemp(int* temp);
bool ItgReadTemp(ubyte* buffer);

#endif /* ITG3200_H_ */