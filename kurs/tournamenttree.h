#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct TournamentTree {
    int key; // ключ
    struct TournamentTree* right; // указатель на правый дочерний узел
    struct TournamentTree* left; // указатель на левый дочерний узел
    int deep; // глубина узла
} TourTree;

TourTree* Create(int count, int* array); // создает дерево
TourTree* InitNode(int deep); // создает узел с ключом -1
void InitDFS(TourTree* node, int tree_deep, int* array, int* i, int count); // шагает в глубину и заполняет листья значениями из массива
int Ceil(int n); // возвращает округленную глубину дерева
void DeleteCurrentWinner(TourTree* node, TourTree* parent); // определяет нового победителя, удаляя прежнего из дерева
double wtime(); // для замера времени алгоритма
void PrintLeafs(TourTree* root); // печатает листья дерева