//
// LINKEDLISTNODE.CPP
// Scott Hall
//
#include <iostream>
#include "linkedListNode.h"

//-----------------------------------------------------------------------------

// Constructor for initializing a Linked List Node
LinkedListNode::LinkedListNode() {

  m_data     = 0;
  m_nextNode = new int;
  m_prevNode = new int;

}

//-----------------------------------------------------------------------------

// Destructor for Linked List Node
LinkedListNode::~LinkedListNode() {

  // Free pointers
  delete m_nextNode;
  delete m_prevNode;
  m_nextNode = NULL;
  m_prevNode = NULL;

}

//-----------------------------------------------------------------------------

// Set the node data
void LinkedListNode::setNodeData(int value) {
  m_data = value;
}

//-----------------------------------------------------------------------------

// Print the node data
void LinkedListNode::printNodeData() {
  std::cout << m_data << " -> ";
}
