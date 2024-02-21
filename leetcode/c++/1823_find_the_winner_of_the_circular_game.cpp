// https://leetcode.cn/problems/find-the-winner-of-the-circular-game/description

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findTheWinner(int n, int k) {
        queue<int> que;
        for (int i = 1; i <= n; i++)
            que.push(i);
        while(que.size() != 1) {
            for (int i = 0; i < k-1; i++) {
                que.push(que.front());
                que.pop();
            }
            que.pop();
        }
        return que.front();
    }
};

// 采用模拟的方法，使用队列来模拟，时间复杂度为O(nk)，空间复杂度为O(n)
// 自己手写循环链表的话会快很多