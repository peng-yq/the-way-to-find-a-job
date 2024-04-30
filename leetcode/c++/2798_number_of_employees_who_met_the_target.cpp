// https://leetcode.cn/problems/number-of-employees-who-met-the-target

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfEmployeesWhoMetTarget(vector<int>& hours, int target) {
        int res = 0;
        for (auto hour : hours) {
            if (hour >= target)
                ++res;
        }
        return res;
    }
};