#include <vector>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>
#include <bitset>
#include <queue>
#include <algorithm>

using Node = int;

class Graph
{
public:
    Graph(Node);
    void addNode(Node, Node);
    void BFS(Node);

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

void Graph::BFS(Node start)
{
    if(start > m_nodes)
        throw std::invalid_argument("Invalid start node");

    std::vector<bool> bsn(m_nodes, false);
    std::queue<Node> queue;

    queue.push(start);

    while(not queue.empty())
        {
            Node node = queue.front();
            queue.pop();
            bsn[node] = true;
            std::cout << "Node: " << node << std::endl;

            for(auto i : m_vertex[node])
                {
                    if (bsn[i] == true) continue;
                    queue.push(i);
                    std::cout << "push " << i << std::endl;
                }
        }
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
    
    g.BFS(2);
    
    return 0;
}
