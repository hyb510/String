//#pragma once
#ifndef  __LINK_H__
#define  __LINK_H__
#include "Link.h"
#endif


//����ͷ�ڵ�
struct link* Create(void);

//�����ڵ�
struct link* CreateNode(int data);

//����һ���ڵ�(ͷ�巨)
void InsertHeadNode(struct link* head, int data);

//����һ���ڵ�(β�巨)
void InsertTailNode(struct link* head, int data);

//���ҽڵ�
struct link* FindNode(struct link* head, int data);

//ɾ���ڵ�
void DeleteNode(struct link* head, int data);

//��������
void SortLink(struct link* head);

//������ӡ
void Display(struct link* head);

//�ͷ���������ڵ�
void FreeLinkNode(struct link* head);

//����������д���ļ�
void SaveToFile(const char* const path, struct link* head);

//���ļ���������
void LoadFromFile(const char* path, struct link* head);