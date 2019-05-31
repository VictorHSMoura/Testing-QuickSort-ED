int GetMedian(int x1, int x2, int x3);
int GetPivot(int *A, int Left, int Right, int type);
void Swap(int *x1, int *x2);
int Partition(int Left, int Right, int *i, int *j, int *A, long *swap, int type);
long Sort(int Left, int Right, int *A, int type, long *swap);
long SortI(int Left, int Right, int *A, int MinSize, long *swap);
long QuickSort(int *A, int n, const char *quickSortType, long *swap);
long Insertion(int *A, int Left, int Right, long *swap);
long NRQuickSort(int *A, int n, long *swap);