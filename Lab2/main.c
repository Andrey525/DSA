#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct trie* root;
    root = trie_create();
    root = trie_insert(root, "Tir", 270);
    root = trie_insert(root, "Tigr", 180);
    root = trie_insert(root, "Tapir", 300);
    root = trie_insert(root, "Barsyk", 15);
    root = trie_insert(root, "Bars", 55);
    root = trie_insert(root, "Barnayl", 440);
    root = trie_insert(root, "Tyndra", 120);
    root = trie_insert(root, "Tehas", 32);
    root = trie_insert(root, "Ten", 3120);
    root = trie_insert(root, "Barhat", 3);
    root = trie_insert(root, "Byrya", 187);
    root = trie_insert(root, "Byryat", 188);
    int value;

    // root = trie_delete(root, "Byrya");
    value = trie_lookup(root, "Tir");
    printf("Value Tir = %d\n", value);
    value = trie_lookup(root, "Tigr");
    printf("Value Tigr = %d\n", value);
    value = trie_lookup(root, "Tapir");
    printf("Value Tapir = %d\n", value);
    value = trie_lookup(root, "Barsyk");
    printf("Value Barsyk = %d\n", value);
    value = trie_lookup(root, "Bars");
    printf("Value Bars = %d\n", value);
    value = trie_lookup(root, "Barnayl");
    printf("Value Barnayl = %d\n", value);
    value = trie_lookup(root, "Tyndra");
    printf("Value Tyndra = %d\n", value);
    value = trie_lookup(root, "Tehas");
    printf("Value Tehas = %d\n", value);
    value = trie_lookup(root, "Ten");
    printf("Value Ten = %d\n", value);
    value = trie_lookup(root, "Barhat");
    printf("Value Barhat = %d\n", value);
    value = trie_lookup(root, "Byrya");
    printf("Value Byrya = %d\n", value);
    value = trie_lookup(root, "Byryat");
    printf("Value Byryat = %d\n", value);

    printf("\n\n");
    trie_print(root, 0);
    return 0;
}
