[动态规划——Hello-Algo](https://www.hello-algo.com/chapter_dynamic_programming/intro_to_dynamic_programming/)

## 动态规划

动态规划通过将一个问题分解为一个个的小问题，再通过小问题的解得到大问题的解（不同于分治，分治中的小问题都是可以单独解决的，动态规划的小问题的解往往又依赖于更小问题的解，不能独立解决）。相比于普通的递归暴力解法，动态规划通过dp数组存储小问题的解，避免重复计算，从而提升时间效率。

**给定一个共有n阶的楼梯，你每步可以上1阶或者2阶，请问有多少种方案可以爬到楼顶。**

### 回溯

首先我们通过回溯算法的思维通过暴力来搜索所有可以爬到楼顶的方案，state为已经爬了的阶数（由于只需要解出有多少种方案，这里可以不记录具体的过程）；choices为1或2，也就是一次可以上1阶或2阶；res为爬到楼顶的方案数目。

```c++
/* 回溯 */
void backtrack(vector<int> &choices, int state, int n, int &res) {
    // 当爬到第 n 阶时，方案数量加 1
    if (state == n)
        res++;
    // 遍历所有选择
    for (auto &choice : choices) {
        // 剪枝：不允许越过第 n 阶
        if (state + choice > n)
            break;
        // 尝试：做出选择，更新状态
        backtrack(choices, state + choice, n, res);
        // 回退
    }
}

/* 爬楼梯：回溯 */
int climbingStairsBacktrack(int n) {
    vector<int> choices = {1, 2}; // 可选择向上爬 1 或 2 阶
    int state = 0;                // 从第 0 阶开始爬
    int res = 0;                  // 使用res记录方案数量
    backtrack(choices, state, n, res);
    return res;
}
```

### 暴力搜索

但这个问题我们可以将问题进行分解，因为每次只能上1阶或2阶，也就是说要爬到第i阶只能从第i-1阶或第i-2阶爬，进一步得到爬到第i阶的方案数等于爬到第i-1阶的方案数+爬到第i-2阶的方案数。假设dp[i]表示爬到第i阶的方案数：

$
    dp[i] = dp[i-1] + dp[i-2];
    dp[1] = dp[2] = 1
$

本质上通过将问题进行分解用递归的方式写出来，相比于回溯，少了尝试中剪枝的过程，因为每一个解都是有确定解法的。

```c++
/* 搜索 */
int dfs(int i) {
    // 已知 dp[1] 和 dp[2] ，返回之
    if (i == 1 || i == 2)
        return i;
    // dp[i] = dp[i-1] + dp[i-2]
    int count = dfs(i - 1) + dfs(i - 2);
    return count;
}

/* 爬楼梯：搜索 */
int climbingStairsDFS(int n) {
    return dfs(n);
}
```

但这种方式会造成一个问题，也是递归的问题，递归树的深度为n,时间复杂度为$O(2^n)$。

<img src="https://www.hello-algo.com/chapter_dynamic_programming/intro_to_dynamic_programming.assets/climbing_stairs_dfs_tree.png">

## 记忆化搜索

由于递归进行暴力搜索出现了很多的重复子问题被再次递归进行计算，从而造成时间爆炸。因此可以通过一个大小为n（n+1也可以，这样索引为0的元素就不用了）数组进行存储问题的解，需要再次使用时直接取出，而不用再次进行递归计算。

```c++
/* 记忆化搜索 */
int dfs(int i, vector<int> &mem) {
    // 已知 dp[1] 和 dp[2] ，返回之
    if (i == 1 || i == 2)
        return i;
    // 若存在记录 dp[i] ，则直接返回之
    if (mem[i] != -1)
        return mem[i];
    // dp[i] = dp[i-1] + dp[i-2]
    int count = dfs(i - 1, mem) + dfs(i - 2, mem);
    // 记录 dp[i]
    mem[i] = count;
    return count;
}

/* 爬楼梯：记忆化搜索 */
int climbingStairsDFSMem(int n) {
    // mem[i] 记录爬到第 i 阶的方案总数，-1 代表无记录
    vector<int> mem(n + 1, -1);
    return dfs(n, mem);
}
```

这样时间复杂度被优化为$O(n)$

<img src="https://www.hello-algo.com/chapter_dynamic_programming/intro_to_dynamic_programming.assets/climbing_stairs_dfs_memo_tree.png">

### 动态规划

但上述问题依旧还是通过递归从顶至底去解决问题，而递归涉及到函数栈的增长，极端情况会导致栈溢出。

而动态规划则是从底至顶去解决问题，先得到小问题的解然后一步步得到大问题的解（虽然一开始思维是从大问题去分解，但是代码是这样写的），这样就不用去使用递归。

```c++
/* 爬楼梯：动态规划 */
int climbingStairsDP(int n) {
    if (n == 1 || n == 2)
        return n;
    // 初始化 dp 表，用于存储子问题的解
    vector<int> dp(n + 1);
    // 初始状态：预设最小子问题的解
    dp[1] = 1;
    dp[2] = 2;
    // 状态转移：从较小子问题逐步求解较大子问题
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}
```

时间复杂度为$O(n)$，空间复杂度也为$O(n)$；从时间和空间复杂度的角度来看，两者的性能是相当的。然而，值得注意的是，记忆化搜索通常会涉及函数调用的递归，而递归调用可能会导致函数调用栈的增长，可能在极端情况下导致栈溢出。

**空间优化**

将数组改为变量，从而将空间复杂度变为$O(1)$

```c++
/* 爬楼梯：空间优化后的动态规划 */
int climbingStairsDPComp(int n) {
    if (n == 1 || n == 2)
        return n;
    int a = 1, b = 2;
    for (int i = 3; i <= n; i++) {
        int tmp = b;
        b = a + b;
        a = tmp;
    }
    return b;
}
```
