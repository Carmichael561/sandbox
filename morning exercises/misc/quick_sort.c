#include <stdlib.h>
#include <stdio.h>

void print(int *Buff, int N)
{
    int i;
    printf("\n");
    for (i = 0; i < N; i++)
        {
            printf("%d\t", Buff[i]);
        }
    printf("\n");
}

void quick_sort(int *Buff, int begin, int end)
{
    int tmp, i, j;
    int pivot;

    if (begin >= end)
        return;

    i = begin;
    j = end;
    pivot = begin;

    while (1)
        {
            while(i < end && Buff[i] <= Buff[pivot])
                ++i;
            while(j >= begin && Buff[j] > Buff[pivot])
                --j;

            if (i >= j)
                break;
            
            tmp = Buff[i];
            Buff[i] = Buff[j];
            Buff[j] = tmp;
        }

    tmp = Buff[j];
    Buff[j] = Buff[pivot];
    Buff[pivot] = tmp;

    print(Buff, sizeof(Buff)/sizeof(Buff[0]));
    quick_sort(Buff, begin, j-1);
    quick_sort(Buff, j+1, end);
}

void quick_sort_pivot_end(int *Buff, int begin, int end)
{
    int i, j, tmp, pivot;
    if (begin >= end) return;
    i = begin, j = end, pivot = end;
    while(1) {
        while(i < end && Buff[i] < Buff[pivot]) i++;
        while (j >= begin && Buff[j] >= Buff[pivot]) j--;
        if (i >= j) break;
        tmp = Buff[i]; Buff[i] = Buff[j]; Buff[j] = tmp;
    }
    tmp = Buff[i]; Buff[i] = Buff[pivot]; Buff[pivot] = tmp;
    quick_sort_pivot_end(Buff, begin, i-1);
    quick_sort_pivot_end(Buff, i+1, end);
}

int main()
{
    int A[] = {-100, 1, 3, 5, -1, 2, 6, 2, 4, 9, 100, 213, 0, 4, 274, -5, 10, 1000};
    //int A[] = {100, 50, 10};
    print(A, sizeof(A)/sizeof(A[0]));
    //    quick_sort(A, 0, sizeof(A)/sizeof(A[0]));
    quick_sort_pivot_end(A, 0, sizeof(A)/sizeof(A[0]));
    print(A, sizeof(A)/sizeof(A[0]));
    printf("test %d\n", 3/2);
    return 0;
}
