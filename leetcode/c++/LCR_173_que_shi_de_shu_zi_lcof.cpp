// https://leetcode.cn/problems/que-shi-de-shu-zi-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int takeAttendance(vector<int>& records) {
        if (records[0] == 1)
            return 0;
        int i = 0, j = records.size() - 1;
        while (i <= j) {
            int mid = i + (j - i) / 2;
            if (records[mid] == mid)
                i = mid + 1;
            else
                j = mid - 1;
        }
        return i;
    }
};

// 有序数组一定要二分，O(logn)，O(1)