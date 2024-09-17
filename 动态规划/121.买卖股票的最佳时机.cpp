/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // max(后项值 - 前项值)
        // a[i] 以第i项结尾，其之前的数的值的最小值
        int l = prices.size();
        vector<int> a(l);
        a[0] = prices[0];
        for(int i = 1; i < l; i++){
            a[i] = min(prices[i], a[i-1]);
        }
        int max_incom = 0;
        for(int i = 0; i < l; i++){
            max_incom = max(max_incom, prices[i] - a[i]);
        }
        return max_incom;
    }
};
// @lc code=end

