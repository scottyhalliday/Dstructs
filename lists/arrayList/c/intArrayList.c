//
// intArrayList.c
// By Scott Hall
//
// Models the data structure for an Integer type ArrayList

#include <stdio.h>
#include <stdlib.h>
#include "intArrayList.h"

// An initializer (sort of a constructor) for integer array list
void IntArrayList(int size, intArrayList *arrayList) {

    arrayList->maxSize = size;
    arrayList->length  = 0;
    arrayList->aList   = (int *) calloc(size, sizeof(int));

}

// --------------------------------------------------------------------------

// Return the maximum allowed size of the ArrayList
int getMaxSize(intArrayList arrayList) {
    return arrayList.maxSize;
}

// --------------------------------------------------------------------------

// Return the current length of the array list
int getLength(intArrayList arrayList) {
    return arrayList.length;
}

// --------------------------------------------------------------------------

// Returns whether the list is empty or not
int isEmpty(intArrayList arrayList) {
    if (arrayList.length == 0) {
        return 1;
    } 
    return 0;
}

// --------------------------------------------------------------------------

// Returns whether the list is full
int isFull(intArrayList arrayList) {
    if (arrayList.length == arrayList.maxSize) {
        return 1;
    }
    return 0;
}

// --------------------------------------------------------------------------

// Clear the ArrayList
void clear(intArrayList arrayList) {
    arrayList.length = 0;
}

// --------------------------------------------------------------------------

// Check if a specified item is in the ArrayList.  Returns the index of the
// match or a -1 if the item is not in the list
int searchArrayList(int value, intArrayList arrayList) {
    int i;

    for (i=0; i<arrayList.length; i++) {
        if (value == arrayList.aList[i]) {
            return i;
        }
    }
    return -1;
}

// --------------------------------------------------------------------------

// Insert an item at the end of the list if it does not already exist
int insertAtEnd(int value, intArrayList *arrayList) {

    if (isFull(*arrayList) == 1) {
        printf("insertAtEnd Error: List is already full.  Cannot add new item\n");
        return 1;
    }    

    if (searchArrayList(value, *arrayList) != -1) {
        printf("insertAtEnd Error: List is already has %d.  Cannot add new item\n", value);
        return 1;
    }

    arrayList->aList[arrayList->length] = value;
    arrayList->length++;

    return 0;
}

// --------------------------------------------------------------------------

// Insert an item at a specified index.  Index must exist, item not already
// exist and the list is not full for item to be added.  All items are 
// shifted
int insertAtIndex(int index, int value, intArrayList *arrayList) {

    int i;

    if (isFull(*arrayList) == 1) {
        printf("insertAtEnd Error: List is already full.  Cannot add new item\n");
        return 1;
    }    

    if (searchArrayList(value, *arrayList) != -1) {
        printf("insertAtEnd Error: List is already has %d.  Cannot add new item\n", value);
        return 1;
    }

    if (index > arrayList->length || index < 0) {
        printf("insertAtEnd Error: Index is out of range\n");
        return 1;   
    }

    arrayList->length++;

    for (i=arrayList->length; i>=index; i--) {
        arrayList->aList[i+1] = arrayList->aList[i];
    }

    arrayList->aList[index] = value;

    return 0;

}

// --------------------------------------------------------------------------

// Check if an item at a given index is equal to value
int isItemAtEqual(int index, int value, intArrayList arrayList) {

    if (index > arrayList.length || index < 0) {
        printf("isItemAtEqual Error: Index is out of range\n");
        return -1;   
    }

    if (arrayList.aList[index] == value) {
        return 1;
    }

    return 0;

}

// --------------------------------------------------------------------------

// Remove item at speficied index
int removeAtIndex(int index, intArrayList *arrayList) {

    int i;

    if (index > arrayList->length || index < 0) {
        printf("insertAtEnd Error: Index is out of range\n");
        return 1;   
    }

    // Shift contents over
    for (i=index; i<arrayList->length; i++) {
        if (i+1 >= getMaxSize(*arrayList)) {
            break;
        }
        arrayList->aList[i] = arrayList->aList[i+1];
    }

    arrayList->length--;

    return 0;

}

// --------------------------------------------------------------------------

// Remove specified item from list (if it exists)
int removeItem(int value, intArrayList *arrayList) {

    int i;
    int index;

    // Get index of value in the list
    index = searchArrayList(value, *arrayList);

    if (index == -1) {
        printf("removeItem Error: List does not contain %d.  Cannot remove item\n", value);
        return 1;
    }

    // Shift contents over
    for (i=index; i<arrayList->length; i++) {
        arrayList->aList[i] = arrayList->aList[i+1];
    }

    arrayList->length--;

    return 0;

}

// --------------------------------------------------------------------------

// Remove specified item from list (if it exists)
int getItemAtIndex(int index, int *value, intArrayList arrayList) {

    if (index > arrayList.length || index < 0) {
        printf("getItemAtIndex Error: Index is out of range\n");
        return -1;   
    }

    *value = arrayList.aList[index];

    return 0;

}

// --------------------------------------------------------------------------

// Print the list contents
void printList(intArrayList arrayList) {

    int i;

    printf("Integer ArrayList:\n");

    for (i=0; i<arrayList.length; i++) {

        if (i>0 && i%10==10) {
            printf("\n");
        }

        printf("%10d, ", arrayList.aList[i]);

    }

    printf("\n");
}

// --------------------------------------------------------------------------

// Free the dynamically allocated ArrayList
void freeList(intArrayList *arrayList) {
    free(arrayList->aList);
}

// --------------------------------------------------------------------------

int main() {

    int i;
    int value;

    // Create and initialize an array list
    intArrayList arrayList1;
    intArrayList arrayList2;

    // Initialize the array lists
    IntArrayList(20, &arrayList1);
    IntArrayList(10, &arrayList2);

    for (i=0; i<10; i++) {
        insertAtEnd(i, &arrayList1);
        insertAtEnd(i, &arrayList2);
    }

    printf("ArrayList 1:\n");
    printList(arrayList1);
    printf("List length size %d and max size %d\n", getLength(arrayList1), getMaxSize(arrayList1));

    printf("\nLet's add 99 at index 2\n"); // Should work
    insertAtIndex(2,99, &arrayList1);
    printList(arrayList1);

    printf("\nLet's try to add 99 at index 2 again\n"); // Should fail, we already added 99
    insertAtIndex(2,99, &arrayList1);
    printList(arrayList1);

    printf("\nLet's check if index 2 has 99 in it\n"); 
    printf("Is 99 at index 2? %d\n", isItemAtEqual(2,99, arrayList1));

    printf("\nLet's remove the value 99\n");
    removeItem(99, &arrayList1);
    printList(arrayList1);

    printf("\nLet's fetch the item at index 7\n");
    printf("Did I find something? %d Better not get -1\n", getItemAtIndex(7, &value, arrayList1));
    printf("The value fetched is %d\n", value);


    printf("\n\nArrayList 2:\n");
    printList(arrayList2);
    printf("List length size %d and max size %d\n", getLength(arrayList2), getMaxSize(arrayList2));

    printf("\nLet's add 99 at index 2\n"); // Should fail, list is full
    insertAtIndex(2,99, &arrayList2);
    printList(arrayList2);

    printf("\nLet's remove the value at index 5\n");
    removeAtIndex(5, &arrayList2);
    printList(arrayList2);

    // Free the lists before quitting
    freeList(&arrayList1);
    freeList(&arrayList2);

    return 0;

}