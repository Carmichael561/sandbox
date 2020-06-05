http://qiao.github.io/PathFinding.js/visual/

inline int find_minimum_path_bfs(vector<vector<int>> &a, int sx, int sy, int ex, int ey)
{
    priority_queue<pi, vector<pi>, greater<pi>> path;
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    int x = sx;
    int y = sy;
    int w;
    path.push({a[y][x], {y, x}});

    while(!path.empty())
    {
        pi top = path.top();
        path.pop();
        w = top.first;
        x = top.second.second;
        y = top.second.first;
        visited[y][x] = true;
        if (x==ex && y==ey)
            break;
        for (int i = 0; i < 4; ++i)
        {
            int ix = x + xdir[i];
            int iy = y + ydir[i];
            if (ix<0||iy<0||ix>=M||iy>=N||visited[iy][ix])
                continue;
            path.push({w+a[iy][ix], {iy, ix}});
        }
    }
    return w;
}