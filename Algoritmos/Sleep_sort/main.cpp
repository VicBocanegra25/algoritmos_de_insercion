#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct SleepSortArgs {
    int value;
    int *sorted_list;
    int *step_counter;
} SleepSortArgs;

void *sleep_sort(void *arg) {
    SleepSortArgs *args = (SleepSortArgs *)arg;
    usleep(args->value * 1000);
    args->sorted_list[*args->step_counter] = args->value;
    (*args->step_counter)++;
    return NULL;
}

int main() {
    srand(time(NULL));
    FILE *list_file = fopen("./../sleep_lists.txt", "w");
    FILE *steps_file = fopen("./../sleep_steps.txt", "w");

    for (int k = 0; k <= 100; k++) {
        int n = k;
        int items[n];
        for (int i = 0; i < n; i++) {
            items[i] = rand() % 100;
        }

        int sorted_list[n];
        int step_counter = 0;

        pthread_t threads[n];
        SleepSortArgs args[n];

        for (int i = 0; i < n; i++) {
            args[i].value = items[i];
            args[i].sorted_list = sorted_list;
            args[i].step_counter = &step_counter;
            pthread_create(&threads[i], NULL, sleep_sort, (void *)&args[i]);
        }

        for (int i = 0; i < n; i++) {
            pthread_join(threads[i], NULL);
        }
        fprintf(list_file, "[");
        for (int i = 0; i < n; i++) {
            if (i < n - 1) {
                fprintf(list_file, "%d, ", sorted_list[i]);
            } else {
                fprintf(list_file, "%d", sorted_list[i]);
            }
        }
        fprintf(list_file, "]\n");

        fprintf(steps_file, "%d\n", step_counter);
    }

    fclose(list_file);
    fclose(steps_file);

    return 0;
}