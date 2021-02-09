vector<int> bfs(int n, int m, vector<vector<int>> edges, int s) 
{
    vector<int> ret(n+1, -1);
    vector<list<int>> g(n+1);
    queue<int> q;
    
    for (int i = 0; i < m; i++)
    {
        int n1 = edges[i][0];
        int n2 = edges[i][1];
        g[n1].push_back(n2);
        g[n2].push_back(n1);
    }
    q.push(s);
    ret[s] = 0;
    while (!q.empty())
    {
        int k = q.front();
        q.pop();
        for (auto i : g[k])
            if (ret[i] == -1)
            {
                q.push(i);
                ret[i] = ret[k]+6;
            }
    }
    if (s == 1)
        ret.erase(ret.begin(), ret.begin()+2);
    else
    {
        ret.erase(ret.begin()+s);
        ret.erase(ret.begin());
    }
    return ret;
}
