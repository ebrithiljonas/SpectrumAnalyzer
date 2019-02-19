import serial
import numpy as np
import matplotlib.pyplot as plt

# https://mynoise.net/NoiseMachines/whiteNoiseGenerator.php

size = 12
repeat = 500


ser = serial.Serial('COM5',512000)
ser.readline()
data = np.zeros((repeat,size), dtype=int)

for i in range(0, repeat):

    print(f"Sample: {i}")

    dataIn = ser.readline()
    dataSplit = dataIn.decode().split(",")

    for d in range(0, size):
        l = int(dataSplit[d])
        
        data[i,d] = int(l)

        
mean = np.mean(data, axis = 0)
print(mean)
print("New Factors:")
print(np.array2string(mean, separator=', ', precision=2))

ser.close()
