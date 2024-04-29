// https://mp.weixin.qq.com/s/ZlyHPNPztpV5wGN4u5n93A

/*
给定一个int数组nums，排列每个数的顺序（每个数不可拆分）使之组成一个最大的整数。

详细描述：给定一个int数组nums，排列每个数的顺序（每个数不可拆分，比如12不能拆成1和2）, 使之组成一个最大的整数。

注意：输出结果可能非常大，所以返回一个字符串而不是整数。

其他

时间限制: 1000ms

内存限制:256.0MB

输入输出示例

示例1

输入：[10,2]

输出："210"

示例2

输入：[10,9,8]

输出："9810"
*/

#include<bits/stdc++.h>
using namespace std;

bool cmp(string a, string b) {
    return a + b > b + a;
}

int main() {
    string input, item, res;
    getline(cin, input);
    input.erase(remove(input.begin(), input.end(), '['), input.end());
    input.erase(remove(input.begin(), input.end(), ']'), input.end());
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    vector<string> nums;
    stringstream ss(input);
    while (getline(ss, item, ',')) {
        nums.push_back(item);
    }
    sort(nums.begin(), nums.end(), cmp);
    if (nums[0] == "0") {
        cout << "0" << endl;
        return 0;
    }
    for (auto num : nums)
        res += num;
    cout << res << endl;
    return 0;
}