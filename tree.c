#include "hathstd.h"

/**
 * Red-Black tree
 */

#define RB_RED 0
#define RB_BLACK 1

static void tree_insert_fixup(Tree*, TreeNode*);
static void tree_left_rotate(Tree*, TreeNode*);
static void tree_right_rotate(Tree*, TreeNode*);

Tree *tree_create(int (*cmp)(void*, void*)) {
    Tree *tree = emalloc(sizeof(Tree));
    tree->cmp = cmp;
    tree->root = NULL;
    return tree;
}

int tree_contains(Tree *tree, void *elem) {
    TreeNode *node = tree->root;
    while (node != NULL) {
        int r = tree->cmp(elem, node->data);
        if (r == 0) return 1;
        else if (r < 0) node = node->left;
        else node = node->right;
    }
    return 0;
}

static void tree_foreach_rec(TreeNode*, void (*function)(void*));

void tree_foreach(Tree *tree, void (*function)(void*)) {
    tree_foreach_rec(tree->root, function);
}

static void tree_foreach_rec(TreeNode *node, void (*function)(void*)) {
    if (node == NULL)
        return;
    tree_foreach_rec(node->left, function);
    function(node->data);
    tree_foreach_rec(node->right, function);
}

int tree_insert(Tree *tree, void *elem) {
    TreeNode *y = NULL;
    TreeNode *x = tree->root;
    TreeNode *z = emalloc(sizeof(TreeNode));
    z->data = elem;

    while (x != NULL) {
        y = x;
        if (tree->cmp(z->data, x->data) < 0)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NULL)
        tree->root = z;
    else if (tree->cmp(z->data, y->data) < 0)
        y->left = z;
    else
        y->right = z;
    z->left = NULL;
    z->right = NULL;
    z->color = RB_RED;
    tree_insert_fixup(tree, z);
}

static void tree_insert_fixup(Tree *tree, TreeNode *z) {
    while (z->parent != NULL && z->parent->parent != NULL &&
            z->parent->color == RB_RED) {
        if (z->parent == z->parent->parent->left) {
            TreeNode *y = z->parent->parent->right;
            if (y != NULL && y->color == RB_RED) {
                z->parent->color = RB_BLACK;
                y->color = RB_BLACK;
                z->parent->parent->color = RB_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    tree_left_rotate(tree, z);
                }
                z->parent->color = RB_BLACK;
                z->parent->parent->color = RB_RED;
                tree_right_rotate(tree, z->parent->parent);
            }
        } else {
            TreeNode *y = z->parent->parent->left;
            if (y != NULL && y->color == RB_RED) {
                z->parent->color = RB_BLACK;
                y->color = RB_BLACK;
                z->parent->parent->color = RB_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    tree_right_rotate(tree, z);
                }
                z->parent->color = RB_BLACK;
                z->parent->parent->color = RB_RED;
                tree_left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = RB_BLACK;
}

static void tree_left_rotate(Tree *tree, TreeNode *x) {
    TreeNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) 
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

static void tree_right_rotate(Tree *tree, TreeNode *x) {
    TreeNode *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right = x;
    x->parent = y;
}

