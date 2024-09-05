/* 迷宫问题(百练4127)
定义一个矩阵：
0 1 0 0 0 
0 1 0 1 0 
0 0 0 0 0 
0 1 1 1 0 
0 0 0 1 0 
它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，
只能横着走或竖着走，不能斜着走，要求编程序找出从
左上角到右下角的最短路线。
 */
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// 定义方向数组，表示四个方向的移动（上、下、左、右）
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// BFS 寻找最短路径
bool bfs(const vector<vector<int>>& maze, vector<vector<int>>& prev) {
    int n = maze.size();
    int m = maze[0].size();
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    // 从起点开始
    q.push({0, 0});
    visited[0][0] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // 如果到达终点
        if (x == n - 1 && y == m - 1) {
            return true;
        }

        // 遍历四个方向
        for (auto& dir : directions) {
            int newX = x + dir[0];
            int newY = y + dir[1];

            // 检查新位置是否合法且未访问过
            if (newX >= 0 && newX < n && newY >= 0 && newY < m && 
                maze[newX][newY] == 0 && !visited[newX][newY]) {
                q.push({newX, newY});
                visited[newX][newY] = true;
                // 一种很新的使用余数来将索引目标的二维元素转化为一维元素的方法！！
                prev[newX][newY] = x * m + y; // 记录路径
            }
        }
    }

    return false; // 没有找到路径
}

// 打印从终点到起点的路径
void printPath(const vector<vector<int>>& prev, int n, int m) {
    stack<pair<int, int>> path;
    int x = n - 1;
    int y = m - 1;

    while (x != 0 || y != 0) {
        path.push({x, y});
        int prevIndex = prev[x][y];
        x = prevIndex / m; // 一种很新的使用余数来将索引目标的二维元素转化为一维元素的方法！！
        y = prevIndex % m;
    }
    path.push({0, 0}); // 起点

    // 打印路径
    while (!path.empty()) {
        auto [px, py] = path.top();
        path.pop();
        cout << "(" << px << ", " << py << ") ";
        if (!path.empty()) {
            cout << "-> ";
        }
    }
    cout << endl;
}

int main() {
    // 定义迷宫
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0}
    };

    int n = maze.size();
    int m = maze[0].size();

    // 记录每个点的前驱，用于还原路径
    vector<vector<int>> prev(n, vector<int>(m, -1));

    if (bfs(maze, prev)) {
        cout << "Found a path:\n";
        printPath(prev, n, m);
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
