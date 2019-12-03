/*
 * FLOAT_BINARY_SEARCH_TREE.H
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of a floating point/double binary search tree.
 * 
 */
#define TRUE  1
#define FALSE 0

// Variables
struct TreeNode {
    struct TreeNode *parent;
    struct TreeNode *left_child;
    struct TreeNode *right_child;
    int is_null;
    char *data;
};

struct TreeNode *ROOT;          // The root node of the tree
struct TreeNode *NULL_NODE;     // A general usage Null node 
int NUM_TREE_NODES;

void             cleanup_binary_tree();
struct TreeNode* create_new_node(char*);
struct TreeNode* create_null_node(char*, struct TreeNode*);
struct TreeNode* delete_node(struct TreeNode*, char*);
int              destroy_tree();
struct TreeNode* find_max_node(struct TreeNode*);
struct TreeNode* find_min_node(struct TreeNode*);
struct TreeNode* find_node(struct TreeNode*, char*);
struct TreeNode* find_open_spot(struct TreeNode*, char*);
void             initialize_binary_tree();
int              insert_node(char*);
int              node_level(struct TreeNode*);
void             print_tree();
int              tree_depth(struct TreeNode*);
int              value_exists(struct TreeNode*, char*);

