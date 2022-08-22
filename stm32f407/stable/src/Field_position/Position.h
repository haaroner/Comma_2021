#pragma once

#include "project_config.h"
#include "math.h"

class Position
{
  public:
    Position();
    void calculate_position(int32_t _x1, int32_t _y1, int32_t _x2, int32_t _y2);
    int32_t robot_x();
    int32_t robot_y();
    uint16_t forward_goal_degree();
    uint16_t backward_goal_degree();
    uint16_t forward_goal_distance();
    uint16_t backward_goal_distance();
  private:
    
};