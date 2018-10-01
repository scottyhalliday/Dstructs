#include <iostream>
#include "arrayList.h"

ArrayList::ArrayList(int size) {
  std::cout << "I am in the ArrayList constructor" << std::endl;
  maxSize = size;
  length  = 0;
  list    = new int[size];
}

// ArrayList::getMaxSize()
// 
// Return the maximum size of the array list
///////////////////////////////////////////////////////////////////////////////
int ArrayList::getMaxSize() const {
  return maxSize;
}

// ArrayList::getLength()
//
// Return the current length of the array list
///////////////////////////////////////////////////////////////////////////////
int ArrayList::getLength() const {
  return length;
}

// ArrayList::isEmpty()
//
// Return boolean value which indicates if the list is empty
///////////////////////////////////////////////////////////////////////////////
bool ArrayList::isEmpty() const {
  return (length == 0);
}

// ArrayList::isFull()
//
// Return boolean value which indicates if the list is full
///////////////////////////////////////////////////////////////////////////////
bool ArrayList::isFull() const {
  return (length == maxSize-1);
}

// ArrayList::clear()
//
// Clear the array list 
///////////////////////////////////////////////////////////////////////////////
void ArrayList::clear() {
  length = 0;
}

// ArrayList::insertEnd(int value)
//
// Insert an item at the end of the list 
///////////////////////////////////////////////////////////////////////////////
void ArrayList::insertEnd(int value) {
  if (this->isFull() == 1) {
    std::cout << "List is full cannot add more" << std::endl;
    return;
  }

  this->list[length] = value;

  std::cout << "Adding Value: " << value << " At Index: " << length << std::endl;

  length++;

}

// ArrayList::insertAt(int index, int value)
//
// Insert an item at a given index in the array list.  If index is beyond the
// range of the current list an error is thrown and nothing is done 
///////////////////////////////////////////////////////////////////////////////
void ArrayList::insertAt(int index, int value) {
  if (this->isFull() == 1) {
    std::cout << "List is full cannot add more" << std::endl;
    return;
  } else if (index > this->length || index < 0) {
    std::cout << "Index is outside the range of the current list.  Array length = " << length << " and index = " << index << std::endl;
    return;
  }

  // Make space for the new value by moving all values to the right by one for values beyond/at index
  for (int i=index+1; i < length+1; i++) {
    this->list[i] = this->list[i-1];
  }

  this->list[index] = value;
  length++;

}

// ArrayList::print()
//
// Print the contents of the list
///////////////////////////////////////////////////////////////////////////////
void ArrayList::print() const {

  std::cout << " Array List Content:" << std::endl;
  for (int i=0; i<length; i++) {

    if (i % 10 == 0 && i != 0) {
      std::cout << std::endl;
    }
    std::cout << this->list[i] << " ";
  }
  std::cout << std::endl;
}

// ****************************************************************************
int main() {
  std::cout << "Hello ArrayList" << std::endl;

  int list2add[] = {1,54,26,7878,56,54,878,2135,24,23,5868,5268,788};

  ArrayList intArray1;

  for (int i=0; i < 13; i++) {
    intArray1.insertEnd(list2add[i]);  
  }
  
  intArray1.print();

}
