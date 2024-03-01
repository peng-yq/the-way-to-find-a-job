// https://leetcode.cn/problems/cong-shang-dao-xia-da-yin-er-cha-shu-ii-lcof/description

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
        vector<vector<int>> res;
        queue<TreeNode*> que;
        if (root == nullptr)
            return res;
        que.push(root);
        while (!que.empty()) {
           int i = que.size();
           vector<int> array;
           while (i--) {
                TreeNode* tmp = que.front();
                que.pop();
                if (tmp->left != nullptr)
                    que.push(tmp->left);
                if (tmp->right != nullptr)
                    que.push(tmp->right);
                array.push_back(tmp->val);
           }
           res.push_back(array);
        }
        return res;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)