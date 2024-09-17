/*
 * @lc app=leetcode.cn id=207 lang=cpp
 *
 * [207] 课程表
 */

// @lc code=start
#include<vector>
using namespace std;
class Solution {
public:
vector<vector<int>> preCourses;// preCourses[i]代表着课程i需要的先修课们，preCourses[i]是一个vector
int have_visited[2001];
bool has_ring = 0;
void visit_pre_course(int pre_course){
    int ll = preCourses[pre_course].size();
    for(int i = 0; i < ll; i++){
        if(have_visited[preCourses[pre_course][i]] == 1){
            has_ring = 1;
            return;
        }
        have_visited[preCourses[pre_course][i]] = 1;
        visit_pre_course(preCourses[pre_course][i]);
        have_visited[preCourses[pre_course][i]] = 0;
    }
}
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 其实这题的意思是，如果选修了某门课a，这门课需要先修课b，那么你在选修a的时候要保证已经选过b
        // 需要保证不能有环
        // 已经保证了prerequisites[i] = [ai, bi]中的0 <= ai, bi < numCourses
        // 所以所有先修课都是要修的，只需要保证没有环就可以
        // 先修课组成一个有向图，使用邻接矩阵储存
        int l = prerequisites.size();
        // 邻接矩阵储存
        preCourses.resize(2000);
        for(int i = 0; i < l; i++){
            // prerequisites[i] 是第i组先修课程对
            // 学prerequisites[i][0]必须先修prerequisites[i][1]
            preCourses[prerequisites[i][0]].push_back(prerequisites[i][1]);
        } 
        // 是否有环？
        // 考虑对每一个先修课进行深度搜索检查是否有环，但是Time Limit Exceeded
        for(int i = 0; i < numCourses; i++){// 课程编号从0开始
            int l_preCourse = preCourses[i].size();
            have_visited[i] = 1;// 第i门课，考虑它的先修是否有环
            for(int j = 0; j < l_preCourse; j++){
                have_visited[preCourses[i][j]] = 1;
                visit_pre_course(preCourses[i][j]);
                if(has_ring == 1){
                    return false;
                }
                have_visited[preCourses[i][j]] = 0;
            }
            have_visited[i] = 0;
        }
        return true;
    }
};
// @lc code=end

