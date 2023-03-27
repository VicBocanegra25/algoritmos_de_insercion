/* Implementación del algoritmo Selection sort.
 * El siguiente código utiliza selection sort para ordenar listas de diferentes tamaños (de 0 a n).
 * Las funciones implementan una variable llamada steps que en cada operación principal incrementa en 1 unidad, lo
 * que nos servirá para evaluar el rendimiento del algoritmo cuando incrementa el tamaño de n.
 * Finalmente, el programa imprime los resultados en dos archivos llamados selection_lists.txt y selection_steps.txt; el primer
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


/* Función selectionSort, implementa un contador para registrar los pasos que le toma ordenar la lista.
 * El algoritmo de selección busca el elemento más pequeño del array y lo cambia por el de la posición 0, luego recorre
 * el array nuevamente en búsqueda del más pequeño y lo cambia el de la posición 1 y así sucesivamente hasta recorrer todo el array.
 ** params:
    int array[]: Un array con los elementos desordenados.
    int n: El tamaño del array
 * returns:
    int n: El número de pasos que le toma ordenar la lista
*/
int selectionSort(int array[], int n)
{
    int i, min_element, j, steps = 0;
    for (i = 0; i < n - 1; i++)
    {
        min_element = i;
        for (j = i + 1; j < n; j++)
        {
            steps++;
            if (array[j] < array[min_element]){
                min_element = j;
            }
        }
        swap(&array[min_element], &array[i]);
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

    FILE *selection_lists = fopen("../selection_lists.txt", "w");
    FILE *selection_steps = fopen("../selection_steps.txt", "w");

    for (i = 0; i<101; i++)
    {
        int array[i];
        generateRandomNumbers(array, i);
        steps = selectionSort(array, i);
        printArraytoFile(array, i, selection_lists);
        fprintf(selection_steps, "%d\n",steps);
    }
    fclose(selection_lists);
    fclose(selection_steps);
    return 0;
}