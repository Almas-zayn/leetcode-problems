/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#define TABLE_SIZE 1007

struct Node {
    char *original;
    struct Node *next;
};

struct HashEntry {
    char *key;
    struct Node *list;
    struct HashEntry *next;
};

struct HashEntry* hashTable[TABLE_SIZE] = {NULL};

unsigned int hash(const char *key) {
    unsigned long hashValue = 5381;
    int c;
    while ((c = *key++))
        hashValue = ((hashValue << 5) + hashValue) + c;
    return hashValue % TABLE_SIZE;
}

char* sortString(const char *s) {
    char *sorted = strdup(s);
    int len = strlen(sorted);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (sorted[i] > sorted[j]) {
                char tmp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = tmp;
            }
        }
    }
    return sorted;
}

void insert(const char *sortedKey, const char *original) {
    unsigned int index = hash(sortedKey);
    struct HashEntry *entry = hashTable[index];

    while (entry) {
        if (strcmp(entry->key, sortedKey) == 0) {
            break; // Found existing key
        }
        entry = entry->next;
    }

    if (!entry) {
        entry = malloc(sizeof(struct HashEntry));
        entry->key = strdup(sortedKey);
        entry->list = NULL;
        entry->next = hashTable[index];
        hashTable[index] = entry;
    }

    struct Node *node = malloc(sizeof(struct Node));
    node->original = strdup(original);
    node->next = entry->list;
    entry->list = node;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    // Clear table
    for (int i = 0; i < TABLE_SIZE; i++) hashTable[i] = NULL;

    // Insert strings
    for (int i = 0; i < strsSize; i++) {
        char *sortedKey = sortString(strs[i]);
        insert(sortedKey, strs[i]);
        free(sortedKey);
    }

    // Collect results
    char ***result = NULL;
    *returnColumnSizes = NULL;
    int groups = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        struct HashEntry *entry = hashTable[i];
        while (entry) {
            // Count items
            int count = 0;
            struct Node *node = entry->list;
            while (node) {
                count++;
                node = node->next;
            }

            // Collect items
            char **group = malloc(sizeof(char*) * count);
            node = entry->list;
            for (int j = 0; j < count; j++) {
                group[j] = node->original;
                node = node->next;
            }

            result = realloc(result, sizeof(char**) * (groups + 1));
            result[groups] = group;

            *returnColumnSizes = realloc(*returnColumnSizes, sizeof(int) * (groups + 1));
            (*returnColumnSizes)[groups] = count;

            groups++;
            entry = entry->next;
        }
    }

    *returnSize = groups;
    return result;
}
