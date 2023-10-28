#include <bits/stdc++.h>
using namespace std;

void bubbleSortWithFlag(vector<int> &nums) {
    for(int i = nums.size() - 1, flag = 0; flag && i > 0; i--) {
        for(int j = 0; j< i; j++) {
                if (nums[j] > nums[j + 1]) {
                    swap(nums[j], nums[j + 1]);
                    flag = 1;
                }
        }
    }
}