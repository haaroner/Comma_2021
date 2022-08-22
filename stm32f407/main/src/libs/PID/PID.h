#pragma once

#include "project_config.h"
#include "my_math.h"

class PID
{
	public:
		PID(uint8_t _mode, int32_t _max_u, float _kp, float _ki, float _kd, int32_t _i_max);
		void set_settings(int32_t _x0, int32_t _max_e, int32_t _min_e);
		int32_t calculate_u(int32_t sen, uint32_t _time);
	
	private:
		my_Math my_math;
		uint8_t mode;
		int32_t x0;
		int32_t e, max_e, min_e;
		int32_t max_u, min_u; 
		float kp, ki, kd;
		int32_t max_i;
		uint32_t time;
		int32_t u, p, i, d, eold;
};
