#include <bits/stdc++.h>
using namespace std;

int main() {
    unordered_map<char, int> gpa = {{'A', 4}, {'B', 3}, {'C', 2}, {'D', 1}, {'F', 0}};
    string s;
    while (getline(cin, s)) {
        double sum = 0.0, len = 0;
        bool flag = false;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == ' ' || s[i] == '\t'){
                continue;
            }else if (gpa.count(s[i]) > 0) {
                sum += gpa[s[i]];
                len++;
            }else {
                flag = true;
                cout << "Unknown" << endl;
                break;
            }
        }
        if (!flag)
            printf("%.2f\n", sum / len);
    }
    return 0;
}

// 使用getline读取一整行字符串，记得处理空格和制表符（' '和'\t'）
// 对于格式化输出，c语言的printf会比c++使用fixed << setprecision(2) 更加方便