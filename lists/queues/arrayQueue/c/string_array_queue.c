/*
 * STRING_QUEUE_ARRAY.C
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of an string type queue using the array list data structure.  
 * The queue is a fixed length array list.  If the queue is full and another
 * item is added an error will occur.  This implementation will not allocate
 * more memory for queue overflow, it will simply disregard the enqueue.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/string_queue_array.h"

// ----------------------------------------------------------------------------
int
clear_queue(struct array_queue *queue)
{
    int i;
    for (i=0; i<queue->index; i++) 
    {
        free(queue->queue[i]);
    }
    queue->index = 0;
    return(0);
}

// ----------------------------------------------------------------------------
int
delete_queue(struct array_queue *queue)
{
    int i;
    for (i=0; i<queue->index; i++) 
    {
        free(queue->queue[i]);
    }
    free(queue->queue);
    free(queue);
    return(0);
}

// --------------------------------------------------------------------------
// Return the maximum allowed size of the ArrayList
int 
get_max_size(struct array_queue *queue) 
{
    return queue->size;
}

// ----------------------------------------------------------------------------
struct array_queue* 
initialize_queue(int size) 
{
    struct array_queue *queue;

    // Allocate the queue
    queue = (struct array_queue*) malloc(sizeof(struct array_queue));

    queue->size  = size;
    queue->index = 0;
    queue->queue = (char **) calloc(size, sizeof(char *));

    return queue;
}

// ----------------------------------------------------------------------------
int
is_empty(struct array_queue *queue)
{
    if (queue->index == 0)
        return(1);
    return(0);
}

// ----------------------------------------------------------------------------
int
is_full(struct array_queue *queue)
{
    if (queue->index == queue->size)
        return(1);
    return(0);
}

// ----------------------------------------------------------------------------
void
print_queue(struct array_queue *queue)
{
    int i;
    printf(" - Queue Contents\n");

    for (i=0; i<queue->size; i++) {
        if (i < queue->index)
            printf(" %s ", queue->queue[i]);
        else
            printf("   -   ");

        if (i % 10 == 0 && i != 0)
            printf("\n");
    }
    printf("\n");
}

// ----------------------------------------------------------------------------
void 
print_queue_status(struct array_queue *queue)
{
    printf("\n ********** QUEUE STATUS REPORT **********\n");

    // Is queue empty?
    if (is_empty(queue) == 1)
        printf(" - queue Empty?       Yes\n");
    else
        printf(" - queue Empty?        No\n");

    // Is queue full?
    if (is_full(queue) == 1)
        printf(" - queue Full?        Yes\n");
    else
        printf(" - queue Full?         No\n");

    printf(" - queue Index    = %5d\n", queue->index);
    printf(" - queue Max Size = %5d\n\n", queue->size);

    // Print the queue
    print_queue(queue);

    printf("\n *****************************************\n\n");

}

// ----------------------------------------------------------------------------
int
enqueue(char *value, struct array_queue *queue)
{

    if (is_full(queue) == 1) {
        printf("** ERROR ** :: ENQUEUE :: Queue is full, cannot enqueue additional items\n");
        printf("                         Remove items by calling DEQUEUE\n");
        return(1);
    }

    // Initialize memory in the current stack location to hold this string
    queue->queue[queue->index] = (char *) calloc(strlen(value)+1, sizeof(char));

    strcpy(queue->queue[queue->index], value);
    queue->index++;

    return(0);
}

// ----------------------------------------------------------------------------
int
dequeue(struct array_queue *queue, char *pvalue)
{
    if (is_empty(queue) == 1) {
        printf("** ERROR ** :: DEQUEUE :: queue is empty, cannot get any more items\n");
        printf("                          Add items by calling ENQUEUE\n");
        return(1);
    }

    strcpy(pvalue, queue->queue[0]);

    remove_at_index(0, queue);

    return(0);

}

// --------------------------------------------------------------------------
// Remove item at speficied index
//
int 
remove_at_index(int index, struct array_queue *queue) 
{

    int i;

    if (index > queue->size || index < 0) {
        printf("removeAtIndex Error: Index is out of range\n");
        return 1;   
    }

    // Shift contents over
    for (i=index; i<queue->size; i++) {
        if (i+1 >= get_max_size(queue)) {
            break;
        }

        // Free the memory that we are shifting into
        free(queue->queue[i]);

        // Re-allocate memory in the spot just freed for the item that is about
        // to shift into it
        queue->queue[i] = (char *) calloc(strlen(queue->queue[i+1])+1, sizeof(char));

        // Copy the item over
        strcpy(queue->queue[i], queue->queue[i+1]);

    }

    // Finally free the last index that used to be at the rear of the queue
    free(queue->queue[i]);

    queue->index--;

    return 0;

}

// ----------------------------------------------------------------------------
int
main(int argc, char **argv)
{
    char pvalue[255];
    struct array_queue *queue;

    printf("\n\nINTEGER QUEUE ARRAY IN C\n\n");
    queue = initialize_queue(10);
    print_queue_status(queue);

    enqueue("Hello" ,queue);
    enqueue("this"  ,queue);
    enqueue("is"    ,queue);
    enqueue("a"     ,queue);
    enqueue("string",queue);
    enqueue("based" ,queue);
    enqueue("stack" ,queue);
    enqueue("It"    ,queue);
    enqueue("is"    ,queue);
    enqueue("a"     ,queue);
    print_queue_status(queue);

    printf("enqueue 11 to the full queue\n");
    enqueue("complicated" ,queue);
    print_queue_status(queue);

    printf("dequeue the top value at the start of the queue\n");
    dequeue(queue, pvalue);
    printf("dequeued '%s' from the queue\n", pvalue);
    print_queue_status(queue);

    printf("enqueue 11 to the full queue\n");
    enqueue("complicated" ,queue);
    print_queue_status(queue);

    printf("\nClear the queue\n");
    clear_queue(queue);    
    print_queue_status(queue);

    delete_queue(queue);
}