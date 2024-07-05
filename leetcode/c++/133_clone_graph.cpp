// https://leetcode.cn/problems/clone-graph

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr)
            return node;
        unordered_map<Node*, Node*> choose;
        function<Node*(Node*)> dfs = [&](Node* root)->Node*{
            if (choose.count(root))
                return choose[root];
            Node* tmp = new Node(root->val);
            choose[root] = tmp;
            for (auto neighbor : root->neighbors)
                tmp->neighbors.push_back(dfs(neighbor));
            return tmp;
        };
        return dfs(node);
    }
};

// dfs实现深拷贝，