// https://leetcode.cn/problems/plus-one

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> res;
        stack<int> stk;
        int sum = 0, pre = 1;
        for (int i = digits.size() - 1; i >= 0; --i) {
            int tmp = digits[i] + pre;
            pre = tmp / 10;
            tmp %= 10;
            stk.push(tmp);
        }
        if (pre)
            stk.push(pre);
        while (!stk.empty()) {
            res.push_back(stk.top());
            stk.pop();
        }
        return res;
    }
};

// O(n), O(n)