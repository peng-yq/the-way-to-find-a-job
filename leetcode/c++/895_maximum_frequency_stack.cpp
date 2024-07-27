// https://leetcode.cn/problems/maximum-frequency-stack

#include <bits/stdc++.h>
using namespace std;

class FreqStack {
public:
    vector<stack<int>> stacks;
    unordered_map<int, int> cnt;
    FreqStack() {

    }
    
    void push(int val) {
        if (cnt[val] == stacks.size()) {
            stacks.push_back({});
        }
        stacks[cnt[val]].push(val);
        cnt[val]++;
    }
    
    int pop() {
        int val = stacks.back().top();
        stacks.back().pop();
        if (stacks.back().empty()) 
            stacks.pop_back();
        cnt[val]--;
        return val;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */

// 用队列保存不同频率的栈，并用哈希表记录元素的个数
// 如果加入的元素的个数超过当前的最大频率，则新建一个栈
// 每次出栈都弹出频率最高的栈顶元素，如果为空则移除栈，同时更新元素个数