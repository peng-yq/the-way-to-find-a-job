// https://leetcode.cn/problems/decode-string/description

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string decodeString(string s) {
        string res;
        stack<int> stack_num;
        stack<string> stack_res;
        int num = 0;
        for (char c : s) {
            if (c == '[') {
                stack_num.push(num);
                stack_res.push(res);
                num = 0;
                res = "";
            } else if (c == ']') {
                string tmp;
                for (int i = stack_num.top(); i > 0; i--)
                    tmp += res;
                stack_num.pop();
                res = stack_res.top() + tmp;
                stack_res.pop();
            } else if (c <= '9' && c >='0')
                num = num * 10 + (c - '0');
            else 
                res += c;
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为o(n)