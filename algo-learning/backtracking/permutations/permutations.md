[全排列问题-Hello-Algo](https://www.hello-algo.com/chapter_backtracking/permutations_problem/)

## 全排列问题

全排列问题是回溯算法的典型应用，给定一个集合（数组或字符串），找出这个集合中元素的所有排列情况。

## 无相等元素

例如：输入一个整数数组，例如[1，2，3]，数组中不包含重复元素，返回所有可能的排列。

我们可以将寻找元素所有排列的过程看作一系列选择的结果，回退表示撤销一个选择，再选择其他元素。按照回溯的模板代码，选择choices即数组中的所有元素，state表示已经选择的排列，但是在一次排列中，每个元素只能选择一次，也就是说state中的所有元素是不重复的。

<img src="https://www.hello-algo.com/chapter_backtracking/permutations_problem.assets/permutations_i.png">

前面说道choices是数组中的所有元素，但实际情况是每个元素只能选择一次，因此需要进行剪枝，即前一轮选择过的元素这一轮不能被选择。通过剪枝可以有效降低算法的时间复杂度，从$O(n^n)$降到$O(n!)$。

<img src="https://www.hello-algo.com/chapter_backtracking/permutations_problem.assets/permutations_i_pruning.png">



