// https://leetcode.cn/problems/roman-to-integer

#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> roma = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};

class Solution {
public:
    int romanToInt(string s) {
        int res = 0, n = s.size();
        for (int i = n - 1; i >= 0; --i) {
            if (i + 1 < n) {
                if (s[i] == 'I' && (s[i + 1] == 'V' || s[i + 1] == 'X'))
                    res -= 1;
                else if (s[i] == 'X' && (s[i + 1] == 'L' || s[i + 1] == 'C'))
                    res -= 10;
                else if (s[i] == 'C' && (s[i + 1] == 'D' || s[i + 1] == 'M'))
                    res -= 100;
                else 
                    res += roma[s[i]];
            } else
                res += roma[s[i]];
        }   
        return res;
    }
};

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> roma = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}
        };

        int res = 0;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            if (i + 1 < n && roma[s[i]] < roma[s[i + 1]]) {
                res -= roma[s[i]];
            } else {
                res += roma[s[i]];
            }
        }
        return res;
    }
};