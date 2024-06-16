// https://leetcode.cn/problems/longest-uncommon-subsequence-i

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findLUSlength(string a, string b) {
        if (a == b)
            return -1;
        else 
            return max(a.size(), b.size());
    }
};

// 脑筋急转弯题，如果a和b不等，则最长特殊子序列为两者中最长的那个；否则为-1
// 时间空间复杂度为O(1)