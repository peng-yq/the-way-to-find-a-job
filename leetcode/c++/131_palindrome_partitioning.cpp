// https://leetcode.cn/problems/palindrome-partitioning

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    bool check(string& s, int i, int j) {
        while (i < j) {
            if (s[i++] != s[j--])
                return false;
        }
        return true;
    }
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> tmp;
        function<void(int)> dfs = [&](int i) {
            if (i == s.length()) {
                res.push_back(tmp);
            }
            for (int j = i; j < s.length(); ++j) {
                if (check(s, i, j)) {
                    tmp.push_back(s.substr(i, j-i+1));
                    dfs(j+1);
                    tmp.pop_back();
                }
            }
        };
        dfs(0);
        return res;
    }
};

// 时间复杂度和空间复杂度很难算