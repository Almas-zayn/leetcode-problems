/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define TABLE_SIZE 10

typedef struct Node
{
    int key;
    int index;
    struct Node *next;
} Node;

Node *hashTable[TABLE_SIZE];

int hash(int key)
{
    if (key < 0)
        key = -key;
    return key % TABLE_SIZE;
}

void insert(int key, int index)
{
    int hashIndex = hash(key);
    Node *newNode = malloc(sizeof(Node));
    newNode->key = key;
    newNode->index = index;
    newNode->next = hashTable[hashIndex];
    hashTable[hashIndex] = newNode;
}

int search(int key)
{
    int hashIndex = hash(key);
    Node *temp = hashTable[hashIndex];
    while (temp != NULL)
    {
        if (temp->key == key)
            return temp->index;
        temp = temp->next;
    }
    return -1;
}

// Two Sum using chaining
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    int *arr = (int *)malloc(sizeof(int) * 2);
    *returnSize = 2;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable[i] = NULL;
    }

    for (int i = 0; i < numsSize; i++)
    {
        int complement = target - nums[i];
        int foundIndex = search(complement);
        if (foundIndex != -1)
        {
            arr[0] = foundIndex;
            arr[1] = i;
            return arr;
        }
        insert(nums[i], i);
    }
    return arr;
}