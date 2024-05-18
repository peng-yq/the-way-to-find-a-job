// https://leetcode.cn/problems/find-the-maximum-divisibility-score

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxDivScore(vector<int>& nums, vector<int>& divisors) {
        sort(divisors.begin(), divisors.end());
        int res = divisors[0], sum = 0;
        for (int i = 0; i < divisors.size(); ++i) {
            int tmp = 0;
            for (int j = 0; j < nums.size(); ++j) {
                if (nums[j] % divisors[i] == 0) 
                    ++tmp;
            }
            if (tmp > sum) {
                sum = tmp;
                res = divisors[i];
            } 
        }
        return res;
    }
};

// 一千二的简单题，再看数据范围这么小，我直接暴力就完事了
// O(mn), O(1)