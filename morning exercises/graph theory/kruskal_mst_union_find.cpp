using namespace std;



struct UnionFind
{
    vector<int> ufmap;
    vector<int> rank;
    UnionFind(int n)
    {
        for(int i = 0; i <=n; ++i)
        {
            ufmap.push_back(i);
            rank.push_back(0);
        }
    }
    int find(int index)
    {
        if (ufmap[index] == index)
            return index;
        ufmap[index] = find(ufmap[index]);
        return ufmap[index];
    }
    void united(int index1, int index2)
    {
        int set1 = find(index1);
        int set2 = find(index2);
        if (set1 == set2)
            return;
        if (rank[set1] == rank[set2])
        {
            ufmap[set1] = set2;
            ++rank[set2];
        } 
        else if (rank[set1] > rank[set2])
            ufmap[set2] = set1;
        else
            ufmap[set1] = set2;
    }
};

struct cmp
{
    bool operator() (pair<int, pair<int, int>> &e1, pair<int, pair<int, int>> &e2)
    {
        return e1.first > e2.first;
    }
};

typedef pair<int, pair<int, int>> gpair;

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight)
{
    int ret = 0;
    int m = g_weight.size();

    priority_queue<gpair, vector<gpair>, cmp> pq;
    for(int i = 0; i < m; ++i)
        pq.push({g_weight[i], {g_from[i], g_to[i]}});

    UnionFind uf(g_nodes);

    while (!pq.empty())
    {
        int v1 = pq.top().second.first;
        int v2 = pq.top().second.second;

        int set1 = uf.find(v1);
        int set2 = uf.find(v2);
        if (set1 != set2)
        {
            uf.united(set1, set2);
            ret += pq.top().first;
        }

        pq.pop();
    }
    printf("%d\n", ret);
    return ret;
}


int main()
{
    string g_nodes_edges_temp;
    getline(cin, g_nodes_edges_temp);

    vector<string> g_nodes_edges = split(rtrim(g_nodes_edges_temp));

    int g_nodes = stoi(g_nodes_edges[0]);
    int g_edges = stoi(g_nodes_edges[1]);

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);

    for (int i = 0; i < g_edges; i++) {
        string g_from_to_weight_temp;
        getline(cin, g_from_to_weight_temp);

        vector<string> g_from_to_weight = split(rtrim(g_from_to_weight_temp));

        int g_from_temp = stoi(g_from_to_weight[0]);
        int g_to_temp = stoi(g_from_to_weight[1]);
        int g_weight_temp = stoi(g_from_to_weight[2]);

        g_from[i] = g_from_temp;
        g_to[i] = g_to_temp;
        g_weight[i] = g_weight_temp;
    }

    kruskals(g_nodes, g_from, g_to, g_weight);

    return 0;
}

