// https://leetcode.cn/problems/restore-ip-addresses

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<string> res;
    void dfs(string& s, string tmp, int start, int count) {
        if (count == 4 && start == s.length()) {
            res.push_back(tmp.substr(0, tmp.length() - 1));
            return;
        }
        if (count >= 4) {
            return;
        }
        for (int i = 1; i <= 3 && start + i <= s.length(); ++i) {
            string part = s.substr(start, i);
            if (stoi(part) > 255 || (part[0] == '0' && i > 1)) {
                continue;
            }
            dfs(s, tmp + part + ".", start + i, count + 1);
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        if (s.length() < 4 || s.length() > 12)
            return res;
        string tmp;
        dfs(s, tmp, 0, 0);
        return res;
    }
};

// 找所有可能一般解法是回溯，由于1 <= s.length <= 20，因此字符串s是可能出现完全不可能的IP地址的（长度<4或者>12）
// 回溯的大概解法，首先确认终止递归的条件，由于IP地址需要4个整数，因此用一个count记录当前已经添加的整数个数
// 注意仅有count=4还不能终止，还需要字符串已经判断完，因此递归终止条件为count == 4 && start == s.length()
// 如果字符串还没判断完，此时提前终止后续判断
// 接下来就是判断当前子串是否符合条件，只有当part范围为0-255，并且不能有前导0才能满足条件
// part最多位数为3位，因此用一个for循环依次判断从start开始的长度为1-3的子串是否满足条件
// 前导0很好判断，即part[0] == '0' && i > 1
// 还有一个小trick，由于tmp的长度为1-3，因此我们直接用传值代替引用，在回溯时通过tmp + part + "."来替代return后的现场恢复
// start和count同理
// 时间复杂度为O(3^4)，没考虑字符串赋值消耗的时间
// 空间复杂度为O(4)，最多进行4次递归调用
// PS：时空复杂度的计算有点复杂，可能是错误