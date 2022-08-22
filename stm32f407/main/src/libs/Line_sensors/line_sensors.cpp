#include "line_sensors.h"


line::line(pin &line_1, 
		 pin &line_2,
		 pin &line_3, 
		 pin &line_4,
		 pin &line_callibrate,
		 Dma &dmaBall): 
				 _line_1(line_1),
				 _line_2(line_2),
				 _line_3(line_3),
				 _line_4(line_4),
				 _line_callibrate(line_callibrate),
				 _dmaBall(dmaBall)
{
	side = 0;
	_state = 0;
	_old_state = 0;
	order[0] = 1;
	order[1] = 0;
	order[2] = 15;
	order[3] = 14;
	order[4] = 13;
	order[5] = 12;
	order[6] = 11;
	order[7] = 10;
	order[8] = 2;
	order[9] = 3;
	order[10] = 4;
	order[11] = 5;
	order[12] = 6;
	order[13] = 7;
	order[14] = 8;
	order[15] = 9;
	collibration_time = 5;
	_dmaBall.dmaInit(DMA2_Stream4, DMA_Channel_0, 1);
	_dmaBall.adcInitInDma();
}

int line::getData(uint32_t time)
{
	if((_line_callibrate.getGPIOx()->IDR & _line_callibrate.getPinNumber()) == 0)
		_state = 0;
	else
		_state = 1;
	_dmaBall.dataReturn(0);	
	
	
	if ((_line_callibrate.getGPIOx()->IDR & _line_callibrate.getPinNumber()) == 1)//button not preesed
  {
    if (_old_state == 1 && time - t > collibration_time * 1000)//checking does the robot need to recalculate setting
    {
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          sen = (i * 4) + j;// calculating sen
          setting[order[sen]] = floor((data_max[order[sen]] + data_min[order[sen]]) / 2.0);// calculating setting for sen
        }
      }
      _old_state = 0;
    }
    t = time;
    _state = 0;// starting main mode
  }
  else
  {
    if (_old_state == 0)
    {
      t = time;
      _old_state = 1;
    }
    _state = 1;// starting callibrating mode
  }
  
  if (_state == 0)// main mode
  {
    for (int i = 0; i < 4; i++)// setupping data-out mas
      output[i] = 0;
    for (int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
      {
        setData(0); // setting to low signal plexor-control pins
        sen = (i * 4) + j;//calculating sen
				setData(sen);
        data[order[sen]] = _dmaBall.dataReturn(0);// reading data from sen
        side = floor(order[sen] / 4.0);// calculating side of the sen(forward, backward, left, right)
        if(data[order[sen]] >= 244)// comparing data of sen with setting of this sen
        {
          output[i] = 1;// changing out-data mas
        }
      }
      //digital_write('C', 1111);//sending data to stm32
    }
  }
  else if (_state == 1)// callibrating mode
  {
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
      setData(0);// clearing plexor-control pins
      sen = (i * 4) + j;// calculating sen to read
      setData(sen); //selecting sensor to read
      sub = _dmaBall.dataReturn(0);// reading data from sen
      if (sub > data_max[order[sen]]) data_max[order[sen]] = sub;// detecting the highest signal(white color)
      if (sub < data_min[order[sen]]) data_min[order[sen]] = sub;// delecting the smallest signal(green/black color)
      }
    }
  }
}

void line::setData(int8_t num)
{
	for(int i = 0; i < 4; i++)
	{
		if(num % 2 == 1)
		{
			num = (num - 1) / 2;
			output[3 - i] = 1;
		}
		else
			output[3 - i] = 0;
	}
	if(output[0] == 0)
		_line_1.resetBit();
	if(output[0] == 1)
		_line_1.setBit();
	
	if(output[1] == 0)
		_line_2.resetBit();
	if(output[1] == 1)
		_line_2.setBit();
	
		if(output[2] == 0)
		_line_3.resetBit();
	if(output[2] == 1)
		_line_3.setBit();
	
		if(output[3] == 0)
		_line_4.resetBit();
	if(output[3] == 1)
		_line_4.setBit();
	
}

//int line::change_u(int degree, uint32_t time)
//{
//	getData();
//	for(int iter = 0; iter < 4; iter++)
//	{
//		if(_data[iter] == 1)
//		{
//			if (times[iter] > 0)
//			{
//				if(time - times[iter] > 5)
//					check[iter] = 1;
//				else
//					check[iter] = 0;
//			}
//			else
//			{
//				times[iter] = time;
//			}
//		}
//		else
//		{
//			times[iter] = 0;
//		}
//	}
//	for(int iter = 0; iter < 4; iter++)
//	{
//		if(check[iter] == 1)
//		{
//			if(iter == 3)
//			iter = -1;
//			if(degree < iter * 90 + 45 && degree > iter * 90 - 45)
//			{
//				if(degree < iter * 90)
//				{
//					degree -= 90;
//				}
//				else
//				{
//					degree += 90;
//				}
//			}
//			if(iter == -1)
//			iter = 3;
//		}
//	}
//	return degree;
//}
