/*
 * FLOAT_STACK_ARRAY.H
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of an double floating point type stack using the array list data structure.  
 * The stack is a fixed length array list.  If the stack is full and another
 * item is added an error will occur.  This implementation will not allocate
 * more memory for stack overflow, it will simply disregard the push.
 * 
 */

// Variables
struct array_stack {
    int     size;          // Max size of the array
    int     index;         // Current index in the array
    double *stack;         // Array to hold the stack
};

// Function prototypes
int clear_stack(struct array_stack*);
int delete_stack(struct array_stack*);
struct array_stack* initialize_stack(int);
int is_empty(struct array_stack*);
int is_full(struct array_stack*);
void print_stack(struct array_stack*);
void print_stack_status(struct array_stack*);
int push(double, struct array_stack*);
int pop(struct array_stack*, double*);
