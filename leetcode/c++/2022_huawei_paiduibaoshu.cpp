// https://codefun2000.com/p/P1217

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int>array(n);
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }
    unordered_map<int, int>height;
    vector<int>res(n, 0);
    for (int i = n-1 ; i >= 0; i--) {
        height[array[i]]++;
        for (int j = 40; j < array[i]; j++)
            res[i] += height[j];
    }
    for (int i = 0; i < n; i++) {
        cout << res[i] << " ";
    }
    return 0;
}

// 时间复杂度为O(nm) 0<= m <= 40
// 空间复杂度为O(n)