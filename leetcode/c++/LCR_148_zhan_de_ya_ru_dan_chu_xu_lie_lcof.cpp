// https://leetcode.cn/problems/zhan-de-ya-ru-dan-chu-xu-lie-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool validateBookSequences(vector<int>& putIn, vector<int>& takeOut) {
        stack<int> st;
        int i = 0;
        for (int num : putIn) {
            st.push(num);
            while (!st.empty() && st.top() == takeOut[i]) {
                st.pop();
                i++;
            }
        }
        return i == takeOut.size();
    }
};

// 模拟出栈过程，遇到匹配值则进行出栈，最后检查是否全部出栈
// O(n), O(n)