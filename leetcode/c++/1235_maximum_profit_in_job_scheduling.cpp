// https://leetcode.cn/problems/maximum-profit-in-job-scheduling

#include <bits/stdc++.h>
using namespace std;

struct Job {
    int startTime_;
    int endTime_;
    int profit_;
};

bool cmp (const Job& a, const Job& b) {
    return a.endTime_ < b.endTime_;
}

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<Job> jobs;
        vector<int> dp(n);
        for (int i = 0; i < n; ++i) {
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end(), cmp);
        dp[0] = jobs[0].profit_;
        for (int i = 1; i < n; ++i) {
            int left = 0, right = i - 1, target = -1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (jobs[mid].endTime_ <= jobs[i].startTime_) {
                    target = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            if (target == -1) {
                dp[i] = max(dp[i-1], jobs[i].profit_);
            } else {
                dp[i] = max(dp[i-1], dp[target] + jobs[i].profit_);
            }
        }
        return dp[n-1];
    }
};

// 动态规划+二分查找
// 首先我们按照工作的结束时间从小到大进行排序，因为我们判断工作是否冲突是根据当前工作的开始时间和前面工作的结束时间进行比较
// 定义动态规划数组dp[n]，其中dp[i]表示索引为0~i的工作所能获得的最大工资
// 动态初始化比较简单，dp[0]就等于最早结束的工作的工资
// 下面是动态转移方程dp[i]的求解，我们需要搜索索引0~i-1的工作中不和第i个工作冲突的最晚结束时间的工作索引target
// 很好理解，前面不冲突的肯定是可以和当前工作一起兼职的，而后面发生冲突的工作则需要进行取舍，如果不做当前工作所获得最大工资也就是dp[i-1]
// 如果做当前工作，所获得最大工资则为dp[target] + 当前工作的工资
// 此外还有一种情况，前面所有的工作都和当前工作冲突了，那就只有比较dp[i-1]和当前工作的工资了
// 因为我们已经按照工作的结束时间进行排序了，求取target的过程可以使用二分查找，其中所有工作都与当前工作冲突的情况求取得到的target为-1
// 时间复杂度为O(nlogn)，空间复杂度为O(n)