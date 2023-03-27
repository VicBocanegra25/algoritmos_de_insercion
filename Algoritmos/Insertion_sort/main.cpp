

/* Implementación del algoritmo Insertion sort.
 * El siguiente código utiliza bubble sort para ordenar listas de diferentes tamaños (de 0 a n).
 * Las funciones impleemntan una variable llamada steps que en cada operación principal incrementa en 1 unidad, lo
 * que nos servirá para evaluar el rendimiento del algoritmo cuando incrementa el tamaño de n.
 * Finalmente, el programa imprime los resultados en dos archivos llamados insertion_list.txt e insertion_steps.txt; el primer
 * archivo contiene las listas ordenadas y el segundo contiene los pasos que le tomó ordenarlas. Este último archivo
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
    int array[]: Un array con los elementos desordenados.
    int n: El tamaño del array
 * returns:
    int n: El número de pasos que le toma ordenar la lista
 * */
int insertionSort(int array[], int n)
{
    int i, element, j, steps = 0;
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

    FILE *insertion_lists = fopen("../insertion_lists.txt", "w");
    FILE *insertion_steps = fopen("../insertion_steps.txt", "w");

    for (i = 0; i<101; i++)
    {
        int array[i];
        generateRandomNumbers(array, i);
        steps = insertionSort(array, i);
        printArraytoFile(array, i, insertion_lists);
        fprintf(insertion_steps, "%d\n",steps);
    }
    fclose(insertion_lists);
    fclose(insertion_steps);
    return 0;
}