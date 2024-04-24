// https://leetcode.cn/problems/edit-distance

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.length(), n2 = word2.length();
        vector<vector<int>> dp(n1+1, vector<int>(n2+1, 600));
        for (int i = 0; i <= n1; i++) 
            dp[i][0] = i;
        for (int i = 0; i <= n2; i++) 
            dp[0][i] = i;
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (word1[i-1] == word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else 
                    dp[i][j] = min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
            }
        }
        return dp[n1][n2];
    }
};

// 记得每次操作要+1+1+1！！！
// 时间复杂度为O(nm)，空间复杂度为O(nm)
// dp[i-1][j]：删除word1[i-1]
// dp[i][j-1]：增加word1[i-1]
// dp[i-1][j-1]：替换word1[i-1] = word[j-1]