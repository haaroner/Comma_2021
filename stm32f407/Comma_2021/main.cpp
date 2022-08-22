#include "project_config.h"
#include "pin_setup.h"
#include "time_service.h"
#include "adc.h"
#include "dma.h"
#include "usart6.h"
#include "usart3.h"
#include "soft_i2c.h"
#include "IRLocator.h"
#include "motor.h"
#include "motors.h"
#include "OpenMV.h"

#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4

#define Usart1 01
#define Usart2 02
#define Usart3 03
#define Usart6 04
#define i2c 05
#define read_UP 06
#define write 07

#define tim1 81
#define tim2 82
#define tim3 83
#define tim4 84
#define tim5 85
#define tim8 88
#define tim9 89
#define tim10 810
#define tim11 811
#define tim12 812
#define tim13 813
#define tim14 814

#define stop_move false

int main()

{
  bool stop_motors = 0;
  uint8_t role, ball_signal;
  int16_t ball_angle;
	Motor m1('E', 5, tim9, CHANNEL1, 'E', 6, tim9, CHANNEL2);				
	Motor m2('B', 5, tim3, CHANNEL2, 'B', 3, tim2, CHANNEL2);
	Motor m3('A', 0, tim2, CHANNEL1, 'A', 1, tim5, CHANNEL2);
	Motor m4('E', 11, tim1, CHANNEL2, 'E', 13, tim1, CHANNEL3);
    
	pin usart6_tx('C', 6, Usart6);		
	pin usart6_rx('C', 7,  Usart6);		
	pin usart3_tx('B', 10, Usart3);		
	pin usart3_rx('B', 11, Usart3);		
	pin i2c3_scl('A', 8, i2c);		
	pin i2c3_sda('C', 9, i2c);		
	pin motors_move('B', 1, read_UP);
	pin gyro_reset('B', 0, read_UP);		

	soft_i2c ir(i2c3_scl, i2c3_sda);
	IRlocator locator360(ir, 0x0E);
	usart6::usart6Init();
	usart3::usart3Init();
	camera camera(usart3_tx, usart3_rx);
	
	motors motors(m1, m2, m3, m4, int(180/500));
//	Adc line_signal(ADC1, 1, 0, ADC_Channel_9, RCC_APB2Periph_ADC1, distL);
//	line_signal.sendMeChannel(ADC_Channel_9);
//	Dma lineDma(RCC_AHB1Periph_DMA2, line_signal);
//	lineDma.dmaInit(DMA2_Stream0, DMA_Channel_0, 1);
//	lineDma.adcInitInDma();
	time_service::init();
	time_service::delay_ms(30000); 
	role = 0; // changing role------------------------------------
	x0_gyro = usart6::read() * 2;
  
  while(true)
  {
    locator360.getData();
    ball_angle = locator360.getAngle();
    ball_signal = locator360.getDistance();
    if(stop_motors == 1)
      motors.moveMotor(0);
    else
      if(role == 0) // atacker
      {
        
      }
      else if(role == 1) // defender
      {
      
      }
  }
}
