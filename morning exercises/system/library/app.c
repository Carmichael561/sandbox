#include <stdio.h>
#include "library.h"

int main(int argc, char** argv)
{
    printf("argc=%d, argv[1]=%s\n", argc, argv[1]);

    signature(argc, argv[1]);
    
    return 0;
}
