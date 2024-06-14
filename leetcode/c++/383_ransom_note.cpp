// https://leetcode.cn/problems/ransom-note

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> rMap(26, 0);
        vector<int> mMap(26, 0);
        for (auto c : ransomNote)
            rMap[c - 'a'] += 1;
        for (auto c : magazine)
            mMap[c - 'a'] += 1;
        for (int i = 0; i < 26; ++i) {
            if (rMap[i] > mMap[i])
                return false;
        }
        return true;
    }
};

// O(m+n)，O(1)