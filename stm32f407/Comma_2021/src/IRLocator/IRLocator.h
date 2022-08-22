#pragma once
#include <project_config.h>
#include <pin_setup.h>
#include "soft_i2c.h"
class IRlocator
{
	public:
		IRlocator(soft_i2c &irI2C, uint32_t addres);
		int16_t collectData(uint8_t data);
    void getData();
    int16_t getAngle();
    uint8_t getDistance();
	private:
		soft_i2c m_irI2C;
		uint32_t m_addres;
    int16_t _angle;
    uint8_t _distance;
};
