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