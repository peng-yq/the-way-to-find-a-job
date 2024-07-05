// https://leetcode.cn/problems/modify-the-matrix

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        for(int j = 0; j < m; j++){
            int zd = -1;
            for(int i = 0; i < n; i++){
                zd = max(zd,matrix[i][j]);
            }
            for(int i = 0; i < n; i++){
                if(matrix[i][j] == -1){
                    matrix[i][j] = zd;
                }
            }
        }
        return matrix;
    }
};

// O(mn), O(1)