#include "motors.h"
#include "math.h"

motors::motors(Motor& m1, 
					 Motor& m2,
					 Motor& m3, 
					 Motor& m4): _m1(m1),
											 _m2(m2), 
											 _m3(m3), 
											 _m4(m4)
{
		
}
void motors::moveMotor(int32_t power)
{
		_m1.motorMove(-power);//without
		_m2.motorMove(-power);//green right
		_m3.motorMove(-power);//white
		_m4.motorMove(power);//blue right
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
										 int _inc)
{
	if(_inc > _maxPower_angle)
		_inc =  _maxPower_angle;
	else if(_inc < -_maxPower_angle)
		_inc =  -_maxPower_angle;
	
	ang = (double(_angle) + 135)/57.3;
	opowers = _maxPower * cos(ang);
	opowers += _inc;
	_m1.motorMove(opowers);
	
	ang = (double(_angle) - 135)/57.3;
	opowers = _maxPower * -cos(ang);
	opowers += _inc;
	_m2.motorMove(-opowers);

	
	ang = (double(_angle) + 45)/57.3;
	opowers = _maxPower * cos(ang);
	opowers -= _inc;
	_m3.motorMove(-opowers);

	
	ang = (double(_angle) - 45)/57.3;
	opowers = _maxPower * cos(ang);
	opowers += _inc;
	_m4.motorMove(opowers);
}

// you are clown
