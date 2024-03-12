// https://leetcode.cn/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSales(vector<int>& sales) {
        int a = 0, b = 0, res = sales[0];
        a = sales[0];
        for (int i = 1; i < sales.size(); i++) {
            if (a >= 0)
                b = a + sales[i];
            else 
                b = sales[i];
            a = b;
            res = max(res, b);
        }
        return res;
    }
};

// O(n), O(1), 主要是状态转移方程, 也是求最大子数组之和