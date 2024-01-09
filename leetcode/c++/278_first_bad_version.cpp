// https://leetcode.cn/problems/first-bad-version/description

#include <bits/stdc++.h>
using namespace std;

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int l = 1, r = n, i = 0;
        while (l <= r) {
            i = l - (l - r) / 2;
            if (!isBadVersion(i))  l = i + 1;
            else if (isBadVersion(i) && isBadVersion(i-1)) r = i - 1;
            else return i;
        }
        return 0;
    }
};

// 时间复杂度为O(logn)，空间复杂度为O(1)