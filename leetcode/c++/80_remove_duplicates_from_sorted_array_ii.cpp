// https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size(), k = 1, cnt = 1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] != nums[i - 1]) {
                cnt = 1;
                nums[k++] = nums[i];
            } else if (cnt < 2) {
                ++cnt;
                nums[k++] = nums[i];
            }
        }
        return k;
    }
};

// O(n), O(1)