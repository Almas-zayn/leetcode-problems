#define HASH_TABLE 10007   // choose a prime / large number

typedef struct Node {
    int key;
    int value;
    struct Node *prev;   
    struct Node *next;   
    struct Node *hnext;  
} Node;

typedef struct {
    int capacity;
    int size;
    Node *head, *tail;    
    Node **hashTable;         
} LRUCache;

int hash(int key) {
    return (key % HASH_TABLE + HASH_TABLE) % HASH_TABLE; 
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache *lru = (LRUCache*)malloc(sizeof(LRUCache));
    lru->capacity = capacity;
    lru->size = 0;
    lru->head = NULL;
    lru->tail = NULL;
    lru->hashTable = (Node**)calloc(HASH_TABLE, sizeof(Node*));
    return lru;
}

void removeNodeFromList(LRUCache *obj, Node *node) {
    if (!node) return;
    if (node->prev) node->prev->next = node->next;
    else obj->head = node->next;   

    if (node->next) node->next->prev = node->prev;
    else obj->tail = node->prev;   

    node->prev = node->next = NULL;
}

void insertAtHead(LRUCache *obj, Node *node) {
    node->next = obj->head;
    node->prev = NULL;
    if (obj->head) obj->head->prev = node;
    obj->head = node;
    if (!obj->tail) obj->tail = node;  

Node* findInHash(LRUCache *obj, int key) {
    int idx = hash(key);
    Node *cur = obj->hashTable[idx];
    while (cur) {
        if (cur->key == key) return cur;
        cur = cur->hnext;
    }
    return NULL;
}

int lRUCacheGet(LRUCache* obj, int key) {
    Node *node = findInHash(obj, key);
    if (!node) return -1;
    removeNodeFromList(obj, node);
    insertAtHead(obj, node);
    return node->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    int idx = hash(key);
    Node *node = findInHash(obj, key);
    if (node) {
        node->value = value;
        removeNodeFromList(obj, node);
        insertAtHead(obj, node);
        return;
    }

    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->prev = newNode->next = newNode->hnext = NULL;

    insertAtHead(obj, newNode);

    newNode->hnext = obj->hashTable[idx];
    obj->hashTable[idx] = newNode;

    obj->size++;

    
    if (obj->size > obj->capacity) {
        Node *evict = obj->tail;
        if (!evict) return; 
        removeNodeFromList(obj, evict);
        int h = hash(evict->key);
        Node *cur = obj->hashTable[h];
        Node *prev = NULL;
        while (cur) {
            if (cur == evict) {
                if (prev) prev->hnext = cur->hnext;
                else obj->hashTable[h] = cur->hnext;
                break;
            }
            prev = cur;
            cur = cur->hnext;
        }

        free(evict);
        obj->size--;
    }
}

void lRUCacheFree(LRUCache* obj) {
    Node *node = obj->head;
    while (node) {
        Node *temp = node;
        node = node->next;
        free(temp);
    }
    free(obj->hashTable);
    free(obj);
}

/* Usage example:
LRUCache* obj = lRUCacheCreate(capacity);
int val = lRUCacheGet(obj, key);
lRUCachePut(obj, key, value);
lRUCacheFree(obj);
*/
