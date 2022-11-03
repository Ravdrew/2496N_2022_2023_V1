from posixpath import split
import matplotlib.pyplot as plt

f = open("C:/Users/Erick/Documents/GitHub/2496N_2022_2023_V1/src/flyvals.txt", "r", encoding='utf-16')

times = []
curr_speeds = []
ema_results = []
dema_results = []
outputs = []
voltages = []

for line in f:
    split_content = line.split(" ")
    split_content = [float(i) for i in split_content]
    #print(split_content)
    times.append(split_content[0])
    curr_speeds.append(split_content[1])
    ema_results.append(split_content[2])
    dema_results.append(split_content[3])
    outputs.append(split_content[4])
    voltages.append(split_content[5]/100)

plt.xlabel('Time')
plt.ylabel('Flywheel Speed in RPM')
plt.plot(times, curr_speeds, color ='red', label ='Current Speed')
plt.plot(times, ema_results, color ='blue', label ='EMA')
plt.plot(times, dema_results, color ='green', label = 'DEMA')
plt.plot(times, outputs, color ='yellow', label ='Outputs')
plt.plot(times, voltages, color = 'orange', label = 'Voltage/100')

plt.legend()
plt.show()