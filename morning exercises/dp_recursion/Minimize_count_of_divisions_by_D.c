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


int compar(void const * a1, void const * a2)
{
    return *(int*)a1 - *(int*)a2;
}
#define MM 200001
#define NN 100001
static int dp[MM][NN];
int minOperations(int n, int* a, int th, int d)
{
    int min_op = 1000000000;

    /*first column is a number of particular elements in original array*/
    for (int i = 0; i < n; i++)
    {
        int op = 1;
        int j = 0;
        dp[a[i]][j]++;

        while (a[i] > 0)
        {
            a[i] /= d;
            j = 1;
            while (dp[a[i]][j]) j++;
            dp[a[i]][j] = op;
            op++;
        }
    }
    
    //sort by number of operations
    for (int i = 0; i < MM; i++)
    {
        int orig = dp[i][0];
        int j = 1;
        int n = 0;
        while (dp[i][j]) n++;
        if (orig + n < th)
            dp[i][0] = -137;
        qsort(&dp[i][1], n, sizeof(int), compar);
    }

    //find minimum number of operations
    for (int i = 0; i < MM; i++)
    {
        if (dp[i][0] < 0)
            continue;

        int elems = dp[i][0];
        int ops = 0;
        int j = 1;
        while ( elems < th )
        {
            elems++;
            ops += dp[i][j];
            j++;
        }
        min_op = min_op > ops ? ops : min_op;
    }
    return min_op;
}



// First fit will be returned
/*
 * Complete the 'minOperations' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY arr
 *  2. INTEGER threshold
 *  3. INTEGER d
 */
#define N 200004
static int fr[N] = {0};
static long long int fr2[N][2] = {0};
int minOperations(int n, int* arr, int th, int d) 
{
    for (int i = 0; i < n; i++)
    {
        fr[arr[i]]++;
        if (fr[arr[i]] >= th) return 0;
    }

    for (int op = 1; op < 10000000; op++)
    {
        for (int i = 0; i < n; i++)
        {
            arr[i] /= d;
            fr2[arr[i]][0]++;
            fr2[arr[i]][1] += op;
            if ((fr2[arr[i]][0] + fr[arr[i]]) >= th)
                return fr2[arr[i]][1] - fr[arr[i]];
        }
    }
    return 0;
}
