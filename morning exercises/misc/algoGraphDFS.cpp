#include <vector>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>
#include <bitset>
#include <queue>
#include <algorithm>
#include <stack>

using Node = int;

class Graph
{
    void recursiveDFS(Node, std::vector<bool>*);
public:
    Graph(Node);
    void addNode(Node, Node);
    void DFS(Node);

private:
    int m_nodes;
    std::unique_ptr<std::list<Node>[]> m_vertex;
};

Graph::Graph(Node n) : m_nodes(n)
{
    m_vertex = std::make_unique<std::list<Node>[]>(m_nodes);
}

void Graph::addNode(Node s, Node d)
{
    if (s >= m_nodes && d >= m_nodes)
        throw std::invalid_argument("Passed nodes out of scope");

    m_vertex[s].push_back(d);
}

void Graph::recursiveDFS(Node node, std::vector<bool>* bsn)
{
    if((*bsn)[node])
        return;

    (*bsn)[node] = true;
    std::cout << "Node: " << node << std::endl;
    for(auto i : m_vertex[node])
        recursiveDFS(i, bsn);
}

void Graph::DFS(Node start)
{
    if(start > m_nodes)
        throw std::invalid_argument("Invalid start node");

    std::vector<bool> bsn(m_nodes, false);

    recursiveDFS(start, &bsn);
}


int main()
{
    Graph g(4);

    g.addNode(0, 1); 
    g.addNode(0, 2); 
    g.addNode(1, 2); 
    g.addNode(2, 0); 
    g.addNode(2, 3); 
    g.addNode(3, 3); 
  
    std::cout << "BFS starting from vertex 2" << std::endl;
    
    g.DFS(2);
    
    return 0;
}
