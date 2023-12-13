// https://codefun2000.com/p/P1001

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    int nums[n];
    for (int i = 0; i < n; i++) 
        cin >> nums[i];
    unordered_map<int, int>count;
    long long res = 0;
    for (int l = 0, r = 0; r < n; r++) {
        count[nums[r]]++;
        while (nums[r] >= x) {
            res += n -r;
            count[nums[l++]--];
        }
    }
    cout << res;
    return 0;
}

// 时间复杂度和空间复杂度为O(n)