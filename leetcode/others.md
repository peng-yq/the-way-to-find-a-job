## ACM输入输出及常见数据结构构造

### 输入数据有多组, 每行表示一组输入数据。

输入描述:

```
输入数据有多组, 每行表示一组输入数据。

每行不定有n个整数，空格隔开。(1 <= n <= 100)。
```

输出描述:

```
每组数据输出求和的结果
```

示例1

输入

```
1 2 3
4 5
0 0 0 0 0
```

输出

```
6
9
0
```

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    while (getline(cin, s)){
        istringstream is(s);
        int sum = 0, tmp;
        while (is >> tmp)
            sum += tmp;
        cout << sum << endl;
    }
    return 0;
}
```

### 多个测试用例，每个测试用例一行。

输入描述:

```
多个测试用例，每个测试用例一行。

每行通过空格隔开，有n个字符，n＜100
```

输出描述:

```
对于每组测试用例，输出一行排序过的字符串，每个字符串通过空格隔开
```

示例1

输入


```
a c bb
f dddd
nowcoder
```

输出


```
a bb c
dddd f
nowcoder
```

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    while (getline(cin, s)) {
        istringstream is(s);
        vector<string> str;
        string tmp;
        while (is >> tmp) 
            str.push_back(tmp);
        sort(str.begin(), str.end());
        for (auto c : str)
            cout << c << " ";
        cout << endl;
    }
    return 0;
}
```

### 多个测试用例（字符串用,分隔），每个测试用例一行。

输入描述:

```
多个测试用例，每个测试用例一行。
每行通过,隔开，有n个字符，n＜100
```

输出描述:

```
对于每组用例输出一行排序后的字符串，用','隔开，无结尾空格
```

示例1

输入


```
a,c,bb
f,dddd
nowcoder
```

输出


```
a,bb,c
dddd,f
nowcoder
```

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    while (getline(cin, s)) {
        for (auto& c : s) {
            if (c == ',')
                c = ' '; 
        }
        istringstream is(s);
        vector<string> str;
        string tmp;
        while (is >> tmp)
            str.push_back(tmp);
        sort(str.begin(), str.end());
        for (int i = 0 ; i < str.size() - 1; ++i) 
            cout << str[i] << ",";
        cout << str.back() << endl;
    }
    return 0;
}
```

### 每一行数据是逗号隔开的整数

输入格式：

```
2 3
1,2,3
1,2,3
```

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    getchar();
    vector<vector<int>> v(m, vector<int>(n));
    for(int i = 0; i < m; ++i) {
        string s;
        getline(cin, s);
        for (auto& c : s) {
            if (c == ',')
                c = ' ';
        }
        istringstream is(s);
        for (int j = 0; j < n; ++j)
            is >> v[i][j];
    }
    for(int i = 0; i < m; i++) {
    	for(int j = 0; j < n; j++) {
    		cout << v[i][j] << " ";
    	}
    	cout << endl;
    }
    return 0;
}
```

### 单链表

```c++
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int val_) : val(val_), next(nullptr) {};
    ListNode(int val_, ListNode* nxt) : val(val_), next(nxt) {};
};

int main() {
    ListNode* dummy = new ListNode(-1);
    ListNode* head = dummy;
    int num;
    while (cin >> num) {
        ListNode* cur = new ListNode(num);
        head->next = cur;
        head = cur;
    }
    dummy = dummy->next;
    while (dummy) {
        cout << dummy->val << " ";
        dummy = dummy->next;
    }
    return 0;
}
```

### 双链表

```c++
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode* pre;
    ListNode(int val_) : val(val_), next(nullptr), pre(nullptr) {};
    ListNode(int val_, ListNode* nxt, ListNode* preN) : val(val_), next(nxt), pre(preN) {};
};

int main() {
    ListNode* dummy = new ListNode(-1);
    ListNode* head = dummy;
    int num;
    while (cin >> num) {
        ListNode* cur = new ListNode(num);
        head->next = cur;
        cur->pre = head;
        head = cur;
    }
    dummy = dummy->next;
    while (dummy) {
        cout << "pre: " << dummy->pre->val << " " << endl;
        cout << "cur: " << dummy->val << " " << endl;
        dummy = dummy->next;
    }
    return 0;
}
```

### 二叉树及其层序遍历

递归的去创建二叉树

```c++
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {};
  TreeNode(int val_) : val(val_), left(nullptr), right(nullptr) {};
  TreeNode(int val_, TreeNode* leftNode, TreeNode* rightNode) : val(val_), left(leftNode), right(rightNode) {};
};

TreeNode* buildTreeHelper(const vector<int>& nums, int index) {
    if (index >= nums.size())
        return nullptr;
    TreeNode* root = new TreeNode(nums[index]);
    root->left = buildTreeHelper(nums, 2 * index + 1);
    root->right = buildTreeHelper(nums, 2 * index + 2);
    return root;
}

TreeNode* buildTree(const vector<int>& nums) {
    return buildTreeHelper(nums, 0);
}

void printLevelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        for (int i = q.size(); i > 0; i--) {
            TreeNode* node = q.front();
            q.pop();
            cout << node->val << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* root = buildTree(nums);
    printLevelOrder(root); // Output should be: 1 2 3 4 5 6 7
    return 0;
}
```

### getchar()

在C++中，当使用`cin`进行输入时，有时会遇到换行符（`'\n'`）残留在输入缓冲区中的情况。这种情况通常发生在以下几种情形下：

1. **混合使用 `cin` 和 `getline`**：`cin` 读取数据后，输入缓冲区中可能会残留一个换行符。如果随后使用 `getline` 读取字符串，这个换行符会被 `getline` 读取，导致读取到的是一个空行。
2. **读取整数或其他非字符串类型后**：`cin` 读取整数、浮点数等非字符串类型时，会在缓冲区中留下一个换行符。

在这些情况下，我们需要使用 `getchar()` 或 `cin.ignore()` 来吸收掉这个换行符，确保后续的输入操作能够正确进行。

## 动态规划经典题型

### 0-1背包问题

给定i个物品，第i个物品的重量为wgt[i-1]、价值为val[i-1]，和一个容量为cap的背包。每个物品只能选择一次，问在不超过背包容量下能放入物品的最大价值。

#### 判断是否为动态规划问题

- 问题可以通过回溯穷举解决，即将放入一个物品视作一次选择，进行多次选择，直到背包放不下，最后通过多次尝试和回退得到所有的选择
- 题目中包含“最大”关键词
- 满足最优子问题的特性。在选择一个物品时，都会有两种选择，一种是选择放入，一种是不选择放入，最终会选择两个之中背包总价值最大的那一个
- 满足无后效性。选择一个物品放入与不放入时，背包的总价值都只与当前物品有关，背包中已经放入的物品的价值是固定的


#### 动态规划

首先需要确定的是状态，根据分析可以知道在做每次选择时，变化的是当前选择的物品编号i、背包的剩余容量c以及背包已装入物品的总价值。

因此dp数组可表示为dp[i,c]为前i个物品在背包剩余容量为c时的总价值。

状态转移方程为dp[i,c] = max(dp[i-1,c], dp[i-1,c-wgt[i-1]] + val[i-1])，若此时物品的重量超过了背包的剩余容量，则只有选择不放入背包，dp[i,c] = dp[i-1,c]

当无物品或无剩余背包容量时最大价值为0，即首列dp[i, 0]和首行dp[0,c]都等于0。

```c++
int knapsackDP(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    vector<vector<int>>dp (n+1, vector<int>(cap + 1, 0));
    for (int i = 1; i < n+1; i++) {
       for (int c = 1; c < cap + 1; c++) {
            if (wgt[i-1] > c) {
                 dp[i][c] = dp[i-1][c];
            }
            else {
                dp[i][c] = max(dp[i-1][c], dp[i-1][c-wgt[i-1]]+val[i-1]);
            }
            
       }
    }
    return dp[n][cap];
}
```

#### 空间优化

前面的解法中空间复杂度为$O(n^2)$，由于每个状态都是由正上方或者左上方的状态选择而来，我们可以尝试只使用一个数组来解决问题，但如果采用正序遍历dp[i,j]的前面状态dp[i,j-1]和dp[i-1， j-1]可能已经被修改（此时只有一个数组），因此需要采用倒序遍历。

```c++
int knapsackDPComp(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    vector<int>dp(cap + 1, 0);
    for (int i = 1; i < n+1; i++) {
        for (int c = cap; c > 0; c--) {
            if (wgt[i-1] <= c)
                dp[c] = max(dp[c], dp[c-wgt[i]]+val[i]);
        }
    }
    return dp[cap];
}
```

### 完全背包问题

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

```c++
int unboundedKnapsackDP(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    vector<vector<int>>dp (n+1, vector<int> (cap+1, 0));
    for (int i = 1; i < n + 1; i++) {
        for (int c = 1; c < cap + 1; c++) {
            if (wgt[i-1] > c) {
                dp[i][c] = dp[i-1][c];
            } else {
                dp[i][c] = max(dp[i-1][c], dp[i][c-wgt[i-1]] + val[i-1]);
            }
        }
    }
    return dp[n][cap];
}
```

**空间优化**

相比于0-1背包问题，此时每个状态基于左边的状态（因为每个物品可以重复选取）以及上方的状态，因此空间优化需要正向进行遍历。

```c++
int unboundedKnapsackDPComp(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    vector<int> dp(cap + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= cap; c++) {
            if (wgt[i - 1] <= c) {
                dp[c] = max(dp[c], dp[c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[cap];
}
```

#### 零钱兑换问题

给定n种硬币，第i种硬币的面值为coins[i]，目标金额为amt，每种硬币可以重复选取，问能够凑出目标金额的最少硬币个数。如果无法凑出目标金额则返回-1。

零钱兑换问题是背包问题的变种，我们可以将硬币对应物品，硬币的面值对应物品的价值，目标金额对应背包的容量，求取不超过背包容量的最大价值变为了凑出目标金额的最少硬币个数。

**思考每轮的决策，定义状态，从而得到dp表**

类似的我们将dp[i,a]定义为前i个硬币能凑出金额a的最小硬币个数。

**找出最优子结构，进而推导出状态转移方程**

dp[i,a] = min(dp[i-1,a], dp[i,a-conis[i-1]] + 1)

**确定边界条件和状态转移顺序**

- a为0时，即目标金额为0，此时无论i为多少，都只需要0个硬币即可凑出目标金额

- i为0时，即没有硬币时，无法凑出任何金额大于0的目标，为无效解，使用amt+1来代替MAX_INT，从而避免+1时产生数组越界

```c++
int coinChangeDP(vector<int> &coins, int amt) {
    int n = coins.size();
    vector<vector<int>>dp(n+1, vector<int> (amt+1,0));
    // dp[0][0] = 0
    for(int i = 1; i < amt+1; i++) {
        dp[0][i] = amt + 1;
    }
    for(int i = 1; i < n+1; i++) {
        for(int a = 1; a < amt+1; a++) {
            if(coins[i-1] > a) {
                dp[i][a] = dp[i-1][a];
            } else {
                dp[i][a] = min(dp[i-1][a], dp[i][a-coins[i-1]]+1);
            }
        }
    }
    return dp[n][amt] == amt + 1? -1:dp[n][amt];
}
```

**空间优化与完全背包问题一致**

```c++
int coinChangeDPComp(vector<int> &coins, int amt) {
    int n = coins.size();
    int MAX = amt + 1;
    vector<int> dp(amt + 1, MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int a = 1; a <= amt; a++) {
            if (coins[i - 1] > a) {
                dp[a] = dp[a];
            } else {
                dp[a] = min(dp[a], dp[a - coins[i - 1]] + 1);
            }
        }
    }
    return dp[amt] != MAX ? dp[amt] : -1;
}
```

#### 零钱兑换问题Ⅱ

给定n种硬币，第i种硬币的面值为coins[i-1]，目标金额为amt，每种硬币可以重复选取，问在凑出目标金额的硬币组合数量。

此时题目求取凑出目标金额的最小硬币数，变成了凑出目标金额的硬币组合数量。这道题也可以用回溯去做，通过选择和回退以及剪枝，但我们不需要得到具体的组合，只需要得到组合数量。因此问题也就和最开始的求取上台阶的方案数量类似，组合数量等于选择硬币以及不选择硬币的组合数量之和。

将dp[i][a]定义为前i个硬币凑出目标金额为a的组合数目。

dp[i][a] = dp[i-1][a] + dp[i][a-conis[i-1]]

- 当只有0个硬币时，不能凑出任何金额大于0的目标，因此组合数初始化为0。
- 当目标金额为0时，任何个数的硬币的组合数均为1。

```c++
int coinChangeIIDP(vector<int> &coins, int amt) {
     int n = coins.size();
    vector<vector<int>>dp(n+1, vector<int> (amt+1,0));
    // dp[0][0] = 0
    for(int i = 0; i < amt+1; i++) {
        dp[i][0] = 1;
    }
    for(int i = 1; i < n+1; i++) {
        for(int a = 1; a < amt+1; a++) {
            if(coins[i-1] > a) {
                dp[i][a] = dp[i-1][a];
            } else {
                dp[i][a] = dp[i-1][a] + dp[i][a-coins[i-1]];
            }
        }
    }
    return dp[n][amt];
}
```

**空间优化与零钱兑换问题一致**

```c++
int coinChangeIIDPComp(vector<int> &coins, int amt) {
    int n = coins.size();
    vector<int> dp(amt + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int a = 1; a <= amt; a++) {
            if (coins[i - 1] > a) {
                dp[a] = dp[a];
            } else {
                dp[a] = dp[a] + dp[a - coins[i - 1]];
            }
        }
    }
    return dp[amt];
}
```

### 编辑距离

编辑距离问题指两个字符串之间互相转换的最小修改次数，通常用于在信息检索与自然语言处理中度量两个序列的相似度。

输入两个字符串s和t，返回将s转换为t所需的最少编辑步数。你可以在一个字符串中进行三种编辑操作：插入一个字符、删除一个字符、替换字符为任意一个字符。

<img src="https://www.hello-algo.com/chapter_dynamic_programming/edit_distance_problem.assets/edit_distance_example.png">

**思考每轮的决策，定义状态，从而得到dp表**

每轮决策都是对两个字符串的两个字符进行编辑操作，将[i,j]定义为对字符串s中的第i个字符和字符串t中的第j个字符进行编辑操作，dp[i,j]定义为对字符串s中的前i个字符和字符串t中的前j个字符进行编辑操作的最小次数。

- 当s[i-1] = t[i-1]，无需进行编辑，转换为对s[i-2]和t[i-2]的比较
- 当s[i-1] != t[i-1]，需要对两个字符进行插入、删除和替换操作（三选一）

**找出最优子结构，进而推导出状态转移方程**

当s[i-1] == t[i-1]时，dp[i][j] = dp[i-1][j-1]

当s[i-1] != t[i-1]时，需要进行修改操作：
- 在s后一个位置添加t[i-1]时，dp[i][j] = dp[i][j-1]
- 删除s[i-1]时，dp[i][j] = dp[i-1][j]
- 将s[i-1]替换为t[i-1]时，dp[i][j] = dp[i-1][j-1]

因为是求编辑操作的最小次数，因此若两个字符不等时，状态转移方程如下：

dp[i][j] = min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]) + 1

**确定边界条件和状态转移顺序**

当s和t字符串长度为0时，无需任何编辑，即dp[0][0] = 0
当s为空，t不为空时，最少编辑步数等于t子字符串的长度，dp[0][j] = j
当s不为空，t为空时，最小编辑步数等于s子字符串的长度，dp[i][0] = i

```c++
int editDistanceDP(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for (int j = 1; j < m+1; j++)
        dp[0][j] = j;
    for (int i = 1; i < n+1; i++)
        dp[i][0] = i;
    for (int i = 1; i < n+1; i++) {
        for (int j = 1; j < m+1; j++) {
            if (s[i-1] == t[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = min(dp[i-1][j-1], dp[i][j-1], dp[i-1][j]) + 1;
        }
    }
    return dp[n][m];
}
```

**优化空间**

正序遍历会失去dp[i-1][j-1]，倒序遍历无法提前得到dp[i][j-1]，因此需要使用一个临时变量保存dp[i-1][j-1]

```c++
int editDistanceDPComp(string s, string t) {
    int n = s.size(), m = t.size();
    vector<int> dp (m+1, 0);
    for (int i = 1; i < m+1; i++) {
        dp[i] = i;
    }
    for (int i = 1; i < n+1; i++) {
        int left = dp[0];
        dp[0] = i;
        for (int j = 1; j < m+1; j++) {
            int temp = dp[j];
            if (s[i-1] == t[j-1]) {
                dp[j] = left;
            } else {
                dp[j] = min (dp[j-1], left, dp[j]) + 1;
            }
            left = temp;
        }
    }
    return dp[m];
}
```

## 回溯经典题型

### 子集和问题

#### 无重复元素

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

#### 有重复元素

给定一个正整数数组nums和一个目标正整数target ，请找出所有可能的组合，使得组合中的元素和等于target。给定数组可能包含重复元素，每个元素只可被选择一次。请以列表形式返回这些组合，列表中不应包含重复组合。

当给定数组中可能包含重复元素时，需要进行剪枝，例如给定数组为{4, 4, 5}，目标元素为9，按照无重复元素的算法，得到的答案为{4, 5}和{4, 5}，需要在第一轮选择时直接剪掉第二个4那个分支。由于数组是排序的，只需比较选择的元素是否等于上一个索引的元素，若相等说明此次选择重复，进行剪枝。

此外，每个元素只可被选择一次，也就是每次选择的开始索引要从上次选择的开始索引的下一位开始。

<img src="https://www.hello-algo.com/chapter_backtracking/subset_sum_problem.assets/subset_sum_ii.png">

```c++
#include <bits/stdc++.h>
using namespace std;

void backtrack(vector<int> &state, vector<int> &choices, int target, int start, vector<vector<int>> &res) {
    if (target == 0) {
        res.push_back(state);
        return;
    }
    for (int i = start; i < choices.size(); i++) {
        
        state.push_back(choices[i]);
        backtrack(state, choices, target - choices[i], i, res);
        state.pop_back();
    }
}

void backtrack(vector<int> &state, vector<int> &choices, int target, int start, vector<vector<int>> &res) {
    if (target == 0) {
        res.push_back(state);
        return;
    }
    for (int i = start; i < choices.size(); i++) {
        if (target - choices[i] < 0)
            break;
        // i > start makes sure i-1 >= 0
        if(i > start && choices[i] == choices[i-1])
            continue;
        state.push_back(choices[i]);
        backtrack(state, choices, target - choices[i], i+1, res);
        state.pop_back();
    }
}

vector<vector<int>> subsetSumI(vector<int> &nums, int target) {
    vector<int> state;
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    backtrack(state, nums, target, 0, res);
    return res;
}
```

### 全排列问题

全排列问题是回溯算法的典型应用，给定一个集合（数组或字符串），找出这个集合中元素的所有排列情况。

#### 无相等元素

例如：输入一个整数数组，例如[1，2，3]，数组中不包含重复元素，返回所有可能的排列。

我们可以将寻找元素所有排列的过程看作一系列选择的结果，回退表示撤销一个选择，再选择其他元素。按照回溯的模板代码，选择choices即数组中的所有元素，state表示已经选择的排列，但是在一次排列中，每个元素只能选择一次，也就是说state中的所有元素是不重复的。

<img src="https://www.hello-algo.com/chapter_backtracking/permutations_problem.assets/permutations_i.png">

前面说道choices是数组中的所有元素，但实际情况是每个元素只能选择一次，因此需要进行剪枝，即前一轮选择过的元素这一轮不能被选择。通过剪枝可以有效降低算法的时间复杂度，从$O(n^n)$降到$O(n!)$。

<img src="https://www.hello-algo.com/chapter_backtracking/permutations_problem.assets/permutations_i_pruning.png">

#### 有相等元素

输入一个整数数组，例如[1, 1, 2]，数组中可能包含重复元素，返回所有不重复的排列。

如果继续采用上述办法，可以发现会有一半的排列都是重复的。最直接的去除重复的办法是通过一个哈希表，直接对排列结果进行去重，但这样没有从根本上解决问题。因为重复排列的选择分支是不该存在的，应该对其进行剪枝，从而减小时间和空间复杂度。

对于含有相等元素的数组，除了之前选择的元素不能被再次选择外，每一轮每个元素也只能选择一次。

<img src="https://www.hello-algo.com/chapter_backtracking/permutations_problem.assets/permutations_ii_pruning.png">

时间复杂度为$O(n!n)$，空间复杂度为$O(n^2)$。

```c++
#include <bits/stdc++.h>
using namespace std;

// template: state choices condition(use to prune) res

void backtrack(vector<int> &state, const vector<int> &choices, vector<bool> &selected, vector<vector<int>> &res) {
    if (state.size() == choices.size()) {
        res.push_back(state);
        return;
    }

    for(int i = 0; i < choices.size(); i++) {
        if(!selected[i]) {
            state.push_back(choices[i]);
            selected[i] = true;
            backtrack(state, choices, selected, res);
            selected[i] = false;
            state.pop_back();
        }
    }
}

vector<vector<int>> permutationsI(vector<int> nums) {
    vector<int> state;
    vector<bool> selected (nums.size(), false);
    vector<vector<int>> res;
    backtrack(state, nums, selected, res);
    return res;
}

void backtrack(vector<int> &state, const vector<int> &choices, vector<bool> &selected, vector<vector<int>> &res) {
    if(state.size() == choices.size()) {
        res.push_back(state);
        return;
    }

    unordered_set<int> duplicated;

    for(int i = 0; i < choices.size(); i++) {
        if(!selected[i] && duplicated.find(choices[i]) == duplicated.end()) {
            duplicated.emplace(choices[i]);
            selected[i] = true;
            state.push_back(choices[i]);
            backtrack(state, choices, selected, res);
            selected[i] = false;
            state.pop_back();
        }
    }
}

vector<vector<int>> permutationsII(vector<int> nums) {
    vector<int> state;
    vector<bool> selected(nums.size(), false);
    vector<vector<int>> res;
    backtrack(state, nums, selected, res);
    return res;
}
```

### N皇后问题

根据国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。给定n个皇后和一个n*n大小的棋盘，寻找使得所有皇后之间无法相互攻击的摆放方案。

从回溯算法来看，state为当前棋盘皇后的排列状态，choices为n*n个格子，res则是最后符合题目条件的n个皇后的排列状态。

<img src="https://www.hello-algo.com/chapter_backtracking/n_queens_problem.assets/n_queens_constraints.png">

#### 剪枝

由于皇后可以攻击与之处在同一行、同一列或同一斜线的棋子，因此在进行选择时需要对其进行剪枝：

- 由于皇后不能处于同一列，并且棋盘大小为n*n，也就是说每一行最多一个皇后，最多进行n轮选择
- 不能处于同一列的限定条件也很好解决，只需要一个数组大小为n的bool数组用于记录每列是否已放置皇后；在进行每轮选择时首先通过这个数组进行判断这一列是否已放置皇后，若放置则直接进行剪枝

不能处于同一斜线的限定条件相对棘手一些，如下图所示斜线可分为两种：

- 第一种斜线上的棋子横坐标-纵坐标的值一致,横坐标-纵坐标的值的范围为[1-n, n-1]，共2n-1个元素，使用一个数组大小为2n-1的bool数组进行记录，需要注意的是由于有负值，因此在计算的时候需要加上n-1与数组索引相对应
- 第二种斜线上的棋子横坐标+纵坐标的值一致,横坐标+纵坐标的值的范围为[0, 2n-2]，共2n-1个元素，直接使用一个数组大小为2n-1的bool数组进行记录

上述bool数组也可以使用同样大小的哈希表进行记录。

<img src="https://cdn.jsdelivr.net/gh/peng-yq/Gallery/img/202311081657545.jpg">

```c++
#include <bits/stdc++.h>
using namespace std;


void backtrack(int row, int n, vector<vector<char>> &state, vector<vector<vector<char>>> &res, vector<bool> &cols, vector<bool> &diags1, vector<bool> &diags2) {
    if (row == n) {
        res.push_back(state);
        return;
    }
    for(int col = 0; col < n; col++) {
        if (cols[col] || diags1[row - col + n - 1] || diags2[row + col])
            continue;
        cols[col] = diags1[row - col + n - 1] = diags2[row + col] = true;
        state[row][col] = 'Q';
        backtrack(row + 1, n, state, res, cols, diags1, diags2);
        state[row][col] = '#';
        cols[col] = diags1[row - col + n - 1] = diags2[row + col] = false;
    }
}

vector<vector<vector<char>>> nQueens(int n) {
    vector<vector<vector<char>>> res;
    vector<vector<char>> state(n, vector<char>(n,'#'));
    vector<bool> cols(n, false); 
    vector<bool> diags1(2*n-1, false);
    vector<bool> diags2(2*n-1, false);
    backtrack(0, n, state, res, cols, diags1, diags2);
}
```

#### 算法特性

- 时间复杂度为$O(n!)$
- 空间复杂度为$O(n^2)$

## 排序

### 选择排序

选择排序的原理很简单，**每轮从未排序的区间里选择最小的元素，并放到已排序区间的末尾（也就是已排序区间的下一个位置）**。

假设数组长度为n，通过选择排序进行排序的流程如下：
- 第一轮循环的索引区间为[0, n-1]，找出其中最小的数，并与索引为0的元素进行交换，完成一个元素的排序
- 第二轮循环的索引区间为[1, n-1]，找出其中最小的数，并与索引为1的元素进行交换，完成两个元素的排序
- 重复上述步骤直到未排序区间只剩一个元素时，也就是经过n-1轮，这个元素必定是最大元素，完成排序

#### 算法特性

- 时间复杂度为$O(n^2)$，最完成循环为n-1轮，里面循环的次数为n,n-1,...,2，求和为$((n-1)(n+2))/2$，所以为$O(n^2)$，非自适应排序
- 空间复杂度为$O(1)，原地排序
- 非稳定排序

```c++
#include <bits/stdc++.h>
using namespace std;

void swap(vector<int> &nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

void selectionSort(vector<int> &nums) {
    for(int i = 0; i < nums.size() - 1; i++) {
        int min = i;
        // we use j = i + 1 instead of j = i, because the min = i
        for(int j = i + 1; j < nums.size(); j++) {
            if(nums[j] < nums[min]) {
                min = j;
            }
        }
        swap(nums, i, min);
    }
}
```

### 冒泡排序

**冒泡排序通过连续的比较和交换相邻元素实现排序，每轮循环从左至右比较相邻元素，如果左元素>右元素则进行交换，每轮循环都会将未排序区间的最大元素选出**。

假设数组长度为n,使用冒泡排序的流程如下：
- 未排序的区间为[0, n-1]，从左到右进行冒泡，冒泡结束后最大元素位于索引n-1处
- 未排序的区间为[0, n-2]，从左到右进行冒泡，冒泡结束后最大元素位于索引n-2处
- 重复上述循环n-1轮后，只剩索引为0的元素，必定为最小元素，完成排序

<img src="https://www.hello-algo.com/chapter_sorting/bubble_sort.assets/bubble_sort_overview.png">

#### 冒泡优化

假如数组本身就是有序的，按照上述流程依旧要进行n-1轮循环。因此只有某一轮循环没有进行交换，则直接结束排序。

经过优化后的冒泡排序最优时间复杂度为$O(n)$，即数组是有序的，第一轮循环即可结束排序。最差和平均时间复杂度仍为$O(n^2)$，计算公式和选择排序一致。

#### 算法特性

- 时间复杂度为$O(n^2)$，优化后为自适应排序
- 空间复杂度为$O(1)$，原地排序
- 稳定排序

```c++
void bubbleSortWithFlag(vector<int> &nums) {
    for(int i = nums.size() - 1, flag = 0; flag && i > 0; i--) {
        for(int j = 0; j< i; j++) {
                if (nums[j] > nums[j + 1]) {
                    swap(nums[j], nums[j + 1]);
                    flag = 1;
                }
        }
    }
}
```

### 插入排序

插入排序的流程和整理一副牌很类似：**在整理一副牌时，有的人会选择拿一张整理一张，这样手中的牌始终是有序的。当拿起一张新牌时，只需将其插入到合适的位置即可**。

假设数组长度为n,采用插入排序的流程如下：
- 初始第一个元素为排序好的
- 选取数组第二个元素插入到合适位置，此时两个元素已排序
- 重复上述步骤，直到最后一个元素插入到合适位置，此时全部元素完成排序

<img src="https://www.hello-algo.com/chapter_sorting/insertion_sort.assets/insertion_sort_overview.png">

#### 算法特性

- 时间复杂度为$O(n^2)$, 自适应排序，当数组完全有序时，时间复杂度为$O(n)$（体现在代码中也就是while循环直接不成立）
- 空间复杂度为$O(1)$，原地排序
- 稳定排序

#### 优势

- **数据量更小时，插入排序比快速排序更快，因为此时时间复杂度相差不大，而快速排序是分治的思想，需要更多的单元操作**
- 许多编程语言（例如 Java）的内置排序函数都采用了插入排序，**大致思路为：对于长数组，采用基于分治的排序算法，例如快速排序；对于短数组，直接使用插入排序**
- 选择排序、冒泡排序和插入排序三者时间复杂度均为$O(n^2)，但插入排序使用更多，涉及更少的单元操作，并且稳定

```c++
void insertionSort(vector<int> &nums) {
    for(int i = 1; i < nums.size(); i++) {
        int base = nums[i], j = i - 1;
        while(j >= 0 && nums[j] > base) {
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = base;
    }
}
```

### 快速排序

#### 哨兵划分

快速排序是一种**基于分治的排序策略**，核心操作是“哨兵划分”：选定数组中的一个数作为基准数，将所有小于基准数的元素移到其左侧，所有大于基准数的元素移到其右侧。

哨兵划分的流程：

1. 选取数组最左端的元素作为基准数，初始化两个指针i, j分别指向数组的最左端和最右端
2. 设置一个循环，每轮循环中使用i (j) 分别寻找第一个比基准数大（小）的元素，并交换这两个元素的位置
3. 执行循环直至i和j相等，然后将基准数交换至两个子数组的分界线（也就是i (j) 的位置）

哨兵划分后的数字将以基准数为界分为左右两个子数组，左子数组的元素均小于基准数，而右子数组的元素均大于基准数。

**需要注意的是哨兵划分后的左右子数组均未排序**。

因此**快速排序的分治策略体现在将一个较大数组的排序问题转换为两个较小数组的排序问题**。

快速排序的整体流程：

1. 进行一次哨兵划分，将原数组变成未排序的左子数组和右子数组
2. 对左右子数组分别递归进行哨兵划分
3. 持续递归，直至子数组长度为1，完成整个数组的排序
   
#### 算法特性

- 时间复杂度为$O(nlogn)$，最差时间复杂度（逆序）为$O(n^2)$
- 空间复杂度为$O(n)$，原地排序
- 非稳定排序（哨兵划分最后一步调整基准数位置导致）

快速排序的平均时间复杂度虽然和归并排序以及堆排序一致（$O(nlogn)$），但通常快速排序效率更高：

- 出现最差时间复杂度情况概率较低
- 缓存使用效率高，哨兵划分就将整个数组加入缓存
- 复杂度的常数系数低，比较、赋值和交换等操作的总数量最少

#### 快速排序优化

快速排序在某些情况下效率会降低，例如数组为全逆序时，快速排序退化为冒泡排序。

快速排序的优化可通过**基准数优化（优化时间复杂度）**以及**尾递归优化（优化空间复杂度）**。

#### 基准数优化

将数组元素的首、中、尾三个元素的中位数设定为基准数。

#### 尾递归优化

每轮哨兵排序后，比较两子数组的长度，只对较短子数组进行递归。

```c++
void swap(vector<int> &nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

int partition(vector<int> &nums, int left, int right) {
    int i = left, j = right;
    while (i < j) {
        while (i < j && nums[left] <= nums[j])
            j--;
        while (i < j && nums[left] >= nums[i])
            i++;
        swap(nums, i, j);
    }
    swap(nums, left, i);
    return i;
}

void quickSort(vector<int> &nums, int left, int right) {
    if (left >= right)
        return; 
    int pivot = partition(nums, left, right);
    partition(nums, left, pivot - 1);
    partition(nums, pivot + 1, right);
}
```

### 归并排序

归并排序也是一种**基于分治的排序策略**，主要分为“划分”和“合并”阶段：

- 划分：从数组中点对数组进行划分，分为左右子数组；再持续对左右子数组递归划分
- 合并：子数组长度为1时停止划分，持续的将左右子数组合并为一个较长的有序数组，直至结束

归并排序的难点在于合并阶段 (比较难理解)：

<img src="https://www.hello-algo.com/chapter_sorting/merge_sort.assets/merge_sort_overview.png"></img>

- [3,7]和[2,6]的合并：2,3比较，先放入2；3,6比较，先放入3；7,6比较，先放入6；右子数组合并完毕，无需比较直接放入7
- [0,1]和[4,5]的合并原理同上
- [2,3,6,7]和[0,1,4,5]的合并原理同上

归并排序与二叉树后序遍历的递归顺序一致，归并排序先递归划分左子数组、右子数组，最后处理合并。

#### 算法特性
- 时间复杂度为$O(nlogn)$，非自适应排序，因为递归次数始终为$logn$
- 空间复杂度为$O(n)$，合并需要辅助数组，非原地排序
- 稳定排序

```c++
void merge(vector<int> &nums, int left, int mid, int right) {
    vector<int> tmp(nums.begin() + left, nums.begin() + right + 1);
    int leftStart = left - left, leftEnd = mid - left;
    int rightStart = mid + 1 - left, rightEnd = right- left;
    int i = leftStart, j = rightStart;
    for(int k = left; k <= right; k++) {
        if(i > leftEnd) {
            nums[k] = tmp[j++];
        }
        else if(j > rightEnd || tmp[i] <= tmp[j]) {
            nums[k] = tmp[i++];
        }
        else {
            nums[k] = tmp[j++];
        }
    }
}

void mergeSort(vector<int> &nums, int left, int right) {
    if(left >= right) 
        return;
    int mid = (left + right) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid + 1, right);
    merge(nums, left, mid, right);
}
```

### 堆排序

堆排序是一种基于堆数据结构的排序，通过“建堆操作”和“元素出堆顺序”实现堆排序：

1. 输入数组建立大顶堆，完成后，最大元素位于堆顶

2. 将堆顶元素和堆底元素进行交换，堆长度减1,已排序元素加一

3. 从堆顶元素开始，从顶到底进行堆化

4. 循环执行2,3步，循环n-1轮（n为数组大小）后，完成数组排序

#### 算法特性

- 时间复杂度为$O(nlogn)$，建堆操作为$O(n)$，从堆中提取最大元素为$O(logn)$，循环n-1轮
- 空间复杂度$O(1)$，原地排序
- 非稳定排序，交换堆顶和堆底元素时，相等元素的相对位置可能变化

```c++
void siftDown(vector<int>& nums, int n, int i) {
    int largest = i, left = i * 2 + 1, right = i * 2 + 2;
    if (left < n && nums[left] > nums[largest])
        largest = left;
    if (right < n && nums[right] > nums[largest])
        largest = right;
    if (largest != i) {
        swap(nums[largest], nums[i]);
        siftDown(nums, n, largest);
    }
}


class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        for (int i = n / 2 - 1; i >= 0; --i) {
            siftDown(nums, n, i);
        }
        for (int i = n - 1; i >= 0; --i) {
            swap(nums[0], nums[i]);
            siftDown(nums, i, 0);
        }
        return nums;
    }
};
```

### 桶排序

选择排序、冒泡排序、插入排序、快速排序、归并排序、堆排序这些利用元素之间的比较来排序的算法，称为“基于比较的排序算法“，其时间复杂度不会小于$O(nlogn)$。堆排序属于“非比较排序算法”，其时间复杂度可以到达线性阶。

桶排序是基于分治的排序算法，通过设置一些具有大小顺序的桶，每个桶有个范围，将数据分配到各个桶中；在每个桶内部堆数据进行排序，再按照桶的顺序将所有数据合并。

<img src="https://www.hello-algo.com/chapter_sorting/bucket_sort.assets/bucket_sort_overview.png">

#### 算法特性

桶排序适合处理体量很大的数据。

- 时间复杂度$O(n+k)$：假设元素在每个桶平均分布，每个桶的元素数量为$n/k$，假设排序单个桶的使用$O({n/k} * log{n/k})$ ,排序所有桶需要使用$O(n * log{n/k})$的时间。当桶的数量$k$很大时，时间复杂度趋向于$O(n)$。合并所有结果需要遍历所有桶和元素，花费$O(n+k)$
- 自适应排序，当所有元素分到一个桶时，时间复杂度为$O(n^2)$
- 空间复杂度为$O(n+k)$，需要$k$个桶和$n$个额外元素；非原地排序
- 是否是稳定排序取决于桶内排序所用的算法

#### 如何实现平均分配

若想桶排序时间复杂度实现线性阶$O(n)$，**关键在于如何实现元素的平均分配**：

- 首先设定一个大致的分界线，将数据划分到3个桶中（也不一定是3）
- 将数据较多的桶再划分到3个桶中，直至每个桶数据量大致相同

本质是一个递归树，让叶节点的值尽可能相同。

**若知道数据的概率分布，则可以直接根据概率分布进行界限划分**。

```c++
void bucketSort(vector<float> &nums) {
    int k = nums.size() / 2;
    vector<vector<float>>buckets(k);
    for(float num : nums){
        int i = num * k;
        buckets[i].push_back(num);
    }
    for(vector<float> &bucket : buckets)
        sort(bucket.begin(), bucket.end());
    int i = 0;
    for(vector<float> &bucket : buckets) {
         for(float num : bucket){
            nums[i++] = num;
        }
    }      
}
```

### 计数排序

计数排序也是非比较排序算法，通过统计元素数量来实现排序，通常应用于**整数数组**。

计数排序的简单实现如下：

1. 遍历数组找出最大的数记为m，创建大小为m+1的辅助数组counter（0的存在）
2. 遍历数组，统计各数字的出现次数：遍历数组nums中的元素num，设置counter[num]的值，访问到便加1
3. 遍历counter数组各元素的次数，将大于1的索引按次数和顺序依次填入nums，最后得到排序好的数组

<img src="https://www.hello-algo.com/chapter_sorting/counting_sort.assets/counting_sort_overview.png">

> 计数排序本质是桶排序在整数数组下的一个特例：counter数组索引为一个桶，统计各数出现次数可以看做是将数据划分到各个桶中。

#### 完整实现

但上述简单实现有一个明显的缺点：假设一个商品对象数组，商品对象包含一个价格的属性，我们想要根据价格这个属性对商品对象进行排序。根据简单实现的步骤3，我们只能得到商品价格排序后的数组，因为不能通过商品价格得到原对象。

#### 前缀和

索引i处的前缀和prefix[i]等于counter数组前i个元素之和：

$$
\text{prefix}[i] = \sum_{j=0}^i \text{counter[j]}
$$

前缀和的意义：prefix[i]-1表示元素i在排序后数组中出现的最后索引，因此计数排序的完整实现如下：
1. 倒序遍历数组nums，因为前缀和是元素num出现的最后索引，所以倒序遍历可以保持数组的稳定性（对于对象来说，毕竟整数数组也不存在稳定排序一说）
2. 将num放入排序后数组res[prefix[num]-1]处，然后将其前缀和prefix[num]值-1
3. 重复步骤1和2，直到数组nums遍历完成

<img src="https://www.hello-algo.com/chapter_sorting/counting_sort.assets/counting_sort_step5.png">

#### 算法特性

- 时间复杂度为$O(n+m)，主要是遍历原数组nums和辅助数组counter，但n基本>>m，时间复杂度趋近于$O(n)$
- 空间复杂度为$O(n+m)$，非原地排序
- 稳定排序

计数排序只适用于**非负整数**数组，如果不满足条件则需要进行转换，排序完再转换回去。

计数排序只适用于**数据量大但数据范围小**，即n>>m。

```c++
void countingSortNaive(vector<int> &nums) {
    int m = 0;
    for(int num : nums)
        m = max(m, num);
    vector<int>counter(m + 1, 0);
    for(int num : nums)
        counter[num]++;
    int i = 0;
    for(int num = 0; num < m; num++){
        for(int j = 0; j < counter[i]; j++, i++)
            nums[i] = num;
    }
}

void countingSort(vector<int> &nums) {
    int m = 0;
    for(int num : nums)
        m = max(m, num);
    vector<int>counter(m + 1, 0);
    for(int num : nums)
        counter[num]++;
    for (int i = 0; i < m; i++){
        counter[i + 1] += counter[i];
    }
    vector<int>res(nums.size());
    for(int i = nums.size() - 1; i >= 0; i--){
        res[counter[nums[i]] - 1] = nums[i];
        counter[nums[i]] --;
    }
    nums = res;
}
```

### sqrt(double)

牛顿迭代法

```c++
double sqrt(double n) {
    const double eps = 1e-15;
    double x = 1;
    while (true) {
        double nx = (x + n / x) / 2;
        if (abs(x - nx) < eps) break;
        x = nx;
    }
    return x;
}
```

## 二叉树排序（迭代）

### 前序

中左右

用栈模拟，先让右子节点进入，再让左子节点进入

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stk;
        if (root)
            stk.push(root);
        while (!stk.empty()) {
            TreeNode* tmp = stk.top();
            stk.pop();
            if (tmp->right)
                stk.push(tmp->right);
            if (tmp->left)
                stk.push(tmp->left);
            res.push_back(tmp->val);
        }
        return res;
    }
};
```

### 后序遍历

左右中

只需简单修改前序遍历，中左右变成中右左，最后返回再反转即可

```c++
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stk;
        if (root)
            stk.push(root);
        while (!stk.empty()) {
            TreeNode* tmp = stk.top();
            stk.pop();
            res.push_back(tmp->val);
            if (tmp->left)
                stk.push(tmp->left);
            if (tmp->right)
                stk.push(tmp->right);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```

### 中序遍历

先一直往左遍历入栈直到为空，然后取出栈顶也就是最左边的节点，加入数组，再往右边开始遍历

```c++
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stk;
        while (root != nullptr || !stk.empty()) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            res.push_back(root->val);
            root = root->right;
        }
        return res;
    }
};
```

## 智能指针

### shared ptr

需要注意以下几个地方：

1. 计数器使用指针
2. 拷贝构造和拷贝赋值需要将计数器++
3. 析构的时候需要将计数器--，如果为0则删除指针和计数器指针
4. 移动构造和移动赋值需要将原来的指针和计数器置为nullptr

```c++
#include <atomic>

template <typename T>
class SharedPtr {
public:
    explicit SharedPtr(T* ptr = nullptr) : ptr_(ptr), ref_count_(new std::atomic<size_t>(1)) {
        if (!ptr) {
            *ref_count_ = 0;
        }
    }

    SharedPtr(const SharedPtr& other) : ptr_(other), ref_count_(other.ref_count_) {
        if (ptr_) {
            ++(*ref_count_);
        }
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != other) {
            release();
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            if (ptr_) {
                ++(*ref_count_);
            }
        }
        return *this;
    }

    SharedPtr(SharedPtr&& other) noexcept
        : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            ref_count_ = other.ref_count_;
            other.ptr_ = nullptr;
            other.ref_count_ = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

    T* get() const {
        return ptr_;
    }

    size_t use_count() const {
        return ref_count_ ? ref_count_->load() : 0;
    }

    ~SharedPtr() {
        release();
    }
private:
    void release() {
        if (ptr_ && ref_count_ && --(*ref_count_) == 0) {
            delete ptr_;
            delete ref_count_;
        }
    }
    T* ptr_;
    std::atomic<size_t>* ref_count_;
}
```

## 设计模式

### 单例模式

保证⼀个类、只有⼀个实例存在，同时提供能对该实例加以访问的全局访问⽅法。

#### 懒汉式

- **线程安全性**：C++11 及之后的标准保证了静态局部变量的初始化是线程安全的，因此你的实现是线程安全的。
- **懒汉式单例模式**：实例在第一次使用时才被创建，符合懒汉式单例模式的定义。

```c++
class mySingleton {
    private:
    	mySingleton(){};
    	mySingleton(const mySingleton&) = delete;
    	mySingleton& operator=(const mySingleton&) = delete;
   	public:
    	static mySingleton& getInstance() {
          	static mySingleton instance;
            return instance;
        };
};
```

#### 饿汉式

饿汉式单例模式则是在类加载时就创建实例，而不管是否有实际使用。饿汉式单例模式通常是通过在类的静态成员变量中直接实例化对象来实现的

```c++
class mySingleton{
    private:
    	mySingleton(){};
    	mySingleton(const mySingleton&) = delete;
    	mySingleton& operator=(const mySingleton&) = delete;
    	static mySingleton instance;
    public:
    	static mySingleton& getInstance() {
          	return instance;  
        };
};

mySingleton mySingleton::instance;
```

## C++

### c语言模拟c++继承

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 基类
typedef struct {
    char name[50];
    void (*printName)(void*);
} Base;

// 基类的方法
void basePrintName(void* self) {
    Base* base = (Base*)self;
    printf("Base name: %s\n", base->name);
}

// 基类的构造函数
Base* baseCreate(const char* name) {
    Base* base = (Base*)malloc(sizeof(Base));
    if (base) {
        strncpy(base->name, name, sizeof(base->name));
        base->printName = basePrintName;
    }
    return base;
}

// 基类的析构函数
void baseDestroy(Base* base) {
    free(base);
}

// 派生类
typedef struct {
    Base base;  // 基类部分
    int age;
    void (*printAge)(void*);
} Derived;

// 派生类的方法
void derivedPrintName(void* self) {
    Derived* derived = (Derived*)self;
    printf("Derived name: %s\n", derived->base.name);
}

void derivedPrintAge(void* self) {
    Derived* derived = (Derived*)self;
    printf("Derived age: %d\n", derived->age);
}

// 派生类的构造函数
Derived* derivedCreate(const char* name, int age) {
    Derived* derived = (Derived*)malloc(sizeof(Derived));
    if (derived) {
        // 初始化基类部分
        Base* base = baseCreate(name);
        if (base) {
            memcpy(&derived->base, base, sizeof(Base));
            free(base);
        }
        // 初始化派生类部分
        derived->age = age;
        derived->base.printName = derivedPrintName;
        derived->printAge = derivedPrintAge;
    }
    return derived;
}

// 派生类的析构函数
void derivedDestroy(Derived* derived) {
    free(derived);
}


int main() {
    // 创建基类对象
    Base* base = baseCreate("BaseObject");
    base->printName(base);

    // 创建派生类对象
    Derived* derived = derivedCreate("DerivedObject", 25);
    derived->base.printName(derived);
    derived->printAge(derived);

    // 销毁对象
    baseDestroy(base);
    derivedDestroy(derived);

    return 0;
}
```

### 手写vector

```c++
#include <iostream>
#include <stdexcept>

template<typename T>
class Vector {
public:
    Vector() : data(nullptr), sz(0), cap(0) {}

    ~Vector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (sz == cap) {
            resize();
        }
        data[sz++] = value;
    }

    void pop_back() {
        if (sz > 0) {
            --sz;
        }
    }

    T& operator[](size_t index) {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t size() const {
        return sz;
    }

    size_t capacity() const {
        return cap;
    }

private:
    void resize() {
        cap = (cap == 0) ? 1 : cap * 2;
        T* newData = new T[cap];
        for (size_t i = 0; i < sz; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    T* data;
    size_t sz;
    size_t cap;
};

int main() {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 手写string

```c++
#include <bits/stdc++.h>
using namespace std;

class myString {
private:
    char* data;
    size_t len;
public:
    myString() : data(new char[1]{'\0'}), len(0) {}

    myString(const char* str) {
        if (str == nullptr) {
            data = new char[1]{'\0'};
            len = 0;
        } else {
            len = strlen(str);
            data = new char[len + 1];
            strcpy(data, str);
        }
    }

    myString(const myString& other) {
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
    }

    myString& operator=(const myString& other) {
        if (this != &other) {
            delete[] data;
            len = other.len;
            data = new char[len + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    ~myString() {
        delete[] data;
    }

    void push_back(char c) {
        char* newData = new char[len + 2];
        for (size_t i = 0; i < len; ++i) {
            newData[i] = data[i];
        }
        newData[len] = c;
        newData[len + 1] = '\0';
        delete[] data;
        data = newData;
        ++len;
    }

    char& operator[](size_t index) {
        if (index >= len) {
            throw out_of_range("index out of range");
        }
        return data[index];
    }

    const char& operator[](size_t index) const {
        if (index >= len) {
            throw out_of_range("index out of range");
        }
        return data[index];
    }

    size_t size() const {
        return len;
    }

    const char* c_str() const {
        return data;
    }
};

int main() {
    myString str("Hello");
    str.push_back('!');
    cout << str.c_str() << endl; // 输出 "Hello!"

    myString str2 = str;
    cout << str2.c_str() << endl; // 输出 "Hello!"

    str2[0] = 'h';
    cout << str2.c_str() << endl; // 输出 "hello!"

    return 0;
}
```

## 多线程

### 生产者-消费者模式

单生产者单消费者

```c++
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

const size_t CAPACITY = 5;
std::queue<int> jobs;
std::mutex mtx;
std::condition_variable cv_producer;
std::condition_variable cv_consumer;
bool done = false;

void produce(int count) {
    for (int i = 1; i <= count; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_producer.wait(lock, [&]{return jobs.size() < CAPACITY;});
        jobs.push(i);
        std::cout << "Produced: " << i << std::endl;
        cv_consumer.notify_one();
    }
    std::unique_lock<std::mutex> lock(mtx);
    done = true;
    cv_consumer.notify_all();
}

void consume() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_consumer.wait(lock, [&]{return !jobs.empty() || done;});
        while (!jobs.empty()) {
            std::cout << "Consumed: " << jobs.front() << std::endl;
            jobs.pop();
            cv_producer.notify_one();
        }
        if (done && jobs.empty()) {
            break;
        }
    }
}

int main() {
    std::thread producer(produce, 10);
    std::thread consumer(consume);
    
    producer.join();
    consumer.join();
    
    return 0;
}
```

3个生产者2个消费者

```c++
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>

const size_t CAPACITY = 5;
std::queue<int> jobs;
std::mutex mtx;
std::condition_variable cv_producer;
std::condition_variable cv_consumer;
bool done = false;
int job_count = 0; // 用于标识生产的总任务数

void produce(int id, int count) {
    for (int i = 1; i <= count; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_producer.wait(lock, [&]{return jobs.size() < CAPACITY;});
        jobs.push(++job_count);
        std::cout << "Producer " << id << " produced: " << job_count << std::endl;
        cv_consumer.notify_one();
    }
    std::unique_lock<std::mutex> lock(mtx);
    done = true;
    cv_consumer.notify_all();
}

void consume(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_consumer.wait(lock, [&]{return !jobs.empty() || done;});
        while (!jobs.empty()) {
            std::cout << "Consumer " << id << " consumed: " << jobs.front() << std::endl;
            jobs.pop();
            cv_producer.notify_one();
        }
        if (done && jobs.empty()) {
            break;
        }
    }
}

int main() {
    int total_jobs = 10; // 总共要生产的任务数
    int jobs_per_producer = total_jobs / 3; // 每个生产者生产的任务数
    int remaining_jobs = total_jobs % 3; // 剩余任务数，由第一个生产者处理

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // 创建3个生产者线程
    for (int i = 0; i < 3; ++i) {
        int jobs_for_this_producer = jobs_per_producer + (i == 0 ? remaining_jobs : 0);
        producers.emplace_back(produce, i + 1, jobs_for_this_producer);
    }

    // 创建2个消费者线程
    for (int i = 0; i < 2; ++i) {
        consumers.emplace_back(consume, i + 1);
    }

    // 等待所有生产者线程完成
    for (auto& producer : producers) {
        producer.join();
    }

    // 设置 done 标志，通知所有消费者
    {
        std::unique_lock<std::mutex> lock(mtx);
        done = true;
    }
    cv_consumer.notify_all();

    // 等待所有消费者线程完成
    for (auto& consumer : consumers) {
        consumer.join();
    }

    return 0;
}
```

### 三个线程交替打印A,B,C

```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
std::atomic<int> index = 1;

void printChar(int id, char c) {
    for (int i = 0; i < 3; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]{return index == id;});
        std::cout << "Thread ID " << id << ": " << c << std::endl;
        index = (id) % 3 + 1;
        cv.notify_all();
    }
}

int main() {
    std::thread t1(printChar, 1, 'A');
    std::thread t2(printChar, 2, 'B');
    std::thread t3(printChar, 3, 'C');
    
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
```

### 两个线程交替打印奇数和偶数

```C++
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
std::atomic<int> index = 0;

void printChar(int id) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]{return (index & 1) == id;});
        std::cout << "Thread ID " << id << ": " << index << std::endl;
        ++index;
        cv.notify_one();
    }
}

int main() {
    std::thread t1(printChar, 0);
    std::thread t2(printChar, 1);

    t1.join();
    t2.join();
    return 0;
}
```

### 线程池

如果要异步获得结果就需要使用`future`了

```c++
#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <vector>
#include <condition_variable>
#include <functional>

class ThreadPool {
public:
    ThreadPool(size_t capacity);
    ~ThreadPool();
    void addJob(std::function<void()> job);
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> jobs;
    std::mutex mtx;
    std::condition_variable cv;
    bool done;
};

ThreadPool::ThreadPool(size_t capacity) : done(false) {
    for (int i = 0; i < capacity; ++i) {
        workers.emplace_back([this]{
           while (true) {
              std::function<void()> job;
              {
                   std::unique_lock<std::mutex> lock(this->mtx);
                   this->cv.wait(lock, [this]{return this->done || !this->jobs.empty();});
                   if (this->done && this->jobs.empty())
                       return;
                   job = std::move(jobs.front());
                   jobs.pop();
              }
              job();
           }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();
    for (int i = 0; i < workers.size(); ++i) {
        workers[i].join();
    }
}

void ThreadPool::addJob(std::function<void()> job) {
    {
        std::unique_lock<std::mutex> lock(mtx);
        jobs.emplace(job);
    }
    cv.notify_one();
}

int main() {
    ThreadPool pool(3);

    pool.addJob([] { std::cout << "Task 1" << std::endl; });
    pool.addJob([] { std::cout << "Task 2" << std::endl; });
    pool.addJob([] { std::cout << "Task 3" << std::endl; });

    return 0;
}
```

