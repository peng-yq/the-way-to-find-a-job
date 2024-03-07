// https://leetcode.cn/problems/group-anagrams/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        vector<vector<string>> res;
        for (auto& str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            map[key].push_back(str);
        }
        for (auto& i : map) {
            res.push_back(i.second);
        }
        return res;
    }
};

// 时间复杂度为O(n*k*logk)，空间复杂度为O(nk)：k为最长字符长度，排序需要k*logk，只适用于长度比较小的字符串