// https://leetcode.cn/problems/total-cost-to-hire-k-workers

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long totalCost(vector<int>& costs, int k, int candidates) {
        int n = costs.size();
        long long res = 0;
        if (candidates * 2 + k > n) {
            sort(costs.begin(), costs.end());
            for (int i = 0; i < k; ++i)
                res += costs[i];
            return res;
        } 
        priority_queue<int, vector<int>, greater<int>> left, right;
        int i = 0, j = n - 1;
        for (; i < candidates; ++i, --j) {
            left.push(costs[i]);
            right.push(costs[j]);
        }
        while (k--) {
            if (left.top() <= right.top()) {
                res += left.top();
                left.pop();
                left.push(costs[i++]);
            } else {
                res += right.top();
                right.pop();
                right.push(costs[j--]);
            }
        }
        return res;
    }
};

// 太菜了呜呜呜呜呜呜呜呜！今天的每日一题做了好久一直有问题，还得是灵神啊
// candidates * 2 + k > n说明k次选择肯定会覆盖整个数组，也就是肯定会选到数组中前k小的数，直接排序然后相加即可
// 如果<= n则说明k次选择不会覆盖整个数组，也就是前后两个堆不会重合，这样就减少了很多判断
// 使用前后两个最小堆（这里只考虑堆与堆之间的下标，堆内的下标不用考虑，因为数值一样，不影响结果）
// 使用两个指针记录前后两个堆推入元素的下标
// 在迭代过程中也不用考虑两个堆是否为空的情况，因为不可能出现两个堆为空的情况，只需比较两个堆的大小即可
// 如果从某个堆中取出了一个数，则再从上次结束的位置后面推入堆中
// 时间复杂度为O((c+k)log(c+k))，进行c+k次堆调整操作；空间复杂度为O(c)
