// https://leetcode.cn/problems/dui-lie-de-zui-da-zhi-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Checkout {
public:
    queue<int> q;
    deque<int> s;
    Checkout() {

    }
    
    int get_max() {
        if (q.empty())
            return -1;
        return s.front();
    }
    
    void add(int value) {
        q.push(value);
        while(!s.empty() && s.back() < value)
            s.pop_back();
        s.push_back(value);
    }
    
    int remove() {
        if (q.empty())
            return -1;
        int res = q.front();
        if (res == s.front())
            s.pop_front();
        q.pop();
        return res;
    }
};


// 双端单调队列存储最大值