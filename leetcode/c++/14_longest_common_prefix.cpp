// https://leetcode.cn/problems/longest-common-prefix

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        sort(strs.begin(), strs.end());
        string s1 = strs[0], s2 = strs[strs.size() - 1];
        int res = 0;
        for (int i = 0; i < s1.size() && i < s2.size() && s1[i] == s2[i]; ++i)
            ++res;
        return s1.substr(0, res);
    }
};

// 在已排序的字符串数组中，最长公共前缀只能是数组中第一个字符串和最后一个字符串的公共前缀。
// O(nlogn), O(1)