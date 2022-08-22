#include "PID.h"

#define gyro_mode 01
#define standart_PID_mode 02

PID::PID(uint8_t _mode, int32_t _max_u, float _kp, float _ki, float _kd, int32_t _i_max)
{
	max_u = _max_u;
	min_u = -_max_u;
	kp = _kp;
	ki = _ki;
	kd = _kd;
	max_i = _i_max;
	time = 0;
	p = 0;
	i = 0;
	d = 0;
	eold = 0;
}

void PID::set_settings(int32_t _x0, int32_t _max_e, int32_t _min_e)
{
	x0 = _x0;
	max_e = _max_e;
	min_e = _min_e;
}

int32_t PID::calculate_u(int32_t sen, uint32_t _time)
{
	e = x0 - sen;
	if(mode == gyro_mode)
		e = my_math.lead_to_degree_range(e, max_e, min_e);
	
	p = e * kp;
	
	i += e * ki;
	if(i > max_i)
		i = max_i;
	else if(i < -max_i)
		i = -max_i;
	
	d = (e - eold) * kd;
	
	u = p + i + d;
	
	u = my_math.leed_to_range(u, max_u, min_u);
	if(time != _time)
	{
		eold = e;
		time = _time;
	}
	return u;
}
