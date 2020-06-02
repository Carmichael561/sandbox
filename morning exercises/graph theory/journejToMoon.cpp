unordered_map<int, list<int>> g;
unordered_map<int, bool> visited;
int c = 0;

void dfs(int vertex)
{
    if (!visited[vertex])
    {
        visited[vertex] = true;
        ++c;
        for (auto i : g[vertex])
        {
            dfs(i);
        }
    }
}

int journeyToMoon(int n, vector<vector<int>> a)
{
        long ret = 0;
    vector<long> countries;

    for (int i = 0; i < (int)a.size(); ++i)
    {
        int u = a[i][0];
        int v = a[i][1];
        g[u].push_front(v);
        g[v].push_front(u);
        printf("add %d %d\n", u, v);
        visited[u] = false;
        visited[v] = false;
    }

    for (int i = 0; i < n; ++i)
        if (g.find(i) == g.end())
            countries.push_back(1);

    for (auto node : g)
    {
        int u = node.first;        
        if (visited[u] == true)
            continue;
        dfs(u);
        countries.push_back(c);
        c = 0;
    }

    ret = 0;
    long sum = 0;
    for (auto p : countries)
    {
        ret += (p*sum);
        sum += p;
    }
    return ret;
}
