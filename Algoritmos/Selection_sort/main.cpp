/* Implementación del algoritmo Selection sort.
 * El siguiente código utiliza selection sort para ordenar listas de diferentes tamaños (de 0 a n).
 * Las funciones implementan una variable llamada steps que en cada operación principal incrementa en 1 unidad, lo
 * que nos servirá para evaluar el rendimiento del algoritmo cuando incrementa el tamaño de n.
 * Finalmente, el programa imprime los resultados en tres archivos llamados selection_lists.txt, selection_time.txt y selection_steps.txt; el primer
 * archivo contiene las listas ordenadas, el segundo contiene el tiempo que le tomó al algoritmo
 * y el último contiene los pasos que le tomó ordenarlas. Este último archivo también
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


/* Función selectionSort, implementa un contador para registrar los pasos que le toma ordenar la lista.
 * El algoritmo de selección busca el elemento más pequeño del array y lo cambia por el de la posición 0, luego recorre
 * el array nuevamente en búsqueda del más pequeño y lo cambia el de la posición 1 y así sucesivamente hasta recorrer todo el array.
 ** params:
    long array[]: Un array con los elementos desordenados.
    long n: El tamaño del array
 * returns:
    long n: El número de pasos que le toma ordenar la lista
*/
long selectionSort(long array[], long n)
{
    long i, min_element, j, steps = 0;
    for (i = 0; i < n - 1; i++)
    {
        // Inicializamos una variable que contendrá el elemento más pequeño (en inicio, el de la posición 0)
        min_element = i;
        for (j = i + 1; j < n; j++)
        {
            // El contador suma 1 a la valor steps en cada comparación
            steps++;
            // Si el valor en la posición j es menor que el elemento mínimo, el elemento mínimo se actualiza
            if (array[j] < array[min_element]){
                min_element = j;
            }
        }
        // Se llama la función swap para intercambiar los elementos de posición
        swap(&array[min_element], &array[i]);
    }
    return steps;
}

/* La función prlongArrayToFile nos ayuda a imprimir el contenido de un array a un archivo con extensión .txt.
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

/* La función main nos permite llamar nuestras funciones n número de veces utilizando un ciclo for, lo que nos permite llevar
 * la cuenta del número de operaciones y del tiempo que le toma al algoritmo en ordenar la lista.
 * */
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
    FILE *selection_lists = fopen("../selection_lists.txt", "w");
    FILE *selection_steps = fopen("../selection_steps.txt", "w");
    FILE *selection_time = fopen("../selection_time.txt", "w");

    // Generamos un array con los valores 800, 8000, 80000
    long array_pruebas[] = {800, 8000, 80000};
    long num_pruebas = sizeof(array_pruebas) / sizeof(array_pruebas[0]);

    // Este ciclo determina el número de veces que se ha de ejecutar el algoritmo.
    for (long i = 0; i<num_pruebas; i++)
    {
        long j = array_pruebas[i];
        long array[j];

        generateRandomNumbers(array, j);

        // Iniciamos el conteo para registrar el tiempo que tarda el array en ordenar la lista
        inicio = clock();
        steps = selectionSort(array, j);
        fin = clock();
        tiempo_total = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printArraytoFile(array, j, selection_lists);
        fprintf(selection_time, "%.5f\n", tiempo_total);
        fprintf(selection_steps, "%lld\n",steps);
    }

    // No olvidemos cerrar los archivos
    fclose(selection_lists);
    fclose(selection_steps);
    fclose(selection_time);

    return 0;
}