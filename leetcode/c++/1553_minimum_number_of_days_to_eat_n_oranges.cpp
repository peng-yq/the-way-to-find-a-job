// https://leetcode.cn/problems/minimum-number-of-days-to-eat-n-oranges

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDays(int n) {
        int dp[n + 1];
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1] + 1;
            if (i % 2 == 0)
                dp[i] = min(dp[i], dp[i / 2] + 1);
            if (i % 3 == 0)
                dp[i] = min(dp[i], dp[i/ 3] + 1);
        }
        return dp[n];
    }
};

// 首先肯定是尽可能的去整除而非减一，这样才能得到最少天数
// 因此一开始的想法是每一次尽可能的多次橘子，也就是只要能被2整除就吃n/2的橘子，只要能被3整除就吃2n/3的橘子
// 能同时被整除就吃这两者中最多的橘子，否则吃一个橘子。这种方式是比较naive的，因为只能保证局部最优，而非全局最优
// 比如当n = 10，上述方式分别是吃5, 1, 2, 1, 1；而正确的方法是1, 6, 2, 1，

// 然后是使用动态规划的方法，每次最多选择3种方式，根据条件依次去比较即可，dp[i-1]表示这次吃一个，
// dp[i/2]表示剩余为2的倍数，dp[i/3]表示剩余为3的倍数，但是n很大时，时间和内存都过不了
// 下面是使用记忆化搜索的办法，尽可能的去整除而非减一
class Solution {
public:
    unordered_map<int, int> cache;
    int minDays(int n) {
        if (n < 2)
            return n;
        if (cache.count(n))
            return cache[n];
        cache[n] = min(minDays(n / 2) + n % 2, minDays(n / 3) + n % 3) + 1;
        return cache[n];
    }
};
// minDays(n / 2) + n % 2表示去构造能被2整除的剩余橘子的最小天数，
// minDays(n / 3) + n % 3表示去构造能被3整除的剩余橘子的最小天数，
// n % 2和n % 3都是每天吃一个，然后minDays(n / 2)和minDays(n / 3)也需要花费1天去吃

