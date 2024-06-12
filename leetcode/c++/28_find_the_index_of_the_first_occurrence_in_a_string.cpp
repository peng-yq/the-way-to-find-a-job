// https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        for (int i = 0; i <= m - n; ++i) {
            int j = 0;
            while (j < n && haystack[i + j] == needle[j])
                ++j;
            if (j == n)
                return i;
        }
        return -1;
    }
};