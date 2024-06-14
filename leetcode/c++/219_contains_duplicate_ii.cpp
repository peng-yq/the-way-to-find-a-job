// https://leetcode.cn/problems/contains-duplicate-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, vector<int>> numMap;
        for (int i = 0; i < nums.size(); ++i) {
            if (numMap.count(nums[i])) {
                for (auto j : numMap[nums[i]]) {
                    if (abs(i - j) <= k)
                        return true;
                }
            }
            numMap[nums[i]].push_back(i);
        }
        return false;
    }
};

// O(n)，O(n)