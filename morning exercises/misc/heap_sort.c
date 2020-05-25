#include <stdio.h>
#include <stdlib.h>

/*
  convert array into max-heap
  swap first and last in max-heap
  decrement array size
  heapify root in max-heap
  goto step first
 */

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

void heapify(int *Buff, int i, int N)
{
    int largest, l, r;
    int tmp;
    largest = i;
    l = 2*largest+1;
    r = 2*largest+2;

    if (l < N && Buff[largest] < Buff[l]) 
        largest = l;
    if (r < N && Buff[largest] < Buff[r])
        largest = r;
    if (i != largest){
        tmp = Buff[i]; Buff[i] = Buff[largest]; Buff[largest] = tmp;
        heapify(Buff, largest, N);
    }
}

void heap_sort(int *Buff, int N)
{
    int i, e;
    int p;
    int tmp;
    e = N-1;
    for (i = N/2-1; i >= 0; i--)
        {
            heapify(Buff, i, N);
        }
    print(Buff, N);

    for (i = 0; i < N; ++i)
        {
            tmp = Buff[0]; Buff[0] = Buff[N-1-i]; Buff[N-1-i] = tmp;
            heapify(Buff, 0, N-1-i);
        }
}

int main()
{
    int A[] = {-100, 1, 3, 5, -1, 2, 6, 2, 4, 9, 100, 213, 0, 4, 274, -5, 10};
    print(A, sizeof(A)/sizeof(A[0]));
    heap_sort(A, sizeof(A)/sizeof(A[0]));
    print(A, sizeof(A)/sizeof(A[0]));
    return 0;
}
