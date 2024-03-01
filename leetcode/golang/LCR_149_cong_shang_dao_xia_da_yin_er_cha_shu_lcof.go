// https://leetcode.cn/problems/cong-shang-dao-xia-da-yin-er-cha-shu-lcof/description

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
    vector<int> decorateRecord(TreeNode* root) {
        queue<TreeNode*> st;
        vector<int> res;
        if (root != nullptr)
            st.push(root);
        else 
            return {};
        while (!st.empty()) {
            TreeNode* node = st.front();
            st.pop();
            res.push_back(node->val);
            if (node->left != nullptr)
                st.push(node->left);
            if (node->right != nullptr)
                st.push(node->right);
        }
        return res;
    }
};

// 层次遍历，O(n)，O(n)