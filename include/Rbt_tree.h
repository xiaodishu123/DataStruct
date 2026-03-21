//
// Created by XDS on 2026/3/18.
//

#ifndef DATASTRUCT_RBT_TREE_H
#define DATASTRUCT_RBT_TREE_H

//Rbt实现
enum Color {RED, BLACK};
//树节点
typedef struct rbt_node {
    int data;
    struct rbt_node* left;// 左子树指针
    struct rbt_node* right;// 右子树指针
    struct rbt_node* parent;//父节点
    enum Color color;
} rbt_node;

// 二叉搜索树结构体
typedef struct rbt_tree {
    rbt_node* root;// 树根节点
    rbt_node* nil;//  哨兵节点
    int node_count;// 节点计数
} rbt_tree;

rbt_tree* rbt_init();//不需要参数，直接创造使用
int rbt_destroy(rbt_tree* tree);//删除后不可以再使用tree，记得防止重复使用
void rbt_insert(rbt_tree* tree,int value);
int rbt_delete(rbt_tree* tree, int value);
rbt_node* rbt_search(rbt_tree* tree, int value);

rbt_node* rbt_find_min(rbt_node* root, rbt_node* nil);
void rbt_traversal(rbt_tree* tree);//中序遍历




#endif //DATASTRUCT_RBT_TREE_H