/*
MT 是美团的缩写，因此小美很喜欢这两个字母。现在小美拿到了一个仅由大写字母组成字符串，她可以最多操作k次，
每次可以修改任意一个字符。小美想知道，操作结束后最多共有多少个'M'和'T'字符？
输入描述
第一行输入两个正整数，代表字符串长度和操作次数。第二行输入一个长度为的、仅由大写字母组成的字符串。1<=k<=n<=10^5

输出描述
输出操作结束后最多共有多少个'M'和'T'字符。

示例 1

输入
5 2
MTUAN

输出
4
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, res = 0;
    string s;
    cin >> n >> k;
    cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] != 'M' && s[i] != 'T')
            res++;
    }
    res = (n-res) + min(res, k);
    cout << res << endl;
    return 0;
}