// https://leetcode.cn/problems/minimum-operations-to-reduce-an-integer-to-0

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(int n) {
        int res = 0;
        while (n) {
            if ((n & 3) == 3) {
                ++n;
                ++res;
            }
            if ((n & 1) == 1) {
                ++res;
            }
            n >>= 1;
        }
        return res;
    }
};

// n 最低位为0则右移，不增加操作数
// n 的二进制末尾有连续两个 1 以上做 +1 操作去进位消除1， step++
// n 的二进制末尾只有一个 1 做 - 操作， step++
// O(n), O(1)