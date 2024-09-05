#include <iostream>
#include <vector>
#include <queue>

/* 
邻接表：graph 是一个二维 vector，它表示图的邻接表。例如，graph[0] = {1, 2} 表示节点 0 连接到节点 1 和节点 2。

visited 数组：visited 数组用来记录每个节点是否已经被访问过，防止重复访问。

队列：queue<int> q 用于存储待访问的节点。

核心逻辑：在 while 循环中，不断取出队列中的节点，访问它的所有未被访问过的邻居节点，并将这些邻居节点入队。 
*/


using namespace std;

void bfs(int startNode, const vector<vector<int>>& graph) {
    // 用于记录每个节点是否被访问过
    vector<bool> visited(graph.size(), false);  
    queue<int> q;  // 创建一个队列用于BFS，判重利用visited来解决；
    // 如果判重不方便利用新开的visited的话，可以使用unordered_set
    q.push(startNode);  // 起始节点入队
    visited[startNode] = true;  // 标记起始节点为已访问

    while (!q.empty()) {
        int currentNode = q.front();  // 取出队首元素
        q.pop();  // 弹出队首元素
        cout << "Visited node: " << currentNode << endl;  // 访问节点

        // 遍历当前节点的所有邻居节点
        for (int neighbor : graph[currentNode]) {
            if (!visited[neighbor]) {  // 如果邻居节点未被访问
                q.push(neighbor);  // 入队
                visited[neighbor] = true;  // 标记为已访问
            }
        }
    }
}

int main() {
    // 定义一个图的邻接表
    vector<vector<int>> graph = {
        {1, 2},     // 节点 0 连接到节点 1 和节点 2
        {0, 3, 4},  // 节点 1 连接到节点 0、3、4
        {0, 4},     // 节点 2 连接到节点 0、4
        {1, 4, 5},  // 节点 3 连接到节点 1、4、5
        {1, 2, 3, 5}, // 节点 4 连接到节点 1、2、3、5
        {3, 4}      // 节点 5 连接到节点 3、4
    };

    // 从节点 0 开始进行广度优先搜索
    bfs(0, graph);

    return 0;
}
