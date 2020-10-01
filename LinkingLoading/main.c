#include <stdio.h>
#include <math.h>

extern void foo(int arg);

static int static_int_global = 10;

int main(int argc, char** argv)
{
    static int static_int = 20;
    puts("Test linking hello world:\n");
    sinf(static_int);
    //foo(argc);
    printf("Bue linking.\n");
    return 0;
}
