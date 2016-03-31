import pandas as pd

file = pd.read_csv("phase.txt",header=None,sep=" ")
res = []
for i in range(0,len(file)):
    if file[2][i] == 0 and file[3][i] == 0: res.append(0)
    elif file[3][i] == 0: res.append(1)
    else: res.append(2)
print res