// https://leetcode.cn/problems/happy-number

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int step(int n) {
        int sum = 0;
        while (n) {
            int tmp = n % 10;
            sum += tmp * tmp;
            n /= 10;
        }
        return sum;
    }
    bool isHappy(int n) {
        int slow = n, fast = n;
        do {
            slow = step(slow);
            fast = step(step(fast));
        } while (slow != fast);
        return slow == 1;
    }
};

// step函数用于求解数字n的各位的平方和，得到下一个状态
// 由于固定位数的位元素平方和处于固定的区间，因此状态的转移过程中要么会形成环，要么在1结束
// 使用快慢指针的方式去判断快乐数，如果在1相遇则说明为快乐数
// O(logn), O(1)