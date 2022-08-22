#include "Position.h"

Position::Position()
{
}
int32_t Position::calculate_pos()
{
  //to understand this part of program you need to found my picture and Georgy Ezhelev, 
  //that can explain you how does it works 
  cathetx_f_b = _x1 - _x2;
  cathety_f_b = _y1 - _y2;//calculating cathets of yellow - blue triangle
  
  if(cathetx_f_b == 0 )
  {
    robot_x = _x1; //if x cordinate is equal in each gates
    robot_y = my_math.my_abs(_y2);
  }
  else if(cathety_f_b == 0)
  {
    robot_x = _y2;
    robot_y = _x2; //if x cordinate is equal in each gates
  }
  else
  {
    hyp_f_b = my_math.calculate_hypotenuse(cathetx_f_b, cathety_f_b);
    hyp_b_c = my_math.calculate_hypotenuse(_x1, _y1);
    
    if(cathetx_f_b < 0)
    {
      a1_f_b = asin(double(cathety_f_b / hyp_f_b)) * 57.3;
      a2_fb_c = acos(double(_y2 / hyp_b_c)) * 57.3;
      a3_f_b_c = a1_f_b - a2_fb_c;
      robot_x = sin(double(a3_f_b_c) / 57.3) * hyp_b_c;
      robot_y = my_math.calculate_cathet(hyp_b_c, robot_x);
    }
    else
    {
      //write thiiiiiiiiiiiiiisS
    }
  }
}

void Position::calculate_data(int32_t* data, uint16_t _angle)
{
  //collectind data of gate position
  _x1 = data[0];
  _y1 = data[1];
  _x2 = data[2];
  _y2 = data[3];
  
  //correcting position of gate using gyro angle(see class my_Math)
  my_math.vector_with_angle_sum(_x1, _y1, _angle);
  my_math.vector_with_angle_sum(_x2, _y2, _angle);
  
  Position::calculate_pos();
}