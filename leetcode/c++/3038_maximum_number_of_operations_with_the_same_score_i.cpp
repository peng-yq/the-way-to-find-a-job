// https://leetcode.cn/problems/maximum-number-of-operations-with-the-same-score-i

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxOperations(vector<int>& nums) {
        int res = 1, n = nums.size(), flag = nums[0] + nums[1];
        for (int i = 2; i < n; i += 2) {
            if (nums[i] + nums[i + 1] == flag)
                ++res;
            else 
                break;
        }
        return res;
    }
};

// 幽默，O(n)，O(1)