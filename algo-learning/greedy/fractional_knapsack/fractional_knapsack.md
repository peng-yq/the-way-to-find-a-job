[分数背包问题-Hello-Algo](https://www.hello-algo.com/chapter_greedy/fractional_knapsack_problem/)

给定n个物品，第i个物品的重量为wgt[i-1]、价值为val[i-1]，和一个容量为cap的背包。每个物品只能选择一次，但可以选择物品的一部分，价值根据选择的重量比例计算，问在限定背包容量下背包中物品的最大价值。

<img src="https://www.hello-algo.com/chapter_greedy/fractional_knapsack_problem.assets/fractional_knapsack_example.png">

这个问题就十分适合贪心算法，相较于0-1背包问题，我们不用考虑物品能否放得下的限制，每次选择都选单位价值最大的物品，并尽可能的放入该物品，也就是说如果背包剩余容量大于该物品的重量，则全部放入，否则尽可能的放入（分数）。

时间复杂度最差为遍历所有的物品为O(n)，空间复杂度为O(n)，n为物品的数量。