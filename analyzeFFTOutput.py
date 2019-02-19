import serial
import numpy as np
import matplotlib.pyplot as plt
import peakutils as pu

# https://tonescope.net/tone
# round(logspace(log10(start),log10(stop),12))

size = 1024


ser = serial.Serial('COM5',512000)
ser.readline()
maxIndex = int(size/2)
data = np.zeros(size, dtype=int)

dataIn = ser.readline()
dataSplit = dataIn.decode().split(",")

for d in range(0, size):
    l = int(dataSplit[d])
    data[d] = int(l)

searchData = data[:maxIndex]

maxValue = np.max(searchData)
maxIndex = np.argmax(searchData)

print(f"Value: {maxValue}, Index: {maxIndex}")

##peaks = pu.indexes(data, thres=0.4, min_dist=10)
##print(peaks)

##plt.plot(data[peaks], marker='o', ls="", ms=3)
plt.plot(data)
plt.show()

ser.close()
