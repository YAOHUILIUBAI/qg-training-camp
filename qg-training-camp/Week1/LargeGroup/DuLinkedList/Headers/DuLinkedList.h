#pragma once
typedef int ElemType;
typedef struct DuLNode {
	ElemType data;
	struct DuLNode* prior, * next;
} DuLNode, * DuLinkedList;
typedef enum Status {
	ERROR,
	SUCCESS,
} Status;
Status InitList_DuL(DuLinkedList* L);					//函数声明
void DestroyList_DuL(DuLinkedList* L);
Status InsertBeforeList_DuL(DuLNode* p, DuLNode* q);
Status InsertAfterList_DuL(DuLNode* p, DuLNode* q);
Status DeleteList_DuL(DuLNode* p, ElemType* e);
void TraverseList_DuL(DuLinkedList L);
void menue();							//函数声明