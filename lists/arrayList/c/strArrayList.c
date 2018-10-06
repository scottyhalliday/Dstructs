//
// strArrayList.c
// By Scott Hall
//
// Models the data structure for a string type ArrayList

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strArrayList.h"

// An initializer (sort of a constructor) for string array list
void StrArrayList(int size, int maxStrLength, strArrayList *arrayList) {

    int i;

    arrayList->maxSize      = size;
    arrayList->maxStrLength = maxStrLength;
    arrayList->length       = 0;
    arrayList->aList        = (char **) calloc(size, sizeof(char *));

    for (i=0; i<size; i++) {
      arrayList->aList[i] = (char *) calloc(maxStrLength, sizeof(char));
    }

}

//-----------------------------------------------------------------------------

// Return the maximum allowed size of the ArrayList
int getMaxSize(strArrayList arrayList) {
    return arrayList.maxSize;
}

//-----------------------------------------------------------------------------

// Return the current length of the array list
int getLength(strArrayList arrayList) {
    return arrayList.length;
}

// --------------------------------------------------------------------------

// Returns whether the list is empty or not
int isEmpty(strArrayList arrayList) {
    if (arrayList.length == 0) {
        return 1;
    }
    return 0;
}

// --------------------------------------------------------------------------

// Returns whether the list is full
int isFull(strArrayList arrayList) {
    if (arrayList.length == arrayList.maxSize) {
        return 1;
    }
    return 0;
}

// --------------------------------------------------------------------------

// Clear the ArrayList
void clear(strArrayList arrayList) {
    arrayList.length = 0;
}

// --------------------------------------------------------------------------

// Check if a specified item is in the ArrayList.  Returns the index of the
// match or a -1 if the item is not in the list
int searchArrayList(char *str, strArrayList arrayList) {
    int i;

    for (i=0; i<arrayList.length; i++) {
        if (strcmp(str,arrayList.aList[i]) == 0) {
            return i;
        }
    }
    return -1;
}

// --------------------------------------------------------------------------

// Insert an item at the end of the list if it does not already exist
int insertAtEnd(char *str, strArrayList *arrayList) {

    if (isFull(*arrayList) == 1) {
        printf("insertAtEnd Error: List is already full.  Cannot add new item\n");
        return 1;
    }

    if (searchArrayList(str, *arrayList) != -1) {
        printf("insertAtEnd Error: List is already has '%s'.  Cannot add new item\n", str);
        return 1;
    }

    strcpy(arrayList->aList[arrayList->length], str);
    arrayList->length++;

    return 0;
}

// --------------------------------------------------------------------------

// Insert an item at a specified index.  Index must exist, item not already
// exist and the list is not full for item to be added.  All items are
// shifted
int insertAtIndex(int index, char *str, strArrayList *arrayList) {

    int i;

    if (isFull(*arrayList) == 1) {
        printf("insertAtEnd Error: List is already full.  Cannot add new item\n");
        return 1;
    }

    if (searchArrayList(str, *arrayList) != -1) {
        printf("insertAtEnd Error: List is already has '%s'.  Cannot add new item\n", str);
        return 1;
    }

    if (index > arrayList->length || index < 0) {
        printf("insertAtEnd Error: Index is out of range\n");
        return 1;
    }

    arrayList->length++;

    for (i=arrayList->length; i>=index; i--) {
        strcpy(arrayList->aList[i+1], arrayList->aList[i]);
    }

    strcpy(arrayList->aList[index], str);

    return 0;

}

// --------------------------------------------------------------------------

// Check if an item at a given index is equal to value
int isItemAtEqual(int index, char *str, strArrayList arrayList) {

    if (index > arrayList.length || index < 0) {
        printf("isItemAtEqual Error: Index is out of range\n");
        return -1;
    }

    if (strcmp(arrayList.aList[index], str) == 0) {
        return 1;
    }

    return 0;

}

// --------------------------------------------------------------------------

// Remove item at speficied index
int removeAtIndex(int index, strArrayList *arrayList) {

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
        strcpy(arrayList->aList[i], arrayList->aList[i+1]);
    }

    arrayList->length--;

    return 0;

}

// Remove specified item from list (if it exists)
int removeItem(char *str, strArrayList *arrayList) {

    int i;
    int index;

    // Get index of value in the list
    index = searchArrayList(str, *arrayList);

    if (index == -1) {
        printf("removeItem Error: List does not contain '%s'.  Cannot remove item\n", str);
        return 1;
    }

    // Shift contents over
    for (i=index; i<arrayList->length; i++) {
        strcpy(arrayList->aList[i], arrayList->aList[i+1]);
    }

    arrayList->length--;

    return 0;

}

// --------------------------------------------------------------------------

// Remove specified item from list (if it exists)
int getItemAtIndex(int index, char *str, strArrayList arrayList) {

    if (index > arrayList.length || index < 0) {
        printf("getItemAtIndex Error: Index is out of range\n");
        return -1;
    }

    strcpy(str, arrayList.aList[index]);

    return 0;

}

// --------------------------------------------------------------------------

// Print the list contents
void printList(strArrayList arrayList) {

    int i;

    printf("String ArrayList:\n");

    for (i=0; i<arrayList.length; i++) {

        if (i>0 && i%10==10) {
            printf("\n");
        }

        printf("%s, ", arrayList.aList[i]);

    }

    printf("\n");
}

// --------------------------------------------------------------------------

// Free the dynamically allocated ArrayList
void freeList(strArrayList *arrayList) {
    int i;

    for (i=0; i<getMaxSize(*arrayList); i++) {
      free(arrayList->aList[i]);
    }

    free(arrayList->aList);
}

//-----------------------------------------------------------------------------
 int main() {


   char str[255];

   strArrayList strList1;

   StrArrayList(10,255, &strList1);

   insertAtEnd("This"  , &strList1);
   insertAtEnd("is"    , &strList1);
   insertAtEnd("my"    , &strList1);
   insertAtEnd("string", &strList1);
   insertAtEnd("array" , &strList1);
   insertAtEnd("list"  , &strList1);

   printList(strList1);

   printf("\nIs it empty? %d\n", isEmpty(strList1));

   printf("\n Let's insert 'IS' into the list at index 2\n");
   insertAtIndex(2, "IS", &strList1);
   printList(strList1);

   printf("\n Let's insert 'STR' into the list at index 4\n");
   insertAtIndex(4, "STR", &strList1);
   printList(strList1);

   printf("\n Let's insert 'STR' again into the list at index 4.  Should fail\n");
   insertAtIndex(4, "STR", &strList1);
   printList(strList1);

   printf("\n Let's remove the item at index 4\n");
   removeAtIndex(4, &strList1);
   printList(strList1);

   printf("\n Let's remove the item at index 40.  Should fail.\n");
   removeAtIndex(40, &strList1);
   printList(strList1);

   printf("\n Let's remove the item 'This' from the list.\n");
   removeItem("This", &strList1);
   printList(strList1);

   printf("\n Let's remove the item 'NotInList' from the list.  Should fail\n");
   removeItem("NotInList", &strList1);
   printList(strList1);

   printf("\nLet's get an item from the list\n");
   getItemAtIndex(3, str, strList1);
   printf("Item at index 3 is '%s'\n", str);

   freeList(&strList1);

 }
