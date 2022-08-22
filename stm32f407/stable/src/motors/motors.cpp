#include "motors.h"
#include "math.h"

motors::motors(Motor& m1, 
					 Motor& m2,
					 Motor& m3, 
					 Motor& m4,
					 int max_d_angle): 
											 _m1(m1),
											 _m2(m2), 
											 _m3(m3), 
											 _m4(m4)
{
	_current_angle = 0;
	_max_d_angle = max_d_angle;
	_curr_time = 0;
}
void motors::moveMotor(int32_t power)
{
		_m1.motorMove(-power);//without
		_m2.motorMove(power);//green right
		_m3.motorMove(-power);//white
		_m4.motorMove(-power);//blue right
}

void motors::stopRobot(int32_t power)
{
	_m1.blockMotor(power);
	_m2.blockMotor(power);
	_m3.blockMotor(power);
	_m4.blockMotor(power);
}

void motors::moveRobot(int _maxPower,
										 int _maxPower_angle,
										 int _angle,
										 int _inc, 
										 uint32_t _time)
{
	if(_inc > _maxPower_angle)
		_inc =  _maxPower_angle;
	else if(_inc < -_maxPower_angle)
		_inc =  -_maxPower_angle;
	_current_angle = _angle;
//	_e_angle = _angle - _current_angle;
//	if(_e_angle < -180)
//		_e_angle += 360;
//	else if(_e_angle > 180)
//		_e_angle -= 360;	
//				
//	if(abs(double(_e_angle)) > _max_d_angle)
//	{
//		if(_time != _curr_time)
//		{
//			if(_e_angle > 0)
//				_current_angle += _max_d_angle;
//			else
//				_current_angle -= _max_d_angle;
//			
//			_curr_time = _time;
//		}
//	}
//	else 
//		_current_angle = _angle;
	
//	if(_current_angle < -180)
//		_current_angle += 360;
//	else if(_current_angle > 180)
//		_current_angle -= 360;	
	
	ang = (double(_current_angle) + 135)/57.3;
	opowers = _maxPower * cos(ang);
	opowers += _inc;
	_m1.motorMove(-opowers);
	
	ang = (double(_current_angle) - 135)/57.3;
	opowers = _maxPower * cos(ang);
	opowers -= _inc;
	_m2.motorMove(-opowers);

	
	ang = (double(_current_angle) + 45)/57.3;
	opowers = _maxPower * cos(ang);
	opowers -= _inc;
	_m3.motorMove(opowers);

	
	ang = (double(_current_angle) - 45)/57.3;
	opowers = _maxPower * cos(ang);
	opowers += _inc;
	_m4.motorMove(-opowers);
}

// you are clown