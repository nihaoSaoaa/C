#include <iostream>
#include <iomanip>
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

// 边表结点
typedef struct ArcNode {
    Vertex adjvex;  // 弧所指向顶点的位置
    WeightType weight;  // 弧的权值
    struct ArcNode* next;   // 指向下一个弧的指针
}ArcNode;

// 顶点表结点
typedef struct VNode {
    DataType data;  // 顶点数据
    struct ArcNode* first;  // 指向相邻边表结点的指针
}VNode, AdjList[MaxVertexNum];

// 邻接表表示的图结构
typedef struct ALGraph {
    int nv; // 顶点数
    int ne; // 边数
    AdjList G;  // 邻接表
}ALGraph;

// 初始化图
void InitALGraph(ALGraph &Graph, int VertexNum) {
    Vertex v;
    Graph.nv = VertexNum;
    Graph.ne = 0;
    for (v = 0; v < Graph.nv; v++) {
        Graph.G[v].first = NULL;
    }
}

// 插入边
void InsertEdge(ALGraph &Graph, Edge edge) {
    ArcNode* newNode = new ArcNode();
    newNode->adjvex = edge.v2;
    newNode->weight = edge.weight;
    newNode->next = Graph.G[edge.v1].first;
    Graph.G[edge.v1].first = newNode;
    // 若是无向图则插入另一条边
    newNode = new ArcNode();
    newNode->adjvex = edge.v1;
    newNode->weight = edge.weight;
    newNode->next = Graph.G[edge.v2].first;
    Graph.G[edge.v2].first = newNode;
}

// 建图
void BuildALGraph(ALGraph &Graph) {
    int nv, i;
    Edge edge;
    cout << "请输入顶点数以初始化图：";
    cin >> nv;
    InitALGraph(Graph, nv);
    cout << "请输入边数：";
    cin >> Graph.ne;
    for (i = 0; i < Graph.ne; i++) {
        cout << "请插入第" << i+1 << "条边(v1, v2, weight)：";
        cin >> edge.v1 >> edge.v2 >> edge.weight;
        InsertEdge(Graph, edge);
    }
    cout << "请输入" << Graph.nv << "个顶点数据";
    for (i = 0; i < Graph.nv; i++) {
        cin >> Graph.G[i].data;
    }
}

// 打印图
void LoadALGraph(ALGraph &Graph) {
    Vertex v;
    ArcNode* p;
    DataType data;
    WeightType weight;
    cout << "--------" << endl;
    for (v = 0; v < Graph.nv; v++) {
        cout << Graph.G[v].data;
        p = Graph.G[v].first;
        while(p) {
            data = Graph.G[p->adjvex].data;
            weight = p->weight;
            cout << " ->" << data << ":" <<weight;
            p = p->next;
        }
        cout << endl;
    }
    cout << "--------" << endl;
}

// 获取第一个邻接点
ArcNode* FirstNeighbor(ALGraph Graph, Vertex v) {

}

// 获取下一个邻接点
ArcNode* NextNeighbor(ALGraph Graph, Vertex v, ArcNode* w) {
    
}

void DFS() {

}

int main() {
    ALGraph Graph;
    BuildALGraph(Graph);
    LoadALGraph(Graph);
    return 0;
}
