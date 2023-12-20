// https://leetcode.cn/problems/valid-parentheses/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
       stack<char>S;
       for (char ch : s) {
            if (S.empty() && (ch == ')' || ch == ']' || ch == '}'))
                return false;
            if (ch == '(' || ch == '[' || ch == '{')
                S.push(ch);
            else if (S.top() == '(' && ch == ')' || S.top() == '[' && ch == ']' || S.top() == '{' && ch == '}')
                S.pop();
            else
                return false;
       }
       return S.empty();
    }
};

// 时间复杂度和空间复杂度都是O(n)