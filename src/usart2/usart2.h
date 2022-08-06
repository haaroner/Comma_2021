#pragma once
#include "project_config.h"

namespace usart2
{
	void usart2Init();
	void write(uint8_t);
	uint16_t read();
	uint16_t available();
	extern volatile uint8_t tx[512];
	extern volatile uint8_t rx[512];
	extern volatile uint16_t _rxCnt;
	extern volatile uint16_t _txCnt;
	extern volatile bool flag;
	extern volatile uint16_t _readCnt;
	extern volatile uint16_t _sendCnt;
}