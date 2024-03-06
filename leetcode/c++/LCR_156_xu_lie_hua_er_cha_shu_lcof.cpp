// https://leetcode.cn/problems/xu-lie-hua-er-cha-shu-lcof/description

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == NULL)
            return "[]";
        string res = "[";
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            TreeNode* node = que.front();
            que.pop();
            if (node != NULL) {
                res += to_string(node->val) + ',';
                que.push(node->left);
                que.push(node->right);
            } else {
                res += "null,";
            }           
        }
        res.pop_back();
        res += ']';
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "[]")
            return NULL;
        data = data.substr(1, data.length() - 2);
        data += ',';
        vector<string> nodes;
        int i = 0, j = 0;
        while (i < data.length()) {
            j = i;
            while(data[i] != ',')
                i++;
            nodes.push_back(data.substr(j, i-j));
            i++;
        }
        TreeNode* root = new TreeNode(stoi(nodes[0]));
        queue<TreeNode*>que;
        que.push(root);
        i = 1;
        while (!que.empty()) {
            TreeNode* node = que.front();
            que.pop();
            if (nodes[i] != "null") {
                node->left = new TreeNode(stoi(nodes[i]));
                que.push(node->left);
            }
            i++;
            if (nodes[i] != "null") {
                node->right = new TreeNode(stoi(nodes[i]));
                que.push(node->right);
            }
            i++;
        }
        return root;
    }
};

// 时间复杂度为O(n)，空间复杂度为O(n)，都是BFS