/*
题意
一组n个软件和k（k < (n*(n - 1)/2)）个依赖关系,若干组查询，查询两个软件的前者是否是后者的直接依赖或间接依赖。（对于[a,b]判断a是否是b的前驱节点）

输入描述
第一行输入两个正整数n和d ，代表软件的个数和依赖关系。后面d行输入相应的依赖关系。下一行输入一个正整数q，代表查询的组数。之后q行输入相应的查询。

输出描述
第一行输出q。之后q行每行输出一个正整数，如果是依赖关系，输出1，否则输出0。

示例1：
输入：
3 3
0 1
1 2
0 2
2
1 0
0 1

输出：
2
0
1
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, d, a, b, q;
    cin >> n >> d;
    vector<vector<int>> nums(n);
    vector<vector<bool>> check(n, vector<bool>(n, false));
    while (d--) {
        cin >> a >> b;
        nums[a].push_back(b);
        check[a][b] = true;
    }
    function<bool(int, int)> checkFun = [&](int a, int b) {
        if (check[a][b] == true)
            return true;
        for (auto num : nums[a]) {
            if (checkFun(num, b)) {
                check[a][b] = true;
                return true;
            }
        }
        return false;
    };
    cin >> q;
    vector<pair<int, int>> toCheck;
    for (int i = 0; i < q; ++i) {
        cin >> a >> b;
        toCheck.push_back({a, b});
    }
    cout << q << endl;
    for (auto p : toCheck) {
        cout << (checkFun(p.first, p.second)? 1 : 0) << endl;
    }
    return 0;
}