// https://leetcode.cn/problems/validate-binary-search-tree

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
    void dfs(TreeNode* root, vector<int>& nums) {
        if (root == nullptr)
            return;
        dfs(root->left, nums);
        nums.push_back(root->val);
        dfs(root->right, nums);
    }
    bool count(vector<int>& nums) {
        for (int i = 0; i < nums.size()-1; i++) {
            if (nums[i] == nums[i+1])
                return false;
        }
        return true;
    }
    bool isValidBST(TreeNode* root) {
        vector<int> nums;
        dfs(root, nums);
        vector<int> sort_nums(nums);
        sort(nums.begin(), nums.end());
        return (nums == sort_nums) && count(sort_nums);
    }
};

// 第一次写出来的方法，有点蠢hhh
// 方法也很简单，每次需要记录前一个节点就好了，然后利用中序遍历有序的特点进行求解
// 时间复杂度为O(O)，空间复杂度为O(n)

class Solution {
public:
    bool dfs(TreeNode* node, TreeNode*& pre) {
        if (node == nullptr)
            return true;
        if (!dfs(node->left, pre))
            return false;
        if (pre != nullptr && pre->val >= node->val)
            return false;
        pre = node;
        return dfs(node->right, pre);
    }
    bool isValidBST(TreeNode* root) {
        TreeNode* pre = nullptr;
        return dfs(root, pre);
    }
};
