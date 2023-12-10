// https://codefun2000.com/p/P1103

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;

int main(void) {
    int n , k;
    cin >> n >> k;
    int s[n];
    for(int i = 0; i < n; i++)
        cin >> s[i];
    int res = 1e9;
    for (int i = 0; i <= 9; i++) {
        for (int l =0, r = 0, tmp = 0; r < n; r++) {
            tmp += abs(s[r] - i);
            if (r >= l + k) 
                tmp -= abs(s[l++] - i);
            if (r == (l + k - 1))
                res = min(res, tmp);
        }
    }
    cout << res;
    return 0;
}

// 时间复杂度为O(n) ， 空间复杂度为O(1)
