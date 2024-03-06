// https://leetcode.cn/problems/zi-fu-chuan-de-pai-lie-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(string& goods, vector<string>& res, string& tmp, vector<bool>& visited) {
        if (tmp.length() == goods.length()) {
            res.push_back(tmp);
            return;
        }
        for (int i = 0; i < goods.length(); i++) {
            if (visited[i] || (i > 0 && goods[i-1] == goods[i] && visited[i-1])) 
                continue;
            tmp.push_back(goods[i]);
            visited[i] = true;
            dfs(goods, res, tmp, visited);
            tmp.pop_back();
            visited[i] = false;          
        }
    }
    vector<string> goodsOrder(string goods) {
        vector<string> res;
        string tmp;
        vector<bool> visited(goods.length(), false);
        sort(goods.begin(), goods.end());
        dfs(goods, res, tmp, visited);
        return res;
    }
};

// 时间复杂度为O(n!*n)，空间复杂度为O(n^2)