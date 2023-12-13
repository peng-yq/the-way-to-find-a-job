#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        unordered_map<int, int>array;
        int res = 0;
        for (int l = 0, r = 0, tmp = 0; r < nums.size(); r++) {
            array[nums[r]]++;
            tmp += nums[r];
            while (array[nums[r]] > 1) {
                array[nums[l]]--;
                tmp -= nums[l++];
            }
            res = max(res, tmp);
        }
        return res;
    }
};

// 时间复杂度和空间复杂度都为O(n)