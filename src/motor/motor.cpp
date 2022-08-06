#include "motor.h"


Motor::Motor(GPIO_TypeDef* GPIOx,
											uint32_t pinNumber,
											uint16_t pinSourceGPIO,
											uint8_t AFGPIO, 
						 GPIO_TypeDef* GPIOx2,
											uint32_t pinNumber2,
											uint16_t pinSourceGPIO2,
											uint8_t AFGPIO2):_p1(GPIOx,
																					pinNumber,
																					GPIO_Mode_AF,
																					GPIO_Speed_100MHz,
																					GPIO_OType_PP, 
																					GPIO_PuPd_NOPULL,
																					pinSourceGPIO,
																					AFGPIO),
																				_p2(GPIOx2,
																					pinNumber2,
																					GPIO_Mode_AF,
																					GPIO_Speed_100MHz,
																					GPIO_OType_PP, 
																					GPIO_PuPd_NOPULL,
																					pinSourceGPIO2,
																					AFGPIO2)
{
	
	_p1.pinInit();	
	_p2.pinInit();
	
}

void Motor::motorPWMInit(uint32_t RCC_TIMx1,
													uint8_t channel1,
													TIM_TypeDef* TIMx1,
													uint32_t RCC_TIMx2,
													uint8_t channel2,
													TIM_TypeDef* TIMx2)
{
	
	_p1.pwmInit(RCC_TIMx1, 2, 4096, 0, channel1, TIMx1);	
	_p2.pwmInit(RCC_TIMx2, 2, 4096, 0, channel2, TIMx2);
	
}

void Motor::motorMove(int32_t pupower)
{
	if(pupower <= -1)
	{
		if(pupower < -4095)
		{
			pupower = -4095;
		}
		_p1.pwm(0);
		_p2.pwm(pupower * -1);
	}
	else
	{
		if(pupower > 4095)
		{
			pupower = 4095;
		}
		_p1.pwm(pupower);
		_p2.pwm(0);
	}
}

void Motor::blockMotor(int32_t pupower)
{
	_p1.pwm(pupower);
	_p2.pwm(pupower);
}
