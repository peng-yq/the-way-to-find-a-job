#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        while (n--) {
            int m, sum = 0, num;
            cin >> m;
            while (m--) {
                cin >> num;
                sum += num;
            }
            cout << sum << endl;
            if (n != 0)
                cout << endl;
        }
    }
    return 0;
}