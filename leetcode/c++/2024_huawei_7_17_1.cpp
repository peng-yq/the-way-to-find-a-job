/*
题意
对于一个文件系统，第一行输入所有的父目录名称，第二行输入所有的子目录/文件名称，第三行输入待查询的文件或目录名称。对于查询的目录或文件名，如果存在子目录或文件，需要按输入的顺序，按层级输出所有的子目录和文件。“/”表示根目录，没有父目录。

输入描述
第一行是一个由所有的父目录名称组成的字符串，按空格分开。第二行是对应父目录的所有子目录或文件名组成的字符串，按空格分开。第三行是查询的文件名或目录名。

输出描述
按输入的顺序逐层输出所有的子目录和文件，包括查询的目录/文件本身

示例1：
输入：
/ / / home usr 
home opt env usr 1.log
home

输出：
home usr 1.log
查询的home目录包含usr子目录，usr下有一个1.log文件，按顺序输出。

示例2：
输入：
/ / / home usr 
home opt env usr 1.log
env

输出：
env
env没有下挂的文件或子目录，直接输出查询本身。
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, tmp;
    getline(cin, s);
    vector<string> father;
    unordered_map<string, vector<string>> children;
    istringstream is(s);
    while (is >> tmp)
        father.push_back(tmp);
    for (int i = 0; i < father.size(); ++i) {
        cin >> tmp;
        children[father[i]].push_back(tmp);
    }
    cin >> tmp;
    queue<string> q;
    q.push(tmp);
    while (!q.empty()) {
        cout << q.front() << " ";
        if (children.count(q.front())) {
            for (auto s : children[q.front()])
                q.push(s);
        }
        q.pop();
    }
    return 0;
}