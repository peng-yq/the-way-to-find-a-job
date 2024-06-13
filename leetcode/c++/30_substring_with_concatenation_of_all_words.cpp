// https://leetcode.cn/problems/substring-with-concatenation-of-all-words

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int wordLen = words[0].size(), wordsLen = words.size();
        if (s.size() < wordLen * wordsLen)
            return {};
        unordered_map<string, int> wordsMap;
        vector<int> res;
        for (auto word : words)
            ++wordsMap[word];
        for (int k = 0; k < wordLen; ++k) {
            unordered_map<string, int> sMap;
            int cnt = 0;
            for (int i = k, j= k; j + wordLen <= s.size(); j += wordLen) {
                ++cnt;
                ++sMap[s.substr(j, wordLen)];
                if (cnt == wordsLen) {
                    if (wordsMap == sMap)
                        res.push_back(i);
                    string tmp = s.substr(i, wordLen);
                    --sMap[tmp];
                    if (sMap[tmp] == 0)
                        sMap.erase(tmp);
                    i += wordLen;
                    --cnt;
                }
            }
        }
        return res;
    }
};

// 常规的滑动窗口题目，唯一需要注意的是区间的开始位置可以是从0~words[0].size()
// 时间复杂度为O(m*n)，m是words[0].size()，n是s.size()
// 空间复杂度为O(m + n)