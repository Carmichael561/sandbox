int prims(int n, vector<vector<int>> edges, int start)
{
    int m = edges.size();
    
    vector<list<pair<int, int>>> g(n+1);
    vector<bool> v(n+1);
    vector<int> mst(n+1);
    int min, next;

    for (int i = 0; i < m; ++i)
    {
        int v1 = edges[i][0];
        int v2 = edges[i][1];
        int e = edges[i][2];
        g[v1].push_front(make_pair(v2, e));
        g[v2].push_front(make_pair(v1, e));
    }

    int k = 1;
    v[start] = true;
    mst[start] = 0;
    while (k != n)
    {
        min = numeric_limits<int>::max();
        for (int i = 1; i <= n; ++i)
        {
            if (v[i] == false)
                continue;

            for (auto l : g[i])
            {
                if (v[l.first]==false && l.second < min)
                {
                    min = l.second;
                    next = l.first;
                }
            }
        }
        v[next] = true;
        mst[next] = min;
        ++k;
    }




    return accumulate(mst.begin(), mst.end(), 0);
}

int main()
{
    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> edges(m);
    for (int i = 0; i < m; i++) {
        edges[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> edges[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int start;
    cin >> start;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int result = prims(n, edges, start);

    fout << result << "\n";

    return 0;
}
