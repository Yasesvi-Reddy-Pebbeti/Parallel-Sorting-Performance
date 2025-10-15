#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for(int i = 0; i < n1; i++) L[i] = arr[l + i];
    for(int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];
}

void parallelMergeSort(int arr[], int l, int r, int depth) {
    if(l < r) {
        int m = l + (r - l)/2;
        if(depth <= 2) {
            #pragma omp parallel sections
            {
                #pragma omp section
                parallelMergeSort(arr, l, m, depth+1);
                #pragma omp section
                parallelMergeSort(arr, m+1, r, depth+1);
            }
        } else {
            parallelMergeSort(arr, l, m, depth+1);
            parallelMergeSort(arr, m+1, r, depth+1);
        }
        merge(arr, l, m, r);
    }
}

int main() {
    int n = 100000;
    int* arr = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) arr[i] = rand() % 10000;

    double start = omp_get_wtime();
    parallelMergeSort(arr, 0, n-1, 0);
    double end = omp_get_wtime();

    printf("Time taken (OpenMP): %f seconds\n", end - start);
    free(arr);
    return 0;
}
