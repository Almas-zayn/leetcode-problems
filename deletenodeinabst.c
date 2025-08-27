/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode *findMin(struct TreeNode *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

struct TreeNode *deleteNode(struct TreeNode *root, int key)
{
    if (root == NULL)
        return NULL;

    if (key < root->val)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->val)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        // Case 1: No child
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        // Case 2: One child
        else if (root->left == NULL)
        {
            struct TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        // Case 3: Two children
        struct TreeNode *successor = findMin(root->right);
        root->val = successor->val; // replace value
        root->right = deleteNode(root->right, successor->val);
    }
    return root;
}
