/*
 * INT_BINARY_TREE.H
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of an integer binary tree.
 * 
 */
#define TRUE  1
#define FALSE 0

// Variables
struct TreeNode {
    struct TreeNode *parent;
    struct TreeNode *left_child;
    struct TreeNode *right_child;
    int level;
    int data;
};

struct TreeNode *ROOT;
int NUM_TREE_NODES;

struct TreeNode* create_new_node(int);
struct TreeNode* find_free_node(struct TreeNode*);
void initialize_binary_tree();
int insert(int);
int search_tree();
int tree_depth(struct TreeNode*);
int node_is_complete(struct TreeNode*);
int node_is_full(struct TreeNode*);

