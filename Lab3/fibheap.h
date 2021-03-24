#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef FIBHEAP_H
#define FIBHEAP_H
#define HEAP_INFINITY -100000
typedef struct node {

    int key; // приоритет узла (ключ, вес)
    char* value; // данные
    struct node* parent; // указатель на родительский узел
    struct node* child; // указатель на один из дочерних узлов
    struct node* left; // указатель на левый сестринский узел
    struct node* right; // указатель на правый сестринский узел
    int degree; // количество дочерних узлов
    bool mark; // индикатор, были ли потери узлом его дочерних узлов

} NodeOfHeap;

typedef struct fibheap {

    NodeOfHeap* min; // указатель на узел с минимальным ключом (минимальный корень)
    int n; // кол-во узлов в куче

} FibHeap;

FibHeap* CreateHeap(); // создаем кучу 0(1)*
NodeOfHeap* CreateNode(int key, char* value); // создаем узел 0(1)*
NodeOfHeap* FibHeapMin(FibHeap* heap); // возвращаем указатель на минимальный узел Θ(1)*

void FibHeapInsert(FibHeap* heap, int key, char* value); // добавляем узел в кучу Θ(1)*
FibHeap* FibHeapUnion(FibHeap* heap1, FibHeap* heap2); // слияние куч Θ(1)* = 0(1)
void FibHeapLinkLists(NodeOfHeap* min1, NodeOfHeap* min2); // слияние пары списков корней
void FibHeapDeleteMin(FibHeap* heap); // удаляем минимальный узел 0(logn)*

void FibHeapConsolidate(FibHeap* heap); // уплотнение списка корней
void FibHeapLink(FibHeap* heap, NodeOfHeap* y, NodeOfHeap* x); // установка узла дочерним к корню
void FibHeapDecreaseKey(FibHeap* heap, NodeOfHeap* x, int newkey); // понижение значения ключа Θ(1)*

void FibHeapCut(FibHeap* heap, NodeOfHeap* x, NodeOfHeap* y); // вырезает связь между x и его родительским узлом y, делая x корнем
void FibHeapCascadingCut(FibHeap* heap, NodeOfHeap* y); // реализует каскадное вырезание над y

void FibHeapDeleteKey(FibHeap* heap, NodeOfHeap* x); // удаляем узел 0(logn)*

int Floor(int n); // округляет log2(n) в меньшую сторону. 
#endif