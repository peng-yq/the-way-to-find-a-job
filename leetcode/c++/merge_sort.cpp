#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& nums, int left, int mid, int right) {
    vector<int> tmp(nums.begin() + left, nums.begin() + right + 1);
    // 注意下面的索引
    int left_start = left - left, left_end = mid - left;
    int right_start = mid + 1 - left, right_end = right -left;
    for (int k = left; k <= right; k++) {
        if (left_start > left_end) {
            nums[k] = tmp[right_start++];
        } else if (right_start > right_end || tmp[right_start] > tmp[left_start]) {
            nums[k] = tmp[left_start++];
        } else {
            nums[k] = tmp[right_start++];
        }
    }
}

void mergeSort(vector<int>& nums, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid+1, right);
    merge(nums, left, mid, right);
}

int main() {
    vector<int> nums = {1, 5, 8, 3, -1};
    mergeSort(nums, 0, nums.size()-1);
    for (auto num : nums)
        cout << num << endl;
    return 0;
}

// 时间复杂度为O(nlogn)，稳定排序，空间复杂度为O(n)；快排为不稳定，空间复杂度为O(logn)