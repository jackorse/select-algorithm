import matplotlib.pyplot as plt
import json

data = json.load(open("out.json"))

name = []
cpu_time_rand = []
cpu_time_rand_worst = []
cpu_time_qsort = []
cpu_time = []
for b in data["benchmarks"]:
  if "BigO" in b["name"] or "RMS" in b["name"]:
    continue
  if "BM_Rand_Selection_WorstCase" in b["name"]:
    cpu_time_rand_worst.append(b['cpu_time'])
  elif "BM_Rand_Selection" in b["name"]:
    cpu_time_rand.append(b['cpu_time'])
  elif "BM_Qsort_Selection" in b["name"]:
     cpu_time_qsort.append(b['cpu_time'])
  else:
     name.append(int(b['name'].split("/")[1]))
     cpu_time.append(b['cpu_time'])

if cpu_time_rand_worst == []:
  plt.plot(name, cpu_time)
  plt.plot(name, cpu_time_rand)
  plt.plot(name, cpu_time_qsort)

  plt.xlabel("Num elements")
  plt.ylabel("Time [ns]")
  plt.legend(["Deterministic", "Random", "Qsort (naive)"])
  plt.title('Complexities')

else:

  fig, axis = plt.subplots(1, 2)
  fig.set_figwidth(20)

  axis[0].plot(name, cpu_time)
  axis[0].plot(name, cpu_time_rand)
  axis[0].plot(name, cpu_time_qsort)
  axis[0].plot(name, cpu_time_rand_worst)

  axis[0].set_xlabel("Num elements")
  axis[0].set_ylabel("Time [ns]")
  axis[0].legend(["Deterministic", "Random", "Qsort (naive)", "Random (Worst)"])
  axis[0].set_title('Complexities')


  plt.subplots_adjust(left=0.1,
                      bottom=0.1,
                      right=0.75,
                      top=0.9,
                      wspace=0.2,
                      hspace=0.4)

  axis[1].plot(name, cpu_time)
  axis[1].plot(name, cpu_time_rand)
  axis[1].plot(name, cpu_time_qsort)


  axis[1].set_xlabel("Num elements")
  axis[1].set_ylabel("Time [ns]")
  axis[1].legend(["Deterministic", "Random", "Qsort (naive)"])
  axis[1].set_title('Complexities')

plt.show()
