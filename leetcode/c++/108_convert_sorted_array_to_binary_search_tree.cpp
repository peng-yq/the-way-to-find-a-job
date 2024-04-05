// https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree

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
    TreeNode* dfs(vector<int>& nums, int i, int j) {
        if (i > j || i < 0 || j > nums.size()-1)
            return nullptr;
        int mid = i + (j - i) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = dfs(nums, i, mid-1);
        root->right = dfs(nums, mid+1, j);
        return root;
    } 
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return dfs(nums, 0, nums.size()-1);
    }
};

// 由于是升序的，每次取中间那个作为根节点，就能保证平衡了
// 时间复杂度为O(n)，空间复杂度为O(logn)