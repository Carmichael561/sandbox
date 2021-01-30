int compar(void const * a1, void const * a2)
{
    return *(int*)a1 - *(int*)a2;
}

int equal(int n, int* a)
{
    long long int min_num_operation = 1000000000;
    qsort(a, n, sizeof(a[0]), compar);
    for (int i = 0; i < 3; i++)
    {
        long long int sum = 0;
        for (int j = 0; j < n; j++)
        {
            int delta = a[j] - a[0] + i;
                  while(true){
                    if( delta >=5 ){
                        delta -= 5;
                        sum++;
                    }else if(delta >=2){
                        delta -= 2;
                        sum++;
                    }else if (delta >= 1){
                        delta -= 1;
                        sum++;
                    } else {
                        break;
                    }
                }
        }
        if (sum < min_num_operation)
            min_num_operation = sum;
    }
    return min_num_operation;
}
