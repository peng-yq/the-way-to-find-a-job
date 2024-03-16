/*
小美定义以下三种单词是合法的：
所有字母都是小写。例如：good
所有字母都是大写。例如：APP
第一个字母大写，后面所有字母都是小写。例如：Alice
现在小美拿到了一个单词，她每次操作可以修改任意一个字符的大小写。小美想知道最少操作几次可以使得单词变成合法的？

输入描述
一个仅由大写字母和小写字母组成的字符串，长度不超过10^5。

输出描述
一个整数，代表操作的最小次数。

示例 1

输入
AbC

输出
1

说明
变成 ABC 或者 Abc 均可。只需要一次操作。
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    string str;
    cin >> str;
    bool flag = false;
    int upper_num = 0, lower_num = 0, n = str.length();
    for (int i = 0; i< n; i++) {
        if (isupper(str[i]) && i == 0) {
            upper_num++;
            flag = true;
        } else if (isupper(str[i])) {
            upper_num++;
        } else {
            lower_num++;
        }
    }
    int x, y, z;
    y = lower_num;
    z = upper_num;
    if (flag) 
        x = upper_num-1;
    else 
        x = upper_num+1;
    cout << min(min(x, y), z) << endl;
    return 0;
}