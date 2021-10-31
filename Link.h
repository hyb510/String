//#pragma once
#ifndef  __LINK_H__
#define  __LINK_H__
#include "Link.h"
#endif


//创建头节点
struct link* Create(void);

//创建节点
struct link* CreateNode(int data);

//插入一个节点(头插法)
void InsertHeadNode(struct link* head, int data);

//插入一个节点(尾插法)
void InsertTailNode(struct link* head, int data);

//查找节点
struct link* FindNode(struct link* head, int data);

//删除节点
void DeleteNode(struct link* head, int data);

//链表排序
void SortLink(struct link* head);

//遍历打印
void Display(struct link* head);

//释放所有链表节点
void FreeLinkNode(struct link* head);

//将链表数据写入文件
void SaveToFile(const char* const path, struct link* head);

//从文件加载数据
void LoadFromFile(const char* path, struct link* head);