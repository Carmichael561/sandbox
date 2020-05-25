#include <iostream>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <set>
#include <unordered_map>

/*
 * create graph
 * sort graph by edge waight
 * loop by sorted edges and take minimum
 * check if in loop
 * take and save into MST struct
 */

struct Edge
{
    Edge(int f, int s, int w) : NodeF(f), NodeS(s), Waight(w){}
    int NodeF;
    int NodeS;
    int Waight;
};

struct Graph
{
    std::vector<Edge> edge;

    Graph(std::initializer_list<Edge> e) : edge(e)
    {
    }
    Graph() = default;

    void insert(Edge& e)
    {
        edge.push_back(e);
    }
};

void print(Graph&);
using Node = int;
using Set = int;
using Rank = int;

class DisjointSet
{
    std::unordered_map<Node, Set> set;
    std::unordered_map<Set, Rank> rank;

public:

    void make(std::vector<Edge> &v)
    {
        std::set<Node> s;
        for_each(v.begin(), v.end(), [&](auto e){

                s.insert(e.NodeF);
                s.insert(e.NodeS);

                rank[e.NodeF] = 0;
                rank[e.NodeS] = 0;
            });
        for(auto i : s)
            set[i] = i;
    }
    
    Set find(Node n)
    {
        Set s = set[n];
        if (s == n)
            return s;
        find(s);
    }

    void unified(Node n1, Node n2)
    {
        Set s1 = find(n1);
        Set s2 = find(n2);

        if (rank[s1] < rank[s2])
            set[s1] = s2;
        else if (rank[s1] > rank[s2])
            set[s2] = s1;

        set[s1] = s2;
    }
};

void KruskalMST(Graph& g, Graph& mst)
{
    //Sort edges in graph
    std::sort(g.edge.begin(), g.edge.end(), [](auto e1, auto e2){ return  e1.Waight < e2.Waight;});
    DisjointSet ds;
    ds.make(g.edge);
    print(g);
    print(mst);

    for (int i = 0; i < g.edge.size(); i++)
    {
        Edge e = g.edge[i];
        //Check if e form loop in mst
        Node n1 = e.NodeF;
        Node n2 = e.NodeS;
        Set s1 = ds.find(n1);
        Set s2 = ds.find(n2);

        if (s1 == s2)
            continue;

        ds.unified(s1, s2);

        //Current edge did not form loop add it
        mst.insert(e);
    }
}

void print(Graph& g)
{
    for_each(g.edge.begin(), g.edge.end(), [](auto e){
            std::cout << e.NodeF << "\t" << e.NodeS << "\t\t" << e.Waight << "\n";
        });
    std::cout << "\n";
}


int main()
{
    Graph g = {Edge(0, 1, 10), Edge(1, 3, 15), Edge(3, 2, 4), Edge(0, 2, 6), Edge(0, 3, 5)};
    print(g);
    Graph MST;
    KruskalMST(g, MST);
    print(MST);


    Graph g2 = {
        Edge(0, 1, 4),
        Edge(0, 7, 8),
        Edge(1, 7, 11),
        Edge(3, 4, 9),
        Edge(4, 5, 10),
        Edge(3, 5, 14),
        Edge(1, 2, 8),
        Edge(2, 3, 7),
        Edge(7, 6, 1),
        Edge(6, 5, 2),
        Edge(7, 8, 7),
        Edge(2, 5, 4),
        Edge(8, 2, 2),
        Edge(8, 6, 6),
    };
    print(g2);
    Graph mst2;
    KruskalMST(g2, mst2);
    print(mst2);
    
    return 0;
}
