// https://leetcode.cn/problems/amount-of-time-for-binary-tree-to-be-infected

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    unordered_set<TreeNode*> visited;
    unordered_map<TreeNode*, TreeNode*> parent;
    TreeNode* startNode = nullptr;
public:
    void dfs(TreeNode* node, int start) {
        if (!node) return;
        if (node->val == start) {
            startNode = node;
            return;
        }
        if (node->left) {
            parent[node->left] = node;
            dfs(node->left, start);
        }
        if (node->right) {
            parent[node->right] = node;
            dfs(node->right, start);
        }
    }
    int amountOfTime(TreeNode* root, int start) {
        dfs(root, start);
        int time = 0;
        queue<TreeNode*> q;
        q.push(startNode);
        visited.insert(startNode);
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left && !visited.count(node->left)) {
                    q.push(node->left);
                    visited.insert(node->left);
                }
                if (node->right && !visited.count(node->right)) {
                    q.push(node->right);
                    visited.insert(node->right);
                }
                if (parent[node] && !visited.count(parent[node])) {
                    q.push(parent[node]);
                    visited.insert(parent[node]);
                }
            }
            if (!q.empty()) time++;
        }
        return time;
    }
};

// 模拟+BFS（好像叫建图），联想到图里面的一道题腐烂橘子
// 使用一个哈希表，保存每个节点的父节点，首先通过DFS遍历一遍树，
// 找到开始的感染节点，以及保存每个节点的父节点（找到了感染节点可以提前停止递归）
// 然后就是从感染点开始，bfs模拟感染过程了，注意每一轮有感染的才增加时间，也就是最后通过队列是否为空来判断
// 时间复杂度为O(n)，空间复杂度为O(n)