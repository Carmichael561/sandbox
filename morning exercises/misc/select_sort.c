#include <stdio.h>
#include <stdlib.h>

int select_sort(int *Buff, int N)
{
    int i;
    int j;
    int tmp;
    int min;
    for (i = 0; i < N; ++i)
        {
            min = i;
            for (j = i+1; j < N; j++)
                {
                    if (Buff[min] > Buff[j]) {
                        min = j;
                    }
                }
            if (min != i) {
                tmp = Buff[i];
                Buff[i] = Buff[min];
                Buff[min] = tmp;
            }
        }
    return 0;
}

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

int main()
{
    int A[] = {-100, 1, 3, 5, -1, 2, 6, 2, 4, 9, 100, 213, 0, 4, 274, -5, 10};
    print(A, sizeof(A)/sizeof(A[0]));
    select_sort(A, sizeof(A)/sizeof(A[0]));
    print(A, sizeof(A)/sizeof(A[0]));
    return 0;
}
