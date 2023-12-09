// https://leetcode.cn/problems/maximum-sum-of-almost-unique-subarray

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxSum(vector<int>& nums, int m, int k) {
        unordered_map<int, int> array;
        long long res = 0, sum = 0;
        for (int l = 0, r = 0; r < nums.size(); r++) {
            array[nums[r]]++;
            sum += nums[r];
            if (r >= l + k) {
                if (--array[nums[l]] == 0)
                    array.erase(nums[l]);
                sum -= nums[l++];
            }
            if (r == l + k -1 && array.size() >= m) 
                res = max(res, sum);
        }
        return res;
    }
};

// 时间复杂度O(n)，空间复杂度O(n)