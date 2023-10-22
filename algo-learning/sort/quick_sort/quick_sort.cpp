#include <bits/stdc++.h>
using namespace std;

void swap(vector<int> &nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

int partition(vector<int> &nums, int left, int right) {
    int i = left, j = right;
    while (i < j) {
        while (i < j && nums[left] <= nums[j])
            j--;
        while (i < j && nums[left] >= nums[i])
            i++;
        swap(nums, i, j);
    }
    swap(nums, left, i);
    return i;
}

void quickSort(vector<int> &nums, int left, int right) {
    if (left >= right)
        return; 
    int pivot = partition(nums, left, right);
    partition(nums, left, pivot - 1);
    partition(nums, pivot + 1, right);
}

