import sensor, utime, image, time, pyb, math #import librares

EXPOSURE_TIME_SCALE = 0.75

green_threshold = [(0, 84, -128, -4, -128, 127)] #threshold of green part of game field
yellow_threshold = [(49, 100, -128, 127, 36, 127)] #yellow gates threshold
blue_threshold = [(3, 96, -119, 116, -128, -37)] #blue gates threshold    (6, 86, -114, 109, -128, -17)
black_threshold = [(0, 100, -128, 127, 2, 16)]
out_threshold = [(26, 100, -128, 127, -128, 9)]

center = [193, 130] #calculating image center 170, 115   193, 130

uart = pyb.UART(3, 115200, timeout = 100, timeout_char = 100)
uart.init(115200, bits=8, parity=False, stop=1, timeout_char=100) #initialize UART

led3 = pyb.LED(2)


sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_auto_gain(True)
sensor.set_auto_whitebal(True)
sensor.set_auto_exposure(True)
current_exposure_time_in_microseconds =  sensor.get_exposure_us()
sensor.set_auto_exposure(True, \
    exposure_us = int(current_exposure_time_in_microseconds* EXPOSURE_TIME_SCALE))
clock = time.clock()
sensor.skip_frames(time = 500)

#sensor.reset() #reset camera
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_auto_exposure(False)
current_exposure_time_in_microseconds =  sensor.get_exposure_us()
sensor.set_auto_exposure(False, \
    exposure_us = int(current_exposure_time_in_microseconds* EXPOSURE_TIME_SCALE))
#sensor.set_gainceiling(2)
clock = time.clock()
sensor.skip_frames(time = 1000) #delay

image_height = sensor.height() #get image framesize
image_width = sensor.width()

data = 1 #output data

blue_v = 0
yellow_v = 0

yellow = [0]*6
blue = [0]*6
old_area = 0

distance = [[],
            [],
            [],
            [],
            [],
            [],
            []]

clock = time.clock()

def get_distance(x, y):
    return math.sqrt(math.pow(x, 2) + math.pow(y, 2))

def linearize(num):
    i = 0
    for mas in distance:
        err = num - mas[1]
        if abs(old_err) > abs(err):
            i += 1
        else:
            break
        old_err = err

    return distance[0][i]

def crc8(data, len):
    crc = 0xFF
    j = 0
    for i in range(0, len):
        crc = crc ^ data[i];
        for j in range(0, 8):
            if (crc & 0x80):
                crc = (crc << 1) ^ 0x31
            else:
             crc = crc << 1
    return crc

def send_data(num1, num2, num3, num4):

    uart.writechar(255)

    if num1 + 127 > 253:
       data[0] = 253
    elif num1 + 127 < 0:
       data[0] = 0
    else:
       data[0] = num1 + 127

    if num2 + 127 > 253:
       data[1] = 253
    elif num2 + 127 < 0:
       data[1] = 0
    else:
       data[1] = num2 + 127

    if num3 + 127 > 253:
       data[2] = 253
    elif num3 + 127 < 0:
       data[2] = 0
    else:
       data[2] = num3 + 127

    if num4 + 127 > 253:
       data[3] = 253
    elif num4 + 127 < 0:
       data[3] = 0
    else:
       data[3] = num4 + 127

    data[4] = crc8(data, 4)

    uart.writechar(int(data[0]))
    uart.writechar(int(data[1]))
    uart.writechar(int(data[2]))
    uart.writechar(int(data[3]))
    uart.writechar(int(data[4]))


while(True):
   clock.tick()
    #print(utime.ticks_ms())
    if utime.ticks_ms() - a > 350:
        led3.on()
        a = utime.ticks_ms()
    else:
        led3.off()
    blue_v = 0
    yellow_v = 0
    img = sensor.snapshot().mask_circle(center[0], center[1] + 5, 130)#.binary(green_threshold, zero=True)#.binary(black_threshold, zero=True) #get corrected image
    old_area = 60
    #detecting yellow gate
    for blob in img.find_blobs(yellow_threshold, merge = True, margin = 20):
        if(blob[2] * blob[3] > old_area):
            yellow_v = 1
            old_area = blob[2] * blob[3]
            img.draw_rectangle(blob[0], blob[1], blob[2], blob[3], (200, 200, 0), 2)
            yellow = [blob[0], blob[1], blob[0] + blob[2], blob[1] + blob[3], int(blob[0] + abs(blob[2]/2)), int(blob[1] +  abs(blob[3]/2))]
    if(old_area < 100):
        yellow[4] = blue[4]
        if back() == "y":
            yellow[5] = 230
        else:
            yellow[5] = 20
    old_area = 60
    #detecting blue gate
    for blob in img.find_blobs(blue_threshold, merge = True, margin = 20):
        if(blob[2] * blob[3] > old_area):
            blue_v = 1
            old_area = blob[2] * blob[3]
            img.draw_rectangle(blob[0], blob[1], blob[2], blob[3], (0, 0, 200), 2)
            blue = [blob[0], blob[1], blob[0] + blob[2], blob[1] + blob[3], int(blob[0] + abs(blob[2]/2)),int(blob[1] +  abs(blob[3]/2))]
    if(old_area < 100):
        blue[4] = yellow[4]
        if back() == "y":
            blue[5] = 20
        else:
            blue[5] = 230
    old_area = 20
    img.draw_line(center[0], center[1], center[0] - dist, center[1], (255, 255, 255), 2)
    img.draw_line(yellow[4], yellow[5], blue[4], blue[5], (255, 255, 255), 2) #line between centers of gates

    yellow_x = yellow[4] - center[0]
    yellow_y = yellow[5] - center[1]
    yellow_distance = linearize(get_distance(yellow_x, yellow_y))
    yellow_angle = math.floor(math.atan2(yellow_y, yellow_x) * 57.8)

    blue_x = blue[4] - center[0]
    blue_y = blue[5] - center[1]
    blue_distance = linearize(get_distance(blue_x, blue_y))
    blue_angle = math.floor(math.atan2(blue_y, blue_x) * 57.8)

    send_data(yellow_distance, yellow_angle, blue_distance, blue_angle)



