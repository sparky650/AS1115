#include "AS1115.h"

void AS1115::setIntensity(uint8_t intensity)
{
	if (intensity > 15) { intensity = 15; }
	writeRegister(GLOBAL_INTEN_r, intensity);
}

void AS1115::setIntensity(uint8_t dig, uint8_t intensity)
{
	if (intensity > 15) { intensity = 15; }
	switch (dig)
	{
	case 0:
		writeRegister(DIGIT01_INTEN_r, intensity);
		break;
	case 1:
		writeRegister(DIGIT01_INTEN_r, intensity << 4);
		break;
	case 2:
		writeRegister(DIGIT23_INTEN_r, intensity);
		break;
	case 3:
		writeRegister(DIGIT23_INTEN_r, intensity << 4);
		break;
	case 4:
		writeRegister(DIGIT45_INTEN_r, intensity);
		break;
	case 5:
		writeRegister(DIGIT45_INTEN_r, intensity << 4);
		break;
	case 6:
		writeRegister(DIGIT67_INTEN_r, intensity);
		break;
	case 7:
		writeRegister(DIGIT67_INTEN_r, intensity << 4);
		break;
	}
}

void AS1115::setDecode(bool state)
{
	writeRegister(DECODE_MODE_r, state ? 0xFF : 0x00);
}

void AS1115::setDecode(uint8_t dig, bool state)
{
	uint8_t mask, tempReg;
	mask =  1 << dig;
	tempReg = readRegister(DECODE_MODE_r);
	if (state) { tempReg |= mask; }
	else { tempReg &= ~mask; }
	writeRegister(DECODE_MODE_r, tempReg);
}

void AS1115::shutdown(bool)
{

}

void AS1115::reset()
{

}

void AS1115::setScanLimit(uint8_t dig)
{
	if (dig > 7) { dig = 7; }
	writeRegister(SCAN_LIMIT_r, dig);
}

void AS1115::setBlink(bool, uint8_t)
{

}

void AS1115::setDigit(uint8_t dig, uint8_t val)
{
	const AS1115_Register_t regMap[8] =
	{DIGIT0_r, DIGIT1_r, DIGIT2_r, DIGIT3_r, DIGIT4_r, DIGIT5_r, DIGIT6_r, DIGIT7_r};
	if (dig > 7) { return; }
	writeRegister(regMap[dig], val);
}

void AS1115::setDigits(uint8_t count, uint8_t *buffer)
{
	if (count > 8) { count = 8; }
	writeRegisters(DIGIT0_r, buffer, count);
}

uint8_t AS1115::getKey(AS1115_key_t reg)
{
	return readRegister((AS1115_Register_t)reg);
}

uint16_t AS1115::getKey()
{
	uint8_t buf[2];
	readRegisters(KEYA_r, buf, 2);
	return ((uint16_t)buf[1]<<8) + (uint16_t)buf[0];
}

bool AS1115::testDigits()
{
	return false;
}

uint8_t AS1115::testShort(uint8_t)
{
	return 0;
}

uint8_t AS1115::testOpen(uint8_t)
{
	return 0;
}
