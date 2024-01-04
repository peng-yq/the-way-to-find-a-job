// https://leetcode.cn/problems/validate-stack-sequences/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> num_stack;
        int i = 0;
        for (int num : pushed) {
            num_stack.push(num);
            while (!num_stack.empty() && num_stack.top() == popped[i]) {
                num_stack.pop();
                i++;
            }
        }
        return i == popped.size()? true : false;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)