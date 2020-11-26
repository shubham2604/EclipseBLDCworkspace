# -*- coding: utf-8 -*-
"""
Created on Thu Nov 26 00:31:25 2020

@author: Shubham
"""

import serial 
import ctypes
import time
import threading

ser = serial.Serial()
ser.port = 'COM4'
ser.baudrate = 256000
ser.open()

def position_loop():
    while 1:
        if(time.time()%25 == 0):
            ser.flush()
        x = ser.read(4)
        enc = x[0]<<24 | x[1]<<16 | x[2]<< 8 | x[3] 
        print(ctypes.c_int32(enc).value * 0.00137329101) 
        #time.sleep(0.0001)    
    return


if __name__ == '__main__':
    p = threading.Thread(target=position_loop)
    p.start()
    while 1:
        position = ctypes.c_int32(int((float(input())/0.00137329101))).value
        packet = position.to_bytes(4, byteorder='big', signed=True)
        ser.write(packet)