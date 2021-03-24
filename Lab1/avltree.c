#include "avltree.h"
#include <stdio.h>
#include <stdlib.h>

struct info_about_avltree* info_create()
{
    struct info_about_avltree* info;
    info = malloc(sizeof(*info));
    if (info != NULL) {
        info->count_deleted = 0;
        info->count_all = 0;
    }
    return info;
}
void avltree_free(struct avltree* tree) // удаление АВЛ-дерева (высвобождение памяти)
{
    if (tree == NULL)
        return;

    avltree_free(tree->left);
    avltree_free(tree->right);
    free(tree);
}

struct avltree* avltree_lookup(struct avltree* tree, int key) // поиск узла в АВЛ-дереве по ключу
{
    while (tree != NULL) {
        if (key == tree->key) {
            return tree;
        } else if (key < tree->key) {
            tree = tree->left;
        } else {
            tree = tree->right;
        }
    }
    // if (tree == NULL) {
    //     printf("\n\nАварийное завершение программы\nПроизведена попытка обратиться к несуществующему узлу\n\n");
    //     exit(-2);
    // }
    return tree;
}

struct avltree* avltree_create(int key, char* value, struct info_about_avltree* info)
{
    struct avltree* node;
    node = malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->deleted = 0;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
        info->count_all++;
    }
    return node;
}

int avltree_height(struct avltree* tree)
{
    return (tree != NULL) ? tree->height : -1;
}

int avltree_balance(struct avltree* tree)
{
    return avltree_height(tree->left) - avltree_height(tree->right);
}

int imax2(int first, int second)
{
    return (first >= second) ? first : second;
}

struct avltree* avltree_add(struct avltree* tree, int key, char* value, struct info_about_avltree* info)
{
    if (tree == NULL) {
        return avltree_create(key, value, info);
    }
    if (key < tree->key) {
        tree->left = avltree_add(tree->left, key, value, info);
        if (avltree_height(tree->left) - avltree_height(tree->right) == 2) {
            if (key < tree->left->key) {
                tree = avltree_right_rotate(tree);
            } else {
                tree = avltree_leftright_rotate(tree);
            }
        }
    } else if (key > tree->key) {
        tree->right = avltree_add(tree->right, key, value, info);
        if (avltree_height(tree->right) - avltree_height(tree->left) == 2) {
            if (key > tree->right->key) {
                tree = avltree_left_rotate(tree);
            } else {
                tree = avltree_rightleft_rotate(tree);
            }
        }
    } else if (key == tree->key) {
        if (tree->deleted == 1) {
            tree->deleted = 0;
            info->count_deleted--;
        }
        tree->value = value;
    }
    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    return tree;
}

struct avltree* avltree_right_rotate(struct avltree* tree)
{
    struct avltree* left;

    left = tree->left;
    tree->left = left->right;
    left->right = tree;

    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    left->height = imax2(avltree_height(left->left), tree->height) + 1;

    return left;
}

struct avltree* avltree_left_rotate(struct avltree* tree)
{
    struct avltree* right;

    right = tree->right;
    tree->right = right->left;
    right->left = tree;

    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    right->height = imax2(avltree_height(right->right), tree->height) + 1;

    return right;
}

struct avltree* avltree_leftright_rotate(struct avltree* tree)
{
    tree->left = avltree_left_rotate(tree->left);
    return avltree_right_rotate(tree);
}

struct avltree* avltree_rightleft_rotate(struct avltree* tree)
{
    tree->right = avltree_right_rotate(tree->right);
    return avltree_left_rotate(tree);
}

// struct avltree* avltree_min(struct avltree* tree)
// {
//     if (tree == NULL)
//         return NULL;
//     struct avltree* node;
//     node = malloc(sizeof(*node));
//     while (tree->left != NULL) {
//         if (tree->left->deleted == 0) {
//             tree = tree->left;
//             node = tree;
//         } else if ((tree->left->deleted == 1) && ((tree->left->left != NULL) || (tree->left->right) != NULL)) {

//             if (tree->left->left == NULL && tree->left->right != NULL) {
//                 tree = tree->left->right;
//                 if (tree->deleted == 0) {
//                     node = tree;
//                 }
//             }
//             tree = tree->left;
//             // if ((tree->right != NULL) && (tree->right->deleted == 0)) {
//             // }
//         }
//     }
//     return tree;
// }

void avltree_min_key(struct avltree* tree, int* min)
{
    if (tree->key < *min && tree->deleted == 0) {
        *min = tree->key;
    }
    if (tree->left != NULL) {
        avltree_min_key(tree->left, min);
    }
    if (tree->right != NULL) {
        avltree_min_key(tree->right, min);
    }
}

struct avltree* avltree_min(struct avltree* tree)
{
    if (tree == NULL) {
        return NULL;
    }
    int* min = malloc(sizeof(int));
    *min = tree->key;
    avltree_min_key(tree, min);
    struct avltree* node = malloc(sizeof(*node));
    node = avltree_lookup(tree, *min);
    printf("\nMIN KEY = %d\n\n", node->key);
    return node;
}

void avltree_max_key(struct avltree* tree, int* max)
{
    if (tree->key > *max && tree->deleted == 0) {
        *max = tree->key;
    }
    if (tree->left != NULL) {
        avltree_max_key(tree->left, max);
    }
    if (tree->right != NULL) {
        avltree_max_key(tree->right, max);
    }
}

struct avltree* avltree_max(struct avltree* tree)
{
    if (tree == NULL) {
        return NULL;
    }
    int* max = malloc(sizeof(int));
    *max = tree->key;
    avltree_max_key(tree, max);
    struct avltree* node = malloc(sizeof(*node));
    node = avltree_lookup(tree, *max);
    printf("\nMAX KEY = %d\n\n", node->key);
    return node;
}

void avltree_print_dfs(struct avltree* tree)
{
    if (tree == NULL) {
        return;
    }
    printf("Ключ = %d, Значение = %s, Высота = %d, Удален = %d\n", tree->key, tree->value, tree->height, tree->deleted);
    if (tree->left != NULL) {
        printf("%d -> %d \t влево по дереву\n", tree->key, tree->left->key);
        avltree_print_dfs(tree->left);
        // printf("%d -> %d \t влево по дереву\n", tree->key, tree->left->key);
    }

    if (tree->right != NULL) {
        printf("%d -> %d \t вправо по дереву\n", tree->key, tree->right->key);
        avltree_print_dfs(tree->right);
        // printf("%d -> %d \t вправо по дереву\n", tree->key, tree->right->key);
    }
}

void dfs(struct avltree* tree, int* array, int* i)
{
    if (tree->deleted == 0) {
        array[*i] = tree->key;
        *i = *i + 1;
    }
    if (tree->left != NULL) {
        dfs(tree->left, array, i);
    }
    if (tree->right != NULL) {
        dfs(tree->right, array, i);
    }
}

struct avltree* make_new_tree(struct avltree* tree, struct avltree* new_tree, int* array, int* i, struct info_about_avltree* info)
{
    struct avltree* node;
    node = malloc(sizeof(*node));

    for (int j = 0; j < *i; j++) {
        node = avltree_lookup(tree, array[j]);
        new_tree = avltree_add(new_tree, node->key, node->value, info);
    }
    return new_tree;
}

struct avltree* avltree_delete(struct avltree* tree, int key, struct info_about_avltree* info)
{
    struct avltree* node;
    node = malloc(sizeof(*node));
    node = avltree_lookup(tree, key);
    if (node->deleted == 0) {
        node->deleted = 1;
        info->count_deleted++;
    }
    if (info->count_deleted == (info->count_all / 3)) {
        info->count_deleted = 0;
        int* array = malloc(sizeof(int) * info->count_all);
        int* i = malloc(sizeof(int));
        *i = 0;
        dfs(tree, array, i);
        printf("\n");
        struct avltree* new_tree;
        new_tree = NULL;
        info->count_all = 0;
        new_tree = make_new_tree(tree, new_tree, array, i, info);
        avltree_free(tree);
        return new_tree;
    }
    return tree;
}