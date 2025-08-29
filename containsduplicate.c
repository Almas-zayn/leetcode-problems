#define HASH_SIZE 1000007

bool hashTablePos[HASH_SIZE];
bool hashTableNeg[HASH_SIZE];

int hash(int key){
    return (key < 0)? (key * -1) % HASH_SIZE :(key % HASH_SIZE);
}

bool containsDuplicate(int* nums, int numsSize) {    
    memset(hashTablePos,0,sizeof(hashTablePos));
    memset(hashTableNeg,0,sizeof(hashTableNeg));
     for(int i = 0 ; i < numsSize ; i++ ){
        if(nums[i] < 0){
            int idx = hash(nums[i]);
            if(hashTableNeg[idx]) return true;
            hashTableNeg[idx] = true;
        }
        if(nums[i] >= 0){
            int idx = hash(nums[i]);
            if(hashTablePos[idx]) return true;
            hashTablePos[idx] = true;
        }
     }
     return false;
}
