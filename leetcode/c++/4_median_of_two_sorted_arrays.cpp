// https://leetcode.cn/problems/median-of-two-sorted-arrays

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size(), len2 = nums2.size(), i = 0, j = 0;
        int len = len1 + len2;
        int pre = 0, nxt = 0;
        for (int k = 0; k <= len/2; k++) {
            pre = nxt;
            if (i < len1 && (j >= len2 || nums1[i] < nums2[j]))
                nxt = nums1[i++];
            else 
                nxt = nums2[j++];
        }
        if (len & 1)
            return double(nxt);
        else {
            long long res = pre + nxt;
            return double(res / 2.0);
        }
    }
};

// O(m+n)的解法，复习了一下合并两个有序数组的写法

// O(log(m+n))的解法，很难想，和数据流中位数那道题有点像

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size(), len2 = nums2.size();
        if (len1 > len2) 
            return findMedianSortedArrays(nums2, nums1);
        int left = 0, right = len1;
        while (left <= right) {
            int mid1 = left + (right - left) / 2;
            int mid2 = (len1 + len2 + 1) / 2 - mid1;
            int maxleft1 = (mid1 == 0) ? INT_MIN : nums1[mid1-1];
            int minRight1 = (mid1 == len1) ? INT_MAX : nums1[mid1];
            int maxleft2 = (mid2 == 0) ? INT_MIN : nums2[mid2-1];
            int minRight2 = (mid2 == len2) ? INT_MAX : nums2[mid2];
            if (maxleft1 <= minRight2 && maxleft2 <= minRight1) {
                if ((len1 + len2) & 1) 
                    return double(max(maxleft1, maxleft2));
                else {
                    long long res = max(maxleft1, maxleft2) + min(minRight1, minRight2);
                    return res / 2.0;
                }
            } else if (maxleft1 > minRight2)
                right = mid1 - 1;
            else 
                left = mid1 + 1;
        }
        return 0;
    }
};