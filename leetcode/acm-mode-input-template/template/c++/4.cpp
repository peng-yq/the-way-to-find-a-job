#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin >> n && n != 0) {
        int sum = 0, a;
        while (n--) {
            cin >> a;
            sum += a;
        }
        cout << sum << endl;
    }
    return 0;
}