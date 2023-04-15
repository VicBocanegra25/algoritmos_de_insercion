# Algoritmia y Complejidad - Actividad: Algoritmos de inserción

Repositorio para almacenar los programas (en C y en Python) correspondientes a las actividades de Algoritmos de Inserción y Análisis de Algoritmos de la materia de Algoritmia y Complejidad de la UNIR. Se implementan diferentes algoritmos de ordenación y se demuestra su eficiencia (de forma visual).

Cada algoritmo tiene su propia carpeta y el código lleva el nombre main.cpp. Los archivos algoritmo_lists.txt, algoritmo_time.txt y algoritmo_steps.txt contienen las listas ordenadas, el tiempo que le toma al algoritmo en ejecutarse y el número de pasos que les toma ordenar listas con números aleatorios entre el 0 y el 100,000. 

Cada programa tiene la tarea de ordenar listas de 800, 8000 y 80000 elementos y en cada ejecución se generan archivos txt nuevos (esto es para permitir la visualización con gráficas). 

Cada algoritmo tiene su propio archivo para visualizar su gráfica, llamado plot_steps.py.

## Tabla con la complejidad temporal resumida (No es lo mismo que la fórmula para el análisis matemático). 

| Algoritmo       | Mejor caso | Caso promedio | Peor caso  |
| :-------------: | :--------: | :-----------: | :--------: |
| Bubble Sort     | O(n)       | O(n²)         | O(n²)      |
| Selection Sort  | O(n²)      | O(n²)         | O(n²)      |
| Insertion Sort  | O(n)       | O(n²)         | O(n²)      |
| Merge Sort      | O(nlog(n)) | O(nlog(n))    | O(nlog(n)) |
| Quick Sort      | O(nlog(n)) | O(nlog(n))    | O(n²)      |
| Sleep Sort      | O(n)       | O(n)          | O(n)       |
