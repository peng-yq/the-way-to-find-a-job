// https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/description

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        deque<TreeNode*> que;
        vector<vector<int>>res;
        if (root != nullptr) que.push_back(root);
        int flag = 1;
        while (!que.empty()) {
            vector<int> tmp;
            for (int i = que.size(); i > 0; i--) {
                if (flag % 2 == 0) {
                    TreeNode* tmp_node = que.back();
                    que.pop_back();
                    tmp.push_back(tmp_node->val);
                    if (tmp_node->right != nullptr) que.push_front(tmp_node->right);
                    if (tmp_node->left != nullptr) que.push_front(tmp_node->left);
                } else {
                    TreeNode* tmp_node = que.front();
                    que.pop_front();
                    tmp.push_back(tmp_node->val);
                    if (tmp_node->left != nullptr) que.push_back(tmp_node->left);
                    if (tmp_node->right != nullptr) que.push_back(tmp_node->right);
                }
            }
            res.push_back(tmp);
            flag++;
        }
        return res;
    }
};

//时间复杂度和空间复杂度都为O(n)