#include "fibheap.h"

FibHeap* CreateHeap()
{
    FibHeap* heap = malloc(sizeof(*heap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}

NodeOfHeap* CreateNode(int key, char* value)
{
    NodeOfHeap* node = malloc(sizeof(*node));
    node->key = key;
    node->value = value;
    node->degree = 0;
    node->mark = false;
    node->parent = NULL;
    node->child = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void FibHeapInsert(FibHeap* heap, int key, char* value)
{
    NodeOfHeap* node = CreateNode(key, value);
    if (heap->min != NULL) { // не пустая куча
        if (heap->min == heap->min->left) { // один корневой узел
            heap->min->left = node;
            heap->min->right = node;
            node->left = heap->min;
            node->right = heap->min;
            if (node->key < heap->min->key) {
                heap->min = node;
            }
        } else { // несколько корневых узлов
            NodeOfHeap* lnode;
            lnode = heap->min->left;
            heap->min->left = node;
            node->right = heap->min;
            node->left = lnode;
            lnode->right = node;
            if (node->key < heap->min->key) {
                heap->min = node;
            }
        }
    } else if (heap->min == NULL) { // пустая куча
        node->left = node;
        node->right = node;
        heap->min = node;
    }
    heap->n++;
}

NodeOfHeap* FibHeapMin(FibHeap* heap)
{
    return heap->min;
}

FibHeap* FibHeapUnion(FibHeap* heap1, FibHeap* heap2)
{
    FibHeap* heap = malloc(sizeof(*heap));
    heap->min = heap1->min;
    FibHeapLinkLists(heap1->min, heap2->min);
    if ((heap1->min == NULL) || (heap2->min != NULL && heap2->min->key < heap->min->key)) {
        heap->min = heap2->min;
    }
    heap->n = heap1->n + heap2->n;
    free(heap1);
    free(heap2);
    return heap;
}

void FibHeapLinkLists(NodeOfHeap* min1, NodeOfHeap* min2)
{
    if (min1 == NULL || min2 == NULL) {
        return;
    }

    NodeOfHeap *left1, *left2;

    left1 = min1->left;
    left2 = min2->left;
    min1->left = left2;
    min2->left = left1;
    left1->right = min2;
    left2->right = min1;
}

void FibHeapDeleteMin(FibHeap* heap)
{
    NodeOfHeap* min = heap->min;

    if (min == NULL) {
        return;
    }

    NodeOfHeap* child = min->child;

    for (int i = 0; i < min->degree; i++) {
        FibHeapInsert(heap, child->key, child->value);
        child->parent = NULL;
        child = child->right;
    }

    /*** Удаляем корень с минимальным ключом, восстанавливаем связи в списке корней ***/
    NodeOfHeap *right, *left;
    right = min->right;
    left = min->left;
    right->left = left;
    left->right = right;
    min->right = NULL;
    min->left = NULL;
    min->child = NULL;
    free(min);

    /*** Определяем новый корень с минимальным ключом ***/

    min = right;

    int t = 1;
    NodeOfHeap *now = min, *minimum = min; // minimum - это указатель на новый минимальный корень, now - для проверки в цикле, min - меняется
    while (t) {
        if (min->key < minimum->key) {
            minimum = min;
        }
        min = min->right;
        if (min == now) {
            t = 0;
        }
    }
    heap->n--;
    heap->min = minimum;
    FibHeapConsolidate(heap);
}

int Floor(int n)
{
    return floor(log2f(n));
}

void FibHeapConsolidate(FibHeap* heap)
{

    int t = 1, Rcount = 0; // Rcount - первоначальное кол-во корневых узлов
    NodeOfHeap *now = heap->min, *min = heap->min;
    while (t) {
        min = min->right;
        if (min == now) {
            t = 0;
        }
        Rcount++;
    }

    int Acount = Floor(heap->n); // максимальная степень корня
    NodeOfHeap* A[Acount + 1];
    for (int i = 0; i < Acount + 1; i++) {
        A[i] = NULL;
    }

    NodeOfHeap *x, *y, *w[Rcount];
    /*** Заполняем первоначальный список корней ***/
    int j = 0;
    now = heap->min;
    min = heap->min;
    t = 1;
    while (t) {
        w[j] = min;
        j++;
        min = min->right;
        if (min == now) {
            t = 0;
        }
    }
    /*** Работа со вспомогательным массивом указателей ***/
    int d;
    for (int i = 0; i < Rcount; i++) {
        x = w[i];
        d = x->degree;
        while (A[d] != NULL) {
            y = A[d];
            if (x->key > y->key) { // обменяли x и y
                NodeOfHeap* temp;
                temp = x;
                x = y;
                y = temp;
            }
            FibHeapLink(heap, y, x); //делаем корень Y дочерним к Y
            A[d] = NULL;
            d = d + 1;
        }
        A[d] = x;
    }
}

void FibHeapLink(FibHeap* heap, NodeOfHeap* y, NodeOfHeap* x)
{
    /*** Убираем Y из списка корней ***/
    NodeOfHeap *left, *right;
    left = y->left;
    right = y->right;
    y->left = NULL;
    y->right = NULL;
    left->right = right;
    right->left = left;
    ////////////////////

    /*** Делаем Y дочерним к X ***/
    if (x->child == NULL) { // степень узла 0
        x->child = y;
        y->left = y;
        y->right = y;
    } else if (x->child->left == x->child) { // степень узла 1
        x->child->left = y;
        x->child->right = y;
        y->left = x->child;
        y->right = x->child;
    } else { // степень узла > 1
        NodeOfHeap* node;
        node = x->child->left;
        x->child->left = y;
        y->right = x->child;
        y->left = node;
        node->right = y;
    }
    ////////////////////////////////////////

    x->degree++;
    y->parent = x;
    y->mark = false;
}

void FibHeapDecreaseKey(FibHeap* heap, NodeOfHeap* x, int newkey)
{
    if (newkey > x->key) { // новый ключ больше значения текущего ключа
        return;
    }
    x->key = newkey;
    NodeOfHeap* y;
    y = x->parent;

    /***
	* Если свойства min-heap нарушены: ключ родителя больше
	* то
	* вырезаем X и переносим его в список корней	
	***/

    if (y != NULL && x->key < y->key) {
        FibHeapCut(heap, x, y);
        FibHeapCascadingCut(heap, y);
    }

    if (x->key < heap->min->key) {
        heap->min = x;
    }
}

void FibHeapCut(FibHeap* heap, NodeOfHeap* x, NodeOfHeap* y)
{
    /*** Удаляем X из списка дочерних узлов Y ***/
    if (x != x->left) { // несколько дочерних узлов
        NodeOfHeap *left, *right;
        left = x->left;
        right = x->right;
        x->left = NULL;
        x->right = NULL;
        left->right = right;
        right->left = left;
        x->parent = NULL;
        y->child = left;
    } else if (x == x->left) { // X - единственный дочерний узел
        x->left = NULL;
        x->right = NULL;
        x->parent = NULL;
        y->child = NULL;
    }

    y->degree--;

    /*** Добавляем X в список корней кучи ***/

    if (heap->min == heap->min->left) { // Y - единственный корневой узел
        heap->min->left = x;
        heap->min->right = x;
        x->left = heap->min;
        x->right = heap->min;
    } else { // несколько корневых узлов
        NodeOfHeap* lnode;
        lnode = heap->min->left;
        heap->min->left = x;
        x->right = heap->min;
        x->left = lnode;
        lnode->right = x;
    }

    x->mark = false;
}

void FibHeapCascadingCut(FibHeap* heap, NodeOfHeap* y)
{
	NodeOfHeap* z = y->parent;
	if (z == NULL) {
		return;
	}
	if (y->mark == false) {
		y->mark = true;
	} else {
		FibHeapCut(heap, y, z);
		FibHeapCascadingCut(heap, z);
	}
}

void FibHeapDeleteKey(FibHeap* heap, NodeOfHeap* x)
{
	FibHeapDecreaseKey(heap, x, HEAP_INFINITY);
	FibHeapDeleteMin(heap);
}