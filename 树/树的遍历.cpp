#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* createTree(int data[], int N);
/* 中序遍历 */
vector<int> inorderTraversal(TreeNode* root);
/* 先序遍历 */
vector<int> preorderTraversal(TreeNode* root);
/* 后序遍历 */
vector<int> postorderTraversal(TreeNode* root);


int main()
{
  TreeNode *T;
  int data[7] = {1,2,3,4,5,6,7};
  T = createTree(data, 7);
  vector<int> preV = preorderTraversal(T);
  vector<int> inV = inorderTraversal(T);
  vector<int> postV = postorderTraversal(T);
  cout << "先序遍历：";
  for (int i = 0; i < preV.size(); i++)
  {
    cout << preV[i] << " ";
  }
  cout << endl;

  cout << "中序遍历：";
  for (int i = 0; i < inV.size(); i++)
  {
    cout << inV[i] << " ";
  }
  cout << endl;

  cout << "后序遍历：";
  for (int i = 0; i < postV.size(); i++)
  {
    cout << postV[i] << " ";
  }
  cout << endl;
  return 0;
}


vector<int> inorderTraversal(TreeNode* root) {
  TreeNode* p = root;
  vector<int> v;
  stack<TreeNode*> s;
  while(p || s.size()) {
    while(p) {
      s.push(p);
      p = p->left;
    }
    if(s.size()) {
      p = s.top();s.pop();
      v.push_back(p->val);
      p = p->right;
    }
  }
  return v;
}

TreeNode* createTree(int data[], int N) {
  TreeNode* Ts = (TreeNode*)malloc(sizeof(TreeNode) * N);
  for (int i = 0; i < N; i++){
    TreeNode t(data[i]);
    Ts[i] = t;
  }
  for(int i = 0; i < N / 2; i++) {
    Ts[i].left = &(Ts[i * 2 + 1]);
    if(i * 2 + 2 < N) Ts[i].right = &(Ts[i * 2 + 2]);
  }
  return &(Ts[0]);
} 

vector<int> preorderTraversal(TreeNode* root) {
  TreeNode* p = root;
  vector<int> v;
  stack<TreeNode*> s;
  while(p || s.size()) {
    while(p) {
      v.push_back(p->val);
      s.push(p->right);
      p = p->left;
    }
    if(s.size()) {
      p = s.top();s.pop();
    }
  }
  return v;
}

vector<int> postorderTraversal(TreeNode* root) {
  TreeNode *p = root, *lastVisit;
  vector<int> v;
  stack<TreeNode*> s;
  while(p || s.size()) {
    while(p) {
      s.push(p);
      p = p->left;
    }
    p = s.top();
    if(p->right == nullptr || p->right == lastVisit) {
      s.pop();
      v.push_back(p->val);
      lastVisit = p;
      p = nullptr;
    }
    else {
      p = p->right;
    };      
  }
  return v;
}