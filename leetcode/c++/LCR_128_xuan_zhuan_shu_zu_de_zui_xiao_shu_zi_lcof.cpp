// https://leetcode.cn/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int stockManagement(vector<int>& stock) {
        int i = 0, j = stock.size() - 1;
        while (i <= j) {
            int m = i + (j - i) / 2;
            if (stock[m] > stock[j])
                i = m + 1;
            else if (stock[m] < stock[j])
                j = m;
            else 
                j = j - 1;
        }
        return stock[i];
    }
};

// 二分查找，充分利用数组之前为有序这个条件，时间复杂度为O(logn)，空间复杂度为O(1)