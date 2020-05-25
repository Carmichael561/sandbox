#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

class DisjointSet
{
public:
    using Node = int;
    using Set  = int;
    using Rank = int;

public:
    void make(std::vector<Node> &v)
    {
        for (auto i : v)
            set[i] = i, rank[i] = 0;
    }

    Set find(Node n)
    {
        Set s = set[n];
        if (s == n)
            return s;

        find(s);
    }

    void united(Node n, Node m)
    {
        Set s1 = find(n);
        Set s2 = find(m);


        if (rank[s1] > rank[s2])
            set[s2] = s1;

        else if (rank[s1] < rank[s2])
            set[s1] = s2;
        
        set[s1] = s2;
    }

private:
    std::unordered_map<Node, Set> set;
    std::unordered_map<Node, Rank> rank;
};

template <typename U>
struct Graph
{
    using Node = int;
    std::vector<U> edge;

    template <typename T>
    Graph(T edg)
    {
        edge.push_back(std::forward<T>(edg));
    }

    template <typename T, typename... Args>
    Graph(T edg, Args... args) : Graph(std::forward<T>(args)...)
    {
        edge.push_back(std::forward<T>(edg));
    }

    void print()
    {
        std::cout << "Print:\n";
        for_each(edge.begin(), edge.end(), [](auto e){
                std::cout << e.first << "\t\t" << e.second << std::endl;
            });
    }
};


bool hasLoop(Graph<std::pair<int, int>> &g)
{
    bool loop = false;
    std::set<int> s;
    std::vector<int> v;
    DisjointSet ds;
    for(int i = 0; i < g.edge.size(); i++)
    {
        s.insert(g.edge[i].first);
        s.insert(g.edge[i].second);
        
    }
    std::copy(s.begin(), s.end(), std::back_inserter(v));
    ds.make(v);

    for_each(v.begin(), v.end(), [](auto e){std::cout << e << "\t\t";});
    std::cout << "\n";

    for(int i = 0; i < g.edge.size(); i++)
    {
        int a = g.edge[i].first;
        int b = g.edge[i].second;

        int s1 = ds.find(a);
        int s2 = ds.find(b);

        if (s1 == s2) {
            loop = true;
            goto out;
        }

        ds.united(a, b);
    }

 out:
    std::cout << "Has loop?: " << loop << std::endl;
    return loop;
}


int main()
{
    std::vector<DisjointSet::Node> v = {1, 2, 3, 4, 5};
    DisjointSet ds;
    ds.make(v);

    using pr = std::pair<int, int>;
    Graph<pr> g(pr(0, 1), pr(0, 2), pr(1, 3), pr(1, 4), pr(3, 4));
    g.print();
    hasLoop(g);

    Graph<pr> g2(pr(0, 1), pr(0, 2), pr(1, 3), pr(1, 4), pr(3, 5), pr(3, 6));
    hasLoop(g2);

    Graph<pr> g3(pr(0, 1), pr(1, 2), pr(0, 2));
    hasLoop(g3);

    Graph<pr> g4(pr(0, 1), pr(0, 2), pr(1, 3), pr(1, 4), pr(2, 8), pr(2, 9), pr(8, 13));
    hasLoop(g4);

}
