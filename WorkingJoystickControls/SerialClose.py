import serial

ser = serial.Serial('/dev/ttyUSB0',baudrate=9600) #opens the serial port
print(ser.name) #checks which port was actually used
ser.close()
