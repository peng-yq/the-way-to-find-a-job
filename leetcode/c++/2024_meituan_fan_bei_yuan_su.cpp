/*
小美拿到了一个数组，她每次操作会将除了第x个元素的其余元素翻倍，一共操作了q次。请你帮小美计算操作结束后所有元素之和。
由于答案过大，请对10^9+7取模。

输入描述
第一行输入两个正整数n,q，代表数组的大小和操作次数。
第二行输入n个正整数ai，代表数组的元素。
第三行输入一个正整数q，代表操作的次数。
接下来的q行，每行输入一个正整数xi，代表第i次操作未被翻倍的元素。
1<=n,q<=10^5
1<=xi<=n
1<=ai<=10^9

输出描述
一个整数，代表操作结束后所有元素之和模10^9+7的值。

示例

输入
4 2
1 2 3 4
1
2

输出
34

说明
第一次操作后，数组变成[1,4,6,8]
第二次操作后，数组变成[2,4,12,16]
所有元素之和为 34。
*/

#include <bits/stdc++.h>
using namespace std;

long long myPow(long long x, long long y, long long mod) {
    long long res = 1;
    while (y) {
        if ((y & 1) == 1) 
            res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

int main() {
    const long long mod = 1000000007;
    int n, q, index;
    cin >> n >> q;
    vector<int> nums(n);
    vector<int> times(n, q);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    for (int i = 0; i < q; i++) {
        cin >> index;
        times[index-1]--;
    }
    for (int i = 0; i < n; i++) {
        sum += (long long)nums[i] * myPow(2ll, (long long)times[i], mod);
        sum %= mod;
    }
    cout << sum << endl;
    return 0;
}

// 快速幂和int溢出
// 时间复杂度为O(n)，空间复杂度为O(1)