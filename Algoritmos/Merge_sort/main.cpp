#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Merge Function: Merges two subarrays of arr[].
    First subarray is arr[l..m]
    Second subarray is arr[m+1..r]
    steps: pointer to a variable that holds the number of steps taken
*/
void merge(int arr[], int l, int m, int r, int* steps)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;

        // Increment steps counter
        (*steps)++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;

        // Increment steps counter
        (*steps)++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;

        // Increment steps counter
        (*steps)++;
    }
}

/*
    Merge Sort Function: Sorts an array of integers in ascending order.
    arr[]: array to be sorted
    l: starting index of array
    r: ending index of array
    steps: pointer to a variable that holds the number of steps taken
*/
void merge_sort(int arr[], int l, int r, int* steps)
{
    if (l < r)
    {
        // Find the middle point
        int m = l+(r-l)/2;

        // Sort first and second halves
        merge_sort(arr, l, m, steps);
        merge_sort(arr, m+1, r, steps);

        // Merge the sorted halves
        merge(arr, l, m, r, steps);
    }
}
int main()
{
    // Seed the random number generator with the current time
    srand(time(NULL));
    // Initialize all values of steps to 0
    int steps[101] = {0};
    // Open file for writing
    FILE *f = fopen("./merge_steps.txt", "w");
    // Check if file was opened successfully
    if (f == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    FILE *f_lists = fopen("./merged_lists.txt", "w");
    if (f_lists == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    // Iterate over different list sizes
    for (int n = 0; n <= 100; n++)
    {
        int arr[n];
        for (int i = 0; i < n; i++)
            // Generate random numbers between 0 and 100
            arr[i] = rand() % 101;
        // Get size of array
        int arr_size = sizeof(arr)/sizeof(arr[0]);
        // Initialize step counter to 0
        int current_steps = 0;
        // Sort array using merge sort
        merge_sort(arr, 0, arr_size - 1, &current_steps);
        // Store number of steps in array
        steps[n] = current_steps;
        fprintf(f_lists, "List %d: ", n);
        for (int i = 0; i < n; i++)
            fprintf(f_lists, "%d ", arr[i]);
        fprintf(f_lists, "\n");
    }
    // Write steps to file
    for (int i = 0; i <= 100; i++)
        fprintf(f, "%d\n", steps[i]);
    // Close file
    fclose(f);
    return 0;
}