// https://leetcode.cn/problems/sliding-window-maximum/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> num_que;
        for (int i = 0, j = 0; j < nums.size(); j++) {
            while (!num_que.empty() && num_que.back() < nums[j])
                    num_que.pop_back();
            num_que.push_back(nums[j]);
            if (j - i + 1 > k) {
                if (num_que.front() == nums[i])
                    num_que.pop_front();
                i++;
            }
            if (j - i + 1 == k) 
                res.push_back(num_que.front());
        }
        return res;
    }
};

// 时间复杂度为O(n)， 空间复杂度为O(k)