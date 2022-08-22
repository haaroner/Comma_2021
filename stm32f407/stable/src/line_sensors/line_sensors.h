#pragma once
#include "project_config.h"
#include "dma.h"
#include "pin_setup.h"
#include "math.h"

class line
{
	public:
		line(pin &line_1, 
			 pin &line_2,
			 pin &line_3, 
			 pin &line_4,
			 pin &line_callibrate,
			 Dma &dmaBall);
		int getData(uint32_t _time);
		void setData(int8_t num);

	private:
		pin _line_1;
		pin _line_2;
		pin _line_3;
		pin _line_4;
		pin _line_callibrate;
		Dma _dmaBall;
		int data[16]; //data of line sensors
		int order[16];
		int setting[16];// the value above which, color is white
		int data_max[16];
		int data_min[16];
		int output[4]; //output data to the stm32
		int side;
		int sub;
		int t;
		uint8_t _state;
		uint8_t _old_state;
		uint8_t sen;
		uint32_t collibration_time;
};
