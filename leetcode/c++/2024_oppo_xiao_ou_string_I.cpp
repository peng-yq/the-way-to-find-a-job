/*
题目描述
小欧拿到了一个字符串，她想知道，有多少个长度为k的连续子串满足：所有字母出现次数为偶数次？

输入描述
第一行输入两个正整数n和k，代表字符串长度和选择的子串长度

第二行输入一个长度为n的 ，仅由小写字母组成的字符串， 

输出描述
一个整数，代表满足条件的子串数量。

示例1
输入
5 2
aabbc
输出
2
*/

#include <bits/stdc++.h>
using namespace std;

bool check(unordered_map<char, int> map, string str, int i, int j) {
    for (; i <= j; i++) {
        if (map[str[i]] & 1 == 1)
            return false;
    }
    return true;
}

int main() {
    int n, k;
    cin >> n >> k;
    string str;
    cin >> str;
    int res = 0;
    unordered_map<char, int> map;
    for (int i = 0, j = 0; j < n; j++) {
        map[str[j]]++;
        if (j - i + 1 > k) {
            if (--map[str[i]] == 0)
                map.erase(str[i]);
            i++;
        }
        if (j - i + 1 == k) {
            if (check(map, str, i, j))
                res++;
        }
    } 
    cout << res << endl;
    return 0;
}

// 上述解法时间复杂度为O(nk),空间复杂度为O(n)

int main() {
    int n, k;
    cin >> n >> k;
    string str;
    cin >> str;
    int res = 0, count = 0;
    unordered_map<char, int> map;
    for (int i = 0, j = 0; j < n; j++) {
        if (++map[str[j]] & 1 == 1)
            count++;
        else 
            count--;
        if (j - i + 1 > k) {
            if (--map[str[i]] & 1 == 1) 
                count++;
            else 
                count--;
            i++;
        }
        if (j - i + 1 == k && count == 0) 
            res++;
    } 
    cout << res << endl;
    return 0;
}

// 维护一个奇数变量来记录当前子串中字符出现次数为奇数的个数，时间复杂度为O(n)，空间复杂度为O(1)