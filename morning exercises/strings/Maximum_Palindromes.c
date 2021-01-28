unsigned long long int n = 1000000007; //(A + B + … + Z)!/(A! B! … Z!) mod M
unsigned long long int factorial(unsigned long long int n)
{
    if (n == 0) return 1;
    return n * factorial(n-1);
}

int answerQuery (int l, int r) 
{
    int fr[128] = {0};
    unsigned long long int fact[128] = {0};
    unsigned long long int sum2 = 0;
    unsigned long long int ret = 1;
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
            fact[i] = factorial(fr[i]);
        }
    
    for (int i = 0; i < 128; i++)
        if (fact[i])
            ret *= fact[i];
    
    ret = factorial(sum2) / ret;
        
    if (odd)
        ret *= odd;    
        
    return ret;
}
