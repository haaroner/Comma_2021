#include "my_math.h"
#include "math.h"

my_Math::my_Math()
{

}
	
int32_t my_Math::map(int32_t num, int32_t min1, int32_t max1, int32_t min2, int32_t max2)
{
	if(max1 < min1) {sub = max1; max1 = min1; min1 = sub;}
	if(max2 < min2) {sub = max2; max2 = min2; min2 = sub;}
	
	map_range1 = max1 - min1;
	map_range2 = max2 - min2;
	map_range_k = my_abs(map_range2 / map_range1);
	map_range_difference = min2 - min1;
	
	sub = num * map_range_k + map_range_difference;
	return int32_t(sub);
}

int32_t my_Math::my_abs(int32_t num)
{
  if(num < 0) num *= -1;
	return num;
}

int32_t my_Math::calculate_hypotenuse(int32_t cathet1, int32_t cathet2)
{
	cathet1 = my_abs(cathet1);
	cathet2 = my_abs(cathet2);
	
	sub = sqrt(double(pow(double(cathet1), 2) + pow(double(cathet2), 2)));
	return int32_t(sub);
}

int32_t my_Math::calculate_cathet(int32_t hypotenuse, int32_t cathet1)
{
	hypotenuse = my_abs(hypotenuse);
	cathet1 = my_abs(cathet1);
	
	sub = sqrt(double(pow(double(hypotenuse), 2) + pow(double(cathet1), 2)));
	return int32_t(sub);
}

int32_t my_Math::lead_to_degree_range(int32_t num, int32_t min, int32_t max)
{
	if(max < min) {sub = max; max = min; min = sub;}
	
	sub = max - min;
	if(num < min)
		 num += sub;
	else if(num > max)
		 num -= sub;
	return num;
}

int32_t my_Math::leed_to_range(int32_t num, int32_t min, int32_t max)
{
	if(max < min) {sub = max; max = min; min = sub;}
	
	if(num > max) num = max;
	else if(num < max) num = min;
	
	return num;
}

int32_t my_Math::vectors_with_general_point_sum_angle(int32_t _angle1, int32_t _angle2, int32_t _length1, int32_t &_length2)
{
  vector_x1 = sin(double(_angle1) / 57.3) * _length1;
  vector_y1 = cos(double(_angle1) / 57.3) * _length1;
  
  vector_x2 = sin(double(_angle2 / 57.3)) * _length2;
  vector_y2 = cos(double(_angle2 / 57.3)) * _length2;
  
  vector_x = vector_x1 + vector_x2;
  vector_y = vector_y1 + vector_y2;
  
  vector_length = my_Math::calculate_hypotenuse(vector_x, vector_y);
  
  _length2 = vector_length;
  
  vector_angle = acos(double(vector_y / vector_length)) * 57.3;
  return vector_angle;
}

int32_t my_Math::vectors_with_general_point_sum_num(int32_t _x1, int32_t _x2, int32_t _y1, int32_t &_y2)
{
  vector_x1 = _x1;
  vector_y1 = _y1;
  
  vector_x2 = _x2;
  vector_y2 = _y2;
  
  vector_angle_1 = atan2(double(vector_x1), double(vector_y1)) * 57.3;
  vector_angle_2 = atan2(double(vector_x2), double(vector_y2)) * 57.3;
  
  vector_x = vector_x1 + vector_x2;
  vector_y = vector_y1 + vector_y2;
  
  vector_length = my_Math::calculate_hypotenuse(vector_x, vector_y);
  
  _y2 = vector_length;
  
  vector_angle = acos(double(vector_y / vector_length)) * 57.3;
  return vector_angle;
}

int32_t my_Math::vector_with_angle_sum(int32_t& _x1, int32_t& _y1, int32_t _angle)
{
  vector_x1 = _x1;
  vector_y1 = _y1;
  
  vector_length = my_Math::calculate_hypotenuse(vector_x1, vector_y1);
  
  vector_angle_1 = atan2(double(vector_x1), double(vector_y1)) * 57.3;
  
  vector_angle = vector_angle_1 + _angle;
  
  vector_x = sin(double(vector_angle) / 57.3) * vector_length;
  vector_y = cos(double(vector_angle) / 57.3) * vector_length;
  
  return vector_angle;
}
	