import matplotlib.pyplot as plt
plt.figure(figsize=[8.5,5])

plt.style.use('bmh')

x = [0,0,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,
     2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
     3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
     3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
     4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,
     5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
     5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
     6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,9]


line_props = dict(color='black', alpha=1)
bbox_props = dict(color='black', alpha=0.9, linestyle="dashdot")
flier_props = dict(marker="o", markersize=5)

plt.ylabel("Unidades defeituosas")

plt.title("Quantidade de notebooks defeituosos observados em 200 lotes com 20 objetos")
plt.boxplot(x, patch_artist=True, labels=["Notebooks"], whiskerprops=line_props, boxprops=bbox_props, flierprops=flier_props)
plt.show()