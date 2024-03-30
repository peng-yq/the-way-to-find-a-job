#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& nums, int left, int right) {
    int i = left, j = right;
    while (i < j) {
        while (i < j && nums[j] >= nums[left])
            j--;
        while (i < j && nums[i] <= nums[left])
            i++;       
        swap(nums[i], nums[j]);
    }
    swap(nums[left], nums[i]);
    return i;
}

void quickSort(vector<int>& nums, int left, int right) {
    if (left >= right) return;
    int mid = partition(nums, left, right);
    quickSort(nums, left, mid - 1);
    quickSort(nums, mid + 1, right);
}

int main() {
    vector<int> nums = {1, 5, 8, 3, -1};
    quickSort(nums, 0, nums.size()-1);
    for (auto num : nums)
        cout << num << endl;
    return 0;
}

// 左端元素为基准值时，必须从右向左开始！！！！
// 因为：
// swap(nums[left], nums[i]);
// return i; 要求nums[i] >= nums[left]，如果是从左往右开始，[1,2,3]这样就会导致遍历完变成[3,2,1]，从左往右则不会