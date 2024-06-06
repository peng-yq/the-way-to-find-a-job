// https://leetcode.cn/problems/count-pairs-of-connectable-servers-in-a-weighted-tree-network

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int signalSpeed) {
        int n = edges.size() + 1;
        vector<vector<pair<int, int>>> tree(n);
        vector<int> res(n);
        for (auto& edge : edges) {
            int x = edge[0], y = edge[1], z = edge[2];
            tree[x].push_back({y, z});
            tree[y].push_back({x, z});
        }
        function<int(int, int, int)> dfs = [&](int x, int fa, int sum)->int {
            int cnt = sum % signalSpeed == 0;
            for (auto& [y, z] : tree[x]) {
                if (y != fa) {
                    cnt += dfs(y, x, sum + z);
                }
            }
            return cnt;
        };
        for (int i = 0; i < n; ++i) {
            if (tree[i].size() == 1)
                continue;
            int sum = 0;
            for (auto& [y, z] : tree[i]) {
                int cnt = dfs(y, i, z);
                res[i] += sum * cnt;
                sum += cnt;
            }
        }
        return res;
    }
};

// 题目中对连通的描述比较啰嗦：
/*
如果两个服务器 a ，b 和 c 满足以下条件，那么我们称服务器 a 和 b 是通过服务器 c 可连接的 ：

a < b ，a != c 且 b != c 。
从 c 到 a 的距离是可以被 signalSpeed 整除的。
从 c 到 b 的距离是可以被 signalSpeed 整除的。
从 c 到 b 的路径与从 c 到 a 的路径没有任何公共边。
*/
// 翻译一下其实就是我们把c看作树的根节点，a和b位于其不同的分支/子树中（只有c这一个共同祖先节点）
// 并且a到c和b到c的距离是可以被signalspeed整除的，至于a<b，也就是说{a, b}和{b, a}只取一对，也就是排列组合中的C
// 加入c的子树中有3个满足条件，3个子树中分别有2，3，4个节点满足路径要求；那么c的连接数为2 * 3 + 4 * (2 + 3) = 26
// vector<vector<pair<int, int>>> tree(n); 因为节点都是0到n-1，使用tree统计每个节点的邻居和到它的距离
// dfs(x, x, z)用于求解x节点的邻居中（及其邻居，也就是子树中的所有节点）满足题目条件的节点数目
/* for (auto& [y, z] : tree[i]) {
        int cnt = dfs(y, i, z);
        res[i] += sum * cnt;
        sum += cnt;
    }
用于求解i的邻居中每个邻居中满足条件的节点数，再相乘即可
*/

// 因为节点只有1000个，可以这样搞，时间复杂度为O(n^2)，空间复杂度为O(n)