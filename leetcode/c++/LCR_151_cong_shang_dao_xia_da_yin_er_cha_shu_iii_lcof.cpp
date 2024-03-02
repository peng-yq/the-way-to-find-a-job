// https://leetcode.cn/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof

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
    vector<vector<int>> decorateRecord(TreeNode* root) {
        if (root == nullptr)
            return {};
        vector<vector<int>> res;
        queue<TreeNode*> que;
        que.push(root);
        bool flag = true;
        while (!que.empty()) {
            int num = que.size();
            vector<int> tmp(num);
            for (int i = 0; i < num; i++) {
                TreeNode* node = que.front();
                if (flag)
                    tmp[i] = node->val;
                else
                    tmp[num-i-1] = node->val;
                que.pop();
                if (node->left != nullptr)
                    que.push(node->left);
                if (node->right != nullptr)
                    que.push(node->right);
            }
            res.push_back(tmp);
            flag = !flag;
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)