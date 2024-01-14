// https://leetcode.cn/problems/kth-largest-element-in-an-array/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int pivot = nums[rand() % nums.size()];
        vector<int> small, equal, big;
        for (int num : nums) {
            if (num > pivot) {
                big.push_back(num);
            }
            if (num == pivot) {
                equal.push_back(num);
            }
            if (num < pivot) {
                small.push_back(num);
            }
        }
        if (big.size() >= k) return findKthLargest(big, k);
        if (equal.size() + big.size() < k) return findKthLargest(small, k - equal.size() - big.size());
        return pivot; 
    }
};

// 时间复杂度为O(n)，空间复杂度也为O(n)
// 确定pivot一定要随机，会快很多
// 最小堆解法

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        
        for (int num : nums) {
            if (minHeap.size() < k) {
                minHeap.push(num);
            } else if (num > minHeap.top()) {
                minHeap.pop();
                minHeap.push(num);
            }
        }
        
        return minHeap.top();
    }
};