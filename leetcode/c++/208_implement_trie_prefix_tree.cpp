// https://leetcode.cn/problems/implement-trie-prefix-tree

#include <bits/stdc++.h>
using namespace std;

class TrieNode {
    public:
        vector<TrieNode*> tree;
        bool isEnd;
        TrieNode() : tree(26, nullptr), isEnd(false) {};
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for (auto ch : word) {
            if (node->tree[ch - 'a'] == nullptr) {
                node->tree[ch - 'a'] = new TrieNode();
            }
            node = node->tree[ch-'a'];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        TrieNode* node = root;
        for (auto ch : word) {
            if (node->tree[ch - 'a'] == nullptr)
                return false;
            node = node->tree[ch - 'a'];
        }
        return node->isEnd;
    }
    
    bool startsWith(string prefix) {
         TrieNode* node = root;
        for (auto ch : prefix) {
            if (node->tree[ch - 'a'] == nullptr)
                return false;
            node = node->tree[ch - 'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

// 前缀树，相比于set，哈希表更加节约空间和时间。
// 高效的前缀搜索：由于每个节点都代表了一条从根到当前节点的路径，即一个字符串的前缀，因此在检查一个前缀是否存在时非常高效。
// 空间效率：相比于存储大量完整单词的哈希表，Trie结构只存储字符，且共享公共前缀。这在存储大量具有相同前缀的单词时更加空间高效。
/*
    root
    /  \
   c    d
  /      \
 a        o
/ \        \
t   r        g
*/