#include <bits/stdc++.h>
using namespace std;

void swap(vector<int>&nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

void siftDown(vector<int> &nums, int n, int i) {
    while(true){
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int ma = i;
        if (l < n && nums[l] > nums[i])
            ma = l;
        if (r < n && nums[r] > nums[i])
            ma = r;
        if (ma == i)
            break;
        swap(nums, ma, i);
        i = ma;
    }
}

void heapSort(vector<int> &nums) {
    for(int i = nums.size() / 2 - 1; i >=0; i--) {
        siftDown(nums, nums.size(), i);
    }
    for(int i = nums.size() - 1; i >=0; i--) {
        swap(nums, 0, i);
        siftDown(nums, i, 0);
    }
}