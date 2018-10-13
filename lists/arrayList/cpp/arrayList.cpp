#include <iostream>
#include "arrayList.h"

//-----------------------------------------------------------------------------

// Constructor for initializing the ArrayList
//
// If the size of the list is specified otherwise it will use the
// default size of 100.  The member access specifieds denoted m_*
// are responsible for storing the maximum ArrayList size and the
// current ArrayList size.
template <class arrayType>
ArrayList<arrayType>::ArrayList(int size) {
  std::cout << "Initializing ArrayList for data type '"
            << typeid(arrayType).name()
            << "'" << std::endl;

  m_maxSize = size;
  m_length  = 0;
  m_list    = new arrayType[size];
}

//-----------------------------------------------------------------------------

// Copy constructor for ArrayList
template <class arrayType>
ArrayList<arrayType>::ArrayList(const ArrayList<arrayType> &cpList) {
  std::cout << "Initializing ArrayList for data type '"
            << typeid(arrayType).name()
            << "' via Copy Constructor" << std::endl;

  m_maxSize = cpList.m_maxSize;
  m_length  = cpList.m_length;
  m_list    = new arrayType[m_maxSize];

  for (int i=0; i<m_length; i++) {
    m_list[i] = cpList.m_list[i];
  }
}

//-----------------------------------------------------------------------------

// Deallocate the ArrayList when done with it -- Free the memory
template <class arrayType>
ArrayList<arrayType>::~ArrayList() {
  delete[] m_list;
}

//-----------------------------------------------------------------------------

// Get the list maximum size
//
// This is simply a reference to the declared size of the array at
// initialization time
template <class arrayType>
int ArrayList<arrayType>::getMaxSize() const {
  return m_maxSize;
}

//-----------------------------------------------------------------------------

// Get the current length of the array
//
// Remember that the ArrayList is in sequential order which usese
// m_length to track where the current ArrayList content ends
template <class arrayType>
int ArrayList<arrayType>::getLength() const {
  return m_length;
}

//-----------------------------------------------------------------------------

// A check to see if the ArrayList is currently empty
template <class arrayType>
bool ArrayList<arrayType>::isEmpty() const {
  return (m_length == 0);
}

//-----------------------------------------------------------------------------

// A check to see if the ArrayList is full
//
// Cannot add additional items if the ArrayList is full
template <class arrayType>
bool ArrayList<arrayType>::isFull() const {
  return (m_length == m_maxSize);
}

//-----------------------------------------------------------------------------

// Clear the ArrayList
//
// Simply resets the ArrayList length class variable.  Doesn't
// actually remove items but just resets the m_length index
// to the beginning of the ArrayList for overwrite.
template <class arrayType>
void ArrayList<arrayType>::clear() {
  m_length = 0;
}

//-----------------------------------------------------------------------------

// Insert the item at the end of the list
//
// Will add the item at the end of the list providing the list isn't full!
template <class arrayType>
void ArrayList<arrayType>::insertAtEnd(const arrayType& value) {
  if (isFull() == 1) {
    std::cerr << "*** ERROR ***\nList is full cannot add more" << std::endl;
    return;
  } else if (searchArrayList(value) != -1) {
      std::cerr << "*** ERROR ***\n"
                   "Value '" << value << "' already exists in the list.  "
                   "Cannot have duplicates.  Not adding value!!!"
                << std::endl;
      return;
  }

  m_list[m_length] = value;

  // Increase the ArrayList end index tracker by 1
  m_length++;

}

//-----------------------------------------------------------------------------

// Insert an item at the specified index
//
// Inserts the item at the index specified so long as the index is valid and
// item does not already exist in the ArrayList
template <class arrayType>
void ArrayList<arrayType>::insertAtIndex(const int index, const arrayType& value) {
  if (index > m_maxSize) {

  } if (isFull() == 1) {
      std::cerr <<  "*** ERROR ***\nList is full cannot add more" << std::endl;
      return;
  } else if (index > m_length || index < 0) {
      std::cerr << "*** ERROR ***\n"
                   "Index is outside the range of the current list.  "
                   "Array length = " << m_length
                << " and index = "   << index
                << std::endl;
    return;
  } else if (searchArrayList(value) != -1) {
      std::cerr << "*** ERROR ***\n"
                   "Value '" << value << "' already exists in the list.  "
                   "Cannot have duplicates.  Not adding value!!!"
                << std::endl;
      return;
  }

  // Make space for the new value by moving all values to the right by one
  // for values beyond/at index
  for (int i=m_length; i > index; i--) {
    m_list[i] = m_list[i-1];
  }

  m_list[index] = value;
  m_length++;

}

//-----------------------------------------------------------------------------

// Returns whether the value at the specified index is equal to the value
// in the ArrayList
template <class arrayType>
bool ArrayList<arrayType>::isItemAtEqual(const int index, const arrayType& value) const {

  if (index > m_length || index < 0) {
    std::cerr << "*** ERROR ***\n"
                 "Index is outside the range of the current list.  "
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
template <class arrayType>
void ArrayList<arrayType>::removeAtIndex(const int index) {

  if (index > m_length || index < 0) {
    std::cerr << "*** ERROR ***\n"
                 "Index is outside the range of the current list.  "
                 "Array length = " << m_length
              << " and index = " << index
              << std::endl;
    return;
  }

  // Move the items to the left to keep list continuous.
  for (int i=index; i<m_length-1; i++) {
    m_list[i] = m_list[i+1];
  }

  m_length--;

}

//-----------------------------------------------------------------------------

// Removes specified item from the ArrayList
//
// Removes an item identified if it exists in the ArrayList.  If it does not
// exist then nothing is removed.
template <class arrayType>
void ArrayList<arrayType>::remove(const arrayType& value) {

  // Get the index where the value to remove is located
  int index = searchArrayList(value);

  if (index == -1) {
    std::cerr << "*** ERROR ***\n"
                 "Value '" << value << "' is not currently in the list."
                 "Nothing to delete so doing nothing."
              << std::endl;
    return;
  }

  // Move the items to the left to keep list continuous.
  for (int i=index; i<m_length-1; i++) {
    m_list[i] = m_list[i+1];
  }

  m_length--;

}
//-----------------------------------------------------------------------------

// Get the item at the specified index
//
// If the index is not valid then return an error
template <class arrayType>
int ArrayList<arrayType>::getItemAtIndex(const int index, arrayType& value) {

  if (index < 0 || index > m_length) {
    std::cerr << "*** ERROR ***\n"
                 "Index is outside the range of the current list.  "
                 "Array length = " << m_length
              << " and index = " << index
              << std::endl;
    return -1;
  }

  value = m_list[index];
  return 0;

}

//-----------------------------------------------------------------------------

// Print the ArrayList items
//
// Prints the ArrayList at 10 items per line
template <class arrayType>
void ArrayList<arrayType>::print() const {

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
template <class arrayType>
int ArrayList<arrayType>::searchArrayList(const arrayType& value) const {

  for (int i=0; i<m_length; i++) {
    if (m_list[i] == value) {
      return i;
    }
  }

  return(-1);
}

//-----------------------------------------------------------------------------

int main() {

  std::cout << "****************************************************\n"
            << "*                                                  *\n"
            << "*         C++ Implementation of ArrayList          *\n"
            << "*                                                  *\n"
            << "****************************************************\n"
            << std::endl;

  // Initialize the ArrayLists
  ArrayList<int>         intList(10);
  ArrayList<double>      doubleList;
  ArrayList<std::string> stringList;

  // Create some data to populate the list
  int         intInput[10]    = {0,1,2,3,4,5,6,7,8,9};
  double      doubleInput[10] = {1.2, 2.3, 3.4, 4.5 , 5.6,
                                 6.7, 7.8, 8.9, 9.10, 10.11};
  std::string stringInput[10] = {"ab", "bc", "cd", "de", "ef",
                                 "fg", "gh", "hi", "jk", "kl"};
  for (int i=0; i<10; i++) {
    intList.insertAtEnd(intInput[i]);
    doubleList.insertAtEnd(doubleInput[i]);
    stringList.insertAtEnd(stringInput[i]);
  }

  // Print the lists
  std::cout << "\nInteger ArrayList:" << std::endl;
  intList.print();

  std::cout << "\nDouble ArrayList:" << std::endl;
  doubleList.print();

  std::cout << "\nString ArrayList:" << std::endl;
  stringList.print();

  std::cout << "\n\n ************* INTEGER ARRAYLIST TESTING ***************\n\n";

  std::cout << "\nAttempting to add '10' to integer list.  Should fail "
            << "since list is already full."
            << std::endl;
  intList.insertAtEnd(10);

  // Remove an item from the integer ArrayList
  std::cout << "\nAttempting to remove item in the third index.  "
            << "Should succeed."
            << std::endl;
  intList.removeAtIndex(3);
  std::cout << "Current List:" << std::endl;
  intList.print();

  std::cout << "\nAttempting to add '10' to integer list.  Should work "
            << "now that there is space for it."
            << std::endl;
  intList.insertAtEnd(10);
  std::cout << "Current List:" << std::endl;
  intList.print();

  std::cout << "\nAttempting to remove item label '6' from integer list.  "
            << "Should work "
            << std::endl;
  intList.remove(6);
  std::cout << "Current List:" << std::endl;
  intList.print();

  std::cout << "\n Attempting to insert an item '6' at index 2" << std::endl;
  intList.insertAtIndex(2,6);
  std::cout << "Current List:" << std::endl;
  intList.print();

  std::cout << "\nClear the list"
            << std::endl;
  intList.clear();
  std::cout << "Current List:" << std::endl;
  intList.print();

  std::cout << "\n\n ************* DOUBLE ARRAYLIST TESTING ***************\n\n";

  std::cout << "\nAttempting to add '100.9' to integer list.  Should work "
            << std::endl;
  doubleList.insertAtEnd(100.9);
  std::cout << "Current List:" << std::endl;
  doubleList.print();

  // Remove an item from the integer ArrayList
  std::cout << "\nAttempting to remove item in the 30 index.  "
            << "Should fail since nothing is there."
            << std::endl;
  doubleList.removeAtIndex(30);
  std::cout << "Current List:" << std::endl;
  doubleList.print();

  std::cout << "\nAttempting to add '1009.85' to integer list at index 9.  "
            << "Should work."
            << std::endl;
  doubleList.insertAtIndex(9, 1009.85);
  std::cout << "Current List:" << std::endl;
  doubleList.print();

  std::cout << "\nAttempting to remove item label '7.8' from integer list.  "
            << "Should work "
            << std::endl;
  doubleList.remove(7.8);
  std::cout << "Current List:" << std::endl;
  doubleList.print();

  std::cout << "\nClear the list"
            << std::endl;
  doubleList.clear();
  std::cout << "Current List:" << std::endl;
  doubleList.print();

  std::cout << "\n\n ************* STRING ARRAYLIST TESTING ***************\n\n";

  std::cout << "\nAttempting to add 'silly' to integer list.  Should work "
            << std::endl;
  stringList.insertAtEnd("silly");
  std::cout << "Current List:" << std::endl;
  stringList.print();

  // Remove an item from the integer ArrayList
  std::cout << "\nAttempting to remove item in the 30 index.  "
            << "Should fail since nothing is there."
            << std::endl;
  stringList.removeAtIndex(30);
  std::cout << "Current List:" << std::endl;
  stringList.print();

  std::cout << "\nAttempting to add 'super' to integer list at index 9.  "
            << "Should work."
            << std::endl;
  stringList.insertAtIndex(9, "super");
  std::cout << "Current List:" << std::endl;
  stringList.print();

  std::cout << "\nAttempting to remove item label 'de' from integer list.  "
            << "Should work "
            << std::endl;
  stringList.remove("de");
  std::cout << "Current List:" << std::endl;
  stringList.print();

  std::string value;
  int found;
  found = stringList.getItemAtIndex(3, value);
  if (found == -1) {
    std::cout << "\n*** ERROR ***\n"
                 "Could not get item at index 3.  Value does not exist"
              << std::endl;

  } else {
    std::cout << "\nGetting item at index 3 whose value is '"
              << value << "'" << std::endl;

  }

  std::cout << "\nClear the list"
            << std::endl;
  stringList.clear();
  std::cout << "Current List:" << std::endl;
  stringList.print();


}
