/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode *newNode(int val)
{
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

struct TreeNode *createTree(struct ListNode *head, struct ListNode *tail)
{
    if (head == tail)
        return NULL;
    struct ListNode *slow = head, *fast = head;
    while (fast != tail && fast->next != tail)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct TreeNode *root = newNode(slow->val);
    root->left = createTree(head, slow);
    root->right = createTree(slow->next, tail);
    return root;
}

struct TreeNode *sortedListToBST(struct ListNode *head)
{
    return createTree(head, NULL);
}
