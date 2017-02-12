#use python 2.7
import serial
import time


ser = serial.Serial('/dev/ttyUSB0',baudrate=9600) #opens the serial port
#http://elinux.org/Serial_port_programming
def readlineCR(port):
    rv = ""
    while True:
        ch = port.read()
        rv += ch
        if ch=='\r' or ch=='':
            return rv

print(ser.name) #checks which port was actually used
file = open('Bash/angle.gcode','r')
for line in file:
	
    #line = line.replace("\n","")
    #if(ser.outWaiting() > 0 ):
        #ser.reset_out()
    splitLine= line.split(" ")
    #print readlineCR(ser)
    
    ser.write(splitLine[2]+" "+splitLine[4]+" "+splitLine[6])
    print splitLine[2]+" "+splitLine[4]+" "+splitLine[6]
	print ord(ser.read(1))
    
  
ser.close()



