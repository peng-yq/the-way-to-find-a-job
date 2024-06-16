// https://leetcode.cn/problems/insert-interval

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        int left = newInterval[0], right = newInterval[1], flag = 0;
        for (const auto& interval : intervals) {
            if (interval[0] > right) {
                if (!flag) {
                    res.push_back({left, right});
                    flag = 1;
                }
                res.push_back(interval);
            } else if (interval[1] < left) {
                res.push_back(interval);
            } else {
                left = min(left, interval[0]);
                right = max(right, interval[1]);
            }
        }
        if (!flag)
            res.push_back({left, right});
        return res;
    }
};

// O(n)，O(1)；合并原数组中所有与新插入区间有交集的区间