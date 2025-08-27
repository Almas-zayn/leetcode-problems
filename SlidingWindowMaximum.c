/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize)
{
    int *result = (int *)malloc(sizeof(int) * (numsSize - k + 1));
    int *deque = (int *)malloc(sizeof(int) * numsSize); // store indexes
    int front = 0, back = -1;
    int idx = 0;

    for (int i = 0; i < numsSize; i++)
    {
        // Remove indices out of window
        if (front <= back && deque[front] <= i - k)
            front++;

        // Remove smaller elements from back
        while (front <= back && nums[deque[back]] <= nums[i])
            back--;

        // Add current index
        deque[++back] = i;

        // First valid window
        if (i >= k - 1)
        {
            result[idx++] = nums[deque[front]];
        }
    }

    *returnSize = idx;
    free(deque);
    return result;
}