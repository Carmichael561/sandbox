#include <stdio.h>
//#include <stdlib.h>

extern char _binary_embedding_txt_to_object_txt_start;
extern char _binary_embedding_txt_to_object_txt_end;

main()
{
    char*  p = &_binary_embedding_txt_to_object_txt_start;

    while ( p != &_binary_embedding_txt_to_object_txt_end ) printf("%c",*p++);
}
