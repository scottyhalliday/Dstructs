/*
 * STRING_QUEUE_LINKED.C
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of an string queue using linked list.  
 * 
 * ****R E F R E S H E R   B L O C K ******************************************
 * For a refresher recall how the '.' and '->' notations are used within C.  
 * '->' is used as a shorthand for a pointer to a variable type struct.  
 * For example, suppose I have the following:
 *
 *     struct this_struct {
 *        int attr;   
 *     }
 *     
 *     struct this_struct *my_struct;
 *     
 * Must initialize the memory where the 'my_struct' is pointing
 *     
 *     my_struct = (struct this_struct *) malloc(sizeof(struct this_struct)); *     
 *     
 * To access the member of the struct and considering my_struct is a pointer,    
 * I would do the following.
 *     
 *     (*my_struct).attr = 100;
 * 
 * Or you can use the convenient '->'    
 *     
 *     my_struct->attr = 100;
 *     
 * Now suppose I don't make a pointer declaration but instead make an actual
 * variable declaration.  Instead of doing this,
 *
 *     struct this_struct *my_struct;
 *
 * I do this,
 *
 *     struct this_struct my_struct;
 *
 * Since this is no longer a pointer declaration we don't need to worry about
 * the address that the pointer points to we can go back to the '.' notation
 * like was seen above since we don't need to include the pointer reference.
 * So I can set the value 'attr' as follows.
 *
 *     my_struct.attr = 100;
 * 
 * I jump between programming languages and I usually forget these minor but
 * important details.  So this will help refresh my memory.
 * 
 * Since we are building a linked list we will want to work with pointers so
 * we can 'point' to other nodes!! 
 * ****************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/string_queue_linked.h"

// ----------------------------------------------------------------------------
int
delete_queue()
{
    if (QUEUE_CNT == 0)
        return(1);
    dequeue();
    return(delete_queue());
}

// ----------------------------------------------------------------------------
int
get_queue_length()
{
    return(QUEUE_CNT);
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
    if (index > QUEUE_CNT) 
    {
        printf("** ERROR ** :: GET_NODE_AT_INDEX :: Index %5d is out of range.  "
               "Current list size is %5d.\n", index, QUEUE_CNT);
        return(NULL);
    }

    if (index < 0) 
    {
        printf("** ERROR ** :: GET_NODE_AT_INDEX :: Index %5d cannot be less than zero\n", index);
        return(NULL);
    }

    cntr = 0;
    n    = HEAD;
    while(cntr < QUEUE_CNT) {
        
        if (cntr == index)
            return(n);

        n = n->next;
        cntr++;
    }

    return(NULL);

}

// ----------------------------------------------------------------------------
void
initialize_queue()
{
    QUEUE_CNT = 0;
    HEAD      = NULL;
    TAIL      = NULL;
}

// ----------------------------------------------------------------------------
//
// Insert a node with specified 'value' at a specified 'index' in the list.
// If the index is out of range, then nothing is inserted.
// 
int
insert_node(int index, char *value) 
{

    struct Node *n;
    struct Node *nprev;

    // Check if the index is out of range
    if (index > QUEUE_CNT) 
    {
        printf("** ERROR ** :: INSERT_NODE :: Index %5d is out of range.  "
               "Current list size is %5d.  NOT INSERTING NODE\n", index, QUEUE_CNT);
        return(0);
    }

    if (index < 0) 
    {
        printf("** ERROR ** :: INSERT_NODE :: Index %5d cannot be less than zero.  "
               "NOT INSERTING NODE\n", index);
        return(0);
    }

    // Allocate memory for the node
    n = (struct Node *) malloc(sizeof(struct Node));

    // Allocate memory for the string itself
    n->data = (char *) calloc(strlen(value), sizeof(char));

    n->next = NULL;
    strcpy(n->data, value);

    // If inserting at the beginning then simply reassign the HEAD node
    if (index == 0) {

        // If the list is empty then assign HEAD
        if (QUEUE_CNT == 0) 
        {
            HEAD = n;
            TAIL = n;
        } 
        // Otherwise, move the head and have the new node point to previous head node
        else 
        {
            n->next = HEAD;
            HEAD = n;
        }
    } 
    // If inserting at the end then simply reassign the TAIL node
    else if (index == QUEUE_CNT) 
    {
        TAIL->next = n;
        TAIL = n;
    }
    // Otherwise insert the node and reassign pointers
    else 
    {
        nprev = get_node_at_index(index-1);
        n->next = nprev->next;
        nprev->next = n;
    }

    // Increment the list node counter
    QUEUE_CNT++;

    return(1);
}

// ----------------------------------------------------------------------------
int
enqueue(char *value)
{
    return(insert_node(0, value));
}

// ----------------------------------------------------------------------------
void
print_queue()
{
    int i;
    struct Node *n;

    i = 0;
    n = HEAD;

    // If the HEAD is NULL then the list is empty and cannot be printed
    if (HEAD == NULL) 
        return;

    while (1) {
        /*
        if (n->next == NULL) 
            printf("Node Data=%d, NEXT IS  NULL\n", n->data);
        else 
            printf("Node Data=%d, NEXT NOT NULL\n", n->data);
        */
        i++;

        if (n->next == NULL) 
            printf("%s\n", n->data);
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
        if (i >= QUEUE_CNT)
        {   
            printf("WARNING:  Got to end of the list without a NULL.  Not Good.\n");
            return;
        }

    }
}

// ----------------------------------------------------------------------------
//
// Remove a node from the list at specified 'index'
//
int remove_node(int index)
{
    struct Node *n;
    struct Node *nprev;
    struct Node *nnext;

    // Check if the index is out of range
    if (index >= QUEUE_CNT) 
    {
        printf("** ERROR ** :: REMOVE_NODE :: Index %5d is out of range.  "
               "Current list size is %5d.  NO NODES REMOVED.\n", index, QUEUE_CNT);
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
        if (QUEUE_CNT > 1) {
            nnext = get_node_at_index(index+1);
            HEAD = nnext;
        } 
        // This is the last node in the list, so cleanup
        else 
        {
            HEAD = NULL;
        }
    }
    else if (index == QUEUE_CNT)
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
    QUEUE_CNT--;

    return(1);

}

// ----------------------------------------------------------------------------
//
// Remove a node from the end of the list
//
int dequeue()
{
    return(remove_node(QUEUE_CNT-1));
}
// ----------------------------------------------------------------------------
int 
main(int argc, char **argv)
{

    initialize_queue();
    
    printf("Create Initial Queue\n");
    enqueue("hello world");
    enqueue("this is a");
    enqueue("linked");
    enqueue("list");
    enqueue("of strings");
    enqueue(".");
    print_queue();
    printf("List length is %d\n", get_queue_length());

    printf("\nEnqueue\n");
    enqueue("I added this");
    print_queue();
    printf("List length is %d\n", get_queue_length());

    printf("\nDequeue\n");
    dequeue();
    print_queue();
    printf("List length is %d\n", get_queue_length());

    printf("\nDelete the queue\n");
    delete_queue();
    printf("List length is %d\n", get_queue_length());


}