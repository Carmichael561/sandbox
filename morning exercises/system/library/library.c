#include <stdio.h>

int signature(int c, char *s)
{
    printf("%s(): %d %s\n", __func__, c, s);
    return 0;
}
