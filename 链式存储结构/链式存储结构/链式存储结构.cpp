// 链式存储结构.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "pch.h"
#include <iostream>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
typedef int status;
typedef int ElemType; //数据元素类型定义
typedef struct node {
	ElemType data;     //data为抽象元素类型
	struct node *next; //next为指针类型 
}*Lnode;
typedef struct List {
	Lnode head;
	int id;
	int length;
	struct List *next;
}*ListN;

status InitList(ListN &L, int id);
status DestroyList(ListN &L, ListN &HeadL);
status ClearList(ListN &L);
status ListEmpty(ListN L);
status ListLength(ListN L);
status GetElem(ListN L, int i, ElemType & e);
status LocateElem(ListN L, ElemType e); //简化过
status PriorElem(ListN L, ElemType cur, ElemType&pre_e);
status NextElem(ListN L, ElemType cur, ElemType&next_e);
status ListInsert(ListN L, int i, ElemType e);
status ListDelete(ListN L, int i, ElemType &e);
status ListTraverse(ListN L); //简化过
status ListSave(ListN L);
status ListRead(ListN &L);
/*--------------------------------------------*/
int main(void) {
	ListN L = NULL;
	ListN HeadL = L;
	bool first = true;
	bool Flag;
	int op = 1;
	int id;
	int e;//数据元素的值
	int i;//数据元素的位置
	ElemType pre_e = NULL;
	ElemType next_e = NULL;
	while (op) {
		L = HeadL;
		Flag = false;
		system("cls"); printf("\n\n");
		printf(" Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf(" 1. InitList     7. LocateElem\n");
		printf(" 2. DestroyList  8. PriorElem\n");
		printf(" 3. ClearList    9. NextElem \n");
		printf(" 4. ListEmpty   10. ListInsert\n");
		printf(" 5. ListLength  11. ListDelete\n");
		printf(" 6. GetElem     12. ListTraverse\n\n");
		printf("13.ListSave\n");
		printf("14.ListRead\n\n");
		printf(" 0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("请输入你要操作的线性表id：");
		scanf_s("%d", &id);
		while (L) {
			if (L->id == id)
			{
				Flag = true;
				break;
			}
			else
			{
				L = L->next;
			}
		}
		printf("请选择你的操作[0~14]:");
		scanf_s("%d", &op);
		switch (op) {
		case 1:
			if (InitList(L, id) == OK) {
				printf("线性表创建成功！\n");
				if (first) {
					HeadL = L;
					first = false;
				}
				else {
					L->next = HeadL;
					HeadL = L;
				}
			}
			else printf("该线性表已存在！\n");
			getchar();getchar();
			break;
		case 2:
			if (Flag) {
				if (DestroyList(L, HeadL) == OK) printf("删除线性表成功！\n");
				else printf("删除线性表失败！\n");
			}
			else
			{
				printf("该线性表不存在！\n");
				printf("删除线性表失败！");
			}
			getchar();getchar();
			break;

		case 3:
			if (Flag) {
				if (ClearList(L) == OK)printf("清除线性表成功！\n");
				else printf("清除线性表失败！\n");
			}
			else
			{
				printf("该线性表不存在！\n");
				printf("清除线性表失败！");
			}
			getchar();getchar();
			break;
		case 4:
			if (Flag) {
				if (ListEmpty(L) == TRUE)printf("True！\n");
				else printf("False！\n");
			}
			else
			{
				printf("该线性表不存在！\n");
			}
			getchar();getchar();
			break;
		case 5:
			if (Flag) {
				if (ListLength(L))printf("求线性表数据元素个数成功！\n");
			}
			else
			{
				printf("该线性表不存在！\n");
				printf("求线性表数据元素个数失败！\n");
			}
			getchar();getchar();
			break;
		case 6:
			if (Flag) {
				if (!L->length) {
					printf("该线性表是空表！\n");
					printf("没有可获取的数据元素！\n");
					getchar();getchar();
					break;
				}
				else {

					printf("请输入所需数据元素的位置(1~%d)：", L->length);
					scanf_s("%d", &i);
					if (GetElem(L, i, e))printf("成功获得第%d个数据元素！\n", i);
					else printf("请输入数据元素的正确位置！\n");
				};
			}
			else
			{
				printf("该线性表不存在！\n");
				printf("获取数据元素失败！\n");
			}
			getchar();getchar();
			break;
		case 7:
			if (Flag) {
				if (!L->length) {
					printf("该线性表是空表！\n");
					printf("没有数据元素可供查找！\n");
				}
				else {
					printf("请输入需要查找的数据元素数值：");
					scanf_s("%d", &e);
					if (LocateElem(L, e))printf("成功查到数据元素%d在该线性表中的位置！\n", e);
					else printf("查找结束！\n");
				};
			}
			else
			{
				printf("该线性表不存在！\n");
				printf("查找数据元素位置失败！\n");
			}
			getchar();getchar();
			break;
		case 8:
			if (Flag) {
				if (!L->length) {
					printf("该线性表是空表！\n");
					printf("获取数据元素前驱失败！\n");
				}
				else {
					printf("请输入需要查找前驱的数据元素数值：");
					scanf_s("%d", &e);
					if (PriorElem(L, e, pre_e))printf("成功查到数据元素%d的前驱！\n", e);
					else printf("查找结束！\n");
				};
			}
			else
			{
				printf("该线性表不存在！\n");
				printf("获取数据元素前驱失败！\n");
			}
			getchar();getchar();
			break;
		case 9:
			if (Flag) {
				if (!L->length) {
					printf("该线性表是空表！\n");
					printf("获取数据元素后继失败！\n");
				}
				else {
					printf("请输入需要查找后继的数据元素数值：");
					scanf_s("%d", &e);
					if (NextElem(L, e, pre_e))printf("成功查到数据元素%d的后继！\n", e);
					else printf("查找结束！\n");
				};
			}
			else
			{
				printf("该线性表不存在！\n");
				printf("获取数据元素后继失败！\n");
			}
			getchar();getchar();
			break;
		case 10:
			if (Flag) {
				printf("请输入要插入的数据元素：");
				scanf_s("%d", &e);
				printf("请输入要插入的位置(1~%d)：", L->length + 1);
				scanf_s("%d", &i);
				if (ListInsert(L, i, e)) printf("插入数据元素成功！\n");
				else printf("插入数据元素失败! \n");
			}
			else
			{
				printf("该线性表不存在！\n");
				printf("插入数据元素失败！\n");
			}
			getchar();getchar();
			break;
		case 11:
			if (Flag) {
				if (!L->length) {
					printf("该线性表是空表！\n");
					printf("没有可删除的数据元素！\n");
				}
				else {
					printf("请输入要删除的位置(1~%d)：", L->length);
					scanf_s("%d", &i);
					if (ListDelete(L, i, e))printf("删除数据元素成功！\n");
					else printf("删除数据元素失败！\n");
				}
			}
			else
			{
				printf("该线性表不存在！\n");
				printf("删除数据元素失败！\n");
			}
			getchar();getchar();
			break;
		case 12:
			if (Flag) {
				if (ListTraverse(L)) printf("已遍历该线性表！\n");
				else printf("该线性表是空表！\n");
			}
			else
			{
				printf("该线性表不存在！\n");
				printf("遍历线性表失败！");
			}
			getchar();getchar();
			break;
		case 13:
			if (Flag) {
				if (ListSave(L)) printf("线性表写入文件成功！\n");
				else printf("线性表写入文件失败！\n");
			}
			else
			{
				printf("该线性表不存在！\n");
				printf("线性表写入文件失败！\n");
			}
			getchar();getchar();
			break;
		case 14:
			if (Flag) {
				if (ListRead(L)) printf("读取线性表文件成功！\n");
				else printf("读取线性表文件失败！\n");
			}
			else
			{
				printf("该线性表不存在！\n");
				printf("读取线性表文件失败！\n");
			}
			getchar();getchar();
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()
/********************************************************************/
/*
函数功能：初始化表
传入参数：表结点L的引用，用户键入的id。
时间复杂度是O(1)。空间复杂度是O(1)。
*/
/********************************************************************/
status InitList(ListN &L, int id) {
	if (!L) {
		L = (ListN)malloc(sizeof(List));
		L->head = (Lnode)malloc(sizeof(node));
		L->head->data = NULL;
		L->id = id;
		L->length = 0;
		L->next = NULL;
		return OK;
	}
	else
		return ERROR;
}

/********************************************************************/
/*
函数功能：销毁表
传入参数：表结点L的引用，L所在链表头结点的引用。
时间复杂度是O(n)。空间复杂度是O(1)。
*/
/********************************************************************/
status DestroyList(ListN &L, ListN &HeadL) {
	ListN tempH = HeadL;
	ClearList(L);
	if (L != HeadL) {
		while (HeadL->next != L) {
			HeadL = HeadL->next;
		}
		HeadL->next = L->next;
		free(L);
		HeadL = tempH;
	}
	else {
		HeadL = L->next;
		free(L);
	}
	return OK;
}

/********************************************************************/
/*
函数功能：清空表
传入参数：表结点L的引用。
时间复杂度是O(n)。空间复杂度是O(1)。
*/
/********************************************************************/
status ClearList(ListN &L) {
	Lnode temp = L->head;
	Lnode del = temp->next;
	for (int i = 0;i < L->length;i++)
	{
		temp = del->next;
		del = NULL;
		free(del);
		del = temp;
	}
	L->length = 0;
	return OK;
}

/********************************************************************/
/*
函数功能：判断空表
传入参数：表结点L的值。
时间复杂度是O(1)。空间复杂度是O(1)。
*/
/********************************************************************/
status ListEmpty(ListN L) {
	if (L->length) {
		printf("该线性表不为空! \n");
		return TRUE;
	}
	else {
		printf("该线性表为空! \n");
		return FALSE;
	}
}

/********************************************************************/
/*
函数功能：求表长
传入参数：表结点L的值。
时间复杂度是O(1)。空间复杂度是O(1)。
*/
/********************************************************************/
status ListLength(ListN L) {
	printf("该线性表的数据元素个数为：%d \n", L->length);
	return OK;
}

/********************************************************************/
/*
函数功能：获得元素
传入参数：表结点L的值，元素位置i，元素e的引用。
时间复杂度是O(n)。空间复杂度是O(1)。
*/
/********************************************************************/
status GetElem(ListN L, int i, ElemType & e) {
	if (i<1 || i>L->length) {
		printf("该线性表没有第%d个元素！\n", i);//考虑周全！
		return ERROR;
	}
	else {
		Lnode temp = L->head;
		for (int j = 0;j < i;j++) {
			temp = temp->next;
		}
		e = temp->data;
		printf("该线性表第%d个元素：%d \n", i, e);
		return OK;
	}
}

/********************************************************************/
/*
函数功能：查找元素
传入参数：表结点L的值，元素值e。
时间复杂度是O(n)。空间复杂度是O(1)。
*/
/********************************************************************/
status LocateElem(ListN L, ElemType e) {
	Lnode temp = L->head;
	for (int i = 0;i < L->length;i++) {
		temp = temp->next;
		if (e == temp->data) {
			printf("元素%d在该线性表第%d位! \n", e, i + 1);
			return OK;
		}
	}
	printf("该线性表不存在元素%d！\n", e);
	return ERROR;
}

/********************************************************************/
/*
函数功能：获得前驱
传入参数：表结点L的值，元素值cur，元素pre_e的引用
时间复杂度是O(n)。空间复杂度是O(1)。
*/
/********************************************************************/
status PriorElem(ListN L, ElemType cur, ElemType&pre_e) {
	Lnode temp = L->head->next;
	Lnode prior;
	for (int i = 1;i < L->length;i++) {
		prior = temp;
		temp = temp->next;
		if (cur == temp->data) {
			pre_e = prior->data;
			printf("元素%d的前驱是：%d \n", cur, pre_e);
			return OK;
		}
	}
	printf("元素%d的前驱不存在！\n", cur);
	return ERROR;
}

/********************************************************************/
/*
函数功能：获得后继
传入参数：表结点L的值，元素值cur，元素next_e的引用
时间复杂度是O(n)。空间复杂度是O(1)。
*/
/********************************************************************/
status NextElem(ListN L, ElemType cur, ElemType&next_e) {
	Lnode temp = L->head;
	for (int i = 1;i < L->length;i++) {
		temp = temp->next;
		if (cur == temp->data) {
			next_e = temp->next->data;
			printf("元素%d的后继是：%d \n", cur, next_e);
			return OK;
		}
	}
	printf("元素%d的后继不存在！\n", cur);
	return ERROR;
}

/********************************************************************/
/*
函数功能：插入元素
传入参数：表结点L的值，元素位置i，元素值e。
时间复杂度是O(n)。空间复杂度是O(1)。
*/
/********************************************************************/
status ListInsert(ListN L, int i, ElemType e) {
	if (i<1 || i>L->length + 1) {
		printf("请输入正确的插入位置！\n");
		return ERROR;
	}
	Lnode temp = L->head;
	Lnode node = (Lnode)malloc(sizeof(node));
	node->data = e;
	node->next = NULL;
	if (i == 1) {
		node->next = temp->next;
		L->head->next = node;
	}
	else {
		for (int j = 0;j < i - 1;j++)
		{
			temp = temp->next;
		}
		Lnode tempn = temp->next;
		temp->next = node;
		node->next = tempn;
	}
	L->length++;                      //线性表长度加1
	return OK;
}

/********************************************************************/
/*
函数功能：删除元素
传入参数：表结点L的值，元素位置i。
时间复杂度是O(n)。空间复杂度是O(1)。
*/
/********************************************************************/
status ListDelete(ListN L, int i, ElemType &e) {
	if (i<1 || i>L->length) {
		printf("请输入正确的删除位置！\n");
		return ERROR;
	}
	Lnode temp = L->head;
	for (int j = 0;j < i - 1;j++)
	{
		temp = temp->next;
	}
	if (L->length == i) {        //考虑表尾特殊情况
		e = temp->next->data;
		temp->next = NULL;
		free(temp->next);
	}
	else {
		Lnode del = temp->next;
		temp->next = del->next;
		e = del->data;
		del = NULL;                //必须要有这句！
		free(del);
	}
	L->length--;
	return OK;
}

/********************************************************************/
/*
函数功能：遍历表
传入参数：表结点L的值。
时间复杂度是O(n)。空间复杂度是O(1)。
*/
/********************************************************************/
status ListTraverse(ListN L) {
	Lnode temp = L->head;
	if (!L->length) {
		return FALSE;
	}
	else {
		int i;
		printf("\n-----------all elements -----------------------\n");
		for (i = 0;i < L->length;i++) {
			temp = temp->next;
			printf("%d ", temp->data);
		}
		printf("\n------------------ end ------------------------\n");
		return TRUE;
	}
}

/********************************************************************/
/*
函数功能：存储表
传入参数：表结点L的值。
时间复杂度是O(n)。空间复杂度是O(1)。
*/
/********************************************************************/
status ListSave(ListN L) {
	Lnode temp = L->head;
	FILE *fp;char road[30];
	printf("请输入文件存储路径：");
	scanf_s("%s", road, sizeof(road));
	errno_t X;
	if ((X = fopen_s(&fp, road, "w+")) != 0) {
		printf("请输入正确的存储路径！\n");
		return ERROR;
	}
	fprintf(fp, "%d\n", L->length);
	for (int i = 0;i < L->length;i++) {
		temp = temp->next;
		fprintf(fp, "%d\n", temp->data);
	}
	fclose(fp);
	return OK;
}

/********************************************************************/
/*
函数功能：读取表
传入参数：表结点L的引用。
时间复杂度是O(n)。空间复杂度是O(1)。
*/
/********************************************************************/
status ListRead(ListN &L) {
	FILE *fp;char road[30];
	printf("请输入文件读取路径：");
	scanf_s("%s", road, sizeof(road));
	errno_t X;
	if ((X = fopen_s(&fp, road, "r")) != 0) {
		printf("请输入正确的存储路径！\n");
		return ERROR;
	}
	fscanf_s(fp, "%d", &L->length);
	Lnode temp = L->head;
	for (int i = 0;i < L->length;i++) {
		Lnode node = (Lnode)malloc(sizeof(node));
		fscanf_s(fp, "%d", &node->data);
		node->next = NULL;
		temp->next = node;
		temp = temp->next;
	}
	fclose(fp);
	return OK;
}