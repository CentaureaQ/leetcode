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
        vector<vector<string>> solution; // 结果
        vector<string> res(n, string(n, '.')); // 初始化 res，每个元素都是大小为 n 的字符串
        NQueen(0, n, res, solution);
        return solution;
    }

    void NQueen(int k, int n, vector<string>& res, vector<vector<string>>& solution) {
        if (k == n) {
            solution.push_back(res); // 如果 k == n，说明已经找到了一个合法解，直接添加到 solution 中
            return;
        }

        for (int i = 0; i < n; i++) {
            if (isValid(k, i, res, n)) { // 检查是否可以在 (k, i) 位置放置皇后
                res[k][i] = 'Q'; // 放置皇后
                NQueen(k + 1, n, res, solution); // 递归放置下一行的皇后
                res[k][i] = '.'; // 回溯，撤销当前行的放置
            }
        }
    }

    bool isValid(int row, int col, vector<string>& res, int n) {
        // 检查列冲突
        for (int i = 0; i < row; i++) {
            if (res[i][col] == 'Q') return false;
        }
        // 检查主对角线冲突
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (res[i][j] == 'Q') return false;
        }
        // 检查副对角线冲突
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (res[i][j] == 'Q') return false;
        }
        return true;
    }
};
// @lc code=end

