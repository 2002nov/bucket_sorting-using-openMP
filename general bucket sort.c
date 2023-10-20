#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct buckets {
  int number;
  int* element;
};

int compare(const void* fvalue, const void* svalue) {
  int p = *((int*)fvalue), q = *((int*)svalue);
  if (p == q) {return 0;}
  else if (p < q) {return -1;}
  else {return 1;}
}

void BucketSort(int arr[], int arraySize) {
  struct buckets bucket[4];
  for (int i = 0; i < 4; i++) {
    bucket[i].number = 0;
    bucket[i].element = (int*)malloc(sizeof(int) * arraySize);
  }
  for (int i = 0; i < arraySize; i++) {
    if (arr[i] >= 0 && arr[i] < 25000) {
      bucket[0].element[bucket[0].number++] = arr[i];
    }
    else if (arr[i] >= 25000 && arr[i] < 50000) {
      bucket[1].element[bucket[1].number++] = arr[i];
    }
    else if (arr[i] >= 50000 && arr[i] < 75000) {
      bucket[2].element[bucket[2].number++] = arr[i];
    }
    else {
      bucket[3].element[bucket[3].number++] = arr[i];
    }
  }
  for (int k = 0, i = 0; i < 4; i++) {
    qsort(bucket[i].element, bucket[i].number, sizeof(int), &compare);
    for (int j = 0; j < bucket[i].number; j++) {
      arr[k + j] = bucket[i].element[j];
    }
    k = k + bucket[i].number;
    free(bucket[i].element);
  }
}

int main(int argc, char *argv[]) {
    int arraySizes[5] = {10000, 100000, 500000, 1000000, 2000000};
    
    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < 5; i++) {
        int arraySize = arraySizes[i];
        int* arr = (int*)malloc(arraySize * sizeof(int));

        // Initialize the array to be sorted
        for (int j = 0; j < arraySize; j++) {
            arr[j] = rand() % 100000;
        }

        // Timing
        clock_t seq_start, seq_end;
        seq_start = clock();

        BucketSort(arr, arraySize);

        seq_end = clock();
        
        double seq_time = (double)(seq_end - seq_start) / CLOCKS_PER_SEC;

        printf("Array Size: %d, Execution Time: %.6lf seconds\n", arraySize, seq_time);

        free(arr); // Don't forget to free the allocated memory
    }

    return 0;
}
