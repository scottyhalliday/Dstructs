//
// doubleArrayList
// By Scott Hall
//
// Header file to include global variables and function prototype definition
// for Double type ArrayList

typedef struct {
	int     maxSize;		// Maximum size of the ArrayList
	int     length;		  // Current length of the ArrayList
	double *aList;			// Double array list
} doubleArrayList;

// Functions
void DoubleArrayList(int, doubleArrayList *);
int  getMaxSize(doubleArrayList);
int  getLength(doubleArrayList);
int  isEmpty(doubleArrayList);
int  isFull(doubleArrayList);
void clear(doubleArrayList);
int  searchArrayList(double, doubleArrayList);
int  insertAtEnd(double, doubleArrayList *);
int  insertAtIndex(int, double, doubleArrayList *);
int  isItemAtEqual(int, double, doubleArrayList);
int  removeAtIndex(int, doubleArrayList *);
int  removeItem(double, doubleArrayList *); // Can't call it remove since remove exists in stdio library
void printList(doubleArrayList);
int  getItemAtIndex(int, double *, doubleArrayList);
void freeList(doubleArrayList *);
