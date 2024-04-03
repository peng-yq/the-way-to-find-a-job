// https://leetcode.cn/problems/find-peak-element

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[mid+1])
                right = mid;
            else 
                left = mid + 1;
        }
        return left;
    }
};

// 是的这个也能二分，只需要和相邻的点比较就行了
// O(logn)，O(1)