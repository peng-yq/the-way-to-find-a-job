// https://leetcode.cn/problems/remove-duplicates-from-sorted-array

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size(), res = 1, k = 1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] != nums[i-1]) {
                ++res;
                nums[k++] = nums[i];
            }
        }
        return res;
    }
};

// O(n)，O(1)