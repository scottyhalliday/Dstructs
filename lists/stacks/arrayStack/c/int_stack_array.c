/*
 * INT_STACK_ARRAY.C
 *
 * Author       : Scott Hall
 * Contributors : Scott Hall (Github: smhall316)
 *                (Please add your name if you contribute)
 *
 * Description:
 * Implementation of an integer type stack using the array list data structure.  
 * The stack is a fixed length array list.  If the stack is full and another
 * item is added an error will occur.  This implementation will not allocate
 * more memory for stack overflow, it will simply disregard the push.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "include/int_stack_array.h"

// ----------------------------------------------------------------------------
int
clear_stack(struct array_stack *stack)
{
    stack->index = 0;
    return(0);
}

// ----------------------------------------------------------------------------
int
delete_stack(struct array_stack *stack)
{
    free(stack->stack);
    free(stack);
    return(0);
}

// ----------------------------------------------------------------------------
struct array_stack* 
initialize_stack(int size) 
{
    struct array_stack *stack;

    // Allocate the stack
    stack = (struct array_stack*) malloc(sizeof(struct array_stack));

    stack->size  = size;
    stack->index = 0;
    stack->stack = (int *) calloc(size, sizeof(int));

    return stack;
}

// ----------------------------------------------------------------------------
int
is_empty(struct array_stack *stack)
{
    if (stack->index == 0)
        return(1);
    return(0);
}

// ----------------------------------------------------------------------------
int
is_full(struct array_stack *stack)
{
    if (stack->index == stack->size)
        return(1);
    return(0);
}

// ----------------------------------------------------------------------------
void
print_stack(struct array_stack *stack)
{
    int i;
    printf(" - Stack Contents\n");

    for (i=0; i<stack->size; i++) {
        if (i < stack->index)
            printf(" %5d ", stack->stack[i]);
        else
            printf("   -   ");

        if (i % 10 == 0 && i != 0)
            printf("\n");
    }
    printf("\n");
}

// ----------------------------------------------------------------------------
void 
print_stack_status(struct array_stack *stack)
{
    printf("\n ********** STACK STATUS REPORT **********\n");

    // Is stack empty?
    if (is_empty(stack) == 1)
        printf(" - Stack Empty?       Yes\n");
    else
        printf(" - Stack Empty?        No\n");

    // Is stack full?
    if (is_full(stack) == 1)
        printf(" - Stack Full?        Yes\n");
    else
        printf(" - Stack Full?         No\n");

    printf(" - Stack Index    = %5d\n", stack->index);
    printf(" - Stack Max Size = %5d\n\n", stack->size);

    // Print the stack
    print_stack(stack);

    printf("\n *****************************************\n\n");

}

// ----------------------------------------------------------------------------
int
push(int value, struct array_stack *stack)
{

    if (is_full(stack) == 1) {
        printf("** ERROR ** :: PUSH :: Stack is full, cannot push additional items\n");
        printf("                       Remove items by calling POP\n");
        return(1);
    }

    stack->stack[stack->index] = value;
    stack->index++;

    return(0);
}

// ----------------------------------------------------------------------------
int
pop(struct array_stack *stack, int *pvalue)
{
    if (is_empty(stack) == 1) {
        printf("** ERROR ** :: POP :: Stack is empty, cannot get any more items\n");
        printf("                      Add items by calling PUSH\n");
        return(1);
    }

    *pvalue = stack->stack[stack->index-1];
    stack->index--;

    return(0);

}

// ----------------------------------------------------------------------------
int
main(int argc, char **argv)
{
    int pvalue;
    struct array_stack *stack;

    printf("\n\nINTEGER STACK ARRAY IN C\n\n");
    stack = initialize_stack(10);
    print_stack_status(stack);

    push(1 ,stack);
    push(2 ,stack);
    push(3 ,stack);
    push(4 ,stack);
    push(5 ,stack);
    push(6 ,stack);
    push(7 ,stack);
    push(8 ,stack);
    push(9 ,stack);
    push(10,stack);
    print_stack_status(stack);

    printf("Push 11 to the full stack\n");
    push(11 ,stack);
    print_stack_status(stack);

    printf("Pop the top value off the stack\n");
    pop(stack, &pvalue);
    printf("Popped %5d from the stack\n", pvalue);
    print_stack_status(stack);

    printf("Push 11 to the full stack\n");
    push(11 ,stack);
    print_stack_status(stack);

    printf("\nClear the stack\n");
    clear_stack(stack);    
    print_stack_status(stack);

    delete_stack(stack);
}