// https://leetcode.cn/problems/maximum-number-of-vowels-in-a-substring-of-given-length/description/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxVowels (string s, int k) {
        unordered_set<char> st = {'a', 'e', 'i', 'o', 'u'};
        int res = 0; 
        for (int l = 0, r = 0, tmp = 0; r < s.length(); r++) {
            if (st.count(s[r]))
                tmp++;
            if (r >= l + k) {
                if (st.count(s[l]))
                    tmp--;
                l++;
            }
            res = max(res, tmp);
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)