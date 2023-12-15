// https://codefun2000.com/p/P1114

#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int sheep[n];
    for (int i = 0; i < n; i++) 
        cin >> sheep[i];
    sort(sheep, sheep+n);
    int res = INT_MAX;
    for (int l = 0, r = 0; r < n; r++) {
        while (sheep[r] - sheep[l] + 1 > n) 
            l++;
        res = min(res, n-(r-l+1));
    }
    cout << res;
}

// 时间复杂度取决于sort的时间复杂度为O(n*logn)