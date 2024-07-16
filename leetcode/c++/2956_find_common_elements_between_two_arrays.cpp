// https://leetcode.cn/problems/find-common-elements-between-two-arrays

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findIntersectionValues(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> s1(nums1.begin(), nums1.end());
        unordered_set<int> s2(nums2.begin(), nums2.end());
        vector<int> res(2, 0);
        for (int x : nums1) res[0] += s2.count(x);
        for (int x : nums2) res[1] += s1.count(x);
        return res;
    }
};

// 时间复杂度和空间复杂度都为O(n)