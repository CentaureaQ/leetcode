/*
 * @lc app=leetcode.cn id=207 lang=cpp
 *
 * [207] 课程表
 */

// @lc code=start
#include<vector>
using namespace std;
// 参考思路：https://zhuanlan.zhihu.com/p/408887993
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 其实这题的意思是，如果选修了某门课a，这门课需要先修课b，那么你在选修a的时候要保证已经选过b
        // 需要保证不能有环
        // 已经保证了prerequisites[i] = [ai, bi]中的0 <= ai, bi < numCourses
        // 所以所有先修课都是要修的，只需要保证没有环就可以

    }
};
// @lc code=end

