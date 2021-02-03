#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

#define MIN(a, b) ((a)<(b)?(a):(b))
#define MAX(a, b) ((a)<(b)?(b):(a))
static int dp[1501] = {0};

int substringDiffHelper(int k, char* s1, char* s2, int i, int j)
{
    int len = strlen(s1) - MAX(i, j);
    memset(dp, 0, sizeof(dp));
    int t = 0;
    while(t < len)
    {
        dp[t] = (s1[i] == s2[j]) ? 0 : 1;
        t++;
        i++;
        j++;
    }    

    int max_len = 0;
    t = 0;
    int errors = 0;
    int s = 0;
    
    while (t < len) 
    {
        while (errors <= k && t < len)
        {
            errors += dp[t];
            if (errors <= k)
                max_len = (t-s+1) > max_len ? (t-s+1) : max_len;
            t++;
        }
        
        while(errors > k && s < t)
        {
            errors -= dp[s];
            s++;
        }
    }
    return max_len;
}

int substringDiff(int k, char* s1, char* s2)
{
    int max = 0;
    int len = strlen(s1);
    
    for (int i = 0; i < len; i++)
    {
        int ret = substringDiffHelper(k, s1, s2, 0, i);
        if (ret > max) max = ret;
    }
    
    for (int i = 1; i < len; i++)
    {
        int ret = substringDiffHelper(k, s1, s2, i, 0);
        if (ret > max) max = ret;
    }
    
    return max;
}


// Complete the substringDiff function below.
int substringDiff_error(int k, char* s1, char* s2) 
{
    int ret = 0;
    int diff = 0;
    int len = strlen(s1);
    int * a = malloc(sizeof(int) * len);
    if (!a)
        return -1;
    memset(a, 0, sizeof(int) * len);

    char *c1 = s1;
    char *c2 = s2;
    int i = 0;
    while(*c1 != '\0')
    {
        if ((int)*c1 != (int)*c2) {
            a[i] = 0;
            diff++;
        }
        else {
            a[i] = 1;
        }
        printf("%d  ", a[i]);
        i++;
        c1++;
        c2++;
    }
    printf("\n");
    
    for (int i = 0; i < len; i++)
    {
        int n = k;
        int j = i;
        while ((n || a[j]) && j < len)
        {
            if (!a[j])
                n--;
            j++;
        }
        ret = (j-i) > ret ? j-i : ret;
    }

    return ret;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* t_endptr;
    char* t_str = readline();
    int t = strtol(t_str, &t_endptr, 10);

    if (t_endptr == t_str || *t_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** kS1S2 = split_string(readline());

        char* k_endptr;
        char* k_str = kS1S2[0];
        int k = strtol(k_str, &k_endptr, 10);

        if (k_endptr == k_str || *k_endptr != '\0') { exit(EXIT_FAILURE); }

        char* s1 = kS1S2[1];

        char* s2 = kS1S2[2];

        int result = substringDiff(k, s1, s2);

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
