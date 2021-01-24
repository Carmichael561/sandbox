#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

// Complete the highestValuePalindrome function below.

// Please either make the string static or allocate on the heap. For example,
// static char str[] = "hello world";
// return str;
//
// OR
//
// char* str = "hello world";
// return str;
//
char* highestValuePalindrome(char* s, int n, int ks) {

    char *str = strdup(s);
    char *b = s;
    char *e = s+n-1;
    int K = ks;
    
    while (b < e)
    {
        if (*b != *e){
            (int)*e > (int)*b ? (*b=*e) : (*e=*b);            
            K--;
        }
        b++;
        e--;
    }
    if (K<0) return "-1";

    int i = 0;
    int j = 0;
    for (i = 0, j = n-1; i < j; i++,j--)
    {
        if (K>=2)
        {
            if (s[i] < '9')
            {
                s[i] = s[j] = '9';
                if (str[i] == str[j])
                    K--;
                K--;
            }
        }
        else if (K==1)
            if ((str[i] != str[j]) && s[i] < '9')
            {
                s[i] = s[j] = '9'; 
                K--;
                break;
            }
    }
    if (K>=1 && i==j && (s[i] < '9'))
        s[i] = '9';
    return s;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** nk = split_string(readline());

    char* n_endptr;
    char* n_str = nk[0];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* k_endptr;
    char* k_str = nk[1];
    int k = strtol(k_str, &k_endptr, 10);

    if (k_endptr == k_str || *k_endptr != '\0') { exit(EXIT_FAILURE); }

    char* s = readline();

    char* result = highestValuePalindrome(s, n, k);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
