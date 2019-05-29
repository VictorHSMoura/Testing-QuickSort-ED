#include "headers/sorting.h"
#include "headers/stack.h"

#include <string.h>
#include <stdio.h>

int Partition(int Esq, int Dir, int *i, int *j, int *A, int *swap, int type) {
    int x, w, comparisons = 0;
    *i = Esq; *j = Dir;
    if (type == 0)
        x = A[(*i + *j)/2]; /* middle element is pivot */
    else if (type == 1) 
        x = A[Esq]; /* first element is pivot */
    else {
        int x1 = (A[Esq] > A[Dir])? A[Esq] : A[Dir];
        x = A[(*i + *j)/2] > x1? x1 : A[(*i + *j)/2]; /* obtaining the pivot by median of three*/
    }
    
    do {
        while (x > A[*i]) { 
            (*i)++; comparisons++;
        }
        comparisons++;
        while (x < A[*j]) {
            (*j)--; comparisons++;
        }
        comparisons++;
        
        if (*i <= *j) {
            w = A[*i]; A[*i] = A[*j]; A[*j] = w;
            (*i)++; (*j)--; (*swap)++;
        }
    } while (*i <= *j);
    return comparisons;
}

//type = 0 -> Classic QuickSort
//type = 1 -> First Element QuickSort
//type = 2 -> Median of Three
long int Sort(int Esq, int Dir, int *A, int type, int *swap) {
    int i, j;
    long int comparisons;
    if ((type == 2) && (Esq-Dir <= 2))
        type = 0;   //setting to classic quicksort is there's less than 3 elements in array
    comparisons = Partition(Esq, Dir, &i, &j, A, swap, type);
    if (Esq < j) comparisons += Sort(Esq, j, A, type, swap);
    if (i < Dir) comparisons += Sort(i, Dir, A, type, swap);
    return comparisons;
}

long int SortI(int Esq, int Dir, int *A, int MinSize, int *swap) {
    int i, j;
    long int comparisons;
    //Call partition while the array's size is bigger than Size
    if ((Dir - Esq) > MinSize) {
        comparisons = Partition(Esq, Dir, &i, &j, A, swap, 2);
        comparisons += SortI(Esq, j, A, MinSize, swap);
        comparisons += SortI(i, Dir, A, MinSize, swap);
    }
    else
        comparisons = Insertion(A, Esq, Dir+1, swap);
    return comparisons;
}

long int QuickSort(int *A, int n, const char *quickSortType, int *swap) {
    long int comparisons = 0;
    if (!strcmp(quickSortType, "QC")) {
        /* execute classic quicksort */
        comparisons = Sort(0, n-1, A, 0, swap);
    } else if (!strcmp(quickSortType, "QM3")) {
        /* execute median of three quicksort */
        comparisons = Sort(0, n-1, A, 2, swap);
    } else if(!strcmp(quickSortType, "QPE")) {
        /* execute first element quicksort */
        comparisons = Sort(0, n-1, A, 1, swap);
    } else if(!strcmp(quickSortType, "QI1")) {
        /* execute 1% insertion quicksort */
        comparisons = SortI(0, n-1, A, n/100, swap);
    } else if(!strcmp(quickSortType, "QI5")) {
        /* execute 5% insertion quicksort */
        comparisons = SortI(0, n-1, A, n/20, swap);
    } else if(!strcmp(quickSortType, "QI10")) {
        /* execute 10% insertion quicksort */
        comparisons = SortI(0, n-1, A, n/10, swap);
    } else if(!strcmp(quickSortType, "QNR")){
        /* execute non-recursive quicksort */
        comparisons = NRQuickSort(A, n, swap);
    } else {
        /* execute nothing */
    }
    return comparisons;
}

int Insertion(int *A, int Esq, int Dir, int *swap) {
    int i, j;
    int aux, comparisons = 0;
    for (i = Esq; i < Dir; i++) {
        aux = A[i];
        j = i-1;
        while (j >= 0) {
            comparisons++;
            if(aux >= A[j])
                break;

            A[j+1] = A[j];
            j--;(*swap)++;
        }
        A[j+1] = aux;
    }
    return comparisons;
}

//Non-Recusive QuickSort
int NRQuickSort(int *A, int n, int *swap) {
    Stack pilha;
    Item item;  //left e right
    int left, right, i, j, comparisons = 0;
 
    MakeEmptyStack(&pilha);
    left = 0;
    right = n-1;
    item.right = right;
    item.left = left;
    Push(item, &pilha);
    do {
        if (right > left) {
            comparisons += Partition(left, right, &i, &j, A, swap, 0);
            if ((j-left) > (right-i)) {
                item.right = j;
                item.left = left;
                Push(item, &pilha);
                left = i;
            }
            else {
                item.left = i;
                item.right = right;
                Push(item, &pilha);
                right = j;
            }
        }
        else {
            Pop(&pilha, &item);
            right = item.right;
            left = item.left;
        }
    } while (!IsEmpty(&pilha));
}