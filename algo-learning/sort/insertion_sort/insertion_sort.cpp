#include <bits/stdc++.h>
using namespace std;

void insertionSort(vector<int> &nums) {
    for(int i = 1; i < nums.size(); i++) {
        int base = nums[i], j = i - 1;
        while(j >= 0 && nums[j] > base) {
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = base;
    }
}