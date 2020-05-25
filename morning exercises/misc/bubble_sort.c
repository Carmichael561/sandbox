#include <stdio.h>
#include <stdlib.h>


int bubble_sort(int *Buff, int N)
{
    int i, j;
    int tmp;
    for (i = 0; i < N-1; i++)
        {
            for (j = 0; j < N-1-i; j++)
                {
                    if (Buff[j] > Buff[j+1])
                        {
                            tmp = Buff[j];
                            Buff[j] = Buff[j+1];
                            Buff[j+1] = tmp;
                        }
                }
        }
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
    bubble_sort(A, sizeof(A)/sizeof(A[0]));
    print(A, sizeof(A)/sizeof(A[0]));
    return 0;
}
