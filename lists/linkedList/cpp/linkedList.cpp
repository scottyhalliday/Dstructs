//
// LINKEDLIST.CPP
// Scott Hall
//

#include <iostream>
#include "linkedList.h"
#include "linkedListNode.h"

//-----------------------------------------------------------------------------

// Constructor for initializing the linked list
LinkedList::LinkedList() {
  std::cout << "LINKED LIST CONSTRUCTOR" << std::endl;
  m_count = 0;
  m_head  = new int;
  m_tail  = new int;
}

//-----------------------------------------------------------------------------

// De-Constructor for cleaning up
LinkedList::~LinkedList() {
  std::cout << "LINKED LIST DECONSTRUCTOR" << std::endl;
  delete m_head;
  delete m_tail;
  m_head = NULL;
  m_tail = NULL;
}

//-----------------------------------------------------------------------------

// Is the list empty
bool LinkedList::isEmpty() {
  if (m_count == 0) {
    return true;
  }
  return false;
}

//-----------------------------------------------------------------------------

// Insert a node at the tail of the list
int LinkedList::insertAtEnd(int value) {

  // Create a new node
  LinkedListNode node;
  node.setNodeData(value);

  if (isEmpty() == true) {
    m_head =
  }

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
