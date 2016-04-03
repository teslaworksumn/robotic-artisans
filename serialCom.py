#use python 2.7
import serial

ser = serial.Serial('/dev/ttyUSB0') #opens the serial port

print(ser.name) #checks which port was actually used
file = open('Bash/angle.gcode','r')
for line in file:
    #line = line.replace("\n","")
    splitLine= line.split(" ")
    ser.write(splitLine[2]+" "+splitLine[4]+" "+splitLine[6])
ser.close()
