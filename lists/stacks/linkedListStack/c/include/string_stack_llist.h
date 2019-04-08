/*
 * STRING_STACK_LLIST.H
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of a string type stack using the linked list 
 * data structure.  Since this is implemented with a linked list there is no 
 * size restriction on the stack.  Of course this functionallity can be 
 * over-ridden by making the stack a strict size.  
 */

// Variables
struct Node {
    struct Node *next;
    char   *data;
};

// Don't feel like doing more complex memory management so when popping
// values just use a fixed size string array to pop items off stack
char popped_value[255];

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
int  pop();
void print_stack();
int  push(char*);
int  remove_node(int);
