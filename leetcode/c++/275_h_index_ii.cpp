// https://leetcode.cn/problems/h-index-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
        if (citations.size() == 1)
            return citations[0] == 0? 0: 1;
        int l = 0, r = citations.size() - 1, res = 0;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (citations[m] >= citations.size() - m) {
                res = citations.size() - m;
                r = m - 1;
            }
            else if (citations[m] < citations.size() - m) {
                l = m + 1;
            }
        }
        return res;
    }
};

// 时间复杂度为O(logn)，空间复杂度为O(1)
// 关键是理解hindex的计算，hindex主要和论文数量有关，
// 即h=5表示至少有5篇论文的引用大于了5，并且hindex是满足条件的最大值（h = n（n<4）都成立）。