// https://leetcode.cn/problems/non-overlapping-intervals/submissions/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1];
        });
        int prev = intervals[0][1], res = 0;
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < prev)
                res++;
            else
                prev = intervals[i][1];
        }
        return res;
    }
};

// 时间复杂度为O(nlogn + n)，空间复杂度为O(1)