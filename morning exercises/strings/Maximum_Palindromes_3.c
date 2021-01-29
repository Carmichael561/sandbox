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
#define STR_LEN 100010
static unsigned long long int f[STR_LEN];
static unsigned long long int modular_multiplicative_inverse_buffer[STR_LEN];
static char* str;
static int **table;

/*
find MMI to a;
(a^prime)%prime = a;
(a^prime-1)%prime = 1;
(a^prime-2)%prime = 1/a;
MMI = a^prime-2;
 */
long long int mmi( long long int a,  long long int prime_2, long long int prime) 
{
    if (prime_2 == 0) return 1;
    long long int p = mmi(a, prime_2 / 2, prime) % prime;
    p = (p * p) % prime;
    return (prime_2 % 2 == 0) ? p : (a * p) % prime;
}

void initialize(char* s) 
{
    str = s;
    int n = strlen(s);
    f[0] = 1;
    modular_multiplicative_inverse_buffer[0] = 1;
    for (int i = 1; i < n; i++)
    {
a        f[i] = ( (f[i-1] * i) % PRIME );
        modular_multiplicative_inverse_buffer[i] = mmi(f[i], PRIME-2, PRIME);
    }
    
    table = malloc(sizeof(int*) * (n+1));
    for (int i = 0; i <= n; i++)
        table[i] = malloc(sizeof(int)*26);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j < 26; j++)
            table[i][j] = 0;
    
    for (int i = 1; i <= n; i++)
        table[i][s[i-1]-'a']++;
        
    for (int i = 2, j = 25; i <= n; i++, j = 25)
        while (j >= 0) {
            table[i][j] += table[i-1][j];
            j--;
        }
    
    for (int i = 0; i < n+1; i++)
    {
        for (int j = 0; j < 26; j++)
            printf("%d ", table[i][j]);
        printf("\n");
    }
}

int answerQuery(int l, int r)
{
    unsigned long long int modular_multiplicative_inverse = 1;
    unsigned long long int sum_of_fact2
	 = 1;
    unsigned long long int odd = 0;
    unsigned long long int even2 = 0;
    
    for (int i = 0; i < 26; i++)
    {
        unsigned long long int num_of_chars = table[r][i] - table[l-1][i];
        if (num_of_chars <= 0) continue;
        if ((num_of_chars % 2) == 1) odd++;
        even2 += (num_of_chars / 2);
        modular_multiplicative_inverse *= modular_multiplicative_inverse_buffer[num_of_chars / 2];
        modular_multiplicative_inverse %= PRIME;
    }
    sum_of_fact2 =  f[even2];
    sum_of_fact2 %= PRIME;
    
    unsigned long long int ret = 0;
    
    ret = sum_of_fact2 * modular_multiplicative_inverse;
    
    ret %= PRIME;
    if (odd)
        return (ret * odd) % PRIME;
    return ret;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

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
