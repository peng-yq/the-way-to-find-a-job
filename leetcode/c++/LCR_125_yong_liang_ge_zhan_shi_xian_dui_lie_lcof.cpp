// https://leetcode.cn/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/description

#include <bits/stdc++.h>
using namespace std;

class CQueue {
public:
    stack<int> A, B;
    CQueue() {

    }
    
    void appendTail(int value) {
        A.push(value);
    }
    
    int deleteHead() {
        if (!B.empty()) {
            int res = B.top();
            B.pop();
            return res;
        }
        if (A.empty())
            return -1;
        while (!A.empty()) {
            int tmp = A.top();
            A.pop();
            B.push(tmp);
        }
        return deleteHead();
    }
};

// 一个栈用于存储入队，另外一个栈用于存储出队