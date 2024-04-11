// https://leetcode.cn/problems/longest-palindrome

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> nums;
        int res = 0, flag = 0;
        for (auto ch : s)
            nums[ch]++;
        for (auto kv : nums) {
            res += kv.second / 2 * 2; // 小trick
            if (kv.second & 1)
                flag = 1;
        }
        return res + flag;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)
// 回文串为偶数所有字符都是偶数，回文串为奇数则只有中间的字符为奇数，其他都是偶数
// 因此先统计每个字符的出现次数，如果是偶数则直接全部加入，如果是奇数则次数减一加入，最后再任选一个奇数次字符放中间即可