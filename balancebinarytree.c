/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int idx;
void inorder(struct TreeNode *root, int *arr)
{
    if (!root)
        return;
    inorder(root->left, arr);
    arr[idx++] = root->val;
    inorder(root->right, arr);
}

struct TreeNode *createBalancedTree(int *arr, int l, int r)
{
    if (l > r)
        return NULL;
    int m = (l + r) / 2;
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val = arr[m];
    node->left = createBalancedTree(arr, l, m - 1);
    node->right = createBalancedTree(arr, m + 1, r);
    return node;
}

int countNodes(struct TreeNode *root)
{
    if (!root)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

struct TreeNode *balanceBST(struct TreeNode *root)
{
    int n = countNodes(root);
    int *arr = (int *)malloc(sizeof(int) * n);
    idx = 0;
    inorder(root, arr);
    struct TreeNode *res = createBalancedTree(arr, 0, n - 1);
    free(arr);
    return res;
}
