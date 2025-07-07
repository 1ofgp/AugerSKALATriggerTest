import serial
import time

counter = 0
ser = serial.Serial('/dev/ttyACM0', 115200)

while True:
    data = ser.read()
    counter = counter +1
    print(counter, time.time_ns())
