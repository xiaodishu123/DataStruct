//
// Created by XDS on 2026/2/25.
//

#ifndef DATASTRUCT_LINKED_LIST_H
#define DATASTRUCT_LINKED_LIST_H

typedef int LLDataType;

// 链表节点
typedef struct LinkedListNode {
    LLDataType data;
    struct LinkedListNode* next;
} LLNode;

// 链表结构
typedef struct {
    LLNode dummy;      // 哨兵节点，dummy.next指向第一个真实节点
    LLNode* tail;      // 指向最后一个节点
    int size;          // 节点数量
} LinkedList;

// 基础操作
void LinkedList_Init(LinkedList* list);
void LinkedList_Destroy(LinkedList* list);
int LinkedList_Size(const LinkedList* list);
int LinkedList_Empty(const LinkedList* list);
void LinkedList_Free(LinkedList* list);

// 插入操作
void LinkedList_Insert(LinkedList* list, int index, LLDataType value);
void LinkedList_PushFront(LinkedList* list, LLDataType value);
void LinkedList_PushBack(LinkedList* list, LLDataType value);

// 删除操作
void LinkedList_Erase(LinkedList* list, int index);
void LinkedList_PopFront(LinkedList* list);
void LinkedList_PopBack(LinkedList* list);

// 查找访问
int LinkedList_Find(const LinkedList* list, LLDataType value);
LLDataType LinkedList_At(const LinkedList* list, int index);
LLNode* LinkedList_GetNode(const LinkedList* list, int index);
LLNode* LinkedList_GetBackNode(const LinkedList* list);

// 批量操作
//void LinkedList_FromArray(LinkedList* list, const LLDataType* arr, int n);
//int LinkedList_ToArray(const LinkedList* list, LLDataType* arr, int capacity);


#endif //DATASTRUCT_LINKED_LIST_H