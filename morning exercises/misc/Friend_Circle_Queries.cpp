#include <bits/stdc++.h>

using namespace std;

unordered_map<int, int> ds;
unordered_map<int, int> rk;
int global_max = -1;

void insert(int v)
{
    if (ds.find(v) == ds.end() && rk.find(v) == rk.end())
    {
        ds[v] = v;
        rk[v] = 1;
    }
}

int find(int v)
{
    if (ds.find(v) == ds.end())
        return -1;
    if (ds[v] == v)
        return v;
    int p = find(ds[v]);
    ds[v] = p;
    return p;
}


void united(int a, int b)
{
    int pa, pb;
    if (ds.find(a) == ds.end() || ds.find(b) == ds.end())
        return;
    pa = find(a);
    pb = find(b);
    if (pa == pb)
        return;
    if (rk.find(pa) == rk.end() || rk.find(pb) == rk.end())
        return;
    if (rk[pa] < rk[pb])
    {
        ds[pa] = pb;
        rk[pb] += rk[pa];
        if (rk[pb] > global_max)
            global_max = rk[pb];
    }
    else
    {
        ds[pb] = pa;
        rk[pa] += rk[pb];
        if (rk[pa] > global_max)
            global_max = rk[pa];
    }
}





// Complete the maxCircle function below.
vector<int> maxCircle(vector<vector<int>> q) 
{
    vector<int> ret;

    for (int i = 0; i < q.size(); ++i)
    {
        int a = q[i][0];
        int b = q[i][1];
        insert(a);
        insert(b);
        united(a, b);
        int max = global_max;
        // for (auto i : rk)
        // {
        //     if (i.second > max)
        //         max = i.second;
        // }
        ret.push_back(max);
    }
    return ret;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> queries(q);
    for (int i = 0; i < q; i++) {
        queries[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> ans = maxCircle(queries);

    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i];

        if (i != ans.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
