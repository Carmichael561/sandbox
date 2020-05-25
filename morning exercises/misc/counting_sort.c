#include <stdio.h>
#include <stdlib.h>

void counting_sort(int *Buff, int N, int K)
{
    int alphabet[K];
    int i;
    int tmp[N];
    for (i = 0; i < N; i++)
        tmp[i] = 0;
    for (i = 0; i < K; i++)
        alphabet[i] = 0;

    for (i = 0; i < N; i++)
        alphabet[Buff[i]]++;

    for (i = 1; i < K; i++){
        alphabet[i] += alphabet[i-1];
        //        printf("alphabet[i] = %d\t", alphabet[i]);
    }
    //    printf("\n");

    for (i = 0; i < N; i++)
        {
            tmp[alphabet[Buff[i]]-1] = Buff[i];
            --alphabet[Buff[i]];
        }

    for (i = 0; i < N; i++)
        Buff[i] = tmp[i];
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
    int A[] = {9, 7, 5, 3, 1, 8, 6, 4, 3, 1, 0};
    print(A, sizeof(A)/sizeof(A[0]));
    counting_sort(A, sizeof(A)/sizeof(A[0]), 10);
    print(A, sizeof(A)/sizeof(A[0]));
    return 0;
}
