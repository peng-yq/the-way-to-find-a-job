// https://leetcode.cn/problems/evaluate-reverse-polish-notation

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        int a, b;
        for (auto token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int a = stk.top(); stk.pop();
                int b = stk.top(); stk.pop();
                switch (token[0]) {
                    case '+':
                        stk.push(b + a);
                        break;
                    case '-':
                        stk.push(b - a);
                        break;
                    case '*':
                        stk.push(b * a);
                        break;
                    case '/':
                        stk.push(b / a);
                        break;
                }
            } else {
                stk.push(stoi(token));
            }
        }
        return stk.top();
    }
};

// O(n)，O(n)
// 遇到操作符号则取出栈顶两个数值进行操作，并把计算的数值压栈，遇到数值则直接入栈