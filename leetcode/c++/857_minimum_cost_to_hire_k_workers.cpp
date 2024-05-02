// https://leetcode.cn/problems/minimum-cost-to-hire-k-workers

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        vector<pair<double, int>> nums;
        for (int i = 0; i < n; ++i) {
            nums.push_back({double(wage[i]) / quality[i], quality[i]});
        }
        auto cmp = [](const pair<double, int>& a, const pair<double, int>& b) {
            return a.first < b.first;
        };
        sort(nums.begin(), nums.end(), cmp);
        priority_queue<int, vector<int>, less<int>> pq;
        double res = 0;
        int sum = 0;
        for (int i = 0; i < k; ++i) {
            pq.push(nums[i].second);
            sum += nums[i].second;
        }
        res = nums[k-1].first * sum;
        for (int i = k; i < n; ++i) {
            if (nums[i].second < pq.top()) {
                sum -= pq.top() - nums[i].second;
                pq.pop();
                pq.push(nums[i].second);
                double tmp = nums[i].first * sum;
                res = min(res, tmp);
            }
        }
        return res;
    }
};

// 太菜菜菜菜菜了！
// 根据下面2个规则：
// 对工资组中的每名工人，应当按其工作质量与同组其他工人的工作质量的比例来支付工资。
// 工资组中的每名工人至少应当得到他们的最低期望工资。
// 可以总结出选中的k个工人的总成本 = 单位工作质量成本最大的工人 * 工作量的总和
// 解释：工作量的总和是固定的，为了满足规则1，应该选择k个工人中的某个工人的单位工作质量成本为基准
// 而为了满足规则2，应该选择k个工人中单位工作质量成本最大的那一位，这样剩余k-1个工人的工资才不会低于其最低期望的工资
// 因此我们对n个工人按照其单位工作质量成本从小到大排序，确保k-n索引的工人能直接加入到k个中，并以其单位工作质量成本为基准
// 那么在遍历n个工人的过程中如何更新k个工人呢？维护一个大小为k的最大堆，
// 如果第i个工人的工作量大于堆顶工人的工作量，就将其入堆并替换掉堆顶的工人，这样虽然基准值变大了，但是工作量总和变少了，有可能得到更小的值
// （有点像盛最多水的容器）
// 时间复杂度为O(nlogn)，空间复杂度为O(n)