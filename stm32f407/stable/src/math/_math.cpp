#include "_math.h"

Math::Math()
{

}
	
int32_t Math::map(int32_t num, int32_t min1, int32_t max1, int32_t min2, int32_t max2)
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

int32_t Math::calculate_hypotenuse(int32_t cathet1, int32_t cathet2)
{
	cathet1 = my_abs(cathet1);
	cathet2 = my_abs(cathet2);
	
	sub = sqrt(double(pow(double(cathet1), 2) + pow(double(cathet2), 2)));
	return int32_t(sub);
}

int32_t Math::calculate_cathet(int32_t hypotenuse, int32_t cathet1)
{
	hypotenuse = my_abs(hypotenuse);
	cathet1 = my_abs(cathet1);
	
	sub = sqrt(double(pow(double(hypotenuse), 2) + pow(double(cathet1), 2)));
	return int32_t(sub);
}

int32_t Math::lead_to_degree_range(int32_t num, int32_t min, int32_t max)
{
	if(max < min) {sub = max; max = min; min = sub;}
	
	sub = max - min;
	if(num < min)
		 num += sub;
	else if(num > max)
		 num -= sub;	
}

int32_t Math::my_abs(int32_t num)
{
	return int32_t(abs(double(num)));
}
	