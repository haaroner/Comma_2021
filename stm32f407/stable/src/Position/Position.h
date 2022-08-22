#pragma once

#include "Project_config.h"
#include "math.h"
#include "my_math.h"

class Position
{
  public:
    Position();
    void calculate_data(int32_t* data, uint16_t _angle);
    int32_t robot_x;
    int32_t robot_y;
    uint16_t forward_goal_angle;
    uint16_t backward_goal_angle;
    uint16_t forward_goal_dist;
    uint16_t backward_goal_dist;
  private:
    int32_t _x1, _y1, _x2, _y2;
    int32_t cathety_f_b, cathetx_f_b, hyp_f_b; //sides of triangle of forward-backward goals
    int32_t cathety_f_c, cathetx_f_c, hyp_f_c; //sides of triangle of forward-center 
    int32_t cathety_b_c, cathetx_b_c, hyp_b_c; //sides of triangle of backward-center 
    uint16_t a1_f_b, a2_fb_c, a3_f_b_c;
    int32_t data[4];
    my_Math my_math;
    int32_t calculate_pos();
};
