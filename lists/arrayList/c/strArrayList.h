//
// strArrayList.h
// By Scott Hall
//
// Header file to include global variables and function prototype definition
// for String type ArrayList

typedef struct {
	int    maxSize;				// Maximum size of the ArrayList
	int    length;				// Current length of the ArrayList
	int    maxStrLength;	// The maximum length of a string in the arraylist
	char **aList;					// String array list
} strArrayList;

// Functions
void StrArrayList(int, int, strArrayList *);
int  getMaxSize(strArrayList);
int  getLength(strArrayList);
int  isEmpty(strArrayList);
int  isFull(strArrayList);
void clear(strArrayList);
int  searchArrayList(char *, strArrayList);
int  insertAtEnd(char *, strArrayList *);
int  insertAtIndex(int, char *, strArrayList *);
int  isItemAtEqual(int, char *, strArrayList);
int  removeAtIndex(int, strArrayList *);
int  removeItem(char *, strArrayList *); // Can't call it remove since remove exists in stdio library
void printList(strArrayList);
int  getItemAtIndex(int, char *, strArrayList);
void freeList(strArrayList *);
