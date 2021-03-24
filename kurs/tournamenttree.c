#include "tournamenttree.h"

TourTree* Create(int count, int* array) // создаем дерево, вызов рекурсивной функции
{
    int tree_deep = Ceil(count); // глубина дерева, которое получится
    printf("tree_deep = %d\n", tree_deep);
    TourTree* root = InitNode(0); // создали корень
    int i = 0; // присвоили уровню 0
    if (count == 0) {
        return root;
    }
    InitDFS(root, tree_deep, array, &i, count); // вход в рекурсию, строим дерево и заполняем его
    return root;
}

TourTree* InitNode(int deep) // инициализирует лист (выделяет память)
{
    TourTree* node = malloc(sizeof(TourTree));
    node->left = NULL;
    node->right = NULL;
    node->key = -1;
    node->deep = deep;
    return node;
}

void InitDFS(TourTree* node, int tree_deep, int* array, int* i, int count) // рекурсивное создание узлов и их заполнение числами (ключами) из массива участников
{
    if (tree_deep != node->deep) { // пока не достигли листьев
        node->left = InitNode(node->deep + 1);
        node->right = InitNode(node->deep + 1);
        InitDFS(node->left, tree_deep, array, i, count); // рекурсивно для левого
        if (*i == count) { // если значения в массиве закончились, а листья у дерева остались (взяли в избытке)
            node->key = node->left->key;
            free(node->right);
            node->right = NULL;
            return; // вернулись обратно
        }
        InitDFS(node->right, tree_deep, array, i, count); // рекурсивно для правого
        if (node->left->key > node->right->key) {
            node->key = node->left->key;
        } else {
            node->key = node->right->key;
        }
    }
    if (*i < count) { // заполняем листок
        if (tree_deep == node->deep) {
            node->key = array[*i];
            *i = *i + 1;
        }
    }
}

void DeleteCurrentWinner(TourTree* node, TourTree* parent) // удаление текущего победителя и определение нового
{
    if (node->left != NULL && node->key == node->left->key) {
        node->key = -1;
        DeleteCurrentWinner(node->left, node);
    }

    if (node->right != NULL && node->key == node->right->key) {
        node->key = -1;
        DeleteCurrentWinner(node->right, node);
    }

    if (node->left == NULL && node->right == NULL) { // дошли до нужного листа
        node->key = -1;
        if (parent->left != NULL && parent->left->key == -1) { // удаляем его если он слева от родителя
            free(parent->left);
            parent->left = NULL;
        } else if (parent->right != NULL && parent->right->key == -1) { // удаляем его если он справа от родителя
            free(parent->right);
            parent->right = NULL;
        }
        return;
    }
    /* Ниже в зависимости от ситуации определяется новый победитель */
    if (node->right == NULL) {
        node->key = node->left->key;
        return;
    } else if (node->left == NULL) {
        node->key = node->right->key;
        return;
    }

    if (node->right->key > node->left->key) {
        node->key = node->right->key;
    } else if (node->left->key > node->right->key) {
        node->key = node->left->key;
    }
}

int Ceil(int n) // возвращает глубину дерева
{
    return ceil(log2f(n));
}

double wtime() // для проверки времени работы алгоритма
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void PrintLeafs(TourTree* node) // рекурсивно в глубину обходим дерево и печатаем значения в листьях
{
    if (node->left == NULL && node->right == NULL) {
        // printf("%d ", node->key);
        return;
    }
    if (node->left != NULL) {
        PrintLeafs(node->left);
    }

    if (node->right != NULL) {
        PrintLeafs(node->right);
    }
}