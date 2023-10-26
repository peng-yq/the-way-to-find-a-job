[计数排序——Hello-Algo](https://www.hello-algo.com/chapter_sorting/counting_sort/)

## 计数排序

计数排序也是非比较排序算法，通过统计元素数量来实现排序，通常应用于**整数数组**。

计数排序的简单实现如下：

1. 遍历数组找出最大的数记为m，创建大小为m+1的辅助数组counter（0的存在）
2. 遍历数组，统计各数字的出现次数：遍历数组nums中的元素num，设置counter[num]的值，访问到便加1
3. 遍历counter数组各元素的次数，将大于1的索引按次数和顺序依次填入nums，最后得到排序好的数组

<img src="https://www.hello-algo.com/chapter_sorting/counting_sort.assets/counting_sort_overview.png">

> 计数排序本质是桶排序在整数数组下的一个特例：counter数组索引为一个桶，统计各数出现次数可以看做是将数据划分到各个桶中。

## 完整实现

但上述简单实现有一个明显的缺点：假设一个商品对象数组，商品对象包含一个价格的属性，我们想要根据价格这个属性对商品对象进行排序。根据简单实现的步骤3，我们只能得到商品价格排序后的数组，因为不能通过商品价格得到原对象。

### 前缀和

索引i处的前缀和prefix[i]等于counter数组前i个元素之和：

$$
\text{prefix}[i] = \sum_{j=0}^i \text{counter[j]}
$$

前缀和的意义：prefix[i]-1表示元素i在排序后数组中出现的最后索引，因此计数排序的完整实现如下：
1. 倒序遍历数组nums，因为前缀和是元素num出现的最后索引，所以倒序遍历可以保持数组的稳定性（对于对象来说，毕竟整数数组也不存在稳定排序一说）
2. 将num放入排序后数组res[prefix[num]-1]处，然后将其前缀和prefix[num]值-1
3. 重复步骤1和2，直到数组nums遍历完成

<img src="https://www.hello-algo.com/chapter_sorting/counting_sort.assets/counting_sort_step5.png">

## 算法特性

- 时间复杂度为$O(n+m)，主要是遍历原数组nums和辅助数组counter，但n基本>>m，时间复杂度趋近于$O(n)$
- 空间复杂度为$O(n+m)$，非原地排序
- 稳定排序

计数排序只适用于**非负整数**数组，如果不满足条件则需要进行转换，排序完再转换回去。

计数排序只适用于**数据量大但数据范围小**，即n>>m。
