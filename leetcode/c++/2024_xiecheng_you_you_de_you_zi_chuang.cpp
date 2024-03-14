/*
游游拿到了一个字符串，她想重排这个字符串后，使得该字符串包含尽可能多的"you"连续子串。你能帮帮她吗？

输入描述
一个仅包含小写字母的字符串，长度不超过10^5

输出描述
重排后的字符串。有多解时输出任意即可。

示例 1

输入
yyoouuuu

输出
uyouyouu
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    string str, res;
    unordered_map<char, int> m;
    cin >> str;
    for (char ch : str) {
        m[ch]++;
    }
    int count = min(min(m['y'], m['o']), m['u']);
    m['y'] -= count;
    m['o'] -= count;
    m['u'] -= count;
    while (count--)
        res += "you";
    for (auto it : m) {
        while (it.second--)
            res += it.first; 
    }
    cout << res << endl;
    return 0;
}

// O(n), O(n)