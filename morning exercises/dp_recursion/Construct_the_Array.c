#define PRIME 1000000007

// Complete the countArray function below.
long long x_present[100001];
long long x_absent[100001];
long countArray(int n, int k, int x)
{
    // Return the number of ways to fill in the array.
    // n == 1 : i=0
    x_present[0] = (x==1) ? 1 : 0;
    x_absent[0]  = (x==1) ? 0 : 1;
    
    for (int i = 1; i < n; i++)
    {
        x_present[i] = x_absent[i-1] % PRIME;
        x_absent[i]  = (x_present[i-1]*(k-1) + x_absent[i-1]*(k-1) - x_absent[i-1]) % PRIME;
        //x_absent[i] = (x_present[i-1]*(k-1) + x_absent[i-1]*(k-2)) % PRIME;
    }
    return x_present[n-1];
}
