import pygame
import serial
import time
import math

#
pygame.init()
pygame.joystick.init()
js = pygame.joystick.Joystick(0)
js.init()


print(js.get_numaxes())
print(js.get_numbuttons())
print(js.get_name())
print(js.get_init())

ser = serial.Serial('/dev/ttyUSB0',baudrate=9600) #opens the serial port
print(ser.name)#prints out the serial name

while(True):
	pygame.event.get()
	time.sleep(.8)
	s=""
	if(js.get_axis(0) <= 0.25): 
		s += str(20*int(math.floor(js.get_axis(0))))+' '
	else:
		s+='20 '
	if(js.get_axis(1) <= 0.25): 
		s += str(20* int(math.floor(js.get_axis(1))))+' '
	else:
		s+='20 '
	s+=str(20*js.get_hat(0)[1])+'\n'  
	#s = str(js.get_axis(0))+" "+str(js.get_axis(1))+" "+str(js.get_hat(0)[1])
	print(s)
	ser.write(s)
