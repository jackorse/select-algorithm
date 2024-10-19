import matplotlib.pyplot as plt
import json

data = json.load(open("out.json"))

name = []
cpu_time_rand = []
cpu_time_qsort = []
cpu_time = []
for b in data["benchmarks"]:
  if "BigO" in b["name"] or "RMS" in b["name"]:
    continue
  if "BM_Rand_Selection" in b["name"]:
    name.append(int(b['name'].split("/")[1]))
    cpu_time_rand.append(b['cpu_time'])
  elif "BM_Qsort_Selection" in b["name"]:
     cpu_time_qsort.append(b['cpu_time'])
  else:
     cpu_time.append(b['cpu_time'])

plt.plot(name, cpu_time)
plt.plot(name, cpu_time_rand)
plt.plot(name, cpu_time_qsort)

plt.xlabel("Num elements")
plt.ylabel("Time [ns]")
plt.legend(["Deterministic", "Random", "Qsort (naive)"])
plt.title('Complexities')
plt.show()