/*
 * INT_STACK_LLIST.H
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of an integer type stack using the linked list data structure.  
 * Since this is implemented with a linked list there is no size restriction
 * on the stack.  Of course this functionallity can be over-ridden by making the
 * stack a strict size.  
 */

// Variables
struct Node {
    struct Node *next;
    int data;
};

struct Node *HEAD;
struct Node *TAIL;
int LLIST_CNT;
int MAX_STACK_SIZE;

// Function prototypes
void clear_stack();
struct Node* get_node_at_index(int);
void initialize_stack();
int  is_empty();
int  is_full();
struct Node* pop();
void print_stack();
int  push(int);
int  remove_node(int);
