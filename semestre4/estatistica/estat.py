import numpy as np
import scipy.stats as binom
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

plt.title("Frequência absoluta da amostra $\it{vs.}$ Frequência esperada pela distribuição binomial", size=12, weight='bold')

# plt.title("Frequência absoluta da amostra", size=12, weight='bold')

plt.ylabel("Frequência de notebooks defeituosos", size=10)
plt.xlabel("Número de notebooks defeituosos", size=10)


bins=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
# plt.hist(x, bins, edgecolor='black', linewidth=1, align='mid')
plt.hist(x, bins, edgecolor='black', linewidth=1, density=True, align='mid', label='Frequência obtida da amostra')

n=20
p=0.2045

y = np.arange(-1, 11)
# x_values = numpy.linspace(lower, upper, n_points)
plt.plot(np.linspace(-0.5, 10.5, len(y)), binom.binom.pmf(y, n, p), color='red', linestyle='steps-mid', label='Frequência esperada (dist. binomial)')
# plt.plot(y, binom.binom.pmf(y, n, p), color='red', linestyle='steps-mid', label='Frequência esperada (dist. binomial)')


plt.legend(fontsize=10)
plt.show()
