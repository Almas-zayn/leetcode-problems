
typedef struct Node {
    long val;
    int priority;
    int size;
    int count;
    struct Node *left, *right;
} Node;

int nodeSize(Node* n) { return n ? n->size : 0; }

void updateSize(Node* n) {
    if (n) n->size = n->count + nodeSize(n->left) + nodeSize(n->right);
}

Node* newNode(long val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->val = val;
    n->priority = rand();
    n->size = 1;
    n->count = 1;
    n->left = n->right = NULL;
    return n;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    updateSize(y);
    updateSize(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    updateSize(x);
    updateSize(y);
    return y;
}

Node* insert(Node* root, long val) {
    if (!root) return newNode(val);
    if (val == root->val) {
        root->count++;
    } else if (val < root->val) {
        root->left = insert(root->left, val);
        if (root->left->priority > root->priority) {
            root = rotateRight(root);
        }
    } else {
        root->right = insert(root->right, val);
        if (root->right->priority > root->priority) {
            root = rotateLeft(root);
        }
    }
    updateSize(root);
    return root;
}

int countLE(Node* root, long val) {
    if (!root) return 0;
    if (val < root->val) {
        return countLE(root->left, val);
    } else if (val > root->val) {
        return root->count + nodeSize(root->left) + countLE(root->right, val);
    } else {
        return root->count + nodeSize(root->left);
    }
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    srand(time(NULL));
    long prefix = 0;
    Node* root = NULL;
    root = insert(root, 0);  

    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        prefix += nums[i];
        long leftBound = prefix - upper;
        long rightBound = prefix - lower;
        int cnt = countLE(root, rightBound) - countLE(root, leftBound - 1);
        count += cnt;
        root = insert(root, prefix);
    }
    return count;
}
