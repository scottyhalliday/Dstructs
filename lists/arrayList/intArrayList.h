//
// intArrayList
// By Scott Hall
// 
// Header file to include global variables and function prototype definition
// for Integer type ArrayList

typedef struct {
	int  maxSize;		// Maximum size of the ArrayList
	int  length;		// Current length of the ArrayList
	int *aList;			// Integer array list
} intArrayList;

// Functions
void IntArrayList(int, intArrayList *);
int getMaxSize(intArrayList);
int getLength(intArrayList);
int isEmpty(intArrayList);
int isFull(intArrayList);
void clear(intArrayList);
int searchArrayList(int, intArrayList);
int insertAtEnd(int, intArrayList *);
int insertAtIndex(int, int, intArrayList *);
int isItemAtEqual(int, int, intArrayList);
int removeAtIndex(int, intArrayList *);
int removeItem(int, intArrayList *); // Can't call it remove since remove exists in stdio library
void printList(intArrayList);
int getItemAtIndex(int, int *, intArrayList);
void freeList(intArrayList *);