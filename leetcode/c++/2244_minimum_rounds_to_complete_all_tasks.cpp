// https://leetcode.cn/problems/minimum-rounds-to-complete-all-tasks

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumRounds(vector<int>& tasks) {
        int res = 0;
        unordered_map<int, int> taskMap;
        for (auto task : tasks) {
            ++taskMap[task];
        }
        for (auto m : taskMap) {
            if (m.second == 1) {
                return -1;
            }
            if (m.second % 3 == 0) {
                res += m.second / 3;
            } else {
                res += m.second / 3 + 1;
            }
        }
        return res;
    }
};

// 先统计每个任务的个数，遍历任务，如果为1直接返回-1（大于等于2的数都能被拆分为2和3），
// 如果能被3整除，直接加商，否则加上商+1
// 前者也就是一次做3个任务，后者则是余1的话把其中一个3和这个1凑成2个2，余2则是凑成1个3和1个2
// 时间复杂度为O(n)，空间复杂度为O(n)