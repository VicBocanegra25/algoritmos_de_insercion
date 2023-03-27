/* Implementación del algoritmo Quick sort.
 * El siguiente código utiliza selection sort para ordenar listas de diferentes tamaños (de 0 a n).
 * Las funciones implementan una variable llamada steps que en cada operación principal incrementa en 1 unidad, lo
 * que nos servirá para evaluar el rendimiento del algoritmo cuando incrementa el tamaño de n.
 * Finalmente, el programa imprime los resultados en dos archivos llamados quick_lists.txt y quick_steps.txt; el primer
 * archivo contiene las listas ordenadas y el segundo contiene los pasos que le tomó ordenarlas. Este último archivo
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
    int *a: Es un puntero al elemento n de un array
    int *b: Es un puntero al elemento n+1 de un array
 * returns:
    void
 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


/* Función partition, implementa un contador para registrar los pasos que le toma ordenar la lista.
 * El algoritmo quickSort es un algoritmo de divide y vencerás. Funciona seleccionando un elemento pivote y partiendo el array
 * en partes distintas. Posteriormente, actúa de forma recursiva, ordenando aquellos que son más grandes o más pequeños
 * que el pivote y colocándolos en la posición correcta. Esta es una función auxiliar que nos ayudará a implementar la recursividad
 * de quickSort.
 ** params:
    int array[]: Un array con los elementos desordenados.
    int lowIndex: El índice inicial del array
    int highIndex: El índice final del array
    steps: Un pointer al contador de pasos
 * returns:
    int: el índice del elemento de partición
*/

int partition(int arr[], int lowIndex, int highIndex, int *steps)
{
    // Se elige el elemento pivote (el último del array)
    int pivotElement = arr[highIndex];

    // i se coloca como el elemento más pequeño
    int i = (lowIndex - 1);

    // Se itera el array comparando cada elemento con el elemento pivote
    for (int j = lowIndex; j <= highIndex - 1; j++)
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
int quickSort(int arr[], int lowIndex, int highIndex)
{
    int steps = 0;
    if (lowIndex < highIndex)
    {
        int pivot = partition(arr, lowIndex, highIndex, &steps);
        steps += quickSort(arr, lowIndex, pivot - 1);
        steps += quickSort(arr, pivot + 1, highIndex);
    }
    return steps;
}


/* La función printArrayToFile nos ayuda a imprimir el contenido de un array a un archivo con extensión .txt.
 * Esto nos servirá para graficar y verificar el resultado de la ordenación.
 * params:
    int array[]: El array que contiene los elementos a imprimir
    int size: El tamaño del array
    FILE *file: El puntero que contiene la dirección del archivo en donde se va a imprimir el contenido
 * returns:
    void
 * */
void printArraytoFile(int array[], int size, FILE *file)
{
    int i;
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
    int array[]: El contenedor que llenaremos con números aleatorios
    int size: La cantidad de números que debe tener el array
 * returns:
    void
 * */

void generateRandomNumbers(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        // Se llena el array con números aleatorios entre el 0 y 100
        array[i] = rand() % 1000;
    }
}

int main()
{
    int i, steps;

    srand(time(0));

    FILE *quick_lists = fopen("../quick_lists.txt", "w");
    FILE *quick_steps = fopen("../quick_steps.txt", "w");

    for (i = 1; i<=101; i++)
    {
        int array[i];
        generateRandomNumbers(array, i);
        steps = quickSort(array, 0,i-1);
        printArraytoFile(array, i, quick_lists);
        fprintf(quick_steps, "%d\n",steps);
    }
    fclose(quick_lists);
    fclose(quick_steps);
    return 0;
}