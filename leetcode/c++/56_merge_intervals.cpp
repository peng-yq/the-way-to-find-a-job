// https://leetcode.cn/problems/merge-intervals

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[0] < b[0])
            return true;
        else if (a[0] == b[0])
            return a[1] < b[1];
        return false;
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        sort(intervals.begin(), intervals.end(), cmp);
        int begin = intervals[0][0], end = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            if (end < intervals[i][0]) {
                res.push_back({begin, end});
                begin = intervals[i][0];
                end = intervals[i][1];
            } else {
                end = max(end, intervals[i][1]);
            }
        }
        res.push_back({begin, end});
        return res;
    }
};

// 时间复杂度为O(nlogn)，空间复杂度为O(1)