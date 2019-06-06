#include "headers/sorting.h"
#include "headers/stack.h"

#include <string.h>
#include <stdio.h>

int GetMedian(int x1, int x2, int x3) {
    if (x1 >= x2 && x1 <= x3 || x1 >= x3 && x1 <= x2)
        return x1;
    if (x2 >= x1 && x2 <= x3 || x2 >= x3 && x2 <= x1)
        return x2;
    return x3;
}

int GetPivot(int *A, int Left, int Right, int type) {
    if (type == 0)
        return A[(Left + Right)/2]; /* middle element is pivot */
    else if (type == 1) 
        return A[Left]; /* first element is pivot */
    else
        return GetMedian(A[Left], A[(Left + Right)/2], A[Right]); /* obtaining the pivot by median of three*/
}

void Swap(int *x1, int *x2) {
    int aux = *x1;
    *x1 = *x2;
    *x2 = aux;
}

int Partition(int Left, int Right, int *i, int *j, int *A, long *swap, int type) {
    int x, comparisons = 0;
    *i = Left; *j = Right;
    x = GetPivot(A, Left, Right, type);
    
    do {
        while (x > A[*i]) { 
            (*i)++; comparisons++;
        } comparisons++;
        while (x < A[*j]) {
            (*j)--; comparisons++;
        } comparisons++;
        
        if (*i <= *j) {
            Swap(&A[*i], &A[*j]);
            (*i)++; (*j)--; (*swap)++;
        }
    } while (*i <= *j);
    return comparisons;
}

//type = 0 -> Classic QuickSort
//type = 1 -> First Element QuickSort
//type = 2 -> Median of Three
long Sort(int Left, int Right, int *A, int type, long *swap) {
    int i, j;
    long int comparisons;
    if ((type == 2) && (Left-Right <= 2))
        type = 0;   //setting to classic quicksort is there's less than 3 elements in array
    comparisons = Partition(Left, Right, &i, &j, A, swap, type);
    if (Left < j) comparisons += Sort(Left, j, A, type, swap);
    if (i < Right) comparisons += Sort(i, Right, A, type, swap);
    return comparisons;
}

long SortI(int Left, int Right, int *A, int MinSize, long *swap) {
    int i, j;
    long int comparisons;
    //Call partition while the array's size is bigger than MinSize
    if ((Right - Left) > MinSize) {
        if((Right - Left) > 2)
            comparisons = Partition(Left, Right, &i, &j, A, swap, 2);
        else
            comparisons = Partition(Left, Right, &i, &j, A, swap, 0);
        comparisons += SortI(Left, j, A, MinSize, swap);
        comparisons += SortI(i, Right, A, MinSize, swap);
    }
    else
        comparisons = Insertion(A, Left, Right+1, swap);
    return comparisons;
}

long QuickSort(int *A, int n, const char *quickSortType, long *swap) {
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

long Insertion(int *A, int Left, int Right, long *swap) {
    int i, j;
    int aux, comparisons = 0;
    for (i = Left; i < Right; i++) {
        aux = A[i];
        j = i-1;
        while (j >= 0) {
            comparisons++;
            if(aux >= A[j]) break;

            A[j+1] = A[j];
            j--; (*swap)++;
        }
        A[j+1] = aux;
    }
    return comparisons;
}

//Non-Recusive QuickSort
long NRQuickSort(int *A, int n, long *swap) {
    Stack pilha;
    Item item;  //left e right
    int left, right, i, j;
    long comparisons = 0;
 
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
    return comparisons;
}