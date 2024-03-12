// https://leetcode.cn/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dismantlingAction(string arr) {
        unordered_map<char, int> check;
        int res = 0;
        for (int i = -1, j = 0; j < arr.length(); j++) {
            if (check.find(arr[j]) != check.end()) {
                i = max(i, check[arr[j]]);
                // 上面这个很关键，保证(i,j]的窗口是不重复的
            } 
            check[arr[j]] = j;
            res = max(res, j-i);
        }
        return res;
    }
};

// 不定长滑动窗口，时间复杂度为O(n)，空间复杂度为O(1)