// https://leetcode.cn/problems/implement-queue-using-stacks/description

#include <bits/stdc++.h>
using namespace std;

class MyQueue {
private:
    stack<int>A, B;
public:
    MyQueue() {

    }
    
    void push(int x) {
       A.push(x);
    }
    
    int pop() {
        int peek = this->peek();
        if ( peek!= -1 ) 
            B.pop();        
        return peek;
    }
    
    int peek() {
        if (!B.empty())
            return B.top();
        if (A.empty())
            return -1;
        while (!A.empty()) {
            B.push(A.top());
            A.pop();
        }
        return B.top();
    }
    
    bool empty() {
        return A.empty() && B.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

// 时间复杂度为O(1), 空间复杂度为O(n)