// linkList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "LinkedList.h"

int main()
{
	char c = 0;						//用于在每次用完吸收“按任意键返回”的值
	LinkedList L=NULL;
	int check = 0;					//用于判断是否已创建链表，若没有，则无法实现其他操作
	int checkc = 0;					//用于判断是否成环，成环无法进行除了退出和删除链表外的操作
	int choice=1;
	while (choice) {
		system("cls");
		menue();
		scanf_s("%d", &choice);
		system("cls");
		if (choice < 0 || choice>11)		//用于判断是否规范输入
		{
			printf_s("请规范输入！\n");
			printf_s("按任意键返回菜单\n");
			c=getchar();
			c=getchar();
			continue;
		}
		if (choice == 1)check++;
		if (check == 0&&choice!=0) {			//用于判断是否已创建链表，若没有，则无法实现其他操作
			printf_s("请先创建链表！\n");
			printf_s("按任意键返回菜单");
			c=getchar();
			c=getchar();
			continue;
		}
		if (checkc == 1 &&choice!= 0) {			//用于判断是否成环，成环无法进行除了退出和删除链表外的操作
			if (choice == 2)
			{
				choice = 2;
				checkc = 0;
			}
			else {
				printf_s("已成环，无法操作\n");
				printf_s("按任意键返回菜单");
				c = getchar();
				c = getchar();
				continue;
			}
		}
		switch (choice)
		{
		case 1: InitList(&L); break;
		case 2: DestroyList(&L); printf_s("删除完成\n"); break;
		case 3: {
			int i;
			printf_s("请输入要插入处的前一节点数：");
			scanf_s("%d", &i);
			LNode* p, * q;
			p = L;
			for (int j = 0; j < i; j++) {
				p = p->next;
				if (p == NULL)break;
			}
			if (p == NULL) {							//异常处理。节点超过链表使的输出
				printf_s("选择节点不存在！插入失败！\n");
				break;
			}
			printf_s("请输入要插入节点的数据：");
			scanf_s("%d", &i);
			q = (LinkedList)malloc(sizeof(LNode));
			q->data = i;
			InsertList(p, q);
			break;
		}
		case 4: {
			int i;
			printf_s("请输入要删除节点位数：");
			scanf_s("%d", &i);
			LNode* p;
			p = L;
			ElemType* e = NULL;
			for (int j = 0; j < i-1; j++) {
				p = p->next;
				if (p == NULL)break;
			}
			if (p == NULL) {						//异常处理。节点超过链表使的输出
				printf_s("选择节点不存在！删除失败！\n");
				break;
			}
			DeleteList(p, e);
			break;
		}
		case 5: {
			if (checkc == 0) {
				TraverseList(L);
			}
			else printf_s("已成环，无法输出\n");
			break; 
		}
		case 6: {
			printf_s("请输入要查找的数据：");
			ElemType e;
			scanf_s("%d", &e);
			SearchList(L, e);
			break; }
		case 7:  ReverseList(&L); break;
		case 8: {
			if (IsLoopList(L) == ERROR) {
				printf_s("未成环\n");
			}
			else printf_s("成环\n");
			break; }
		case 9: {
			L = ReverseEvenList(&L);
			break;
		}
		case 10: {
			LinkedList p;
			p = FindMidNode(&L);
			printf_s("中间节点数据为：%d\n", p->data);
			break; }
		case 11: { cycle(&L); checkc++; break; }
		}
		if (choice == 0) { DestroyList(&L); break; }
		if (choice == 2)check = 0;
		printf_s("按任意键返回菜单");
		c=getchar();
		c = getchar();
	}
}
void menue() {											//菜单
	printf_s("=====     单链表ADT    ======\n");
	printf_s("=====    1.创建链表    ======\n");
	printf_s("=====    2.删除链表    ======\n");
	printf_s("=====    3.插入节点    ======\n");
	printf_s("=====    4.删除节点    ======\n");
	printf_s("=====    5.遍历链表    ======\n");
	printf_s("===== 6.查找数据的节点 ======\n");
	printf_s("=====    7.反转链表    ======\n");
	printf_s("=====    8.是否成环    ======\n");
	printf_s("=====    9.奇偶调换    ======\n");
	printf_s("=====  10.寻找中间节点 ======\n");
	printf_s("=====  11.链表成环     ======\n");
	printf_s("=====     0.退出       ======\n");
	printf_s("请输入你的选择：\n");
}
Status InitList(LinkedList* L) {
	LinkedList p;
	p = (LinkedList)malloc(sizeof(LNode));     //申请空间，创建头节点
	(* L) = p;
	if (*L == NULL)                             //失败返回EERROR
	{
		printf_s("申请失败\n");
		return ERROR;
	}
	else {
		printf_s("创建空链表成功\n");
		(*L)->next = NULL;						 //成功返回SUCCESS
	}                
	int a=0;
	printf_s("请输入要创建的节点个数:");
	scanf_s("%d",&a);
	LNode* p1, * p2;
	p1 = (LinkedList)malloc(sizeof(LNode));
	if (p1 == NULL) {
		printf_s("申请失败\n");
		return ERROR;
	}
	if (a > 0) {
		p2 = p1;
		(*L)->next = p1;
		p1->data = 1;
		for (int i = 2; i <= a; i++) {				//根据前面收集创建节点数自动动态申请形成链表
			p1 = (LinkedList)malloc(sizeof(LNode));
			if (p1 == NULL) {
				printf_s("申请失败\n");
				return ERROR;
			}
			p2->next = p1;
			p1->data = i;
			p2 = p1;
		}
		p2->next = NULL;
	}
	printf_s("创建完成\n");
	return SUCCESS;
}
void DestroyList(LinkedList* L) {
	Status IsLoopList(LinkedList L);
	LinkedList p;
	if (IsLoopList(*L) == SUCCESS)		//若成环，删除节点的操作
	{
		p = (*L)->next;
		(* L )->next = NULL;
		*L = p;
	}
	while ((*L) != NULL) {                      //循环，使链表从第一个开始一个个节点free掉
		p = (*L);
		(*L) = (*L)->next;
		free(p);
	}
}
Status InsertList(LNode* p, LNode* q) {		//在p节点后插入节点q
	q->next = p->next;
	p->next = q;
	return SUCCESS;
}
Status DeleteList(LNode* p, ElemType* e){		//删除节点p并且记录节点p内数据
		e = &((p->next)->data);
		p->next = (p->next)->next;
		return SUCCESS;
}
void TraverseList(LinkedList L) {		//遍历链表同时输出链表数据
	L = L->next;
	while (L!= NULL) {
		printf_s("%d->", L->data);
		L = L->next;
	}
	printf_s("NULL\n");
}
Status SearchList(LinkedList L, ElemType e) {
	int i = 0;										//记录为第几个节点为所找的
	while (L != NULL) {
		if (L->data == e) {							//找到结束
			break;
		}
		else {										//否则检查下个节点并且记录数加一
			i++;
			L = L->next;
		}
	}
	if (L == NULL) {								//判断是否不存在数据为e的节点
		printf_s("链表内不存在该数据\n");
		return ERROR;
	}				
	else {
		printf_s("该数在第%d个节点\n", i);
		return SUCCESS;
	}
}
Status ReverseList(LinkedList* L) {
	LNode *p1, * p2;
	LNode *head;
	p1 = (*L)->next;
	p2 = p1->next;
	head = p2->next;
	p1->next = NULL;
	while (head != NULL) {			//反转链表，用三个指针。分别指向方向调换的两个节点和其中大节点的下一节点
		p2->next = p1;
		p1 = p2;
		p2 = head;
		head = head->next;
	}
	p2->next = p1;
	(*L)->next = p2;
	printf_s("反转完成\n");
	return SUCCESS;
}
Status IsLoopList(LinkedList L) {
	LNode* slow, * fast;
	slow = L->next;
	fast = slow;
	while (fast != NULL&&fast->next!= NULL) {		//异常处理，若指针为空或其下一个地址为空，则不会让快指针走两步
		fast = fast->next->next;
		slow = slow->next;
		if (slow == fast)							//若循环，快的会追上慢的
			return SUCCESS;
	}
	return ERROR;
}
LNode* ReverseEvenList(LinkedList* L) {
	LNode* p1, * p2,*p3;
	p3 = (*L);
	p1 = (*L)->next->next;
	p2 = (*L)->next;
	while (p1 != NULL) {						//调换链表，用三个指针。分别指向方向调换的两个节点和其中小节点的上一节点
		p2->next = p1->next;
		p1->next = p2;
		(*L)->next = p1;
		(*L) = p2;
		p2 = p2->next;
		if (p2 == NULL)
			break;
		p1 = p2->next;
	}
	printf_s("调换完成\n");
	return p3;
}
LNode* FindMidNode(LinkedList* L) {
	LNode* fast, * slow;					//设置快慢指针
	slow = (*L)->next;
	fast = slow->next;
	while (fast != NULL) {
		slow = slow->next;
		fast = fast->next;
		fast = fast->next;
	}
	return slow;							//快的一次两步，慢的一次一步，快的到空指针。慢的到中间节点
}
void cycle(LinkedList *L) {
	LinkedList p1;
	p1 = *L;
	while (p1->next != NULL)			//使最后一个节点指向头节点
	{
		p1 = p1->next;
	}
	p1->next = *L;
	printf_s("成环完成\n");
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
