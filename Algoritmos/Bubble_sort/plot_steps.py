"""
Este script nos permite graficar el contenido de bubble_steps.txt, un archivo que contiene los pasos que le toma al bubble sort
para ordenar listas de diferentes tamaños que contienen elementos al azar (de 0 a 100).
@author: Víctor B
@date: 25/03/2023
"""

import numpy as np
import matplotlib.pyplot as plt

# Se cargan los archivos en una variable steps, desde el path actual
steps = np.loadtxt('bubble_steps.txt')

plt.plot(range(0,101),steps, label="Número de pasos")
plt.title("La gráfica del rendimiento de Bubble Sort.")
plt.legend()
plt.ylabel("Pasos")
plt.xlabel("Elementos en la lista")
plt.show()