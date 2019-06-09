#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers/sorting.h"

#define N_ARRAYS 20 //number of arrays used on tests

//print a sigle array
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
        if (!strcmp(arrayType, "OrdC")) //ascending order array (1 to n)
            for (int j = 0; j < arraySize; j++)
                arrays[i][j] = j;
        else if (!strcmp(arrayType, "OrdD")) //descending order array (n to 1)
            for (int j = 0; j < arraySize; j++)
                arrays[i][j] = (arraySize - j);
        else if (!strcmp(arrayType, "Ale")) //random array (numbers between 0 and n-1)
            for (int j = 0; j < arraySize; j++)
                arrays[i][j] = rand() % arraySize;
    }
    return arrays;
}

//generate a copy of a set of arrays
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

//free a set of arrays
void freeArrays(int **arrays) {
    for (int i = 0; i < N_ARRAYS; i++) {
        free(arrays[i]);
    }
    free(arrays);
}

int main(int argc, char const *argv[]) {
    int **arrays, **copy, *exec_time, median, arraySize;
    long swap = 0;
    double comparisons = 0.0, aux_swap = 0.0;
    char quickSortType[5], arrayType[5];
    struct timespec start, end;
    
    srand(time(NULL));

    //copying arguments passed for the program to more adequate variables
    strcpy(quickSortType, argv[1]);
    strcpy(arrayType, argv[2]);
    arraySize = atoi(argv[3]);

    arrays = generateArrays(arrayType, arraySize);
    exec_time = (int *) malloc(N_ARRAYS * sizeof(int));

    //copying original arrays to not lose their information only if the user enters flag -p
    if (argc == 5 && !strcmp(argv[4], "-p"))
        copy = copyArrays(arrays, arraySize);

    for (int i = 0; i < N_ARRAYS; i++) {
        clock_gettime(CLOCK_REALTIME, &start);
        
        //dividing by N_ARRAYS to get average while preventing overflow
        comparisons += QuickSort(arrays[i], arraySize, quickSortType, &swap)/(double)N_ARRAYS;
        aux_swap += swap/(double)N_ARRAYS;
        swap = 0;
        
        clock_gettime(CLOCK_REALTIME, &end);
        exec_time[i] = 1.e+6 * (double) (end.tv_sec - start.tv_sec) 
                        + 1.e-3 * (double) (end.tv_nsec - start.tv_nsec);
    }
    swap = (long)aux_swap;
    
    //using aux_swap to not modify the original swap count
    //sorting to get median time
    QuickSort(exec_time, N_ARRAYS, "QC", &aux_swap);
    median = (exec_time[N_ARRAYS/2] + exec_time[(N_ARRAYS/2) - 1])/2;
    
    printf("%s %s %d %.0lf %ld %d\n", quickSortType, arrayType, arraySize,
    comparisons, swap, median);

    //print the copy of the original arrays if the flag -p exists
    if (argc == 5 && !strcmp(argv[4], "-p")) {
        for (int i = 0; i < N_ARRAYS; i++) {
            printArray(copy[i], arraySize);
        }
        freeArrays(copy);
    }
    
    freeArrays(arrays);
    free(exec_time);
    return 0;
}