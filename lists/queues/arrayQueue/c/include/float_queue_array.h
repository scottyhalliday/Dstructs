/*
 * FLOAT_QUEUE_ARRAY.H
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of an double floating point type queue using an array list data structure.  
 * The queue is a fixed length array list.  If the queue is full and another
 * item is added an error will occur.  This implementation will not allocate
 * more memory for queue overflow, it will simply disregard the push.
 * 
 */

// Variables
struct array_queue {
    int     size;          // Max size of the array
    int     index;         // Current index in the array
    double *queue;         // Array to hold the queue
};

// Function prototypes
int clear_queue(struct array_queue*);
int delete_queue(struct array_queue*);
struct array_queue* initialize_queue(int);
int is_empty(struct array_queue*);
int is_full(struct array_queue*);
void print_queue(struct array_queue*);
void print_queue_status(struct array_queue*);
int enqueue(double, struct array_queue*);
int dequeue(struct array_queue*, double*);
int get_max_size(struct array_queue*);
int remove_at_index(int, struct array_queue*);
