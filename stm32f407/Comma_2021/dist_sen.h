#pragma once
#include "project_config.h"
#include "dma.h"
#include "pin_setup.h"
#include "math.h"

class dist_sen 
{
	public:
		dist_sen(Dma &dmaL,
					Dma &dmaR,
					volatile int &e_gyro);
	bool getDataL(uint16_t _porogL);
	bool getDataR(uint16_t _porogR);
	private:
		Dma _dmaL;
		Dma _dmaR;
		int _e_gyro;
};