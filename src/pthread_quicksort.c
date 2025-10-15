#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_THREADS 4

typedef struct {
    int* arr;
    int low;
    int high;
    int depth;
} ThreadData;

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

void* threadedQuickSort(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int* arr = data->arr;
    int low = data->low;
    int high = data->high;
    int depth = data->depth;

    if(low < high) {
        int pi = partition(arr, low, high);

        if(depth < 3) {
            pthread_t left, right;
            ThreadData left_data = { arr, low, pi - 1, depth + 1 };
            ThreadData right_data = { arr, pi + 1, high, depth + 1 };

            pthread_create(&left, NULL, threadedQuickSort, &left_data);
            pthread_create(&right, NULL, threadedQuickSort, &right_data);

            pthread_join(left, NULL);
            pthread_join(right, NULL);
        } else {
            ThreadData left_data = { arr, low, pi - 1, depth + 1 };
            ThreadData right_data = { arr, pi + 1, high, depth + 1 };
            threadedQuickSort(&left_data);
            threadedQuickSort(&right_data);
        }
    }

    return NULL;
}

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (tv.tv_usec / 1000000.0);
}

int main() {
    int n = 100000;
    int* arr = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) arr[i] = rand() % 10000;

    double start = get_time();
    ThreadData main_data = { arr, 0, n - 1, 0 };
    threadedQuickSort(&main_data);
    double end = get_time();

    printf("Time taken (Pthreads QuickSort): %f seconds\n", end - start);
    free(arr);
    return 0;
}
