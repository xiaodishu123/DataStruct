//
// Created by XDS on 2026/3/14.
//
#include "Bst_tree.h"

#include <stdio.h>
#include <stdlib.h>


bst_tree* bst_init()
{
    bst_tree* tree = (bst_tree*)malloc(sizeof(bst_tree));
    if (tree == NULL)
    {
        printf("Memory Error");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    tree->node_count = 0;
    return tree;
}
bst_node* bst_create_node(int value)
{
    bst_node* node = (bst_node*)malloc(sizeof(bst_node));
    if (node == NULL)
    {
        printf("Memory Error");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}
bst_node* bst_insert_recursive(bst_node* root, int value)//如果后面为NULL返回创建节点
{
    if (root == NULL)
    {
        return bst_create_node(value);//创建
    }
    if (value < root->data)
    {
        root->left = bst_insert_recursive(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = bst_insert_recursive(root->right, value);
    }
    return root;//相等不插入
}
void bst_insert(bst_tree* tree, int value)//封装
{
    if (tree == NULL)
    {
        printf("Tree is null");
        return;
    }
    tree->root = bst_insert_recursive(tree->root, value);
    tree->node_count++;
}


bst_node* bst_search_recursive(bst_node* root, int value)
{
    if (root == NULL || root->data == value)
    {
        return root;//找到返回节点
    }
    if (value < root->data)
    {
        return bst_search_recursive(root->left, value);
    }
    return bst_search_recursive(root->right, value);
}
bst_node* bst_search(bst_tree* tree, int value)//封装,找不到返回NULL
{
    if (tree == NULL)
    {
        printf("Tree is null");
        return NULL;
    }
    return bst_search_recursive(tree->root, value);
}

bst_node* bst_find_min(bst_node* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}
bst_node* bst_delete_recursive(bst_node* root, int value)//返回删除节点后的tree的根节点
{
    if (root == NULL)return root;
    if (value < root->data)
    {
        root->left = bst_delete_recursive(root->left, value);
    }else if (value > root->data)
    {
        root->right = bst_delete_recursive(root->right, value);
    }else
    {
        if (root->left == NULL) {//要删除的节点是叶节点或只有一个子节点
            bst_node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            bst_node* temp = root->left;
            free(root);
            return temp;
        }
        //使用右边最小节点替代
        bst_node* current = bst_find_min(root->right);
        root->data = current->data;
        root->right = bst_delete_recursive(root->right, current->data);
    }
    return root;
}
int bst_delete(bst_tree* tree, int value)//封装
{
    if (bst_search(tree, value) == NULL) {//先找
        return 0;
    }
    tree->root = bst_delete_recursive(tree->root, value);
    tree->node_count--;
    return 1;
}
//中序遍历
void bst_inorder_traversal(bst_node* root)
{
    if (root != NULL)
    {
        bst_inorder_traversal(root->left);
        printf("%d\n", root->data);
        bst_inorder_traversal(root->right);
    }
}
void bst_traversal(bst_tree* tree)
{
    if (tree == NULL)
    {
        printf("Tree is null");
        return;
    }
    bst_inorder_traversal(tree->root);
}


void bst_free_tree_recursive(bst_node* root)//后序遍历释放
{
    if (root != NULL)
    {
        bst_free_tree_recursive(root->left);
        bst_free_tree_recursive(root->right);
        root->left = NULL;
        root->right = NULL;
        free(root);
    }
}
int bst_destroy(bst_tree* tree)//记得防止重复使用tree
{
    if (tree == NULL)return 0;
    bst_free_tree_recursive(tree->root);
    tree->root = NULL;//防止重复使用
    free(tree);
    return 1;
}


int bst_is_empty(bst_tree* tree) {
    return tree->root == NULL;
}
int bst_node_count_(bst_node* root)
{
    if (root == NULL)return 0;
    return 1 + bst_node_count_(root->right) + bst_node_count_(root->left);
}
int bst_node_count(bst_tree* tree)//封装
{
    if (tree == NULL)return 0;
    return 1 + bst_node_count_(tree->root);
}


int bst_height_(bst_node* root)
{
    if (root == NULL)return 0;
    int left_height = bst_height_(root->left);
    int right_height = bst_height_(root->right);
    return (left_height >= right_height ? left_height : right_height) + 1;
}
int bst_height(bst_tree* tree)//封装
{
    if (tree == NULL)return 0;
    return bst_height_(tree->root);
}