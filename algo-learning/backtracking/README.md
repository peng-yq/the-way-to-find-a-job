[回溯算法——Hello-Algo](https://www.hello-algo.com/chapter_backtracking/backtracking_algorithm/)

## 回溯算法

回溯算法是一种暴力穷举算法，从一个初始状态出发，暴力穷举所有可能的解，遇到正确的解则进行记录，直到找到所有解或者穷举完所有可能都无法找到解为止。

## 尝试与回退

回溯算法的关键在于“尝试”和“回退”，回溯算法在搜索所有可能解的过程中，当遇到某个状态无法前进时或无法得到满足解的条件时，它会撤销上一步操作，回退到之前的状态，并尝试其他可能的选择。

例如：在二叉树中搜索所有值为7的节点，请返回根节点到这些节点的路径。

```c++
void preOrder(TreeNode *root) {
    if(root == nullptr)
        return;
    path.push_back(root);
    if (root.val == 7)
        res.push_back(path);
    preOrder(root->left);
    preOrder(root->right);
    path.pop_back();
}

```

在每次“尝试”中将节点添加进path进行路径记录，在“回退”前将节点从path弹出，恢复“尝试”前的状态，并在符合条件时将path添加到res记录根节点到满足条件节点的路径。

<img src="https://www.hello-algo.com/chapter_backtracking/backtracking_algorithm.assets/preorder_find_paths_step10.png">

## 剪枝

复杂的回溯算法通常包含一个或多个约束条件，约束条件通常用于“剪枝”。

例如：在二叉树中搜索所有值为7的节点，请返回根节点到这些节点的路径，并要求路径中不包含值为3的节点。

要求不包含值为3的节点便是约束条件，需要进行剪枝，也就是经过这个节点的解都不符合条件，就不用向下穷举了，从而提高搜索效率。

```c++
void preOrder(TreeNode *root) {
    if(root == nullptr || root->val == 3)
        return;
    path.push_back(root);
    if(root->val == 7)
        res.push_back(path);
    preOrder(root->left);
    preOrder(root->right);
    path.pop_back();
}
```

<img src="https://www.hello-algo.com/chapter_backtracking/backtracking_algorithm.assets/preorder_find_constrained_paths.png">

## 框架代码

```c++
/* 回溯算法框架 */
void backtrack(State *state, vector<Choice *> &choices, vector<State *> &res) {
    // 判断是否为解
    if (isSolution(state)) {
        // 记录解
        recordSolution(state, res);
        // 停止继续搜索
        return;
    }
    // 遍历所有选择
    for (Choice choice : choices) {
        // 剪枝：判断选择是否合法
        if (isValid(state, choice)) {
            // 尝试：做出选择，更新状态
            makeChoice(state, choice);
            backtrack(state, choices, res);
            // 回退：撤销选择，恢复到之前的状态
            undoChoice(state, choice);
        }
    }
}
```

## 算法特性

回溯算法的本质是DFS（深度优先遍历算法），通过穷举所有解来解决问题，优势在于可以找到所有可能的解决方案，并且在合理的剪枝操作下，回溯算法具有很高的效率。

处理大规模问题时，回溯算法的运行效率较低下：

- 时间，因为本质是穷举所有解，时间复杂度可能会很高
- 空间，递归以及保存辅助变量

**回溯算法仍然是某些搜索问题和约束满足问题的最佳解决方案**。

回溯算法的优化：

- 剪枝：避免搜索肯定不会产生解的路径
- 启发式搜索：搜索过程引入一些策略，优先搜索最有可能产生解的路径

回溯算法经典问题：

- 全排列问题
- 子集和问题
- n皇后问题