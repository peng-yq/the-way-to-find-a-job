#include <bits/stdc++.h>
using namespace std;

void move(vector<int> &src, vector<int> &tar) {
    int pan = src.back();
    src.pop_back();
    tar.push_back(pan);
}

void dfs(int i, vector<int> &src, vector<int> &buf, vector<int> &tar) {
    if(i == 1) {
        move(src, tar);
    }
    dfs(i-1, src, tar, buf);
    move(src, tar);
    dfs(i-1, buf, src, tar);
}

void solveHanota(vector<int> &A, vector<int> &B, vector<int> &C) {
    dfs(A.size(), A, B, C);
}