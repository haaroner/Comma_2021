#pragma once

#include <project_config.h>
#include <pin_setup.h>

class Motor
{
	public:
		Motor(GPIO_TypeDef* GPIOx,
			uint32_t pinNumber,
			uint16_t pinSourceGPIO,
			uint8_t AFGPIO, 
			GPIO_TypeDef* GPIOx2,
			uint32_t pinNumber2,
			uint16_t pinSourceGPIO2,
			uint8_t AFGPIO2);
		void motorPWMInit(uint32_t RCC_TIMx1,
			uint8_t channel1,
			TIM_TypeDef* TIMx1,
			uint32_t RCC_TIMx2,
			uint8_t channel2,
			TIM_TypeDef* TIMx2);
		void motorMove(int32_t pupower);
		void blockMotor(int32_t pupower);
	private:
		pin _p1;
		pin _p2;
		
};
