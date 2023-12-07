// https://codefun2000.com/p/P1095

#include <bits/stdc++.h>
using namespace std;

bool change(string s, string t){
    int charS[3] = {0}, charT[3] = {0};
    string newS, newT;
    for (int i = 0; i < int(s.length()); i++) {
        if(s[i] == 'm')
            charS[0]++;
        else if (s[i] == 'h')
            charS[1]++;
        else if (s[i] == 'y')
            charS[2]++;
        else 
            newS.push_back(s[i]);
    }
    for (int i = 0; i < int(t.length()); i++) {
        if(t[i] == 'm')
            charT[0]++;
        else if (t[i] == 'h')
            charT[1]++;
        else if (t[i] == 'y')
            charT[2]++;
        else 
            newT.push_back(t[i]);
    }
    if (newS == newT) {
        if (charS[0] - charS[1] == charT[0] - charT[1] && 
        charS[0] - charS[2] == charT[0] - charT[2] &&
        charS[1] - charS[2] == charT[1] - charT[2]) 
            return true;
        return false;
    }
    return false;
}

int main(void) {
    int n;
    cin >> n;
    while(n--) {
        string s, t;
        cin >> s >> t;
        if (change(s, t))
            cout << "Yes" << endl;
        else 
            cout << "No" << endl;
    }
}

// 时间复杂度和空间复杂度均为O(n+m)