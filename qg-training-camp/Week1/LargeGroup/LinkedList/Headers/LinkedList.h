#pragma once
#include <iostream>
typedef int ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LNode, * LinkedList;

typedef enum Status {
	ERROR,
	SUCCESS,
} Status;
Status InitList(LinkedList* L);			//函数声明
void DestroyList(LinkedList* L);
Status InsertList(LNode* p, LNode* q);
Status DeleteList(LNode* p, ElemType* e);
void TraverseList(LinkedList L);
Status SearchList(LinkedList L, ElemType e);
Status ReverseList(LinkedList* L);
Status IsLoopList(LinkedList L);
LNode* ReverseEvenList(LinkedList* L);
LNode* FindMidNode(LinkedList* L);
void cycle(LinkedList* L);
void menue();							//函数声明