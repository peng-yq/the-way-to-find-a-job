// https://leetcode.cn/problems/daily-temperatures

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res(temperatures.size(), 0);
        stack<int> stk;
        for (int i = temperatures.size() - 1; i >= 0; i--) {
            while (!stk.empty() && temperatures[i] >= temperatures[stk.top()]) {
                stk.pop();
            }
            if (!stk.empty())
                res[i] = stk.top() - i; 
            stk.push(i);
        }
        return res;
    }
};

// 单调栈，栈里只留有用的，并且单调
// 时间复杂度和空间复杂度均为O(n)