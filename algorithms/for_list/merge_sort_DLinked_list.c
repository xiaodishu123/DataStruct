//
// Created by XDS on 2026/3/11.
//
#include <stdio.h>

#include "DLinked_list.h"
static DListNode* dlist_merge(DListNode* left,DListNode* right)
{
    DListNode dummy = {0,NULL,NULL};//虚拟节点
    DListNode* p = &dummy;
    while(left!=NULL && right!=NULL)
    {
        if (left->data <= right->data)//“=”稳定排序
        {
            p->next = left;
            left->prev=p;
            left=left->next;
        }else{
            p->next = right;
            right->prev=p;
            right=right->next;
        }
        p=p->next;
    }
    p->next = left == NULL ? right : left;
    if (p->next != NULL)
    {
        p->next->prev = p;
    }


    if (dummy.next != NULL)//防止指针异常
    {
        dummy.next->prev = NULL;
    }


    if (dummy.next != NULL)
    {
        while (p->next != NULL) {
        p = p->next;
        }
        dummy.next->prev = p;  //注意注意注意尾节点存储在头节点的 prev 中！！！
    }

    return dummy.next;
}
static DListNode* dlist_split_mid(DListNode* head)
{
    DListNode* slow = head;
    DListNode* fast = head->next;
    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    DListNode* mid = slow->next;
    slow->next = NULL;
    if (mid)//防止mid为NULL
    {
        mid->prev = NULL;
    }
    return mid;//右边的开始
}
static DListNode* dlist_merge_sort_internal(DListNode* head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    DListNode* mid =dlist_split_mid(head);
    DListNode* left = dlist_merge_sort_internal(head);
    DListNode* right = dlist_merge_sort_internal(mid);

    return dlist_merge(left, right);
}
void dlist_merge_sort(DList* list)
{
    if (list == NULL)
    {
        printf("list is NULL\n");
        return;
    }
    if (list->size <= 1) {
        return;  // 无需排序,防止指针异常
    }
    DListNode* head = list->dummy.next;
    head->prev = NULL;
    list->dummy.prev->next = NULL;//取消虚拟节点
    head = dlist_merge_sort_internal(head);

    list->dummy.prev = head->prev;//prve暂时记录尾节点

    head->prev = &list->dummy;//恢复
    list->dummy.prev->next = &list->dummy;
    list->dummy.next = head;

}