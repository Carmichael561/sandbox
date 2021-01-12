unsigned long long int way[300][300] = {0};

long long int ways_helper2(int n, int m, int* coins)
{
    for (int i = 0; i < 300; i++)
    for (int j = 0; j < 300; j++)
        {
            way[i][j] = 0;
        }
    
    for (int i = 0; i < 50; i++)
        way[0][i] = 1;
    
    long long int include;
    long long int exclude;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            include = exclude = 0;
            if (i - coins[j] >= 0)
            {
                include = way[i-coins[j]][j];
            }
            
            if (j >= 1)
            {
                exclude = way[i][j-1];
            }
            
            way[i][j] = include + exclude;
        }
    }
    
    return way[n][m-1];
}
