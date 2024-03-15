/*
游游拿到了一个数组，她每次操作可以任选一个元素加 1 或者减 1。游游想知道，将所有元素都变成和ai相等需要操作最少多少次？你需要回答i∈[1,n]的结果。

输入描述
第一行输入一个正整数n，代表数组的大小。第二行输入n个正整数ai，代表数组的元素。
1<=n<=10^5
1<=ai<=10^9

输出描述
输出n行，分别代表i∈[1,n]的结果。

示例 1

输入
3
2 1 4

输出
3
4
5
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long> nums(n+1, 0), sort_nums;
    vector<long long> presum(n+1, 0);
    for (int i = 1; i <= n; i++)
        cin >> nums[i];
    sort_nums = nums;
    sort(sort_nums.begin(), sort_nums.end());
    for (int i = 1; i <= n; i++) 
        presum[i] = presum[i-1] + sort_nums[i];
    for (int i = 1; i <= n; i++) {
        int index = lower_bound(sort_nums.begin(), sort_nums.end(), nums[i]) - sort_nums.begin();
        cout << index * nums[i] - presum[index] + presum[n] - presum[index] - (n-index) * nums[i] << endl;
    }
    return 0;
}

// 只有排序后才能使用前缀和这样计算，直接拿和减去需要变成的值a*个数是naive的想法