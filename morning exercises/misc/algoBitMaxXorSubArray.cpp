#include <iostream>
#include <memory>
#include <limits>

class Trie
{
public:
    //    Trie(){std::cout << "constructor\n";}
    //    ~Trie(){std::cout << "destructor\n";}
public:
    std::unique_ptr<Trie> data[2];
    int acc_xor;
};

void insertTrie(Trie* root, int val)
{
    Trie *tmp = root;
    
    for(int i = std::numeric_limits<int>::digits; i >= 0; i--)
    {
        bool bit = (val & (1 << i));
        //        std::cout << "       bit = " << bit << " digit " << i <<  std::endl;
        
        if (tmp->data[bit] == nullptr)
            tmp->data[bit] = std::make_unique<Trie>();

        tmp = tmp->data[bit].get();
    }
    tmp->acc_xor = val;
}

int queryTrie(Trie *root, int pre_xor)
{
    Trie *tmp = root;

    for (int i = std::numeric_limits<int>::digits - 1; i >= 0; i--)
    {
        bool bit = (1 << i) & pre_xor;
        //        std::cout << "bit ==== " << bit << std::endl;
        
        if (tmp->data[1 - bit] != nullptr)
            tmp = tmp->data[1 - bit].get();
        else if (tmp->data[bit].get() != nullptr)
            tmp = tmp->data[bit].get();
    }

    return tmp->acc_xor ^ pre_xor;
}

int maxXor(int *arr, int n)
{
    for(int i = 0; i < n; i++)
        std::cout << arr[i] << "\t\t";
    std::cout << std::endl;

    std::unique_ptr<Trie> root = std::make_unique<Trie>();
    int pre_xor = 0;
    int max = std::numeric_limits<int>::min();

    insertTrie(root.get(), pre_xor);

    for (int i = 0; i < n; i++)
    {
        pre_xor |= arr[i];
        //        std::cout << "insert\n";
        insertTrie(root.get(), pre_xor);

        //        std::cout << "query\n";
        max = std::max(max, queryTrie(root.get(), pre_xor));
    }

    //    std::cout << "END\n";

    return max;
}

int main()
{
    int arr[] = {8, 1, 2, 12};
    int max = maxXor(arr, sizeof(arr)/sizeof(arr[0]));
    std::cout << "Max XOR: " << max << std::endl;

    int arr2[] = {1, 1, 2, 11, 1};
    max = maxXor(arr2, sizeof(arr2)/sizeof(arr2[0]));
    std::cout << "Max XOR: " << max << std::endl;
    
    return 0;
}
