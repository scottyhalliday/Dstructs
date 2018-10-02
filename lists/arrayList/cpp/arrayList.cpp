#include <iostream>
#include "arrayList.h"

//-----------------------------------------------------------------------------

// Constructor for initializing the ArrayList
//
// If the size of the list is specified otherwise it will use the 
// default size of 100.  The member access specifieds denoted m_*
// are responsible for storing the maximum ArrayList size and the 
// current ArrayList size.
ArrayList::ArrayList(int size) {
  std::cout << "I am in the ArrayList constructor" << std::endl;
  m_maxSize = size;
  m_length  = 0;
  m_list    = new int[size];
}

//-----------------------------------------------------------------------------

// Copy constructor for ArrayList
ArrayList::ArrayList(const ArrayList &cpList) {
  std::cout << "Copy constructor" << std::endl;
}

//-----------------------------------------------------------------------------

// Deallocate the ArrayList when done with it -- Free the memory
ArrayList::~ArrayList() {
  delete[] m_list;
}

//-----------------------------------------------------------------------------

// Get the list maximum size
//
// This is simply a reference to the declared size of the array at
// initialization time
int ArrayList::getMaxSize() const {
  return m_maxSize;
}

//-----------------------------------------------------------------------------

// Get the current length of the array
//
// Remember that the ArrayList is in sequential order which usese
// m_length to track where the current ArrayList content ends
int ArrayList::getLength() const {
  return m_length;
}

//-----------------------------------------------------------------------------

// A check to see if the ArrayList is currently empty
bool ArrayList::isEmpty() const {
  return (m_length == 0);
}

//-----------------------------------------------------------------------------

// A check to see if the ArrayList is full
//
// Cannot add additional items if the ArrayList is full
bool ArrayList::isFull() const {
  return (m_length == m_maxSize);
}

//-----------------------------------------------------------------------------

// Clear the ArrayList
//
// Simply resets the ArrayList length class variable.  Doesn't
// actuall remove items but just resets the m_length index
// to the beginning of the ArrayList for overwrite.
void ArrayList::clear() {
  m_length = 0;
}

//-----------------------------------------------------------------------------

// Insert the item at the end of the list
//
// Will add the item at the end of the list providing the list isn't full!
void ArrayList::insertEnd(int value) {
  if (isFull() == 1) {
    std::cerr << "List is full cannot add more" << std::endl;
    return;
  }

  m_list[m_length] = value;

  std::cout << "Adding Value: " << value 
            << " At Index: "    << m_length 
            << std::endl;

  // Increase the ArrayList end index tracker by 1
  m_length++;

}

//-----------------------------------------------------------------------------

// Insert an item at the specified index
//
// Inserts the item at the index specified so long as the index is valid
void ArrayList::insertAt(int index, int value) {
  if (index > m_maxSize) {

  } if (isFull() == 1) {
    std::cerr << "List is full cannot add more" << std::endl;
    return;
  } else if (index > m_length || index < 0) {
    std::cerr << "Index is outside the range of the current list.  "
                 "Array length = " << m_length 
              << " and index = "   << index 
              << std::endl;
    return;
  }

  // Make space for the new value by moving all values to the right by one 
  // for values beyond/at index
  for (int i=m_length+1; i > index; i--) {
    m_list[i] = m_list[i-1];
  }

  m_list[index] = value;
  m_length++;

}

//-----------------------------------------------------------------------------

// Returns whether the value at the specified index is equal to the value
// in the ArrayList
bool ArrayList::isItemAtEqual(int index, int value) const {

  if (index > m_length || index < 0) {
    std::cerr << "Index is outside the range of the current list.  "
                 "Array length = " << m_length 
              << " and index = " << index 
              << std::endl;
    return(0);
  }

  return(m_list[index] == value);

}

//-----------------------------------------------------------------------------

// Removes item at the specified index
//
// Removes the item at the speficied index so long as the index is valid.
// Once removed the ArrayList is shifted to keep it continuous
void ArrayList::removeItemAt(int index) {

  if (index > m_length || index < 0) {
    std::cerr << "Index is outside the range of the current list.  "
                 "Array length = " << m_length 
              << " and index = " << index 
              << std::endl;
    return;
  }

  // Move the items to the left to keep list continuous.
  for (int i=index; i<m_length; i++) {
    m_list[i] = m_list[i+1];
  }

  m_length--;

}

//-----------------------------------------------------------------------------

// Print the ArrayList items
//
// Prints the ArrayList at 10 items per line
void ArrayList::print() const {

  std::cout << " Array List Content:" << std::endl;
  for (int i=0; i<m_length; i++) {

    if (i % 10 == 0 && i != 0) {
      std::cout << std::endl;
    }
    std::cout << m_list[i] << ", ";
  }
  std::cout << std::endl;
}

//-----------------------------------------------------------------------------

int main() {
  std::cout << "Hello ArrayList" << std::endl;
  std::cout << __cplusplus;
  int list2add[] = {1,54,26,7878,56,54,878,2135,24,23,5868,5268,788};

  ArrayList intArray1(15);
  ArrayList intArray2(intArray1);

  for (int i=0; i < 13; i++) {
    intArray1.insertEnd(list2add[i]);
  }

  intArray1.print();
  intArray1.insertAt(20,777);
  intArray1.print();
  std::cout << "Current list length " << intArray1.getLength() << std::endl;
  std::cout << "Does they equal " << intArray1.isItemAtEqual(4,54) << std::endl;
  intArray1.removeItemAt(1);
  intArray1.print();

}
