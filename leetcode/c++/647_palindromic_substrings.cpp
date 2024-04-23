// https://leetcode.cn/problems/palindromic-substrings/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length(), res = 0;
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i <= j; ++i) {
                if (s[i] == s[j] && (j-i < 2 || dp[i+1][j-1] == true)) {
                    dp[i][j] = true;
                    res++;
                }
            }
        }
        return res;
    }
};

// 直接暴力也能过，但时空复杂度爆炸，其中时间复杂度为O(n^3)
// 动态规划：状态转移方程：if (s[i] == s[j] && (j-i < 2 || dp[i+1][j-1] == true)) {dp[i][j] = true;res++;}
// 也就是如果dp[i][j]是回文子串，在左右两边加1个相等的字符也是回文子串，然后单个字符和相等的2个字符也是回文子串
// 需要注意的是，状态转移方程的求解需要先从外部开始也就是j，因为如果从i开始外循环，状态转移方程中的[i+1]还没有求到
// 时间复杂度为O(n^2)，空间复杂度为O(n^2)

// 还有一种中心扩展法，也是基于动态规划的思想，我们选择一个或两个中间点（对应奇数长度/偶数长度字符的子串），并由这个中间点向两边扩展
// 中心点是2*n-1个，单个中心点是n个，2个中心点为n-1个
// 当中心点是奇数时，left和right为两边的字符，对应偶数长度的子串
// 当中心点时偶数时，left和right为同一个字符，对应奇数长度的子串
// 时间复杂度为O(n^2)，空间复杂度为O(1)

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length(), res = 0;
        for (int center = 0; center < 2 * n - 1; ++center) {
            int left = center / 2;
            int right = left + center % 2;
            while (left >= 0 && right < n && s[left] == s[right]) {
                res++;
                left--;
                right++;
            }
        }
        return res;
    }
};