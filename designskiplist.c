
#define MAX_LEVEL 32
#define P 0.25

typedef struct SkiplistNode {
    int val;
    struct SkiplistNode* forward[MAX_LEVEL];
} SkiplistNode;

typedef struct {
    SkiplistNode* head;
    int level;
} Skiplist;

SkiplistNode* newNode(int val) {
    SkiplistNode* node = (SkiplistNode*)malloc(sizeof(SkiplistNode));
    node->val = val;
    for (int i = 0; i < MAX_LEVEL; i++) {
        node->forward[i] = NULL;
    }
    return node;
}

int randomLevel() {
    int lvl = 1;
    while (((double)rand() / RAND_MAX) < P && lvl < MAX_LEVEL) {
        lvl++;
    }
    return lvl;
}

Skiplist* skiplistCreate() {
    srand(1); 
    Skiplist* obj = (Skiplist*)malloc(sizeof(Skiplist));
    obj->head = newNode(INT_MIN); 
    obj->level = 1;
    return obj;
}

bool skiplistSearch(Skiplist* obj, int target) {
    SkiplistNode* curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--) {
        while (curr->forward[i] && curr->forward[i]->val < target) {
            curr = curr->forward[i];
        }
    }
    curr = curr->forward[0];
    return curr && curr->val == target;
}

void skiplistAdd(Skiplist* obj, int num) {
    SkiplistNode* update[MAX_LEVEL];
    SkiplistNode* curr = obj->head;

    for (int i = obj->level - 1; i >= 0; i--) {
        while (curr->forward[i] && curr->forward[i]->val < num) {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }

    int lvl = randomLevel();
    if (lvl > obj->level) {
        for (int i = obj->level; i < lvl; i++) {
            update[i] = obj->head;
        }
        obj->level = lvl;
    }

    SkiplistNode* new_node = newNode(num);
    for (int i = 0; i < lvl; i++) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }
}

bool skiplistErase(Skiplist* obj, int num) {
    SkiplistNode* update[MAX_LEVEL];
    SkiplistNode* curr = obj->head;

    for (int i = obj->level - 1; i >= 0; i--) {
        while (curr->forward[i] && curr->forward[i]->val < num) {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }

    curr = curr->forward[0];
    if (!curr || curr->val != num) return false;

    for (int i = 0; i < obj->level; i++) {
        if (update[i]->forward[i] == curr) {
            update[i]->forward[i] = curr->forward[i];
        }
    }

    free(curr);

    while (obj->level > 1 && obj->head->forward[obj->level - 1] == NULL) {
        obj->level--;
    }

    return true;
}

void skiplistFree(Skiplist* obj) {
    SkiplistNode* curr = obj->head;
    while (curr) {
        SkiplistNode* next = curr->forward[0];
        free(curr);
        curr = next;
    }
    free(obj);
}

/**
 * Your Skiplist struct will be instantiated and called as such:
 * Skiplist* obj = skiplistCreate();
 * bool param_1 = skiplistSearch(obj, target);
 
 * skiplistAdd(obj, num);
 
 * bool param_3 = skiplistErase(obj, num);
 
 * skiplistFree(obj);
*/
