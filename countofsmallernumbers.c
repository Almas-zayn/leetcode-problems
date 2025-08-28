/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void update(int *BIT, int size, int index, int value) {
    while (index <= size) {
        BIT[index] += value;
        index += (index & -index);
    }
}

int query(int *BIT, int index) {
    int sum = 0;
    while (index > 0) {
        sum += BIT[index];
        index -= (index & -index);
    }
    return sum;
}

int cmpfunc(const void *a, const void *b) {
    long x = *(long *)a;
    long y = *(long *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int binarySearch(long *arr, int size, long target) {
    int left = 0, right = size - 1, mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid + 1;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    if (numsSize == 0) return NULL;

    int *result = (int*)calloc(numsSize, sizeof(int));

    long *sorted = (long*)malloc(sizeof(long) * numsSize);
    for (int i = 0; i < numsSize; i++) sorted[i] = nums[i];
    qsort(sorted, numsSize, sizeof(long), cmpfunc);

    int m = 0;
    for (int i = 0; i < numsSize; i++) {
        if (i == 0 || sorted[i] != sorted[i-1]) {
            sorted[m++] = sorted[i];
        }
    }

    int *BIT = (int*)calloc(m + 2, sizeof(int));

    for (int i = numsSize - 1; i >= 0; i--) {
        int idx = binarySearch(sorted, m, nums[i]); 
        result[i] = query(BIT, idx - 1);  
        update(BIT, m, idx, 1);       
    }
    free(BIT);
    free(sorted);
    return result;
}
