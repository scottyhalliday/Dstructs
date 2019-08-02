/*
 * STRING_BINARY_TREE.H
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of an string binary tree.
 * 
 */
#define TRUE  1
#define FALSE 0

// Variables
struct TreeNode {
    struct TreeNode *parent;
    struct TreeNode *left_child;
    struct TreeNode *right_child;
    int    is_null;
    int    level;
    char   *data;
};

struct TreeNode *ROOT;          // The root node of the tree
struct TreeNode *NULL_NODE;     // A general usage Null node 
int NUM_TREE_NODES;

void             cleanup_binary_tree();
struct TreeNode* create_new_node(char*);
struct TreeNode* create_null_node(char*, struct TreeNode*);
int              delete_node(char*);
int              delete_tree();
struct TreeNode* find_open_leaf(struct TreeNode*);
struct TreeNode* fetch_node(struct TreeNode*, char*);
int              get_number_of_nodes();
void             initialize_binary_tree();
int              insert_node(char*);
int              node_is_full(struct TreeNode*);
int              node_level(struct TreeNode*);
void             print_tree();
void             rearrange_nodes(struct TreeNode*, struct TreeNode*);
int              value_exists(struct TreeNode*, char*);
int              tree_depth(struct TreeNode*);

