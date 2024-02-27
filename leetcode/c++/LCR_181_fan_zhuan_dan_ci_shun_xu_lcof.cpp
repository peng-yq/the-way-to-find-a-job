// https://leetcode.cn/problems/fan-zhuan-dan-ci-shun-xu-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseMessage(string message) {
        int j = message.length() - 1, end;
        string res;
        while (j >= 0 && message[j] == ' ') j--;
        while (j >= 0) {
            end = j;
            while (j >= 0 && message[j] != ' ') j--;
            for (int i = j + 1; i <= end; i++)
                res.push_back(message[i]);
            res.push_back(' ');
            while (j >= 0 && message[j] == ' ') j--;
        }
        if (!res.empty() && res.back() == ' ') {
            res.pop_back();
        }
        return res;
    }
};

// O(n), O(n)