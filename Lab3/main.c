#include "fibheap.h"

int main()
{
    FibHeap* heap1;
    heap1 = CreateHeap();
    FibHeapInsert(heap1, 13, "Осьминог");
    FibHeapInsert(heap1, 6, "Акула");
    FibHeapInsert(heap1, 12, "Дельфин");
    FibHeapInsert(heap1, 8, "Рак");
    printf("%d %s n = %d\n", heap1->min->key, heap1->min->value, heap1->n);
    printf("%d %s n = %d\n", heap1->min->left->key, heap1->min->left->value, heap1->n);
    printf("%d %s n = %d\n", heap1->min->left->left->key, heap1->min->left->left->value, heap1->n);

    FibHeap* heap2;
    heap2 = CreateHeap();
    FibHeapInsert(heap2, 1, "Скат");
    FibHeapInsert(heap2, 7, "Конек");
    FibHeapInsert(heap2, 11, "Планктон");
    FibHeapInsert(heap2, 2, "Кит");
    FibHeapInsert(heap2, 122, "Карась");
    printf("%d %s n = %d\n", heap2->min->key, heap2->min->value, heap2->n);
    printf("%d %s n = %d\n", heap2->min->left->key, heap2->min->left->value, heap2->n);
    printf("%d %s n = %d\n", heap2->min->left->left->key, heap2->min->left->left->value, heap2->n);

    FibHeap* heap;
    heap = FibHeapUnion(heap1, heap2);

    int t = 1;
    NodeOfHeap *now = heap->min, *min = heap->min;
    printf("\nINLINE\n");
    while (t) {
        printf("min key = %d\n", min->key);
        min = min->right;
        if (min == now) {
            t = 0;
        }
    }
    // printf("\n%d %s n = %d\n", heap->min->key, heap->min->value, heap->n);
    // printf("%d %s n = %d\n", heap->min->right->key, heap->min->right->value, heap->n);
    // printf("%d %s n = %d\n", heap->min->right->right->key, heap->min->right->right->value, heap->n);
    // printf("%d %s n = %d\n", heap->min->left->key, heap->min->left->value, heap->n);

    FibHeapDeleteMin(heap);

    // FibHeapConsolidate(heap);
    t = 1;
    now = heap->min;
    min = heap->min;
    printf("\n\n");
    while (t) {
        printf("min key = %d\n", min->key);
        min = min->right;
        if (min == now) {
            t = 0;
        }
    }

    FibHeapDecreaseKey(heap, heap->min->child->right, 1);

    t = 1;
    now = heap->min;
    min = heap->min;
    printf("\n\n");
    while (t) {
        printf("min key = %d\n", min->key);
        min = min->right;
        if (min == now) {
            t = 0;
        }
    }

    printf("MIN KEY = %d\n", heap->min->key);
    printf("heap->min->child->key = %d\n", heap->min->child->key);

    FibHeapDeleteKey(heap, heap->min);

    printf("MIN KEY = %d\n", heap->min->key);
    printf("heap->min->child->key = %d\n", heap->min->child->key);

    printf("MIN Right KEY = %d\n", heap->min->right->key);
}