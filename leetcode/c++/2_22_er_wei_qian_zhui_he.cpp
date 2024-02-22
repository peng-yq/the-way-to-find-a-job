#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    int num[n+1][m+1], res[n+1][m+1];
    for (int i = 1; i < n+1; i++) {
        for (int j = 1; j < m+1; j++) {
            cin >> num[i][j];
            res[i][j] = res[i][j-1] + res[i-1][j] - res[i-1][j-1] + num[i][j];
        }
    }
    int x1, x2, y1, y2;
    while(q--) {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << res[x2][y2] - res[x2][y1-1] - res[x1-1][y2] + res[x1-1][y1-1] << endl;
    }
}