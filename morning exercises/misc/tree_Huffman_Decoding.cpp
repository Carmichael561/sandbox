void decode_huff(node * root, string s) 
{
    node *n = root;
    //cout << s << "\n";
    //cout << isalpha(root->data);
    for (int i = 0; i < s.size(); ++i)
    {
        if(s[i] == '0')
            n = n->left;
        else
            n = n->right;


        if (n && n->left==nullptr && n->right==nullptr)
        {
            cout << n->data;
            n = root;
        }
    }
}
