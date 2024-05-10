// https://leetcode.cn/problems/count-tested-devices-after-test-operations

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countTestedDevices(vector<int>& batteryPercentages) {
        int res = 0, n = batteryPercentages.size(), sum = 0;
        for (int i = 0; i < n; ++i) {
            if (batteryPercentages[i] - sum > 0) {
                res += 1;
                sum += 1;
            }
        }
        return res;
    }
};

// 小学生水平