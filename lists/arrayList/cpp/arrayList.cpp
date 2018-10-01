#include <iostream>
#include "arrayList.h"

ArrayList::ArrayList(int size) {
  std::cout << "I am in the ArrayList constructor" << std::endl;
  maxSize = size;
  length  = 0;
  list    = new int[size];
}

// ArrayList::getMaxSize()
// ----------------------------------------------------------------------------
// INPUT      : None
// OUTPUT     : Integer value representing the maximum size of the array list
// DESCRIPTION:
//    Return the maximum size of the array list
int ArrayList::getMaxSize() {
  return maxSize;
}

// ArrayList::isEmpty()
// ----------------------------------------------------------------------------
// INPUT      : None
// OUTPUT     : Boolean value which tells that if the list is empty
// DESCRIPTION:
//    Return boolean value which indicates if the list is empty
bool const ArrayList::isEmpty() {
  return (length == 0);
}

// ArrayList::isFull()
// ----------------------------------------------------------------------------
// INPUT      : None
// OUTPUT     : Boolean value which tells that if the list is full
// DESCRIPTION:
//    Return boolean value which indicates if the list is full
bool ArrayList::isFull() const {
  return (length == maxSize-1);
}

// ****************************************************************************
int main() {
  std::cout << "Hello ArrayList" << std::endl;

  ArrayList intArray1;
  std::cout << "intArray1 maxSize = " << intArray1.getMaxSize() << std::endl;
  std::cout << "intArray1 Empty?    " << intArray1.isEmpty() << std::endl;
  std::cout << "intArray1 Full?     " << intArray1.isFull() << std::endl;
}
