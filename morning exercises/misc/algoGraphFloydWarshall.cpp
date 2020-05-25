#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>

int INF = std::numeric_limits<int>::max() / 2;

void print(auto g)
{
        std::for_each(g.begin(), g.end(), [](auto &v){
            std::for_each(v.begin(), v.end(), [](auto &e){
                    std::cout << e << "\t\t";
                });
            std::cout << "\n";
        });
        std::cout << "\n\n\n";
}

void algoFloydWarshall(std::vector<std::vector<int>> v)
{
    std::vector<std::vector<int>> g(v);

    int Vertexes = g[0].size();

    print(g);
    for (int intermediate = 0; intermediate < Vertexes; intermediate++)
    {
        for (int i = 0; i < Vertexes; i++)
        {
            for (int j = 0; j < Vertexes; j++)
            {

                if (g[i][j] > g[i][intermediate] + g[intermediate][j])
                    g[i][j] = g[i][intermediate] + g[intermediate][j];   
            }
        }
    }
    print(g);
}

int main()
{
    std::vector<std::vector<int>> graph =
        { {0,   5,  INF, 10}, 
        {INF, 0,   3, INF}, 
        {INF, INF, 0,   1}, 
        {INF, INF, INF, 0} };;
    
    algoFloydWarshall(graph);
    
    return 0;
}
