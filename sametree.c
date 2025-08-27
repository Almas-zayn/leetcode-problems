/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void inorder(struct TreeNode *p, struct TreeNode *q, int *flag)
{
    if (p != NULL && q != NULL && *flag == 0)
    {
        inorder(p->left, q->left, flag);
        if (p->val != q->val)
        {
            *flag = 1;
            return;
        }
        inorder(p->right, q->right, flag);
    }
    if (p == NULL && q != NULL)
        *flag = 1;
    if (p != NULL && q == NULL)
        *flag = 1;
}

bool isSameTree(struct TreeNode *p, struct TreeNode *q)
{
    int flag = 0;
    inorder(p, q, &flag);
    if (flag == 1)
        return false;
    else
        return true;
}