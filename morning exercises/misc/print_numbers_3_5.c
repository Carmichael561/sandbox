#include <stdio.h>

int main()
{
    int i;
    for (i = 1; i < 100; i++)
        {
            if ((i%3 == 0) && (i%5 == 0)) {
                printf("FizzBuzz %d\n", i);
                continue;
            }

            if (i%3 == 0){
                printf("Fizz %d\n", i);
                continue;
            }

            if (i%5 == 0){
                printf("Buzz %d\n", i);
                continue;
            }

            printf("%d\n", i);            
        }

    return 0;
}
