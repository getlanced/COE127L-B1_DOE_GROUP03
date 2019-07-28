import matplotlib.pyplot as plt
import csv

data = []
with open('graphDat.csv','r') as f:
    reader = csv.reader(f,delimiter= ',')
    for line in reader:
        data.append(line)

data1 = []
for i in range(1,len(data)):
    data1.append(data[i][1])

data2 = []
for i in range (1,len(data)):
    data2.append(data[i][2])

data3 = []    
for i in range (1,len(data)):
    data3.append(data[i][3])

#set plot
plt.plot(data2,data1,'.r-',label ='Setup Time')

plt.plot(data2,data3,'.b-',label = 'Performance Time')

#set label
plt.xlabel('No. of Lines')
plt.ylabel('Time Taken (s)')
plt.legend()
plt.show()
