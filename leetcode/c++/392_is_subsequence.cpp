// https://leetcode.cn/problems/is-subsequence/description/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int p1 = 0, p2 = 0;
        while(p1 < s.length() && p2 < t.length()) {
            if (s[p1] == t[p2]) {
                p1++;
            } 
              p2 ++;
        }
        return p1 == s.length();
    }
};