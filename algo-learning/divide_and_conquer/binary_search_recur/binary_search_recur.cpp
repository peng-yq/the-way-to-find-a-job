#include <bits/stdc++.h>
using namespace std;

int dfs(vector<int> &nums, int target, int i, int j) {
    if(i > j)
        return -1;
    int m = i + (j - i) / 2;
    if(nums[m] < target) {
        return dfs(nums, target, m+1, j);
    } else if(nums[m] > target) {
        return dfs(nums, target, i, m-1);
    } else {
        return m;
    }
}

int binarySearch(vector<int> &nums, int target) {
    return dfs(nums, target, 0, nums.size());
}