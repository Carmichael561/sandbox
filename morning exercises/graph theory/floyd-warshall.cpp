int FloydPath(vector<vector<int>> edges, int A, int B) 
{
    int max = numeric_limits<int>::max();
    vector<vector<int>> g(1024, vector<int>(1024, max));
    int m, n;
    m = edges.size();
    n = -1;
    for (int i = 0; i < m; ++i)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int c = edges[i][2];
        if (g[u][v] > c)
            g[u][v] = c;
        if (g[v][u] > c)
            g[v][u] = c;
        if (u > n) n = u;
        if (v > n) n = v;
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
            {
                if (i==j || g[i][k]==max || g[k][j]==max) continue;

                int t = (g[i][k] | g[k][j]);
                if (t < g[i][j])
                    g[i][j] = t;
            }
    return g[A][B]==max ? -1 : g[A][B];
}
