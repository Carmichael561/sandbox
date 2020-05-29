vector<int> bfs(int n, int m, vector<vector<int>> edges, int s) 
{
    vector<int> path(n+1, -1);
    int max = 10000000;
    int edge_cost = 6;
    vector<bool> visited(n+1, false);
    vector<list<int>> graph(n+1);

    printf("n=%d, m=%d, edges.size=%d\n", n, m, (int)edges.size());

    for (int i = 0; i < m; ++i)
    {
        graph[edges[i][0]].push_front(edges[i][1]);
        graph[edges[i][1]].push_front(edges[i][0]);
    }

    //for (int e = 0; e <= n; ++e)
    int k = 0;
    for (auto e : graph)
    {
        printf("%d: ", k);
        for (auto l : e)
            printf("%d\t", l);
        printf("\n");
        ++k;
    }

    int i = s;
    path[i] = 0;
    while (1)
    {
        visited[i] = true;
        printf("start from %d\n", i);
        for (auto e : graph[i])
        {
            if (visited[e])
                continue;

            int p = path[e] == -1 ? max : path[e];

            if (p > path[i] + edge_cost)
                path[e] = path[i] + edge_cost;

            printf("path to %d is %d\n", e, path[e]);
        }

        int min = max;
        for (int j = 1; j <= n; ++j)
        {
            if (!visited[j] && path[j] != -1 && path[j] < min)
                min = path[j],
                i = j;
        }
        if (min == max)
            break;
    }
    path.erase(path.begin()+s);
    path.erase(path.begin());
    return path;
}

