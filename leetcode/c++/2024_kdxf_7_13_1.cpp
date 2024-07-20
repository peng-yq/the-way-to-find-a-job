// https://codefun2000.com/p/P1842

/*
牛牛拥有一个长度为 n 的01 串，现在他想知道，对于每个字符，在它前面的最近的不同字符的下标是多少？

输入描述
本题为多组测试数据，第一行输入一个正整数 T(1<=t<=100)，代表测试数据组数。对于每组测试数据，第一行输入一个正整数 n(1<=n<=1000)，代表初始 01串的长度。第二行输入一个长度为 n的01 串，代表初始字符串。

输出描述
对于每组测试数据，一行输出 n 个整数 a1,a2,...,an，其中 ai 代表初始字符串中第 i 个位置的字符前面，最近的不同字符的下标是 ai，特殊的，如果前面不存在不同字符，则输出 -1 表示不存在。

示例 1
输入
1
4
1101

输出
-1 -1 2 3
*/


#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        getchar();
        string s;
        getline(cin, s);
        vector<int> check(2, -1);
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0')
                cout << check[1] << " ";
            else 
                cout << check[0] << " ";
            check[s[i] - '0'] = i + 1;
        }
        cout << endl;
    }
    return 0;
}