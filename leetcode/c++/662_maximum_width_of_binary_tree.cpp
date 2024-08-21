// https://leetcode.cn/problems/maximum-width-of-binary-tree

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (root == nullptr)
            return 0;
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({root, 1ll});
        int res = 1;
        while (!q.empty()) {
            int n = q.size();
            unsigned long long left = q.front().second, right = q.back().second;
            res = max(res, static_cast<int>(right - left + 1));
            for (int i = 0; i < n; ++i) {
                TreeNode* tmp = q.front().first;
                unsigned long long index = q.front().second;
                q.pop();
                if (tmp->left)
                    q.push({tmp->left, 2 * index});
                if (tmp->right)
                    q.push({tmp->right, 2 * index + 1});
            }
        }
        return res;
    }
};


// 给每个节点编号再层序遍历即可