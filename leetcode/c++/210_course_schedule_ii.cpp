// https://leetcode.cn/problems/course-schedule-ii

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> inDegree(numCourses), res;
        unordered_map<int, vector<int>> numMap;
        for (int i = 0; i < prerequisites.size(); ++i) {
            ++inDegree[prerequisites[i][0]];
            numMap[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
        queue<int>q;
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0)
                q.push(i);
        }
        int count = 0;
        while (!q.empty()) {
            int tmp = q.front();
            q.pop();
            ++count;
            res.push_back(tmp);
            for (int i = 0; i < numMap[tmp].size(); ++i) {
                if (inDegree[numMap[tmp][i]] > 0) {
                    if (--inDegree[numMap[tmp][i]] == 0)
                        q.push(numMap[tmp][i]);
                }
            }
        }
        if (count == numCourses)
            return res;
        else 
            return {};
    }
};

// 时间复杂度和空间复杂度都是O(n+m)，n是课程数量，m是边的数量
// 拓扑排序（Topological Sorting）是一种用于有向无环图（DAG, Directed Acyclic Graph）的排序算法。
// 它将图中的所有顶点排成一个线性序列，使得对于图中的每一条有向边 ( (u, v) )，顶点 ( u ) 在序列中出现在顶点 ( v ) 之前。