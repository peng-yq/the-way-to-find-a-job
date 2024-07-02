// https://leetcode.cn/problems/maximum-prime-difference/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumPrimeDifference(vector<int>& nums) {
        auto check = [](int num)->bool {
            for (int i = 2; i * i <= num; ++i) {
                if (num % i == 0)
                    return false;
            }
            return num >= 2;
        };
        int first, last, flag = 1;
        for (int i = 0; i < nums.size(); ++i) {
            if (check(nums[i])) {
                if (flag) {
                    first = i;
                    flag = 0;
                }
                last = i;
            }
        }
        return last - first;
    }
};

// 一种方法是可以先计算出100以内的质数，用哈希表保存
// 一种就是直接判断了