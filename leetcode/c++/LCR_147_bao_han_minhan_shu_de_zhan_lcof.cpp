// https://leetcode.cn/problems/bao-han-minhan-shu-de-zhan-lcof/description

#include <bits/stdc++.h>
using namespace std;

class MinStack {
public:
    stack<int> s1, s2;
    MinStack() {

    }
    
    void push(int x) {
        s1.push(x);
        if (s2.empty() || x <= s2.top())
            s2.push(x);
    }
    
    void pop() {
        if (s1.top() == s2.top())
            s2.pop();
        s1.pop();
    }
    
    int top() {
        return s1.top();
    }
    
    int getMin() {
        return s2.top();
    }
};

// 用一个栈来存储栈中的最小值，每次入队时将最新的最小值加入，最小值出队时在两个栈同步删除