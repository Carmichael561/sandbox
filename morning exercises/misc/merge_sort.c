#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void merge(int *Buff, int b, int m, int e)
{
    int i = b, in = m, j = m + 1, jn = e;
    int k;
    int l[m-b+1];
    int r[e-m];
    for (i = 0, k = b; i < m-b+1; i++)
        {
            l[i] = Buff[k];
            k++;
            //            printf("%d\t", l[i]);
        }
    //    printf("\n");
    for (j = 0, k = m + 1; j < e-m; j++)
        {
            r[j] = Buff[k];
            k++;
            //            printf("%d\t", r[j]);
        }

    in = m - b + 1;
    jn = e - m;

    for (k = b, i = j = 0; k<=e && i<in && j<jn; k++)
        {
            if (l[i] < r[j]) {
                Buff[k] = l[i];
                i++;
            }
            else if (r[j] == l[i]) {
                Buff[k] = r[j];
                Buff[k+1] = l[i];
                j++; i++; k++;
            }
            else {
                Buff[k] = r[j];
                j++;
            }
        }
    
    while (i < in)
        {
            Buff[k] = l[i];
            i++;
            k++;
        }
    while (j < jn)
        {
            Buff[k] = r[j];
            j++;
            k++;
        }
    
}

void merge_sort(int *Buff, int begin, int end)
{
    int middle;
    if (begin >= end) return;
    middle = (end - begin) / 2 + begin;
    merge_sort(Buff, begin, middle);
    merge_sort(Buff, middle+1, end);
    merge(Buff, begin, middle, end);
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
    merge_sort(A, 0, sizeof(A)/sizeof(A[0]));
    print(A, sizeof(A)/sizeof(A[0]));
    return 0;
}
