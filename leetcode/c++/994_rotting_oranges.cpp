// https://leetcode.cn/problems/rotting-oranges

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int row = grid.size(), col = grid[0].size(), count = 0, res = 0;
        queue<pair<int, int>> bads;
        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == 1) 
                    count++;
                if (grid[i][j] == 2)
                    bads.push({i, j});
            }
        }
        while (!bads.empty() && count > 0) {
            for (int k = bads.size(); k > 0; k--) {
                auto bad = bads.front();
                bads.pop();
                for (auto dir : directions) {
                    int i = bad.first + dir[0], j = bad.second + dir[1];
                    if (i >= 0 && i < row && j >= 0 && j < col && grid[i][j] == 1) {
                        grid[i][j] = 2;
                        count--;
                        bads.push({i, j});
                    }
                }
            }
            res++;
        }
        return count==0? res : -1;
    }
};

// BFS，先统计新鲜橘子的数量并把坏掉的橘子入队
// BFS直到队列为空或者没有新鲜的橘子了，这里注意每一轮的的时间需要在一轮队列结束后增加，这也是bfs的关键
// 时间复杂度和空间复杂度均为O(mn)