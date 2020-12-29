#include <iostream>
#include <stdbool.h>
#include <iomanip>
#include <stack>
#include <queue>
using namespace std;
#define MaxVertexNum 100 // 最大顶点数
#define INFINITY 65535 // ∞设为双字节无符号整数的最大值65535

typedef int Vertex; // 顶点下标表示顶点
typedef int WeightType; //边的权值类型
typedef char DataType; // 顶点存储的数据类型

// 边结构
typedef struct Edge {
    Vertex v1, v2;  // 表示边的两个顶点
    WeightType weight;  // 边的权重
}Edge;

// 邻接矩阵表示的图结构
typedef struct MGraph {
    int nv; // 顶点数
    int ne; // 边数
    WeightType G[MaxVertexNum][MaxVertexNum];   // 邻接矩阵表
    DataType Data[MaxVertexNum];  //顶点数据数组 
}MGraph;

//初始化图函数 -- 有顶点数但无边的图
void InitMGraph(MGraph &Graph, int VertexNum) {
    int v, w;
    Graph.nv = VertexNum;
    Graph.ne = 0;
    for (v = 0; v < Graph.nv; v++) {
        for (w = 0;w < Graph.nv;w++) {
            Graph.G[v][w] = INFINITY;
        }
    }
}

// 插入边
void InsertEdge(MGraph &Graph, Edge edge) {
    Graph.G[edge.v1-1][edge.v2-1] = edge.weight;
    Graph.G[edge.v2-1][edge.v1-1] = edge.weight; // 若是无向图则再插入另一条边
}

// 建图
void BuildMGraph(MGraph &Graph) {
    int nv, i;
    Edge edge;
    cout << "请输入顶点数以初始化图：";
    cin >> nv;
    InitMGraph(Graph, nv);
    cout << "请输入边数：";
    cin >> Graph.ne;
    for (i = 0; i < Graph.ne; i++) {
        cout << "请插入第" << i+1 << "条边(v1, v2, weight)：";
        cin >> edge.v1 >> edge.v2 >> edge.weight;
        InsertEdge(Graph, edge);
    }
    cout << "请输入" << Graph.nv << "个顶点数据";
    for (i = 0; i < Graph.nv; i++) {
        cin >> Graph.Data[i];
    }
}

// 打印图
void LoadGraph(MGraph &Graph) {
    int v, w;
    cout << "-----------" << endl;
    cout << " ";
    for (v = 0; v < Graph.nv; v++) {
        cout << setw(5) << Graph.Data[v];
    }
    cout << endl;
    for (v = 0; v < Graph.nv; v++) {
        cout << Graph.Data[v] << " ";
        for (w = 0; w < Graph.nv; w++) {
            if(Graph.G[v][w] == INFINITY) cout << setw(5) << " 0";
            else cout << setw(5) << Graph.G[v][w];
        }
        cout << endl;   
    }
    cout << "-----------" << endl;
}

// 获取第一个邻接点
Vertex FirstNeighbor(MGraph &Graph, Vertex v) {
    if(v != -1) {
        for(int i = 0; i < Graph.nv; i++) {
            if(Graph.G[v][i] != INFINITY) {
                return i;
            }
        }
    }
    return -1;
}

// 获取下一个邻接点
Vertex NextNeighbor(MGraph &Graph, Vertex v, Vertex w) {
    if(v != -1 && w != -1) {
        for(int i = w+1; i < Graph.nv; i++) {
            if(Graph.G[v][i] != INFINITY) {
                return i;
            }
        }
    }
    return -1;
}

// 深度优先搜索
void DFS(MGraph Graph, Vertex v, bool visited[]) {
    Vertex w;
    visited[v] = true;
    cout << Graph.Data[v] << " ";
    for ( w = FirstNeighbor(Graph, v); w >= 0; w = NextNeighbor(Graph, v, w)) {
        if(!visited[w]) DFS(Graph, w, visited);
    }
    
}

void DFSTraversal(MGraph Graph) {
    bool visited[MaxVertexNum];
    for (Vertex i = 0; i < Graph.nv; i++) {
        visited[i] = false;
    }
    for (Vertex i = 0; i < Graph.nv; i++) {
        if(!visited[i]) DFS(Graph, 0, visited);
    }
} 

// 广度优先搜索
void BFS(MGraph &Graph, Vertex v, bool visited[]) {
    queue<Vertex> que;
    Vertex w;
    que.push(v);
    visited[v] = true;
    cout << Graph.Data[v] << " ";
    while(!que.empty()) {
        v = que.front();que.pop();
        for ( w = FirstNeighbor(Graph, v); w >= 0; w = NextNeighbor(Graph, v, w)) {
            if(!visited[w]) {
                que.push(w);
                visited[w] = true;
                cout << Graph.Data[w] << " ";
            }       
        }   
    }
}

void BFSTraversal(MGraph &Graph) {
    bool visited[MaxVertexNum];
    for (Vertex i = 0; i < Graph.nv; i++) {
        visited[i] = false;
    }
    for (Vertex i = 0; i < Graph.nv; i++) {
        if(!visited[i]) BFS(Graph, 0, visited);
    }
}

void DFS_NonRC(MGraph Graph, Vertex v) {
    Vertex w;
    stack<Vertex> st;
    bool visited[MaxVertexNum];
    for (Vertex i = 0; i < Graph.nv; i++) {
        visited[i] = false;
    }
    st.push(v);visited[v] = true;
    while(!st.empty()) {
        v = st.top(); st.pop();
        cout << v;
        for ( w = FirstNeighbor(Graph, v); w >= 0; w = NextNeighbor(Graph, v, w)) {
            if(!visited[w]) {
                st.push(w);
                visited[w] = true;
            } 
        }
    }
}


int main() {
    MGraph Graph;
    BuildMGraph(Graph);
    LoadGraph(Graph);
    cout << "DFS:";
    DFSTraversal(Graph);
    cout << endl;
    cout << "BFS:";
    BFSTraversal(Graph);
    cout << endl;
    return 0;
}

