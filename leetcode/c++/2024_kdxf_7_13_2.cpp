// https://codefun2000.com/p/P1843

/*
给定n个数字A1,A2,..An，请求出这些数字中出现次数小于等于k的最小的数。

输入描述
第一行正整数n,k，接下来一行n个正整数，第i个表示Ai 1<=k<=n<=10^5,1<=Ai<=10^9

输出描述
一行一个整数，表示答案。如果不存在出现次数少于等于k次的数字，输出-1

示例 1
输入
5 2
1 1 1 2 3

输出
2
说明
1出现了三次，不合法；2,3均只出现了一次，其中2最小

示例 2
输入
8 2
1 1 4 5 7 1 3 3

输出
3
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