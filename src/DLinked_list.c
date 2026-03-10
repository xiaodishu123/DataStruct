//
// Created by XDS on 2026/2/27.
//

#include "DLinked_list.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void DList_Init(DList* list)
{
    if (list == NULL) return;
    list->dummy.next = &list->dummy;
    list->dummy.prev = &list->dummy;
    list->size = 0;
}
static DListNode* CreateNode(DListValue value)
{
    DListNode* new_node = (DListNode*)malloc(sizeof(DListNode));
    if (new_node == NULL)
    {
        printf("Malloc Failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}
void DList_Destroy(DList* list)
{
    if (list == NULL) return;
    DListNode* current_node = list->dummy.next;
    while (current_node != &list->dummy)
    {
        DListNode* next = current_node->next;
        free(current_node);
        current_node = next;
    }
    list->dummy.next = &list->dummy;
    list->dummy.prev = &list->dummy;
    list->size = 0;
}
int DList_Size(const DList* list)
{
    if (list == NULL) return -1;
    return list->size;
}
int DList_Empty(const DList* list)
{
    if (list == NULL) return -1;
    if (list->size == 0) return 1;
    return 0;
}

DListValue DListFront(const DList* list)
{
    if (list == NULL)
    {
        printf("list is NULL\n");
        exit(EXIT_FAILURE);
    }
    return list->dummy.next->data;
}
DListValue DListBack(const DList* list)
{
    if (list == NULL)
    {
        printf("list is NULL\n");
        exit(EXIT_FAILURE);
    }
    return list->dummy.prev->data;
}
static int index_new(const DList* list,int index)
{
    int size = list->size;
    if (index == size)
    {
        return size;
    }
    int mid = (size - 1) / 2;
    if (index >= 0 && index < size)
    {
        if (index < mid) {
            // 在前半部分，返回正数（从头部移动的步数）
            return index;
        }
        else {
            // 在后半部分，返回负数（从尾部反向移动的步数）
            // 计算：从尾部需要反向移动多少步
            int steps_from_tail = size - 1 - index;
            return -1-steps_from_tail;  // 返回负数
        }
    }
    if (index < 0 && index >= -size)
    {
        if (size + index > mid)
        {
            return index;
        }
        else
        {
            return size + index;  // 返回正数
        }
    }
    printf("index is out of range\n");
    exit(EXIT_FAILURE);
}
DListValue DList_At(const DList* list, int index)
{
    if (list == NULL)
    {
        printf("list is NULL\n");
        exit(EXIT_FAILURE);
    }
    index = index_new(list,index);
    if (index < 0 && -index <= list->size)
    {
        DListNode* current = list->dummy.prev;
        for (int i = -1; i > index; i--)
        {
            current = current->prev;
        }
        return current->data;
    }
    if (index < 0 || index >= list->size)
    {
        printf("index is out of bound\n");
        exit(EXIT_FAILURE);
    }
    DListNode* current = list->dummy.next;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current->data;
}

void DList_Insert(DList* list, int index, DListValue value)
{
    DList_InsertBefore(list,DList_GetNode(list,index),value);
}
void DList_PushFront(DList* list, DListValue value)
{
    DList_Insert(list, 0, value);
}
void DList_PushBack(DList* list, DListValue value)
{
    DList_Insert(list, list->size, value);
}
void DList_InsertBefore(DList* list, DListNode* pos, DListValue value)
{
    if (list == NULL || pos == NULL) return;
    DListNode* new_node = CreateNode(value);
    new_node->next = pos;
    new_node->prev = pos->prev;
    pos->prev->next = new_node;
    pos->prev = new_node;
    list->size++;
}
void DList_InsertAfter(DList* list, const DListNode* pos, DListValue value)
{
    DListNode* new_pos = pos->next;
    DList_InsertBefore(list,new_pos,value);
}
int DList_Erase(DList* list, int index)
{
    return DList_EraseNode(list,DList_GetNode(list,index));
}
int DList_PopFront(DList* list)
{
    if (list == NULL)return 0;
    return DList_EraseNode(list, list->dummy.next);
}
int DList_PopBack(DList* list)
{
    if (list == NULL)return 0;
    return DList_EraseNode(list, list->dummy.prev);
}
int DList_Remove(DList* list, DListValue value)
{
    if (list == NULL)return 0;
    DListNode* current = list->dummy.next;
    while (current != NULL && current != &list->dummy)
    {
        if (current->data == value)
        {
            return DList_EraseNode(list, current);
        }
        current = current->next;
    }
    return 0;
}
int DList_RemoveAll(DList* list, DListValue value)
{
    if (list == NULL) return 0;
    DListNode* current = list->dummy.next;
    while (current != NULL && current != &list->dummy)
    {
        if (current->data == value)
        {
            DList_EraseNode(list, current);
        }
        current = current->next;
    }
    if (current == &list->dummy)
    {
        return 1;
    }
    return 0;
}

DListNode* DList_FindNode(const DList* list,DListValue value)
{
    if (list == NULL)return NULL;
    DListNode* current = list->dummy.next;
    while (current != &list->dummy)
    {
        if (current->data == value)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
DListNode* DList_GetNode(DList* list, int index)
{
    if (list == NULL)return NULL;
    index = index_new(list,index);
    if (index == list->size)
    {
        return &list->dummy;
    }
    if (index > list->size || -index > list->size)
    {
        printf("index is out of bound\n");
        exit(EXIT_FAILURE);
    }
    if (index >= 0)
    {
        DListNode* current = list->dummy.next;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current;
    }
    if (index < 0)
    {
        DListNode* current = list->dummy.prev;
        for (int i = -1; i > index; i--)
        {
            current = current->prev;
        }
        return current;
    }
    return NULL;
}
int DList_EraseNode(DList* list, DListNode* node)
{
    if (list == NULL || node == NULL)return 0;
    if (&list->dummy == node)
    {
        printf("dummy can`t EraseNode\n");
        return 0;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    list->size--;
    return 1;
}


static void DListNode_Swap(DList* list, DListNode* node1, DListNode* node2)
{
    if (list == NULL || node1 == NULL || node2 == NULL)return;
    if (node1->next == node2) {  // node1在node2前面
        // 调整node1的前驱节点
        if (node1->prev != NULL)
            node1->prev->next = node2;
        // 调整node2的后继节点
        if (node2->next != NULL)
            node2->next->prev = node1;
        // 交换两个节点的指针
        node1->next = node2->next;
        node2->prev = node1->prev;
        node1->prev = node2;
        node2->next = node1;
    }
    else if (node2->next == node1) {
        DListNode_Swap(list, node2, node1);  // 递归调用
    }
    else {  // 不相邻的节点
        // 保存原始的前后节点
        DListNode* node1_prev = node1->prev;
        DListNode* node1_next = node1->next;
        DListNode* node2_prev = node2->prev;
        DListNode* node2_next = node2->next;

        // 更新前后节点的指针
        if (node1_prev != NULL) node1_prev->next = node2;
        if (node1_next != NULL) node1_next->prev = node2;
        if (node2_prev != NULL) node2_prev->next = node1;
        if (node2_next != NULL) node2_next->prev = node1;

        // 交换节点的指针
        node1->prev = node2_prev;
        node1->next = node2_next;
        node2->prev = node1_prev;
        node2->next = node1_next;
    }
}

void DList_Reverse(DList* list)
{
    if (list == NULL)return;
    DListNode* current = list->dummy.next;
    DListNode* current2 = list->dummy.prev;
    for (int i = 0; i < list->size/2; i++)
    {
        DListNode_Swap(list, current, current2);
        DListNode* temp = current->prev;
        current = current2->next;
        current2 = temp;
    }
}

//need after sort
void DList_Unique(DList* list)
{
    if (list == NULL)
    {
        printf("list is NULL\n");
        return;
    }
    DListNode* current = list->dummy.next;
    while (current != NULL && current != &list->dummy)
    {
        if (current->data == current->next->data)
        {
            DList_EraseNode(list, current->next);
        }else
        {
            current = current->next;
        }
    }
}

void DList_Sort(DList* list)
{
    if (list == NULL)
    {
        printf("sorted list is NULL\n");
        return;
    }
    for (int i = 0; i < list->size-1; i++)
    {
        DListNode* current = list->dummy.next;
        while (current != NULL && current->next != &list->dummy)
        {
            int end = current->data - current->next->data;
            if (end > 0)
            {
                DListNode_Swap(list, current, current->next);
            }else{
                current = current->next;//else防止竞争关系
            }
        }
    }
}

void DList_SortWithCompare(DList* list,CompareFunc myfunc)
{
    if (list == NULL)return;
    for (int i = 0; i < list->size-1; i++)
    {
        DListNode* current = list->dummy.next;
        while (current != NULL && current->next != &list->dummy)
        {
            int end = myfunc(current->data,current->next->data);
            if (end > 0)
            {
                DListNode_Swap(list, current, current->next);
            }else{
                current = current->next;//else防止竞争关系
            }
        }
    }
}


void DList_Traverse(const DList* list, DListTraverseFunc func, void* context)
{
    if (list == NULL)
    {
        printf("list is NULL\n");
        return;
    }
    DListNode* current = list->dummy.next;
    while (current != NULL && current != &list->dummy)
    {
        func(current, context);
        current = current->next;
    }
}

void DList_TraverseReverse(const DList* list, DListTraverseFunc func, void* context)
{
    if (list == NULL)
    {
        printf("list is NULL\n");
        return;
    }
    DListNode* current = list->dummy.prev;
    while (current != NULL && current != &list->dummy)
    {
        func(current, context);
        current = current->prev;
    }
}