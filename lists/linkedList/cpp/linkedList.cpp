//
// LINKEDLIST.CPP
// Scott Hall
//

#include <iostream>
#include "linkedList.h"

//-----------------------------------------------------------------------------

// Constructor for initializing the linked list
LinkedList::LinkedList() {
  std::cout << "LINKED LIST CONSTRUCTOR" << std::endl;
  m_count = 0;
  m_head  = NULL;
  m_tail  = NULL;
}

//-----------------------------------------------------------------------------

// De-Constructor for cleaning up
LinkedList::~LinkedList() {
  std::cout << "LINKED LIST DECONSTRUCTOR" << std::endl;
}


//-----------------------------------------------------------------------------

int main() {

  std::cout << "****************************************************\n"
            << "*                                                  *\n"
            << "*         C++ Implementation of LinkedList         *\n"
            << "*                                                  *\n"
            << "****************************************************\n"
            << std::endl;

  // Initialize the linked lists
  LinkedList intLinkedList = LinkedList();

}
