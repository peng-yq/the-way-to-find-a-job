[汉诺塔问题——Hello-Algo](https://www.hello-algo.com/chapter_divide_and_conquer/hanota_problem/)

## 汉诺塔问题

汉诺塔的问题描述如下：给定三根柱子，记为 A、B 和 C 。起始状态下，柱子A上套着n个圆盘，它们从上到下按照从小到大的顺序排列。我们的任务是要把这n个圆盘移到柱子C上，并保持它们的原有顺序不变。在移动圆盘的过程中，需要遵守以下规则：

- 圆盘只能从一个柱子顶部拿出，从另一个柱子顶部放入
- 每次只能移动一个圆盘
- 小圆盘必须时刻位于大圆盘之上

<img src="https://www.hello-algo.com/chapter_divide_and_conquer/hanota_problem.assets/hanota_example.png">

假如A上只有1个圆盘，我们只需直接将这个圆盘移到C上即可。

假如A上有2个圆盘，由于规则3的限制，我们需要借助B，称其为缓冲柱：

1. 先将A顶上的圆盘移动到B
2. 再将A底下的圆盘移动到C
3. 将B上的圆盘移动到C，完成移动

假如A上有3个圆盘呢？我们已经知道了只有1个盘子和有2个盘子时的解，因此解决过程如下：

1. 先将A上面两个盘看作一个整体，将其移动到B
2. 然后将A底下的圆盘移动到C
3. 最后将B上的圆盘移动到C，完成移动

上述步骤中我们将最上面的两个圆盘看作了一个整体，但这是不符合规则的，因为一次只能移动一个圆盘，那实际过程中是怎么移动而又不破坏规则的呢：

1. A中的圆盘从顶到底编号命名为1、2、3
2. 将A中的1移动到C
3. 将A中的2移动到B
4. 将C中的1移动到B,此时B有两个圆盘，顺序从顶到底为1、2
5. 将A中的3移动到C
6. 将B中的1移动到A
7. 将B中的2移动到C
8. 将A中的1移动到C,完成移动

可以看到2-4步则对应看成整体的第1步；第5步对应看成整体的第2步；第6-8步对应看成整体的第3步。

如果A中的盘子数量更多也是同样的解题思路：假设问题规模为n，f(n)表示将n个盘子进行移动的解题思路，将问题分解为f(n-1)和f(1)，这样不用去考虑f(n-1)的解题细节，因为f(n-1)会不断被分解为f(n-2)和f(1)，直到f(1)：

- 将n-1个盘子借助C从A移动到B
- 将1个盘子从A移动到C
- 将N-1个盘子借助A从B移动到C

也就是汉诺塔将f(n)问题划分了三个子问题f(n-1)、f(1)和f(n-1)

时间复杂度为$O(n)$，空间复杂度为$O(n)$

<img src="https://www.hello-algo.com/chapter_divide_and_conquer/hanota_problem.assets/hanota_recursive_tree.png">