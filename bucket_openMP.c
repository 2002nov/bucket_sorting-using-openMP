#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Bucket {
    int number;
    int *elements;
};

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void SequentialSort(int arr[], int arraySize) {
    struct Bucket buckets[4];
    int i, j, k;

    for (i = 0; i < 4; i++) {
        buckets[i].number = 0;
        buckets[i].elements = (int *)malloc(arraySize * sizeof(int)); // Allocate space for all elements
    }

    // Distribute elements into buckets
    for (i = 0; i < arraySize; i++) {
        int bucketIndex = arr[i] / (arraySize / 4);
        buckets[bucketIndex].elements[buckets[bucketIndex].number++] = arr[i];
    }

    k = 0;
    for (i = 0; i < 4; i++) {
        qsort(buckets[i].elements, buckets[i].number, sizeof(int), compare);
        for (j = 0; j < buckets[i].number; j++) {
            arr[k++] = buckets[i].elements[j];
        }
    }

    // Free allocated memory for the buckets
    for (i = 0; i < 4; i++) {
        free(buckets[i].elements);
    }
}

void ParallelSort(int arr[], int ParallelSorted[], int arraySize, int numThreads) {
    struct Bucket *buckets = (struct Bucket *)malloc(numThreads * 4 * sizeof(struct Bucket));
    int i, j;

    // Initialize buckets for all threads
    for (i = 0; i < numThreads * 4; i++) {
        buckets[i].number = 0;
        buckets[i].elements = (int *)malloc((arraySize / numThreads) * sizeof(int));
    }

    #pragma omp parallel num_threads(numThreads)
    {
        int tid = omp_get_thread_num();

        // Distribute elements into buckets in parallel
        #pragma omp for
        for (i = 0; i < arraySize; i++) {
            int bucketIndex = arr[i] / (arraySize / 4);
            int index = tid * 4 + bucketIndex;
            buckets[index].elements[buckets[index].number++] = arr[i];
        }

        // Sort the local buckets in parallel
        #pragma omp for
        for (i = 0; i < numThreads * 4; i++) {
            qsort(buckets[i].elements, buckets[i].number, sizeof(int), compare);
        }

        // Merge the sorted buckets back into the main array
        #pragma omp single
        {
            int k = 0;
            for (i = 0; i < numThreads * 4; i++) {
                for (j = 0; j < buckets[i].number; j++) {
                    ParallelSorted[k++] = buckets[i].elements[j];
                }
            }
        }
    }

    // Free allocated memory for the buckets
    for (i = 0; i < numThreads * 4; i++) {
        free(buckets[i].elements);
    }

    free(buckets);
}

int main() {
    int i;
    int arraySize = 10000; // Adjust the array size as needed
    int numThreads = 4;

    time_t seq_start, seq_end;

    // Adjust the number of threads as needed
    int *arr = (int *)malloc(arraySize * sizeof(int));
    int *ParallelSorted = (int *)malloc(arraySize * sizeof(int));
    int *SequentialSorted = (int *)malloc(arraySize * sizeof(int));

    // Initialize array to be sorted
    srand(time(NULL));
    for (i = 0; i < arraySize; i++) {
        arr[i] = rand() % 10000;
        SequentialSorted[i] = arr[i];
    }

    // Sequential bucket Sort
    time(&seq_start);
    SequentialSort(SequentialSorted, arraySize);
    time(&seq_end);

    // Parallel bucket sort using OpenMP
    double openmp_start = omp_get_wtime();
    ParallelSort(arr, ParallelSorted, arraySize, numThreads);
    //SequentialSort(SequentialSorted, arraySize);
    double openmp_end = omp_get_wtime();
    
    /*
    printf("unsorted array: ");
    for (i = 0; i < arraySize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nsorted array using sequential bucket sort: ");
    for (i = 0; i < arraySize; i++) {
        printf("%d ", sequentialSorted[i]);
    }
    printf("\nsorted array using parallel bucket sort: ");
    for (i = 0; i < arraySize; i++) {
        printf("%d ", ParallelSorted[i]);
    }
    */

    //printf("\nTime used in sequential bucket sort using OpenMP: %lf seconds\n", difftime(seq_end, seq_start));
    printf("\nTime used in parallel bucket sort using OpenMP: %lf seconds\n", openmp_end - openmp_start);

    free(arr);
    free(ParallelSorted);
    free(SequentialSorted);

    return 0;
}
