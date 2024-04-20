// https://leetcode.cn/problems/longest-valid-parentheses

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stk;
        stk.push(-1);
        int res = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(')
                stk.push(i);
            else {
                stk.pop();
                if (stk.empty())
                    stk.push(i);
                else 
                    res = max(res, i - stk.top());
            }
        }
        return res;
    }
};

// 括号匹配第一反应就是用栈，栈很清晰，题解很多dp的，dp感觉有点麻烦。
// 因为是求子串长度，因此用栈保存括号的索引，先入栈一个-1表示开始点，-1方便求取长度
// (入栈索引，)先要出栈，如果先求再出栈，长度是不对的，比如[()()]，最后长度就是2，所以应该先出栈，再判断是否为空
// 如果为空了，表示没有匹配的（注意这里我们提前入栈了个-1）(，因此需要更新开始点的位置，也就是把当前)的索引入栈
// 如果不为空，表示有匹配的(，更新最长子串长度。