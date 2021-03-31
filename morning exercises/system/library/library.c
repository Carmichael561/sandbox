#include <stdio.h>

int cripto = 137;

int signature(int c, char *s)
{
    cripto = c;
    printf("%s(): %d %s\n", __func__, c, s);
    return 0;
}
