
int comp(const void* a1, const void* a2)
{
    return (*(int*)a1 - *(int*)a2);
}

long getWays2(int n, int c_count, long* c)
{
    if (n == 0) return 1;
    if (n > 0 && c_count <= 0) return 0;
    if (n < 0) return 0;
    
    return getWays2(n, c_count - 1, c) + 
           getWays2(n - c[c_count - 1], c_count, c);
}

long getWays(int n, int c_count, long* c) 
{
    qsort(c, c_count, sizeof(c[0]), comp);
    
    long **dp;
    dp = malloc((n+1)*sizeof(long));
    for (int i = 0; i < n+1; i++)
    {
        dp[i] = malloc(c_count*sizeof(long));
        memset(dp[i], 0, c_count*sizeof(long));
    }
        
    for (int j = 0; j < c_count; j++)
        dp[0][j] = 1;
    for (int i = 1; i < n+1; i++)
        dp[i][0] = i%c[0]==0 ? 1 : 0;

    for (int j = 1; j < c_count; j++)
    {
        int m = c[j];
        for (int i = 1; i < n+1; i++)
        {
            dp[i][j] += dp[i][j-1];
            if (i - m >= 0)
                dp[i][j] += dp[i-m][j];
        }
    }

    long ret = dp[n][c_count-1];
    for (int i = 0; i < n+1; i++)
        free(dp[i]);
    free(dp);
    return ret;
}
