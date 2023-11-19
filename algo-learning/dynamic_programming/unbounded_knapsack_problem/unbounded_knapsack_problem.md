[完全背包问题-Hello-Algo](https://www.hello-algo.com/chapter_dynamic_programming/unbounded_knapsack_problem/)

## 完全背包问题

给定n个物品，第i个物品的重量为wgt[i-1]、价值为val[i-1]，和一个容量为cap的背包。每个物品可以重复选取，问在不超过背包容量下能放入物品的最大价值。

**相比于0-1背包问题，完全背包问题多了一个物品可以重复选取的条件**。

回忆0-1背包问题，我们将状态[i,c]定义为前i个物品在背包剩余容量为c时的最大价值。

- 当不放入物品i时，dp[i,c]等于dp[i-1,c]
- 当放入物品i时，dp[i,c]等于dp[i-1,c-wgt[i-1]]

而完全背包问题中每个物品可以重复选取：

- 当不放入物品i时，dp[i,c]等于dp[i-1,c]
- 当放入物品i时，dp[i,c]等于dp[i,c-wgt[i-1]]

状态转移方程为：

dp[i,c] = max(dp[i-1,c], dp[i,c-wgt[i-1]])

