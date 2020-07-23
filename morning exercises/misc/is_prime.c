char *yes = "Prime";
char *not = "Not prime";

char* primality(int n) 
{
    if (n <= 1)
        return not;
    if (n <= 3)
        return yes;

    if (n%2==0 || n%3==0)
        return not;

    int k = sqrt(n);
    for (int i = 5; i <= k; i+=6)
    {
        if (n%i == 0 || n%(i+2) == 0)
            return not;
    }
    return yes;
}
