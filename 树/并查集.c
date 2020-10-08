#include <stdio.h>
#include <stdlib.h>

#define MAX 1000                  /* 集合最大元素个数 */
typedef int ElementType;           /* 默认元素可以用非负整数表示 */
typedef int SetName;               /* 默认用根结点的下标作为集合名称 */
typedef ElementType SetType[MAX]; /* 假设集合元素下标从0开始 */

// 找到集合的根结点的下标
SetName Find(SetType S, ElementType X)
{
  if(S[X] < 0) {
    return X;
  }else {
    // 路径压缩
    return S[X] = Find(S, S[X]);
  }
}

// 集合合并，合并根节点
// 按秩归并
void Union(SetType S, SetName Root1, SetName Root2)
{
  if(S[Root1] > S[Root2]) {
    S[Root2] += S[Root1];
    S[Root1] = Root2;
  }else {
    S[Root1] += S[Root2];
    S[Root2] = Root1;
  }
}