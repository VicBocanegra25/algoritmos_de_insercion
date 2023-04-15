

/* Implementación del algoritmo Insertion sort.
 * El siguiente código utiliza insertion sort para ordenar listas de diferentes tamaños (de 0 a n).
 * Las funciones implementan una variable llamada steps que en cada operación principal incrementa en 1 unidad, lo
 * que nos servirá para evaluar el rendimiento del algoritmo cuando incrementa el tamaño de n.
 * Finalmente, el programa imprime los resultados en dos archivos llamados insertion_list.txt, insertion_time e
 * insertion_steps.txt; el primer archivo contiene las listas ordenadas, el segundo contiene el tiempo
 * que se demora el algoritmo y el tercero los pasos que le tomó ordenarlas. Este último archivo
 * nos servirá para generar una gráfica (en otro programa) y ver el crecimiento de la función.
 * @date: 26/03/2023
 * @author: Víctor Bocanegra
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/* Función insertionSort, implementa un contador para registrar los pasos que le toma ordenar la lista.
 * Funciona comparando el elemento en la posición i+1 con el elemento en la posición i, los compara y si encuentra que están
 * en la posición incorrecta, los cambia de lugar.
 * params:
    long array[]: Un array con los elementos desordenados.
    long n: El tamaño del array
 * returns:
    long n: El número de pasos que le toma ordenar la lista
 * */
long insertionSort(long array[], long n)
{
    long i, element, j, steps = 0;
    for (i = 1; i < n; i++)
    {
        element = array[i];
        j = i-1;
        while(j >= 0 && array[j] > element)
        {
            steps++;
            array[j+1] = array[j];
            j = j -1;
        }
        steps++;
        array[j + 1] = element;
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
            fprintf(file, "%d, ", array[i]);
        }
        else
        {
            fprintf(file, "%d", array[i]);
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
    long i;

    // Nos servirá para medir el tiempo que tarda en ejecutar el algoritmo para cada una de las muestras
    clock_t inicio, fin;
    // El tiempo que le tomó al algoritmo
    double tiempo_total;
    srand(time(0));

    // Inicializamos los archivos txt en los cuales guardaremos la lista ordenada, así como el número de pasos y del tiempo.
    FILE *insertion_lists = fopen("../insertion_lists.txt", "w");
    FILE *insertion_steps = fopen("../insertion_steps.txt", "w");
    FILE *insertion_time = fopen("../insertion_time.txt", "w");

    // Generamos un array con los valores 800, 8000, 80000
    long array_pruebas[] = {800, 8000, 80000};
    long num_pruebas = sizeof(array_pruebas) / sizeof(array_pruebas[0]);

    // Este ciclo determina el número de veces que se ha de ejecutar el algoritmo.
    for (i = 0; i<num_pruebas; i++)
    {
        long j = array_pruebas[i];
        long array[j];
        generateRandomNumbers(array, j);
        // Iniciamos el conteo para registrar el tiempo que tarda el array en ordenar la lista
        inicio = clock();
        steps = insertionSort(array, j);
        fin = clock();
        tiempo_total = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printArraytoFile(array, j, insertion_lists);
        fprintf(insertion_time, "%.5f\n", tiempo_total);
        fprintf(insertion_steps, "%lld\n",steps);
    }
    // No olvidemos cerrar los archivos
    fclose(insertion_lists);
    fclose(insertion_time);
    fclose(insertion_steps);
    return 0;
}