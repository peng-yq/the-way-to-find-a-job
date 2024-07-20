/*
题意
小红有一笔旅游预算，旅游地点有若干组项目，每个项目有自己的价格和体验次数，求在当前预算下最多能体验的次数。预算和价格都是50的倍数。

输入描述
第一行输入总预算。
之后K行输入每个项目的花费和能体验的项目次数。

输出描述
在当前预算下最多能体验的次数。

示例1：
输入：
3000
100 2
200 3
100 0
500 1
200 2

输出：
8
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    int budget, cost, times;
    cin >> budget;
    budget /= 50;

    vector<pair<int, int>> projects;
    while (cin >> cost >> times)
        projects.push_back({cost / 50, times});

    vector<int> dp(budget + 1, 0);

    for (auto [a, b] : projects) {
        for (int i = budget; i >= a; --i) {
            dp[i] = max(dp[i], dp[i - a] + b);
        }
    }

    cout << dp[budget] << endl;
    return 0;
}

