// https://leetcode.cn/problems/course-schedule/description

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> in_degree(numCourses);
        unordered_map<int, vector<int>> num_map;
        for (int i = 0; i < prerequisites.size(); i++) {
            in_degree[prerequisites[i][0]]++;
            num_map[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
        queue<int> num_que;
        for (int i = 0; i < numCourses; i++) {
            if (in_degree[i] == 0) num_que.push(i);
        }
        int count = 0;
        while (!num_que.empty()) {
            int tmp = num_que.front();
            num_que.pop();
            count++;
            for (int i = 0; i < num_map[tmp].size(); i++) {
                if (in_degree[num_map[tmp][i]] > 0) {
                    if (--in_degree[num_map[tmp][i]] == 0) num_que.push(num_map[tmp][i]);
                }
            }
        }
        return count == numCourses? true : false; 
    }
};

// 时间复杂度和空间复杂度都为O(n+m)，n和m分别为点和边的数量
// 这道题本质是在判断是否构成有向无环图（DAG），先统计每个点的入度和出度（这里入度只需统计数量即可，出度需要统计具体的节点）
// BFS使用队列，首先将入度为0的节点入队，这些也是最开始的节点
// 队列不为空时，出队节点（表示这个课程可以上），然后将其所有出度节点的入度减一（表示前置课程减少一个）
// 如果其出度节点的入度为0了则将其加入队列，最后判断出队的数量是否等于课程数量