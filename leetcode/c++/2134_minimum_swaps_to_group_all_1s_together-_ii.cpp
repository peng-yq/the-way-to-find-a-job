// https://leetcode.cn/problems/minimum-swaps-to-group-all-1s-together-ii/description/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int k = 0, res = 1e5 + 10, n = nums.size();
        vector<int> array;
        for (int i = 0; i < 2 * n; i ++){
            if (i < n)
                k += nums[i];
            array.push_back(nums[i % n]);
        }          
        for (int l = 0, r = 0, tmp = 0; r < 2*n; r++) {
            tmp += abs(array[r] - 1);
            if (r >= l + k) {
                tmp -= abs(array[l++] - 1);
            }
            if (r == l + k -1)
                res = min(res, tmp);
        }
        return res;
    }
};

// 时间复杂度O(n), 空间复杂度O(n)