// https://leetcode.cn/problems/maximum-number-of-operations-with-the-same-score-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxOperations(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> memo(n, vector<int>(n));
        bool done = false;
        function<int (int, int, int)> delop = [&](int left, int right, int target) -> int {
            if (done) return 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) 
                    memo[i][j] = -1;
            }
            function<int (int, int)> dfs = [&](int left, int right) -> int {
                if (done) return 0;
                if (left >= right) {
                    done = true;
                    return 0;
                }
                int& res = memo[left][right];
                if (res != -1)
                    return res;
                res = 0;
                if (nums[left] + nums[left + 1] == target) res = max(res, dfs(left + 2, right) + 1);
                if (nums[right - 1] + nums[right] == target) res = max(res, dfs(left, right - 2) + 1);
                if (nums[left] + nums[right] == target) res = max(res, dfs(left + 1, right - 1) + 1);
                return res;
            };
            return dfs(left, right);
        };
        int res1 = delop(2, n - 1, nums[0] + nums[1]);
        int res2 = delop(0, n - 3, nums[n - 2] + nums[n - 1]);
        int res3 = delop(1, n - 2, nums[0] + nums[n - 1]);
        return max({res1, res2, res3}) + 1;
    }
};

// 时间复杂度为O(n^2)，空间复杂度为O(n^2)
// 很好的一道边界DP，一开始想到了用边界，但是用的if/else，没有去考虑各种情况，居然出其的过了大部分用例（只有2个没过），运气好，如果是笔试能捡漏
// 这道题每次递归都需要考虑3种情况，为了减少无效递归，使用记忆化数组，需要注意的是每次target变更需要初始化记忆化数组
// done的加入使得时间大大减少，因为只有当整个数组都被操作完毕才会被置为true，那么后面的递归也没必要执行了。