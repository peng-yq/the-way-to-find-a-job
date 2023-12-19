// https://leetcode.cn/problems/sliding-subarray-beauty/description/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        int n = nums.size();
        vector<int>res;
        int numbers[101] = {};
        for (int l = 0, r =0; r < n; r++) {
            numbers[nums[r]+50]++;
            if (r - l + 1 > k) {
                numbers[nums[l++]+50]--;
            }
            if (r - l + 1 == k) {
                int tmp = 0;
                for (int j = 0; j <= 100; j++) {
                    tmp += numbers[j];
                    if (tmp >= x) {
                        res.push_back(min(j - 50, 0));
                        break;
                    }
                        
               }
            }            
        }
        return res;
    }
};

// 用数组更节约时间和内存，时间复杂度为O(nm) m=101，空间复杂度为O(n-k+1)