#pragma once
#include "project_config.h"
#include "usart3.h"
#include "pin_setup.h"


class camera
{
	public:
		camera(pin &tx, pin &rx);
		void getData();
		int32_t get_forward_x();
		int32_t get_forward_y();
    int32_t get_backward_x();
		int32_t get_backward_y();
	private:
		int8_t sign;
		pin m_rx, m_tx;
		uint8_t camera_data;
		int16_t _data;
		int16_t _x1;
		int16_t _y1;
    int16_t _x2;
		int16_t _y2;
		int16_t old_data;
		int8_t near_gate_color;
		bool color; //1=y 0=b
		bool num;
		bool finaly;
		bool read;
		uint8_t data[5];
		uint8_t crc8(uint8_t* data, int len);
};
