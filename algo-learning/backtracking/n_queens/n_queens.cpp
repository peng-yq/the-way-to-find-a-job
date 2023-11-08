#include <bits/stdc++.h>
using namespace std;


void backtrack(int row, int n, vector<vector<char>> &state, vector<vector<vector<char>>> &res, vector<bool> &cols, vector<bool> &diags1, vector<bool> &diags2) {
    if (row == n) {
        res.push_back(state);
        return;
    }
    for(int col = 0; col < n; col++) {
        if (cols[col] || diags1[row - col + n - 1] || diags2[row + col])
            continue;
        cols[col] = diags1[row - col + n - 1] = diags2[row + col] = true;
        state[row][col] = 'Q';
        backtrack(row + 1, n, state, res, cols, diags1, diags2);
        state[row][col] = '#';
        cols[col] = diags1[row - col + n - 1] = diags2[row + col] = false;
    }
}

vector<vector<vector<char>>> nQueens(int n) {
    vector<vector<vector<char>>> res;
    vector<vector<char>> state(n, vector<char>(n,'#'));
    vector<bool> cols(n, false); 
    vector<bool> diags1(2*n-1, false);
    vector<bool> diags2(2*n-1, false);
    backtrack(0, n, state, res, cols, diags1, diags2);
}

