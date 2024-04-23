// https://leetcode.cn/problems/longest-palindromic-substring

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        string res = "";
        vector<vector<bool>> dp(n, vector<bool>(n));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i <= j; ++i) {
                if (s[i] == s[j] && (j - i < 2 || dp[i+1][j-1] == true)) {
                    dp[i][j] = true;
                    if (j-i+1 > res.length())
                        res = s.substr(i, j-i+1);
                }
            }
        }
        return res;
    }
};

// 动态规划，把求回文子串个数改一下就可以用，时间复杂度为O(n^2)，空间复杂度为O(n^2)
// 中心扩展法，时间复杂度为O(n^2)，空间复杂度为O(1)

class Solution {
public:
    string longestPalindrome(string s) {
        string res = "";
        int n = s.length();
        for (int center = 0; center < 2 * n - 1; ++center) {
            int left = center / 2;
            int right = left + center % 2;
            while (left >= 0 && right < n && s[left] == s[right]) {
                if (right - left + 1 > res.length())
                    res = s.substr(left, right - left + 1);
                left--;
                right++;
            }
        }
        return res;
    }
};