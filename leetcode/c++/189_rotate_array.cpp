// https://leetcode.cn/problems/rotate-array

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void reverse(vector<int>& nums, int begin, int end) {
        while (begin < end) {
            swap(nums[begin++], nums[end--]);
        }
    }
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        reverse(nums, 0, n-1);
        reverse(nums, 0, k-1);
        reverse(nums, k, n-1);
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)
// 轮转k次会发现数组后k%n个数会到数组的最前面，然后把前面的数依次后移，因此可以先反转整个数组，然后再依次反转前半部分和后半部分