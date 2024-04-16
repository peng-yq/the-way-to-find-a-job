// https://leetcode.cn/problems/jump-game-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int res = 0, max_length = 0, current_length = 0, n = nums.size();
        for (int i = 0; i < n - 1; ++i) {
            max_length = max(max_length, i + nums[i]);
            if (i == current_length) {
                res++;
                current_length = max_length;
                if (current_length >= n-1)
                    break;
            }
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)
// 每次都尽可能的跳最远，当然这个说法是有问题的，比如[2,3,1,1,4]，并不是说我们在第一步跳的时候就得跳到下标为2的地方
// 还得考虑全局，因此每一轮都求目前能跳到的最远距离，到达上一步中能跳到的最远距离时更新下一轮跳的最远距离为当前的最远距离