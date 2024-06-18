// https://leetcode.cn/problems/apply-discount-to-prices

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string discountPrices(string sentence, int discount) {
        istringstream is(sentence);
        ostringstream os;
        string word;
        double d = (100 - discount) / 100.0;
        while (is >> word) {
            if (word[0] == '$' && word.size() > 1 && all_of(word.begin() + 1, word.end(), ::isdigit)) {
                double price = stod(word.substr(1));
                price *= d;
                os << fixed << setprecision(2) << "$" << price;
            } else {
                os << word;
            }
            if (is.peek() != EOF)
                os << " ";
        }
        return os.str();
    }
};

// 时间复杂度和空间复杂度都是O(n)，主要是输入输出流以及格式化输出