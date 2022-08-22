//#pragma once

#include "project_config.h"

class my_Math
{
	public:
		my_Math();
		int32_t map(int32_t num, int32_t min1, int32_t max1, int32_t min2, int32_t max2);
		int32_t my_abs(int32_t num);
		int32_t calculate_hypotenuse(int32_t cathet1, int32_t cathet2);
		int32_t calculate_cathet(int32_t hypotenuse, int32_t cathet1);
		int32_t lead_to_degree_range(int32_t num, int32_t min, int32_t max);
		int32_t leed_to_range(int32_t num, int32_t min, int32_t max);
	private:
		int32_t map_range1;
		int32_t map_range2;
		int32_t map_range_k;
		int32_t map_range_difference;
		int32_t sub;
};