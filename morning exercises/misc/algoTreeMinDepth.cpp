#include <iostream>
#include <memory>
#include <queue>


struct Node
{
    Node(int v, std::unique_ptr<Node> l, std::unique_ptr<Node> r) : v(v), left(std::move(l)), right(std::move(r))
    {}
    
    int v;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};

struct Item
{
    Item(Node * n, uint d) : node(n), depth(d)
    {}
    
    Node *node;
    uint depth;
};

std::unique_ptr<Node> addNode(int v)
{
    auto node = std::make_unique<Node>(v, nullptr, nullptr);

    return std::move(node);
}

uint getMinDepth(Node *root)
{
    uint depth = 0;
    
    if (root == nullptr)
        return depth;

    std::queue<Item> queue;

    queue.push(Item(root, 0));

    while(not queue.empty())
    {
        Item item = queue.front();
        queue.pop();

        Node *l = item.node->left.get();
        Node *r = item.node->right.get();
        depth = item.depth;

        if (l == nullptr && r == nullptr)
            return depth;

        if (l != nullptr)
            queue.push(Item(l, depth+1));

        if (r != nullptr)
            queue.push(Item(r, depth+1));
    }
    
    return depth;
}

int main()
{
    std::unique_ptr<Node> root = addNode(0);
    root->left = addNode(1);
    root->right = addNode(2);
    root->left->left = addNode(3);
    root->left->right = addNode(4);
    root->left->left->left = addNode(5);
    root->left->left->right = addNode(6);

    root->right->left = addNode(7);
    root->right->left->left = addNode(8);

    int depth = getMinDepth(root.get());
    std::cout << "Min depth is: " << depth << std::endl;

    return 0;
}
