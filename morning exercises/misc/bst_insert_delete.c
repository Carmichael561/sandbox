#include <stdio>

struct node
{
    int value;
    struct node *left;
    struct node *right;
};

struct node *bst;

struct node* bst_insert(struct node *root, int value)
{
    struct node *tmp;
    if (root == 0)
        {
            root = malloc(sizeof(struct node));
            root.value = value;
            root.left = 0;
            root.right = 0;
            return root;
        }
    if (value < root->value)
        {
            root->left = bst_insert(root->left, value);
        }
    else
        {
            root->right = bst_insert(root->right, value);
        }
}

void bst_delete(struct node *root, int value)
{
    struct node *c, *l, *r, *p;

    if (root == NULL)
        return;

    c = root;
    p = NULL;
    l = root->left;
    r = root->right;

    while (1)
        {
            if (value == c->value){break;}

            if (value < c->value){p = c; c = c->left;}

            else{}
        }
}

int main()
{
    bst_insert(bst, 10);
    bst_insert(bst, -1);
    bst_insert(bst, 23);

    return 0;
}
