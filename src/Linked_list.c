#include "../include/Linked_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
//
// Created by XDS on 2026/2/25.
//


void LinkedList_Init(LinkedList* list)
{
    if (list == NULL)return;
    list->dummy.data = 0;
    list->dummy.next = NULL;
    list->tail = &(list->dummy);
    list->size = 0;
}
// CreateNode
static LLNode* CreateNode(LLDataType value) {
    LLNode* new_node = (LLNode*)malloc(sizeof(LLNode));
    if (new_node == NULL) {
        printf("Memory Error!\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}
void LinkedList_Destroy(LinkedList* list)
{
    if (list == NULL)return;
    LLNode* current = list->dummy.next;
    while (current != NULL)
    {
        LLNode* next = current->next;
        free(current);
        current = next;
    }
    list->dummy.next = NULL;
    list->tail = &(list->dummy);
    list->size = 0;
}
int LinkedList_Size(const LinkedList* list)
{
    if (list == NULL)return -1;
    return list->size;
}
int LinkedList_Empty(const LinkedList* list)
{
    if (list == NULL)return -1;
    if (list->dummy.next == NULL)return 1;
    return 0;
}
void LinkedList_Free(LinkedList* list)
{
    if (list == NULL)return;
    LinkedList_Destroy(list);
    free(list);
    list = NULL;
}

void LinkedList_Insert(LinkedList* list, int index, LLDataType value)
{
    if (list == NULL)return;
    if (index < 0 || index > list->size)
    {
        printf("Index Error!\n");
        return;
    }
    LLNode* new_node = CreateNode(value);
    assert(new_node != NULL);
    LLNode* prev = &(list->dummy);
    for (int i = 0; i < index; i++)
    {
        prev = prev->next;
    }
    new_node->next = prev->next;
    prev->next = new_node;
    list->size++;
    if (prev == list->tail)
    {
        list->tail = new_node;
    }
}
void LinkedList_PushFront(LinkedList* list, LLDataType value)
{
    LinkedList_Insert(list, 0, value);
}
void LinkedList_PushBack(LinkedList* list, LLDataType value)
{
    if (list == NULL)return;
    LLNode* new_node = CreateNode(value);
    assert(new_node != NULL);
    list->tail->next = new_node;
    list->tail = new_node;
    list->size++;
}

void LinkedList_Erase(LinkedList* list, int index)
{
    if (list == NULL)return;
    if (index < 0 || index >= list->size)
    {
        printf("Index Error!\n");
        return;
    }
    LLNode* prev = &(list->dummy);
    for (int i = 0; i < index; i++)
    {
        prev = prev->next;
    }
    if (prev->next == list->tail)
    {
        list->tail = prev;
    }
    LLNode* to_delete = prev->next;
    prev->next = prev->next->next;
    free(to_delete);
    list->size--;
}
void LinkedList_PopFront(LinkedList* list)
{
    if (list == NULL)return;
    LinkedList_Erase(list, 0);
}
void LinkedList_PopBack(LinkedList* list)
{
    if (list == NULL)return;
    LinkedList_Erase(list,list->size-1);
}

int LinkedList_Find(const LinkedList* list, LLDataType value)
{
    if (list == NULL)return -1;
    LLNode* current = list->dummy.next;
    for (int i = 0; i < list->size; i++)
    {
        if (current->data == value)
        {
            return i;
        }
        current = current->next;
    }
    return -1;
}
LLDataType LinkedList_At(const LinkedList* list, int index)
{
    if (list == NULL)
    {
        printf("LinkList is NULL!\n");
        exit(EXIT_FAILURE);
    }
    if (index < 0 || index >= list->size)
    {
        printf("Index Error!\n");
        exit(EXIT_FAILURE);
    }
    LLNode* get_node = LinkedList_GetNode(list, index);
    if (get_node == NULL)
    {
        printf("Node Error!\n");
        exit(EXIT_FAILURE);
    }
    return get_node->data;
}
LLNode* LinkedList_GetNode(const LinkedList* list, int index)
{
    if (list == NULL)return NULL;
    if (index < 0 || index >= list->size)
    {
        printf("Index Error!\n");
        return NULL;
    }
    if (index == list->size - 1)
    {
        return list->tail;
    }
    LLNode* current = list->dummy.next;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current;
}
LLNode* LinkedList_GetBackNode(const LinkedList* list)
{
    if (list == NULL)return NULL;
    return LinkedList_GetNode(list,list->size - 1);
}
