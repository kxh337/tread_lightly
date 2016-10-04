import serial
import sys
import time

port = "/dev/ttyACM0"
baudrate = 9600

ser = serial.Serial(port, baudrate, timeout = 2)

if len(sys.argv) == 3:
    cmd = sys.argv[1]
    data = sys.argv[2]

time.sleep(1);

intcmd = int(cmd)
chrcmd = chr(intcmd)
intdata = int(data) 
chrdata = chr(intdata)

send = bytearray(2)
send[0] = chrcmd
send[1] = chrdata

if(ser.isOpen()):
	ser.write(send)
	

time.sleep(0.1)
print ser.read(2)

ser.close()
