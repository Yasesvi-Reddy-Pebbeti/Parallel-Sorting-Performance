#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_THREADS 4

typedef struct {
    int* arr;
    int left;
    int right;
} ThreadData;

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

void mergeSort(int arr[], int l, int r) {
    if(l < r) {
        int m = l + (r - l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void* threadedMergeSort(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int l = data->left;
    int r = data->right;
    int* arr = data->arr;

    if(l < r) {
        int m = l + (r - l) / 2;

        pthread_t left_thread, right_thread;
        ThreadData left_data = { arr, l, m };
        ThreadData right_data = { arr, m + 1, r };

        pthread_create(&left_thread, NULL, threadedMergeSort, &left_data);
        pthread_create(&right_thread, NULL, threadedMergeSort, &right_data);

        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);

        merge(arr, l, m, r);
    }
    return NULL;
}

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main() {
    int n = 100000;
    int* arr = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) arr[i] = rand() % 10000;

    double start = get_time();
    ThreadData main_data = { arr, 0, n - 1 };
    threadedMergeSort(&main_data);
    double end = get_time();

    printf("Time taken (Pthreads): %f seconds\n", end - start);
    free(arr);
    return 0;
}
