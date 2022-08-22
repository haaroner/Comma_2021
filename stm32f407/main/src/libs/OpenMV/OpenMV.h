#pragma once
#include "project_config.h"
#include "USART.h"
#include "pin_setup.h"


class camera
{
	public:
		camera(pin &tx, pin &rx);
		void getData();
		int8_t get_x();
		int8_t get_y();
	private:
		int8_t sign;
		pin m_rx, m_tx;
		uint8_t camera_data;
		int16_t _data;
		int16_t _x;
		int16_t _y;
		int16_t old_data;
		int8_t near_gate_color;
		bool color; //1=y 0=b
		bool num;
		bool finaly;
		bool read;
		uint8_t data[3];
		uint8_t crc8(uint8_t* data, int len);
};
