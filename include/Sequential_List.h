//
// Created by XDS on 2026/1/18.
//

#ifndef DATASTRUCT_SEQUENTIAL_LIST_H
#define DATASTRUCT_SEQUENTIAL_LIST_H

typedef int SLDataType;
typedef struct
{
    SLDataType* data;
    int size;
    int capacity;
} SeqList;

#define SEQLIST_INIT_SIZE 4

void SeqListInit(SeqList* ps);
void SeqListDestroy(SeqList* ps);
void SeqListClear(SeqList* ps);
void SeqListInsert(SeqList* ps,int pos,SLDataType x);
void SeqListPushBack(SeqList* ps,SLDataType x);
void SeqListPushFront(SeqList* ps,SLDataType x);
void SeqListAppendArray(SeqList *ps, const SLDataType *Array,int ArraySize);

void SeqListErase(SeqList* ps,int pos);
void SeqListPopBack(SeqList* ps);
void SeqListPopFront(SeqList* ps);

int SeqListFind(SeqList* ps,SLDataType x);
int SeqListSize(SeqList* ps);
int SeqListIsEmpty(SeqList* ps);
SLDataType SeqListGetElem(SeqList* ps,int pos);

SeqList* SeqListCreat(const SLDataType *Array,int ArraySize);
void SeqListFree(SeqList* ps);



#endif //DATASTRUCT_SEQUENTIAL_LIST_H