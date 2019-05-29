#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers/sorting.h"

#define N_ARRAYS 20

void printArray(int *array, int arraySize) {
    for (int i = 0; i < arraySize; i++)
        printf("%d ", array[i]);
    printf("\n");
} 

//initialize arrays based on arrayType
int **generateArrays(const char *arrayType, int arraySize) {
    int **arrays;
    arrays = (int **) malloc(N_ARRAYS * sizeof(int *));

    for (int i = 0; i < N_ARRAYS; i++) {
        arrays[i] = (int *) calloc(arraySize, sizeof(int));
        if (!strcmp(arrayType, "OrdC")) //ascending order array
            for (int j = 0; j < arraySize; j++)
                arrays[i][j] = j + (rand() % 2);
        else if (!strcmp(arrayType, "OrdD")) //descending order array
            for (int j = 0; j < arraySize; j++)
                arrays[i][j] = (arraySize - j) + (rand() % 2);
        else if (!strcmp(arrayType, "Ale")) //random array
            for (int j = 0; j < arraySize; j++)
                arrays[i][j] = rand() % arraySize;
    }
    return arrays;
}

int **copyArrays(int **arrays, const int arraySize) {
    int **copy;
    copy = (int **) malloc(N_ARRAYS * sizeof(int *));
    for (int i = 0; i < N_ARRAYS; i++) {
        copy[i] = (int *) malloc(arraySize * sizeof(int));
        for (int j = 0; j < arraySize; j++)
            copy[i][j] = arrays[i][j];
    }
    return copy;
}

void freeArrays(int **arrays) {
    for (int i = 0; i < N_ARRAYS; i++) {
        free(arrays[i]);
    }
    free(arrays);
}

int main(int argc, char const *argv[]) {
    int **arrays, **copy, swap = 0;
    long *median_time;
    double comparisons = 0.0, aux_swap = 0.0;
    struct timespec start, end;
    
    srand(time(NULL));

    arrays = generateArrays(argv[2], atoi(argv[3]));
    median_time = (long *) malloc(N_ARRAYS * sizeof(long));

    //copying original arrays to not lose their information only if the user enters flag -p
    if (argc == 5 && !strcmp(argv[4], "-p"))
        copy = copyArrays(arrays, atoi(argv[3]));

    for (int i = 0; i < N_ARRAYS; i++) {
        clock_gettime(CLOCK_REALTIME, &start);
        
        //dividing by N_ARRAYS to get average while preventing overflow
        comparisons += QuickSort(arrays[i], atoi(argv[3]), argv[1], &swap)/(double)N_ARRAYS;
        aux_swap += swap/(double)N_ARRAYS;
        swap = 0;
        
        clock_gettime(CLOCK_REALTIME, &end);
        median_time[i] = 1.e+6 * (double) (end.tv_sec - start.tv_sec) 
                        + 1.e-3 * (double) (end.tv_nsec - start.tv_nsec);
    }
    swap = (int)aux_swap;
    
    //using aux_swap to not modify the original swap count
    //sorting to get median time
    QuickSort(median_time, N_ARRAYS, "QC", &aux_swap);
    printf("%s %s %d %.0lf %d %ld\n", argv[1], argv[2], atoi(argv[3]),
    comparisons, swap, median_time[N_ARRAYS/2]);

    if (argc == 5 && !strcmp(argv[4], "-p")) {
        for (int i = 0; i < N_ARRAYS; i++) {
            printArray(copy[i], atoi(argv[3]));
        }
        freeArrays(copy);
    }
    
    freeArrays(arrays);
    free(median_time);
    return 0;
}