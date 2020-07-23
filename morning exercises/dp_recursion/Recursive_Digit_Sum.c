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

int fine_digit(long long int n)
{
    printf("fine_digit = %lld\n", n);

    if (n < 10)
        return n;

    long long int sum = 0;
    
    while (n)
    {
        char i = n % 10;
        sum += i;
        n -= i;
        n /= 10;
    }
    return fine_digit(sum);
}


// Complete the superDigit function below.
int superDigit1(char* n, int k) {

    printf("k = %d\n", k);
    printf("%s\n", n);

    if (k==0)
        return 0;

    int len = strlen(n);
    int total_len = len*k;
    char *str = malloc(total_len + 1);
    if (!str)
        return 0;
    int i = 0;
    while (k > 0)
    {
        strncpy(str + (len*i), n, len);
        --k;
        ++i;
    }
    str[total_len] = '\0';
    printf("%s\n", str);

    if (total_len == 1)
        return atoi(str);

    int ret = 0;
    long long int num = 0;

    char *s = str;
    while (s[0] != '\0')
    {
        num += s[0] - 48;
        ++s;
    }

    printf("num = %lld\n", num);

    ret = fine_digit(num);

    printf("ret = %d\n", ret);

    return ret;
}







//////////////second try

inline int add_dig_to_digstr(char* s, int n)
{
    if (n <= 0)
        return 0;

    long long int len = strlen(s);
    int i = len - 1;
    char *t = s+i;
    int a = n, k = 0, m = 0;

    while (a && i >= 0)
    {
        k = t[0] - 48;
        m = (k+a)%10;
        a = (k+a-m)/10;
        t[0] = m + 48;
        --i;
        --t;
        //printf("k = %d, m = %d, a = %d\n", k, m, a);
    }
    return a;
}

inline int sum_digs_of_str(char * s)
{
    //printf("1 sum_digs_of_str: %s\n", s);
    int n, a;
    long long int len = strlen(s);
    if (len == 1)
        return s[0]-48;
    n = s[len-1]-48;
    s[len-1] = '\0';
    //printf("2 sum_digs_of_str: %s, %d\n", s, n);
    a = add_dig_to_digstr(s, n);
    //printf("3 sum_digs_of_str: %s, %d, a=%d\n", s, n, a);

    if (a)
        s[len-1] = a+48;
    s[len] = '\0';
    return sum_digs_of_str(s);
}

int superDigit(char* n, int k) {

    printf("k = %d\n", k);
    printf("%s\n", n);

    if (k==0)
        return 0;

    long long int len = strlen(n);
    long long int total_len = len*k;
    char *str = malloc(total_len + 10);
    memset(str, '\0', total_len+10);
    if (!str)
        return 0;
    int i = 0;
    while (k > 0)
    {
        strncpy(str + (len*i), n, len);
        --k;
        ++i;
    }
    str[total_len] = '\0';
    printf("%s\n", str);

    if (total_len == 1)
        return atoi(str);

    int ret = 0;

    ret = sum_digs_of_str(str);

    //printf("ret = %d\n", ret);
    return ret;
}


int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** nk = split_string(readline());

    char* n = nk[0];

    char* k_endptr;
    char* k_str = nk[1];
    int k = strtol(k_str, &k_endptr, 10);

    if (k_endptr == k_str || *k_endptr != '\0') { exit(EXIT_FAILURE); }

    int result = superDigit(n, k);

    fprintf(fptr, "%d\n", result);

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

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

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
