[选择排序——Hello-Algo](https://www.hello-algo.com/chapter_sorting/selection_sort/)

## 选择排序

选择排序的原理很简单，每轮从未排序的区间里选择最小的元素，并放到已排序区间的末尾（也就是已排序区间的下一个位置）。

假设数组长度为n，通过选择排序进行排序的流程如下：
- 第一轮循环的索引区间为[0, n-1]，找出其中最小的数，并与索引为0的元素进行交换，完成一个元素的排序
- 第二轮循环的索引区间为[1, n-1]，找出其中最小的数，并与索引为1的元素进行交换，完成两个元素的排序
- 重复上述步骤直到未排序区间只剩一个元素时，也就是经过n-1轮，这个元素必定是最大元素，完成排序

## 算法特性

- 时间复杂度为$O(n^2)$，最完成循环为n-1轮，里面循环的次数为n,n-1,...,2，求和为$((n-1)(n+2))/2$，所以为$O(n^2)$，非自适应排序
- 空间复杂度为$O(1)，原地排序
- 非稳定排序

