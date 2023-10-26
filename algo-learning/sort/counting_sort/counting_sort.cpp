#include <bits/stdc++.h>
using namespace std;

void countingSortNaive(vector<int> &nums) {
    int m = 0;
    for(int num : nums)
        m = max(m, num);
    vector<int>counter(m + 1, 0);
    for(int num : nums)
        counter[num]++;
    int i = 0;
    for(int num = 0; num < m; num++){
        for(int j = 0; j < counter[i]; j++, i++)
            nums[i] = num;
    }
}

void countingSort(vector<int> &nums) {
    int m = 0;
    for(int num : nums)
        m = max(m, num);
    vector<int>counter(m + 1, 0);
    for(int num : nums)
        counter[num]++;
    for (int i = 0; i < m; i++){
        counter[i + 1] += counter[i];
    }
    vector<int>res(nums.size());
    for(int i = nums.size() - 1; i >= 0; i--){
        res[counter[nums[i]] - 1] = nums[i];
        counter[nums[i]] --;
    }
    nums = res;
}