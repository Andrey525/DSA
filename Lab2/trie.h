
struct trie {
    int value;
    char ch;
    struct trie* sibling; // brother node
    struct trie* child; // child node
};

struct trie* trie_create();
int trie_lookup(struct trie* root, char* key);
struct trie* trie_insert(struct trie* root, char* key, int value);
struct trie* trie_delete(struct trie* root, char* key);
struct trie* trie_delete_dfs(struct trie* root, struct trie* parent, char* key, int* found, int value);
void trie_print(struct trie* root, int level);