
struct avltree {
    int key;
    char* value;
    int height;
    int deleted;

    struct avltree* left;
    struct avltree* right;
};

struct info_about_avltree {
    int count_deleted;
    int count_all;
};

struct avltree*
avltree_add(struct avltree* tree, int key, char* value, struct info_about_avltree* info);
struct avltree* avltree_lookup(struct avltree* tree, int key);
struct avltree* avltree_create(int key, char* value, struct info_about_avltree* info);
int avltree_height(struct avltree* tree);
int avltree_balance(struct avltree* tree);
struct avltree* avltree_right_rotate(struct avltree* tree);
struct avltree* avltree_left_rotate(struct avltree* tree);
struct avltree* avltree_leftright_rotate(struct avltree* tree);
struct avltree* avltree_rightleft_rotate(struct avltree* tree);
// struct avltree* avltree_min(struct avltree* tree);
void avltree_max_key(struct avltree* tree, int* max);
struct avltree* avltree_max(struct avltree* tree);
void avltree_min_key(struct avltree* tree, int* min);
struct avltree* avltree_min(struct avltree* tree);
struct avltree* avltree_delete(struct avltree* tree, int key, struct info_about_avltree* info);
void avltree_free(struct avltree* tree);
void avltree_print_dfs(struct avltree* tree);
void dfs(struct avltree* tree, int* array, int* i);
struct avltree* make_new_tree(struct avltree* tree, struct avltree* new_tree, int* array, int* i, struct info_about_avltree* info);

struct info_about_avltree* info_create();