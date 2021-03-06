﻿/*
 * Mpu6050.cpp
 *
 * Created: 24.9.2016 г. 10:03:54
 *  Author: Kosyo
 */ 

#include "Mpu6050.h"

Mpu6050::Mpu6050(bool ad0)
{
	addr = MPU_ADDR;
	if(ad0) addr |= 1;
}

bool Mpu6050::Init(ubyte gyroRange, ubyte accRange)
{
	if(gyroRange > 3) return false;
	if(accRange > 3) return false;

	if(!TwiWriteToReg(addr, PWR_MGMT_1, 1)) return false; // sleep = 0 + clock = gyro X
	if(!TwiWriteToReg(addr, SMPLRT_DIV, 0)) return false; // 8 KHz sample rate
	if(!TwiWriteToReg(addr, CONFIG, 0)) return false; // no DLPF
	if(!TwiWriteToReg(addr, GYRO_CONFIG, gyroRange << 3)) return false;
	if(!TwiWriteToReg(addr, ACCEL_CONFIG, accRange << 3)) return false;

	return true;
}

bool Mpu6050::GetAccelerometer(ubyte* buffer)
{
	return TwiReadFromReg(addr, ACC_XH, buffer, 6);
}

bool Mpu6050::GetAccelerometer(int* ax, int* ay, int* az)
{
	ubyte buff[6];
	if(!TwiReadFromReg(addr, ACC_XH, buff, 6)) return false;

	*ax = buff[0] << 8 | buff[1];
	*ay = buff[2] << 8 | buff[3];
	*az = buff[4] << 8 | buff[5];

	return true;
}

bool Mpu6050::GetGyroscope(ubyte* buffer)
{
	return TwiReadFromReg(addr, GYRO_XH, buffer, 6);
}

bool Mpu6050::GetGyroscope(int* gx, int* gy, int* gz)
{
	ubyte buff[6];
	if(!TwiReadFromReg(addr, GYRO_XH, buff, 6)) return false;

	*gx = buff[0] << 8 | buff[1];
	*gy = buff[2] << 8 | buff[3];
	*gz = buff[4] << 8 | buff[5];

	return true;
}

bool Mpu6050::GetTemperature(int* temp)
{
	ubyte buff[2];
	if(!TwiReadFromReg(addr, TEMPH, buff, 2)) return false;

	*temp = buff[0] << 8 | buff[1];
	return true;
}