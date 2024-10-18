import pandas as pd
import matplotlib.pyplot as plt
import json
%matplotlib inline


data = json.load(open("out.json"))
bench = data["benchmarks"][: len(data["benchmarks"]) - 2]

name = [int(i['name'].split("/")[1]) for i in bench]
cpu_time = [i['cpu_time'] for i in bench]

print(name)
print(cpu_time)

df = pd.DataFrame({'name':name, 'cpu_time':cpu_time})


plt.plot(name, cpu_time)
