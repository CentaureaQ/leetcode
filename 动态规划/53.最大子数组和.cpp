/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // 使用a[i]表示以i为终点的最大子数组？
        // 这样可以保证一个连续性
        int l = nums.size();
        vector<int> max_sum(l, 0);
        max_sum[0] = nums[0];
        for(int i = 1; i < l; i++){
            max_sum[i] = max(nums[i], nums[i] + max_sum[i-1]);
        }
        int result = -10001;
        for(int i = 0; i < l; i++){
            result = max(result, max_sum[i]);
        }
        return result;
    }
};
// @lc code=end

