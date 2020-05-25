#include <stdio.h>
#include <stdlib.h>

quick_sort_iteration(int *Buff, int b, int e)
{
    int stack[e-b+1];
    int sp;
    int _e, _b;
    int __e, __b;
    int pivot;
    int tmp;
    
    sp = -1;

    stack[++sp] = b;
    stack[++sp] = e;

    while (sp >= 0) {
        // peek
        __e = _e = stack[sp--];
        __b = _b = stack[sp--];
        pivot = Buff[__b];

        while (1) {
            while (_b <= __e && Buff[_b] <= pivot) _b++;
            while (_e >= __b && Buff[_e] > pivot) _e--;
            if (_b >= _e) break;
            tmp = Buff[_b]; Buff[_b] = Buff[_e]; Buff[_e] = tmp;
        }
        _b = __b;
        tmp = Buff[_b]; Buff[_b] = Buff[_e]; Buff[_e] = tmp;

        if (__b >= b && __b <= _e-1) {
            stack[++sp] = __b;
            stack[++sp] = _e-1;
        }

        if (__e <= e &&_e+1 <= __e) {
            stack[++sp] = _e+1;
            stack[++sp] = __e;
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
    quick_sort_iteration(A, 0, sizeof(A)/sizeof(A[0]) - 1);
    print(A, sizeof(A)/sizeof(A[0]));
    return 0;
}
