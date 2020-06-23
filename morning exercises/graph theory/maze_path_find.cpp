http://qiao.github.io/PathFinding.js/visual/

int N, M;
typedef pair<int, pair<int, int>> pi; 

int xdir[] = {0, 0, -1, 1};
int ydir[] = {-1, 1, 0, 0};

int endx, endy;

void find_minimum_path_dfs(vector<vector<int>> &a, vector<vector<bool>> &visited, int x, int y, int &w)
{
    visited[y][x] = true;
    for (int i = 0; i < 4; ++i)
    {
        int ix = x + xdir[i];
        int iy = y + ydir[i];
        if (ix<0||iy<0||ix>=M||iy>=N||visited[iy][ix]) continue;
        if (ix==endx && iy==endy)
        {
            w+=a[iy][ix];
            break;
        }
        find_minimum_path_dfs(a, visited, ix, iy, w);
        if (w)
        {
            w+=a[iy][ix];
            break;
        }
    }
}

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

vector<int> shortestPath(vector<vector<int>> a, vector<vector<int>> q)
{
    N = a.size();
    M = a[0].size();
    int Q = q.size();
    vector<int> ret;
    for (int i = 0; i < Q; ++i)
    {
        int w = 0;
        w = find_minimum_path_bfs(a, q[i][1], q[i][0], q[i][3], q[i][2]);

        // vector<vector<bool>> seen(N, vector<bool>(M, false));
        // endx = q[i][3];
        // endy = q[i][2];
        // int sx = q[i][1];
        // int sy = q[i][0];
        // w = 0;
        // find_minimum_path_dfs(a, seen, sx, sy, w);
        ret.push_back(w);
    }
    return ret;
}