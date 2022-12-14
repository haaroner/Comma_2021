#include "OpenMV.h"

uint8_t camera::crc8(uint8_t* data, int len)
{
    uint8_t crc = 0xFF, i, j;
    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (j = 0; j < 8; j++) {
            if (crc & 0x80) crc = (char)((crc << 1) ^ 0x31);
            else crc <<= 1;
        }
    }
    return crc;
}

camera::camera(pin &tx, pin &rx):m_tx(tx), m_rx(rx)
{
	m_tx.pinInit();
	m_rx.pinInit();
	usart3::usart3Init();
	sign = 1;
	num = 0;
	_x = 0;
	near_gate_color = 2;
	color = true;
	old_data = 0;
	read = true;
}
void camera::getData()
{
	if(usart3::available() > 3)
	{
		camera_data = usart3::read();
		//old_data = camera_data;
		if(camera_data == 255)
		{
		for(int i = 0; i < 3; i++)
			{
				data[i] = usart3::read();
			}
			if(data[2] == crc8(data, 2))
			{
				_x = data[0] - 127;
				_y = data[1] - 127;
			}
		}
	}
}
int8_t camera::get_x()
{
	return _x;
}

int8_t camera::get_y()
{
	return _y;
}

