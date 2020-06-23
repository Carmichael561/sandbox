inline int bfs(int n, vector<vector<int>> &graph, int id, vector<long> &ids)
{
    int ret = 0;
    vector<bool> visited(n+1, false);
    vector<int> path(n+1, -1);
    queue<int> q;

    q.push(id);
    visited[id] = true;

    int v;
    while (!q.empty())
    {
        v = q.front();
        q.pop();

        if (v!=id && ids[v-1]==ids[id-1])
            break;

        for (auto e : graph[v])
        {
            if (visited[e])
                continue;
            q.push(e);
            visited[e] = true;
            path[e] = v;
        }
    }

    while(v != id)
    {
        v = path[v];
        ++ret;
    }
    return ret;
}


int findShortest(int graph_nodes, vector<int> graph_from, vector<int> graph_to, vector<long> ids, long val) 
{
    int n = graph_nodes;
    int m = graph_from.size();

    vector<vector<int>> graph(n+1);
    vector<int> paths;

    for (int i = 0; i < m; ++i)
    {
        int v = graph_from[i];
        int u = graph_to[i];
        graph[v].push_back(u);
        graph[u].push_back(v);
        printf("%d/%ld -> %d/%ld\n", v, ids[v-1], u, ids[u-1]);
    }

    vector<long> color_to_id;
    for (int i = 0; i < (int)ids.size(); ++i)
        if (ids[i] == val)
            color_to_id.push_back(i+1);
    if (color_to_id.size() <= 1)
        return -1;

    
    for (auto id : color_to_id)
    {
        int ret = bfs(n, graph, id, ids);
        paths.push_back(ret);
    }

    return *min_element(paths.begin(), paths.end());
}

