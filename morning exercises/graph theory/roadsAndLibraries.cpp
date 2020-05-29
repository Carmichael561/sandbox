struct UnionFind
{
    vector<int> indexes;
    vector<int> rank;
    UnionFind(int n)
    {
        indexes.reserve(n+1);
        rank.reserve(n+1);
        for (int i = 0; i <= n; ++i)
            indexes[i] = i,
            rank[i] = 0;
    }
    int find(int k)
    {
        if (k == indexes[k])
            return k;
        indexes[k] = find(indexes[k]);
        return indexes[k];
    }

    int united(int k1, int k2)
    {
        int set1 = find(k1);
        int set2 = find(k2);
        printf("k1=%d set1=%d,    k2=%d set2=%d\n", k1, set1, k2, set2);
        if (set1 == set2)
        {
            return -1;
        }
        if (rank[set1] >= rank[set2])
        {
            indexes[set2] = set1;
            ++rank[set1];
            return 0;
        }
        indexes[set1] = set2;
        ++rank[set2];
        return 0;
    }
};

long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities)
{
    long ret = 0;
    UnionFind uf(n);
    int m = cities.size();

    printf("n=%d  m=%d,  lib=%d  road=%d\n", n, m, c_lib, c_road);

    
    for (int i = 0; i < m; ++i)
    {
        int r = uf.united(cities[i][0], cities[i][1]);
        if (!r)
        { 
            ret += c_road;
            printf("build road %d --- %d\n", cities[i][0], cities[i][1]);
        }
        else {
            printf("DO NOT BUILD %d --- %d\n", cities[i][0], cities[i][1]);
        }
    }

    for (int i = 1; i <= n; ++i)
        if (uf.indexes[i] == i)
            ret += c_lib;

    long l = (long)c_lib * (long)n;
    if (ret > l)
        ret = l;

    return ret;
}

