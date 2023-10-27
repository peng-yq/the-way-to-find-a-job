#include <bits/stdc++.h>
using namespace std;

// we use exp = 10^(k - 1) here insted of k to save time to caculate 10^(k - 1) again

int digit(int num, int exp) {
    return (num / exp) % 10;
}

void countingSortDigit(vector<int> &nums, int exp) {
    vector<int>counter(10, 0);
    for(int num : nums) {
        counter[digit(num, exp)]++;
    }
    for(int i = 0; i < 10; i++) {
        counter[i + 1] += counter[i];
    }
    vector<int>res(nums.size(), 0);
    for(int i = nums.size() - 1; i >=0; i--) {
        res[counter[digit(nums[i], exp)] - 1] = nums[i];
        counter[digit(nums[i], exp)] --;
    }
    nums = res;
}

void radixSort(vector<int> &nums) {
     int m = *max_element(nums.begin(), nums.end());
     for(int exp = 1; exp <= m; exp *= 10)
        countingSortDigit(nums, exp);
}