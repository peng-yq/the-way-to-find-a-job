#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int num[n + 1], res[m + 1];
    res[0] = 0;
    for (int i = 1; i < n + 1; i++) {
        cin >> num[i];
        res[i] = res[i-1] + num[i];
    }
    int l, r;
    while (m--) {
        cin >> l >> r;
        cout << res[r] - res[l-1] << endl;
    }
    return 0;
}

// 一维前缀和模板，预处理时间复杂度为O(n)，最后求各区间的前缀和时间复杂度为O(1)