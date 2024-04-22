// https://leetcode.cn/problems/find-the-duplicate-number/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast)
                break;
        } 
        fast = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};

// 因为数组大小为n+1，并且数组中只存在一个重复元素，元素大小为[1, n]
// 因此将数组看作一个链表，数组元素为下一个节点的索引，这道题就变成求环形链表的入口点
// 采用快慢指针，快的走2步，慢的走1步，当快的和慢的相遇时，慢的路程为s，快的为f = 2s = s+nb -> s = nb
// 此时再让快的从头开始，并且走一步，相遇时快的走了a步，慢的走了a+nb，也就是环的入口点
// 时间复杂度为O(n)，空间复杂度为O(1)