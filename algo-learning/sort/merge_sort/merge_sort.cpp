#include <bits/stdc++.h>
using namespace std;

void merge(vector<int> &nums, int left, int mid, int right) {
    vector<int> tmp(nums.begin() + left, nums.begin() + right + 1);
    int leftStart = left - left, leftEnd = mid - left;
    int rightStart = mid + 1 - left, rightEnd = right- left;
    int i = leftStart, j = rightStart;
    for(int k = left; k <= right; k++) {
        if(i > leftEnd) {
            nums[k] = tmp[j++];
        }
        else if(j > rightEnd || tmp[i] <= tmp[j]) {
            nums[k] = tmp[i++];
        }
        else {
            nums[k] = tmp[j++];
        }
    }
}

void mergeSort(vector<int> &nums, int left, int right) {
    if(left >= right) 
        return;
    int mid = (left + right) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid + 1, right);
    merge(nums, left, mid, right);
}