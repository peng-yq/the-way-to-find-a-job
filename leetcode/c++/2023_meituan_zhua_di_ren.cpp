#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    int num[1001][1001] = {0}, res[1001][1001] = {0};
    int max_num = 0;
    while (n--) {
        int x, y;
        cin >> x >> y;
        num[x][y] = 1;
    }
    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= 1000; j++) {
            res[i][j] = res[i][j-1] + res[i-1][j] - res[i-1][j-1] + num[i][j];
        }
    }
    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= 1000; j++) {
            int x2 = min(i + a, 1000);
            int y2 = min(j + b, 1000);                     
            int current = res[x2][y2] - res[i-1][y2] - res[x2][j-1] + res[i-1][j-1];
            max_num = max(max_num, current);
        }
    }
    cout << max_num << endl;
    return 0;
}


// 题单题解真垃圾，codefun2000真垃圾