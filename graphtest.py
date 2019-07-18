import matplotlib.pyplot as plt
import pandas as pd


#set directory
df=pd.read_excel('graphdata.xlsx','Sheet1')
#set plot
plt.bar(df['Time Take: Processing'],df['Time Taken: Map Fill'])


#set label
plt.xlabel('Time Taken: Map Fill')
plt.ylabel('Time Take: Processing')
plt.title('Time Take: Processing vs Time Taken: Map Fill Graph')


plt.show()

