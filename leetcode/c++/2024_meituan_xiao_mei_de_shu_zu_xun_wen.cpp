/*
小美拿到了一个由正整数组成的数组，但其中有一些元素是未知的（用 0 来表示）。
现在小美想知道，如果那些未知的元素在区间[l,r]范围内随机取值的话，数组所有元素之和的最小值和最大值分别是多少？
共有q次询问。

输入描述

第一行输入两个正整数n,q，代表数组大小和询问次数。
第二行输入n个整数ai，其中如果输入ai的为 0，那么说明ai是未知的。
接下来的q行，每行输入两个正整数l,r，代表一次询问。
1<=n,q<=10^5
0<=ai<=10^9
1<=l<=r<=10^9

输出描述

输出q行，每行输出两个正整数，代表所有元素之和的最小值和最大值。

示例 1

输入
3 2
1 0 3
1 2
4 4

输出
5 6
8 8
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q, res = 0, count = 0;
    cin >> n >> q;
    int nums[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (nums[i] == 0)
            count++;
        res += nums[i];
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        int min_val = res + count * l;
        int max_val = res + count * r;
        cout << min_val << ' ' << max_val << endl;
        
    }
    return 0;
}