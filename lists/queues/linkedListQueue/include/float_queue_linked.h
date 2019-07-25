/*
 * INT_LINKED_QUEUE.H
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of an integer type queue using the linked list data structure.  
 * 
 */

// Variables
struct Node {
    struct Node *next;
    double data;
};

struct Node *HEAD;
struct Node *TAIL;
int QUEUE_CNT;

// Function prototypes
int delete_queue();
int get_queue_length();
struct Node* get_node_at_index(int);
void initialize_queue();
int insert_node(int, double); 
int enqueue(double);
void print_queue();
double remove_node(int);
double dequeue();
