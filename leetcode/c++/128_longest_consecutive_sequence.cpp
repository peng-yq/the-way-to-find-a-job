// https://leetcode.cn/problems/longest-consecutive-sequence

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set;
        for (int num : nums)
            num_set.insert(num);
        int res = 0, tmp = 0;
        for (const int& num : num_set) {
            // 这一步很关键
            if (!num_set.contains(num - 1)) {
                int curnum = num;
                tmp = 1;
                while (num_set.contains(++curnum)) {
                    tmp++;
                }
                res = max(res, tmp);
            }
        }
        return res;
    }
};

// 时间和空间复杂度为O(n)