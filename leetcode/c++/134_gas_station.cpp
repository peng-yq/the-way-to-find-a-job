// https://leetcode.cn/problems/gas-station

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size(), total_tank = 0, current_tank = 0, res = 0;
        for (int i = 0; i < n; ++i) {
            total_tank += gas[i] - cost[i];
            current_tank += gas[i] - cost[i];
            if (current_tank < 0) {
                current_tank = 0;
                res = i + 1;
            }
        }
        return total_tank >= 0 ? res : -1;
    }
};

// 贪心，如果能顺利跑完一圈说明gas的和是大于cost的和的，
// 题目确保了如果有解是唯一解，使用total_tank累加站点拥有的油和前往下一个站点的油的差值，如果最后大于0说明有解
// 使用current_tank记录起点到当前站点的剩余油，如果小于0说明res到i中间的任何一个站点都不能做为起点，因为油量是在逐渐减少的
// O(n)，O(1)