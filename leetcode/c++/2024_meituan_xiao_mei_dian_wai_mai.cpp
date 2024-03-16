/*
小美是美团外卖的忠实用户，她经常去美团外卖 app 上面点外卖，因为会员红包的性价比太高啦！
现在小美点了若干道菜，她希望你计算一个订单的总价。你能帮帮她吗？

输入描述
第一行输入一个正整数，代表菜品总数。
第二行输入个正整数，代表每道菜的价格。
第三行输入两个正整数x和y，x代表满减的价格，y代表红包的价格。
1<=n<=10^5
1<=x,y,ai<=10^9
保证所有的和大于，保证会用到满减

输出描述
一个正整数，代表小美最终应付的钱数。

示例 1

输入
4
10 20 10 20
25 10

输出
25

说明
四个菜一共 60 元，满减减掉了 25 元，再用一个 10 元的红包，因此需要付 25 元。
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int prices[n];
    long long sum = 0;
    for (int i = 0; i <n; i++) {
        cin >> prices[i];
        sum += prices[i];
    }
    int x, y;
    cin >> x >> y;
    cout << sum - x - y << endl;
    return 0;
}