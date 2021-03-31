#include <stdio.h>

#include "rev_lib.h"

char * test = "Hello rev";

int main(int argc, char** argv)
{
    reverse(&test);

    printf("%s\n", test);
    
    return 0;
}
