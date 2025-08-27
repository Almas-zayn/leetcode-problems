#define HASH_TABLE 10007

typedef struct Node
{
    int key;
    int value;
    struct Node *next, *prev;
} Node;

typedef struct
{
    int capacity;
    struct Node *head, *tail;
    struct Node **hashTable;
} LRUCache;

int hash(int key, int capacity)
{
    return key % capacity;
}

LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *lru = (LRUCache *)malloc(sizeof(LRUCache));
    lru->capacity = capacity;
    lru->head = NULL;
    lru->tail = NULL;
    struct Node **temp = (struct Node **)calloc(capacity, sizeof(struct Node *));
    for (int i = 0; i < lru->capacity; i++)
    {
        temp[i] = NULL;
    }
    lru->hashTable = temp;
    return lru;
}

int lRUCacheGet(LRUCache *obj, int key)
{
    int index = hash(key, obj->capacity);
    struct Node *node = obj->hashTable[index];
    if (node == NULL)
        return -1;
    else
    {
        int value = node->value;
        return value;
    }
    return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    int index = hash(key, obj->capacity);
    struct Node *node = obj->hashTable[index];
    if (node)
    {
        node->value = value;
    }
    else
    {
        node = malloc(sizeof(struct Node));
        node->prev = NULL;
        node->value = value;
        node->next = obj->head;
        obj->head = node;
        obj->hashTable[index] = node;
    }
}

void lRUCacheFree(LRUCache *obj)
{
    struct Node *node = obj->head;
    while (node)
    {
        Node *temp = node;
        node = node->next;
        free(temp);
    }
    free(obj->hashTable);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);

 * lRUCachePut(obj, key, value);

 * lRUCacheFree(obj);
*/