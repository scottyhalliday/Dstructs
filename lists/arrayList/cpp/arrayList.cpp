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
  std::cout << "*** Copy constructor" << std::endl;
  m_maxSize = cpList.m_maxSize;
  m_length  = cpList.m_length;
  m_list    = new int[m_maxSize];

  for (int i=0; i<m_length; i++) {
    m_list[i] = cpList.m_list[i];
  }
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
// actually remove items but just resets the m_length index
// to the beginning of the ArrayList for overwrite.
void ArrayList::clear() {
  m_length = 0;
}

//-----------------------------------------------------------------------------

// Insert the item at the end of the list
//
// Will add the item at the end of the list providing the list isn't full!
void ArrayList::insertAtEnd(const int value) {
  if (isFull() == 1) {
    std::cerr << "List is full cannot add more" << std::endl;
    return;
  } else if (searchArrayList(value) != -1) {
      std::cerr << "Value " << value << " already exists in the list.  "
                   "Cannot have duplicates.  Not adding value!!!"
                << std::endl;
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
// Inserts the item at the index specified so long as the index is valid and
// item does not already exist in the ArrayList
void ArrayList::insertAtIndex(const int index, const int value) {
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
  } else if (searchArrayList(value) != -1) {
      std::cerr << "Value " << value << " already exists in the list.  "
                   "Cannot have duplicates.  Not adding value!!!"
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
bool ArrayList::isItemAtEqual(const int index, const int value) const {

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
void ArrayList::removeAtIndex(const int index) {

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

// Removes specified item from the ArrayList
//
// Removes an item identified if it exists in the ArrayList.  If it does not
// exist then nothing is removed.
void ArrayList::remove(const int value) {

  // Get the index where the value to remove is located
  int index = searchArrayList(value);

  if (index == -1) {
    std::cerr << "Value " << value << " is not currently in the list."
                 "Nothing to delete so doing nothing."
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

// Search the ArrayList for the given value
//
// Search the ArrayList for the given value and return the index of the match
// else return -1 to indicate that the value is not currently in the list
int ArrayList::searchArrayList(const int value) const {

  for (int i=0; i<m_length; i++) {
    if (m_list[i] == value) {
      return i;
    }
  }

  return(-1);
}

//-----------------------------------------------------------------------------

int main() {
  std::cout << "Hello ArrayList" << std::endl;
  int list2add[] = {1,54,26,7878,56,54,878,2135,24,23,5868,5268,788};

  ArrayList intArray1(15);

  for (int i=0; i < 13; i++) {
    intArray1.insertAtEnd(list2add[i]);
  }

  intArray1.print();
  intArray1.insertAtIndex(20,777);
  intArray1.print();
  std::cout << "Current list length " << intArray1.getLength() << std::endl;
  std::cout << "Does they equal " << intArray1.isItemAtEqual(4,54) << std::endl;
  intArray1.removeAtIndex(1);
  intArray1.print();
  ArrayList intArray2(intArray1);
  intArray2.print();
  std::cout << " " << std::endl;
  std::cout << " " << std::endl;
  intArray1.removeAtIndex(1);
  intArray1.print();
  intArray2.print();
  std::cout << intArray1.searchArrayList(8585858) << std::endl;
  intArray1.insertAtIndex(3, 878);
  intArray1.remove(878);
  intArray1.print();

}
