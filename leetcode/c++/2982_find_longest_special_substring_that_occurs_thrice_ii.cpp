// https://leetcode.cn/problems/find-longest-special-substring-that-occurs-thrice-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumLength(string s) {
        int n = s.length(), tmp = 0, res = 0;
        char pre = s[0];
        vector<vector<int>> counts(26);
        for (int i = 0; i < n; ++i) {
            char ch = s[i];
            if (ch == pre)
                ++tmp;
            else if (ch != pre) {
                counts[pre - 'a'].push_back(tmp);
                tmp = 1;
                pre = ch;
            }
            if (i == n -1)
                counts[ch - 'a'].push_back(tmp);
        }
        for (auto group : counts) {
            if (!group.empty()) {
                sort(group.begin(), group.end(), greater<int>());
                group.push_back(0);
                group.push_back(0);
                int choose1 = group[0] - 2, choose2 = min(group[0] - 1, group[1]), choose3 = group[2];
                res = max(res, max(max(choose1, choose2), choose3));
            }
        }
        return res == 0? -1:res;
    }
};

// 时间复杂度为O(nlogn)，使用大小为3的堆时间复杂度可达到O(n)（堆操作为3log3），空间O(n)
// 需要记录每个字母的每个特殊字符的长度，比如用数组s，再按从大到小排序
// 分为以下3种情况：
// 1. 最长的特殊字符里面选3个，也就是s[0] - 2
// 2. 从最长和次长的里面选3个，也就是min(s[0] - 1， s[1])；分别表示s[0]和s[1]相等时，取出3个s[0]-1长度的字符；s[0]和s[1]不等时，s[0]选出2个s[1]，s[1]出一个
// 3. 从最长、次长和第三长选三个，也就是s[2]
// 3者取最大即可，再从所有字符中选出最大的