/*
 * INT_STACK_LLIST.C
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

#include <stdio.h>
#include <stdlib.h>
#include "include/int_stack_llist.h"

// ----------------------------------------------------------------------------
// Clear the contents of the stack
void
clear_stack()
{

    struct Node *n;
    do 
    {
        n = pop();
    } 
    while (n != NULL);

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
        
        if (cntr == index)
            return(n);

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
struct Node*
pop()
{

    struct Node *n;

    // If stack is empty then return NULL
    if (LLIST_CNT == 0)
    {
        printf("** WARNING ** :: POP :: Stack is empty, nothing to pop\n");
        return(NULL);
    }

    // Get the node at the top of the stack
    n = get_node_at_index(LLIST_CNT-1);

    // Remove the node from the stack
    remove_node(LLIST_CNT-1);

    return(n);
    
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
            printf("%5d  <-- TOP OF STACK\n", n->data);
        else
            printf("%5d -> ", n->data);

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
push(int value)
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
    n->data = value;
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
    free(n);

    // Decrement our counter
    LLIST_CNT--;

    return(1);

}

// ----------------------------------------------------------------------------
int
main(int argc, char **argv)
{

    struct Node *n;

    printf("\n\nStack Data Structure -- C Implementation -- Linked List Stack\n\n");
    initialize_stack(0);
    push(100);
    push(101);
    push(102);
    push(103);
    push(104);
    push(105);
    push(106);
    push(107);
    push(108);
    push(109);
    push(110);
    push(111);
    push(112);
    push(113);
    push(114);
    push(115);
    push(116);
    push(117);
    push(118);
    push(119);
    push(120);

    printf("Stack:\n");
    print_stack();

    printf("Pop item from the stack\n");
    n = pop();
    printf("Item popped '%d'\n", n->data);
    printf("Stack:\n");
    print_stack();

    printf("\nPop item from the stack\n");
    n = pop();
    printf("Item popped '%d'\n", n->data);
    printf("Stack:\n");
    print_stack();

    printf("\nPop item from the stack\n");
    n = pop();
    printf("Item popped '%d'\n", n->data);
    printf("Stack:\n");
    print_stack();

    printf("\nPop item from the stack\n");
    n = pop();
    printf("Item popped '%d'\n", n->data);
    printf("Stack:\n");
    print_stack();

    printf("\nPop item from the stack\n");
    n = pop();
    printf("Item popped '%d'\n", n->data);
    printf("Stack:\n");
    print_stack();

    printf("\nPop item from the stack\n");
    n = pop();
    printf("Item popped '%d'\n", n->data);
    printf("Stack:\n");
    print_stack();

    printf("\nPop item from the stack\n");
    n = pop();
    printf("Item popped '%d'\n", n->data);
    printf("Stack:\n");
    print_stack();

    printf("\nPop item from the stack\n");
    n = pop();
    printf("Item popped '%d'\n", n->data);
    printf("Stack:\n");
    print_stack();

    printf("\nPush item to the stack\n");
    push(1000);
    printf("Stack:\n");
    print_stack();

    printf("\nPush item to the stack\n");
    push(2000);
    printf("Stack:\n");
    print_stack();

    printf("\nPop item from the stack\n");
    n = pop();
    printf("Item popped '%d'\n", n->data);
    printf("Stack:\n");
    print_stack();

    // Check if the stack is full.  It shouldn't be since we didn't specifiy a max length
    printf("Is the stack full? ");
    if (is_full() == 1) 
        printf("YES\n");
    else
        printf("NO\n");

    do 
    {
        n = pop();
        if (n != NULL)
        {
            printf("Item popped is '%d'\n", n->data);
        }
    } while (n != NULL);

    // Should be empty we just popped everything
    printf("Is the stack empty? ");
    if (is_empty() == 1) 
        printf("YES\n");
    else
        printf("NO\n");

    printf("Stack:\n");
    print_stack();

    // Make a fixed size stack
    printf("\n\nMAKE A FIXED SIZE STACK\n\n");
    initialize_stack(10);

    push(1);
    push(2);
    push(3);
    push(4);
    push(5);
    push(6);
    push(7);
    push(8);
    push(9);
    push(10);

    printf("Stack:\n");
    print_stack();

    printf("Push to the full stack...Should fail\n");
    push(11);

    n = pop();
    printf("Item popped '%d'\n", n->data);
    printf("Stack:\n");
    print_stack();

    printf("Push to the stack...Should work since we just made space\n");
    push(11);
    printf("Stack:\n");
    print_stack();

    printf("Clear the stack, all done.\n");
    clear_stack();

}










