int thirdMax(int *nums, int numsSize)
{
    long first = LONG_MIN, second = LONG_MIN, third = LONG_MIN;
    int cnt = 0;
    for (int i = 0; i < numsSize; i++)
    {
        int n = nums[i];
        if (n == first || n == second || n == third)
            continue; // skip duplicates
        if (n > first)
        {
            third = second;
            second = first;
            first = n;
        }
        else if (n > second)
        {
            third = second;
            second = n;
        }
        else if (n > third)
        {
            third = n;
        }
    }
    return (third == LONG_MIN) ? first : third;
}
