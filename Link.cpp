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

//����ͷ�ڵ�
struct link* Create(void)
{
	struct link* p = (struct link*)malloc(sizeof(struct link));
	if (NULL == p)
		DEBUG_PRINT;
	memset(p, 0, sizeof(struct link));
	return p;
}

//�����ڵ�
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

//����һ���ڵ�(ͷ�巨)
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

//����һ���ڵ�(β�巨)
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

//���ҽڵ�
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

//ɾ���ڵ�
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
		printf("û��%d�������!\n", data);
		return;
	}
	pdel = p->next;
	p->next = pdel->next;
	free(pdel);
}

//��������
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

//������ӡ
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

//�ͷ���������ڵ�
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

//����������д���ļ�
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


//���ļ���������
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
		printf("�ļ�Ϊ��,û�м��ص�����!\n");
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
		data = rand() % 100;	//�����
		InsertTailNode(head, data);
		//InsertHeadNode(head, data);
	}
	Display(head);

	//ɾ��
	printf("������Ҫɾ������:");
	scanf_s(" %d", &data);
	DeleteNode(head, data);
	printf("ɾ����:\n");
	Display(head);

	//����
	printf("������Ҫ���ҵ���:");
	scanf_s(" %d", &data);
	p = FindNode(head, data);
	if (p != NULL)
	{
		printf("�Ѳ��ҵ�����%d!\n", data);
	}
	else {
		printf("û���ҵ�%d������!\n", data);
	}

	//����
	SortLink(head);
	printf("�����:\n");
	Display(head);

	SaveToFile(FILEPATH, head);

	FreeLinkNode(head);
}