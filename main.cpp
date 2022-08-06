#include "project_config.h"
#include "pin_setup.h"
#include "time_service.h"
#include "adc.h"
#include "dma.h"
#include "usart6.h"
#include "usart3.h"
#include "soft_i2c.h"
#include "IRLocator.h"
#include "Motor_Pin.h"
#include "motor.h"
#include "motors.h"
#include "OpenMV.h"
#include "line_sensors.h"
#include "dist_sen.h"

#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4
int main()

{
	volatile int dop = 0;
	volatile bool change_role = false, dist_state = false, line_data[4] = {0, 0, 0, 0}, out_side_en = false, out_side = false, go_zone = 0, stop = 0, gate_color = 0,
	line_zone[4] = {0, 0, 0, 0}, side_kick = false, gyro_reset_en = false, side_kick_en = false, kick_en = false, kick_over_time_en = false;
	
	volatile uint8_t state = 0, dist, seeker_state = 0, role = 0, old_role = 0, 
		new_role = 0, u = 0;
	
	volatile int16_t gyro = 0, start_gyro = 0, seeker = 0, x0_gyro = 0,
		 locator_offset = 0, sign = 1, last_robot_x = 0, 
		 robot_x = 0, last_robot_y = 0, robot_y = 0, forward_goal_degree = 0,
		 backward_goal_degree = 0, goal_atan = 0, state_ob = 0, gate_dist = 0;
	
	volatile uint32_t sub = 0, kick_over_time = 0, out_side_tim = 0, a,
	 kick_tim = 0, gyro_reset_tim = 0, change_role_tim = 0, side_kick_tim = 0,
	 line_tim[4] = {0, 0, 0, 0}, camera_tim[4] = {0, 0, 0, 0}, go_tim = 0, time = 0,
	 dist_state_tim = 0;
	
	volatile int e_gyro = 0, p_angle, move_seeker = 0, u_angle = 0, move_angle = 0, k_angle = 30, e_gate = 0, k_gate = 0, p_gate = 0, x0_back_gate = 180, x0_forward_gate = 0, 
		move_gate = 0, speed_seeker = 3095, speed_angle = 1000, ring = 0, move_x = 0, move_y = 0;
	
	volatile float e_seeker = 0, p_seeker = 0, i_seeker = 0, pi_seeker = 0, k_seeker = 1,
		ki_seeker, x0_seeker = 0, i_angle = 0, ki_angle = 0.25, actual_dist = 0, 
		k_seeker_change = 1, k_angle_change = 0.999, last_dist = 0, 
		robot_pos_change = 1, dist_change = 0.999;
	volatile char back_gate;
	
	Motor m1(GPIOE,//without
					 GPIO_Pin_5,
					 GPIO_PinSource5,
					 GPIO_AF_TIM9,
					 GPIOE,
					 GPIO_Pin_6,
					 GPIO_PinSource6,
					 GPIO_AF_TIM9);
	
	m1.motorPWMInit(RCC_APB2ENR_TIM9EN,
									CHANNEL1,
									TIM9,
									RCC_APB2ENR_TIM9EN,
									CHANNEL2,
									TIM9);//without
	
	Motor m2(GPIOB,//green
					 GPIO_Pin_5,
					 GPIO_PinSource5,
					 GPIO_AF_TIM3, 
					 GPIOB,
					 GPIO_Pin_3,
					 GPIO_PinSource3,
					 GPIO_AF_TIM2);
								
	m2.motorPWMInit(RCC_APB1ENR_TIM3EN,
									CHANNEL2,
									TIM3,
									RCC_APB1ENR_TIM2EN,
									CHANNEL2,
									TIM2);//green
	
	Motor m3(GPIOA,//white
					 GPIO_Pin_0,
					 GPIO_PinSource0,
					 GPIO_AF_TIM2, 
					 GPIOA,
					 GPIO_Pin_1,
					 GPIO_PinSource1,
					 GPIO_AF_TIM5);
					 
	m3.motorPWMInit(RCC_APB1ENR_TIM2EN,
									CHANNEL1,
									TIM2,
									RCC_APB1ENR_TIM5EN,
									CHANNEL2,
									TIM5);
	
	Motor m4(GPIOE,//blue 
					 GPIO_Pin_11,
					 GPIO_PinSource11,
					 GPIO_AF_TIM1, 
					 GPIOE,
					 GPIO_Pin_13,
					 GPIO_PinSource13,
					 GPIO_AF_TIM1);
					 
	m4.motorPWMInit(RCC_APB2ENR_TIM1EN,
									CHANNEL2,
									TIM1,
									RCC_APB2ENR_TIM1EN,
									CHANNEL3,
									TIM1); //blue 
									
	pin usart6_tx(GPIOC,//without
							  GPIO_Pin_6,
							  GPIO_Mode_AF,
							  GPIO_Speed_100MHz,
							  GPIO_OType_PP,
							  GPIO_PuPd_NOPULL,
							  GPIO_PinSource6,
							  GPIO_AF_USART6);
	usart6_tx.pinInit();
	
	pin usart6_rx(GPIOC,
								GPIO_Pin_7,
								GPIO_Mode_AF,
								GPIO_Speed_100MHz,
								GPIO_OType_PP,
								GPIO_PuPd_NOPULL,
								GPIO_PinSource7,
								GPIO_AF_USART6);
	usart6_rx.pinInit();
	
	pin usart3_tx(GPIOB,//without
								GPIO_Pin_10,
								GPIO_Mode_AF,
								GPIO_Speed_100MHz,
								GPIO_OType_PP,
								GPIO_PuPd_NOPULL,
								GPIO_PinSource10,
								GPIO_AF_USART3);
	usart3_tx.pinInit();
	
	pin usart3_rx(GPIOB,
								GPIO_Pin_11,
								GPIO_Mode_AF,
								GPIO_Speed_100MHz,
								GPIO_OType_PP,
								GPIO_PuPd_NOPULL,
								GPIO_PinSource11,
								GPIO_AF_USART3);
	usart3_rx.pinInit();
	
	pin i2c3_scl(GPIOA,//without
							 GPIO_Pin_8,
							 GPIO_Mode_OUT,
							 GPIO_Speed_100MHz,
							 GPIO_OType_OD,
							 GPIO_PuPd_UP,
							 GPIO_PinSource8,
							 GPIO_AF_I2C3);
	i2c3_scl.pinInit();
	
	pin i2c3_sda(GPIOC,
							 GPIO_Pin_9,
							 GPIO_Mode_OUT,
							 GPIO_Speed_100MHz,
							 GPIO_OType_OD,
							 GPIO_PuPd_UP,
							 GPIO_PinSource9,
							 GPIO_AF_I2C3);	
	i2c3_sda.pinInit();	
	
	pin role_sw(GPIOB,
                GPIO_Pin_13,
                GPIO_Mode_IN,
                GPIO_Speed_100MHz,
                GPIO_OType_OD,
                GPIO_PuPd_UP,
                GPIO_PinSource13,
                GPIO_AF_I2C3);
	role_sw.pinInit();
	

	pin line_1(GPIOD,
                GPIO_Pin_6,
                GPIO_Mode_OUT,
                GPIO_Speed_100MHz,
                GPIO_OType_OD,
                GPIO_PuPd_UP,
                GPIO_PinSource6,
                GPIO_AF_I2C3);
	line_1.pinInit();
	
	pin line_2(GPIOD,
                GPIO_Pin_4,
                GPIO_Mode_OUT,
                GPIO_Speed_100MHz,
                GPIO_OType_OD,
                GPIO_PuPd_UP,
                GPIO_PinSource4,
                GPIO_AF_I2C3);
	line_2.pinInit();
	
	pin line_3(GPIOD,
                GPIO_Pin_2,
                GPIO_Mode_OUT,
                GPIO_Speed_100MHz,
                GPIO_OType_OD,
                GPIO_PuPd_UP,
                GPIO_PinSource2,
                GPIO_AF_I2C3);
	line_3.pinInit();
	
	pin line_4(GPIOD,
                GPIO_Pin_0,
                GPIO_Mode_OUT,
                GPIO_Speed_100MHz,
                GPIO_OType_OD,
                GPIO_PuPd_UP,
                GPIO_PinSource0,
                GPIO_AF_I2C3);
	line_4.pinInit();
	
	pin line_callibrate(GPIOD,
                GPIO_Pin_9,
                GPIO_Mode_OUT,
                GPIO_Speed_100MHz,
                GPIO_OType_OD,
                GPIO_PuPd_UP,
                GPIO_PinSource9,
                GPIO_AF_I2C3);
	line_callibrate.pinInit();
	
//	pin line_reader(GPIOB,
//                GPIO_Pin_0,
//                GPIO_Mode_AN,
//                GPIO_Speed_100MHz,
//                GPIO_OType_OD,
//                GPIO_PuPd_NOPULL,
//                GPIO_PinSource0,
//                GPIO_AF_I2C3);
//	line_reader.pinInit();

	pin motors_move(GPIOB,
                GPIO_Pin_1,
                GPIO_Mode_IN,
                GPIO_Speed_100MHz,
                GPIO_OType_PP,
                GPIO_PuPd_UP,
                GPIO_PinSource1,
                GPIO_AF_I2C3);
	motors_move.pinInit();
	
	pin gyro_reset(GPIOB,
                GPIO_Pin_0,
                GPIO_Mode_IN,
                GPIO_Speed_100MHz,
                GPIO_OType_PP,
                GPIO_PuPd_UP,
                GPIO_PinSource0,
                GPIO_AF_I2C3);
	gyro_reset.pinInit();
	
//	pin distR(GPIOB,//!!!change settings!!! #Frog 
//                GPIO_Pin_0,
//                GPIO_Mode_AN,
//                GPIO_Speed_100MHz,
//                GPIO_OType_OD,
//                GPIO_PuPd_NOPULL,
//                GPIO_PinSource0,
//                GPIO_AF_I2C3);
//	distR.pinInit(); 
	soft_i2c ir(i2c3_scl, i2c3_sda);
	IRlocator locator360(ir, 0x0E);
	usart6::usart6Init();
	usart3::usart3Init();
	camera camera(usart3_tx, usart3_rx);
	
	motors motors(m1, m2, m3, m4);
//	Adc line_signal(ADC1, 1, 0, ADC_Channel_9, RCC_APB2Periph_ADC1, distL);
//	line_signal.sendMeChannel(ADC_Channel_9);
//	Dma lineDma(RCC_AHB1Periph_DMA2, line_signal);
//	lineDma.dmaInit(DMA2_Stream0, DMA_Channel_0, 1);
//	lineDma.adcInitInDma();
	//line line(line_1, line_2, line_3, line_4, line_callibrate, lineDma);
	time_service::init();
	time_service::delay_ms(30000); 
	role = 0; // changing role------------------------------------
	x0_gyro = usart6::read() * 2;
	robot_x = 0;//camera.get_x()* 0.1 + last_robot_x * 0.9;
	last_robot_x = camera.get_x();
	robot_y = 0;//camera.get_y() * 0.1 + last_robot_y * 0.9;
	//time_service::delay_ms(5000);
	//usart6::available();
//motors.moveMotors(2000,2000,2000,2000);

//dma for dist
//	Adc adcL(ADC1, 1, 0, ADC_Channel_8, RCC_APB2Periph_ADC1, distL);
//	adcL.sendMeChannel(ADC_Channel_8);
//	Dma dmaL(RCC_AHB1Periph_DMA2, adcL);

//	Adc adcR(ADC1, 1, 0, ADC_Channel_8, RCC_APB2Periph_ADC1, distR);
//	adcL.sendMeChannel(ADC_Channel_8);
//	Dma dmaR(RCC_AHB1Periph_DMA2, adcL);//!!!change settings!!! #Frog 
	
	//dist_sen dist_sen(dmaL,dmaR,e_gyro);

	while(true)
	{
//		line_1.resetBit();
//		line_2.resetBit();
//		line_3.resetBit();
//		line_4.resetBit();
		time = time_service::getCurTime();
		
		gyro = usart6::read() * 2;
		
		camera.getData();
		robot_x = camera.get_x() * robot_pos_change + last_robot_x * (1 - robot_pos_change);
		last_robot_x = camera.get_x();
		robot_y = camera.get_y() * robot_pos_change + last_robot_y * (1 - robot_pos_change);
		last_robot_y = camera.get_y();
		//sub = lineDma.dataReturn(0);
		if(robot_x == 0)
			robot_x = 1;
		if(robot_y == 0)
			robot_y = 1;
		
		gate_dist = sqrt(double(robot_x * robot_x) + double(robot_y * robot_y));
		if(robot_y < 0)
		{
			backward_goal_degree = atan2(abs(double(robot_y)), double(robot_x)) * 57.3;
			gate_dist = sqrt(double(robot_x * robot_x) + double(robot_y * robot_y));
			if(backward_goal_degree > 90)
				x0_back_gate = (180 - backward_goal_degree) + 270;
			else
				x0_back_gate = (90 - backward_goal_degree);
			}
		else
		{
			forward_goal_degree = atan2(abs(double(robot_y)), double(robot_x)) * 57.3;
			if(forward_goal_degree > 90)
				x0_forward_gate = forward_goal_degree - 90;
			else
				x0_forward_gate = 360 - (90 - forward_goal_degree);
		}
		
		
		dist = locator360.getData(0x07);
		actual_dist = dist * dist_change + last_dist * (1 - dist_change);
		last_dist = dist;
		if(dist < 10)
		{
			seeker = locator360.getData(0x04) * 5;
			seeker_state = 1;
			if(time - dist_state_tim > 500)
				dist_state = false;
		}
		else
		{
			dist_state = true;
			dist_state_tim = time;
			seeker = locator360.getData(0x06) * 5;
			seeker_state = 0;
		}
		
		if((robot_x < -15 && robot_x > 15/* && dist_sen.getDataR(500)*/))
			 {
				 if(out_side != true)
					  out_side_tim = time;
				 out_side = true;
				 if(time - out_side_tim > 50)
					 out_side_en = true;
				 else
					 out_side_en = false;
			 }
			 else
			 {
				 out_side = false;
				 out_side_tim = time;
			 }
		
		if((gyro_reset.getGPIOx()->IDR & gyro_reset.getPinNumber()) == true)
		{
			if(gyro_reset_en == false)
				gyro_reset_tim = time;
			gyro_reset_en = true;
			if(time - gyro_reset_tim > 500)
				x0_gyro = gyro;
		}
		else
		{
			gyro_reset_en = false;
			gyro_reset_tim = time;
		}
		//line_data[0], line_data[1], line_data[2], line_data[3] = line.getData();
//		for(int i = 0; i < 4; i++)
//		{
//			if(line_data[i] == 0)
//				line_tim[i] = 0;
//			else 
//				line_tim[i] = time_service::getCurTime();
//		}
		//motors.moveRobot(2095, 0, e_seeker, 0);
	
// new_role = !(role_sw.getGPIOx()->IDR & role_sw.getPinNumber());
//        if(new_role != role)
//        {
//            if(change_role == false)
//            {
//                change_role = true;
//                a = time_service::getCurTime();
//            }
//            else
//            {
//                if(time_service::getCurTime() - a > 10)
//                {
//                    role = new_role;
//                    change_role = false;
//                }
//            }
//        }
				
		if(role == 0)
		{
			if(old_role == 1 && time - change_role_tim > (650 + 180 * kick_over_time_en))
			{
				role = 1;
				old_role = 0;
			}
			if (old_role == 1 && gate_dist < 100 && robot_y > 0)
			{
				role = 1;
				old_role = 0;
			}
			if(abs(double(robot_x)) < 25)
			{
				if((seeker < (25 + locator_offset)) || (seeker > 330 + locator_offset))
				{
					state = 0;
					if(robot_x > 15)
						x0_seeker = 15;
					else if(robot_x < -15)
						x0_seeker = 345;
					else
						x0_seeker = 0;
					if(old_role == 1)
						speed_seeker = 4000;
					else
						speed_seeker = 3950;
				}
				else
				{
					state = 1;
					kick_over_time_en = true;
					x0_seeker = 0;
					state_ob = 0;
					speed_seeker = 3950;
				}
			}
			else
			{
				e_gate = x0_forward_gate - seeker;
				
				e_gate = seeker - x0_seeker;
				if(e_gate < -180)
				 e_gate += 360;
				else if(e_gate > 180)
				 e_gate -= 360;	
				
				if(x0_forward_gate > 35 && x0_forward_gate < 180)
					x0_forward_gate = 30;
				else if(x0_forward_gate < 325 && x0_forward_gate > 180)
					x0_forward_gate = 330;
				if(robot_x > 25)
					{
						if(abs(double(e_gate)) > 20)
						{
							state = 1;
							kick_over_time_en = true;
							x0_seeker = x0_forward_gate;
							speed_seeker = 3950;
	//						if(robot_x > 70 && seeker > 135 && seeker < 225)
	//						  x0_seeker = 45;
						}
						else
						{
							state = 0;
							x0_seeker = x0_forward_gate;
							speed_seeker = 3950;
						}
				}
				else if(robot_x < -25)
				{
					if(abs(double(e_gate)) > 20)
					{
						state = 1;
						kick_over_time_en = true;
						x0_seeker = x0_forward_gate;
						speed_seeker = 3950;
	//					if(robot_x < -70 && seeker > 135 && seeker < 225)
	//						x0_seeker = 315;
					}
					else
					{
						state = 0;
						x0_seeker = x0_forward_gate;
						speed_seeker = 3950;
					}
				}
				else
				{
					state = 0;
					if(robot_x > 0)
						x0_seeker = x0_forward_gate;
					else
						x0_seeker = x0_forward_gate;
					speed_seeker = 3950;
				}
			}
			if(state == 0)
			{
			 e_seeker = seeker - x0_seeker - e_gyro;
		
			 if(e_seeker < -180)
				 e_seeker += 360;
			 else if(e_seeker > 180)
				 e_seeker -= 360;	
		
			 p_seeker = e_seeker * k_seeker;
	 
			 u = p_seeker;
			}
			else if(state == 1)
			{
//				if((seeker >= 25 + locator_offset && seeker <= 75 + locator_offset) || (seeker <= 335 + locator_offset && seeker >= 285 + locator_offset))
//			{
//				if( seeker > 180 + locator_offset)
//					x0_seeker = 75 + locator_offset;
//				else
//					x0_seeker = 285 + locator_offset;
//			}
//			else
//			{
//				if( seeker > 180 + locator_offset)
//					x0_seeker = 90 + locator_offset;
//				else
//					x0_seeker = 270 + locator_offset;
//			}
			if(dist_state == true)
			{		
				e_seeker = seeker - x0_seeker;
				if(e_seeker < -180)
				 e_seeker += 360;
				else if(e_seeker > 180)
				 e_seeker -= 360;	
				
				if(e_seeker > 0)
				{
					p_seeker = seeker + 90;
				}
				else
				{
					p_seeker = seeker - 90;
				}
				
				if(p_seeker < -180)
				 p_seeker += 360;
				else if(p_seeker > 180)
				 p_seeker -= 360;	
//				if(state_ob == 0)
//				{
//					if(seeker <= 180)
//						p_seeker = seeker + 90;
//					else
//						p_seeker = seeker - 90;
//				}
//				else
//				{
//					if(state_ob < 180 && state_ob > seeker)
//						p_seeker = seeker - 90;
//					else if(state_ob > 180 && state_ob < seeker)
//						p_seeker = seeker + 90;
//				}
//				if(robot_x > 50 && abs(double(robot_y)) > 110 && seeker < 270 && seeker > 90)
//					{
//						p_seeker = seeker + 90;
//					}
//					else if(robot_x < -50  && abs(double(robot_y)) > 110  && seeker < 270 && seeker > 90)
//					{
//						p_seeker = seeker - 90;
//					}	
//				speed_seeker = 3600;
			}
			else
			{
				e_seeker = seeker - e_gyro;
		
			 if(e_seeker < -180)
				 e_seeker += 360;
			 else if(e_seeker > 180)
				 e_seeker -= 360;	
		
			 p_seeker = e_seeker * k_seeker;
	 
			 u = p_seeker;
			}
		}
//			if(abs(double(e_seeker)) < 10)
//				speed_seeker = 3980;
			
			 e_gyro = x0_gyro - gyro;
			 
			 if(e_gyro < -180)
				e_gyro += 360;
			 else if(e_gyro > 180)
				e_gyro -= 360;
			 
			 p_angle = e_gyro * k_angle;
				
			 if(i_angle <= 300 && i_angle >= -300)
			 {
				 i_angle += e_gyro * ki_angle;
			 }
			 else 
			 {
				 if(i_angle > 300)
					i_angle = 300;
				 else
					 i_angle = -300;
			 }
			 u_angle = p_angle + i_angle;
					
//			 if((line_tim[0] > 10 && (seeker > 270 || seeker < 90)) || (line_tim[1] > 10 && seeker > 0 && seeker < 180) ||
//				 (line_tim[2] > 10 && seeker > 90 && seeker < 270) || (line_tim[3] > 10 && seeker > 180 && seeker < 355))
//				 stop = 1;
//			 else
//				 stop = 0;
			 stop = 0;
			 if(old_role == 1)
				 speed_seeker = 4000;
			  if((((robot_x < -46 && gate_dist > 110) || (robot_x < -52 && gate_dist < 110)) && ((seeker > 105 || seeker < 10) || (p_seeker > 180))/* && dist_sen.getDataR(500)*/))
			 {
				 if(line_zone[0] != true)
					  camera_tim[0] = time;
				 line_zone[0] = true;
				 if(time - camera_tim[0] > 1)
				 {
					 p_seeker = 90;
					 speed_seeker = 3750;
				 }
//					 while(time - camera_tim[0] < 750 && seeker > 180 && seeker < 360 &&
//							 robot_x < -75)
//						 {
//							 time = time_service::getCurTime();
//							 speed_seeker = 3100; 
//							 p_seeker = 90;
//							 gyro = usart6::read() * 2;
//							 e_gyro = x0_gyro - gyro;
//				 
//							 if(e_gyro < -180)
//								e_gyro += 360;
//							 else if(e_gyro > 180)
//								e_gyro -= 360;
//						
//								p_angle = e_gyro * k_angle;	
//								motors.moveRobot(speed_seeker, 1000, p_seeker, p_angle);
//						 }
			 }
			 else
			 {
				 line_zone[0] = false;
			 }
			 if(((robot_x > 45 && gate_dist > 110) || (robot_x > 55 && gate_dist < 110)) && ((seeker < 255 || seeker > 350) || (p_seeker < 180))/* && dist_sen.getDataL(500)*/)
			 {
				 if(line_zone[1] != true)
					  camera_tim[1] = time;
				 line_zone[1] = true;
				 if(time - camera_tim[1] > 1)
				 {
					 p_seeker = 270;
					 speed_seeker = 3750;
				 }
//					 while(time - camera_tim[1] < 750 && seeker < 180 && seeker > 0 &&
//							 robot_x > 75)
//						 {
//							 time = time_service::getCurTime();
//							 speed_seeker = 3100; 
//							 p_seeker = 270;
//							 gyro = usart6::read() * 2;
//							 e_gyro = x0_gyro - gyro;
//				 
//							 if(e_gyro < -180)
//								e_gyro += 360;
//							 else if(e_gyro > 180)
//								e_gyro -= 360;
//						
//								p_angle = e_gyro * k_angle;	
//								motors.moveRobot(speed_seeker, 1000, p_seeker, p_angle);
//						 }
			 }
			 else
			 {
				 line_zone[1] = false;
				 camera_tim[1] = time;
			 }
			 if((gate_dist < 90 && abs(double(robot_x < 15)) && robot_y > 0) || (gate_dist < 86 && abs(double(robot_x > 15)) && robot_y > 0) ||
				 (gate_dist < 79 && abs(double(robot_x < 15)) && robot_y < 0) || (gate_dist < 84 && abs(double(robot_x > 15)) && robot_y < 0))
			 {
					if(robot_y > 0)
							p_seeker = x0_forward_gate + 180;
					else
					{
						if(seeker < 100 || seeker > 260)
							p_seeker = seeker;
						else
						{
							if(seeker > 15 && seeker < 180)
								p_seeker = 45;
							else if(seeker < 345 && seeker > 180)
							p_seeker = backward_goal_degree;
						}
					}
					
					if(p_seeker > 360)
						 p_seeker -= 360;	
					speed_seeker = 3800;
			 }
			 else
			 {
				 line_zone[2] = false;
				 camera_tim[2] = time;
			 }
			 if(abs(double(robot_y)) < 76)
			 {
				 if(line_zone[3] != true)
					  camera_tim[3] = time;
				 line_zone[3] = true;
				 if(time - camera_tim[3] > 1)
				 {
					 if(robot_y > 0)
						 p_seeker = 180;
					 else
							p_seeker = 0;
					 speed_seeker = 3750;
				 }
			 }
			 else
			 {
				 line_zone[3] = false;
				 camera_tim[3] = time;
			 }
//			 if(robot_y <= 0 && robot_y > -80
//				 /*seeker > 90 && seeker < 270*/)
//			 {
//				 if(line_zone[3] != true)
//					  camera_tim[3] = time;
//				 line_zone[3] = true;
//				  if(time - camera_tim[3] > 30)
//						p_seeker = 0;
				//}
//					 while(time - camera_tim[3] < 750 &&
//						 robot_y <= 0 && robot_y > -90)
//					 {
//						 time = time_service::getCurTime();
//						 speed_seeker = 3100; 
//						 p_seeker = 0;
//						 gyro = usart6::read() * 2;
//						 e_gyro = x0_gyro - gyro;
//			 
//						 if(e_gyro < -180)
//							e_gyro += 360;
//						 else if(e_gyro > 180)
//							e_gyro -= 360;
//					
//							p_angle = e_gyro * k_angle;	
//						  motors.moveRobot(speed_seeker, 1000, p_seeker, p_angle);
//					 }
//			 else
//			 {
//				 line_zone[3] = false;
//				 camera_tim[3] = time;
//			 }
			 
			 if(gate_dist < 100)
				 speed_seeker = 3920; 
			 
			 if(p_seeker < -180)
				 p_seeker += 360;
			 else if(p_seeker > 180)
				 p_seeker -= 360;	
			  
			 move_seeker = p_seeker * k_seeker_change + move_seeker * (1 - k_seeker_change);
			 move_angle = u_angle * k_angle_change + move_angle * (1 - k_angle_change);
			 
			 if(seeker == 1275)
				motors.moveRobot(0, 1000, 0, u_angle * 3);
			 else
				motors.moveRobot(speed_seeker, 1000, move_seeker, move_angle);
			 
			
		}
		else if(role == 1)
		{
			speed_seeker = 3950;
			
			e_seeker = seeker - x0_back_gate/* - e_gyro*/;
		
			if(e_seeker < -180)
				e_seeker += 360;
			else if(e_seeker > 180)
				e_seeker -= 360;	
			
		if(e_seeker > 10)
		{
			if(x0_back_gate < 180)
			{
				p_seeker = x0_back_gate + 90;
				if(gate_dist > 81)
					p_seeker += 10;
				else if(gate_dist < 79)
					p_seeker -= 10;
			}
			else
			{
				p_seeker = x0_back_gate + 90;
				if(gate_dist > 81)
					p_seeker += 10;
				else if(gate_dist < 79)
					p_seeker -= 10;
			}
			if(x0_back_gate > 45 && x0_back_gate < 180)
				speed_seeker = 0;
			
			if(seeker < 225 && seeker > 135)
				speed_seeker = 0;
			
			if(robot_x > 50)
				speed_seeker = 0;
		}
		else if(e_seeker < -10)
		{
			if(x0_back_gate > 180)
			{
				p_seeker = x0_back_gate - 90;
				if(gate_dist > 81)
					p_seeker -= 0;
				else if(gate_dist < 79)
					p_seeker += 0;
			}
			else	
			{
				p_seeker = x0_back_gate - 90;
				if(gate_dist > 81)
					p_seeker -= 0;
				else if(gate_dist < 79)
					p_seeker += 0;
			}
			if(x0_back_gate < 225 && x0_back_gate > 135	)
				speed_seeker = 0;
			
			if(seeker < 270 && seeker > 90)
				speed_seeker = 0;
			
			if(robot_x < -50)
				speed_seeker = 0;
		}	
		else
			speed_seeker = 0;
		
		if((dist_state == true || sub > 50) && (seeker < 45 || seeker > 315))
		{
			if(kick_en == false)
					kick_tim = time;
			kick_en = true;
			if(time - kick_tim > 3500 && time - kick_tim < 6500)
			{
				role = 0;
				change_role_tim = time;
				old_role = 1;
				forward_goal_degree = 0;
				kick_over_time_en = false;
				p_seeker = seeker;
			}
			if(old_role == 0)
			{
				kick_en = false;
				kick_tim = time;
				old_role = 1;
				while(time - kick_tim < 1500 && (gate_dist > 103))
				{
					camera.getData();
					robot_x = camera.get_x() * robot_pos_change + last_robot_x * (1 - robot_pos_change);
					last_robot_x = camera.get_x();
					robot_y = camera.get_y() * robot_pos_change + last_robot_y * (1 - robot_pos_change);
					last_robot_y = camera.get_y();
					
					gate_dist = sqrt(double(robot_x * robot_x) + double(robot_y * robot_y));
					
					time = time_service::getCurTime();
					speed_seeker = 3850;
									
					p_seeker = 180;
					gyro = usart6::read() * 2;
					e_gyro = x0_gyro - gyro;
					 
					if(e_gyro < -180)
						e_gyro += 360;
					else if(e_gyro > 180)
						e_gyro -= 360;
						
					p_angle = e_gyro * k_angle;	
					motors.moveRobot(speed_seeker, 1000, p_seeker, p_angle);
				}
			}
		}
		else
		{
			kick_tim = time;
		}
				//if(seeker_state == 0)
				//{
//				 if(go_zone != true)
//					  go_tim = time;
//				 go_zone = true;
//				 if(time - go_tim > 2000 && time - go_tim < 6000)
//				 {
//					 frog = true;
//					 p_seeker = 0;
//					 speed_seeker = 3000; 
//			 }
//			 else
//			 {
//				 go_zone = false;
//				 go_tim = time;
//				 frog = false;
					//p_seeker = 0;
					//speed_seeker = 3200;
			 //}			 
			if(gate_dist > 82 || robot_y > 0)
			 {
				 if(line_zone[3] != true)
					  camera_tim[3] = time;
				 line_zone[3] = true;
				 if(time - camera_tim[3] > 30)
				 {
					 p_seeker = 180;
					 speed_seeker = 3100;
				 }
			 }
			 else
			 {
				 line_zone[3] = false;
				 camera_tim[3] = time;
			 }
			if(gate_dist < 77)
			{
				if(line_zone[2] != true)
					camera_tim[2] = time;
				line_zone[2] = true;
				if(time - camera_tim[2] > 10)
				{
				  p_seeker = 0;
					speed_seeker = 3100;
				}
			}
			else
			{
				line_zone[2] = false;
				camera_tim[2] = time;
			}
			
			
			if(robot_y > -70 && robot_y < 0)
			{
				if(robot_x > 30)
					p_seeker = 315;
				else if(robot_x < -30)
					p_seeker = 45;
				else
				p_seeker = 0;
				speed_seeker = 3300;
			}
			
			if(robot_y < -90 || robot_y > 0)
			{
				p_seeker = 180;
				speed_seeker = 3100;
			}
//	1222222222			 speed_seeker = 0;
//			}
//			}

//			
			 
//			if(robot_y <= 0 && robot_y > -75
//				 /*seeker > 90 && seeker < 270*/)
//			 {
//				 if(line_zone[3] != true)
//					  camera_tim[3] = time;
//				 line_zone[3] = true;
//				  if(time - camera_tim[3] > 30)
//					{
//					 p_seeker = 0;
//					 speed_seeker = 3100;
//					}
//			 }
//			 else
//			 {
//				 line_zone[3] = false;
//				 camera_tim[3] = time;
//			 }
//			 if(seeker_state == 1)
//			 {
//			 if(robot_y <= 0 && robot_y < -90
//				 /*seeker > 90 && seeker < 270*/)
//			 {
//				 if(line_zone[2] != true)
//					  camera_tim[2] = time;
//				 line_zone[2] = true;
//				  if(time - camera_tim[2] > 30)
//					{
//					 p_seeker = 180;
//					 speed_seeker = 3100;
//					}
//				}
//			 else
//			 {
//				 line_zone[2] = false;
//				 camera_tim[2] = time;
//			 }
//		 }
//			 if(seeker_state == 0)
//			 {
//			 if(robot_y <= 0 && robot_y < -75
//				 /*seeker > 90 && seeker < 270*/)
//			 {
//				 if(line_zone[2] != true)
//					  camera_tim[2] = time;
//				 line_zone[2] = true;
//				  if(time - camera_tim[2] > 30)
//					{
//					 p_seeker = 180;
//					 speed_seeker = 3100;
//					}
//				}
//			 else
//			 {
//				 line_zone[2] = false;
//				 camera_tim[2] = time;
//			 }
//		 }

			if(p_seeker < -180)
				p_seeker += 360;
			 else if(p_seeker > 180)
				p_seeker -= 360;

			 e_gyro = x0_gyro - gyro;
			 
			 if(e_gyro < -180)
				e_gyro += 360;
			 else if(e_gyro > 180)
				e_gyro -= 360;
		
			  p_angle = e_gyro * k_angle;	
			  if(seeker == 1275)
					motors.moveRobot(0, 850, 0, p_angle * 3);
				else
					motors.moveRobot(speed_seeker, 750, p_seeker, p_angle);
		}	
	}
}


/*
if(dist > 110 && robot_y >= 0 && robot_y < 80 && abs(double(robot_x)) > 40)
					{
						if(side_kick == false)
						{
							side_kick_tim = time;
							side_kick = true;
						}
						else
						{
							if(time - side_kick_tim > 500 && time - side_kick_tim < 1500)
							{
								if(forward_goal_degree > 25)
								{
									x0_gyro = start_gyro - 20;
									side_kick_en = true;
								}
								else if(forward_goal_degree < -25)
								{
									x0_gyro = start_gyro + 20;
									side_kick_en = true;
								}
								else 
								{
									x0_gyro = start_gyro;
									side_kick_en = true;
								}
								
								if(x0_gyro < 0)
									x0_gyro = 360 + x0_gyro;
								else if(x0_gyro > 359)
									x0_gyro = x0_gyro - 360;
							}
							else if(time - side_kick_tim > 1500 && time - side_kick_tim < 4000)
							{
								x0_gyro = start_gyro;
							}
							else if(time - side_kick_tim > 4000)
							{
								side_kick = false;
								side_kick_en = false;
							}
						}
					}
					if(seeker_state == 0)
			{
				if(kick_en == false)
					kick_tim = time;
				kick_tim = true;
				if(time - kick_tim > 2500 && time - kick_tim < 5000)
					p_seeker = x0_seeker;
				else if(time - kick_tim > 5000)
					*/