// https://leetcode.cn/problems/reorganize-string

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reorganizeString(string s) {
        vector<int> counts(26, 0);
        int maxNum = 0, n = s.size();
        char maxCh;
        for (auto ch : s) {
            if (++counts[ch - 'a'] > maxNum) {
                maxNum = counts[ch - 'a'];
                maxCh = ch;
            }
        }
        if (maxNum > n - maxNum + 1) 
            return "";
        string res(n, 0);
        int i = 0;
        for (; maxNum--; i += 2) {
            res[i] = maxCh;
        }
        counts[maxCh - 'a'] = 0;
        for (int j = 0; j < 26; ++j) {
            int cnt = counts[j];
            while (cnt--) {
                if (i >= n) {
                    i = 1;
                }
                res[i] = 'a' + j;
                i += 2;
            }
        }
        return res;
    }
};

// 和今天的每日一题差不多，只不过这道题是要求构造，同样的道理，只需统计出现次数最大的字符及其数量m
// 如果m > n - m + 1，那么说明肯定不能构造出匹配字符串
// 否则一定可以构造出大小为n的字符串，我们进行构造，首先将最大的字符串放到偶数位置，记录下一个需要放的位置i
// 依次遍历其他字符，依旧放到偶数位置，直到i大于等于n，为了避免相邻两字符一致，需要将i重置为1
// 依次放置到奇数位置