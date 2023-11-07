[子集和问题-Hello-Algo](https://www.hello-algo.com/chapter_backtracking/subset_sum_problem/)

## 无重复元素

给定一个正整数数组nums和一个目标正整数target，请找出所有可能的组合，使得组合中的元素和等于target。给定数组无重复元素，每个元素可以被选取多次。请以列表形式返回这些组合，列表中不应包含重复组合。

例如，输入集合{3, 4, 5}和目标整数9，解为{3, 3, 3}和{4, 5}。需要注意以下两点:

- 输入集合中的元素可以被无限次重复选取
- 子集是不区分元素顺序的，比如{4, 5}和{5, 4}是同一个子集

参考全排列问题的解法，将每次寻找解的过程看作一次次的选择，子集和问题中选择结束的条件为元素和为目标值。转换为模板代
码也就是：state表示已选择的组合，比如{3, 3}；choices表示每次供选择的元素，由于集合中的元素可以被无限次重复选取，choices为集合中的所有元素；res表示所有可能的组合；selected不再需要，因为元素可以被无限次重复选取。

此外，我们还需要添加剪枝的条件：

- 如果此次选择加入的元素与组合中现有元素之和已经大于目标值target了，那这个分支的后续选择均没必要再继续了（假设集合有序），需要进行剪枝
- 需要考虑类似{4, 5}和{5, 4}这种重复子集的情况，需要进行剪枝。由于集合有序，那子轮选择的索引应该从母轮索引开始，对于集合{3, 4, 5}而言，第一轮选择为4时，这个分支下的第二轮选择应该从4开始，3需要被剪枝，因为{4, 3}和{3, 4}是同一子集，后者已经在第一轮选择为3的分支进行了

<img src="https://www.hello-algo.com/chapter_backtracking/subset_sum_problem.assets/subset_sum_i_naive.png">

<img src="https://www.hello-algo.com/chapter_backtracking/subset_sum_problem.assets/subset_sum_i_pruning.png">

因此除了上述参数，模板函数的参数还需要包括目标值以及选择的起始索引。
