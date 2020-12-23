#include <stdio.h>
#include <stdlib.h>
typedef enum { FALSE,TRUE } Status;

typedef int ElemType;
typedef int Position;
typedef struct SqList{
	ElemType* data;
	int length;
	int listSize;
}SqList, *List;

void swap(ElemType *a, ElemType *b) {
	ElemType p = *a;
	*a = *b;
	*b = p;
}

List InitSqlist(int N) {
	List L;
	L = (List)malloc(sizeof(SqList));
	L->data = (ElemType*)malloc(sizeof(ElemType) * N);
	L->length = 0;
	L->listSize = N;
	return L;
}

Status Push(List L, ElemType x) {
	if(L->length == L->listSize) {
		printf("顺序表空间已满！\n");
		return FALSE;
	}
	L->data[L->length++] = x;
	return TRUE;
}

List InitSqlistWithElem(int n, int m) {
	int i, x;
	List L = InitSqlist(n);
	printf("输入顺序表的%d个有序数据：", n);
	for (i = 0; i < m; i++) {
		scanf("%d", &x);
		Push(L, x);
	}
	return L;
}

Status Insert(List L, ElemType x ,Position p) {
	Position i;
	if(L->length == L->listSize) {
		printf("顺序表空间已满！\n");
		return FALSE;
	}
	if(p < 1 || p > L->length + 1) {
		printf("插入位置不合法！\n");
		return FALSE;
	}
	for (i = L->length; i >= p ; i--) {
		L->data[i] = L->data[i - 1];
	}
	L->data[i] = x;
	L->length++;
	return TRUE;
}

int Delete(List L, Position p) {
	Position i;
	ElemType x;
	if(L->length == 0) {
		printf("顺序表为空！\n");
		return FALSE;
	}
	if(p < 1 || p > L->length) {
		printf("插入位置不合法！\n");
		return FALSE;
	}
	x = L->data[p - 1];
	for (i = p; i < L->length; i++)
	{
		L->data[i - 1] = L->data[i]; 
	}
	L->length--;
	return x;
}

void ReverseSqList(List L) {
	int i;
	for(i = 0; i < L->length /2 ;i++) {
		swap(&(L->data[i]), &(L->data[L->length - 1 - i]));
	}
}

void LoadList(List L) {
	Position i;
	printf("当前顺序表为：");
	for (i = 0; i < L->length; i++)
	{
		printf("%d ", L->data[i]);
	}
	printf("\n");
}

List MergeList(List L1, List L2) {
	int i = 0, j = 0, k = 1;
	List L = InitSqlist(L1->listSize + L2->listSize);
	while(i < L1->length && j < L2->length) {
		if(L1->data[i] <= L2->data[j]) {
			Push(L, L1->data[i++]);
		}else {
			Push(L, L2->data[j++]);
		}
	}
	while(i < L1->length) Push(L, L1->data[i++]);
	while(j < L2->length) Push(L, L1->data[j++]);
	return L;
}

void exec_1() {
	int i;
	int flag, n, p, res;
	int circle = 1;
	List L;
	printf("输入数字创建空间大小为N的线性表 -- N: ");
	scanf("%d", &flag);
	while(flag == 0) {
		printf("输入合法的空间大小 -- N：");
		scanf("%d", &flag);
	}
	L = InitSqlist(flag);
	printf("要初始化的数字个数n：");
	scanf("%d", &n);
	if(n != 0) printf("请输入%d个数字: ", n);
	for (i = 0; i < n; i++) {
		scanf("%d", &flag);
		Push(L, flag);
	}
	LoadList(L);
	while(circle) {
		printf("-----\n输入11插入\n输入22删除\n输入33逆置\n输入44退出\n-----\n");
		scanf("%d", &flag);
		switch (flag)
		{
		case 11:
			printf("输入要插入的值和位置：");
			scanf("%d %d", &flag, &p);
			Insert(L, flag, p);
			LoadList(L);
			break;
		case 22:
			printf("删除的位置：");
			scanf("%d", &p);
			res = Delete(L, p);
			if(res) printf("删除的值为%d\n", res);
			LoadList(L);
			break;
		case 33:
			ReverseSqList(L);
			LoadList(L);
			break;
		case 44:
			circle = 0;
			break;
		default:
			break;
		}
	}
}

void exec_2() {
	int i, x, n;
	List La, Lb, Lc;
	printf("合并两个顺序表，请初始化顺序表.\n");
	printf("第一个顺序表的空间大小：");
	scanf("%d", &n);
	La = InitSqlistWithElem(n, n);
	printf("第二个顺序表的空间大小：");
	scanf("%d", &n);
	Lb = InitSqlistWithElem(n, n);
	Lc = MergeList(La, Lb);
	LoadList(Lc);
}

int main()
{
	exec_2();
	return 0;
}



