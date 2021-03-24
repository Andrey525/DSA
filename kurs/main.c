#include "tournamenttree.h"

int main()
{
    int array[] = { 40, 38, 14, 20, 18, 220, 17, 109, 1, 32, 11, 100, 121, 19, 302, 29, 4, 2, 15, 329 };
    // int array[10000];
    // for (int i = 0; i < 10000; i++) {
    //     array[i] = i + 1;
    // }
    int count = sizeof(array) / 4;
    printf("size = %d\n", count);

    double begin = wtime();
    TourTree* root = Create(count, array);
    double end = wtime();
    printf("\nTime for adding %d elements: %.6f\n", count, end - begin);
    // printf("\n\n\nИсходный массив: ");
    begin = wtime();
    PrintLeafs(root);
    end = wtime();
    printf("\nTime for find leafs %d elements: %.6f\n", count, end - begin);
    // printf("\n(^^PrintLeafs^^)\n\n");

    // printf("root->key = %d\n", root->key);

    int sortarray[count];
    begin = wtime();

    int j = 0;
    while (root->key != -1) {
        sortarray[j] = root->key;
        DeleteCurrentWinner(root, root);
        j++;
    }
    // sortarray[0] = root->key;
    // DeleteCurrentWinner(root, root);
    end = wtime();
    printf("\nTime for sorting %d elements: %f\n", count, end - begin);
    printf("\n\n\nИсходный массив: ");

    for (int i = 0; i < count; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n\nОтсортированыый массив: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", sortarray[i]);
    }
    printf("\n\n\nsortarray[0] = %d\n", sortarray[0]);
    printf("\n\n\nsortarray[1] = %d\n", sortarray[1]);
    for (int i = 0; i < count; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", sortarray[i]);
    }
    printf("\n\n");

    return 0;
}
