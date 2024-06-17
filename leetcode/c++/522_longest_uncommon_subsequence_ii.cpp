// https://leetcode.cn/problems/longest-uncommon-subsequence-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        auto check = [&](string& s1, string& s2)->bool {
            int i = 0, j = 0;
            while (i < s1.size() && j < s2.size()) {
                if (s1[i] == s2[j]) {
                    ++i;
                }
                ++j;
            }
            return i == s1.size();
        };
        sort(strs.begin(), strs.end(), [](const string& a, const string& b)->bool{
            return a.size() > b.size();
        });
        int n = strs.size();
        for (int j = 0; j < n; ++j) {
            int flag = 0;
            if (j > 0 && strs[j] == strs[j - 1]) {
                continue;
            }
            for (int i = 0; i < n; ++i) {
                if (j != i && check(strs[j], strs[i])) {
                    flag = 1;
                    break;
                }
            }
            if (!flag)
                return strs[j].size();
        }
        return -1;
    }
};

// 判断每个字符串是否是其它字符串的子序列
// 时间复杂度为O(n^2m)，空间复杂度为O(1)