#define MOD 1000000007

typedef struct Node {
    int key;
    int count;   
    int height;
    int size;     
    struct Node *left, *right;
} Node;

int height(Node* n) { return n ? n->height : 0; }
int size(Node* n)   { return n ? n->size : 0; }
int max(int a, int b) { return a > b ? a : b; }

Node* newNode(int key) {
    Node* n = malloc(sizeof(Node));
    n->key = key;
    n->count = 1;
    n->height = 1;
    n->size = 1;
    n->left = n->right = NULL;
    return n;
}

void update(Node* n) {
    if (!n) return;
    n->height = 1 + max(height(n->left), height(n->right));
    n->size = n->count + size(n->left) + size(n->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    update(y);
    update(x);
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    update(x);
    update(y);
    return y;
}

int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* insert(Node* root, int key, int* lessCount, int* equalBefore) {
    if (!root) return newNode(key);

    if (key == root->key) {
        *lessCount += size(root->left);
        *equalBefore = root->count;  
        root->count++;
    } else if (key < root->key) {
        root->left = insert(root->left, key, lessCount, equalBefore);
    } else {
        *lessCount += size(root->left) + root->count;
        root->right = insert(root->right, key, lessCount, equalBefore);
    }

    update(root);

    int balance = getBalance(root);
    if (balance > 1 && key < root->left->key) return rightRotate(root);
    if (balance < -1 && key > root->right->key) return leftRotate(root);
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int createSortedArray(int* instructions, int n) {
    Node* root = NULL;
    long long cost = 0;

    for (int i = 0; i < n; i++) {
        int less = 0, equalBefore = 0;
        root = insert(root, instructions[i], &less, &equalBefore);

        int totalSoFar = i; 
        int greater = totalSoFar - less - equalBefore;

        cost += (less < greater ? less : greater);
        cost %= MOD;
    }

    return (int)cost;
}
