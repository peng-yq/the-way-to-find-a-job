/*
小美拿到了一个大小为n的数组，她希望删除一个区间后，使得剩余所有元素的乘积末尾至少有k个 0。小美想知道，一共有多少种不同的删除方案？

输入描述
第一行输入两个正整数n，k。第二行输入n个正整数ai，代表小美拿到的数组。
1<=n,k<=10^5
1<=ai<=10^9

输出描述
一个整数，代表删除的方案数。

示例 1

输入
5 2
2 5 3 4 20

输出
4

说明
第一个方案，删除[3]。
第二个方案，删除[4]。
第三个方案，删除[3,4]。
第四个方案，删除[2]。
*/

#include <bits/stdc++.h>
using namespace std;

int calcFactor(int x, int y) {
    int res = 0;
    while (x % y == 0) {
        res++;
        x /= y;
    }
    return res;
}

int main() {
    int n, k;
    cin >> n >> k;
    int num[n];
    vector<pair<int, int>> factors(n);
    pair<int, int> allFactor {0, 0};
    long long res = 0;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
        factors[i] = {calcFactor(num[i], 2), calcFactor(num[i], 5)};
        allFactor.first += factors[i].first;
        allFactor.second += factors[i].second;
    }
    for (int i = 0, j = 0; j < n; j++) {
        allFactor.first -= factors[j].first;
        allFactor.second -= factors[j].second;
        while (i <= j && min(allFactor.first, allFactor.second) < k) {
            allFactor.first += factors[i].first;
            allFactor.second += factors[i].second;
            i++;
        }
        res += j-i+1;
    }
    cout << res << endl;
    return 0;
}

// 2, 5以及不定长滑动窗口