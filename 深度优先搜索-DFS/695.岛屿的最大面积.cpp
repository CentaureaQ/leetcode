/*
 * @lc app=leetcode.cn id=695 lang=cpp
 *
 * [695] 岛屿的最大面积
 */
#include<vector>
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    int next_step[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int m, n;
    void dfs(int x, int y, int & island, vector<vector<int>>& grid){
        grid[x][y] = 0;
        island++;
        for(int i = 0; i < 4; i++){
            int x1 = x + next_step[i][0];
            int y1 = y + next_step[i][1];
            if(x1>=0 && x1<m && y1>=0 && y1<n){
                // valid [x1][y1]
                if(grid[x1][y1] == 0) continue;
                else dfs(x1, y1, island, grid);
            }
        }
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        
        int island = 0;
        int max_island = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 0) continue;
                else{
                    island = 0;
                    //cout<< "============="<< endl;
                    dfs(i, j, island, grid);
                    //cout << "island: "<<island<<endl;

                    if(island > max_island) max_island = island;
                }
            }
        }
        return max_island;
    }
};
// @lc code=end

