#include <stdio.h>
#include "library.h"

int main(int argc, char** argv) {
        printf("argc=%d, argv[1]=%s cripto=%d\n", argc, argv[1], cripto);

        cripto = 220;
    
signature(argc, argv[1]);
    
    return 0;
}
