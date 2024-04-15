// https://leetcode.cn/problems/top-k-frequent-elements

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> check;
        vector<int> res;
        for (auto num : nums) {
            check[num]++;
        }
        vector<pair<int, int>> sortnums(check.begin(), check.end());
        sort(sortnums.begin(), sortnums.end(), [](const pair<int, int>& a, const pair<int, int>& b)->bool{
            return a.second > b.second;
        });
        for (int i = 0; i < k; ++i) {
            res.push_back(sortnums[i].first);
        }
        return res;
    }
    vector<int> topKFrequent2(vector<int>& nums, int k) {
        map<int, int> check;
        vector<int> res;
        for (auto num : nums) {
            check[num]++;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        for (auto [key, value] : check) {
            minHeap.push({value, key});
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        while (!minHeap.empty()) {
            res.push_back(minHeap.top().second);
            minHeap.pop();
        }
        return res;
    }
};

// 解决topk通常有下面三种解法（还有个冒泡的，O(nk)就不写了）
// O(nlogn)解法，空间复杂度为O(n)
// O(nlogk)解法，空间复杂度为O(n)，用堆，前k大就用大小为k的小顶堆；前k小就用大小为k的大顶堆

class Solution {
public:
    int partitation(vector<pair<int, int>>& nums, int low, int high) {
        int pivot = low;
        int i = low, j = high;
        while (i < j) {
            while (i < j && nums[j].first <= nums[pivot].first)
                j--;
            while (i < j && nums[i].first >= nums[pivot].first)
                i++;
            swap(nums[j], nums[i]);
        }
        swap(nums[i], nums[pivot]);
        return i;
    } 
    void quickSelect(vector<pair<int, int>>& nums, int low, int high, int k) {
        if (low >= high)
            return;
        int n = partitation(nums, low, high);
        if (n == k-1)
            return;
        else if (n > k-1)
            quickSelect(nums, low, n-1, k);
        else 
            quickSelect(nums, n+1, high, k);
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> res;
        vector<pair<int, int>> tmp;
        unordered_map<int, int> check;
        for (const auto& num : nums) {
            check[num]++;
        }
        for (const auto& num : check) {
            tmp.push_back({num.second, num.first});
        }
        quickSelect(tmp, 0, tmp.size()-1, k);
        for (int i = 0; i < k; i++) {
            res.push_back(tmp[i].second);
        }
        return res;
    }
};

// 快速选择，时间复杂度为O(n)，基准值直接选左边的得了，不坑自己了