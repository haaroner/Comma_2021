#pragma once
#include <project_config.h>
#include <motor.h>

class motors 
{
	public:
		motors(Motor& m1, 
					Motor& m2,
					Motor& m3, 
					Motor& m4,
					int max_d_angle);
	void moveMotor(int32_t power);
	void stopRobot(int32_t power);
	void moveRobot(int _maxPower,
										 int _maxPower_angle,
										 int _angle,
										 int _inc,
										 uint32_t _time);
	private:
		uint32_t _curr_time;
		int _current_angle;
		int _max_d_angle;
		int _e_angle;
		Motor _m1;
		Motor _m2;
		Motor _m3;
		Motor _m4;
		signed int opowers;
		uint16_t _maxPowerMove;
		double ang;
};