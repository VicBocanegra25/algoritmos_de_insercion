/* Implementación del algoritmo Quick sort.
 * El siguiente código utiliza selection sort para ordenar listas de diferentes tamaños (de 0 a n).
 * Las funciones implementan una variable llamada steps que en cada operación principal incrementa en 1 unidad, lo
 * que nos servirá para evaluar el rendimiento del algoritmo cuando incrementa el tamaño de n.
 * Finalmente, el programa imprime los resultados en tres archivos llamados quick_lists.txt, quick_time.txt y quick_steps.txt; el primer
 * archivo contiene las listas ordenadas, el segundo contiene el tiempo que le tomó en ordenar la lista y el último el número de pasos. Este último archivo
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


/* Función partition, implementa un contador para registrar los pasos que le toma ordenar la lista.
 * El algoritmo quickSort es un algoritmo de divide y vencerás. Funciona seleccionando un elemento pivote y partiendo el array
 * en partes distintas. Posteriormente, actúa de forma recursiva, ordenando aquellos que son más grandes o más pequeños
 * que el pivote y colocándolos en la posición correcta. Esta es una función auxiliar que nos ayudará a implementar la recursividad
 * de quickSort.
 ** params:
    long array[]: Un array con los elementos desordenados.
    long lowIndex: El índice inicial del array
    long highIndex: El índice final del array
    steps: Un pointer al contador de pasos
 * returns:
    long: el índice del elemento de partición
*/

long partition(long arr[], long lowIndex, long highIndex, long *steps)
{
    // Se elige el elemento pivote (el último del array)
    long pivotElement = arr[highIndex];

    // i se coloca como el elemento más pequeño
    long i = (lowIndex - 1);

    // Se itera el array comparando cada elemento con el elemento pivote
    for (long j = lowIndex; j <= highIndex - 1; j++)
    {
        (*steps)++;
        if (arr[j] <= pivotElement)
        {
            // Si el elemento actual es más pequeño o igual que el pivote, se intercambia con la posición i+1
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[highIndex]);

    // Se regresa el índice del pivote
    return (i + 1);
}
// QuickSort Function with step counter
long quickSort(long arr[], long lowIndex, long highIndex)
{
    long steps = 0;
    if (lowIndex < highIndex)
    {
        long pivot = partition(arr, lowIndex, highIndex, &steps);
        steps += quickSort(arr, lowIndex, pivot - 1);
        steps += quickSort(arr, pivot + 1, highIndex);
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

    // Nos servirá para medir el tiempo que tarda en ejecutar el algoritmo para cada una de las muestras
    clock_t inicio, fin;
    // El tiempo que le tomó al algoritmo
    double tiempo_total;
    srand(time(0));

    // Inicializamos los archivos txt en los cuales guardaremos la lista ordenada, así como el número de pasos y del tiempo.
    FILE *quick_lists = fopen("../quick_lists.txt", "w");
    FILE *quick_steps = fopen("../quick_steps.txt", "w");
    FILE *quick_time = fopen("../quick_time.txt", "w");

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
        steps = quickSort(array, 0,j-2);
        fin = clock();
        tiempo_total = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printArraytoFile(array, j, quick_lists);
        fprintf(quick_steps, "%lld\n",steps);
        fprintf(quick_time, "%.5f\n", tiempo_total);

    }
    // No olvidemos cerrar los archivos
    fclose(quick_lists);
    fclose(quick_steps);
    fclose(quick_time);

    return 0;
}