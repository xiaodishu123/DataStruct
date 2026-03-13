//
// Created by XDS on 2026/3/12.
//

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "Hash_table.h"

void HashLinkedList_Init(HashList* list)
{
    if (list == NULL)return;
    list->dummy.value = 1;
    list->dummy.next = NULL;
    list->size = 0;
}
static HashListNode* CreateHashNode(key_type key,value_type value) {
    HashListNode* new_node = (HashListNode*)malloc(sizeof(HashListNode));
    if (new_node == NULL) {
        printf("Memory Error!\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}
int HashLinkedList_Size(const HashList* list)
{
    if (list == NULL)return -1;
    return list->size;
}
int HashLinkedList_Empty(const HashList* list)
{
    if (list == NULL)return -1;
    if (list->dummy.next == NULL)return 1;
    return 0;
}
void HashLinkedList_Destroy(HashList* list)
{
    if (list == NULL)return;
    HashListNode* current = list->dummy.next;
    while (current != NULL)
    {
        HashListNode* next = current->next;
        free(current);
        current = next;
    }
    list->dummy.next = NULL;
    list->size = 0;
}
void HashList_Insert(HashList* list, int key, int value)
{
    HashListNode* new_node = CreateHashNode(key, value);
    assert(new_node != NULL);
    HashListNode* temp = list->dummy.next;
    list->dummy.next = new_node;
    new_node->next = temp;
    list->size++;
}

HashListNode* HashList_Find(const HashList* list, int key)
{
    if (list == NULL)return NULL;
    HashListNode* current = list->dummy.next;
    while (current != NULL)
    {
        if (current->key == key)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int HashList_Remove(HashList* list, int key)
{
    if (list == NULL)return -1;
    HashListNode* prev = &list->dummy;
    while (prev->next != NULL)
    {
        if (prev->next->key == key)
        {
            HashListNode* removed_node = prev->next;
            prev->next = prev->next->next;
            free(removed_node);
            removed_node = NULL;
            list->size--;
            return 1;
        }
        prev = prev->next;
    }
    return -1;
}
void HashList_Traverse(const HashList* list, HashListTraverseFunc func, void* context)
{
    if (list == NULL)
    {
        printf("HashList is NULL!\n");
        return;
    };
    HashListNode* current = list->dummy.next;
    while (current != NULL)
    {
        func(current->key, current->value, context);
        current = current->next;
    }
}

//========================================
HashTable* HashTable_Create(int capacity)
{
    if (capacity <= 0)
    {
        capacity = DEFAULT_CAPACITY;//默认容量
    };
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL)
    {
        printf("Memory Error!\n");
        return NULL;
    }
    HashList* hl = (HashList*)malloc(sizeof(HashList)*capacity);
    if (hl == NULL)
    {
        printf("Memory Error!\n");
        free(table);
        return NULL;
    }
    table->buckets = hl;
    table->size = 0;
    table->capacity = capacity;
    HashList* currrent = table->buckets;
    for (int i = 0; i < capacity; i++)
    {
        HashLinkedList_Init(currrent);
        currrent++;
    }
    return table;
}
void HashTable_Destroy(HashTable* table) {
    if (!table)
    {
        printf("HashTable is NULL!\n");
        return;
    };
    for (int i = 0; i < table->capacity; i++) {
        HashLinkedList_Destroy(&table->buckets[i]);
    }
    free(table->buckets);
    free(table);
}

int HashTable_Size(const HashTable* table)
{
    if (table == NULL)
    {
        printf("HashTable is NULL!\n");
        return -1;
    }
    return table->size;
}
int HashTable_Capacity(const HashTable* table)
{
    if (table == NULL)
    {
        printf("HashTable is NULL!\n");
        return -1;
    }
    return table->capacity;
}
int HashTable_IsEmpty(const HashTable* table)
{
    if (table == NULL)
    {
        printf("HashTable is NULL!\n");
        return -1;
    }
    if (table->size == 0)
    {
        return 1;
    }
    return 0;
}
float HashTable_LoadFactor(const HashTable* table)//负载因子
{
    if (table == NULL)
    {
        printf("HashTable is NULL!\n");
        return -1;
    }
    return (float)table->size / (float)table->capacity;
}
static unsigned int hash_fun(key_type key, int table_size) {//简单哈希函数
    return (unsigned int)key % table_size;
}
int HashTable_Put(HashTable* table, key_type key, value_type value)//插入成功返回1，更新成功返回2
{
    if (table == NULL)
    {
        printf("HashTable is NULL!\n");
        return -1;
    }
    unsigned int index = hash_fun(key, table->capacity);
    if (index >= table->capacity)
    {
        printf("HashTable table hash_fun error!\n");
        return -1;
    }
    HashListNode* current = HashList_Find(&table->buckets[index], key);
    if (current == NULL)
    {
        HashList_Insert(&table->buckets[index], key, value);
        table->size++;
        return 1;
    }
    current->value = value;
    return 2;
}
int HashTable_Get(const HashTable* table, key_type key, int* out_value)
{
    if (table == NULL)
    {
        printf("HashTable is NULL!\n");
        return -1;
    }
    unsigned int index = hash_fun(key, table->capacity);
    if (index >= table->capacity)
    {
        printf("HashTable table hash_fun error!\n");
        return -1;
    }
    HashListNode* current = HashList_Find(&table->buckets[index], key);
    if (current == NULL)
    {
        return 0;
    }
    *out_value = current->value;
    return 1;
}
int HashTable_Remove(HashTable* table, key_type key)
{
    if (table == NULL)
    {
        printf("HashTable is NULL!\n");
        return -1;
    }
    unsigned int index = hash_fun(key, table->capacity);
    if (index >= table->capacity)
    {
        printf("HashTable table hash_fun error!\n");
        return -1;
    }
    if (HashList_Remove(&table->buckets[index],key) == 1)
    {
            table->size--;
            return 1;
    }
    return 0;
}
int HashTable_ContainsKey(const HashTable* table, key_type key)
{
    if (table == NULL)
    {
        printf("HashTable is NULL!\n");
        return -1;
    }
    unsigned int index = hash_fun(key, table->capacity);
    if (index >= table->capacity)
    {
        printf("HashTable table hash_fun error!\n");
        return -1;
    }
    return HashList_Find(&table->buckets[index], key) != NULL ? 1 : 0;
}


void HashTable_Traverse(const HashTable* table, HashListTraverseFunc func, void* context)
{
    if (table == NULL)
    {
        printf("HashTable is NULL!\n");
        return;
    }
    for (int i = 0; i < table->capacity; i++)
    {
        HashList_Traverse(&table->buckets[i], func, context);
    }
}
void HashTable_Print(const HashTable* table)
{
    if (table == NULL)
    {
        printf("HashTable is NULL!\n");
        return;
    }
    for (int i = 0; i < table->capacity; i++)
    {
        printf("buckets%d\n", i+1);
        HashList* list = &table->buckets[i];
        if (list == NULL)
        {
            printf("HashList is NULL!\n");
            return;
        };
        HashListNode* current = list->dummy.next;
        while (current != NULL)
        {

            printf("%d->%d\n", current->key,current->value);
            current = current->next;
        }
    }
}
void HashTable_Clear(HashTable* table) {
    if (!table) return;
    for (int i = 0; i < table->capacity; i++) {
        HashLinkedList_Destroy(&table->buckets[i]);
    }
    table->size = 0;
}