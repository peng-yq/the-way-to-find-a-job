// https://leetcode.cn/problems/minimum-genetic-mutation

class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        auto check = [](const string& s1, const string& s2)->int {
            int res = 0;
            for (int i = 0; i < 8; ++i) {
                if (s1[i] != s2[i])
                    ++res;
            }
            return res;
        };
        int res = INT_MAX;
        unordered_map<string, int> visited;
        function<void(const string&, int)> dfs = [&](const string& node, int count) {
            if (node == endGene) {
                res = min(res, count);
                return;
            }
            if (visited[node]++) return;
            for (auto& str : bank) {
                if (check(str, node) == 1) {
                    dfs(str, count + 1);
                }
            }
            visited[node] = 0;
        };
        dfs(startGene, 0);
        return res == INT_MAX? -1 : res;
    }
};

// 由于一次基因变化就意味着这个基因序列中的一个字符发生了变化，并且另有一个基因库 bank 记录了所有有效的基因变化，只有基因库中的基因才是有效的基因序列。
// 因此依次去匹配bank中的所有字符串，如果只差一个字符，就加入变化序列，同时用一个哈希表标记已经被访问过
// 如果变换到最终基因则更新最小变化长度
// 时间复杂度为O(n^2)，空间复杂度最大递归深度为O(n)，n为bank大小