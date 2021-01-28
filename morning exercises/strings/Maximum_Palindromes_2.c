#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

#define PRIME 1000000007
#define NF 100
static unsigned long long int f[NF];
static char* str;

unsigned long long int factorial_iter(unsigned long long int n)
{
    unsigned long long int f = 1;
    if (n <= 1)
        return f;
    for (int i = 2; i <= n; i++)
    {
        f %= PRIME;
        f = (i * f) % PRIME;
    }
    return f;
}

void initialize(char* s) 
{
    str = s;
    for (int i = 0; i < NF; i++)
        f[i] = factorial_iter(i);
}

int answerQuery (int l, int r) 
{
    int fr[128] = {0};
    unsigned long long int fact[128] = {0};
    unsigned long long int sum2 = 0;
    unsigned long long int ret = 1;
    unsigned long long int tmp = 1;
    int odd = 0;
    
    l--;
    r--;
    for (int i = l; i <= r; i++)
        fr[str[i]]++;
    for (int i = 0; i < 128; i++)
        if (fr[i]) {
            if ((fr[i] % 2) == 1) {odd++; fr[i]--;}
            fr[i] /= 2;
            sum2 += fr[i];
            if (fr[i] < NF)
                fact[i] = f[fr[i]];
            else
                fact[i] = factorial_iter(fr[i]);
        }
    for (int i = 0; i < 128; i++)
        if (fact[i]) {
            ret *= fact[i];
        }


    if (sum2 < NF)
        ret = f[sum2] / ret;
    else
        ret = factorial_iter(sum2) / ret;            
    ret %= PRIME;
    odd %= PRIME;
    if (odd)
        ret *= odd;            
    return ret % PRIME;
}

int main()
{
	putenv("OUTPUT_PATH=/home/gsyl/sandbox/morning exercises/strings/RES.txt");
	char * env_p = getenv("OUTPUT_PATH");
	printf("OUTPUT_PATH: %s\n", env_p);
    FILE* fptr = fopen(env_p, "w");

    char* s = readline();

    printf("Input s: %s\n", s);

    initialize(s);

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int l = parse_int(*(first_multiple_input + 0));

        int r = parse_int(*(first_multiple_input + 1));

        int result = answerQuery(l, r);

        fprintf(fptr, "%d\n", result);
    }

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

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
