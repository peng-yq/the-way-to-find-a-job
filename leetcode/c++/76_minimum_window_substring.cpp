// https://leetcode.cn/problems/minimum-window-substring

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> tMap, sMap;
        int count = 0, start = 0, len = INT_MAX;
        for (char ch : t) tMap[ch]++;
        for (int i = 0, j = 0; j < s.length(); ++j) {
            if (tMap.count(s[j])) {
                sMap[s[j]]++;
                if (sMap[s[j]] == tMap[s[j]])
                    count++;
            }
            while (count == tMap.size()) {
                if (j - i + 1 < len) {
                    start = i;
                    len = j - i + 1;
                }
                if (sMap.count(s[i])) {
                    if (sMap[s[i]] == tMap[s[i]])
                        count--;
                    sMap[s[i]]--;
                }
                i++;
            }
        }
        return len == INT_MAX ? "" : s.substr(start, len);
    }
};

// 不定长滑动窗口加哈希表，先用一个哈希表记录目标串中字符出现的频率，这里我们用start和len来记录满足条件的子串，比起用两个字符串更加方便直接
// 在窗口滑动的过程中，我们只关注t中出现的字符，如果窗口中某个字符（t中出现的字符）的频率等于t中对应字符出现的频率相等，我们将count进行+1
// 当count和tMap的大小一致时，表示当前窗口满足匹配条件，开始缩小窗口，更新对应变量，直到窗口不满足条件
// 时间复杂度为O(m+n)，空间复杂度为O(1)，注意这里是O(1);