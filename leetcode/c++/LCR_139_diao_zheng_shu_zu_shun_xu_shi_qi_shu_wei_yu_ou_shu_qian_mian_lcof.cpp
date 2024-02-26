// https://leetcode.cn/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> trainingPlan(vector<int>& actions) {
        int i = 0, j = actions.size() - 1;
        while (i < j) {
            while (i < j && (actions[i] & 1) == 1)
                i++;
            while (i < j && (actions[j] & 1) == 0)
                j--;
            swap(actions[i], actions[j]);
        }
        return actions;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)
// 所有在i左边的均为奇数，在j右边的为偶数，不满足条件的则进行交换