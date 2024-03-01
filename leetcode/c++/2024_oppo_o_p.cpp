/*
小欧在一张纸上写了一个字母，是O 或者 P，盲人小皮想知道这个字母是什么，你需要告诉小皮，小欧写的字母是O还是 P。
已知纸张的空白部分用'.'表示，小欧写的部分用'#'表示。如果小欧写的是一个闭合的圆，那么就是 O，否则就是 P。

输入描述
第一行输入一个整数t表示询问次数。 对于每次询问，第一行输入两个整数n, m：表示纸张大小

接下来n行，每行输入一个长度为m的字符串。

输出描述
对每个询问输出一个O或者P表示答案. 数据保证一定小欧写的字母一定是O或者 P。

样例
输入
2
5 5
#####
#...#
#...#
#...#
#####
5 5
.###.
.#.#.
.###.
.#...
.#...

输出
O
P
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        bool res = true;
        vector<vector<char>> paper(n, vector<char>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) 
                cin >> paper[i][j];
        }
        for (int i = 0; i < m; i++) {
            if (paper[0][i] == '.') res = false;
            if (paper[n-1][i] == '.') res = false;
        }
        for (int i = 0; i < n; i++) {
            if (paper[i][0] == '.') res = false;
            if (paper[i][m-1] == '.') res = false; 
        }
        if (res) 
            cout << 'O' << endl;
        else 
            cout << 'P' << endl;
    }
}

// 模拟，题目不完整，测试用例也少，这题解写的太简单了，只能说codefun2000挺垃圾的