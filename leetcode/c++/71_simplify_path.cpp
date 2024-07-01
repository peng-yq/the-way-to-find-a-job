// https://leetcode.cn/problems/simplify-path

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        stack<string> stk;
        vector<string> elements;
        int n = path.size();
        string res;
        for(int i = 0; i < n; ++i) {
            while (i < n && path[i] == '/') {
                ++i;
            }
            int j = i;
            while (j < n && path[j] != '/') {
                ++j;
            }
            string tmp = path.substr(i, j - i);
            if (tmp == "..") {
                if (!stk.empty())
                    stk.pop();
            }
            else if (tmp != "." && tmp != "")
                stk.push(tmp);
            i = j;
        }
        while (!stk.empty()) {
            elements.push_back(stk.top());
            stk.pop();
        }
        reverse(elements.begin(), elements.end());
        for (auto& e : elements) {
            res += "/" + e;
        }
        return res.empty() ? "/" : res;
    }
};

// O(n), O(n)
// 难到不难