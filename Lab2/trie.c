#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

struct trie* trie_create() // создание пустого узла
{
    struct trie* node;
    node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->ch = '\0';
    node->value = -1;
    node->sibling = NULL;
    node->child = NULL;
    return node;
}

int trie_lookup(struct trie* root, char* key) // поиск значения, по введенным ключам
{
    struct trie *node, *list;
    for (list = root; *key != '\0'; key++) {
        for (node = list; node != NULL; node = node->sibling) {
            if (node->ch == *key)
                break;
        }
        if (node != NULL) {
            list = node->child;
        } else {
            printf("Данное слово отсутствует в словаре!\n");
            return -1;
        }
    }
    if (node->value == -1) {
        printf("Данная последовательность букв имеется в словаре, но не составляет слово!\n");
    }
    return node->value; // этот узел будет являться листом, возвращаем его значение
}

struct trie* trie_insert(struct trie* root, char* key, int value) // вставка слова
{
    struct trie *node, *parent, *list;
    parent = NULL;
    list = root;
    for (; *key != '\0'; key++) {
        // ищем sibling node
        for (node = list; node != NULL; node = node->sibling) {
            if (node->ch == *key)
                break;
        }
        if (node == NULL) { // узел не найден, создаем новый узел
            node = trie_create();
            node->ch = *key;
            node->sibling = list;
            if (parent != NULL)
                parent->child = node;
            else
                root = node;
            list = NULL;
        } else { // узел найден, переходим на следующий уровень
            list = node->child;
        }
        parent = node;
    }
    node->value = value; // присваиваем значение
    return root;
}

struct trie* trie_delete(struct trie* root, char* key)
{
    int found;
    int value = trie_lookup(root, key);
    return trie_delete_dfs(root, NULL, key, &found, value);
}

struct trie* trie_delete_dfs(struct trie* root, struct trie* parent, char* key, int* found, int value)
{
    struct trie *node, *prev = NULL;
    if (*key == '\0' && root == NULL) {
        *found = 1;
    } else if (*key == '\0' && root != NULL) {
        *found = 2;
    } else {
        *found = 0;
    }
    if (root == NULL || *key == '\0')
        return root;
    for (node = root; node != NULL; node = node->sibling) {
        if (node->ch == *key) {
            break;
        }
        prev = node;
    }
    if (node == NULL) {
        return root;
    }
    trie_delete_dfs(node->child, node, key + 1, found, value);
    if (*found == 2 && node->child != NULL) { // удаление значения, в случае, когда у данного ключа есть child
        node->value = -1;
        *found = 0;
    }
    if (*found == 1 && node->child == NULL && (node->value == -1 || node->value == value)) {
        /* Удаляем узел */
        if (prev != NULL) {
            prev->sibling = node->sibling;
        } else {
            if (parent != NULL)
                parent->child = node->sibling;
            else
                root = node->sibling;
        }
        node->value = -1;
        free(node);
    }
    return root;
}

void trie_print(struct trie* root, int level)
{
	struct trie *node;
	int i;
	for (node = root; node != NULL; node = node->sibling) {
		for (i = 0; i < level; i++) {
			printf("  ");
		}
		if (node->value != -1) {
			printf("%c (%d)\n\n\n", node->ch, node->value);
		}
		else {
			printf("%c \n", node->ch);
		}
		if (node->child != NULL) {
			trie_print(node->child, level + 1);
		}
	}
}