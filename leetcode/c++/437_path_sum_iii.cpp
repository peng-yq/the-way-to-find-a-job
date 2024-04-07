// https://leetcode.cn/problems/path-sum-iii

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),right(right) {}
};

class Solution {
private:
    int res = 0;
public:
    void dfs(TreeNode* root, long long targetSum) {
        if (root == nullptr)
            return;
        if (targetSum - root->val == 0)
            res++;
        dfs(root->left, targetSum - root->val);
        dfs(root->right, targetSum - root->val);
    }
    void doubleDfs(TreeNode* root, int targetSum) {
        if (root == nullptr)
            return;
        dfs(root, (long long)targetSum);
        doubleDfs(root->left, (long long)targetSum);
        doubleDfs(root->right, (long long)targetSum);
    }
    int pathSum(TreeNode* root, int targetSum) {
        doubleDfs(root, targetSum);
        return res;
    }
};

// 双重递归法，O(n^2)，O(n)
// 前缀和解法，O(n)，O(n)

class Solution {
private:
    int res;
    void dfs(TreeNode* root, long long targetSum, long long curSum, unordered_map<long long, int>& presum) {
        if (root == nullptr)
            return;
        curSum += root->val;
        if (presum.contains(curSum - targetSum))
            res += presum[curSum - targetSum];
        presum[curSum]++; // 注意这里要在后面刷新，以规避targetSum = 0的情况
        dfs(root->left, targetSum, curSum, presum);
        dfs(root->right, targetSum, curSum, presum);
        presum[curSum]--;
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        res = 0;
        unordered_map<long long, int> presum;
        presum[0] = 1;
        dfs(root, (long long)targetSum, 0ll, presum);
        return res;
    }
};