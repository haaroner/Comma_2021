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
#include "my_math.h"

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
	volatile int dop = 0;
	volatile bool change_role = false, dist_state = false, line_data[4] = {0, 0, 0, 0}, out_side_en = false, out_side = false, go_zone = 0, stop = 0, gate_color = 0,
	line_zone[4] = {0, 0, 0, 0}, side_kick = false, gyro_reset_en = false, side_kick_en = false, kick_en = false, kick_over_time_en = false;
	
	volatile uint8_t state = 0, dist, seeker_state = 0, role = 0, old_role = 0, 
		new_role = 0, u = 0;
	
	volatile int16_t gyro = 0, start_gyro = 0, seeker = 0, x0_gyro = 0,
		 locator_offset = 0, sign = 1, last_robot_x = 0, 
		 robot_x = 0, last_robot_y = 0, robot_y = 0, forward_goal_degree = 0,
		 backward_goal_degree = 0, goal_atan = 0, state_ob = 0, gate_dist = 0, gate_position[4] = {0, 0, 0, 0};
	
	volatile uint32_t sub = 0, kick_over_time = 0, out_side_tim = 0, a,
	 kick_tim = 0, gyro_reset_tim = 0, change_role_tim = 0, side_kick_tim = 0,
	 line_tim[4] = {0, 0, 0, 0}, camera_tim[4] = {0, 0, 0, 0}, go_tim = 0, time = 0,
	 dist_state_tim = 0;
	
	volatile int e_gyro = 0, p_angle, move_seeker = 0, u_angle = 0, move_angle = 0, k_angle = 25, e_gate = 0, k_gate = 0, p_gate = 0, x0_back_gate = 180, x0_forward_gate = 0, 
		move_gate = 0, speed_seeker = 3095, speed_angle = 1000, ring = 0, move_x = 0, move_y = 0;
	
	volatile float e_seeker = 0, p_seeker = 0, i_seeker = 0, pi_seeker = 0, k_seeker = 1,
		ki_seeker, x0_seeker = 0, i_angle = 0, ki_angle = 0.25, actual_dist = 0, 
		k_seeker_change = 1, k_angle_change = 0.999, last_dist = 0, 
		robot_pos_change = 1, dist_change = 0.999;
	volatile char back_gate;
  
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
  my_Math my_math;

	while(true)
	{
		time = time_service::getCurTime();
		
		gyro = usart6::read() * 2;
		
		camera.getData();
		//gate_dist = sqrt(double(robot_x * robot_x) + double(robot_y * robot_y));
		gate_dist = my_math.calculate_hypotenuse(robot_x, robot_y);
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
		
		if(robot_x < -15 && robot_x > 15)
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
	
		if(role == 0)
		{
			if(old_role == 1 && time - change_role_tim > (650 + 180 * kick_over_time_en))
			{
				role = 1;
				old_role = 0;
			}
			if(old_role == 1 && gate_dist < 100 && robot_y > 0)
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
				}
				else
				{
					state = 1;
					kick_over_time_en = true;
					x0_seeker = 0;
					state_ob = 0;
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
				//e_gate = my_math.lead_to_degree_range(e_gate, -180, 180);
				
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
					}
					else
					{
						state = 0;
						x0_seeker = x0_forward_gate;
					}
				}
				else if(robot_x < -25)
				{
					if(abs(double(e_gate)) > 20)
					{
						state = 1;
						kick_over_time_en = true;
						x0_seeker = x0_forward_gate;
					}
					else
					{
						state = 0;
						x0_seeker = x0_forward_gate;
					}
				}
				else
				{
					state = 0;
					if(robot_x > 0)
						x0_seeker = x0_forward_gate;
					else
						x0_seeker = x0_forward_gate;
				}
			}
			if(state == 0)
			{
				e_seeker = seeker - x0_seeker - e_gyro;
		
			 if(e_seeker < -180)
				 e_seeker += 360;
			 else if(e_seeker > 180)
				 e_seeker -= 360;	
				//e_seeker = my_math.lead_to_degree_range(e_seeker, -180, 180);
		
				p_seeker = e_seeker * k_seeker;
	 
				u = p_seeker;
			}
			else if(state == 1)
			{
				if(dist_state == true)
				{		
					e_seeker = seeker - x0_seeker;
					if(e_seeker < -180)
					 e_seeker += 360;
					else if(e_seeker > 180)
					 e_seeker -= 360;	
					//e_seeker = my_math.lead_to_degree_range(e_seeker, -180, 180);
					
					if(e_seeker > 0)
						p_seeker = seeker + 90;
					else
						p_seeker = seeker - 90;
					
					if(p_seeker < -180)
					 p_seeker += 360;
					else if(p_seeker > 180)
					 p_seeker -= 360;	
					//p_seeker = my_math.lead_to_degree_range(p_seeker, -180, 180);
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
				 //e_seeker = my_math.lead_to_degree_range(e_seeker, -180, 180);
					
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
			//e_gyro = my_math.lead_to_degree_range(e_gyro, -180, 180);
			 
			p_angle = e_gyro * k_angle;
				
			if(i_angle <= 300 && i_angle >= -300)
				i_angle += e_gyro * ki_angle;
			else 
			{
				if(i_angle > 300)
					i_angle = 300;
				else
					i_angle = -300;
			}
			u_angle = p_angle + i_angle;
					
			stop = 0;
			if((((robot_x < -46 && gate_dist > 110) || (robot_x < -52 && gate_dist < 110)) && ((seeker > 105 || seeker < 10) || (p_seeker > 180))/* && dist_sen.getDataR(500)*/))
			{
				if(line_zone[0] != true)
					camera_tim[0] = time;
				line_zone[0] = true;
				if(time - camera_tim[0] > 1)
				{
					p_seeker = 90;
				}
			}
			else
				line_zone[0] = false;
		
			if(((robot_x > 45 && gate_dist > 110) || (robot_x > 55 && gate_dist < 110)) && ((seeker < 255 || seeker > 350) || (p_seeker < 180))/* && dist_sen.getDataL(500)*/)
			{
				if(line_zone[1] != true)
					camera_tim[1] = time;
				line_zone[1] = true;
				if(time - camera_tim[1] > 1)
				{
					p_seeker = 270;
				}
			}
			else
				line_zone[1] = false;
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
				}
			}
			else
				line_zone[3] = false;
			 
//			if(gate_dist < 100)
//				speed_seeker = 3920; 
			 
//			if(p_seeker < -180)
//				p_seeker += 360;
//			else if(p_seeker > 180)
//				p_seeker -= 360;	\
			  
			move_seeker = p_seeker * k_seeker_change + move_seeker * (1 - k_seeker_change);
			move_angle = u_angle * k_angle_change + move_angle * (1 - k_angle_change);
			if(seeker < 180)
			{
				e_seeker = seeker - 90;
				p_seeker = 90 + e_seeker ;
			}
			if(old_role == 1)
				speed_seeker = 2900;
			else 
			{
				speed_seeker = 2750;
			}
			
			if(stop_move)
			 motors.moveMotor(0);
			else
			{
				if(seeker == 1275)
					motors.moveRobot(0, 1000, 0, p_angle * 3, time);
				else
					motors.moveRobot(speed_seeker, 1000, p_seeker, p_angle, time);
			}			 
		}
		else if(role == 1)//goalkeeper
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
						//robot position!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					
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
						
						if(stop_move)
							motors.moveMotor(0);
						else
							motors.moveRobot(speed_seeker, 1000, p_seeker, p_angle, time);
					}			 
				}
			}
			else
				kick_tim = time;
		
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
				motors.moveRobot(0, 850, 0, p_angle * 3, time);
			else
				motors.moveRobot(speed_seeker, 750, p_seeker, p_angle, time);
		}	
	}
}
