/* DFS 算法的步骤：
从起始节点开始，访问该节点并将其标记为已访问。
选择一个未访问的相邻节点，递归地对其执行DFS。如果没有未访问的相邻节点，则回溯到上一个节点。
重复步骤2，直到所有节点都被访问。
 */
#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    // 构造函数，初始化图
    Graph(int vertices);
    
    // 添加边
    void addEdge(int v, int w);
    
    // 深度优先搜索
    void DFS(int v);
    
private:
    int vertices; // 图中的顶点数
    vector<vector<int>> adj; // 邻接表
    vector<bool> visited; // 访问标记数组
};

Graph::Graph(int vertices) {
    this->vertices = vertices;
    adj.resize(vertices);
    visited.resize(vertices, false);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // v -> w
    adj[w].push_back(v); // w -> v （因为是无向图）
}

void Graph::DFS(int v) {
    // 标记当前节点为已访问
    visited[v] = true;
    cout << v << " ";
    
    // 递归访问所有未被访问的相邻节点
    for (int i : adj[v]) {
        if (!visited[i]) {
            DFS(i);
        }
    }
}

int main() {
    // 创建一个图
    Graph g(6);
    
    // 添加边
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    // 从顶点 0 开始深度优先搜索
    cout << "深度优先搜索起始于节点 0:" << endl;
    g.DFS(0);

    return 0;
}
