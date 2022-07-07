#!/usr/bin/env python3
import serial

arduino_port = "/dev/ttyACM0"
baud = 9600
fileName="uno-data.csv"

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "w")
print("Created file")

samples = 10 #how many samples to collect
print_labels = True
line = 0 #start at 0 because our header is 0 (not real data)
while line <= samples:
    # incoming = ser.read(9999)
    # if len(incoming) > 0:
    if print_labels:
        if line==0:
            print("Methane PPM, Visible, IR, UV, CO2, CO PPM:")
            file.write("Methane PPM, Visible, IR, UV, CO2, CO PPM:" + "\n")
        else:
            print("Line " + str(line) + ": writing...")
    getData=str(ser.readline())
    data=getData[0:][:-2]
    print(data)

    #file = open(fileName, "a")
    file.write(data + "\n") #write data with a newline
    line = line+1

print("Data collection complete!")
file.close()