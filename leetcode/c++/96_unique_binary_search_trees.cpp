// https://leetcode.cn/problems/unique-binary-search-trees

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }
};

// dp[i] = 以j为中点，左边的二叉搜索树数量*右边的二叉搜索树数量之和
// dp[i] += dp[j - 1] * dp[i - j];
// 时间复杂度O(n^2)