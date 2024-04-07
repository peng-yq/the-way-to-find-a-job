// https://leetcode.cn/problems/flood-fill

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs(vector<vector<int>>& image, int i, int j, int color, int baseNum) {
        int row = image.size(), col = image[0].size();
        if (i < 0 || i >= row || j < 0 || j >= col || image[i][j] != baseNum)
            return;
        image[i][j] = color;
        dfs(image, i+1, j, color, baseNum);
        dfs(image, i-1, j, color, baseNum);
        dfs(image, i, j+1, color, baseNum);
        dfs(image, i, j-1, color, baseNum);
    }
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        if (image[sr][sc] == color)
            return image;
        dfs(image, sr, sc, color, image[sr][sc]);
        return image;
    }
};

// 需要注意如果初始点等于color时，直接返回image，避免无线递归
// 时间复杂度和空间复杂度均为O(mn)