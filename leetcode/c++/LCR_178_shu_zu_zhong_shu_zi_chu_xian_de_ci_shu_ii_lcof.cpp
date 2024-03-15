// https://leetcode.cn/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-ii-lcof

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trainingPlan(vector<int>& actions) {
        int array[32]{0};
        for (int action : actions) {
            for (int i = 0; i < 32; i++) {
                if ((action & 1) != 0)
                    array[i]++;
                action >>= 1; 
            }
        }
        int res = 0;
        for (int i = 31; i >= 0; i--) {
            res <<= 1; // 先左移确保新位的正确加入
            res |= array[i] % 3;
        }
        return res;
    }
};

// 统计每一位出现的次数，然后对3求余再复原原数即可，时间复杂度为O(n)，空间复杂度为O(1)
// 有限状态机实在是不会