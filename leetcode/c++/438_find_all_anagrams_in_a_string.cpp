// https://leetcode.cn/problems/find-all-anagrams-in-a-string

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.length() < p.length())
            return {};
        vector<int> s_check(26, 0);
        vector<int> p_check(26, 0);
        for (char c : p)
            p_check[c-'a']++;
        vector<int> res;
        for (int i = 0, j = 0; j < s.length(); j++) {
            s_check[s[j]-'a']++;
            if (j-i+1 == p.length()) {
                if (s_check == p_check) 
                    res.push_back(i);
                s_check[s[i++]-'a']--;
            }
        }
        return res;
    }
};

// 时间复杂度为O(n)，比较两个数组时间复杂度为O(1)，空间复杂度为O(1)
// 其实没啥难度，主要是字符串的比较经常用统计26个字母出现的频率来做哈希表