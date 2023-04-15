/* Implementación del algoritmo merge sort.
 * El siguiente código utiliza merge sort para ordenar listas de diferentes tamaños (800, 8000, 80000).
 * Las funciones implementan una variable llamada steps que en cada operación principal incrementa en 1 unidad, lo
 * que nos servirá para evaluar el rendimiento del algoritmo cuando incrementa el tamaño de n.
 * Finalmente, el programa imprime los resultados en dos archivos llamados merge_list.txt, merge_time.txt y merge_steps.txt;
 * el primer archivo contiene las listas ordenadas, el segundo contiene el tiempo que le tomó al algoritmo ordenar la lista, mientras que el
 * último contiene los pasos que le tomó ordenarlas. Este último archivo nos servirá para generar una gráfica (en otro programa)
 * y ver el crecimiento de la función.
 * @date: 26/03/2023
 * @author: Víctor Bocanegra
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Función merge: Combina dos subarrays ordenados en un array ordenado.
 * params:
    long array[]: El array que se va a dividir y combinar
    long left[]: El subarray izquierdo
    long right[]: El subarray derecho
    long left_size: El tamaño del subarray izquierdo
    long right_size: El tamaño del subarray derecho
 * returns:
    unsigned long long: El número de pasos que le toma combinar los subarrays
 */
unsigned long long merge(long array[], long left[], long right[], long left_size, long right_size)
{
    unsigned long long steps = 0;
    long i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size)
    {
        steps++;
        if (left[i] <= right[j])
        {
            array[k++] = left[i++];
        }
        else
        {
            array[k++] = right[j++];
        }
    }

    while (i < left_size)
    {
        array[k++] = left[i++];
        steps++;
    }

    while (j < right_size)
    {
        array[k++] = right[j++];
        steps++;
    }

    return steps;
}

/* Función mergeSort: Implementa el algoritmo de ordenamiento merge sort y un contador para registrar los pasos que le toma ordenar la lista.
 * params:
    long array[]: Un array con los elementos desordenados.
    long n: El tamaño del array
 * returns:
    unsigned long long: El número de pasos que le toma ordenar la lista
 * */
unsigned long long mergeSort(long array[], long n)
{
    unsigned long long steps = 0;
    if (n < 2)
    {
        return steps;
    }

    long mid = n / 2;
    long left[mid];
    long right[n - mid];

    for (long i = 0; i < mid; i++)
    {
        left[i] = array[i];
    }

    for (long i = mid; i < n; i++)
    {
        right[i - mid] = array[i];
    }

    steps += mergeSort(left, mid);
    steps += mergeSort(right, n - mid);
    steps += merge(array, left, right, mid, n -mid);
    return steps;
}

/* La función printArrayToFile nos ayuda a imprimir el contenido de un array a un archivo con extensión .txt.

Esto nos servirá para graficar y verificar el resultado de la ordenación.
params:
long array[]: El array que contiene los elementos a imprimir
long size: El tamaño del array
FILE *file: El puntero que contiene la dirección del archivo en donde se va a imprimir el contenido
returns:
void
*/
void printArraytoFile(long array[], long size, FILE *file)
{
    long i;
    fprintf(file, "[");
    for (i = 0; i < size; i++)
    {
        if (i < size - 1)
        {
            fprintf(file, "%ld, ", array[i]);
        }
        else
        {
            fprintf(file, "%ld", array[i]);
        }
    }
    fprintf(file, "]\n");
}
/* Función generateRandomNumbers. Nos sirve para llenar los arrays con números al azar.

params:
long array[]: El contenedor que llenaremos con números aleatorios
long size: La cantidad de números que debe tener el array
returns:
void
*/
void generateRandomNumbers(long array[], long size)
{
    long i;
    for (i = 0; i < size; i++)
    {
// Se llena el array con números aleatorios entre el 0 y 100000
        array[i] = rand() % 100000;
    }
}

int main()
{
// Steps debe ser del tipo long long debido a la magnitud tan grande de los pasos
    unsigned long long steps;
// Nos servirá para medir el tiempo que tarda en ejecutar el algoritmo para cada una de las muestras
    clock_t inicio, fin;
// El tiempo que le tomó al algoritmo
    double tiempo_total;
    srand(time(0));
    // Inicializamos los archivos txt en los cuales guardaremos la lista ordenada, así como el número de pasos y del tiempo.
    FILE *merge_lists = fopen("./merge_list.txt", "w");
    FILE *merge_steps = fopen("./merge_steps.txt", "w");
    FILE *merge_time = fopen("./merge_time.txt", "w");

// Generamos un array con los valores 800, 8000, 80000
    long array_pruebas[] = {800, 8000, 80000};
    long num_pruebas = sizeof(array_pruebas) / sizeof(array_pruebas[0]);

// Este ciclo determina el número de veces que se ha de ejecutar el algoritmo.
    for (long i = 0; i < num_pruebas; i++)
    {
        long j = array_pruebas[i];
        long array[j];

        generateRandomNumbers(array, j);

        // Iniciamos el conteo para registrar el tiempo que tarda el array en ordenar la lista
        inicio = clock();
        steps = mergeSort(array, j);
        fin = clock();
        tiempo_total = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printArraytoFile(array, j, merge_lists);
        fprintf(merge_time, "%.5f\n", tiempo_total);
        fprintf(merge_steps, "%lld\n", steps);
    }

// No olvidemos cerrar los archivos
    fclose(merge_lists);
    fclose(merge_steps);
    fclose(merge_time);
    return 0;
    }

