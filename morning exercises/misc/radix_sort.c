#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

/*
  b - base or apphabet
  d - number of digits
  n - array size
 */

void radix_sort(int *Buff, int N, int R)
{
    int b = R, d, i, j;
    int max;
    int tmp[N];
    int count[b];

    max = Buff[0];
    for (i = 1; i < N; i++) {
        if(Buff[i] > max) max = Buff[i];
    }
    d = log10(max);
    printf("N=%d, R=%d, max=%d, d=%d\n", N, R, max, d);

    for (i = 1; i <= pow10(d); i*=10)
        {

            for (j = 0; j < N; j++) tmp[j] = 0;
            for (j = 0; j < b; j++) count[j] = 0;
            
            for (j = 0; j < N; j++) {
                count[(Buff[j]/(i))%b]++;
            }

            for (j = 0; j < b; j++)
                printf("%d\t", count[j]);
            printf("\n");
            
            for (j = 1; j < b; j++) {
                count[j] += count[j-1];
            }

            for (j = 0; j < b; j++)
                printf("count[j] = %d\n", count[j]);

            for (j = 0; j < N; j++) {
                //printf("count[j] = %d\n", count[Buff]);
                tmp[count[(Buff[j]/(i))%b] - 1] = Buff[j];
                count[(Buff[j]/(i))%b]--;
            }

            for (j = 0; j < N; j++)
                Buff[j] = tmp[j];

            print(Buff, N);
        }
}

#define SQUARE(x) (x)*(x)

int main()
{
    int A[] = {100, 1, 3, 5, 1, 2, 6, 2, 4, 9, 100, 213, 0, 4, 274, 5, 10};
    print(A, sizeof(A)/sizeof(A[0]));
    radix_sort(A, sizeof(A)/sizeof(A[0]), 10);
    print(A, sizeof(A)/sizeof(A[0]));

    int i = 5;
    int j = 5;
    printf("%d\n", SQUARE((++i)));
    printf("%d\n", (++j)*(++j));
    
    return 0;
}
