/*
小美拿到了一个n*n 的矩阵，其中每个元素是 0 或者 1。
小美认为一个矩形区域是完美的，当且仅当该区域内 0 的数量恰好等于 1 的数量。
现在，小美希望你回答有多少个i*i的完美矩形区域。你需要回答1<=i<=n的所有答案。

输入描述

第一行输入一个正整数n，代表矩阵大小。
接下来的n行，每行输入一个长度为n的01 串，用来表示矩阵。

输出描述
输出n行，第i行输出的I*I 完美矩形区域的数量。

示例 1

输入
4
1010
0101
1100
0011

输出
0
7
0
1
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> str(n+1, string(n+1, '0'));
    vector<vector<int>> sum(n+1, vector<int>(n+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> str[i][j];
            sum[i][j] = sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1] + (str[i][j] - '0');
        }
    }
    for (int i = 1; i <= n; i++) {
        int res = 0;
        if ((i & 1) == 1) {
            cout << 0 << endl;
            continue;
        }
        if (i == n) {
            if (sum[n][n] == (n * n) / 2)
                cout << 1 << endl;
            else 
                cout << 0 << endl;
            break;
        }
        for (int x1 = 1; x1 <= n; x1++) {
            for (int y1 = 1; y1 <= n; y1++) {
                int x2 = x1 + i -1, y2 = y1 + i -1;
                if (x2 <= n && y2 <= n) {
                    if (sum[x2][y2] - sum[x2][y1-1] - sum[x1-1][y2] + sum[x1-1][y1-1] == (i * i) / 2)
                        res++;
                }
            }
        }
        cout << res << endl;
    }
}

// 二维前缀和