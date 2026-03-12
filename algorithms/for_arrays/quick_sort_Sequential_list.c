//
// Created by XDS on 2026/3/12.
//

#include <stdio.h>

#include "algorithms_sort_list.h"
#include "Sequential_List.h"

void quick_sort(SeqList* array, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    SLDataType* arraydata = array->data;
    SLDataType temp = arraydata[mid];
    arraydata[mid] = arraydata[left];
    arraydata[left] = temp;//放在第一个位置方便对比
    int length = left;//恢复需要使用的
    for (int i = left + 1; i <= right; i++)
    {
        if (arraydata[i] <= arraydata[left])
        {
            length++;
            SLDataType temp1 = arraydata[length];
            arraydata[length] = arraydata[i];
            arraydata[i] = temp1;
        }
    }
    SLDataType temp2 = arraydata[length];
    arraydata[length] = arraydata[left];
    arraydata[left] = temp2;
    quick_sort(array, left, length - 1);
    quick_sort(array, length + 1, right);
}
void quick_sort_Sequential_list(SeqList* array)
{
    if (array == NULL)
    {
        printf("Array is NULL!\n");
        return;
    }
    if (array->size <= 1)return;
    quick_sort(array, 0, array->size - 1);
}