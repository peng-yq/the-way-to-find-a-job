// https://leetcode.cn/problems/serialize-and-deserialize-binary-tree

#include<bits/stdc++.h>
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
            TreeNode* tmp = que.front();
            que.pop();
            if (tmp != NULL) {
                res += to_string(tmp->val) + ",";
                que.push(tmp->left);
                que.push(tmp->right);
            } else{
                res += "null,";
            }
        }
        res.pop_back();
        res += "]";
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data == "[]")
            return NULL;
        string str = data.substr(1, data.length() - 2);
        stringstream ss(str);
        string item;
        vector<string> val;
        while(getline(ss, item, ',')) val.push_back(item);
        TreeNode* root = new TreeNode(stoi(val[0]));
        queue<TreeNode*> que;
        que.push(root);
        int i = 1;
        while (!que.empty()) {
            TreeNode* tmp = que.front();
            que.pop();
            if (val[i] != "null") {
                tmp->left = new TreeNode(stoi(val[i]));
                que.push(tmp->left);
            }
            i++;
            if (val[i] != "null") {
                tmp->right = new TreeNode(stoi(val[i]));
                que.push(tmp->right);
            }
            i++;
        }
        return root;
    }
};

// 时间复杂度和空间复杂度两个函数都是O(n)，stringstream的使用