#include <iostream>
#include<stdlib.h>
#include<stdbool.h>
using namespace std;

typedef int ElemType;
typedef struct QNode *PtrToQNode;
typedef struct QNode{
  	ElemType data;
	PtrToQNode next;
}QNode;
typedef struct Queue{
	PtrToQNode front, rear;
	int size;
}Queue;

bool initQueue(Queue &que) {
	PtrToQNode p = (PtrToQNode)malloc(sizeof(QNode));
	p->next = NULL;
	que.front = que.rear = p;
	que.size = 0;
	return true;
}

bool isEmpty(Queue que) {
	return que.front->next == NULL;
}

bool enQueue(Queue &que, ElemType x) {
	PtrToQNode p;
	p = (PtrToQNode)malloc(sizeof(QNode));
	p->data = x;
	p->next = NULL;
	que.rear->next = p;
	que.rear = p;
	que.size++;
	return true;
}

bool deQueue(Queue &que, ElemType &x) {
	PtrToQNode p;
	if(isEmpty(que)) {
		cout << "队列为空!" << endl;
		return false;
	}
	p = que.front->next;
	que.front->next = p->next;
	x = p->data;
	free(p);
	que.size--;
	return true; 
}

void loadQueue(Queue que) {
	PtrToQNode p;
	cout << "当前队列：" << endl;
	for (int i = 0; i < que.size; i++) {
		cout << "--";
	}
	cout << endl;
	p = que.front->next;
	while(p) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
	for (int i = 0; i < que.size; i++) {
		cout << "--";
	}
	cout << endl;
}

int main() {
	int x;
	Queue que;
	initQueue(que);
	enQueue(que, 2);
	enQueue(que, 3);
	enQueue(que, 4);
	loadQueue(que);
	enQueue(que, 5);
	loadQueue(que);
	deQueue(que, x);
	loadQueue(que);
	return 0;
}



