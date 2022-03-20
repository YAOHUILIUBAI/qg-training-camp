// duLinkedList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "DuLinkedList.h"
int main()
{
	char c = 0;						//用于在每次用完吸收“按任意键返回”的值
	DuLinkedList L = NULL;
	int check = 0;					//用于判断是否已创建链表，若没有，则无法实现其他操作
	int choice = 1;
	while (choice) {
		system("cls");
		menue();
		scanf_s("%d", &choice);
		system("cls");
		if (choice < 0 || choice>6)		//用于判断是否规范输入
		{
			printf_s("请规范输入！\n");
			printf_s("按任意键返回菜单\n");
			c = getchar();
			c = getchar();
			continue;
		}
		if (choice == 1)check++;					
		if (check == 0 && choice != 0) {			//用于判断是否已创建链表，若没有，则无法实现其他操作
			printf_s("请先创建链表！\n");
			printf_s("按任意键返回菜单");
			c = getchar();
			c = getchar();
			continue;
		}
		switch (choice)
		{
		case 1: InitList_DuL(&L); break;
		case 2: DestroyList_DuL(&L); printf_s("删除完成\n"); break;
		case 3: {
			int i;
			printf_s("请输入要插入处的后一节点数：");
			scanf_s("%d", &i);
			DuLNode* p, * q;
			p = L;
			for (int j = 0; j < i; j++) {
				p = p->next;
				if (p == NULL)break;
			}
			if (p == NULL) {						//异常处理。节点超过链表使的输出
				printf_s("选择节点不存在！插入失败！\n");
				break;
			}
			printf_s("请输入要插入节点的数据：");
			scanf_s("%d", &i);
			q = (DuLinkedList)malloc(sizeof(DuLNode));
			q->data = i;
			InsertBeforeList_DuL(p, q);
			break;
		}
		case 4: {
			int i;
			printf_s("请输入要插入处的前一节点数：");
			scanf_s("%d", &i);
			DuLNode* p, * q;
			p = L;
			for (int j = 0; j < i; j++) {
				p = p->next;
				if (p == NULL)break;
			}
			if (p == NULL) {						//异常处理。节点超过链表使的输出
				printf_s("选择节点不存在！插入失败！\n");
				break;
			}
			printf_s("请输入要插入节点的数据：");
			scanf_s("%d", &i);
			q = (DuLinkedList)malloc(sizeof(DuLNode));
			q->data = i;
			InsertAfterList_DuL(p, q);
			break;
		}
		case 5: {
			int i;
			printf_s("请输入要删除节点位数：");
			scanf_s("%d", &i);
			DuLNode* p;
			p = L;
			ElemType* e = NULL;
			for (int j = 0; j < i - 1; j++) {
				p = p->next;
				if (p == NULL)break;
			}
			if (p == NULL) {							//异常处理。节点超过链表使的输出
				printf_s("选择节点不存在！删除失败！\n");
				break;
			}
			DeleteList_DuL(p, e);
			break;
		}
		case 6: {
			TraverseList_DuL(L);
			break;
		}
		}
		if (choice == 0) { DestroyList_DuL(&L); break; }
		if (choice == 2)check = 0;
		printf_s("按任意键返回菜单");
		c = getchar();
		c = getchar();
	}
}
void menue() {											//菜单
	printf_s("=====    双向链表ADT   ======\n");
	printf_s("=====    1.创建链表    ======\n");
	printf_s("=====    2.删除链表    ======\n");
	printf_s("=====   3.插入前节点   ======\n");
	printf_s("=====   4.插入后节点   ======\n");
	printf_s("=====    5.删除节点    ======\n");
	printf_s("=====    6.遍历链表    ======\n");
	printf_s("=====     0.退出       ======\n");
	printf_s("请输入你的选择：\n");
}
Status InitList_DuL(DuLinkedList* L) {
	DuLinkedList p;
	p = (DuLinkedList)malloc(sizeof(DuLNode));     //申请空间，创建头节点
	(*L) = p;
	if (*L == NULL)                             //失败返回EERROR
	{
		printf_s("申请失败\n");
		return ERROR;
	}
	else {
		printf_s("创建空链表成功\n");
		(*L)->next = NULL;
		(*L)->prior = NULL;
	}
	int a = 0;
	printf_s("请输入要创建的节点个数:");
	scanf_s("%d", &a);
	DuLNode* p1, * p2;
	p1 = (DuLinkedList)malloc(sizeof(DuLNode));
	if (p1 == NULL) {
		printf_s("申请失败\n");
		return ERROR;
	}
	if (a > 0) {
		p2 = p1;
		(*L)->next = p1;
		(p1)->prior = *L;
		p1->data = 1;
		for (int i = 2; i <= a; i++) {				//根据前面收集创建节点数自动动态申请形成链表
			p1 = (DuLinkedList)malloc(sizeof(DuLNode));
			if (p1 == NULL) {
				printf_s("申请失败\n");
				return ERROR;
			}
			p2->next = p1;
			p1->data = i;
			p1->prior = p2;
			p2 = p1;
		}
		p2->next = NULL;
	}
	printf_s("创建完成\n");
	return SUCCESS;
}
void DestroyList_DuL(DuLinkedList* L) {
	DuLinkedList p;
	while ((*L) != NULL) {                      //循环，使链表从第一个开始一个个节点free掉
		p = (*L);
		(*L) = (*L)->next;
		free(p);
	}
}
Status InsertBeforeList_DuL(DuLNode* p, DuLNode* q) {		//在选择节点前处插入新节点
	q->next = p;
	q->prior = p->prior;
	(p->prior)->next = q;
	p->prior = q;
	return SUCCESS;
}
Status InsertAfterList_DuL(DuLNode* p, DuLNode* q) {		//在选择节点后处插入新节点
	q->next = p->next;
	q->prior = p;
	p->next = q;
	(q->next)->prior = q;
	return SUCCESS;
}
Status DeleteList_DuL(DuLNode* p, ElemType* e) {		//删除节点并记录其数据
	e = &((p->next)->data);
	((p->next)->next)->prior = p;
	p->next = (p->next)->next;
	return SUCCESS;
}
void TraverseList_DuL(DuLinkedList L) {		//遍历链表并输出
	L = L->next;
	while (L != NULL) {
		printf_s("%d<->", L->data);
		L = L->next;
	}
	printf_s("NULL\n");

}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
