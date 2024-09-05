/*
 * @lc app=leetcode.cn id=329 lang=cpp
 *
 * [329] 矩阵中的最长递增路径
 */

# include<vector>
# include<algorithm>
#include <iostream>

using namespace std;

// @lc code=start
class Solution {
public:
    struct land{
        int height;
        int hang;
        int lie;
        // int max_l = 1;
    };
    static bool cmp(land x, land y){
        return x.height < y.height;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        land lands[m*n];
        int id = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                lands[id].height = matrix[i][j];
                lands[id].hang = i;
                lands[id].lie = j;
                id++;
            }
        }
        sort(lands, lands + id, cmp);
        // vector<int> line(n, 1);
        vector<vector<int>> max_l_road(m, vector<int>(n, 1));
        for(int i = 0; i < id; i++){
            int hang = lands[i].hang;
            int lie = lands[i].lie;
            if((hang + 1) < m && matrix[hang + 1][lie] > matrix[hang][lie]) max_l_road[hang + 1][lie] = max(max_l_road[hang + 1][lie], (max_l_road[hang][lie] + 1));
            if((lie + 1) < n && matrix[hang][lie + 1] > matrix[hang][lie]) max_l_road[hang][lie + 1] = max(max_l_road[hang][lie + 1], (max_l_road[hang][lie] + 1));
            if((hang - 1) >= 0 && matrix[hang - 1][lie] > matrix[hang][lie]) max_l_road[hang - 1][lie] = max(max_l_road[hang - 1][lie], (max_l_road[hang][lie] + 1));
            if((lie - 1) >= 0 && matrix[hang][lie - 1] > matrix[hang][lie]) max_l_road[hang][lie - 1] = max(max_l_road[hang][lie - 1], (max_l_road[hang][lie] + 1));
            cout <<"height"<< lands[i].height <<" " << max_l_road[hang][lie] << endl;
        }
        int max_l_max = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(max_l_road[i][j] > max_l_max) max_l_max = max_l_road[i][j];
            }
        }
        return max_l_max;
    }
};
// @lc code=end

