#define MAX_SIZE 100000

typedef struct {
    int data[MAX_SIZE];
    int size;
} MaxHeap;

typedef struct {
    int data[MAX_SIZE];
    int size;
} MinHeap;

void maxHeapPush(MaxHeap* h, int val) {
    int i = h->size++;
    h->data[i] = val;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->data[p] >= h->data[i]) break;
        int tmp = h->data[p];
        h->data[p] = h->data[i];
        h->data[i] = tmp;
        i = p;
    }
}

int maxHeapPop(MaxHeap* h) {
    int top = h->data[0];
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (1) {
        int l = 2*i + 1, r = 2*i + 2, largest = i;
        if (l < h->size && h->data[l] > h->data[largest]) largest = l;
        if (r < h->size && h->data[r] > h->data[largest]) largest = r;
        if (largest == i) break;
        int tmp = h->data[i];
        h->data[i] = h->data[largest];
        h->data[largest] = tmp;
        i = largest;
    }
    return top;
}

int maxHeapTop(MaxHeap* h) { return h->data[0]; }

void minHeapPush(MinHeap* h, int val) {
    int i = h->size++;
    h->data[i] = val;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->data[p] <= h->data[i]) break;
        int tmp = h->data[p];
        h->data[p] = h->data[i];
        h->data[i] = tmp;
        i = p;
    }
}

int minHeapPop(MinHeap* h) {
    int top = h->data[0];
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (1) {
        int l = 2*i + 1, r = 2*i + 2, smallest = i;
        if (l < h->size && h->data[l] < h->data[smallest]) smallest = l;
        if (r < h->size && h->data[r] < h->data[smallest]) smallest = r;
        if (smallest == i) break;
        int tmp = h->data[i];
        h->data[i] = h->data[smallest];
        h->data[smallest] = tmp;
        i = smallest;
    }
    return top;
}

int minHeapTop(MinHeap* h) { return h->data[0]; }

typedef struct {
    MaxHeap left; 
    MinHeap right; 
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->left.size = 0;
    obj->right.size = 0;
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    if (obj->left.size == 0 || num <= maxHeapTop(&obj->left)) {
        maxHeapPush(&obj->left, num);
    } else {
        minHeapPush(&obj->right, num);
    }

    if (obj->left.size > obj->right.size + 1) {
        int val = maxHeapPop(&obj->left);
        minHeapPush(&obj->right, val);
    } else if (obj->right.size > obj->left.size) {
        int val = minHeapPop(&obj->right);
        maxHeapPush(&obj->left, val);
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->left.size > obj->right.size) {
        return (double)maxHeapTop(&obj->left);
    } else {
        return ((double)maxHeapTop(&obj->left) + (double)minHeapTop(&obj->right)) / 2.0;
    }
}

void medianFinderFree(MedianFinder* obj) {
    free(obj);
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 * double param_2 = medianFinderFindMedian(obj);
 * medianFinderFree(obj);
*/
