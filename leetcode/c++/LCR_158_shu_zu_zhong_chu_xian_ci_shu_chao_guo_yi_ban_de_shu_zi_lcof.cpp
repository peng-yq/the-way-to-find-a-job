// https://leetcode.cn/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof

#include <bits/stdc++.h>
using  namespace std;

class Solution {
public:
    int inventoryManagement(vector<int>& stock) {
      int vote = 0, x = 0;
      for (auto num : stock) {
        if (vote == 0) {
            x = num;
        }
        vote += num == x? 1 : -1;
      }
      return x;
    }
};

// 摩尔投票法，测试了一下排序然后取中间的数最快