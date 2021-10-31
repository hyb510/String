#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define DEBUG_PRINT		printf("%s %d:head is NULL\n", __FILE__, __LINE__)
#define FILEPATH "data.bin"
using namespace std;

struct link
{
	int data;
	struct link* next;
};

//创建头节点
struct link* Create(void)
{
	struct link* p = (struct link*)malloc(sizeof(struct link));
	if (NULL == p)
		DEBUG_PRINT;
	memset(p, 0, sizeof(struct link));
	return p;
}

//创建节点
struct link* CreateNode(int data)
{
	struct link* p = (struct link*)malloc(sizeof(struct link));
	if (NULL == p)
	{
		DEBUG_PRINT;
		return NULL;
	}
	memset(p, 0, sizeof(struct link));
	p->data = data;
	return p;
}

//插入一个节点(头插法)
void InsertHeadNode(struct link* head, int data)
{
	struct link* node = NULL;
	if (NULL == head)
	{
		DEBUG_PRINT;
		return;
	}
	node = CreateNode(data);
	node->next = head->next;
	head->next = node;
}

//插入一个节点(尾插法)
void InsertTailNode(struct link* head, int data)
{
	struct link* p = NULL, * node = NULL;
	if (NULL == head)
	{
		DEBUG_PRINT;
		return;
	}
	node = CreateNode(data);
	p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = node;
	node->next = NULL;
}

//查找节点
struct link* FindNode(struct link* head, int data)
{
	struct link* p = NULL;
	if (NULL == head)
	{
		DEBUG_PRINT;
		return NULL;
	}
	p = head;
	while (p->next != NULL)
	{
		if (p->next->data == data)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

//删除节点
void DeleteNode(struct link* head, int data)
{
	struct link* pdel = NULL, * p = NULL;
	if (NULL == head)
	{
		DEBUG_PRINT;
		return;
	}
	p = FindNode(head, data);
	if (NULL == p)
	{
		printf("没有%d这个数据!\n", data);
		return;
	}
	pdel = p->next;
	p->next = pdel->next;
	free(pdel);
}

//链表排序
void SortLink(struct link* head)
{
	struct link* p = NULL, * q = NULL, * pos = NULL;
	int temp = 0;
	if (NULL == head || head->next == NULL)
	{
		printf("%s %d:head or head->next is NULL\n", __FILE__, __LINE__);
		return;
	}
	for (p = head->next; p->next != NULL; p = p->next)
	{
		for (pos = p, q = p->next; q != NULL; q = q->next)
		{
			if (q->data < pos->data)	//if(pos->data > q->data)
			{
				pos = q;
			}
		}
		if (pos != p)
		{
			temp = p->data;
			p->data = pos->data;
			pos->data = temp;
		}
	}
}

//遍历打印
void Display(struct link* head)
{
	struct link* p = NULL;
	if (NULL == head)
	{
		DEBUG_PRINT;
		return;
	}
	p = head->next;
	while (p != NULL)
	{
		printf("p:%p,p->data:%d,p->next:%p\n", p, p->data, p->next);
		p = p->next;
	}
}

//释放所有链表节点
void FreeLinkNode(struct link* head)
{
	struct link* p = NULL, * q = NULL;
	if (NULL == head)
	{
		DEBUG_PRINT;
		return;
	}
	p = head->next;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
	free(head);
	//head = NULL;
	//p = NULL;
	//q = NULL;
}

//将链表数据写入文件
void SaveToFile(const char* const path, struct link* head)
{
	FILE* fp = NULL;
	struct link* p = NULL;
	if (NULL == head || NULL == path)
	{
		printf("%s %d:head or file is NULL!\n", __FILE__, __LINE__);
		return;
	}
	fopen_s(&fp, FILEPATH, "wb");
	//if (NULL == fp)
	//{
	//	perror("file open failed in load");
	//	return;
	//}
	p = head->next;
	while (NULL != p)
	{
		fwrite(&p->data, sizeof(p->data), 1, fp);
		p = p->next;
	}
	if (ferror(fp))
	{
		perror("Load file error!\n");
	}
	fclose(fp);
	fp = NULL;
}


//从文件加载数据
void LoadFromFile(const char* path, struct link* head)
{
	int data = 0;
	FILE* fp = NULL;
	if (NULL == head || NULL == path)
	{
		printf("%s %d:head or file is NULL!\n", __FILE__, __LINE__);
		return;
	}
	//fp = fopen(path, "rb");
	//if (NULL == fp)
	//{
	//	perror("file open failed in load");
	//	return;
	//}
	fopen_s(&fp, FILEPATH, "rb");
	if (NULL == fp)
	{
		printf("文件为空,没有加载到内容!\n");
		return;
	}
	while (fread(&data, sizeof(data), 1, fp) > 0)
	{
		InsertTailNode(head, data);
	}
	if (ferror(fp)) {
		perror("Load file error!\n");
	}
	fclose(fp);
	fp = NULL;
}


int main(void)
{
	int i = 0, data = 0;
	struct link* p = NULL;
	struct link* head = Create();
	LoadFromFile(FILEPATH, head);
	for (i = 0; i < 10; i++)
	{
		//data = i + 1;		//rand()%100;
		data = rand() % 100;	//随机数
		InsertTailNode(head, data);
		//InsertHeadNode(head, data);
	}
	Display(head);

	//删除
	printf("请输入要删除的数:");
	scanf_s(" %d", &data);
	DeleteNode(head, data);
	printf("删除后:\n");
	Display(head);

	//查找
	printf("请输入要查找的数:");
	scanf_s(" %d", &data);
	p = FindNode(head, data);
	if (p != NULL)
	{
		printf("已查找到数据%d!\n", data);
	}
	else {
		printf("没有找到%d的数据!\n", data);
	}

	//排序
	SortLink(head);
	printf("排序后:\n");
	Display(head);

	SaveToFile(FILEPATH, head);

	FreeLinkNode(head);
}