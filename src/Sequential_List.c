//
// Created by XDS on 2026/1/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/Sequential_List.h"

void SeqListInit(SeqList* ps)
{
    if (ps == NULL)return;
    ps->data = (SLDataType*)malloc(SEQLIST_INIT_SIZE * sizeof(SLDataType));
    if (ps->data == NULL)
    {
        printf("Memory Error!\n");
        exit(EXIT_FAILURE);
    }
    ps->size = 0;
    ps->capacity = SEQLIST_INIT_SIZE;
}
void SeqListDestroy(SeqList* ps)
{
    if (ps == NULL)return;
    free(ps->data);
    ps->data = NULL;
    ps->size = 0;
}
void SeqListClear(SeqList* ps)
{
    if (ps == NULL)return;
    ps->size = 0;
}
static void SeqListCheckCapacity(SeqList* ps)
{
    if (ps == NULL)return;
    if (ps->size == ps->capacity)
    {
        int newcapacity = ps->capacity == 0 ? SEQLIST_INIT_SIZE : ps->capacity * 2;
        SLDataType *temp = (SLDataType*)realloc(ps->data,newcapacity * sizeof(SLDataType));
        if (temp == NULL)
        {
            printf("Memory Error!\n");
            exit(EXIT_FAILURE);
        }
        ps->data = temp;
        ps->capacity = newcapacity;
    }
}
//add
void SeqListPushBack(SeqList* ps, const SLDataType x)
{
    if (ps == NULL)return;
    SeqListCheckCapacity(ps);
    ps->data[ps->size] = x;
    ps->size++;
}
void SeqListPushFront(SeqList* ps,SLDataType x)
{
    SeqListInsert(ps, 0, x);
}
void SeqListAppendArray(SeqList *ps, const SLDataType *Array, const int ArraySize)
{
    if (ps == NULL || Array == NULL ||ArraySize <= 0)return;
    for (int i = 0; i < ArraySize; i++)
    {
        SeqListPushBack(ps,Array[i]);
    }
}
void SeqListInsert(SeqList* ps, const int pos,SLDataType x)
{
    if (ps == NULL)return;
    if (pos < 0 || pos > ps->size-1)
    {
        printf("Out of Range!\n");
        exit(EXIT_FAILURE);
    }
    SeqListCheckCapacity(ps);
    for(int i = ps->size; i >= pos; i--)
    {
        ps->data[i] = ps->data[i-1];
    }
    ps->data[pos] = x;
    ps->size++;
}

//
//pop
void SeqListPopBack(SeqList* ps)
{
    if (ps == NULL || ps->size <= 0)return;
    ps->size--;
}
void SeqListErase(SeqList* ps, const int pos)
{
    if (ps == NULL)return;
    if (pos < 0 || pos > ps->size-1)
    {
        printf("Out of Range!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = pos;i < ps->size-1; i++)
    {
        ps->data[i] = ps->data[i+1];
    }
    ps->size--;
}
void SeqListPopFront(SeqList* ps)
{
    SeqListErase(ps,0);
}




//
//
int SeqListFind(SeqList* ps, const SLDataType x)
{
    if (ps == NULL)return -1;
    for (int i = 0; i < ps->size; i++)
    {
        if (ps->data[i] == x)
        {
            return i;
        }
    }
    return -1;
}
int SeqListSize(SeqList* ps)
{
    if (ps == NULL)return -1;
    return ps->size;
}
int SeqListIsEmpty(SeqList* ps)
{
    if (ps == NULL)return -1;
    if (ps->size == 0)return 1;
    return 0;
}
SLDataType SeqListGetElem(SeqList* ps,const int pos)
{
    if (ps == NULL)
    {
        printf("SeqList is NULL!\n");
        exit(EXIT_FAILURE);
    }
    if (pos < 0 || pos >= ps->size)
    {
        printf("Out of Range!\n");
        exit(EXIT_FAILURE);
    }
    return ps->data[pos];
}
//


//
SeqList* SeqListCreat(const SLDataType *Array, const int ArraySize)
{
    SeqList* new_list = (SeqList*)malloc(sizeof(SeqList));
    if (new_list == NULL)
    {
        printf("Memory Error!\n");
        exit(EXIT_FAILURE);
    }
    SeqListInit(new_list);
    SeqListAppendArray(new_list,Array,ArraySize);
    return new_list;
}
void SeqListFree(SeqList* ps)
{
    if (ps == NULL)return;
    SeqListDestroy(ps);
    free(ps);
    ps = NULL;
}
//