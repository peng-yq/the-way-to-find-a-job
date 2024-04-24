// https://leetcode.cn/problems/longest-common-subsequence

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else 
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[m][n];
    }
};

// 动态规划，时间复杂度为O(mn)，空间复杂度为O(mn)
// 由于状态转移方程是dp[i-1][j-1]，避免边界问题，dp数组大小定义为m+1*n+1，注意这样比较的话是text1[i-1]和text2[j-1]
// dp[i][j]表示从头开始长度为i和j的两个字符串的最长公共子串长度
// 如果比较的text1[i-1]和text2[j-1]相等，那么dp[i][j] = dp[i-1][j-1] + 1，否则选择去掉text[i-1]或text[j-1]的最大的那个