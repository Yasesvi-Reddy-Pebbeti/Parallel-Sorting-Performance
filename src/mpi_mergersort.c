#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void merge(int* arr, int* temp, int left, int mid, int right) {
    int i = left, j = mid, k = left;
    while(i < mid && j <= right) temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while(i < mid) temp[k++] = arr[i++];
    while(j <= right) temp[k++] = arr[j++];
    for(i = left; i <= right; i++) arr[i] = temp[i];
}

void mergeSort(int* arr, int* temp, int left, int right) {
    if(left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, temp, left, mid);
        mergeSort(arr, temp, mid+1, right);
        merge(arr, temp, left, mid+1, right);
    }
}

int main(int argc, char* argv[]) {
    int rank, size, n = 100000;
    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int* arr = malloc(n * sizeof(int));
    int* temp = malloc(n * sizeof(int));

    if(rank == 0) {
        for(int i = 0; i < n; i++) arr[i] = rand() % 10000;
        start = MPI_Wtime();  // Start timing only on root
    }

    int chunk_size = n / size;
    int* sub_arr = malloc(chunk_size * sizeof(int));
    MPI_Scatter(arr, chunk_size, MPI_INT, sub_arr, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    int* sub_temp = malloc(chunk_size * sizeof(int));
    mergeSort(sub_arr, sub_temp, 0, chunk_size - 1);

    MPI_Gather(sub_arr, chunk_size, MPI_INT, arr, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        mergeSort(arr, temp, 0, n - 1);
        end = MPI_Wtime();  // End timing
        printf("Time taken (MPI): %f seconds\n", end - start);
    }

    free(arr); free(temp); free(sub_arr); free(sub_temp);
    MPI_Finalize();
    return 0;
}
