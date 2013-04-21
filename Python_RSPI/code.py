#!/usr/bin/env python

import serial
import time
ser = serial.Serial("/dev/ttyACM0",9600)

flag=True

while(flag)
	#start
	ser.write("0")
	time.sleep(1)

	#Digital Write
	ser.write("1")
	time.sleep(1)
	
	#DDR
	ser.write("1")
	time.sleep(1)
	
	#PORT
	ser.write("1")
	time.sleep(1)
	
	#start
	ser.write("0")
	time.sleep(1)

	#Digital Write
	ser.write("1")
	time.sleep(1)
	
	#DDR
	ser.write("1")
	time.sleep(1)
	
	#PORT
	ser.write("0")
	time.sleep(1)
	