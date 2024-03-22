// https://leetcode.cn/problems/subarray-sum-equals-k

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0, presum = 0;
        unordered_map<int, int> sum;
        sum[0] = 1; // 这个比较巧妙，这样前缀和直接为k的就可以被计算
        for (int i = 0; i < nums.size(); i++) {
            presum += nums[i];
            if (sum.contains(presum - k))
                res += sum[presum-k];
            sum[presum]++;
        }       
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)