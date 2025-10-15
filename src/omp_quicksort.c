#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++) {
        if(arr[j] < pivot) {
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }

    int tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;

    return i + 1;
}

void quicksort(int arr[], int low, int high, int depth) {
    if(low < high) {
        int pi = partition(arr, low, high);

        if(depth < 3) {
            #pragma omp parallel sections
            {
                #pragma omp section
                quicksort(arr, low, pi - 1, depth + 1);

                #pragma omp section
                quicksort(arr, pi + 1, high, depth + 1);
            }
        } else {
            quicksort(arr, low, pi - 1, depth + 1);
            quicksort(arr, pi + 1, high, depth + 1);
        }
    }
}

int main() {
    int n = 100000;
    int* arr = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) arr[i] = rand() % 10000;

    double start = omp_get_wtime();
    quicksort(arr, 0, n - 1, 0);
    double end = omp_get_wtime();

    printf("Time taken (OpenMP QuickSort): %f seconds\n", end - start);
    free(arr);
    return 0;
}
