// https://leetcode.cn/problems/binary-tree-right-side-view

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
    void dfs(TreeNode* root, vector<int>& res, int height) {
        if (root == nullptr)
            return;
        if (height == res.size()) 
            res.push_back(root->val);
        dfs(root->right, res, height+1);
        dfs(root->left, res, height+1);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int>res;
        dfs(root, res, 0);
        return res;
    }   
};

// bfs和dfs都能做出来，bfs就是每一层最后一个添加到数组中；dfs就是根节点，右子节点，左子节点这样递归，第一次到这个高度时就添加进数组
// 时间复杂度和空间复杂度两者都是O(n)