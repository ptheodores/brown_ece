import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams["figure.figsize"] = [8.50, 3.50]
plt.rcParams["figure.autolayout"] = True

data = pd.read_csv("plot_data.txt")

out = data.pivot(index='interval', values='hitrate', columns='name').plot()
out.set_ylabel("hit rate")
out.set_xlabel("")

plt.legend(bbox_to_anchor=(0.25, 1.0))
plt.show()
