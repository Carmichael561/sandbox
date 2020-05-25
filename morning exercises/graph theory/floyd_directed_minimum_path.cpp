#define MAX_W 10000
void floyd(int nodes, vector<int> from, vector<int> to, vector<int> w, int x, int y)
{
    static bool init = false;
    static vector<vector<int>> dist(nodes+1, vector<int>(nodes+1, -1));
    
    if (init)
    {
        printf("%d\n", dist[x][y]);
        return;
    }

    int m = w.size();
    for (int i = 0; i < m; ++i)
    {
        int v1 = from[i];
        int v2 = to[i];
        dist[v1][v2] = w[i];
        dist[v1][v1] = 0;
        dist[v2][v2] = 0;
    }

    for (int k = 1; k <= nodes; ++k)
    for (int i = 1; i <= nodes; ++i)
    {
        for (int j = 1; j <= nodes; ++j)
        {
            if (i==j || i==k || j==k) continue;

            int current_path = dist[i][j];
            if (current_path < 0) current_path = MAX_W;
            
            int new_path1 = dist[i][k];
            if (new_path1 < 0) new_path1 = MAX_W;

            int new_path2 = dist[k][j];
            if (new_path2 < 0) new_path2 = MAX_W;
            
            if (current_path > new_path1 + new_path2)
                dist[i][j] = new_path1 + new_path2;
        }
    }

    init = true;
    printf("%d\n", dist[x][y]);
}


int main()
{
    int road_nodes;
    int road_edges;

    cin >> road_nodes >> road_edges;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> road_from(road_edges);
    vector<int> road_to(road_edges);
    vector<int> road_weight(road_edges);

    for (int i = 0; i < road_edges; i++) {
        cin >> road_from[i] >> road_to[i] >> road_weight[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string xy_temp;
        getline(cin, xy_temp);

        vector<string> xy = split_string(xy_temp);

        int x = stoi(xy[0]);
        int y = stoi(xy[1]);

        floyd(road_nodes, road_from, road_to, road_weight, x, y);
    }

    return 0;
}
 
