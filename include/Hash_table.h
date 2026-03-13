//
// Created by XDS on 2026/3/12.
//

#ifndef DATASTRUCT_HASH_TABLE_H
#define DATASTRUCT_HASH_TABLE_H
// ========================================
//专用哈希表链表
typedef int key_type;
typedef int value_type;
typedef struct HashListNode {
    key_type key;
    value_type value;
    struct HashListNode* next;
} HashListNode;

// 哈希表链表（单向，带哨兵节点）
typedef struct {
    HashListNode dummy;  //哨兵节点
    int size;
} HashList;

// 基础操作
void HashLinkedList_Init(HashList* list);
int HashLinkedList_Size(const HashList* list);
int HashLinkedList_Empty(const HashList* list);
void HashLinkedList_Destroy(HashList* list);
// 插入操作 (头部插入)
void HashList_Insert(HashList* list, int key, int value);

// 查找操作（返回找到的节点指针，找不到返回NULL）
HashListNode* HashList_Find(const HashList* list, int key);

// 删除操作（删除指定键节点）
int HashList_Remove(HashList* list, int key);

// 遍历操作
typedef void (*HashListTraverseFunc)(int key, int value, void* context);
void HashList_Traverse(const HashList* list, HashListTraverseFunc func, void* context);
// ========================================

// ==================== 哈希表主体 ====================
typedef struct {
    HashList* buckets;   // 桶数组，每个桶是一个专用链表
    int capacity;        // 桶的数量
    int size;            // 键值对总数
} HashTable;
#define DEFAULT_CAPACITY 17
#define MAX_LOAD_FACTOR 0.75
// 创建和销毁
HashTable* HashTable_Create(int capacity);
void HashTable_Destroy(HashTable* table);

// 基本信息
int HashTable_Size(const HashTable* table);
int HashTable_Capacity(const HashTable* table);
int HashTable_IsEmpty(const HashTable* table);
float HashTable_LoadFactor(const HashTable* table);

// 核心操作
int HashTable_Put(HashTable* table, key_type key, value_type value);
int HashTable_Get(const HashTable* table, key_type key, value_type* out_value);
int HashTable_Remove(HashTable* table, key_type key);
int HashTable_ContainsKey(const HashTable* table, key_type key);

// 工具函数
void HashTable_Traverse(const HashTable* table, HashListTraverseFunc func, void* context);
void HashTable_Print(const HashTable* table);
void HashTable_Clear(HashTable* table);






#endif //DATASTRUCT_HASH_TABLE_H