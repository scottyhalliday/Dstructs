/*
 * STRING_LINKED_LIST.H
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of an string queue using a linked list
 * 
 */

// Variables
struct Node {
    struct Node *next;
    char *data;
};

struct Node *HEAD;
struct Node *TAIL;
int QUEUE_CNT;

// Function prototypes
int  get_queue_length();
struct Node* get_node_at_index(int);
void initialize_queue();
int  insert_node(int, char*);
int  enqueue(char*);
void print_queue();
int  remove_node(int);
int  dequeue();
int  delete_queue();

