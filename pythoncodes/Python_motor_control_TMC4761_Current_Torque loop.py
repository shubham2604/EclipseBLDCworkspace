# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import serial 
import ctypes
import time

ser = serial.Serial()
ser.port = 'COM4'
ser.baudrate = 256000
ser.open()
flag = 0
speed = ctypes.c_int16(3000).value
while 1:
    if(speed==-3000):
        speed = 3000
    speed = speed - 1
    x = ser.read(4)
    enc = x[0]<<24 | x[1]<<16 | x[2]<< 8 | x[3] 
    print(ctypes.c_int32(enc).value * 0.00137329101) 
    if(speed):
        packet = speed.to_bytes(2, byteorder='big', signed=True)
        #print(packet)
        #ser.write(packet)
    time.sleep(0.01)