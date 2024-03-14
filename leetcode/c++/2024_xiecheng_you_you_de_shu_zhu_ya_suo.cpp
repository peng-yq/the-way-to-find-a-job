/*
游游拿到了一个数组，她希望你将数组相同的相邻元素压缩在一起。你能帮帮她吗？
给定的数组是已经被压缩了一部分的形式，请你继续将其压缩到不能再压缩为止。举个例子，数组[2,3,5,5,5,3]会被压缩成[2(1),3(1),5(3),3(1)]。

输入描述
一个字符串，代表待压缩的数组。字符串长度不超过10^5，且括号内的一定是不超过10^9的正整数。数组中每个元素的值域范围是[-10^9,10^9]

输出描述
一个字符串，表示压缩后的数组。

示例 1

输入
[1(2),1(1),-1(3)]

输出
[1(3),-1(3)]

说明
该字符串表示的数组是[1,1,1,-1,-1,-1]

示例 2

输入
[1(1),2(2),3(31),3(42),2(12)]

输出
[1(1),2(2),3(73),2(12)]
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    string str, res;
    cin >> str;
    str = str.substr(1, str.length() - 2);
    res = "[";

    string pre = "";
    long long count = 0;

    for (int i = 0; i < str.length(); i++) {
        int start = i;
        while (i < str.length() && str[i] != '(') i++;
        string now = str.substr(start, i - start);

        int numStart = ++i;
        while (i < str.length() && str[i] != ')') i++;
        string num = str.substr(numStart, i - numStart);

        if (now == pre) {
            count += stoll(num);
        } else {
            if (!pre.empty()) {
                res += pre + "(" + to_string(count) + "),";
            }
            pre = now;
            count = stoll(num);
        }

        ++i;
    }

    if (!pre.empty()) {
        res += pre + "(" + to_string(count) + ")";
    }

    res += "]";
    cout << res << endl;
    return 0;
}

// 时间复杂度为O(n)，空间复杂度为O(n)，很麻烦的一道题