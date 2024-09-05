/*
 * @lc app=leetcode.cn id=300 lang=cpp
 *
 * [300] 最长递增子序列
 */
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


// @lc code=start
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int l = nums.size();
        // cout << l << endl;
        vector<int> MaxLenth_nums(l, 1); // 以nums中某个数为截止的最长递增子序列长度
        for(int i = 0; i < l; i++){
            for(int j = 0; j < i; j++){
                if(nums[j] < nums[i]){
                    int maybe_answer = MaxLenth_nums[j] + 1; // 有可能被选中成“以这个数为结尾的最长递增子序列”的前项
                    if(maybe_answer > MaxLenth_nums[i])
                        MaxLenth_nums[i] = maybe_answer;
                }
            }
        }
        auto maxPosition = max_element(MaxLenth_nums.begin(), MaxLenth_nums.end());
        return *maxPosition;
    }

};
// @lc code=end

