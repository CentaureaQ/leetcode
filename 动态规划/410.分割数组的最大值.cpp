/*
 * @lc app=leetcode.cn id=410 lang=cpp
 *
 * [410] 分割数组的最大值
 */
#include<vector>
#include<algorithm>
#include <string.h>
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        // 前i个数分成j个的最大数组的最小值：dp[i][j]
        // dp[i][j] = min(dp[i][j], max(dp[i-k][j-1], 其中最后k个数组成的一组的值)) 【k分别=1到i】
        int l = nums.size(); // l <= 1000
        cout<< l << endl;
/*         vector<int> sum_num;
        sum_num.push_back(nums[0]);
        for(int i = 1; i < l; i++){
            sum_num.push_back(sum_num[i-1] + nums[i]);
        } */
        int sum_num[1010];
        memset(sum_num, 0, sizeof(sum_num));
        sum_num[0] = nums[0];
        for(int i = 1; i < l; i++){
            sum_num[i] = (sum_num[i-1] + nums[i]);
        } 
        //int dp[1010][60];
        vector<vector<int>> dp(1010, vector<int>(60, 10000000));
        //memset(dp, 1000000, sizeof(dp));
        // dp[0][1] = nums[0]; // 动态规划要把这些开头的基础状态提前初始化好
        for(int i = 0; i < l; i++){
            dp[i][1] = sum_num[i];
        }
        for(int i = 1; i < l; i++){
            int x = min(i + 1, k);
            for(int j = 2; j <= x; j++){ 
                cout << "i: j = "<< i << ", " << j << endl;
                for(int k0 = 1; k0 <= i - j + 2; k0++){
                    dp[i][j] = min(dp[i][j], max(dp[i-k0][j-1], (sum_num[i] - sum_num[i - k0])));
                }
            }
        }
/*         for(int i = 0; i < 5; i++){
            for(int j  =1; j < 5; j++){
                cout << "dp (" << i << ", " << j << ") " << dp[i][j] << endl;
            }
        } */
        return dp[l-1][k];

    }
};
// @lc code=end

