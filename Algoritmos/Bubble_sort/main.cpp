

/* Implementación del algoritmo bubble sort.
 * El siguiente código utiliza bubble sort para ordenar listas de diferentes tamaños (de 0 a n).
 * Las funciones impleemntan una variable llamada steps que en cada operación principal incrementa en 1 unidad, lo
 * que nos servirá para evaluar el rendimiento del algoritmo cuando incrementa el tamaño de n.
 * Finalmente, el programa imprime los resultados en dos archivos llamados bubble_list.txt y bubble_steps.txt; el primer
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

/* Función bubble sort, implementa un contador para registrar los pasos que le toma ordenar la lista.
 * params:
    int array[]: Un array con los elementos desordenados.
    int n: El tamaño del array
 * returns:
    int n: El número de pasos que le toma ordenar la lista
 * */
int bubbleSort(int array[], int n)
{
    int i, j, steps = 0;
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

    FILE *bubble_lists = fopen("../bubble_list.txt", "w");
    FILE *bubble_steps = fopen("../bubble_steps.txt", "w");

    for (i = 0; i<101; i++)
    {
        int array[i];
        generateRandomNumbers(array, i);
        steps = bubbleSort(array, i);
        printArraytoFile(array, i, bubble_lists);
        fprintf(bubble_steps, "%d\n",steps);
    }
    fclose(bubble_lists);
    fclose(bubble_steps);
    return 0;
}