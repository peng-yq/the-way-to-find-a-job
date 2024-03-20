// https://leetcode.cn/problems/generate-parentheses

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(vector<string>& res, string tmp, int n, int left, int right) {
        if (tmp.length() == 2*n) {
            res.push_back(tmp);
            return;
        }
        if (left < n) 
            dfs(res, tmp + '(', n, left+1, right);
        if (left > right)
            dfs(res, tmp + ')', n, left, right+1);
    }
    vector<string> generateParenthesis(int n) {
        vector<string>res;
        dfs(res, "", n, 0, 0);
        return res;
    }
};

// 这个回溯还挺难写的（虽然好想），时间复杂度比较难计算