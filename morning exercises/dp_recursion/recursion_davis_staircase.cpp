#include <bits/stdc++.h>

using namespace std;

int stepPerms1(int n) 
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    if (n == 3)
        return 4;

    return stepPerms1(n-3) + stepPerms1(n-2) + stepPerms1(n-1);
}



static long arr[40] = {0, 1, 2, 4, 0};
int stepPermsdp(int n) 
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    if (n == 3)
        return 4;

    if (arr[n] != 0)
        return arr[n];

    long ret = stepPermsdp(n-3) + stepPermsdp(n-2) + stepPermsdp(n-1);
    if (arr[n] == 0)
        arr[n] = ret;

    return ret;
}


// Complete the stepPerms function below.
int stepPerms(int n)
{
    int n1 = 1;
    int n2 = 2;
    int n3 = 4;
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    if (n == 3)
        return 4;

    int i = 3;
    int ret = 0;

    while (++i <= n)
    {
        ret = n1+n2+n3;
        n1 = n2;
        n2 = n3;
        n3 = ret;
    }

    return ret;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int s;
    cin >> s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int s_itr = 0; s_itr < s; s_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int res = stepPermsdp(n);

        fout << res << "\n";
    }

    fout.close();

    return 0;
}
