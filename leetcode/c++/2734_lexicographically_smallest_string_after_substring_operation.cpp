// https://leetcode.cn/problems/lexicographically-smallest-string-after-substring-operation

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string smallestString(string s) {
        bool flag=false;
        for(auto& i : s){
            if(i=='a' && !flag) continue;
            if(i=='a' && flag) break;
            i = i - 1;
            flag = true;
        }
        if(!flag) s[s.size()-1] = 'z';
        return s;
    }
};

// O(n),O(1)