// https://leetcode.cn/problems/er-cha-shu-de-shen-du-lcof/description

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
    int calculateDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        return max(calculateDepth(root->left), calculateDepth(root->right)) + 1;
    }
};

// DFS，时间复杂度为O(n)，空间复杂度为O(n)，没有BFS快