[完全背包问题-Hello-Algo](https://www.hello-algo.com/chapter_dynamic_programming/unbounded_knapsack_problem/)

## 完全背包问题

给定n个物品，第i个物品的重量为wgt[i-1]、价值为val[i-1]，和一个容量为cap的背包。每个物品可以重复选取，问在不超过背包容量下能放入物品的最大价值。

**相比于0-1背包问题，完全背包问题多了一个物品可以重复选取的条件**。

回忆0-1背包问题，我们将状态[i,c]定义为前i个物品在背包剩余容量为c时的最大价值。

- 当不放入物品i时，dp[i,c]等于dp[i-1,c]
- 当放入物品i时，dp[i,c]等于dp[i-1,c-wgt[i-1]] + val[i-1]

而完全背包问题中每个物品可以重复选取：

- 当不放入物品i时，dp[i,c]等于dp[i-1,c]
- 当放入物品i时，dp[i,c]等于dp[i,c-wgt[i-1]] + val[i-1]

状态转移方程为：

dp[i,c] = max(dp[i-1,c], dp[i,c-wgt[i-1]] + val[i-1])

**空间优化**

相比于0-1背包问题，此时每个状态基于左边的状态（因为每个物品可以重复选取）以及上方的状态，因此空间优化需要正向进行遍历。

## 零钱兑换问题

给定n种硬币，第i种硬币的面值为coins[i]，目标金额为amt，每种硬币可以重复选取，问能够凑出目标金额的最少硬币个数。如果无法凑出目标金额则返回-1。

零钱兑换问题是背包问题的变种，我们可以将硬币对应物品，硬币的面值对应物品的价值，目标金额对应背包的容量，求取不超过背包容量的最大价值变为了凑出目标金额的最少硬币个数。

**思考每轮的决策，定义状态，从而得到dp表**

类似的我们将dp[i,a]定义为前i个硬币能凑出金额a的最小硬币个数。

**找出最优子结构，进而推导出状态转移方程**

dp[i,a] = min(dp[i-1,a], dp[i,a-conis[i-1]] + 1)

**确定边界条件和状态转移顺序**

- a为0时，即目标金额为0，此时无论i为多少，都只需要0个硬币即可凑出目标金额

- i为0时，即没有硬币时，无法凑出任何金额大于0的目标，为无效解，使用amt+1来代替MAX_INT，从而避免+1时产生数组越界

**空间优化与完全背包问题一致**

## 零钱兑换问题Ⅱ

给定n种硬币，第i种硬币的面值为coins[i-1]，目标金额为amt，每种硬币可以重复选取，问在凑出目标金额的硬币组合数量。

此时题目求取凑出目标金额的最小硬币数，变成了凑出目标金额的硬币组合数量。这道题也可以用回溯去做，通过选择和回退以及剪枝，但我们不需要得到具体的组合，只需要得到组合数量。因此问题也就和最开始的求取上台阶的方案数量类似，组合数量等于选择硬币以及不选择硬币的组合数量之和。

将dp[i][a]定义为前i个硬币凑出目标金额为a的组合数目。

dp[i][a] = dp[i-1][a] + dp[i][a-conis[i-1]]

- 当只有0个硬币时，不能凑出任何金额大于0的目标，因此组合数初始化为0。
- 当目标金额为0时，任何个数的硬币的组合数均为1。

**空间优化与零钱兑换问题一致**