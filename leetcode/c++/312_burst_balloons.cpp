// https://leetcode.cn/problems/burst-balloons

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        auto shot = [&](int i, int j) {
            int m = 0;
            for (int k = i + 1; k < j; ++k) {
                int left = dp[i][k];
                int right = dp[k][j];
                m = max(m, left + right + nums[i] * nums[k] * nums[j]);
            }
            dp[i][j] = m;
        };
        for (int len = 2; len < n; ++len) {
            for (int i = 0; i < n - len; ++i) 
                shot(i, i + len);
        }
        return dp[0][n - 1];
    }
};

// 太难了，O(n^2)，
// 看这个吧：
// https://leetcode.cn/problems/burst-balloons/solutions/337630/zhe-ge-cai-pu-zi-ji-zai-jia-ye-neng-zuo-guan-jian-/?envType=daily-question&envId=2024-06-10