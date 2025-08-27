/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void inorder(struct TreeNode *root, long long *prev, int *flag)
{
    if (root != NULL && *flag == 0)
    {
        inorder(root->left, prev, flag);

        if (*flag == 0)
        {
            if (*prev >= root->val)
            {
                *flag = 1;
                return;
            }
            *prev = root->val;
        }

        inorder(root->right, prev, flag);
    }
}

bool isValidBST(struct TreeNode *root)
{
    int flag = 0;
    long long prev = (long long)INT_MIN - 1;
    inorder(root, &prev, &flag);
    return flag == 0;
}