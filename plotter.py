import matplotlib.pyplot as plt
import math
import csv
  
x = []
y = []
  
with open('test_output/data1.csv','r') as csvfile:
    lines = csv.reader(csvfile, delimiter=',')
    for row in lines:
        val = int(row[0])*math.log(int(row[0]))   # Problema 1
        #val = int(row[0])*int(row[0])             # Problema 2
        x.append(val)
        y.append(int(row[1]))
  
plt.plot(x, y, color = 'g', linestyle = 'dashed',
         marker = 'o')
  
plt.xticks(rotation = 25)
plt.xlabel('Tamanho do input')
plt.ylabel('Tempo(microsegundos)')
#plt.title('', fontsize = 20)
plt.grid()
plt.legend()
plt.savefig('problema1.png')