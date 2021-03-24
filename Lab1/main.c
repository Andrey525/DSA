#include "avltree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

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
    struct avltree* node;
    node = malloc(sizeof(*node));
    node = avltree_lookup(tree, key);
    struct avltree* list;
    list = malloc(sizeof(*list));

    for (int i = 1; i < 50001; i++) {
        if (i <= 1000) {
            if (i % 100 == 0) {
                printf("\n\nNUMBER OF ADD NODES = %d \t TREE HEIGHT = %d\n", i, avltree_height(tree));
                double begin = wtime();
                node = avltree_max(tree);
                double end = wtime();
                printf("NODE MAX KEY = %d\n", node->key);
                printf("n = %d; time = %.6lf\n", i, end - begin);
            }
        }
        if (i % 10000 == 0) {
            printf("\n\nNUMBER OF ADD NODES = %d \t TREE HEIGHT = %d\n", i, avltree_height(tree));
            double begin = wtime();
            node = avltree_max(tree);
            double end = wtime();
            printf("NODE MAX KEY = %d\n", node->key);
            printf("n = %d; time = %.6lf\n", i, end - begin);
        }
        value[i] = strcpy(value[i], "Нелев");
        tree = avltree_add(tree, i, value[i], info);
    }
    // avltree_print_dfs(tree);
    printf("______\n");

    for (int i = 0; i <= (info->count_all / 3); i++) {
        if (i < (info->count_all / 3) && i > (16660)) {
            printf("INFO: %d %d\n", info->count_all, info->count_deleted);
        }
        int num = (i + 1) * 2;
        tree = avltree_delete(tree, num, info);
    }

    // avltree_print_dfs(tree);
    // node = avltree_lookup(tree, );
    // printf("Node key = %d\n", node->key);
    for (int i = 0; i <= (info->count_all / 4); i++) {
        int num = rand() % 50000;
        if (avltree_lookup(tree, num) != NULL) {
            tree = avltree_delete(tree, num, info);
        }
    }
    tree = avltree_delete(tree, 50000, info);

    // avltree_print_dfs(tree);
    printf("INFO: %d %d\n", info->count_all, info->count_deleted);
    return 0;
}
