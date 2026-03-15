//
// Created by XDS on 2026/3/14.
//

#ifndef DATASTRUCT_BST_TREE_H
#define DATASTRUCT_BST_TREE_H


// 二叉搜索树节点
typedef struct bst_node {
    int data;
    struct bst_node* left;// 左子树指针
    struct bst_node* right;// 右子树指针
} bst_node;

// 二叉搜索树结构体
typedef struct bst_tree {
    bst_node* root;// 树根节点
    int node_count;// 节点计数
} bst_tree;

bst_tree* bst_init();//不需要参数，直接创造使用
int bst_destroy(bst_tree* tree);//删除后不可以再使用tree，记得防止重复使用
void bst_insert(bst_tree* tree, int value);
bst_node* bst_search(bst_tree* tree, int value);
int bst_delete(bst_tree* tree, int value);
void bst_traversal(bst_tree* tree);//中序遍历

int bst_is_empty(bst_tree* tree);
int bst_node_count(bst_tree* tree);
int bst_height(bst_tree* tree);

#endif //DATASTRUCT_BST_TREE_H