#include "dist_sen.h"
dist_sen::dist_sen(Dma &dmaL,
					Dma &dmaR,
					volatile int &e_gyro): _dmaL(dmaL),
												_dmaR(dmaR),
												_e_gyro(e_gyro)
{
	_dmaL.dmaInit(DMA2_Stream4, DMA_Channel_0, 1);
	_dmaL.adcInitInDma();
	_dmaR.dmaInit(DMA2_Stream4, DMA_Channel_0, 1);
	_dmaR.adcInitInDma();
}
bool dist_sen::getDataL(uint16_t _porogL)
{
	if(_dmaL.dataReturn(0) * cos(double(_e_gyro)) > _porogL || (_e_gyro > -30 && _e_gyro < 30))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool dist_sen::getDataR(uint16_t _porogR)
{
	if(_dmaR.dataReturn(0) * cos(double(_e_gyro)) > _porogR || (_e_gyro > -30 && _e_gyro < 30))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
