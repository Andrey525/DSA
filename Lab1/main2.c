#include "avltree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    int key = 0;
    char* value[50001];
    for (int i = 0; i < 50001; i++) {
        value[i] = malloc(sizeof(char) * 24);
    }
    value[0] = strcpy(value[0], "Лев");
    struct info_about_avltree* info;
    info = info_create();
    struct avltree* tree;
    tree = avltree_create(key, value[0], info);
    // struct avltree* node;
    // node = malloc(sizeof(*node));
    // node = avltree_lookup(tree, key);
    // printf("Node key = %d\n", node->key);

    for (int i = 1; i < 6; i++) {

        value[i] = strcpy(value[i], "Нелев");
        tree = avltree_add(tree, i, value[i], info);
    }
    printf("\nDFS for initial avltree:\n\n");
    avltree_print_dfs(tree);
    // struct avltree* node;
    avltree_max(tree);
    avltree_min(tree);
    printf("INFO: %d %d\n", info->count_all, info->count_deleted);

    printf("______\n");

    tree = avltree_delete(tree, 5, info);
    printf("\nDFS when one node was deleted in avltree:\n\n");
    avltree_print_dfs(tree);
    avltree_max(tree);
    avltree_min(tree);
    printf("INFO: %d %d\n", info->count_all, info->count_deleted);
    tree = avltree_delete(tree, 0, info);

    printf("\nDFS when was deleted 1/3 nodes in avltree:\n\n");
    avltree_print_dfs(tree);
    avltree_max(tree);
    avltree_min(tree);
    printf("INFO: %d %d\n", info->count_all, info->count_deleted);

    tree = avltree_add(tree, 4, "Кит", info);
    tree = avltree_delete(tree, 4, info);
    printf("\nDFS when same node was added and deleted:\nIn my case it was already added node (key = 4)\n\n");
    avltree_print_dfs(tree);
    avltree_max(tree);
    avltree_min(tree);
    printf("INFO: %d %d\n", info->count_all, info->count_deleted);
    tree = avltree_add(tree, 4, "Осьминог", info);
    printf("\nDFS when node was added in avltree:\n\n");
    avltree_print_dfs(tree);
    avltree_max(tree);
    avltree_min(tree);
    printf("INFO: %d %d\n", info->count_all, info->count_deleted);
    return 0;
}
