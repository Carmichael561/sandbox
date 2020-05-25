#include <stdlib.h>
#include <stdio.h>


int insert_sort(int *Buff, int N)
{
    int i = 1;
    while(i <= N-1)
        {
            int j = i;
            while(j > 0 && Buff[j] < Buff[j-1])
                {
                    int tmp = Buff[j];
                    Buff[j] = Buff[j-1];
                    Buff[j-1] = tmp;
                    --j;
                }
            ++i;
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
    insert_sort(A, sizeof(A)/sizeof(A[0]));
    print(A, sizeof(A)/sizeof(A[0]));
    return 0;
}
