// https://leetcode.cn/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int digit(int i) {
        int res = 0;
        while (i != 0) {
            res += i % 10;
            i /= 10;
        }
        return res;
    }
    void check(int m, int n, int i, int j, int cnt, vector<vector<bool>>& visited, int& res) {
        if (i >= m || j >= n || visited[i][j] || digit(i) + digit(j) > cnt)
            return ;
        visited[i][j] = true;
        res++;
        check(m, n, i+1, j, cnt, visited, res);
        check(m, n, i, j+1, cnt, visited, res);
    }
    int wardrobeFinishing(int m, int n, int cnt) {
       int res = 0;
       vector<vector<bool>> visited(m, vector<bool>(n, false));
       check(m, n, 0, 0, cnt, visited, res);
       return res;
    }
};

// 时间复杂度为O(mn)，空间复杂度为O(mn)