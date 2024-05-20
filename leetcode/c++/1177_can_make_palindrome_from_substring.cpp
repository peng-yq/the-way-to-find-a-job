// https://leetcode.cn/problems/can-make-palindrome-from-substring

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        int m = s.size(), n = queries.size();
        vector<bool> res(n, false);
        vector<vector<int>> presum(m + 1, vector<int>(26, 0));
        for (int i = 1; i <= m; ++i) {
            presum[i] = presum[i-1];
            ++presum[i][s[i - 1] - 'a'];
        }
        for (int i = 0; i < n; ++i) {
            int left = queries[i][0], right = queries[i][1] + 1, k = queries[i][2], sum = 0;
            for (int j = 0; j < 26; ++j) {
                if ((presum[right][j] - presum[left][j]) % 2 != 0)
                    ++sum;
            }
            if ((sum / 2) <= k)
                res[i] = true;
        }
        return res;
    }
};

// 判断一个字符串是否是回文字符串：双指针从头和尾开始遍历字符直到相遇，如果遇到不相同的则不是回文字符串
// 但是如果字符串可以排列位置呢？那就得看字符串中奇数字符的个数，如果奇数字符的个数为n，那么我们需要进行n / 2次替换
// 如果n是奇数，比如3，需要替换3 / 2为1次，任意替换一个奇数字符为另外一个，再把剩余的一个放在正中间
// 如果n是偶数呢，比如4，需要替换4 / 2为2次，需要替换2个字符为另外2个
// 如果我们每个字符串都去遍历字符串进行判断肯定会超时，而且做了很多多余的操作
// 因此使用前缀和，presum[i][j]表示s[0]到s[i-1]组成的字符串中字母表第j个字母的个数
// 此外因为我们只需要确认某个元素的个数是奇数还是偶数，可以直接使用异或，0为偶数，1为奇数，0 ^ 1 = 1, 0 ^ 0 = 0， 1 ^ 1 = 0
// 时间复杂度为O((m + n) * 26)，空间复杂度为O(m * 26)

class Solution {
public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        int m = s.size(), n = queries.size();
        vector<bool> res(n, false);
        vector<vector<int>> presum(m + 1, vector<int>(26, 0));
        for (int i = 1; i <= m; ++i) {
            presum[i] = presum[i-1];
            presum[i][s[i - 1] - 'a'] ^= 1; // 奇数+1为偶数，偶数加1为奇数
        }
        for (int i = 0; i < n; ++i) {
            int left = queries[i][0], right = queries[i][1] + 1, k = queries[i][2], sum = 0;
            for (int j = 0; j < 26; ++j) {
                sum += presum[right][j] ^ presum[left][j]; // 奇数加奇数等于偶数，奇数加偶数等于奇数，偶数加偶数等于偶数
            }
            res[i] = sum / 2 <= k;
        }
        return res;
    }
};

// 下面是一种更吊的方法，直接用26位位掩码来存储s[0]到s[i]中每个字符的奇偶性
// 时间复杂度位O(n + m)，空间复杂度为O(n)

class Solution {
public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>> &queries) {
        int n = s.length(), q = queries.size(), sum[n + 1];
        sum[0] = 0;
        for (int i = 0; i < n; i++) {
            int bit = 1 << (s[i] - 'a');
            sum[i + 1] = sum[i] ^ bit; // 该比特对应字母的奇偶性：奇数变偶数，偶数变奇数
        }

        vector<bool> ans(q); // 预分配空间
        for (int i = 0; i < q; i++) {
            auto &query = queries[i];
            int left = query[0], right = query[1], k = query[2];
            int m = __builtin_popcount(sum[right + 1] ^ sum[left]);
            ans[i] = m / 2 <= k;
        }
        return ans;
    }
};