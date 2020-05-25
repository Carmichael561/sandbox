#include <algorithm>
#include <vector>
#include <iostream>
#include <memory>
#include <list>
#include <utility>
#include <queue>


using Node = unsigned int;
using Weight = unsigned int;
using Distance = unsigned int;

class Dejk;

class Graph
{
    friend Dejk;

public:
    Graph(unsigned int n) : nodes(n)
    {
        vertexes = std::make_unique<std::list<std::pair<Node, Weight>>[]>(nodes);
    }

    void addNode(Node, Node, Weight);
    void iterateGraph();

private:
    Node nodes;
    std::unique_ptr<std::list<std::pair<Node, Weight>>[]> vertexes;
};

class Dejk
{
public:
    Dejk(Node, Graph&);
    void distance();
private:
    Node start;
    std::vector<Distance> map;
    Graph &g;
};

void Dejk::distance()
{
    for (int i = 0; i < g.nodes; i++)
    {
        std::cout << i << ":\t\t" << map[i] << std::endl;
    }
}

Dejk::Dejk(Node s, Graph& g) : g(g)
{
    if(s > g.nodes)
        return;

    Node n = s;
    std::vector<bool> spt(g.nodes, false);
    for(int i = 0; i < g.nodes; i++)
        map.push_back(std::numeric_limits<Distance>::max());
    map[n] = 0;

    for(int i = 0; i < g.nodes; i++)
    {   
        //1. get minimum waight from spt
        Distance min = std::numeric_limits<Distance>::max();
        for(int node = 0; node < g.nodes; node++)
        {   
            if (!spt[node] && map[node] < min) {
                min = map[node];
                n = node;
            }
        }

        spt[n] = true;
        
        //2. update map adjasent
        for(auto node : g.vertexes[n])
        {
            Node N = node.first;
            Weight W = node.second;

            if(spt[N] || map[N] < map[n] + W)
                continue;

            map[N] = map[n] + W;
        }
    }
}

void Graph::addNode(Node s, Node d, Weight w)
{
    vertexes[s].push_back(std::make_pair(d, w));
}

void Graph::iterateGraph()
{
    for (int j = 0; j < nodes; j++)
        {
            std::cout << j << ": ";
            for(auto i : vertexes[j])
                std::cout << i.first << " [" << i.second << "]; ";
            std::cout << std::endl;
        }
}

constexpr unsigned int V = 9;

int main()
{
    Graph g(V);

   int graph[V][V] = {{0, 4,  0, 0,  0,  0,  0, 8,  0}, 
                      {4, 0,  8, 0,  0,  0,  0, 11, 0}, 
                      {0, 8,  0, 7,  0,  4,  0, 0,  2}, 
                      {0, 0,  7, 0,  9,  14, 0, 0,  0}, 
                      {0, 0,  0, 9,  0,  10, 0, 0,  0}, 
                      {0, 0,  4, 14, 10, 0,  2, 0,  0}, 
                      {0, 0,  0, 0,  0,  2,  0, 1,  6}, 
                      {8, 11, 0, 0,  0,  0,  1, 0,  7}, 
                      {0, 0,  2, 0,  0,  0,  6, 7,  0}
                     };


   for(int i = 0; i < V; i++)
       {
           for(int j = 0; j < V; j++)
               {
                   if(graph[i][j])
                       g.addNode(i, j, graph[i][j]);
               }
       }

   
   g.iterateGraph();

   Dejk d0(0, g);
   d0.distance();

   Dejk d1(1, g);
   d1.distance();

   return 0;
}
    
