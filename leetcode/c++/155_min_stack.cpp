// https://leetcode.cn/problems/min-stack/description

#include <bits/stdc++.h>
using namespace std;

class MinStack {
private:
    stack<int> real_stack;
    stack<int> min_stack;
public:
    MinStack() {

    }
    
    void push(int val) {
        real_stack.push(val);
        if (min_stack.empty() || val <= min_stack.top()) 
            min_stack.push(val);
    }
    
    void pop() {
        if (real_stack.top() == min_stack.top())
            min_stack.pop();
        real_stack.pop();
    }
    
    int top() {
        return real_stack.top();
    }   
    
    int getMin() {
        return min_stack.top();
    }
};

// 时间复杂度为O(1)，空间复杂度为O(n)