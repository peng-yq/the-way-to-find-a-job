// https://leetcode.cn/problems/find-longest-awesome-substring

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestAwesome(string s) {
        int n = s.length(), res = 0, pre = 0;
        vector<int> pos(1 << 10, n);
        pos[0] = -1;
        for (int i = 0; i < n; ++i) {
            pre ^= 1 << (s[i] - '0');
            for (int j = 0; j < 10; ++j)
                res = max(res, i - pos[pre ^ (1 << j)]);
            res = max(res, i - pos[pre]);
            if (pos[pre] == n)
                pos[pre] = i;
        }
        return res;
    }
};

// 时间复杂度为O(n*10)，空间复杂度为O(2*10)

// 前缀和 + 位掩码，使用位掩码来表示某个元素的奇偶数比如1010表示数字1和3个数为奇数，其他为偶数个数
// 如何更新位掩码呢？用异或：pre ^= 1 << (s[i] - '0');
// 此外，我们还需要记录每个位掩码第一次出现的次数，每个元素都有0和1两种情况，一共2^10种情况，用一个大小位2^10的数组来模拟，初始大小为n
// 当pos[pre] = n时表示这个位掩码第一次出现，更新其位置，此外pos[0]需要记录为-1，方便计算长度
// res = max(res, i - pos[pre]);
// 这行代码检查当前位掩码 pre 第一次出现的位置。如果 pre 在之前已经出现过（即 pos[pre] 不是初始化的 n），
// 则说明从 pos[pre] + 1 到 i 这段子字符串中，所有字符的出现次数的奇偶性都没有改变
// （因为同一个位掩码再次出现意味着每个数字的出现次数增加了偶数次）。
// 这意味着这个子字符串的字符可以重新排列成一个回文字符串。
// 因此，我们更新 res 为这个子字符串的长度 i - pos[pre]。

// for (int j = 0; j < 10; ++j) res = max(res, i - pos[pre ^ (1 << j)]);
// 这个循环遍历所有可能的数字（0到9），并对当前的位掩码 pre 进行翻转操作。pre ^ (1 << j) 表示将 pre 中的第 j 位翻转（如果是0变成1，如果是1变成0），
// 这相当于改变了数字 j 的出现次数的奇偶性。
// 如果 pos[pre ^ (1 << j)] 不是初始化的 n，则说明在之前的某个位置，位掩码为 pre 翻转第 j 位后的值已经出现过。
// 这意味着从 pos[pre ^ (1 << j)] + 1 到 i 这段子字符串中，除了数字 j 的出现次数是奇数次（因为我们翻转了它的奇偶性），
// 其他所有数字的出现次数都是偶数次。这样的子字符串可以通过重新排列成为一个回文字符串，其中一个字符（数字 j）位于中心。