/*
 * @lc app=leetcode.cn id=51 lang=cpp
 *
 * [51] N 皇后
 */
#include <vector>
#include <string>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solution;
        vector<string> moren(n, ".");
        vector<vector<string>> res(n, moren);
        int sum_solution = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                res[i][j] = ".";
            }
        }
        NQueen(0, n, res, solution, sum_solution);
        return solution;
    }
    void NQueen(int k, int n, vector<vector<string>> & res, vector<vector<string>> & solution, int & sum_solution){
        if(k == n){ // 最后的截止情况
            vector<string> one_result;
            for(int w0 = 0; w0 < n; w0++){
                string line;
                for(int w1 = 0; w1 < n; w1++){
                    line += res[w0][w1]; // res是棋局
                }
                one_result.push_back(line);
            }
            solution.push_back(one_result);
        }
        for(int i = 0; i < n; i++){ // 遍历第k行寻找这一行的皇后位置，i列
            bool shuxianOK = 1, xiexianOK = 1;
            for(int j = 0; j < k; j++){
                if(res[j][i] == "Q") {
                    shuxianOK = 0;
                    break;
                }
            }
            if(!shuxianOK) continue;
            for(int heng = k - 1, shu = i - 1; heng >= 0 && shu >= 0; heng--, shu--){
                if(res[heng][shu] == "Q"){
                    xiexianOK = 0;
                    break;
                }
            }
            if(xiexianOK) {
                for(int heng = k - 1, shu = i + 1; heng >= 0 && shu < n; heng--, shu++){
                    if(res[heng][shu] == "Q"){
                        xiexianOK = 0;
                        break;
                    }
                }
            }
            if(!xiexianOK) continue;
            // 剩下的是竖着和斜线都没有queen的情况，为合理摆放位置；
            res[k][i] = "Q";
            NQueen(k + 1, n, res, solution, sum_solution);
            res[k][i] = '.'; // 回溯，撤销当前行的放置 递归这里要记得回溯！
        }

    }
};
// @lc code=end

