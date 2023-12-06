#include <bits/stdc++.h>
using namespace std;

int maxProductCutting(int n) {
    if (n <= 3) {
        return 1 * (n-1);
    }
    int a = n /3, b = n %3;
    if (b == 0) {
        return (int)pow(3, a);
    } else if (b == 1) {
        return (int)pow(3, a-1) * 2 * 2;
    } else {
        return (int)pow(3, a) * 2;
    }
}