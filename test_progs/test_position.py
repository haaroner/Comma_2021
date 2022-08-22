import math

sign = 1

def my_abs(num):
  if(num < 0): num *= -1
  return num


def calculate_hypotenuse(cathet1, cathet2):
    cathet1 = my_abs(cathet1)
    cathet2 = my_abs(cathet2)
	
    sub = math.sqrt(pow(cathet1, 2) + pow(cathet2, 2))
    return int(sub)

def calculate_cathet(hypotenuse, cathet1):
	hypotenuse = my_abs(hypotenuse)
	cathet1 = my_abs(cathet1)
	
	sub = math.sqrt(pow(hypotenuse, 2) + pow(cathet1, 2))
	return int(sub)

def calculate_pos():    
    _x1 = -25
    _y1 = 20
    _x2 = -20
    _y2 = -100

    robot_x = 0
    robot_y = 0



    cathetx_f_b = _x1 - _x2
    cathety_f_b = _y1 - _y2 #calculating cathets of yellow - blue triangle

    if(_x1 < 0 and _x2 < 0):
        sign = -1
        cathetx_f_b = my_abs(cathetx_f_b)
        cathety_f_b = my_abs(cathety_f_b)
        _x1 = my_abs(_x1)
        _y1 = my_abs(_y1)
        _x2 = my_abs(_x2)
        _y2 = my_abs(_y2)
    else: sign = 1
  
    if(cathetx_f_b == 0 ):
        robot_x = -_x1 #if x cordinate is equal in each gates
        robot_y = my_abs(_y2)
        
    elif(cathety_f_b == 0):
        robot_x = _y2
        robot_y = _x2 #if x cordinate is equal in each gates
    else:
        hyp_f_b = calculate_hypotenuse(cathetx_f_b, cathety_f_b)
        hyp_b_c = calculate_hypotenuse(_x2, _y2)
        if(cathetx_f_b < 0):
            a1_f_b = math.asin(my_abs(cathetx_f_b / hyp_f_b)) * 57.3#error
            a2_fb_c = math.acos(my_abs(_y2 / hyp_b_c)) * 57.3
            a3_f_b_c = a1_f_b - a2_fb_c
            print(a1_f_b, a2_fb_c, a3_f_b_c);
            robot_x = math.sin(a3_f_b_c / 57.3) * hyp_b_c
            robot_y = calculate_cathet(hyp_b_c, robot_x)
    return robot_x, robot_y

robot_x, robot_y = calculate_pos()
print("x =", robot_x * sign, " y =", robot_y)   

