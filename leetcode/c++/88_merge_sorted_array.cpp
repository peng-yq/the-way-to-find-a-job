// https://leetcode.cn/problems/merge-sorted-array

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (n == 0)
            return;
        int i = 0, j = 0;
        vector<int> nums;
        while (i < m || j < n) {
            if (j >= n || i < m && nums1[i] <= nums2[j]) {
                nums.push_back(nums1[i++]);
            } else {
                nums.push_back(nums2[j++]);
            }
        }
        nums1 = nums;
    }
};

// O(m+n)，O(m+n)

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (j >= 0) {
            if (i >= 0 && nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }
    }
};

// O(m + n), O(1)