"""
Este script nos permite graficar el contenido de todos los archivos steps.txt. Con ello, podremos comparar 
el comportamiento de los diversos algoritmos de ordenamiento y cuánto les toma ordenar listas de diferentes tamaños que continenen elementos al azar (de 0 a 100).
@author: Víctor B
@date: 25/03/2023
"""

import numpy as np
import matplotlib.pyplot as plt

# Se cargan los archivos en una variable steps, desde el path actual
steps_insertion = np.loadtxt('./Insertion_sort/insertion_steps.txt')
steps_selection = np.loadtxt('./Selection_sort/selection_steps.txt')
steps_bubble = np.loadtxt('./Bubble_sort/bubble_steps.txt')
steps_merge= np.loadtxt('./Merge_sort/merge_steps.txt')
steps_quick = np.loadtxt('./Quick_sort/quick_steps.txt')
steps_sleep = np.loadtxt('./Sleep_sort/sleep_steps.txt')

plt.plot(range(0,101),steps_insertion, label="Insertion Sort")
plt.plot(range(0,101),steps_selection, label="Selection Sort")
plt.plot(range(0,101),steps_bubble, label="Bubble Sort")
plt.plot(range(0,101),steps_merge, label="Merge Sort")
plt.plot(range(0,101),steps_quick, label="Quick Sort")
plt.plot(range(0, 101), steps_sleep, label = "Sleep sort")

plt.title("Algoritmos de ordenación", fontsize = 20)
plt.legend()
plt.ylabel("Pasos", fontsize = 16)
plt.xlabel("Elementos en la lista", fontsize = 16)
plt.show()
