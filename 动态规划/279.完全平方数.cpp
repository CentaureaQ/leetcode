/*
 * @lc app=leetcode.cn id=279 lang=cpp
 *
 * [279] 完全平方数
 */

// @lc code=start
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
class Solution {
public:
    int numSquares(int n) {
        // 把number[i]代表和为i的完全平方数的最小数量
        int max_q = sqrt(n);// 组成n的最大的平方数为max_q的平方
        vector<int> number(n+1, INT_MAX);
        number[0] = 0;
        //number[1] = 1; 
        //number[2] = 2;
        for(int i = 1; i <= n; i++){
            int max_j = sqrt(i);
            for(int j = 1; j <= max_j; j++){
                number[i] = min(number[i - j*j] + 1, number[i]);
            }
        }
        return number[n]; 
    }
};
// @lc code=end

