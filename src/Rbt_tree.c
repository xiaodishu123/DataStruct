//
// Created by XDS on 2026/3/18.
//
#include "Rbt_tree.h"

#include <stdio.h>
#include <stdlib.h>


rbt_tree* rbt_init()
{
    rbt_tree* tree = (rbt_tree*)malloc(sizeof(rbt_tree));
    tree->node_count = 0;
    tree->nil = (rbt_node*)malloc(sizeof(rbt_node));
    tree->nil->left = NULL;
    tree->nil->right = NULL;
    tree->nil->parent = NULL;
    tree->nil->data = 0;
    tree->nil->color = BLACK;
    tree->root = tree->nil;
    return tree;
}//不需要参数，直接创造使用
rbt_node* rbt_create_node(int value, rbt_node* nil)
{
    rbt_node* node = (rbt_node*)malloc(sizeof(rbt_node));
    if (node == NULL)
    {
        printf("Memory Error");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->left = nil;
    node->right = nil;
    node->parent = nil;
    node->color = RED;//初始红色
    return node;
}
void rbt_rotate_right(rbt_node* node, rbt_tree* tree)
{
    if (node == tree->nil || node->left == tree->nil)return;
    rbt_node* new_root = node->left;
    rbt_node* temp = node->left->right;
    node->left->right = node;
    node->left = temp;
    if (temp != tree->nil)temp->parent = node;
    if (node->parent == tree->nil)
    {
        tree->root = new_root;
    }else if (node->parent->left == node)
    {
        node->parent->left = new_root;
    }else
    {
        node->parent->right = new_root;
    }
    new_root->parent = node->parent;
    node->parent = new_root;
}
void rbt_rotate_left(rbt_node* node, rbt_tree* tree)
{
    if (node == tree->nil || node->right == tree->nil)return;
    rbt_node* new_root = node->right;
    rbt_node* temp = node->right->left;
    node->right->left = node;
    node->right = temp;
    if (temp != tree->nil)temp->parent = node;
    if (node->parent == tree->nil)
    {
        tree->root = new_root;
    }else if (node->parent->left == node)
    {
        node->parent->left = new_root;
    }else
    {
        node->parent->right = new_root;
    }
    new_root->parent = node->parent;
    node->parent = new_root;
}
rbt_node* rbt_find_min(rbt_node* root, rbt_node* nil)
{
    if (root == nil)
    {
        return nil;
    }
    if (root == NULL)
    {
        return NULL;
    }
    while (root->left != nil)
    {
        root = root->left;
    }
    return root;//可能返回nil
}
static void rbt_insert_fixup(rbt_tree* tree, rbt_node* z)
{
    if (tree == NULL || z == NULL)
    {
        printf("NULL Error");
        return;
    }
    while (z->parent != tree->nil && z->parent->color == RED)//红红
    {
        if (z->parent == z->parent->parent->left)//L
        {
            rbt_node* u = z->parent->parent->right;
            if (u->color == RED)//叔节点为红
            {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                u->color = BLACK;
                z = z->parent->parent;
            }else
            {
                if (z == z->parent->right)//LR
                {
                    rbt_rotate_left(z->parent, tree);
                    z = z->left;//调整z
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbt_rotate_right(z->parent->parent, tree);
            }
        }else//R
        {
            rbt_node* u = z->parent->parent->left;
            if (u->color == RED)//叔节点为红
            {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                u->color = BLACK;
                z = z->parent->parent;
            }else
            {
                if (z == z->parent->left)//RL
                {
                    rbt_rotate_right(z->parent, tree);
                    z = z->right;//调整z
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbt_rotate_left(z->parent->parent, tree);
            }
        }
    }
    tree->root->color = BLACK;//根节点
}








rbt_node* rbt_search_recursive(rbt_node* root, int value, rbt_node* nil)
{
    if (root == NULL || root == nil)
    {
        return NULL;//nil返回NULL
    }
    if (root->data == value)
    {
        return root;//找到返回节点
    }
    if (value < root->data)
    {
        return rbt_search_recursive(root->left,value,nil);
    }
    return rbt_search_recursive(root->right,value,nil);
}
rbt_node* rbt_search(rbt_tree* tree, int value)//封装,找不到返回NULL
{
    if (tree == NULL)
    {
        printf("Tree is null");
        return NULL;
    }
    return rbt_search_recursive(tree->root,value,tree->nil);
}





void rbt_free_tree_recursive(rbt_node* root,rbt_node* nil)//后序遍历释放
{
    if (root != NULL && root != nil)
    {
        rbt_free_tree_recursive(root->left,nil);
        rbt_free_tree_recursive(root->right,nil);
        free(root);
    }
}
int rbt_destroy(rbt_tree* tree)//记得防止重复使用tree
{
    if (tree == NULL)return 0;
    rbt_free_tree_recursive(tree->root,tree->nil);
    tree->root = NULL;//防止重复使用
    free(tree->nil);//删除哨兵节点
    free(tree);
    return 1;
}




void rbt_insert(rbt_tree* tree,int value)//使用迭代插入
{
    if (tree == NULL)return;
    rbt_node* z = rbt_create_node(value, tree->nil);//新节点
    rbt_node* y = tree->nil;//父节点
    rbt_node* x = tree->root;//当前节点
    while (x != tree->nil)//寻找插入位置
    {
        y = x;
        if (value < x->data)
        {
            x = x->left;
        }else if (value > x->data)
        {
            x = x->right;
        }else
        {
            free(z);//相等不插入
            return;
        }
    }
    z->parent = y;
    if (y == tree->nil)
    {
        tree->root = z;
    }else if (value < y->data)
    {
        y->left = z;
    }else
    {
        y->right = z;
    }
    rbt_insert_fixup(tree, z);
    tree->node_count++;
}


static void rbt_dblack(rbt_tree* tree, rbt_node* brother)
{
    rbt_node* x;
    if (brother->parent->left == brother)//调用前已经保证parent不为nil
    {
        x = brother->parent->right;
    }else
    {
        x = brother->parent->left;
    }
    if (x->color == RED)//双黑为红色，第一次双黑必定为黑
    {
        x->color = BLACK;
        return;
    }
    if (brother->color == RED)//兄弟是红色
    {
        rbt_node* f = brother->parent;
        brother->color = BLACK;
        f->color = RED;
        if (brother == f->right)
        {
            rbt_rotate_left(f,tree);
            rbt_dblack(tree,f->right);
        }else
        {
            rbt_rotate_right(f,tree);
            rbt_dblack(tree,f->left);
        }
        return;
    }
    if (brother->left->color == RED || brother->right->color == RED)
    {
        rbt_node* f = brother->parent;
        if (brother == f->left)//L
        {
            if (brother->left->color == RED)//LL
            {
                brother->left->color = brother->color;
                brother->color = f->color;
                f->color = BLACK;
                rbt_rotate_right(f, tree);
                x->color = BLACK;
                return;
            }
            brother->right->color = f->color;//LR
            f->color = BLACK;
            rbt_rotate_left(brother,tree);
            rbt_rotate_right(f,tree);
            x->color = BLACK;
            return;
        }
        if (brother->right->color == RED)//RR
        {
            brother->right->color = brother->color;
            brother->color = f->color;
            f->color = BLACK;
            rbt_rotate_left(f, tree);
            x->color = BLACK;
            return;
        }
        brother->left->color = f->color;//RL
        f->color = BLACK;
        rbt_rotate_right(brother,tree);
        rbt_rotate_left(f,tree);
        x->color = BLACK;
        return;
    }
    brother->color = RED;
    if (brother->parent->parent == tree->nil)//双黑上移后为根节点
    {
        brother->parent->color = BLACK;
        return;
    }
    rbt_node* dblack_brother;
    if (brother->parent == brother->parent->parent->left)
    {
        dblack_brother = brother->parent->parent->right;
    }else
    {
        dblack_brother = brother->parent->parent->left;
    }
    rbt_dblack(tree, dblack_brother);//双黑上移
}

int rbt_delete_(rbt_tree* tree,rbt_node* root, int value)//返回删除节点后的tree的根节点
{
    if (tree == NULL)return 0;
    rbt_node* nil = tree->nil;
    rbt_node* y = root->parent;//父节点
    rbt_node* x = root;//当前节点
    while (x != tree->nil && x->data != value)//寻找删除位置
    {
        y = x;
        if (value < x->data)
        {
            x = x->left;
        }else
        {
            x = x->right;
        }
    }
    if (x == nil)
    {
        return 0;
    }
    if (x->left == nil && x->right == nil)
    {
        if (x == tree->root)//根节点直接删除
        {
            tree->root = nil;
            free(x);
            return 1;
        }
        rbt_node* b;
        if (x == x->parent->left)
        {
            b = x->parent->right;
        }else
        {
            b = x->parent->left;
        }
        if (x == y->left)
        {
            y->left = nil;
        }else
        {
            y->right = nil;
        }
        if (x->color == BLACK)//删除变双黑，第一次双黑必定为黑
        {
            rbt_dblack(tree, b);
        }
        free(x);//红色直接删除
        return 1;
    }
    if (x->right == nil)
    {
        x->left->parent = y;
        if (x == y->right)
        {
            y->right = x->left;
        }else
        {
            y->left = x->left;
        }
        x->left->color = BLACK;
        if (x == tree->root)//链接根节点
        {
            tree->root = x->left;
        }
        free(x);
        return 1;
    }
    if (x->left == nil)
    {
        x->right->parent = y;
        if (x == y->right)
        {
            y->right = x->right;
        }else
        {
            y->left = x->right;
        }
        x->right->color = BLACK;
        if (x == tree->root)//链接根节点
        {
            tree->root = x->right;
        }
        free(x);
        return 1;
    }
    rbt_node* delete_node = rbt_find_min(x->right,nil);
    x->data = delete_node->data;
    rbt_delete_(tree,x->right,delete_node->data);
    return 1;
}
int rbt_delete(rbt_tree* tree, int value)//封装
{
    if (tree == NULL || tree->root == NULL)return 0;
    int deleted = rbt_delete_(tree,tree->root,value);
    if (deleted)tree->node_count--;
    return deleted;
}

//中序遍历
void rbt_inorder_traversal(rbt_node* root,rbt_node* nil)
{
    if (root != NULL && root != nil)
    {
        rbt_inorder_traversal(root->left,nil);
        printf("%d\n", root->data);
        rbt_inorder_traversal(root->right,nil);
    }
}
void rbt_traversal(rbt_tree* tree)
{
    if (tree == NULL)
    {
        printf("Tree is null");
        return;
    }
    rbt_inorder_traversal(tree->root,tree->nil);
}