

/* Implementación del algoritmo bubble sort.
 * El siguiente código utiliza bubble sort para ordenar listas de diferentes tamaños (de 0 a n).
 * Las funciones impleemntan una variable llamada steps que en cada operación principal incrementa en 1 unidad, lo
 * que nos servirá para evaluar el rendimiento del algoritmo cuando incrementa el tamaño de n.
 * Finalmente, el programa imprime los resultados en dos archivos llamados bubble_list.txt, bubble_time.txt y  bubble_steps.txt; el primer archivo contiene las listas ordenadas, el segundo contiene el tiempo que le tomó al algoritmo ordenar la lista, mientras que el último contiene los pasos que le tomó ordenarlas. Este último archivo
 * nos servirá para generar una gráfica (en otro programa) y ver el crecimiento de la función.
 * @date: 26/03/2023
 * @author: Víctor Bocanegra
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* Función para intercambiar los elementos si uno es más grande que el otro. Utiliza punteros y una variable llamada
 * 'temp' para almacenar temporalmente el valor de a y poder hacer el cambio.
 * params:
    long *a: Es un puntero al elemento n de un array
    long *b: Es un puntero al elemento n+1 de un array
 * returns:
    void
 */
void swap(long *a, long *b)
{
    long temp = *a;
    *a = *b;
    *b = temp;
}

/* Función bubble sort, implementa un contador para registrar los pasos que le toma ordenar la lista.
 * params:
    long array[]: Un array con los elementos desordenados.
    long n: El tamaño del array
 * returns:
    unsigned long long n: El número de pasos que le toma ordenar la lista
 * */
unsigned long long bubbleSort(long array[], long n)
{
    long i, j, steps = 0;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n -i - 1; j++)
        {
            // Cada que se hace la comparación, se incrementa en 1 el stepcount
            steps++;
            // Si el elemento n es más grande que n+1, se intercambian sus posiciones
            if (array[j] > array[j + 1])
            {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
    return steps;
}

/* La función printArrayToFile nos ayuda a imprimir el contenido de un array a un archivo con extensión .txt.
 * Esto nos servirá para graficar y verificar el resultado de la ordenación.
 * params:
    long array[]: El array que contiene los elementos a imprimir
    long size: El tamaño del array
    FILE *file: El puntero que contiene la dirección del archivo en donde se va a imprimir el contenido
 * returns:
    void
 * */
void printArraytoFile(long array[], long size, FILE *file)
{
    long i;
    fprintf(file,"[");
    for (i=0; i<size; i++)
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
 * params:
    long array[]: El contenedor que llenaremos con números aleatorios
    long size: La cantidad de números que debe tener el array
 * returns:
    void
 * */

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
    FILE *bubble_lists = fopen("../bubble_list.txt", "w");
    FILE *bubble_steps = fopen("../bubble_steps.txt", "w");
    FILE *bubble_time = fopen("../bubble_time.txt", "w");

    // Generamos un array con los valores 800, 8000, 80000
    long array_pruebas[] = {800, 8000, 80000};
    long num_pruebas = sizeof(array_pruebas) / sizeof(array_pruebas[0]);

    // Este ciclo determina el número de veces que se ha de ejecutar el algoritmo.
    for (long i = 0; i<num_pruebas; i++)
    {
        long j = array_pruebas[i];
        long array[j];
;
        generateRandomNumbers(array, j);

        // Iniciamos el conteo para registrar el tiempo que tarda el array en ordenar la lista
        inicio = clock();
        steps = bubbleSort(array, j);
        fin = clock();
        tiempo_total = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printArraytoFile(array, j, bubble_lists);
        fprintf(bubble_time, "%.5f\n", tiempo_total);
        fprintf(bubble_steps, "%lld\n",steps);
    }

    // No olvidemos cerrar los archivos
    fclose(bubble_lists);
    fclose(bubble_steps);
    fclose(bubble_time);
    return 0;
}