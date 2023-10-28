#include <bits/stdc++.h>
using namespace std;

void swap(vector<int> &nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

void selectionSort(vector<int> &nums) {
    for(int i = 0; i < nums.size() - 1; i++) {
        int min = i;
        // we use j = i + 1 instead of j = i, because the min = i
        for(int j = i + 1; j < nums.size(); j++) {
            if(nums[j] < nums[min]) {
                min = j;
            }
        }
        swap(nums, i, min);
    }
}