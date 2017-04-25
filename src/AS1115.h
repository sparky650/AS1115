/**
 * @file	AS1115.h
 * @author	Keegan Morrow
 * @version 0.0.1
 * @brief Arduino library for the AS1115 LED driver
 *
 */

#ifndef __AS1115_h_
#define __AS1115_h_

#include <Arduino.h>
#include <Wire.h>
#include <wireUtil.h>

enum AS1115_Register_t
{
	DIGIT0_r = 0x01,
	DIGIT1_r = 0x02,
	DIGIT2_r = 0x03,
	DIGIT3_r = 0x04,
	DIGIT4_r = 0x05,
	DIGIT5_r = 0x06,
	DIGIT6_r = 0x07,
	DIGIT7_r = 0x08,
	DECODE_MODE_r = 0x09,
	GLOBAL_INTEN_r = 0x0A,
	SCAN_LIMIT_r = 0x0B,
	SHUTDOWN_r = 0x0C,
	SELF_ADDR_r = 0x0D,
	FEATURE_r = 0x0E,
	DISP_TEST_r = 0x0F,
	DIGIT01_INTEN_r = 0x10,
	DIGIT23_INTEN_r = 0x11,
	DIGIT45_INTEN_r = 0x12,
	DIGIT67_INTEN_r = 0x13,
	DIGIT0_DIAG_r = 0x14,
	DIGIT1_DIAG_r = 0x15,
	DIGIT2_DIAG_r = 0x16,
	DIGIT3_DIAG_r = 0x17,
	DIGIT4_DIAG_r = 0x18,
	DIGIT5_DIAG_r = 0x19,
	DIGIT6_DIAG_r = 0x1A,
	DIGIT7_DIAG_r = 0x1B,
	KEYA_r = 0x1C,
	KEYB_r = 0x1D
};

enum AS1115_key_t { KEY_A = 0x1C, KEY_B = 0x1D };

static const uint8_t MCP23017_defaultAddress = 0x00;

class AS1115: public wireUtil<AS1115_Register_t, uint8_t>
{
public:
	AS1115()
	{
		timeoutTime = 1000UL;
		timeoutFlag = false;
	}
	using wireUtil::begin;
	/**
	* @brief Initialize the chip at the default address
	*
	*/
	void begin() {begin(AS1115_defaultAddress);}
	/**
	* @brief Get the hardware address from the logical address of the chip
	*
	* @param a Logical address of the chip
	* @return Hardware address of the chip
	*/
	uint8_t addressIndex(uint8_t a) {return a + AS1115_defaultAddress;}

	void setIntensity(uint8_t);
	void setIntensity(uint8_t, uint8_t);
	void setDecode(uint8_t, bool);
	void shutdown(bool);
	void reset();
	void setScanLimit(uint8_t);
	void setBlink(bool, uint8_t);
	void setDigit(uint8_t, uint8_t);
	void setDigits(uint8_t, uint8_t *);
	uint8_t getKey(AS1115_key_t);
	uint16_t getKey();
	bool testDigits();
	uint8_t testShort(uint8_t);
	uint8_t testOpen(uint8_t);
};

#endif // __AS1115_h_