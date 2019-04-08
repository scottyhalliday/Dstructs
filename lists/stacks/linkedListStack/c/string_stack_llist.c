/*
 * STRING_STACK_LLIST.C
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/string_stack_llist.h"

// ----------------------------------------------------------------------------
// Clear the contents of the stack
void
clear_stack()
{

    int n;
    do 
    {
        n = pop();
    } 
    while (n != 1);

}

// ----------------------------------------------------------------------------
//
// Return the node at the specified index.  If index is invalid then a NULL
// node will be returned.
//
struct Node*
get_node_at_index(int index)
{
    int cntr;
    struct Node *n;

    // Check if the index is out of range
    if (index > LLIST_CNT) 
    {
        printf("** ERROR ** :: GET_NODE_AT_INDEX :: Index %5d is out of range.  "
               "Current list size is %5d.\n", index, LLIST_CNT);
        return(NULL);
    }

    if (index < 0) 
    {
        printf("** ERROR ** :: GET_NODE_AT_INDEX :: Index %5d cannot be less than zero\n", index);
        return(NULL);
    }

    // Find the node in the linked list
    cntr = 0;
    n    = HEAD;
    while(cntr < LLIST_CNT) {
        
        if (cntr == index) {
            return(n);
        }

        n = n->next;
        cntr++;
    }

    return(NULL);

}

// ----------------------------------------------------------------------------
// Initialize the stack.  If the @size is greater than zero then the stack 
// will enforce a maximum stack size limit.  If size is zero then the stack
// has no limit and can continue to grow.  If the stack size is limited then
// once the stack is full, no additional items can be pushed and are ignored
void
initialize_stack(int size)
{
    LLIST_CNT      = 0;
    HEAD           = NULL;
    TAIL           = NULL;
    MAX_STACK_SIZE = size;
}

// ----------------------------------------------------------------------------
int
is_empty()
{
    if (LLIST_CNT == 0)
        return(1);
    return(0);
}

// ----------------------------------------------------------------------------
// Recall that if the user specified a maximum size then the stack will not
// grow past that size.  If not specified then the stack has no size.
int
is_full()
{
    if (MAX_STACK_SIZE > 0 && LLIST_CNT == MAX_STACK_SIZE)
        return(1);
    return(0);
}

// ----------------------------------------------------------------------------
// Nothing more than a convenience function to remove the item at the end of
// the linked list.  
int
pop()
{

    struct Node *n;

    strcpy(popped_value,"");

    // If stack is empty then return NULL
    if (LLIST_CNT == 0)
    {
        printf("** WARNING ** :: POP :: Stack is empty, nothing to pop\n");
        return(1);
    }

    // Get the node at the top of the stack
    n = get_node_at_index(LLIST_CNT-1);
    strcpy(popped_value,n->data);
    
    // Remove the node from the stack
    remove_node(LLIST_CNT-1);

    return(0);
    
}

// ----------------------------------------------------------------------------
void
print_stack()
{
    int i;
    struct Node *n;

    i = 0;
    n = HEAD;

    // If the HEAD is NULL then the stack is empty and cannot be printed
    if (HEAD == NULL) 
        return;

    while (1) {

        i++;
        
        if (n->next == NULL) 
            printf("%s  <-- TOP OF STACK\n", n->data);
        else
            printf("%s -> ", n->data);

        // If the next node is NULL then we are done!
        if (n->next == NULL) {
            return;
        }

        // Move to the next node
        n = n->next;

        // Move to a new line after 10 prints
        if (i % 10 == 0) 
            printf("\n");

        // Last fail safe
        if (i >= LLIST_CNT)
        {   
            printf("WARNING:  Got to end of the stack without a NULL.  Not Good.\n");
            return;
        }

    }

}

// ----------------------------------------------------------------------------
// Push the item to the stack.  If the stack has a maximum allowable length
// check to see if the stack is full.  If full then don't push item.
int
push(char *value)
{
    struct Node *n;

    // Before allocating memory check to see if the stack is full
    if (MAX_STACK_SIZE > 0)
    {
        if (LLIST_CNT == MAX_STACK_SIZE)
        {
            printf("** ERROR ** :: PUSH :: Stack is currently full.  Cannot push additional items\n");
            return(1);
        }
    }

    // Allocate memory for the new item and set its content
    n = (struct Node*) malloc(sizeof(struct Node));
    n->data = (char *) calloc(strlen(value), sizeof(char));
    strcpy(n->data, value);    
    n->next = NULL;

    // Is this the first item in the stack?
    if (LLIST_CNT == 0) 
    {
        HEAD = n;
    }
    else
    {
        TAIL->next = n;
    }

    // Re-assign the TAIL
    TAIL = n;

    LLIST_CNT++;

    return(0);
}

// ----------------------------------------------------------------------------
// Remove a node from the list at specified @index
int 
remove_node(int index)
{
    struct Node *n;
    struct Node *nprev;
    struct Node *nnext;

    // Check if the index is out of range
    if (index >= LLIST_CNT) 
    {
        printf("** ERROR ** :: REMOVE_NODE :: Index %5d is out of range.  "
               "Current list size is %5d.  NO NODES REMOVED.\n", index, LLIST_CNT);
        return(0);
    }

    if (index < 0) 
    {
        printf("** ERROR ** :: REMOVE_NODE :: Index %5d cannot be less than zero.  "
               "NO NODES REMOVED\n", index);
        return(0);
    }

    n = get_node_at_index(index);

    if (index == 0)
    {
        if (LLIST_CNT > 1) {
            nnext = get_node_at_index(index+1);
            HEAD = nnext;
        } 
        // This is the last node in the list, so cleanup
        else 
        {
            HEAD = NULL;
        }
    }
    else if (index == LLIST_CNT-1)
    {
        nprev = get_node_at_index(index-1);
        nprev->next = NULL;
        TAIL = nprev;
    }
    else
    {
        nprev = get_node_at_index(index-1);
        nnext = get_node_at_index(index+1);

        nprev->next = nnext;
    }

    // Release the node's memory
    free(n->data);
    free(n);

    // Decrement our counter
    LLIST_CNT--;

    return(1);

}

// ----------------------------------------------------------------------------
int
main(int argc, char **argv)
{

    printf("\n\nStack Data Structure -- C Implementation -- Linked List Stack\n\n");
    initialize_stack(0);
    push("Stacks");
    push("are");
    push("neat");
    push("Super");
    push("Simple");
    push("Data");
    push("Structure");
    push("!!");

    printf("Stack:\n");
    print_stack();

    printf("Let's Pop!\n");
    pop();
    printf("Item popped is '%s'\n", popped_value);
    printf("Stack:\n");
    print_stack();

    printf("\nLet's clear the stack\n");
    clear_stack();
    printf("Stack:\n");
    print_stack();

    printf("\n\nLet's make a fixed size stack\n\n");
    initialize_stack(10);
    push("Hi");
    push("Hi");
    push("Hi");
    push("Hi");
    push("Hi");
    push("Hi");
    push("Hi");
    push("Hi");
    push("Hi");
    push("Hi");
    printf("Stack:\n");
    print_stack();

    printf("\nTry to push to full stack...should fail\n");
    push("Bye");
    printf("Stack:\n");
    print_stack();

    printf("\nPop off top stack item and try to re-push...should work\n");
    pop();
    push("Bye");
    printf("Stack:\n");
    print_stack();

    pop(); printf("Item popped is '%s'\n", popped_value);
    pop(); printf("Item popped is '%s'\n", popped_value);
    pop(); printf("Item popped is '%s'\n", popped_value);
    pop(); printf("Item popped is '%s'\n", popped_value);
    pop(); printf("Item popped is '%s'\n", popped_value);
    pop(); printf("Item popped is '%s'\n", popped_value);
    pop(); printf("Item popped is '%s'\n", popped_value);
    pop(); printf("Item popped is '%s'\n", popped_value);
    pop(); printf("Item popped is '%s'\n", popped_value);
    pop(); printf("Item popped is '%s'\n", popped_value);
    printf("Stack:\n");
    print_stack();

    pop(); printf("Item popped is '%s'\n", popped_value);

}










