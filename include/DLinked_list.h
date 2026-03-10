//
// Created by XDS on 2026/2/27.
//

#ifndef DATASTRUCT_DLINKED_LIST_H
#define DATASTRUCT_DLINKED_LIST_H

typedef int DListValue;

// 双向链表节点
typedef struct DListNode {
    DListValue data;
    struct DListNode* prev;
    struct DListNode* next;
} DListNode;

// 双向循环链表
typedef struct {
    DListNode dummy;  // 哨兵节点，dummy.next是头，dummy.prev是尾
    int size;
} DList;

// 初始化：dummy.next = dummy.prev = &dummy
// 空链表时：dummy -> dummy（循环）

// 基本操作
void DList_Init(DList* list);
void DList_Destroy(DList* list);
int DList_Size(const DList* list);
int DList_Empty(const DList* list);

// 元素访问
DListValue DList_Front(const DList* list);
DListValue DList_Back(const DList* list);
DListValue DList_At(const DList* list, int index);

// 插入操作
void DList_Insert(DList* list, int index, DListValue value);
void DList_PushFront(DList* list, DListValue value);
void DList_PushBack(DList* list, DListValue value);
void DList_InsertBefore(DList* list, DListNode* pos, DListValue value);
void DList_InsertAfter(DList* list, const DListNode* pos, DListValue value);

// 删除操作
int DList_Erase(DList* list, int index);
int DList_PopFront(DList* list);
int DList_PopBack(DList* list);
int DList_Remove(DList* list, DListValue value);
int DList_RemoveAll(DList* list, DListValue value);

// 节点操作
DListNode* DList_FindNode(const DList* list,DListValue value);
DListNode* DList_GetNode(DList* list, int index);
int DList_EraseNode(DList* list, DListNode* node);  // O(1)删除节点

// 链表操作
void DList_Reverse(DList* list);
void DList_Unique(DList* list);//need after sort
void DList_Sort(DList* list);
typedef int (*CompareFunc)(DListValue, DListValue);
void DList_SortWithCompare(DList* list,CompareFunc myfunc);

// 遍历
typedef void (*DListTraverseFunc)(DListNode* node, void* context);
void DList_Traverse(const DList* list, DListTraverseFunc func, void* context);
void DList_TraverseReverse(const DList* list, DListTraverseFunc func, void* context);

#endif //DATASTRUCT_DLINKED_LIST_H