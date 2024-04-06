// https://leetcode.cn/problems/flatten-binary-tree-to-linked-list

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
    void dfs(TreeNode* root, vector<TreeNode*>& nodes) {
        if (root == nullptr) 
            return;
        nodes.push_back(root);
        dfs(root->left, nodes);
        dfs(root->right, nodes);
    } 
    void flatten(TreeNode* root) {
        if (root == nullptr)
            return;
        vector<TreeNode*> nodes;
        dfs(root, nodes);
        for (int i = 0; i < nodes.size() - 1; i++) {
            nodes[i]->left = nullptr;
            nodes[i]->right = nodes[i+1];
        }
        nodes[nodes.size()-1]->right = nullptr;
    }
};

// 蠢办法，空间复杂度和时间复杂度都为O(n)，其实也挺快的

class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* cur = root;
        while (cur != nullptr) {
            if (cur->left != nullptr) {
                TreeNode* pre = cur->left;
                while (pre->right != nullptr) {
                    pre = pre->right;
                }
                pre->right = cur->right;
                cur->right = cur->left;
                cur->left = nullptr;
            }
            cur = cur->right;
        }
    }
};

// 时间复杂度为O(n)，空间复杂度为O(1)
// 把左子树的最右边的节点连接到当前根节点的右节点，再把左子树移到当前根节点的右节点，然后左节点为空，再迭代到右节点（之前的左节点）
// 也就是先序遍历

