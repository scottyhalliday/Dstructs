#include <iostream>
#include "arrayList.h"

ArrayList::ArrayList(int size) {
  std::cout << "I am in the ArrayList constructor" << std::endl;
  m_maxSize = size;
  m_length  = 0;
  m_list    = new int[size];
}

// ArrayList::getMaxSize()
//
// Return the maximum size of the array list
///////////////////////////////////////////////////////////////////////////////
int ArrayList::getMaxSize() const {
  return m_maxSize;
}

// ArrayList::getLength()
//
// Return the current length of the array list
///////////////////////////////////////////////////////////////////////////////
int ArrayList::getLength() const {
  return m_length;
}

// ArrayList::isEmpty()
//
// Return boolean value which indicates if the list is empty
///////////////////////////////////////////////////////////////////////////////
bool ArrayList::isEmpty() const {
  return (m_length == 0);
}

// ArrayList::isFull()
//
// Return boolean value which indicates if the list is full
///////////////////////////////////////////////////////////////////////////////
bool ArrayList::isFull() const {
  return (m_length == m_maxSize);
}

// ArrayList::clear()
//
// Clear the array list
///////////////////////////////////////////////////////////////////////////////
void ArrayList::clear() {
  m_length = 0;
}

// ArrayList::insertEnd(int value)
//
// Insert an item at the end of the list
///////////////////////////////////////////////////////////////////////////////
void ArrayList::insertEnd(int value) {
  if (isFull() == 1) {
    std::cerr << "List is full cannot add more" << std::endl;
    return;
  }

  m_list[m_length] = value;

  std::cout << "Adding Value: " << value << " At Index: " << m_length << std::endl;

  m_length++;

}

// ArrayList::insertAt(int index, int value)
//
// Insert an item at a given index in the array list.  If index is beyond the
// range of the current list an error is thrown and nothing is done
///////////////////////////////////////////////////////////////////////////////
void ArrayList::insertAt(int index, int value) {
  if (index > m_maxSize) {

  } if (isFull() == 1) {
    std::cerr << "List is full cannot add more" << std::endl;
    return;
  } else if (index > m_length || index < 0) {
    std::cerr << "Index is outside the range of the current list.  Array length = " << m_length << " and index = " << index << std::endl;
    return;
  }

  // Make space for the new value by moving all values to the right by one for values beyond/at index
  for (int i=m_length+1; i > index; i--) {
    m_list[i] = m_list[i-1];
  }

  m_list[index] = value;
  m_length++;

}

// ArrayList::print()
//
// Print the contents of the list
///////////////////////////////////////////////////////////////////////////////
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

// ArrayList::isItemAtEqual(int index, int value)
//
// Determine if the value specified is equal to the value in the arrayList
// at the given index.
///////////////////////////////////////////////////////////////////////////////
bool ArrayList::isItemAtEqual(int index, int value) const {

  if (index > m_length || index < 0) {
    std::cerr << "Index is outside the range of the current list.  Array length = " << m_length << " and index = " << index << std::endl;
    return(0);
  }

  return(m_list[index] == value);

}

// ****************************************************************************
int main() {
  std::cout << "Hello ArrayList" << std::endl;

  int list2add[] = {1,54,26,7878,56,54,878,2135,24,23,5868,5268,788};

  ArrayList intArray1(15);

  for (int i=0; i < 13; i++) {
    intArray1.insertEnd(list2add[i]);
  }

  intArray1.print();
  intArray1.insertAt(20,777);
  intArray1.print();
  std::cout << "Current list length " << intArray1.getLength() << std::endl;
  std::cout << "Does they equal " << intArray1.isItemAtEqual(4,54) << std::endl;


}
