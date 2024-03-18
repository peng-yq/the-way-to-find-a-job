// https://leetcode.cn/problems/zheng-ze-biao-da-shi-pi-pei-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool articleMatch(string s, string p) {
        if (p.empty())
            return s.empty();
        bool first_match = !s.empty() && (s[0] == p[0] || p[0] == '.');
        if (p.length() >= 2 && p[1] == '*')
            return (first_match && articleMatch(s.substr(1), p)) || articleMatch(s, p.substr(2));
        else
            return first_match && articleMatch(s.substr(1), p.substr(1));
    }
};

// 递归解法，最差时间复杂度为O(2^min(m, n))，空间复杂度为O(min(m, n))

class Solution {
public:
    bool articleMatch(string s, string p) {
        int m = s.length(), n = p.length();
        vector<vector<bool>>dp(m+1, vector<bool>(n+1, false));
        dp[0][0] = true;
        for (int j = 2; j <= n; j += 2)
            dp[0][j] = (dp[0][j-2] && p[j-1] == '*');
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j-1] != '*') {
                    if (dp[i-1][j-1] && s[i-1] == p[j-1])
                        dp[i][j] = true;
                    else if (dp[i-1][j-1] && p[j-1] == '.')
                        dp[i][j] = true;
                } else {
                    if (dp[i][j-2])
                        dp[i][j] = true;
                    else if (dp[i-1][j] && s[i-1] == p[j-2])
                        dp[i][j] = true;
                    else if (dp[i-1][j] && p[j-2] == '.' )
                        dp[i][j] = true;
                }
            }
        }
        return dp[m][n];
    }
};

// 动态规划解法，初始化和递推思路都很妙
// 时间复杂度和空间复杂度均为O(mn)