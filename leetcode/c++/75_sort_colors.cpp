// https://leetcode.cn/problems/sort-colors

#include <bits/stdc++.h>
using  namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zero = 0, one = 0, two = 0;
        for (int num : nums) {
            if (num == 0) {
                nums[two++] = 2;
                nums[one++] = 1;
                nums[zero++] = 0;
            } else if (num == 1) {
                nums[two++] = 2;
                nums[one++] = 1;
            } else {
                nums[two++] = 2;
            }
        }
    }
};

// 三指针，zero，one，two分别保存下一次0，1，2插入的位置
// 一次遍历，如果是0，则需要把2，1，0位置往后移，因为0插入了，注意这里是保存的下一次需要插入的位置，此外为了避免覆盖，需要先移动2，再1
// 1和2类似
// O(n)，O(1)