// https://leetcode.cn/problems/find-the-longest-substring-containing-vowels-in-even-counts

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findTheLongestSubstring(string s) {
        int n = s.size(), pre = 0, res = 0;
        vector<int> pos(1 << 5, n);
        pos[0] = -1;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'a') {
                pre ^= 1 << 0;
            } else if (s[i] == 'e') {
                pre ^= 1 << 1;
            } else if (s[i] == 'i') {
                pre ^= 1 << 2;
            } else if (s[i] == 'o') {
                pre ^= 1 << 3;
            } else if (s[i] == 'u') {
                pre ^= 1 << 4;
            }
            res = max(res, i - pos[pre]);
            if (pos[pre] == n)
                pos[pre] = i;
        }
        return res;
    }
};

// 前缀和 + 位掩码，但这里只关心a, e, i, o, u 5个字母
// 时间复杂度为O(n)，空间复杂度为O(2^5)